
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
	Client &client,
	std::string const &args
	)
{
	(void)_channel_manager;
	(void)args;
	(void)_user_manager;

	#include <sstream>

	User& user = _user_manager.get_user(client.get_fd());
	std::stringstream ss;
	ss << "Nickname: " << user.get_nickname() << "\n";
	ss << "Username: " << user.get_username() << "\n";
	ss << "Authenticated: " << user.get_is_authenticated() << "\n";
	client.write(ss.str());
}
