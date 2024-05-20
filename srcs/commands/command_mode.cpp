#include "IrcReplies.hpp"
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
	// (void)client;

	//si pas channel, ignorer le message, return
	//CARO : rajouté la if ci-dessous pour éviter err_msg "no such channel" à la connexion
	//+ erreur valgrind reglee
	
	
	// HERE ->mode ne marche pas pour avec ca:
	/*
	User& user = _user_manager.get_user(client.get_fd());
	if (user.get_is_authenticated() == false)
		return ;
	*/
	// fin

	std::istringstream ss(args);
	std::string channel_name, modestring, mode_arg;

	if (!(ss >> channel_name >> modestring >> mode_arg) || channel_name.empty() || modestring.empty())
	{
		client.write(ERR_NEEDMOREPARAMS(SERVER_NAME, "mode"));
		return ;
	}

	if (DEBUG)
	{
		std::cout << "channel_name: " << channel_name << std::endl;
		std::cout << "modestring: " << modestring << std::endl;
	}

	if (is_valid_mode(_channel_manager, client, channel_name, modestring, mode_arg) == false)
		return ;

	update_mode(_channel_manager, channel_name, modestring[0], modestring[1], mode_arg, client.get_fd());

	return ;
}
