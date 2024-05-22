#pragma once

#include "ChannelManager.hpp"
#include "Client.hpp"
#include "ClientManager.hpp"
#include "CommandHandler.hpp"
#include "Macros.hpp"
#include "User.hpp"
#include "utils.hpp"


class Client;
class CommandHandler;

class Server
{
	private :

		std::string _port;
		int _server_fd;
		int _epoll_fd;

		void	_check_epoll_events();
		void	_setup_epoll();
		void	_setup_socket();
		void 	_accept_new_client();

		ClientManager *_client_manager;

		int				create_socket(struct addrinfo const & settings);
		struct addrinfo	set_settings();
		void			bind_socket_to_port(struct addrinfo server_settings);
		void			listen_to_users_requests();

	public :
		Server(std::string port);
		~Server();

		void 				init(ClientManager &client_manager);
		void 				run();
};
