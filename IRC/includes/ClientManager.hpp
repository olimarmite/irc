#pragma once

#include "Client.hpp"
#include "CommandHandler.hpp"
#include <map>

class ChannelManager;

class ClientManager {
private:
	std::map<int, Client> _clients;
	CommandHandler *_command_handler;


public:
	ClientManager();
	~ClientManager();

	void	init(CommandHandler &command_handler);
	void	add_client(int client_fd);
	void	remove_client(int client_fd);
	void	disconnect_all_clients();
	Client &get_client(int client_fd);
	void	destroy_unused_clients();
};
