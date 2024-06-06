#include "../includes/Macros.hpp"
#include "../includes/utils.hpp"
#include "../includes/User.hpp"
#include "../includes/UserManager.hpp"
#include "../includes/ChannelManager.hpp"
#include "../includes/Client.hpp"
#include "../includes/ClientManager.hpp"
#include "../includes/IrcReplies.hpp"

bool	is_topic_valid(ChannelManager &_channel_manager, Client &client, std::string const & channel_name)
{
	if (_channel_manager.channel_exists(channel_name) == false)
	{
		client.write(ERR_NOSUCHCHANNEL(SERVER_NAME, channel_name));
		return false;
	}

	if (_channel_manager.is_user_in_channel(client.get_fd(), channel_name) == false)
	{
		client.write(ERR_NOTONCHANNEL(SERVER_NAME, channel_name));
		return false;
	}

	if (_channel_manager.get_channel(channel_name).is_topic_restricted_to_operators == true)
	{
		if (_channel_manager.is_operator(client.get_fd(), channel_name) == false)
		{
			client.write(ERR_CHANOPRIVSNEEDED(SERVER_NAME, channel_name));
			return false;
		}
	}

	return true;
}
