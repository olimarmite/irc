
#include "ChannelManager.hpp"
#include "ClientManager.hpp"
#include "CommandHandler.hpp"
#include "Server.hpp"
#include "User.hpp"
#include "UserManager.hpp"
#include <iostream>
#include <string>
#include <sstream>


void	command_info(
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


	User& user = _user_manager.get_user(client.get_fd());
	std::stringstream ss;
	ss << "Nickname: " << user.get_nickname() << "\n";
	ss << "Username: " << user.get_username() << "\n";
	ss << "Authenticated: " << user.get_is_authenticated() << "\n";
	client.write(ss.str());
	return ;
}
