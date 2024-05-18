#include "IrcReplies.hpp"
#include "ChannelManager.hpp"
#include "ClientManager.hpp"
#include "CommandHandler.hpp"
#include "Server.hpp"
#include "User.hpp"
#include "UserManager.hpp"
#include <iostream>
#include <string>


// peut etre faire un boolean is_channel_invite_only pour pas l'update une deuxieme fois
void	update_channel_invite_only(char sign)
{
	if (sign == '+')
	{
		std::cout << "invite only mode activated" << std::endl;
	}
	else if (sign == '-')
	{
		std::cout << "invite only mode deactivated" << std::endl;
	}
	return ;
}

void	update_topic_restricted_to_operators()
{
	return ;
}

void	update_channel_key()
{
	return ;
}

void	update_user_limit()
{
	return ;
}

void	update_channel_operator()
{
	return ;
}

bool	is_valid_mode(std::string const & modestring)
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

void	update_mode(char sign, char mode)
{
	if (mode == 'i')
		update_channel_invite_only(sign);
	else if (mode == 't')
		update_topic_restricted_to_operators();
	else if (mode == 'k')
		update_channel_key();
	else if (mode == 'l')
		update_user_limit();
	else if (mode == 'o')
		update_channel_operator();

	return ;
}

void	command_mode(
	ChannelManager &_channel_manager,
	UserManager &_user_manager,
	Client &client,
	std::string const &args
	)
{
	(void)_channel_manager;
	(void)args;
	(void)_user_manager;
	(void)client;


	std::istringstream ss(args);
	
	std::string channel_name;
	std::string modestring;

	if (!(ss >> channel_name >> modestring) || channel_name.empty() || modestring.empty())
	{
		client.write(ERR_NEEDMOREPARAMS(SERVER_NAME, "mode"));
		return ;
	}

	std::cout << "channel_name: " << channel_name << std::endl;
	std::cout << "modestring: " << modestring << std::endl;


	if (_channel_manager.channel_exists(channel_name) == false)
	{
		client.write(ERR_NOSUCHCHANNEL(SERVER_NAME, channel_name));
		return ;
	}

	if (_channel_manager.is_user_in_channel(client.get_fd(), channel_name) == false)
	{
		client.write(ERR_NOTONCHANNEL(SERVER_NAME, channel_name));
		return ;
	}

	// TODO --> voir avec caro et olivier quel container pour les operators
	/*
	if (_channel_manager.is_user_operator(client.get_fd(), channel_name) == false)
	{
		client.write(ERR_CHANOPRIVSNEEDED(SERVER_NAME, channel_name));
		return ;
	}
	*/


	std::cout << modestring.length() << std::endl;

	if (is_valid_mode(modestring) == false)
	{
		client.write(ERR_UNKNOWNMODE(SERVER_NAME, modestring));
		return ;
	}

	update_mode(modestring[0], modestring[1]);

	return ;
}
