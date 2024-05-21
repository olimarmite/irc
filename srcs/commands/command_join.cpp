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
	ClientManager &_client_manager,
	const ServerSettings &_server_settings,
	Client &client,
	std::string const &args
	)
{
	(void)_client_manager;
	(void)_server_settings;
  
	// TODO faire user_limit

	std::istringstream	ss(args);
	std::string			channel_name, password_arg;
	if (!(ss >> channel_name) || channel_name.empty())
	{
		client.write(ERR_NEEDMOREPARAMS(SERVER_NAME, "join"));
		return ;
	}

	ss >> password_arg;

	if (is_check_all_channel_valid(channel_name, client, _channel_manager, password_arg) == false)
		return ;

	User user = _user_manager.get_user(client.get_fd());

	handle_join_command(_channel_manager, user, client, _client_manager, channel_name);

	return ;
}
