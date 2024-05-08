#include "Client.hpp"
#include "Server.hpp"
#include <cstddef>
#include <cstring>
#include <ostream>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <iostream>
#include <errno.h>
#include "Macros.hpp"
#include "CommandHandler.hpp"

Client::Client() :
	_fd(INVALID_FD),
	_read_buffer(""),
	_write_buffer(std::queue<std::string>()),
	_command_handler(NULL)
{
}

Client::~Client()
{
}

void Client::_on_command(std::string const & command)
{
	_command_handler->handle_command(*this, command);
}

void Client::_check_commands_in_buffer()
{
	if (DEBUG)
		std::cout << BGRN << _read_buffer << PRINT_END;
	
	size_t pos = _read_buffer.find(COMMAND_END);

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

	if (DEBUG)
		std::cout << "Reading from fd: " << _fd << std::endl;
	recv_size = recv(_fd, buffer, BUFFER_SIZE, 0);
	if (recv_size == -1)
	{
		if (DEBUG)
			std::cerr << "Error: recv failed: " << strerror(errno) << std::endl;
		return recv_size;
	}
	if (recv_size > 0)
	{
		_read_buffer.append(buffer, recv_size);
		if (DEBUG)
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
			if (DEBUG)
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

void Client::init(int fd, CommandHandler &command_handler)
{
	_fd = fd;
	_read_buffer = "";
	_write_buffer = std::queue<std::string>();
	_command_handler = &command_handler;
	_command_handler->on_connection(*this);
}

void Client::disconnect()
{
	if (_fd == INVALID_FD)
		return;
	_command_handler->on_disconnection(*this);
	close(_fd);
	_fd = INVALID_FD;
}

int Client::get_fd() const
{
	return _fd;
}

Client & Client::operator=(Client const & other)
{
	if (this != &other)
	{
		_fd = other._fd;
		_read_buffer = other._read_buffer;
		_write_buffer = other._write_buffer;
		_command_handler = other._command_handler;
	}
	return *this;
}
