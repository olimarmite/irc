#include "../includes/Macros.hpp"
#include "../includes/utils.hpp"
#include "../includes/User.hpp"
#include "../includes/UserManager.hpp"
#include "../includes/Client.hpp"
#include "../includes/ClientManager.hpp"
#include "../includes/IrcReplies.hpp"

bool	does_nickname_have_channel_prefix(std::string const & nickname)
{
	if (
		nickname[0] == '#' ||
		nickname[0] == '&' ||
		nickname[0] == '~' ||
		nickname[0] == '@' ||
		nickname[0] == '%' ||
		nickname[0] == ':'
		)
			return true;

	if (nickname[0] == '+' && nickname[1])
	{
		if (
			nickname[1] == 'q' ||
			nickname[1] == 'a' ||
			nickname[1] == 'o' ||
			nickname[1] == 'h' ||
			nickname[1] == 'v'
			)
			return true;
	}

	return false;
}

bool	does_nickname_already_exist(std::string const & nickname, UserManager & _user_manager)
{
	if (_user_manager.user_exists(nickname) == true)
		return true;
	return false;
}

bool	is_nickname_valid(std::string const & nickname, UserManager & _user_manager, User & user, Client &client)
{
	(void)user;
	
	if (nickname.empty())
	{
		client.write(ERR_NONICKNAMEGIVEN(SERVER_NAME));
		return false;
	}

	std::string	invalid = " ,*?!@.$:";
	if (does_nickname_have_channel_prefix(nickname) == true || nickname.find_first_of(invalid) != std::string::npos)
	{
		client.write(ERR_ERRONEUSNICKNAME(SERVER_NAME, nickname));
		return false;
	}

	if (does_nickname_already_exist(nickname, _user_manager) == true)
	{
		client.write(ERR_NICKNAMEINUSE(SERVER_NAME, nickname));
		return false;
	}

	return true;
}