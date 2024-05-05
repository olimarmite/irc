#pragma once

#include "ChannelManager.hpp"
#include "Client.hpp"
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
		std::string _password;
		int _server_fd;
		int _epoll_fd;
		std::map<int, Client> _clients;

		void	_add_client(int client_fd);
		void	_check_epoll_events();
		void	_setup_epoll();
		void	_setup_socket();

		//TODO move this to main
		ChannelManager _channel_manager;
		CommandHandler _command_handler;

	public :
		Server(int port, std::string password);
		~Server();

		void 				init();
		void 				run();

		ChannelManager &	get_channel_manager(); //TODO remove this
		CommandHandler &	get_command_handler(); //TODO remove this

		Client &			get_client(int fd);
		void				remove_client(int fd);
};
