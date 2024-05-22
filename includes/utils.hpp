#pragma once
#include "Macros.hpp"
#include "User.hpp"
#include "UserManager.hpp"
#include "Client.hpp"
#include "ClientManager.hpp"
#include "ChannelManager.hpp"

// Main
bool	is_arg_valid(int argc, char **argv);
bool	is_valid_port(std::string const & port);
bool	is_valid_password(std::string const & password);

// Nickname
bool	does_nickname_have_channel_prefix(std::string const & nickname);
bool	does_nickname_already_exist(std::string const & nickname);
bool	is_nickname_valid(std::string const & nickname, UserManager & _user_manager, User & user, Client &client, bool *nick_conflict);

// Channel
bool	is_check_all_channel_valid(std::string const & channel_name, Client &client, ChannelManager & _channel_manager, std::string const & password_arg);
bool	is_valid_channel_prefix(char c);
bool	is_channel_name_valid(std::string const & channel);
bool	is_channel_key_protected(Channel & channel, Client &client, std::string const & channel_name, std::string const & password, std::string const & password_arg);
bool	is_channel_invite_only(Channel & channel, Client &client, std::string const & channel_name);
bool	is_user_limit_reached(Channel & channel, Client &client);

// Invite
bool	is_valid_invite(std::string const & channel_name, std::string const & nickname, UserManager & _user_manager, ChannelManager & _channel_manager, Client &client);

// Mode
bool	is_valid_mode(ChannelManager & _channel_manager, Client &client, std::string const & channel_name, std::string const & modestring, std::string const & mode_arg);
bool	is_valid_mode_syntax(std::string const & modestring, std::string const & mode_arg);
bool	are_mode_arg_valid(std::string const & modestring, std::string const & mode_arg);
bool	is_an_integer(std::string const & str);

void	update_mode(ChannelManager & _channel_manager, UserManager &_user_manager, ClientManager &_client_manager, std::string const & channel_name, char sign, char mode, std::string const & mode_arg, int client_fd);
void	update_channel_invite_only(ChannelManager & _channel_manager, std::string const & channel_name, char sign);
void	update_topic_restricted_to_operators(ChannelManager & _channel_manager, std::string const & channel_name, char sign);
void	update_channel_key(ChannelManager & _channel_manager, std::string const & channel_name, char sign, std::string const & mode_arg);
void	update_user_limit(ChannelManager & _channel_manager, std::string const & channel_name, char sign, std::string const & mode_arg);
void	update_channel_operator(ChannelManager & _channel_manager, UserManager &_user_manager, ClientManager &_client_manager, std::string const & channel_name, char sign, std::string const & mode_arg, int client_fd);

// Join
void	broadcast_to_all_users(Channel & channel, ClientManager &_client_manager, Client &client, std::string const & channel_name, User &user);
void	handle_join_command(ChannelManager & _channel_manager, User &user, Client &client, ClientManager & _client_manager, std::string const & channel_name);

// Kick
bool	is_kick_valid(ChannelManager & _channel_manager, UserManager &_user_manager, Client &client, std::string const & channel_name, std::string const & nickname);
void	handle_kick_command(ChannelManager &_channel_manager, UserManager &_user_manager, ClientManager &_client_manager, Client &client, std::string const & channel_name,  std::string const & nickname);

// Topic
bool	is_topic_valid(ChannelManager & _channel_manager, Client &client, std::string const & channel_name);