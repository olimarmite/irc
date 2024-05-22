#include "ChannelManager.hpp"
#include "ClientManager.hpp"
#include "CommandHandler.hpp"
#include "Server.hpp"
#include "User.hpp"
#include "UserManager.hpp"
#include "IrcReplies.hpp"
#include "utils.hpp"
#include <iostream>
#include <string>

void	command_nick(
	ChannelManager &_channel_manager,
	UserManager &_user_manager,
	ClientManager &_client_manager,
	const ServerSettings &_server_settings,
	Client &client,
	std::string const &args
	)
{
	// FIX nick qui marche pas bien a un impact sur kick
	
	// TODO quand 2nd user change de nick, msg n'apparait pas
	// -> peut etre pas bon client avec le write

	(void)_server_settings;
	(void)_channel_manager;
	(void)_client_manager;

	bool nick_conflict = false;

	User	& user = _user_manager.get_user(client.get_fd());

	if (is_nickname_valid(args, _user_manager, user, client, &nick_conflict) == false)
		return ;
		

	if (DEBUG)
		std::cout << "old nickname = " <<user.get_nickname() <<std::endl;

	client.write(NICK_CHANGED(user.get_nickname(), user.get_username(), args, "NICK")); 
	user.set_nickname(args);

	if (DEBUG)
		std::cout << "new nickname = " <<user.get_nickname() <<std::endl;

	if (DEBUG)
	{
		std::cout <<"ALL USERS : " <<std::endl;
		_user_manager.print_all_users();
	}

	if (nick_conflict == false && user.get_is_authenticated() == false)
	{
		client.write(WELCOME_MESSAGE(user.get_username(), user.get_nickname()));
		user.set_is_authenticated(true);
		if (DEBUG)
			std::cout <<BHGRN <<"User authentification set to true" <<PRINT_END;
	}
}
