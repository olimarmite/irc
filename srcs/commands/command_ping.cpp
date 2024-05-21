#include "Client.hpp"
#include "ChannelManager.hpp"
#include "IrcReplies.hpp"
#include "UserManager.hpp"
#include <cstdlib>
#include <string>


void	command_ping(
	ChannelManager &_channel_manager,
	UserManager &_user_manager,
	ClientManager &_client_manager,
	const ServerSettings &_server_settings,
	Client &client,
	std::string const &args
	)
{
	(void)args;
	(void)_channel_manager;
	(void)_client_manager;
	(void)_server_settings;

	User	& user = _user_manager.get_user(client.get_fd());
	client.write(PONG_MSG(SERVER_NAME, user.get_nickname()));
	return ;
}
