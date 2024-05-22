#include "ClientManager.hpp"
#include "CommandHandler.hpp"
#include "Macros.hpp"
#include "Server.hpp"
#include <netinet/in.h>
#include <stdexcept>
#include <string>
#include <sys/socket.h>

Server::Server(std::string port) : _port(port),
	_server_fd(INVALID_FD), _epoll_fd(INVALID_FD)
{
}

Server::~Server()
{
	if (_server_fd != INVALID_FD)
	{
		close(_server_fd);
	}
	if (_epoll_fd != INVALID_FD)
	{
		close(_epoll_fd);
	}
}

/* Sets the server socket (= its fd) to listening mode.
This tells the operating system that it wishes to start
receiving connections. The server then queues incoming
connections from users until it accepts or declines them.
fcntl allows the listen() function to be non-blocking. */
void	Server::listen_to_users_requests()
{
	int ret;

	ret = listen(_server_fd, MAX_PENDING_CONNECTIONS);
	if ( ret == INVALID_LISTEN)
		throw std::runtime_error(ERROR_LISTEN(errno));

	if (DEBUG)
		std::cout << "Server socket set to listening mode" << std::endl;
}

/* Binds the socket to the server's port/IP to allow
to receive and send data on and from said socket.
Getaddrinfo() fills server_info with all the info needed to
bind the socket to the port such as IP, port, protocol, etc.
server_info tells getaddrinfo what it should look for and
server_info is filled with what it found.*/
void	Server::bind_socket_to_port(struct addrinfo server_settings)
{
	int ret;
	struct addrinfo* server_info;

	ret = getaddrinfo(NULL, _port.c_str(), &server_settings, &server_info);
	if (ret != 0)
		throw std::runtime_error(ERROR_GETADDRINFO(errno));

	ret = bind(_server_fd, server_info->ai_addr, server_info->ai_addrlen);
	if (ret == INVALID_PORT)
		throw std::runtime_error(ERROR_BIND(errno));

	freeaddrinfo(server_info);

	if (DEBUG)
		std::cout << "Server socket binded to port" << std::endl;

}

/* Creates a file descriptor (such as open()). */
int	Server::create_socket(struct addrinfo const & settings)
{
	int server_fd;

	server_fd = socket(settings.IP_TYPES, settings.SOCKET_TYPE, settings.PROTOCOL);
	if (server_fd == INVALID_FD)
	{
		throw std::runtime_error(ERROR_SOCKET(errno)); // + errno
	}

//--------------------------------------TEST
// Set the socket to non-blocking mode
	int flags = fcntl(server_fd, F_GETFL, 0);
	if (flags == -1)
		throw std::runtime_error(ERROR_FCNTL(errno));

	flags |= O_NONBLOCK;
	int ret = fcntl(server_fd, F_SETFL, flags);
	if (ret == -1)
		throw std::runtime_error(ERROR_FCNTL(errno));

//--------------------------------------TEST

	if (DEBUG)
		std::cout << "Server socket created" << std::endl;

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

	if (DEBUG)
		std::cout << "Server socket settings set" << std::endl;

	return settings;
}

void Server::_setup_socket()
{
	struct addrinfo server_settings = set_settings();
	_server_fd = create_socket(server_settings);
	bind_socket_to_port(server_settings);
	listen_to_users_requests();

	if (DEBUG)
		std::cout << "Server socket setup done" << std::endl;
}

void Server::_setup_epoll()
{
	struct epoll_event settings;

//epoll_fd est un fd de controle, il nous permet d'interragir avec epoll
	_epoll_fd = epoll_create1(0); //avec flag 0 c'est l'équivalent d'utiliser l'ancienne fx epoll_create()
	if (_epoll_fd == INVALID_FD)
		throw std::runtime_error(ERROR_EPOLL_CREATE(errno));

//ajout du server_fd à epoll
	settings.events = EPOLLIN;
	settings.data.fd = _server_fd;
	if (epoll_ctl(_epoll_fd, EPOLL_CTL_ADD, _server_fd, &settings) == INVALID_NB)
		throw std::runtime_error(ERROR_EPOLL_CTL(errno));

	if (DEBUG)
		std::cout << "Epoll setup done" << std::endl;
}

void Server::_check_epoll_events()
{
	struct epoll_event	events[MAX_REQUESTS];
	int					event_count;

	event_count = epoll_wait(_epoll_fd, events, MAX_REQUESTS, -1); //-1 = timeout (wait until something happens)

	if (DEBUG)
		std::cout << "Event count: " << event_count << std::endl;

	if (event_count == -1)
	{
		throw std::runtime_error(ERROR_EPOLL_WAIT(errno));
	}
	for (int i = 0; i < event_count; i++)
	{
		if (events[i].data.fd == _server_fd)
			_accept_new_client();
		else
		{
			if (_client_manager->get_client(events[i].data.fd).read() == 0)
				_client_manager->remove_client(events[i].data.fd);
			//else : there is an event
		}
	}
}

void Server::init(ClientManager &client_manager)
{
	_client_manager = &client_manager;

	if (DEBUG)
		std::cout << "Server launching" << std::endl;
	_setup_socket();
	_setup_epoll();
	if (DEBUG)
		std::cout << "Server launched on port " << _port << std::endl <<std::endl;
}

void Server::run()
{
	_check_epoll_events();
}

void Server::_accept_new_client()
{
	int client_fd;

	client_fd = accept(_server_fd, NULL, NULL);
	if (client_fd == INVALID_FD)
	{
			throw std::runtime_error(ERROR_ACCEPT(errno));
	}

	if (DEBUG)
		std::cout <<"New client fd : " << client_fd << std::endl;

	struct epoll_event	settings;
	settings.events = EPOLLIN;
	settings.data.fd = client_fd;
	if (epoll_ctl(_epoll_fd, EPOLL_CTL_ADD, client_fd, &settings) == INVALID_NB)
	{
			throw std::runtime_error(ERROR_EPOLL_CTL(errno));
	}

	if (DEBUG)
		std::cout << "New client connected: " << client_fd << std::endl;
	_client_manager->add_client(client_fd);
}
