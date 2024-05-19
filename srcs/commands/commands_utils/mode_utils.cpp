#include "../includes/Macros.hpp"
#include "../includes/utils.hpp"
#include "../includes/User.hpp"
#include "../includes/UserManager.hpp"
#include "../includes/ChannelManager.hpp"
#include "../includes/Client.hpp"
#include "../includes/ClientManager.hpp"
#include "../includes/IrcReplies.hpp"


// TODO --> voir avec caro les creations de channel

// Checks
bool	is_valid_mode(ChannelManager & _channel_manager, Client &client, std::string const & channel_name, std::string const & modestring)
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

	// TODO --> voir avec caro et olivier quel container pour les operators
	/*
	if (_channel_manager.is_user_operator(client.get_fd(), channel_name) == false)
	{
		client.write(ERR_CHANOPRIVSNEEDED(SERVER_NAME, channel_name));
		return ;
	}
	*/

	if (!is_valid_mode_syntax(modestring))
	{
		client.write(ERR_UNKNOWNMODE(SERVER_NAME, modestring));
		return false;
	}

	return true;
}

bool	is_valid_mode_syntax(std::string const & modestring)
{
	if (modestring.length() != 2)
		return false;

	if (modestring[0] != '+' && modestring[0] != '-')
		return false;
	
	if (
		modestring[1] != 'i' &&
		modestring[1] != 't' &&
		modestring[1] != 'k' &&
		modestring[1] != 'l' &&
		modestring[1] != 'o'
		)
		return false;
	return true;
}

// Handlers
void	update_mode(ChannelManager & _channel_manager, std::string const & channel_name, char sign, char mode)
{
	//TO DO peut etre plus de parsing a faire selon les modes
	
	if (mode == 'i')
		update_channel_invite_only(_channel_manager, channel_name, sign);
	else if (mode == 't')
		update_topic_restricted_to_operators(_channel_manager, channel_name, sign);
	else if (mode == 'k')
		update_channel_key(_channel_manager, channel_name, sign);
	else if (mode == 'l')
		update_user_limit(_channel_manager, channel_name, sign);
	else if (mode == 'o')
		update_channel_operator(_channel_manager, channel_name, sign);

	return ;
}

// TODO
// // peut etre faire un boolean is_channel_invite_only pour pas l'update une deuxieme fois
void	update_channel_invite_only(ChannelManager & _channel_manager, std::string const & channel_name, char sign)
{
	if (sign == '+')
	{
		_channel_manager.get_channel(channel_name).is_invite_only = true;
		std::cout << BGRN "invite only mode activated" << std::endl;
	}
	else if (sign == '-')
	{
		_channel_manager.get_channel(channel_name).is_invite_only = false;
		std::cout << BYEL "invite only mode deactivated" << std::endl;
	}
	return ;
}

void	update_topic_restricted_to_operators(ChannelManager & _channel_manager, std::string const & channel_name, char sign)
{
	if (sign == '+')
	{
		_channel_manager.get_channel(channel_name).is_topic_restricted_to_operators = true;
		std::cout << BGRN "topic restricted to operators mode activated" << std::endl;
	}
	else if (sign == '-')
	{
		_channel_manager.get_channel(channel_name).is_topic_restricted_to_operators = false;
		std::cout << BYEL "topic restricted to operators mode deactivated" << std::endl;
	}
	return ;
}

void	update_channel_key(ChannelManager & _channel_manager, std::string const & channel_name, char sign)
{
	if (sign == '+')
	{
		_channel_manager.get_channel(channel_name).is_key_needed = true;
		std::cout << BGRN "key needed mode activated" << std::endl;
	}
	else if (sign == '-')
	{
		_channel_manager.get_channel(channel_name).is_key_needed = false;
		std::cout << BYEL "key needed mode deactivated" << std::endl;
	}
	return ;
}

void	update_user_limit(ChannelManager & _channel_manager, std::string const & channel_name, char sign)
{
	if (sign == '+')
		_channel_manager.get_channel(channel_name).user_limit = 0;
	else if (sign == '-')
		_channel_manager.get_channel(channel_name).user_limit = 2000;
	return ;
}

void	update_channel_operator(ChannelManager & _channel_manager, std::string const & channel_name, char sign)
{
	(void)_channel_manager;
	(void)channel_name;

	if (sign == '+')
	{
		//_user_manager.get_user(user_fd).is_operator = true;
	}
	else if (sign == '-')
	{
		// TODO
	}
	return ;
}
