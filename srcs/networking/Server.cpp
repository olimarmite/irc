#include "ClientManager.hpp"
#include "CommandHandler.hpp"
#include "Macros.hpp"
#include "Server.hpp"
#include <netinet/in.h>
#include <stdexcept>
#include <string>
#include <sys/socket.h>

Server::Server(int port, std::string password) : _port(port),
	_password(password), _server_fd(INVALID_FD), _epoll_fd(INVALID_FD)
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

void Server::_setup_socket()
{
	struct sockaddr_in	addr;

	// TODO use getaddrinfo
	_server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (_server_fd == -1)
	{
		throw std::runtime_error(strerror(errno));
	}
	addr.sin_family = PF_INET;
	addr.sin_port = htons(_port);
	addr.sin_addr.s_addr = INADDR_ANY;
	bzero(&(addr.sin_zero), 8);
	if (bind(_server_fd, (const struct sockaddr *)&addr,
			sizeof(struct sockaddr)) == -1)
	{
		throw std::runtime_error(strerror(errno));
	}
	if (listen(_server_fd, MAX_PENDING_CONNECTIONS) == -1)
	{
		throw std::runtime_error(strerror(errno));
	}
}

void Server::_setup_epoll()
{
	struct epoll_event	event;

	_epoll_fd = epoll_create1(0);
	if (_epoll_fd == -1)
	{
		throw std::runtime_error(strerror(errno));
	}
	event.events = EPOLLIN;
	event.data.fd = _server_fd;
	if (epoll_ctl(_epoll_fd, EPOLL_CTL_ADD, _server_fd, &event) == -1)
	{
		throw std::runtime_error(strerror(errno));
	}
}

void Server::_check_epoll_events()
{
	struct epoll_event	events[MAX_REQUESTS];
	int					event_count;

	event_count = epoll_wait(_epoll_fd, events, MAX_REQUESTS, -1);
	std::cout << "Event count: " << event_count << std::endl;
	if (event_count == -1)
	{
		throw std::runtime_error(strerror(errno));
	}
	for (int i = 0; i < event_count; i++)
	{
		if (events[i].data.fd == _server_fd)
		{
			_accept_new_client();
		}
		else
		{
			std::cout << "Client event" << std::endl;
			if (_client_manager->get_client(events[i].data.fd).read() == 0)
			{
				std::cout << "read() == 0" << std::endl;
				_client_manager->remove_client(events[i].data.fd);
			}
		}
	}
}

void Server::init(ClientManager &client_manager)
{
	_client_manager = &client_manager;

	std::cout << "Server launching" << std::endl;
	_setup_socket();
	_setup_epoll();
	std::cout << "Server launched on port " << _port << std::endl;
}

void Server::run()
{
	_check_epoll_events();
}

void Server::_accept_new_client()
{
	int client_fd;

	client_fd = accept(_server_fd, NULL, NULL);
	if (client_fd == -1)
	{
		throw std::runtime_error(strerror(errno));
	}

	struct epoll_event	event;
	event.events = EPOLLIN;
	event.data.fd = client_fd;
	if (epoll_ctl(_epoll_fd, EPOLL_CTL_ADD, client_fd, &event) == -1)
	{
		throw std::runtime_error(strerror(errno));
	}

	std::cout << "New client connected: " << client_fd << std::endl;
	_client_manager->add_client(client_fd);
}
