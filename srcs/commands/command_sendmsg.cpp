#include "Client.hpp"
#include "ChannelManager.hpp"
#include "IrcReplies.hpp"
#include "UserManager.hpp"
#include "utils.hpp"
#include <string>

void	command_sendmsg(
	ChannelManager &_channel_manager,
	UserManager &_user_manager,
	ClientManager &_client_manager,
	const ServerSettings &_server_settings,
	Client &client,
	std::string const &args
	)
{
	(void)_server_settings;
	
	User origin_user = _user_manager.get_user(client.get_fd());
	std::string message = parse_message(args);
	if (DEBUG)
		std::cout <<BRED <<"MESSAGE = " + message <<PRINT_END;
	
	if (args[0] != '#') //if private message
	{
		if (DEBUG)
		{
			std::cout <<"List of users" <<std::endl;
			_user_manager.print_all_users();
		}

		std::string nickname = parse_nickname(args);
		if (_user_manager.user_exists(nickname) == true)
		{
			User dest_user = _user_manager.get_user_by_name(nickname);
			Client dest_client = _client_manager.get_client(dest_user.get_fd());

			dest_client.write(MSG_RECEIVED(origin_user.get_nickname(), dest_user.get_username(), \
			dest_user.get_nickname(), message, "PRIVMSG"));
		}
		else
		{
			User origin_user = _user_manager.get_user(client.get_fd());
			client.write(ERR_NOSUCHNICK(SERVER_NAME, nickname));
			return ;
		}
	}
	else //message for channel
	{
		if (DEBUG)
			_channel_manager.print_all_channels();

		std::string	channel_name = parse_channel_name(args);
		if (_channel_manager.channel_exists(channel_name) == false)
		{
			User origin_user = _user_manager.get_user(client.get_fd());
			client.write(ERR_NOSUCHNICK(SERVER_NAME, channel_name));
			return ;
		}
		else
		{
			if (_channel_manager.is_user_in_channel(client.get_fd(), channel_name) == false)
				return ;

			_channel_manager.send_message_to_channel(client.get_fd(), channel_name, message, _user_manager);
		}
	}
}
