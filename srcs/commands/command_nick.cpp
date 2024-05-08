
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
	client.write("Changed nickname to " + args + "\n");
}
