#pragma once

#include "Macros.hpp"

class User
{
	private:
		int				_id;
		int				_fd;
		std::string		_username;
		std::string		_nickname;

	public:
		User();
		User(int client_fd);
		~User();

		void				setUsername(std::string username);
		void				setNickname(std::string username);
		std::string const &	getUsername() const;
		std::string const &	getNickname() const;
		int					getFd() const;
};