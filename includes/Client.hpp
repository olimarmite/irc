#pragma once
#include <queue>
#include <string>

#define BUFFER_SIZE 1024

class	Server;

class Client
{
  private:
	int _fd;
	std::string _read_buffer;
	std::queue<std::string> _write_buffer;
	Server *_server;

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
	void init(int fd, Server &server);
	int getFd() const;
	bool getIsAuthanticated() const;
	void setIsAuthanticated(bool isAuthanticated);

	Client &operator=(Client const &rhs);
};
