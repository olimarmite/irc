#include "../includes/Macros.hpp"
#include "../includes/utils.hpp"
#include "../includes/User.hpp"
#include "../includes/UserManager.hpp"
#include "../includes/ChannelManager.hpp"
#include "../includes/Client.hpp"
#include "../includes/ClientManager.hpp"
#include "../includes/IrcReplies.hpp"

bool	is_valid_invite(std::string const & channel_name, std::string const & nickname, UserManager & _user_manager, ChannelManager & _channel_manager, Client &client)
{
	if (_user_manager.user_exists(nickname) == false)
	{
		client.write(ERR_NOSUCHNICK(SERVER_NAME, nickname));
		return false;
	}

	if (_channel_manager.channel_exists(channel_name) == false)
	{
		client.write(ERR_NOSUCHCHANNEL(SERVER_NAME, channel_name));
		return false;
	}

	if (_channel_manager.get_channel(channel_name).is_invite_only == true)
	{
		client.write(ERR_INVITEONLYCHAN(SERVER_NAME, channel_name));
		return false;
	}

	if (_channel_manager.is_user_in_channel(client.get_fd(), channel_name) == false)
	{
		client.write(ERR_NOTONCHANNEL(SERVER_NAME, channel_name));
		return false;
	}

	if (_channel_manager.is_user_in_channel(_user_manager.get_user_by_name(nickname).get_fd(), channel_name) == true)
	{
		client.write(ERR_USERONCHANNEL(SERVER_NAME, nickname, channel_name));
		return false;
	}

	return true;
}