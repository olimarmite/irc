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
	(void)_channel_manager;

	User	& user = _user_manager.get_user(client.get_fd());

	if (is_nickname_valid(args, _user_manager, user, client) == false)
		return ;

	if (DEBUG)
		std::cout << "old nickname = " <<user.get_nickname() <<std::endl;

	// TODO handle_nick_command
	client.write(NICK_CHANGED(user.get_nickname(), user.get_username(), args, "NICK"));
	user.set_nickname(args);

	if (DEBUG)
		std::cout << "new nickname = " <<user.get_nickname() <<std::endl;

	if (DEBUG)
	{
		std::cout <<"ALL USERS : " <<std::endl;
		_user_manager.print_all_users();
	}
}
