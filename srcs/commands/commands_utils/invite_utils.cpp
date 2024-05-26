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
	if (_channel_manager.channel_exists(channel_name) == false)
	{
		client.write(ERR_NOSUCHCHANNEL(SERVER_NAME, channel_name));
		return false;
	}

	if (_user_manager.user_exists(nickname) == false)
	{
		client.write(ERR_NOSUCHNICK(SERVER_NAME, nickname));
		return false;
	}

	if (_channel_manager.is_operator(client.get_fd(), channel_name) == false)
	{
		client.write(ERR_CHANOPRIVSNEEDED(SERVER_NAME, channel_name));
		return false;
	}

	if (_channel_manager.is_user_in_channel(client.get_fd(), channel_name) == false)
	{
		client.write(ERR_NOTONCHANNEL(SERVER_NAME, channel_name));
		return false;
	}

	User &user = _user_manager.get_user(client.get_fd());
	if (_channel_manager.is_user_in_channel(_user_manager.get_user_by_name(nickname).get_fd(), channel_name) == true)
	{
		client.write(ERR_USERONCHANNEL(SERVER_NAME, user.get_nickname(), nickname, channel_name));
		return false;
	}

	if (_channel_manager.get_channel(channel_name).user_limit > 0)
	{
		if (_channel_manager.get_channel(channel_name).clients_fd.size() >= _channel_manager.get_channel(channel_name).user_limit)
		{
			client.write(ERR_CHANNELISFULL(SERVER_NAME, channel_name));
			return false;
		}
	}

	return true;
}

void send_invitation_messages(ClientManager & _client_manager, Client &client, User &user, User &user_to_invite, const std::string &channel_name)
{
	client.write(RPL_INVITING(SERVER_NAME, channel_name, user.get_nickname(), user_to_invite.get_nickname()));
	Client &client_to_invite = _client_manager.get_client(user_to_invite.get_fd());
	client_to_invite.write(RPL_INVITED(user.get_nickname(), user.get_username(), user_to_invite.get_nickname(), channel_name, "INVITE"));
	client_to_invite.write(JOINED_CHANNEL(user_to_invite.get_nickname(), user_to_invite.get_username(), channel_name, "JOIN"));
}

void handle_invite_command(ChannelManager & _channel_manager, UserManager & _user_manager, ClientManager & _client_manager, Client &client, std::string const & channel_name, std::string const & nickname)
{
	User &user_to_invite = _user_manager.get_user_by_name(nickname);
	Channel &channel = _channel_manager.get_channel(channel_name);
	User &user = _user_manager.get_user(client.get_fd());

	channel.clients_fd.insert(user_to_invite.get_fd());

	send_invitation_messages(_client_manager, client, user, user_to_invite, channel_name);

	broadcast_to_all_users(channel, _client_manager, client, channel_name, user_to_invite);

	return ;
}