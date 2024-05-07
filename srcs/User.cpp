#include "../includes/User.hpp"

User::User() {}

User::User(int client_fd) :
_id(INVALID_NB), _fd(client_fd), _username(""), _nickname("")
{
	(void)_fd;
	(void)_id;
}

User::~User() {}

void	User::setUsername(std::string username)
{
	_username = username;
}

void	User::setNickname(std::string username)
{
	_nickname = username;
}

std::string const &	User::getUsername() const
{
	return _username;
}

std::string const &	User::getNickname() const
{
	return _nickname;
}

int	User::getFd() const
{
	return _fd;
}