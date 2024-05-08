#include "User.hpp"
#include "Macros.hpp"

User::User() :
	_fd(INVALID_FD), _username(""), _nickname(""), _is_authenticated(false), _is_operator(false)
{}

User::User(int client_fd) :
	_fd(client_fd), _username(""), _nickname(""), _is_authenticated(false), _is_operator(false)
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

int	User::get_is_authenticated() const
{
	return _is_authenticated;
}

void	User::set_is_authenticated(int is_authenticated)
{
	_is_authenticated = is_authenticated;
}

int	User::get_is_operator() const
{
	return _is_operator;
}

void	User::set_is_operator(int is_operator)
{
	_is_operator = is_operator;
}