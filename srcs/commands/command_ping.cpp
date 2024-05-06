#include "Client.hpp"
#include "ChannelManager.hpp"
#include <string>


void	command_ping(
	ChannelManager &_channel_manager,
	Client &client,
	std::string const &args
	)
{
	(void)args;
	(void)_channel_manager;
	client.write("PONG !\n");
}
