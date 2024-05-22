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
	(void)_server_settings;

	User& user = _user_manager.get_user(client.get_fd());
	if (user.get_is_authenticated() == false)
	{
		client.write(ERR_NOTREGISTERED(SERVER_NAME));
		return ;
	}

	std::istringstream ss(args);
	std::string channel_name, modestring, mode_arg;
	if (!(ss >> channel_name >> modestring) || channel_name.empty() || modestring.empty())
	{
		client.write(ERR_NEEDMOREPARAMS(SERVER_NAME, "mode"));
		return ;
	}

	if (channel_name == user.get_nickname())
		return ;

	if (!(ss >> mode_arg))
		mode_arg = "";

	if (is_valid_mode(_channel_manager, client, channel_name, modestring, mode_arg) == false)
		return ;

	update_mode(_channel_manager, _user_manager, _client_manager, channel_name, modestring[0], modestring[1], mode_arg, client.get_fd());

	return ;
}
