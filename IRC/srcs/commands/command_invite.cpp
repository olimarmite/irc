#include "ChannelManager.hpp"
#include "ClientManager.hpp"
#include "CommandHandler.hpp"
#include "IrcReplies.hpp"
#include "Server.hpp"
#include "User.hpp"
#include "UserManager.hpp"
#include <iostream>
#include <sstream>
#include <string>

void	command_invite(
	ChannelManager &_channel_manager,
	UserManager &_user_manager,
	ClientManager &_client_manager,
	const ServerSettings &_server_settings,
	Client &client,
	std::string const &args
	)
{
	(void)_client_manager;
	(void)_server_settings;

	std::istringstream iss(args);
	std::string	nickname, channel_name;

	if (!(iss >> nickname >> channel_name) || channel_name.empty() || nickname.empty())
	{
		client.write(ERR_NEEDMOREPARAMS(SERVER_NAME, "invite"));
		return ;
	}

	if (is_valid_invite(channel_name, nickname, _user_manager, _channel_manager, client) == false)
		return ;

	handle_invite_command(_channel_manager, _user_manager, _client_manager, client, channel_name, nickname);

	return ;
}


