#pragma once

#include <map>
#include "User.hpp"

class UserManager
{
	private:
		std::map<int, User> _users;
	public:
		UserManager();
		~UserManager();
		User &get_user(int fd);
		void add_user(int fd);
		void remove_user(int fd);
		std::map<int, User> &getUsers();
};
