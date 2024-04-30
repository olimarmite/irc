#include "../includes/Server.hpp"

Server::Server(std::string port, std::string password)
: _port(port), _password(password), _server_fd(INVALID_FD), _epoll_fd(INVALID_FD)
{
}


Server::~Server()
{
	/*Si le serveur ferme, les fd des users doivent-ils 
	etre egalement close?*/

	close(_server_fd);
	close(_epoll_fd);
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

/* Accepts new client connection and returns their fd.
The new client_fd is added to epoll_ctl to be monitored
by epoll (which allows to receive future packages). */
void	Server::accept_connections(struct epoll_event * requests)
{
	// accept() avant de verifier le mot de passe car il
	//faut pouvoir recevoir le mot de passe pour le test

	struct sockaddr_in	clientAddress;
	socklen_t			clientAddressLength = sizeof(clientAddress);
	int client_fd = INVALID_FD;

	for (int i = 0; requests[i].data.fd; i++)
	{
		if (requests[i].data.fd == _server_fd) //accept
		{
			client_fd = accept(_server_fd, (struct sockaddr*)&clientAddress, &clientAddressLength);
			if (client_fd == INVALID_FD)
			{
				std::cerr << "Failed to add client socket to epoll instance." << std::endl;
				close(client_fd);
			}

			struct epoll_event settings;
			int ret;


			//ajout du new client_fd à epoll
			settings.events = EPOLLIN;
			settings.data.fd = client_fd;
			ret = epoll_ctl(_epoll_fd, EPOLL_CTL_ADD, client_fd, &settings);
			if (ret == INVALID_NB)
				throw std::runtime_error(ERROR_EPOLL_CTL + static_cast<std::string>(strerror(errno)));

			_clients_fd_list.push_back(client_fd);
			std::cout << "Accepted client fd: " << client_fd << std::endl;
		}
		else //PRINT MESSAGE
		{
			int bytes_read = 0;
			char buffer[1024] = {0};
			bytes_read = read(requests[i].data.fd, buffer, 1024);
			if (bytes_read == INVALID_NB)
				std::cerr << "Failed to read from client socket." << std::endl;
			else
				std::cout << "Message from client: " << buffer << std::endl;
		}
	}
}

void	Server::manage_requests(struct epoll_event * requests)
{
	if (requests == NULL)
		return;
	accept_connections(requests);

	//TODO : commands like create channels, send msg, etc

	delete[] requests;
}

/* Epoll() returns the nb of requests from users.
Each user can send multiple requests.
Epoll() is more efficient than poll() and select()
because :
- it allocates less memory.
- when an event (=request) occurs, the user's socket is
automaticallly added to the list.
- it retuns a list with only the socket that had events
(so no need to iterate over the whole list of users).
- no need to use fcntl
- its "edge-triggering" mode allows to avoid having to
retrive the user's data right away (if you're not ready
to do something with it for example).
Timeout set to -1 because I have nothing else to do on the
background while waiting for user requests. */
struct epoll_event *	Server::poll_for_requests()
{
	int nb_of_requests = 0;
	struct epoll_event *requests = new epoll_event[MAX_REQUESTS]();
	int timeout = WAIT_UNTIL_SOMETHING_HAPPENS;

	nb_of_requests = epoll_wait(_epoll_fd, requests, MAX_REQUESTS, timeout);
	if (nb_of_requests == INVALID_NB)
		throw std::runtime_error(ERROR_EPOLL_WAIT + static_cast<std::string>(strerror(errno)));

	return requests;
}

void	Server::run()
{
	try
	{
		struct epoll_event * requests;

		requests = poll_for_requests(); //requests = connection, msg, commands
		manage_requests(requests); //creates chanels, etc
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	return ;
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

int	Server::launch_epoll(int server_fd)
{
	(void) server_fd;

	int epoll_fd = INVALID_FD;
	struct epoll_event settings;
	int ret;

//epoll_fd est un fd de controle, il nous permet d'interragir avec epoll
	epoll_fd = epoll_create1(0); //avec flag 0 c'est l'équivalent d'utiliser l'ancienne fx epoll_create() donc tester avec après
	if (epoll_fd == INVALID_FD)
	{
		throw std::runtime_error(ERROR_EPOLL_CREATE + static_cast<std::string>(strerror(errno)));
		return INVALID_FD;
	}

//ajout du server_fd à epoll
	settings.events = EPOLLIN;
	settings.data.fd = server_fd;
	ret = epoll_ctl(epoll_fd, EPOLL_CTL_ADD, server_fd, &settings);
	if (ret == INVALID_NB)
	{
		throw std::runtime_error(ERROR_EPOLL_CTL + static_cast<std::string>(strerror(errno)));
		return INVALID_FD;
	}

	return epoll_fd;
}

/* Sets the server socket (= its fd) to listening mode.
This tells the operating system that it wishes to start
receiving connections. The server then queues incoming
connections from clients until it accepts or declines them.
fcntl allows the listen() function to be non-blocking. */
void	Server::listen_to_users_requests(int const & server_fd)
{
	int ret;

	ret = listen(server_fd, MAX_PENDING_CONNECTIONS);
	if ( ret == INVALID_LISTEN)
	{
		throw std::runtime_error(ERROR_LISTEN);
		return ;
	}

/* 	ret = fcntl(server_fd, F_SETFL, O_NONBLOCK); /VAUT MIEUX JUSTE APRES CREATION SOCKET
	if (ret == INVALID_FCNTL)
		throw std::runtime_error(ERROR_FCNTL); */
}

/* Binds the socket to the server's port/IP to allow
to receive and send data on and from said socket. 
Getaddrinfo() fills server_info with all the info needed to
bind the socket to the port such as IP, port, protocol, etc.
server_info tells getaddrinfo what it should look for and
server_info is filled with what it found.*/
void	Server::bind_socket_to_port(struct addrinfo server_settings, int const & server_fd)
{
	int ret;
	struct addrinfo* server_info;

	ret = getaddrinfo(NULL, _port.c_str(), &server_settings, &server_info);
	if (ret != 0)
		throw std::runtime_error(ERROR_GETADDRINFO + static_cast<std::string>(gai_strerror(ret)));

	ret = bind(server_fd, server_info->ai_addr, server_info->ai_addrlen);
	if (ret == INVALID_PORT)
		throw std::runtime_error(ERROR_BIND + static_cast<std::string>(gai_strerror(ret)));

	freeaddrinfo(server_info);
}

/* Creates a file descriptor (such as open()). */
int	Server::create_socket(struct addrinfo const & settings)
{
	int server_fd;

	server_fd = socket(settings.IP_TYPES, settings.SOCKET_TYPE, settings.PROTOCOL);
	if (server_fd == INVALID_FD)
	{
		std::cerr << "Socket error: " << strerror(errno) << std::endl <<PRINT_END; //errno n'apparait pas bien intégré avec le throw qui suit
		throw std::runtime_error(ERROR_SOCKET);
	}

//--------------------------------------TEST
// Set the socket to non-blocking mode
	int flags = fcntl(server_fd, F_GETFL, 0);
	if (flags == -1)
		throw std::runtime_error(ERROR_FCNTL);

	flags |= O_NONBLOCK;
	int ret = fcntl(server_fd, F_SETFL, flags);
	if (ret == -1)
		throw std::runtime_error(ERROR_FCNTL);

//--------------------------------------TEST

	return server_fd;
}

struct addrinfo	Server::set_settings()
{
	struct addrinfo settings;

	memset(&settings, 0, sizeof(settings));
	settings.IP_TYPES = ALL_IP_TYPES;
	settings.SOCKET_TYPE = TCP_STREAM_SOCKET;
	settings.PROTOCOL = CHOOSE_AUTOMATICALLY;

	settings.SERVER_IP = LOCAL_IP; //used in bind()

	return settings;
}

void	Server::launch()
{
	try
	{
		struct addrinfo server_settings = set_settings();
		int server_fd = create_socket(server_settings);
		bind_socket_to_port(server_settings, server_fd);
		listen_to_users_requests(server_fd);
		int epoll_fd = launch_epoll(server_fd);

		//free server_settings ici?

		_epoll_fd = epoll_fd;
		_server_fd = server_fd;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}