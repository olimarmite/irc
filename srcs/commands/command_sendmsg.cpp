#include "Client.hpp"
#include "ChannelManager.hpp"
#include <string>

void	command_sendmsg(
	ChannelManager &_channel_manager,
	UserManager &_user_manager,
	Client &client,
	std::string const &args
	)
{
	(void)client;
	(void)_user_manager;
	_channel_manager.send_message_to_channel("default", args);
}
