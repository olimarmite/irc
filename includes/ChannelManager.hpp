#pragma once

#include "Client.hpp"
#include <map>
#include <string>
#include <vector>


struct Channel {
	std::string name;
	std::map<int, Client> clients;
};

class ChannelManager {
private:
	std::map<std::string, Channel> _channels;
	std::map<int, std::vector<std::string> > _clientChannels;

public:
	ChannelManager();
	~ChannelManager();

	void join_channel(Client &client, std::string const &channel);
	void leave_channel(Client &client, std::string const &channel);
	void leave_all_channels(Client &client);
	void send_message_to_channel(Client &client, std::string const &channel, std::string const &message);
	Channel &get_channel(std::string const &channel);
};
