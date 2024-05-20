#include "../includes/Macros.hpp"
#include "../includes/utils.hpp"
#include "../includes/User.hpp"
#include "../includes/UserManager.hpp"
#include "../includes/ChannelManager.hpp"
#include "../includes/Client.hpp"
#include "../includes/ClientManager.hpp"
#include "../includes/IrcReplies.hpp"

bool	is_kick_valid(ChannelManager &_channel_manager, UserManager &_user_manager, Client &client, std::string const & channel_name, std::string const & nickname)
{
	(void)_channel_manager;
	(void)_user_manager;
	(void)client;
	(void)channel_name;
	(void)nickname;
	
	// if (_channel_manager.channel_exists(channel_name) == false)
	// {
	// 	client.write(ERR_NOSUCHCHANNEL(_user(), channel_name));
	// 	return false;
	// }

	// if (_channel_manager.is_user_in_channel(nickname, channel_name) == false)
	// {
	// 	client.write(ERR_USERNOTINCHANNEL(client.get_nickname(), nickname, channel_name));
	// 	return false;
	// }

	// if (_channel_manager.is_user_operator(client.get_fd(), channel_name) == false)
	// {
	// 	client.write(ERR_CHANOPRIVSNEEDED(client.get_nickname(), channel_name));
	// 	return false;
	// }
	return true;
}