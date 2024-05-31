#include "../includes/Macros.hpp"
#include "../includes/utils.hpp"
#include "../includes/User.hpp"
#include "../includes/UserManager.hpp"
#include "../includes/ChannelManager.hpp"
#include "../includes/Client.hpp"
#include "../includes/ClientManager.hpp"
#include "../includes/IrcReplies.hpp"

// Checks
bool	is_valid_mode(
	ChannelManager & _channel_manager,
	Client &client,
	std::string const & channel_name,
	std::string const & modestring,
	std::string const & mode_arg
	)
{
	if (_channel_manager.channel_exists(channel_name) == false)
	{
		client.write(ERR_NOSUCHCHANNEL(SERVER_NAME, channel_name));
		return false;
	}

	if (!is_valid_mode_syntax(modestring, mode_arg))
	{
		client.write(ERR_UNKNOWNMODE(SERVER_NAME, modestring));
		return false;
	}

	if (_channel_manager.is_user_in_channel(client.get_fd(), channel_name) == false)
	{
		client.write(ERR_NOTONCHANNEL(SERVER_NAME, channel_name));
		return false;
	}

	if (_channel_manager.is_operator(client.get_fd(), channel_name) == false)
	{
		client.write(ERR_CHANOPRIVSNEEDED(SERVER_NAME, channel_name));
		return false;
	}

	return true;
}

bool	is_an_integer(std::string const & str)
{
	if(str.empty())
		return false;
	
	for(std::string::const_iterator it = str.begin(); it != str.end(); ++it)
	{
		if(!std::isdigit(*it))
			return false;
	}
	return true;
}

bool	are_mode_arg_valid(std::string const & modestring, std::string const & mode_arg)
{
	if (modestring[1] == 'o' && mode_arg.empty())
		return false;
	
	if (modestring[0] == '+')
	{
		if (modestring[1] == 'k' && mode_arg.empty())
			return false;
		if (modestring[1] == 'l' && (mode_arg.empty() || !is_an_integer(mode_arg)))
			return false;
	}
	else if (modestring[0] == '-')
	{
		if (modestring[1] == 'k' && mode_arg.empty() == false)
			return false;
		if (modestring[1] == 'l' && mode_arg.empty() == false)
			return false;
	}
	return true;
}

bool	is_valid_mode_syntax(std::string const & modestring, std::string const & mode_arg)
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

	if (are_mode_arg_valid(modestring, mode_arg) == false)
		return false;
	
	return true;
}

// Handlers
void	update_mode(ChannelManager & _channel_manager, UserManager &_user_manager, ClientManager &_client_manager, std::string const & channel_name, char sign, char mode, std::string const & mode_arg, int client_fd)
{
	if (mode == 'i')
		update_channel_invite_only(_channel_manager, channel_name, sign);
	else if (mode == 't')
		update_topic_restricted_to_operators(_channel_manager, channel_name, sign);
	else if (mode == 'k')
		update_channel_key(_channel_manager, channel_name, sign, mode_arg);
	//TODO : VERIFIER ce qui se passe qd on limite à 1 alors qu'on est deja 2 dedans
	else if (mode == 'l')
		update_user_limit(_channel_manager, channel_name, sign, mode_arg);
	else if (mode == 'o')
		update_channel_operator(_channel_manager, _user_manager, _client_manager, channel_name, sign, mode_arg, client_fd);

	return ;
}

void	update_channel_invite_only(ChannelManager & _channel_manager, std::string const & channel_name, char sign)
{
	if (sign == '+')
	{
		_channel_manager.get_channel(channel_name).is_invite_only = true;
		_channel_manager.send_message_to_channel2(channel_name, BYEL + channel_name + ": Is now invite only\n");
	}
	else if (sign == '-')
	{
		_channel_manager.get_channel(channel_name).is_invite_only = false;
		_channel_manager.send_message_to_channel2(channel_name,  BGRN + channel_name + ": Is no longer invite only\n");
	}
	return ;
}

void	update_topic_restricted_to_operators(ChannelManager & _channel_manager, std::string const & channel_name, char sign)
{
	if (sign == '+')
	{
		_channel_manager.get_channel(channel_name).is_topic_restricted_to_operators = true;
		_channel_manager.send_message_to_channel2(channel_name, BYEL + channel_name + ": Topic is now restricted to operators\n");
	}
	else if (sign == '-')
	{
		_channel_manager.get_channel(channel_name).is_topic_restricted_to_operators = false;
		_channel_manager.send_message_to_channel2(channel_name, /* BGRN +  */channel_name + ": Topic is no longer restricted to operators\n");
	}
	return ;
}

void	update_channel_key(ChannelManager & _channel_manager, std::string const & channel_name, char sign, std::string const & mode_arg)
{
	if (sign == '+')
	{
		_channel_manager.get_channel(channel_name).is_key_needed = true;
		_channel_manager.get_channel(channel_name).password = mode_arg;
		_channel_manager.send_message_to_channel2(channel_name, BYEL + channel_name + ": Key is required to join\n");
	}
	else if (sign == '-')
	{
		_channel_manager.get_channel(channel_name).is_key_needed = false;
		_channel_manager.get_channel(channel_name).password = "";
		_channel_manager.send_message_to_channel2(channel_name, /* BGRN +  */channel_name + ": Key is no longer required to join\n");
	}
	return ;
}

void	update_user_limit(ChannelManager & _channel_manager, std::string const & channel_name, char sign, std::string const & mode_arg)
{
	int	user_limit = std::atoi(mode_arg.c_str());

	if (sign == '+')
	{
		_channel_manager.get_channel(channel_name).user_limit = user_limit;
		_channel_manager.send_message_to_channel2(channel_name, BYEL + channel_name + ": User limit set to " + mode_arg + "\n");
	}
	else if (sign == '-')
	{
		_channel_manager.get_channel(channel_name).user_limit = -1;
		_channel_manager.send_message_to_channel2(channel_name, /* BGRN +  */channel_name + ": User limit removed\n");
	}
	return ;
}

void	update_channel_operator(ChannelManager & _channel_manager, UserManager &_user_manager, ClientManager &_client_manager, std::string const & channel_name, char sign, std::string const & mode_arg, int client_fd)
{
	Client cmd_client = _client_manager.get_client(client_fd);
	User cmd_user = _user_manager.get_user(client_fd);

	if (_user_manager.user_exists(mode_arg) == false)
	{
		cmd_client.write(ERR_NOSUCHNICK(SERVER_NAME, mode_arg));
		return;
	}
  
	if (_channel_manager.is_user_in_channel(_user_manager.get_user_by_name(mode_arg).get_fd(), channel_name) == false)
	{
		cmd_client.write(ERR_USERNOTINCHANNEL(cmd_user.get_nickname(), mode_arg, channel_name));
		return ;
	}
	
	User user = _user_manager.get_user_by_name(mode_arg);
	if (sign == '+')
	{
		_channel_manager.get_channel(channel_name).operators.insert(user.get_fd());
		_channel_manager.send_message_to_channel2(channel_name, /* BGRN +  */channel_name + ": " + user.get_nickname() + " is now a channel operator\n");
	}
	else if (sign == '-')
	{
		_channel_manager.get_channel(channel_name).operators.erase(user.get_fd());
		_channel_manager.send_message_to_channel2(channel_name, BYEL + channel_name + ": " + user.get_nickname() + " is no longer a channel operator\n");
	}

	cmd_client.write(RPL_MODEUPDATECHANOP(cmd_user.get_nickname(), cmd_user.get_username(), channel_name, sign, user.get_nickname()));
	return ;
}
