#include "../includes/Macros.hpp"
#include "../includes/utils.hpp"
#include "../includes/User.hpp"
#include "../includes/UserManager.hpp"
#include "../includes/ChannelManager.hpp"
#include "../includes/Client.hpp"
#include "../includes/ClientManager.hpp"
#include "../includes/IrcReplies.hpp"

void	broadcast_to_all_users(Channel & channel, ClientManager &_client_manager, Client &client, std::string const & channel_name, User &user)
{
	std::set<int> users_in_channel = channel.clients_fd;
	std::set<int>::iterator it = users_in_channel.begin();

	for (it = users_in_channel.begin(); it != users_in_channel.end(); it++)
	{
		Client dest_client = _client_manager.get_client(*it);
		
		if (dest_client.get_fd() != client.get_fd())
			dest_client.write(JOINED_CHANNEL(user.get_nickname(), user.get_username(), channel_name, "JOIN"));
	}
	return ;
}

void	handle_join_command(ChannelManager & _channel_manager, User &user, Client &client, ClientManager &_client_manager, std::string const & channel_name)
{
	if (_channel_manager.channel_exists(channel_name) == false)
		_channel_manager.create_channel(channel_name, "", client.get_fd());

	if (_channel_manager.is_user_in_channel(client.get_fd(), channel_name) == false)
	{
		_channel_manager.join_channel(client.get_fd(), channel_name);
		
		Channel channel = _channel_manager.get_channel(channel_name);

		client.write(CHAN_TOPIC(channel_name, channel.topic));
		client.write(JOINED_CHANNEL(user.get_nickname(), user.get_username(), channel_name, "JOIN"));
		broadcast_to_all_users(channel, _client_manager, client, channel_name, user);
	}
	return ;
}