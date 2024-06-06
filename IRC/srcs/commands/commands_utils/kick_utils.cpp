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

	if (_channel_manager.is_user_in_channel(client.get_fd(), channel_name) == false)
	{
		client.write(ERR_USERNOTINCHANNEL(SERVER_NAME, nickname, channel_name));
		return false;
	}

	if (_channel_manager.is_operator(client.get_fd(), channel_name) == false)
	{
		client.write(ERR_CHANOPRIVSNEEDED(SERVER_NAME, channel_name));
		return false;
	}

	User to_be_kicked = _user_manager.get_user_by_name(nickname);
	if (_channel_manager.is_operator(to_be_kicked.get_fd(), channel_name) == true)
		client.write("Cannot kick channel operator\n");

	return true;
}

void	handle_kick_command(ChannelManager &_channel_manager, UserManager &_user_manager, ClientManager &_client_manager, Client &client, std::string const & channel_name,  std::string const & nickname)
{
	User kicked = _user_manager.get_user_by_name(nickname);

	if (_channel_manager.is_operator(kicked.get_fd(), channel_name) == false)
	{
		User kicker = _user_manager.get_user(client.get_fd());
		std::set<int> clients_in_channel = _channel_manager.get_channel(channel_name).clients_fd;
		for (std::set<int>::iterator it = clients_in_channel.begin(); it != clients_in_channel.end(); it++)
		{
			Client curr_client = _client_manager.get_client(*it);
			curr_client.write(RPL_KICK(kicker.get_nickname(), kicker.get_username(), channel_name, nickname, "KICK"));
		}
		_channel_manager.leave_channel(kicked.get_fd(), channel_name);
	}

	return ;
}
