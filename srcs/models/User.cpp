#include "User.hpp"
#include "Macros.hpp"
#include <string>

User::User() :
	_fd(INVALID_FD), _username(""), _nickname(""), _is_registered(false)
{}

User::User(int client_fd) :
	_fd(client_fd), _username(""), _nickname(""), _is_registered(false)
{
	(void)_fd;
}

User::~User() {}

void	User::set_username(std::string username)
{
	_username = username;
}

void	User::set_nickname(std::string username)
{
	_nickname = username;
}

std::string const &	User::get_username() const
{
	return _username;
}

std::string const &	User::get_nickname() const
{
	return _nickname;
}

int	User::get_fd() const
{
	return _fd;
}

int	User::get_is_registered() const
{
	return _is_registered;
}

void	User::set_is_registered(int is_registered)
{
	_is_registered = is_registered;
}

void	User::set_used_password(std::string password)
{
	_used_password = password;
}

std::string	const &User::get_used_password() const
{
	return _used_password;
}