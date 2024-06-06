#include "ChannelManager.hpp"
#include "ClientManager.hpp"
#include "CommandHandler.hpp"
#include "Server.hpp"
#include "User.hpp"
#include "UserManager.hpp"
#include "IrcReplies.hpp"
#include "utils.hpp"
#include <iostream>
#include <string>

void	command_nick(
	ChannelManager &_channel_manager,
	UserManager &_user_manager,
	ClientManager &_client_manager,
	const ServerSettings &_server_settings,
	Client &client,
	std::string const &args
	)
{
	(void)_server_settings;
	(void)_channel_manager;
	(void)_client_manager;

	bool nick_conflict = false;

	User	& user = _user_manager.get_user(client.get_fd());

	if (is_nickname_valid(args, _user_manager, user, client, &nick_conflict) == false)
		return ;

	if (nick_conflict)
		return ; 
	user.set_nickname(args);

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
	else {
		client.write(NICK_CHANGED(user.get_nickname(), user.get_username(), args, "NICK")); 
	}
}
