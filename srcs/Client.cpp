#include "Client.hpp"
#include <cstring>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <iostream>
#include <errno.h>
#include "Macros.hpp"

Client::Client() :
	_fd(INVALID_FD),
	_read_buffer(""),
	_write_buffer(std::queue<std::string>())
{
}

Client::~Client()
{
}

void Client::_on_command(std::string const & command)
{
	std::cout << "Command: " << command << std::endl;
	this->write("Received command: [" + command + "]\n");
}

void Client::_check_commands_in_buffer()
{
	std::string::size_type pos = _read_buffer.find(COMMAND_END);

	while (pos != std::string::npos)
	{
		std::string command = _read_buffer.substr(0, pos);
		_read_buffer.erase(0, pos + sizeof(COMMAND_END) / sizeof(char) - 1);
		_on_command(command);
		pos = _read_buffer.find(COMMAND_END);
	}
}

int Client::read()
{
	char buffer[BUFFER_SIZE];
	int recv_size = 0;

	std::cout << "Reading from fd: " << _fd << std::endl;
	recv_size = recv(_fd, buffer, BUFFER_SIZE, 0);
	if (recv_size == -1)
	{
		std::cerr << "Error: recv failed: " << strerror(errno) << std::endl;
		return recv_size;
	}
	if (recv_size > 0)
	{
		_read_buffer.append(buffer, recv_size);
		std::cout << "Read buffer: " << _read_buffer << std::endl;
		_check_commands_in_buffer();
	}
	return recv_size;
}

void Client::flush_messages()
{
	int sended_size = 0;
	int message_size = 0;

	while (!_write_buffer.empty())
	{
		message_size = _write_buffer.front().size();
		sended_size = send(_fd, _write_buffer.front().c_str(), message_size, 0);
		if (sended_size == -1)
		{
			std::cerr << "Error: send failed: " << strerror(errno) << std::endl;
			return;
		}
		if (sended_size < message_size)
		{
			_write_buffer.front().erase(0, sended_size);
			return;
		}
		else
		{
			_write_buffer.pop();
		}
	}
}


void Client::write(std::string const & message)
{
	_write_buffer.push(message);
	flush_messages();
}

void Client::init(int fd)
{
	_fd = fd;
	_read_buffer = "";
	_write_buffer = std::queue<std::string>();
}

void Client::disconnect()
{
	if (_fd == INVALID_FD)
		return;
	close(_fd);
	_fd = INVALID_FD;
}
