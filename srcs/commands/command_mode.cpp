#include "IrcReplies.hpp"
#include "ChannelManager.hpp"
#include "ClientManager.hpp"
#include "CommandHandler.hpp"
#include "Server.hpp"
#include "User.hpp"
#include "UserManager.hpp"
#include <iostream>
#include <string>

void	command_mode(
	ChannelManager &_channel_manager,
	UserManager &_user_manager,
	ClientManager &_client_manager,
	const ServerSettings &_server_settings,
	Client &client,
	std::string const &args
	)
{
	(void)_channel_manager;
	(void)args;
	(void)_user_manager;
	(void)_client_manager;
	(void)_server_settings;

	(void)client;


	std::istringstream ss(args);

	std::string channel_name;
	std::string modestring;

	//si pas channel, ignorer le message, return

	if (!(ss >> channel_name >> modestring) || channel_name.empty() || modestring.empty())
	{
		client.write(ERR_NEEDMOREPARAMS(SERVER_NAME, "mode"));
		return ;
	}

	if (DEBUG)
	{
		std::cout << "channel_name: " << channel_name << std::endl;
		std::cout << "modestring: " << modestring << std::endl;
	}

	if (is_valid_mode(_channel_manager, client, channel_name, modestring) == false)
		return ;

	update_mode(_channel_manager, channel_name, modestring[0], modestring[1]);

	return ;
}
