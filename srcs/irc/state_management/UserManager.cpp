#include "UserManager.hpp"

UserManager::UserManager() {}

UserManager::~UserManager() {}

User &UserManager::get_user(int fd)
{
	return _users[fd];
}

void UserManager::add_user(int fd)
{
	_users[fd] = User(fd);
}

void UserManager::remove_user(int fd)
{
	_users.erase(fd);
}

bool UserManager::user_exists(std::string user_nickname)
{
	std::map<int, User>::iterator it = _users.begin();
	while (it != _users.end())
	{
		if (it->second.get_nickname() == user_nickname)
		{
			return true;
		}
	}
	return false;
}


User &UserManager::get_user_by_name(std::string user_nickname)
{
	std::map<int, User>::iterator it = _users.begin();
	while (it != _users.end())
	{
		if (it->second.get_nickname() == user_nickname)
		{
			break ;
		}
	}
	return it->second;
}