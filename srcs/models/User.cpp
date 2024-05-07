#include "User.hpp"
#include "Macros.hpp"

User::User() :
	_fd(INVALID_FD), _username(""), _nickname(""), _is_authenticated(false)
{}

User::User(int client_fd) :
	_fd(client_fd), _username(""), _nickname(""), _is_authenticated(false)
{
	(void)_fd;
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

int	User::getIsAuthenticated() const
{
	return _is_authenticated;
}

void	User::setIsAuthenticated(int is_authenticated)
{
	_is_authenticated = is_authenticated;
}
