#pragma once

#include "Macros.hpp"

class User
{
	private:
		int				_fd;
		std::string		_username;
		std::string		_nickname;
		int 			_is_authenticated;

	public:
		User();
		User(int client_fd);
		~User();

		void				set_username(std::string username);
		void				set_nickname(std::string username);
		void				set_is_authenticated(int is_authenticated);
		int					get_is_authenticated() const;
		std::string const &	get_username() const;
		std::string const &	get_nickname() const;
		int					get_fd() const;
};
