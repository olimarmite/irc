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
	
	// Methods
	void		create_channel(std::string const & channel_name, std::string const & password);
	bool		is_user_in_channel(int client_fd, std::string const & channel_name);

	void		send_message_to_channel(int client_fd, std::string const & channel_name, std::string const & message);

	void		join_channel(int client_fd, std::string const &channel);

	void		init(ClientManager &client_manager);
	void		leave_channel(int client_fd, std::string const &channel);
	void		leave_all_channels(int client_fd);
	bool		channel_exists(std::string const & channel_name);

	//debug
	void		print_all_channels();
};
