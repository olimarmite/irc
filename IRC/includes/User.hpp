#pragma once

#include "Macros.hpp"
#include <string>

class User
{
	private:
		int				_fd;
		std::string		_username;
		std::string		_nickname;
		std::string		_used_password;
		int 			_is_registered;

	public:
		// Const & Dest
		User();
		User(int client_fd);
		~User();

		// Get & Set
		void				set_username(std::string username);
		void				set_nickname(std::string username);
		void				set_used_password(std::string password);
		std::string const &	get_used_password() const;
		void				set_is_registered(int is_registered);
		int					get_is_registered() const;
		std::string const &	get_username() const;
		std::string const &	get_nickname() const;
		int					get_fd() const;
};
