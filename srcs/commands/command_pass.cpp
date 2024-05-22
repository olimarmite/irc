#include "ChannelManager.hpp"
#include "ClientManager.hpp"
#include "CommandHandler.hpp"
#include "Server.hpp"
#include "UserManager.hpp"
#include "utils.hpp"
// #include <iostream>
// #include <string>
#include "IrcReplies.hpp"

void	command_pass(
	ChannelManager &_channel_manager,
	UserManager &_user_manager,
	ClientManager &_client_manager,
	const ServerSettings &_server_settings,
	Client &client,
	std::string const &args
	)
{
	(void)_channel_manager;
	(void)_user_manager;
	(void)_client_manager;
	(void)client;

	std::string entered_pass = args;
	if (entered_pass != _server_settings.password)
		client.disconnect();
}