#include "../includes/Server.hpp"

Server::Server(std::string port, std::string password)
: _port(port), _password(password), _server_fd(INVALID_FD), _epoll_fd(INVALID_FD)
{
}

Server::~Server()
{
	//lignes suivantes creent segfault lorsque password insere par user est incorrect
	// for (int i = 0; _userList[i].getUsername() != ""; i++) //pas sure de cette condition
	// 	close(_userList[i].getFd());
	close(_server_fd);
	close(_epoll_fd);
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

void	Server::send_welcome_message(User user)
{
	std::string message = WELCOME_MESSAGE(user.getUsername());

	int bytes_sent = send(user.getFd(), message.c_str(), message.length(), MSG_NOSIGNAL);
	if (bytes_sent == INVALID_NB)
		throw std::runtime_error(ERROR_FAIL_MSG + static_cast<std::string>(gai_strerror(bytes_sent)));
}

// User	Server::create_user(int user_fd)
// {
// /* TODO : Tous les messages envoyes par le serveur et par le user doivent finir par \r\n
// Du coup lancer : nc -C localhost 1500 */

// 	User newUser(user_fd);
// 	char input[1024];
// 	std::string message;
// 	int bytes_read = 0;
// 	int bytes_sent = 0;
// 	int i;

// 	message = "Enter password : \r\n";
// 	bytes_sent = send(user_fd, message.c_str(), message.length(), MSG_NOSIGNAL);
// 	if (bytes_sent == INVALID_NB)
// 		throw std::runtime_error(ERROR_SEND);
// 	bytes_read = read(user_fd, input, sizeof(input));
// 	if (bytes_read == INVALID_NB)
// 		throw std::runtime_error(ERROR_READ);

// 	i = 0;
// 	while(input[i] != '\n')
// 		i++;
// 	input[i] = '\0';

// 	// std::cout <<"input = [" <<input <<"]" <<std::endl;
// 	// std::cout <<"password = [" <<_password <<"]" <<std::endl;

// 	if (input != _password)
// 	{
// 		message = "Invalid password : connection to server refused";
// 		send(user_fd, message.c_str(), message.length(), MSG_NOSIGNAL); //le proteger
// 		close (user_fd);
// 		throw std::runtime_error(ERROR_PASSW);
// 	}

// 	message = "Enter username : \r\n";
// 	bytes_sent = send(user_fd, message.c_str(), message.length(), MSG_NOSIGNAL);
// 	if (bytes_sent == INVALID_NB)
// 		throw std::runtime_error(ERROR_SEND);
// 	bytes_read = read(user_fd, input, sizeof(input));
// 	if (bytes_read == INVALID_NB)
// 		throw std::runtime_error(ERROR_READ);
// 	// if (isValidUsername(input) == false) //mettre dans utils.cpp?
// 	// {
// 			//throw error
// 			// close(user_fd)?
// 			// 		return NULL;
// 	// }

// 	i = 0;
// 	while(input[i] != '\n')
// 		i++;
// 	input[i] = '\0';

// 	newUser.setUsername(input);

// 	message = "Enter nickname : \r\n";
// 	bytes_sent = send(user_fd, message.c_str(), message.length(), MSG_NOSIGNAL);
// 	if (bytes_sent == INVALID_NB)
// 		throw std::runtime_error(ERROR_SEND);
// 	bytes_read = read(user_fd, input, sizeof(input));
// 	if (bytes_read == INVALID_NB)
// 		throw std::runtime_error(ERROR_READ);
// 	// if (isValidNickame(input) == false)
// 	// {
// 			//throw error
// 			// close(user_fd)?
// 			// 		return NULL;
// 	// }

// 	i = 0;
// 	while(input[i] != '\n')
// 		i++;
// 	input[i] = '\0';

// 	newUser.setNickname(input);

// 	_userList.push_back(newUser);

// 	return newUser;
// }

size_t findEndOfWordInString(const std::string& str, const std::string& word)
{
	size_t start = str.find(word);
	if (start != std::string::npos) {
		return start + word.length() - 1;
	} else {
		// Word not found
		return std::string::npos;
	}
}

User	Server::create_user(int user_fd)
{
	User newUser(user_fd);
	std::string message;
	std::string entered_password;
	std::string entered_username;
	std::string entered_nickname;
	std::string str_input;
	char input[1024];
	ssize_t bytes_read = 0;
	int bytes_sent = 0;
	int i;


	message = "Enter password : \r\n";
	bytes_sent = send(user_fd, message.c_str(), message.length(), MSG_NOSIGNAL);
	if (bytes_sent == INVALID_NB)
		throw std::runtime_error(ERROR_SEND);
	bytes_read = read(user_fd, input, sizeof(input) - 1);
	if (bytes_read > 0)
	{
		// input[bytes_read] = '\0'; //non car bytes_read > longueur du password
		i = 5;
		while (isalpha(input[i]))
			i++;
		input[i] = '\0';
		std::cout <<"Input = " <<input <<std::endl; //TEST
		str_input = input; //converts char * to string, declaration has to be on the same line
		if (str_input.substr(0, 5) == "PASS ")
		// int pos = findEndOfWordInString(str_input, "PASS "); //TEST
		// if (pos != -1) //TEST
		{
			// std::cout <<"Pos = " <<pos <<std::endl;
			// std::cout <<"beginning of password = " <<str_input[pos] <<std::endl; //TEST
			// std::cout <<"password = " <<str_input.substr(pos) <<std::endl; //TEST


			entered_password = str_input.substr(5);
			// entered_password = str_input.substr(pos); //TEST
			std::cout <<"Password = " <<entered_password <<std::endl;

			
			if (entered_password != _password)
			{
				message = "Invalid password : connection to server refused\r\n";
				send(user_fd, message.c_str(), message.length(), MSG_NOSIGNAL); //le proteger
				close (user_fd);
				throw std::runtime_error(ERROR_PASSW);
			}
		}
		else
			throw std::runtime_error(ERROR_PSWD);
	}

	message = "Enter nickname : \r\n";
	bytes_sent = send(user_fd, message.c_str(), message.length(), MSG_NOSIGNAL);
	if (bytes_sent == INVALID_NB)
		throw std::runtime_error(ERROR_SEND);
	bytes_read = read(user_fd, input, sizeof(input));
	if (bytes_read == INVALID_NB)
		throw std::runtime_error(ERROR_READ);
	// input[bytes_read] = '\0';
	i = 5;
	while (isalpha(input[i]))
		i++;
	input[i] = '\0';
	str_input = input;
	if (str_input.substr(0, 5) == "NICK ")
		entered_nickname = str_input.substr(5);
	else
		throw std::runtime_error(ERROR_NICK);
	// if (isValidNickame(entered_nickname) == false)
	// {
			//throw error
			// close(user_fd)?
			// 		return NULL;
	// }
	newUser.setNickname(entered_nickname);

	message = "Enter username : \r\n";
	bytes_sent = send(user_fd, message.c_str(), message.length(), MSG_NOSIGNAL);
	if (bytes_sent == INVALID_NB)
		throw std::runtime_error(ERROR_SEND);
	bytes_read = read(user_fd, input, sizeof(input));
	if (bytes_read == INVALID_NB)
		throw std::runtime_error(ERROR_READ);
	// input[bytes_read] = '\0';
	i = 5;
	while (isalpha(input[i]))
		i++;
	input[i] = '\0';
	str_input = input;
	if (str_input.substr(0, 5) == "USER ")
		entered_username = str_input.substr(5);
	else
		throw std::runtime_error(ERROR_USER);
	// if (isValidUsername(entered_username) == false) //mettre dans utils.cpp?
	// {
			//throw error
			// close(user_fd)?
			// 		return NULL;
	// }
	newUser.setUsername(entered_username);

	_userList.push_back(newUser);

	return newUser;
}


/* Accepts new user connection and returns their fd.
The new user_fd is added to epoll_ctl to be monitored
by epoll (which allows to receive future packages). */
void	Server::accept_connections(struct epoll_event * requests)
{
	struct sockaddr_in	userAddress;
	socklen_t			userAddressLength = sizeof(userAddress);
	int user_fd = INVALID_FD;
	struct epoll_event settings;
	int ret;
	User user;

	for (int i = 0; requests[i].data.fd; i++)
	{
		if (requests[i].data.fd == _server_fd)
		{
			user_fd = accept(_server_fd, (struct sockaddr*)&userAddress, &userAddressLength);
			if (user_fd == INVALID_FD)
			{
				std::cerr << "Failed to add user socket to epoll instance." << std::endl;
				close(user_fd);
			}

			settings.events = EPOLLIN;
			settings.data.fd = user_fd;
			ret = epoll_ctl(_epoll_fd, EPOLL_CTL_ADD, user_fd, &settings);
			if (ret == INVALID_NB)
				throw std::runtime_error(ERROR_EPOLL_CTL + static_cast<std::string>(strerror(errno)));

			user = create_user(user_fd);
			send_welcome_message(user);

			//TODO : delete les requests[i] qui ont ete acceptees
		}
	}
}

void	Server::manage_requests(struct epoll_event * requests)
{
	accept_connections(requests);

	//TODO ici : gerer les commandes comme create channels, send msg, etc

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
	struct epoll_event * requests;

	requests = poll_for_requests(); //requests = connection, msg, commands
	manage_requests(requests); //creates chanels, etc
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
		throw std::runtime_error(ERROR_EPOLL_CREATE + static_cast<std::string>(strerror(errno)));

//ajout du server_fd à epoll
	settings.events = EPOLLIN;
	settings.data.fd = server_fd;
	ret = epoll_ctl(epoll_fd, EPOLL_CTL_ADD, server_fd, &settings);
	if (ret == INVALID_NB)
		throw std::runtime_error(ERROR_EPOLL_CTL + static_cast<std::string>(strerror(errno)));

	return epoll_fd;
}

/* Sets the server socket (= its fd) to listening mode.
This tells the operating system that it wishes to start
receiving connections. The server then queues incoming
connections from users until it accepts or declines them.
fcntl allows the listen() function to be non-blocking. */
void	Server::listen_to_users_requests(int const & server_fd)
{
	int ret;

	ret = listen(server_fd, MAX_PENDING_CONNECTIONS);
	if ( ret == INVALID_LISTEN)
		throw std::runtime_error(ERROR_LISTEN);

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
	struct addrinfo server_settings = set_settings();
	int server_fd = create_socket(server_settings);
	bind_socket_to_port(server_settings, server_fd);
	listen_to_users_requests(server_fd);
	int epoll_fd = launch_epoll(server_fd);

	//free server_settings ici?

	_epoll_fd = epoll_fd;
	_server_fd = server_fd;
}