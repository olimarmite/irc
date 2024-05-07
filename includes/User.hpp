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

		void				setUsername(std::string username);
		void				setNickname(std::string username);
		void				setIsAuthenticated(int is_authenticated);
		int					getIsAuthenticated() const;
		std::string const &	getUsername() const;
		std::string const &	getNickname() const;
		int					getFd() const;
};
