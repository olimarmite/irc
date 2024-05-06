#pragma once

#include <queue>
#include <string>
#include "CommandHandler.hpp"

#define BUFFER_SIZE 1024

class	Server;

class Client
{
  private:
	int _fd;
	std::string _read_buffer;
	std::queue<std::string> _write_buffer;
	CommandHandler *_command_handler;

	bool is_authanticated; //TODO move this in User class

	void _check_commands_in_buffer();
	void _on_command(std::string const &command);

  public:
	Client();
	~Client();

	int read();
	void write(std::string const &message);
	void flush_messages();
	void disconnect();
	void init(int fd, CommandHandler &command_handler);
	int get_fd() const;
	bool get_is_authanticated() const;
	void set_is_authanticated(bool isAuthanticated);

	Client &operator=(Client const &rhs);
};
