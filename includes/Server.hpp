#pragma once

#include "Client.hpp"
#include "Macros.hpp"
#include "User.hpp"
#include <map>

class Server
{
	private :
		int _port;
		std::string _password;
		int _server_fd;
		int _epoll_fd;
		std::map<int, Client> _clients;

		void	_add_client(int client_fd);
		void	_check_epoll_events();
		void	_setup_epoll();
		void	_setup_socket();

	public :
		Server(int port, std::string password);
		~Server();

		void 				launch();
		void 				run();
};
