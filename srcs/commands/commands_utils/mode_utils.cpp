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
	
	if (!is_valid_mode_syntax(modestring, mode_arg))
	{
		client.write(ERR_UNKNOWNMODE(SERVER_NAME, modestring));
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
	if (modestring[1] == 'k' && mode_arg.empty())
		return false;
	if (modestring[1] == 'l' && (mode_arg.empty() || !is_an_integer(mode_arg)))
		return false;
	if (modestring[1] == 'o' && mode_arg.empty())
		return false;
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
	//TO DO peut etre plus de parsing a faire selon les modes

	if (mode == 'i')
		update_channel_invite_only(_channel_manager, channel_name, sign);
	else if (mode == 't')
		update_topic_restricted_to_operators(_channel_manager, channel_name, sign);
	else if (mode == 'k')
		update_channel_key(_channel_manager, channel_name, sign, mode_arg);
	else if (mode == 'l')
		update_user_limit(_channel_manager, channel_name, sign, mode_arg);
	else if (mode == 'o') // mettre nickname apres mode
		update_channel_operator(_channel_manager, _user_manager, _client_manager, channel_name, sign, mode_arg, client_fd);

	return ;
}

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

void	update_channel_key(ChannelManager & _channel_manager, std::string const & channel_name, char sign, std::string const & mode_arg)
{
	if (sign == '+')
	{
		_channel_manager.get_channel(channel_name).is_key_needed = true;
		_channel_manager.get_channel(channel_name).password = mode_arg;
		std::cout << BGRN "key needed mode activated" << std::endl;
	}
	else if (sign == '-')
	{
		_channel_manager.get_channel(channel_name).is_key_needed = false;
		_channel_manager.get_channel(channel_name).password = "";
		std::cout << BYEL "key needed mode deactivated" << std::endl;
	}
	return ;
}

void	update_user_limit(ChannelManager & _channel_manager, std::string const & channel_name, char sign, std::string const & mode_arg)
{
	int user_limit = 0;
	std::istringstream iss(mode_arg);
	if (!iss >> user_limit)
		return ;
	
	if (sign == '+')
		_channel_manager.get_channel(channel_name).user_limit = user_limit;
	else if (sign == '-')
		_channel_manager.get_channel(channel_name).user_limit = -1;
	return ;
}

void	update_channel_operator(ChannelManager & _channel_manager, UserManager &_user_manager, ClientManager &_client_manager, std::string const & channel_name, char sign, std::string const & mode_arg, int client_fd)
{
	Client cmd_client = _client_manager.get_client(client_fd);
	User cmd_user = _user_manager.get_user(client_fd);

	if (_user_manager.user_exists(mode_arg) == false)
	{
		std::cout <<"User to change mode for does not exist" <<std::endl; //client.write() ?
		return;
	}
	User user = _user_manager.get_user_by_name(mode_arg);
	if (_channel_manager.is_user_in_channel(user.get_fd(), channel_name) == false)
	{
		std::cout <<"User to change mode for was not found in channel" <<std::endl; //client.write() ?
		return ;
	}
	
	if (sign == '+')
		_channel_manager.get_channel(channel_name).operators.insert(user.get_fd());
	else if (sign == '-')
		_channel_manager.get_channel(channel_name).operators.erase(user.get_fd());
	// else
		//sign error

	cmd_client.write(RPL_MODEUPDATECHANOP(cmd_user.get_nickname(), cmd_user.get_username(), channel_name, sign, user.get_nickname()));

	return ;
}
