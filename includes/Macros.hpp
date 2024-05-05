#pragma once

/*****	Libraries	****/

#include <iostream>
#include <cstdlib> //EXIT_FAILURE/SUCCESS
// #include <cstdio> //stderr
#include <cstring> //memset
#include <unistd.h> //close()
#include <cerrno> //for errno

#include <string>
// #include <map>
#include <vector>

#include <sys/socket.h> //socket()
#include <netdb.h> //struct addrinfo
#include <fcntl.h>
#include <sys/epoll.h>

// #include <sys/types.h>
// #include <netinet/in.h> //to retrieve ip and port from sockaddr_storage client_addr
// #include <arpa/inet.h>

/****	Values	****/
#define	EXPECTED_ARGC	3

#define	INVALID_FD		-1
#define	INVALID_PORT	-1
#define	INVALID_LISTEN	-1
#define	INVALID_FCNTL	-1
#define	INVALID_ACCEPT	-1
#define	INVALID_NB	-1

#define	MAX_PENDING_CONNECTIONS	5 //most servers accept 20
#define	MAX_REQUESTS 50 //for epoll_wait (je me rends pas compte de combien on devrait mettre)
#define WAIT_UNTIL_SOMETHING_HAPPENS -1

#define IPv4	AF_INET
#define IPv6	AF_INET6

// #define ALL_IP_TYPES		AF_UNSPEC
#define ALL_IP_TYPES		AF_INET
#define TCP_STREAM_SOCKET	SOCK_STREAM
#define LOCAL_IP			AI_PASSIVE
#define CHOOSE_AUTOMATICALLY	0

#define IP_TYPES	ai_family
#define SOCKET_TYPE	ai_socktype
#define SERVER_IP	ai_flags
#define PROTOCOL	ai_protocol

#define IRSSI 0
#define NETCAT 1

/****	Errors	****/
#define ERROR			"Error\n"

// Errors main
#define	ERROR_ARG		DELIM BRED ERROR "Expected: ./ircserv <port> <password>\n" DELIM PRINT_END
#define	ERROR_PORT		DELIM BRED ERROR "Invalid port!\n" DELIM PRINT_END
#define	ERROR_PASS		DELIM BRED ERROR "Invalid password!\n" DELIM PRINT_END

// Exceptions
#define	ERROR_SOCKET			DELIM BRED ERROR "Failed to create socket!\n" DELIM
#define	ERROR_BIND				DELIM BRED ERROR "Failed to bind socket to port!\n" DELIM
#define	ERROR_LISTEN			DELIM BRED ERROR "Listen failed!\n" DELIM
#define	ERROR_ACCEPT			DELIM BRED ERROR "Accept failed!\n" DELIM
#define	ERROR_FAIL_MSG			DELIM BRED ERROR "Failed to send welcome message to client!\n" DELIM
#define	ERROR_DC				DELIM BRED ERROR "Client disconnected before welcome message was sent!\n" DELIM
#define	ERROR_EPOLL_CREATE		DELIM BRED ERROR "Epoll creation failed!\n" DELIM
#define	ERROR_EPOLL_CTL			DELIM BRED ERROR "Epoll failed to add client fd!\n" DELIM
#define	ERROR_EPOLL_WAIT		DELIM BRED ERROR "Epoll failed to wait for events!\n" DELIM
#define	ERROR_GETADDRINFO		DELIM BRED ERROR "Getaddrinfo failed!\n" DELIM
#define	ERROR_FCNTL				DELIM BRED ERROR "Fcntl failed to set socket to non-blocking mode\n" DELIM
#define	ERROR_READ			 	DELIM BRED ERROR "Failed to read from client!\n" DELIM
#define	ERROR_SEND			 	DELIM BRED ERROR "Failed to send msg to client!\n" DELIM
#define	ERROR_PASSW				DELIM BRED ERROR "Invalid password : connection to server refused\n" DELIM
#define	ERROR_PSWD				DELIM BRED ERROR "Invalid password command! Expected : PASS <password>\n" DELIM
#define	ERROR_USER				DELIM BRED ERROR "Invalid username command! Expected : USER <username>\n" DELIM
#define	ERROR_NICK				DELIM BRED ERROR "Invalid nickname command! Expected : NICK <nickname>\n" DELIM

//est ce qu on peut ecrire ca comme ca? : (si oui faire pour tous les erno)
// #define	ERROR_GETADDRINFO		DELIM BRED ERROR "Getaddrinfo failed: " + static_cast<std::string>(gai_strerror(ret)) PRINT_END

/****	Debug	****/
//Constructors & Destructors
#define	DEBUG		1
#define	D_CONST		SEP "default constructor called" PRINT_END
#define	C_CONST		SEP "copy constructor called" PRINT_END
#define	P_CONST		SEP "parametric constructor called" PRINT_END
#define	DECONST		SEP "deconstructor called" PRINT_END

//Calls
#define	SERV_CLOSED	std::cout << BYEL "	-Server closed-" << PRINT_END

//Classes
#define	CLIENT		"Client"
#define	SERVER		"Server"

#define COMMAND_END	"\r\n"

/****	PROTOCOL MESSAGES	****/
#define WELCOME_MESSAGE(username) ":ircserv 001 " + username + \
	" :Welcome to the ircserv IRC Network " + username + \
	"!~" + username + "@127.0.0.1\n" + \
	":ircserv 002 " + username + \
	" :Your host is ircserv, running version bahamut-2.2.2\n" + \
	":ircserv 003 " + username + \
	" :This server was created Tue Apr 30 2024 at 16:38:57 UTC"

/****	Visuals	****/

//Separators
#define	SEP		"	--> "
#define	DELIM	BYEL "--------------------------------------------------\n"

//Blinks
#define	BL_ON	"\033[5m"
#define	BL_OFF	"\033[25m"

//Regular text
#define	BLK		"\e[0;30m"
#define	RED		"\e[0;31m"
#define	GRN		"\e[0;32m"
#define	YEL		"\e[0;33m"
#define	BLU		"\e[0;34m"
#define	MAG		"\e[0;35m"
#define	CYN		"\e[0;36m"
#define	WHT		"\e[0;37m"

//Regular bold text
#define	BBLK	"\e[1;30m"
#define	BRED	"\e[1;31m"
#define	BGRN	"\e[1;32m"
#define	BYEL	"\e[1;33m"
#define	BBLU	"\e[1;34m"
#define	BMAG	"\e[1;35m"
#define	BCYN	"\e[1;36m"
#define	BWHT	"\e[1;37m"

//Regular underline text
#define	UBLK	"\e[4;30m"
#define	URED	"\e[4;31m"
#define	UGRN	"\e[4;32m"
#define	UYEL	"\e[4;33m"
#define	UBLU	"\e[4;34m"
#define	UMAG	"\e[4;35m"
#define	UCYN	"\e[4;36m"
#define	UWHT	"\e[4;37m"

//Regular background
#define	BLKB	"\e[40m"
#define	REDB	"\e[41m"
#define	GRNB	"\e[42m"
#define	YELB	"\e[43m"
#define	BLUB	"\e[44m"
#define	MAGB	"\e[45m"
#define	CYNB	"\e[46m"
#define	WHTB	"\e[47m"

//High intensty background
#define	BLKHB	"\e[0;100m"
#define	REDHB	"\e[0;101m"
#define	GRNHB	"\e[0;102m"
#define	YELHB	"\e[0;103m"
#define	BLUHB	"\e[0;104m"
#define	MAGHB	"\e[0;105m"
#define	CYNHB	"\e[0;106m"
#define	WHTHB	"\e[0;107m"

//High intensty text
#define	HBLK	"\e[0;90m"
#define	HRED	"\e[0;91m"
#define	HGRN	"\e[0;92m"
#define	HYEL	"\e[0;93m"
#define	HBLU	"\e[0;94m"
#define	HMAG	"\e[0;95m"
#define	HCYN	"\e[0;96m"
#define	HWHT	"\e[0;97m"

//Bold high intensity text
#define	BHBLK	"\e[1;90m"
#define	BHRED	"\e[1;91m"
#define	BHGRN	"\e[1;92m"
#define	BHYEL	"\e[1;93m"
#define	BHBLU	"\e[1;94m"
#define	BHMAG	"\e[1;95m"
#define	BHCYN	"\e[1;96m"
#define	BHWHT	"\e[1;97m"

//Reset
#define	RESET		"\e[0m"
#define	PRINT_END	RESET << std::endl
#define	LINE_BREAK	std::cout << std::endl
