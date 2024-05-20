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

	(void)_channel_manager;
	(void)args;
	(void)_user_manager;
	(void)_client_manager;
	(void)_server_settings;

	std::string const & channel_name = args;
	std::string const & password = ""; // si la channel est en mode +k, il faut ajouter le password ici

	if (is_check_all_channel_valid(channel_name, password, client, _channel_manager) == false)
		return ;

	User user = _user_manager.get_user(client.get_fd());

	handle_join_command(_channel_manager, user, client, channel_name, password);

	return ;
}
