#include "ChannelManager.hpp"
#include "ClientManager.hpp"
#include "CommandHandler.hpp"
#include "Macros.hpp"
#include "Server.hpp"
#include "User.hpp"
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
	(void)_server_settings;

	std::string entered_pass = args;
	
	User &user = _user_manager.get_user(client.get_fd());


	if (user.get_is_registered())
	{
		client.write(ERR_ALREADYREGISTRED(SERVER_NAME));
		return ;
	}
	
	user.set_used_password(entered_pass);
}