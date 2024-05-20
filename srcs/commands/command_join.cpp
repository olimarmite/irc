#include "ChannelManager.hpp"
#include "ClientManager.hpp"
#include "CommandHandler.hpp"
#include "Server.hpp"
#include "UserManager.hpp"
#include "utils.hpp"
#include <iostream>
#include <string>
#include "IrcReplies.hpp"

void	command_join(
	ChannelManager &_channel_manager,
	UserManager &_user_manager,
	Client &client,
	std::string const &args
	)
{

	std::string const & channel_name = args;
	std::string const & password = _channel_manager.get_channel(channel_name).password;

	if (is_check_all_channel_valid(channel_name, password, client, _channel_manager) == false)
		return ;
	
	User user = _user_manager.get_user(client.get_fd());

	handle_join_command(_channel_manager, user, client, channel_name, password);

	return ;
}
