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

