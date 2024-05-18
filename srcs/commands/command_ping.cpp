#include "Client.hpp"
#include "ChannelManager.hpp"
#include "UserManager.hpp"
#include <cstdlib>
#include <string>


void	command_ping(
	ChannelManager &_channel_manager,
	UserManager &_user_manager,
	ClientManager &_client_manager,
	const ServerSettings &_settings,
	Client &client,
	std::string const &args
	)
{
	(void)args;
	(void)_channel_manager;
	(void)_user_manager;
	(void)_client_manager;
	(void)_settings;

	client.write("PONG !\n");
}
