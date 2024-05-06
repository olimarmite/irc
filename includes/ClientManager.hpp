#pragma once

#include "Client.hpp"
#include "CommandHandler.hpp"
#include <map>

class ChannelManager;

class ClientManager {
private:
	std::map<int, Client> _clients;
	ChannelManager *_channel_manager;
	CommandHandler *_command_handler;

public:
	ClientManager();
	~ClientManager();

	void	init(ChannelManager &channel_manager, CommandHandler &command_handler);
	void	add_client(int client_fd);
	void	remove_client(int client_fd);
	Client &get_client(int client_fd);

};
