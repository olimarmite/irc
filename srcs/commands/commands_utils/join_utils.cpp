#include "../includes/Macros.hpp"
#include "../includes/utils.hpp"
#include "../includes/User.hpp"
#include "../includes/UserManager.hpp"
#include "../includes/ChannelManager.hpp"
#include "../includes/Client.hpp"
#include "../includes/ClientManager.hpp"
#include "../includes/IrcReplies.hpp"

void	handle_join_command(ChannelManager & _channel_manager, User &user, Client &client, std::string const & channel_name, std::string const & password)
{
	if (_channel_manager.channel_exists(channel_name) == false)
		_channel_manager.create_channel(channel_name, password, client.get_fd());

	if (DEBUG)
		_channel_manager.print_all_channels();

	if (_channel_manager.is_user_in_channel(client.get_fd(), channel_name) == false)
	{
		_channel_manager.join_channel(client.get_fd(), channel_name); //CA ENTRE ICI SANS PASSER PAR CHANNEL DOES NOT EXIST
		
		Channel channel = _channel_manager.get_channel(channel_name);

		std::cout << RPL_TOPIC(user.get_nickname(), user.get_username(), channel_name, channel.topic, "TOPIC") << std::endl;
		std::cout << JOINED_CHANNEL(user.get_nickname(), user.get_username(), channel_name, "JOIN") << std::endl;

		client.write(RPL_TOPIC(user.get_nickname(), user.get_username(), channel_name, channel.topic, "TOPIC"));
		client.write(JOINED_CHANNEL(user.get_nickname(), user.get_username(), channel_name, "JOIN"));
	}
	return ;
}