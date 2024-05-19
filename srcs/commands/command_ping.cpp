#include "Client.hpp"
#include "ChannelManager.hpp"
#include "IrcReplies.hpp"
#include "UserManager.hpp"
#include <cstdlib>
#include <string>


void	command_ping(
	ChannelManager &_channel_manager,
	UserManager &_user_manager,
	Client &client,
	std::string const &args
	)
{
	(void)args;
	(void)_channel_manager;
	(void)_user_manager;
	// >> :serenity.fl.us.dal.net PONG serenity.fl.us.dal.net :kquerel

	User	& user = _user_manager.get_user(client.get_fd());
	client.write(PONG_MSG(SERVER_NAME, user.get_nickname()));
}
