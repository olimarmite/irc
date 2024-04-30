#pragma once

#include "Macros.hpp"

class Server
{
	private :
		std::string _port;
		std::string _password;

		int _server_fd;
		int _epoll_fd;

		std::vector<int>	_clients_fd_list;

		int						create_socket(struct addrinfo const & settings);
		struct addrinfo			set_settings();
		void					bind_socket_to_port(struct addrinfo server_settings, int const & server_fd);
		void					listen_to_users_requests(int const & server_fd);
		struct epoll_event *	poll_for_requests();
		int						launch_epoll(int server_fd);
		void					manage_requests(struct epoll_event * requests);
		void					accept_connections(struct epoll_event * requests);
	
	public :
		Server(std::string port, std::string password);
		~Server();
 
		void 				launch();
		void 				run();

};