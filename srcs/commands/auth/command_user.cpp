#include "ChannelManager.hpp"
#include "ClientManager.hpp"
#include "CommandHandler.hpp"
#include "Macros.hpp"
#include "Server.hpp"
#include "User.hpp"
#include "UserManager.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include "IrcReplies.hpp"

void	command_user(
	ChannelManager &_channel_manager,
	UserManager &_user_manager,
	ClientManager &_client_manager,
	const ServerSettings &_settings,
	Client &client,
	std::string const &args
	)
{
	// if (_user_manager.get_user(client.get_fd()))
	//<user> <mode> <unused> <realname>

	(void)_channel_manager;
	(void)_user_manager;
	(void)client;
	(void)args;
	(void)_client_manager;
	(void)_settings;


	std::string args_user;
	std::string args_mode;
	std::string args_unused;
	std::string args_realname;
	// USER octonaute octonaute irc.dal.net :Octo


	std::istringstream iss(args);
	iss >> args_user;
	iss >> args_mode;
	iss >> args_unused;
	iss >> args_realname;

	if (args_user.empty() || args_mode.empty() || args_unused.empty() || args_realname.empty())
	{
		client.write(ERR_NEEDMOREPARAMS(SERVER_NAME, "USER"));
		return ;
	}

	User &user = _user_manager.get_user(client.get_fd());
	if (user.get_username().empty())
	{
		user.set_username(args_user);
		// user.set_mode(args_mode);
		// user.set_realname(args_realname);
	}
	else
	{
		client.write(ERR_ALREADYREGISTRED(SERVER_NAME));
	}
	client.write("NOTICE AUTH :*** User registered\n");
	client.write(WELCOME_MESSAGE(user.get_username()));
}
