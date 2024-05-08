#include "Client.hpp"
#include "ChannelManager.hpp"
#include "UserManager.hpp"
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
	(void)_channel_manager;
	(void)args;
	//TODO
	// _channel_manager.send_message_to_channel(_channel_manager.get_channel(), args);
}
