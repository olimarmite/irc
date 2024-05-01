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

size_t findEndOfWordInString(const std::string& str, const std::string& word)
{
	size_t start = str.find(word);
	if (start != std::string::npos) {
		return start + word.length();
	} else {
		// Word not found
		return std::string::npos;
	}
}

std::string	Server::ask_for_username(int user_fd, std::string input, int type)
{
	std::string message;
	std::string entered_username;
	int i;
	int word_length;

	if (type == NETCAT)
	{
		message = "Enter username : \r\n";
		int bytes_sent = send(user_fd, message.c_str(), message.length(), MSG_NOSIGNAL);
		if (bytes_sent == INVALID_NB)
			throw std::runtime_error(ERROR_SEND);
		char buffer[1024 + 1];
		int bytes_read = read(user_fd, buffer, 1024);
		if (bytes_read == INVALID_NB)
			throw std::runtime_error(ERROR_READ);
		std::cout <<"bytes_read : " <<bytes_read <<std::endl;
		buffer[bytes_read] = '\0';
		std::string str_buffer(buffer);
		std::cout <<"buffer = " <<buffer <<std::endl;
		if (str_buffer.substr(0, 5) == "USER ")
		{
			entered_username = str_buffer.substr(5);
			std::cout <<"Entered username = " <<entered_username <<std::endl;
		}
		else
			throw std::runtime_error(ERROR_USER);
	}
	else if (type == IRSSI)
	{
		int pos = findEndOfWordInString(input, "USER ");
		if (pos != -1)
		{
			word_length = 0;
			i = pos;
			while (isalnum(input[i++]))
				word_length++;
			entered_username = input.substr(pos, word_length);
			std::cout <<"Entered username = " <<entered_username <<std::endl;
		}
		else
			throw std::runtime_error(ERROR_USER);
	}
	
	// if (isValidUsername(entered_username) == false)
	// {
			//throw error
			// close(user_fd)?
			// 		return NULL;
	// }

	return entered_username;
}

std::string	Server::ask_for_nickname(int user_fd, std::string input, int type)
{
	std::string message;
	std::string entered_nickname;
	int i;
	int word_length;

	if (type == NETCAT)
	{
		message = "Enter nickname : \r\n";
		int bytes_sent = send(user_fd, message.c_str(), message.length(), MSG_NOSIGNAL);
		if (bytes_sent == INVALID_NB)
			throw std::runtime_error(ERROR_SEND);
		char buffer[1024 + 1];
		sleep(4); //FIX : read suivant return chars chelou ou vide. N'attend pas que j'ecrive
		int bytes_read = read(user_fd, buffer, 1024);
		if (bytes_read == INVALID_NB)
			throw std::runtime_error(ERROR_READ);
		std::cout <<"bytes_read : " <<bytes_read <<std::endl;
		buffer[bytes_read] = '\0';
		std::string str_buffer(buffer);
		std::cout <<"buffer = " <<buffer <<std::endl;
		if (str_buffer.substr(0, 7) == "\r\nNICK ")
		{
			entered_nickname = str_buffer.substr(7);
			std::cout <<"Entered nickname = " <<entered_nickname <<std::endl;
		}
		else
			throw std::runtime_error(ERROR_NICK);
	}
	else if (type == IRSSI)
	{
		int pos = findEndOfWordInString(input, "NICK ");
		if (pos != -1)
		{
			word_length = 0;
			i = pos;
			while (isalnum(input[i++]))
				word_length++;
			entered_nickname = input.substr(pos, word_length);
			std::cout <<"Entered nickname = " <<entered_nickname <<std::endl;
		}
		else
			throw std::runtime_error(ERROR_NICK);
	}

	// if (isValidNickame(entered_nickname) == false)
	// {
			//throw error
			// close(user_fd)?
			// 		return NULL;
	// }

	return entered_nickname;
}

void	Server::ask_for_password(int user_fd, std::string input, int type)
{
	std::string message;
	std::string entered_password;
	int i;
	int word_length;

	if (type == NETCAT)
	{
		message = "Enter password : \r\n";
		int bytes_sent = send(user_fd, message.c_str(), message.length(), MSG_NOSIGNAL);
		if (bytes_sent == INVALID_NB)
			throw std::runtime_error(ERROR_SEND);
		char buffer[1024 + 1];
		int bytes_read = read(user_fd, buffer, 1024);
		if (bytes_read == INVALID_NB)
			throw std::runtime_error(ERROR_READ);
		buffer[bytes_read] = '\0';
		std::string str_buffer(buffer);
		if (str_buffer.substr(0, 5) == "PASS ")
		{
			entered_password = str_buffer.substr(5);
			std::cout <<"Entered password = [" <<entered_password <<"]" <<std::endl;
		}
		else
			throw std::runtime_error(ERROR_PSWD);
	}
	else if (type == IRSSI)
	{
		int pos = findEndOfWordInString(input, "PASS ");
		if (pos != -1)
		{
			word_length = 0;
			i = pos;
			while (isalnum(input[i++]))
				word_length++;
			entered_password = input.substr(pos, word_length);
			std::cout <<"Entered password = " <<entered_password <<std::endl;
		}
		else
			throw std::runtime_error(ERROR_PSWD);
	}

	if (entered_password != _password)
	{
		message = "Invalid password : connection to server refused\r\n";
		int bytes_sent = send(user_fd, message.c_str(), message.length(), MSG_NOSIGNAL); //le proteger
		if (bytes_sent == INVALID_NB)
			throw std::runtime_error(ERROR_SEND);
		close (user_fd);
		throw std::runtime_error(ERROR_PASSW);
	}
}

User	Server::create_user(int user_fd)
{
	User newUser(user_fd);
	std::string entered_username;
	std::string entered_nickname;
	char buffer[1024];
	std::string input;
	ssize_t bytes_read = 0;
	bool type;


	// // Set socket to non-blocking mode
	// int flags = fcntl(user_fd, F_GETFL, 0);
	// if (flags == -1)
	// {
	// 	// perror("fcntl");
	// 	// return;
	// 	std::cout <<"error" <<std::endl;
	// }
	// flags |= O_NONBLOCK;
	// if (fcntl(user_fd, F_SETFL, flags) == -1)
	// {
	// 	// perror("fcntl");
	// 	// return;
	// 	std::cout <<"error" <<std::endl;
	// }

	bytes_read = read(user_fd, buffer, sizeof(buffer) - 1);
	if (bytes_read > 0)
	{
		// type = IRSSI;
		buffer[bytes_read] = '\0';
		input = buffer; //tansform from char * to str
		// std::cout <<"input = " <<input <<std::endl;
		/*--> irssi envoie tout d'un coup le pass, nick et user,
		ce n'est pas à nous de les écrire car il les get
		automatiquement. */
	}
	// else
	// 	type = NETCAT;

	if (input.substr(0, 6) == "CAP LS") //on est dans irssi
		type = IRSSI;
	else
		type = NETCAT;

	ask_for_password(user_fd, input, type);
	std::cout <<"Password accepted" <<std::endl;
	entered_nickname = ask_for_nickname(user_fd, input, type);
	std::cout <<"Nickname accepted" <<std::endl;
	newUser.setNickname(entered_nickname);
	entered_username = ask_for_username(user_fd, input, type);
	newUser.setUsername(entered_username);
	std::cout <<"Username accepted" <<std::endl;

	_userList.push_back(newUser);
	// std::cout <<"User added to _clientList" <<std::endl;

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