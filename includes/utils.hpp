#pragma once

#include "Macros.hpp"
#include "User.hpp"
#include "UserManager.hpp"

bool	is_valid_port(std::string const & port);
bool	is_valid_password(std::string const & password);
bool	is_arg_valid(int argc, char **argv);
bool	does_nickname_have_channel_prefix(std::string const & nickname);
bool	is_nickname_valid(std::string const & nickname, UserManager & _user_manager, User & user);
bool	is_channel_valid(std::string const & channel);
bool	does_nickname_already_exist(std::string const & nickname);