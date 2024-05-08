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
		bool user_exists(std::string user_nickname);
		User &get_user_by_name(std::string user_nickname);
		void	print_all_users();
};
