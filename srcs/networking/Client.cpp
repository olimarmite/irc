#include "Client.hpp"
#include "Server.hpp"
#include "IrcReplies.hpp"
#include <cstddef>
#include <cstring>
#include <ostream>
#include <stdexcept>
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
	_command_handler(NULL),
	_connection_status(DISCONNECTED)
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
	size_t pos = _read_buffer.find(NEW_LINE);

	while (_connection_status == CONNECTED && pos != std::string::npos)
	{
		std::string command = _read_buffer.substr(0, pos);
		_read_buffer.erase(0, pos + NEW_LINE.length());
		std::cout << "< " << command << std::endl;
		_on_command(command);
		pos = _read_buffer.find(NEW_LINE);
	}
}

int Client::read()
{
	char buffer[BUFFER_SIZE];
	int recv_size = 0;

	recv_size = recv(_fd, buffer, BUFFER_SIZE, 0);
	if (recv_size == -1)
	{
		return recv_size;
	}
	if (recv_size > 0)
	{
		_read_buffer.append(buffer, recv_size);
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
		sended_size = send(_fd, _write_buffer.front().c_str(), message_size, MSG_DONTWAIT | MSG_NOSIGNAL);
		if (sended_size == -1)
		{
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
	std::cout << "> " << message << std::endl;
	_write_buffer.push(message);
	flush_messages();
}

void Client::init(int fd, CommandHandler &command_handler)
{
	std::cout << "NEW CLIENT fd:" << fd << std::endl;
	_fd = fd;
	_read_buffer = "";
	_write_buffer = std::queue<std::string>();
	_command_handler = &command_handler;
	_command_handler->on_connection(*this);
	_connection_status = CONNECTED;
}

void Client::disconnect()
{
	std::cout << "disconnect Client fd:" << _fd << std::endl;
	if (_fd == INVALID_FD)
		return;
	_command_handler->on_disconnection(*this);
	close(_fd);
	_connection_status = DISCONNECTED;
	_fd = INVALID_FD;
	_read_buffer = "";
	_write_buffer = std::queue<std::string>();

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
