//          `--::-.`
//      ./shddddddddhs+.
//    :yddddddddddddddddy:
//  `sdddddddddddddddddddds`
//  ydddh+sdddddddddy+ydddds  None:Socket
// /ddddy:oddddddddds:sddddd/ By adebray - adebray
// sdddddddddddddddddddddddds
// sdddddddddddddddddddddddds Created: 2015-04-17 19:21:34
// :ddddddddddhyyddddddddddd: Modified: 2015-05-10 19:54:07
//  odddddddd/`:-`sdddddddds
//   +ddddddh`+dh +dddddddo
//    -sdddddh///sdddddds-
//      .+ydddddddddhs/.
//          .-::::-`

#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <vector>
#include <iostream>
#include <cstring>
#include <ios>

#include "Client.hpp"

extern "C" {
	#include <unistd.h>
	#include <sys/time.h>
	#include <sys/types.h>
	#include <netinet/ip.h>
	#include <arpa/inet.h>
}

class Socket {
private:
	Socket(void);
	Socket(Socket const &);

	Socket &	operator=(Socket const &);

	int						isset_cnt;
	int						fd;
	int						_nbClients;
	struct sockaddr_in		my_addr;
	fd_set					active_fd_set;
	fd_set					read_fd_set;
	std::vector<Client *>	_list;

	void					init(std::string, int);
	Client *				_accept(void);
	int						_read(int);
	void					_write(int, std::string);
	void					isset(void);
public:
	Socket(std::string, int);
	~Socket(void);

	void					_select(void);
	int						getNbClients(void);
	int						getFd(void);
};

#endif
