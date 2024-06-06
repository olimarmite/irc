#include "ChannelManager.hpp"
#include "ClientManager.hpp"
#include "CommandHandler.hpp"
#include "Server.hpp"
#include "User.hpp"
#include "IrcReplies.hpp"
#include "UserManager.hpp"
#include <iostream>
#include <sstream>
#include <string>

void	command_user(
	ChannelManager &_channel_manager,
	UserManager &_user_manager,
	ClientManager &_client_manager,
	const ServerSettings &_server_settings,
	Client &client,
	std::string const &args
	)
{
	(void)_channel_manager;
	(void)_client_manager;
	(void)_server_settings;

	User &user = _user_manager.get_user(client.get_fd());

	std::istringstream ss(args);
	std::string username;
	std::getline(ss, username, ' ');

	if (username.empty())
	{
		client.write(ERR_NEEDMOREPARAMS(SERVER_NAME, "USER"));
		return ;
	}

	user.set_username(username);
	
	if (user.get_is_registered() == false
		&& user.get_nickname().empty() == false
		&& user.get_username().empty() == false)
	{

		if (user.get_used_password() == _server_settings.password)
		{
			client.write(WELCOME_MESSAGE(user.get_username(), user.get_nickname()));
			user.set_is_registered(true);
		}
		else {
			client.write(ERR_PASSWDMISMATCH(SERVER_NAME));
			client.disconnect();
		}
	}

	return ;
}
