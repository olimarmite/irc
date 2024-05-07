
#include "ChannelManager.hpp"
#include "ClientManager.hpp"
#include "CommandHandler.hpp"
#include "Server.hpp"
#include "User.hpp"
#include "UserManager.hpp"
#include <iostream>
#include <string>


void	command_topic(
	ChannelManager &_channel_manager,
	UserManager &_user_manager,
	Client &client,
	std::string const &args
	)
{
	(void)_channel_manager;
	(void)args;
	(void)_user_manager;
	(void)client;

	//TODO
	return ;
}
