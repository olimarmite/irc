
#include "ChannelManager.hpp"
#include "ClientManager.hpp"
#include "CommandHandler.hpp"
#include "Server.hpp"
#include "User.hpp"
#include "UserManager.hpp"
#include "utils.hpp"
#include <iostream>
#include <string>

void	command_nick(
	ChannelManager &_channel_manager,
	UserManager &_user_manager,
	Client &client,
	std::string const &args
	)
{
	(void)_channel_manager;
	(void)args;
	(void)_user_manager;

	User	& user = _user_manager.get_user(client.get_fd());
	
	if (is_nickname_valid(args, _user_manager, user) == false)
		return ;

	user.set_nickname(args);
	//???
	// >> :kquerel!~kquerel@7026-7ad1-fcef-778e-fe1c.210.62.ip NICK :new_nickname
	// std::string	error_msg = ":" + SERVER_NAME + " 432 " + user.get_nickname() + " " + nickname + " :Erroneous Nickname";
	// send(user.get_fd(), error_msg.c_str(), error_msg.length(), 0);
	client.write("Changed nickname to " + args + "\n");
}
