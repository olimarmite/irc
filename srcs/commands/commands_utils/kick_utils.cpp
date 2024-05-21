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

	return true;
}

void	handle_kick_command(ChannelManager &_channel_manager, UserManager &_user_manager, Client &client, std::string const & channel_name,  std::string const & nickname)
{
	User kicked_user = _user_manager.get_user_by_name(nickname);

	//---
	if (DEBUG)
	{
		std::cout <<"----------------" <<std::endl;
		std::cout <<BRED <<"List of operators in channel " <<channel_name <<PRINT_END;
		_channel_manager.print_operators(channel_name, _user_manager);
		std::cout <<"----------------" <<std::endl;
	}
	//---

	if (_channel_manager.is_operator(kicked_user.get_fd(), channel_name) == false)
	{
		std::cout << "I am here" << std::endl;
		_channel_manager.leave_channel(kicked_user.get_fd(), channel_name);

		//---
		if (DEBUG)
		{
			std::cout <<BBLU <<"User to be kicked is not the channel operator" <<PRINT_END;
			std::cout <<BBLU <<"User has been kicked" <<PRINT_END;
			std::cout <<BBLU <<"List of clients in channel " <<channel_name <<PRINT_END;
			_channel_manager.print_all_clients(channel_name);
		}
		//---

		User user = _user_manager.get_user(client.get_fd());
		client.write(RPL_KICK(user.get_nickname(), user.get_username(), channel_name, nickname, "KICK"));
		
	}
	//---
	else
	{
		std::cout <<BRED <<"User to be kicked is the channel operator" <<PRINT_END;
		client.write("KICK " + channel_name + " " + nickname + " :Cannot kick channel operator");
	}
	//---

	return ;
}
