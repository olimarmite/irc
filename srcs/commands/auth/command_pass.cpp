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

void	command_pass(
	ChannelManager &_channel_manager,
	UserManager &_user_manager,
	ClientManager &_client_manager,
	const ServerSettings &_settings,
	Client &client,
	std::string const &args
	)
{
	(void)_channel_manager;
	(void)_client_manager;

	std::string password = args;

	User &user = _user_manager.get_user(client.get_fd());
	if (user.get_username().empty() == false || user.get_is_authenticated() == true)
	{
		client.write(ERR_ALREADYREGISTRED(SERVER_NAME));
		return ;
	}
	std::cout << "password: " << '"' <<password << '"'<<  std::endl;
	std::cout << "is auth ? " << user.get_is_authenticated() << std::endl;
	if (password != _settings.password)
	{
		std::cout << "password mismatch" << std::endl;
		client.write(ERR_PASSWDMISMATCH(SERVER_NAME));
		// client.disconnect();
		return ;
	}
	std::cout << "success" << std::endl;
	user.set_is_authenticated(true);
	std::cout << "is auth ? " << user.get_is_authenticated() << std::endl;
}
