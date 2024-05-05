#pragma once
#include <queue>
#include <string>

#define BUFFER_SIZE 1024

class Client
{
private:
	int _fd;
	std::string _read_buffer;
	std::queue<std::string> _write_buffer;
	void _check_commands_in_buffer();
	void _on_command(std::string const & command);

public:
	Client(int fd);
	Client();
	~Client();

	int read();
	void write(std::string const & message);
	void flush_messages();
	void disconnect();
	void init(int fd);
};
