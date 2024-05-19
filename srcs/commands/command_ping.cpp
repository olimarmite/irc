#include "Client.hpp"
#include "ChannelManager.hpp"
#include "IrcReplies.hpp"
#include "UserManager.hpp"
#include <cstdlib>
#include <string>


void	command_ping(
	ChannelManager &_channel_manager,
	UserManager &_user_manager,
	Client &client,
	std::string const &args
	)
{
	(void)args;
	(void)_channel_manager;
	(void)_user_manager;
	client.write("PONG !\n");
}
