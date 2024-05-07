#pragma once

#include "ChannelManager.hpp"
#include "Client.hpp"
#include "ClientManager.hpp"
#include "CommandHandler.hpp"
#include "Macros.hpp"
#include "User.hpp"
#include <map>


class Client;
class CommandHandler;

class Server
{
	private :
		int _port;
		std::string _password; // passer ca dans une autre classe
		int _server_fd;
		int _epoll_fd;

		void	_check_epoll_events();
		void	_setup_epoll();
		void	_setup_socket();
		void 	_accept_new_client();

		ClientManager *_client_manager;


	public :
		Server(int port, std::string password);
		~Server();

		void 				init(ClientManager &client_manager);
		void 				run();

		ChannelManager &	get_channel_manager(); //TODO remove this
		CommandHandler &	get_command_handler(); //TODO remove this

};
