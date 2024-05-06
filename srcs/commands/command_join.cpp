#include "ChannelManager.hpp"
#include "ClientManager.hpp"
#include "CommandHandler.hpp"
#include "Server.hpp"
#include <iostream>
#include <string>

void	command_join(
	ChannelManager &_channel_manager,
	Client &client,
	std::string const &args
	)
{
	(void)_channel_manager;
	(void)args;
	_channel_manager.join_channel(client.get_fd(), args);
	// server.get_channel_manager().join_channel(client, args);
}
