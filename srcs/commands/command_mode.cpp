
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
	Client &client,
	std::string const &args
	)
{
	(void)_channel_manager;
	(void)args;
	(void)_user_manager;
	(void)client;

	std::cout << args << PRINT_END;

	//HERE parsing peut etre different selon dans channels ou pas
	//TODO /MODE #test42 i
	return ;
}
