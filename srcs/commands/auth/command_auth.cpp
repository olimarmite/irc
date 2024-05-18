
#include "ChannelManager.hpp"
#include "ClientManager.hpp"
#include "CommandHandler.hpp"
#include "Server.hpp"
#include "User.hpp"
#include "UserManager.hpp"
#include <iostream>
#include <string>


void	command_auth(
	ChannelManager &_channel_manager,
	UserManager &_user_manager,
	ClientManager &_client_manager,
	const ServerSettings &_settings,
	Client &client,
	std::string const &args
	)
{
	(void)_channel_manager;
	(void)args;
	(void)_user_manager;
	(void)_client_manager;
	(void)_settings;


	User& user = _user_manager.get_user(client.get_fd());
	user.set_is_authenticated(true);
	client.write("Authenticated\n");
	return ;
}
