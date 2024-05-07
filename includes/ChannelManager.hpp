#pragma once

#include "Client.hpp"
#include "ClientManager.hpp"
#include <map>
#include <set>
#include <string>
#include <vector>


struct Channel {
	std::string name;
	std::set<int> clients_fd;
};

class ChannelManager {
private:
	std::map<std::string, Channel> _channels;
	std::map<int, std::set<std::string> > _clientChannels;
	ClientManager *_client_manager;

public:
	ChannelManager();
	~ChannelManager();

	void init(ClientManager &client_manager);
	void join_channel(int client_fd, std::string const &channel);
	void leave_channel(int client_fd, std::string const &channel);
	void leave_all_channels(int client_fd);
	void send_message_to_channel(std::string const &channel, std::string const &message);
	Channel &get_channel(std::string const &channel);
};
