#pragma once

#include "Client.hpp"
#include "ClientManager.hpp"
#include <map>
#include <set>
#include <string>
#include <vector>


struct Channel
{
	std::string		name;
	std::string		password;
	std::set<int>	clients_fd;
	std::string		topic;

	// -> pour mode
	bool			is_invite_only;
	bool			is_topic_restricted_to_operators;
	bool			is_key_needed;
	unsigned int	user_limit;

	std::set<int>	operators;
};

class ChannelManager
{
private:
	std::map<std::string, Channel>			_channels;
	std::map<int, std::set<std::string> >	_clientChannels;
	ClientManager*							_client_manager;

public:
	// Const & Dest
	ChannelManager();
	~ChannelManager();

	// Get & Set
	Channel&	get_channel(std::string const &channel);
	void		set_channel_name(std::string const & channel_name);
	void		set_channel_topic(std::string const & channel_name, std::string const & channel_topic);
	std::set<int>	get_operators(std::string const & channel_name);

	// Methods
	void		create_channel(std::string const & channel_name, std::string const & password, int const & client_fd);
	bool		is_user_in_channel(int client_fd, std::string const & channel_name);
	void		send_message_to_channel(int client_fd, std::string const & channel_name, std::string const & message, UserManager &_user_manager);
	void		join_channel(int client_fd, std::string const &channel);
	void		init(ClientManager &client_manager);
	void		leave_channel(int client_fd, std::string const &channel);
	void		leave_all_channels(int client_fd);
	bool		channel_exists(std::string const & channel_name);
	bool		is_operator(int client_fd, std::string channel_name);

  ClientManager &get_client_manager();

	//debug
	void		print_all_channels();
	void		print_all_clients(std::string channel_name);
	void		print_operators(std::string channel_name, UserManager user_manager);

};
