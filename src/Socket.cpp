//          `--::-.`
//      ./shddddddddhs+.
//    :yddddddddddddddddy:
//  `sdddddddddddddddddddds`
//  ydddh+sdddddddddy+ydddds  None:Socket
// /ddddy:oddddddddds:sddddd/ By adebray - adebray
// sdddddddddddddddddddddddds
// sdddddddddddddddddddddddds Created: 2015-04-17 19:22:25
// :ddddddddddhyyddddddddddd: Modified: 2015-05-10 18:32:20
//  odddddddd/`:-`sdddddddds
//   +ddddddh`+dh +dddddddo
//    -sdddddh///sdddddds-
//      .+ydddddddddhs/.
//          .-::::-`

#include <sstream>
#include <Socket.hpp>

Socket::Socket(std::string host, int port) : _nbClients(0)
{
	fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd == -1)
		std::cerr << "socket creation failed" << std::endl;

	memset(&(my_addr), 0, sizeof(struct sockaddr_in));
	my_addr.sin_family = AF_INET;
	inet_aton(host.c_str(), (struct in_addr *)&(my_addr).sin_addr);
	my_addr.sin_port = htons(port);

	if (bind(fd, (struct sockaddr *)&(my_addr), sizeof(struct sockaddr_in)) == -1)
		std::cerr << "bind failed" << std::endl;
	if (listen(fd, 0) == -1)
		std::cerr << "listen failed" << std::endl;

	FD_ZERO (&(active_fd_set));
	FD_SET (fd, &(active_fd_set));
};

Socket::~Socket(void) { close(fd); };

void	Socket::_select(void)
{
	std::cout << "_select : nb client : " << _nbClients << std::endl;

	read_fd_set = active_fd_set;
	if (select (FD_SETSIZE, &(read_fd_set), NULL, NULL, NULL) < 0)
	{
		std::cerr << "select" << std::endl;
		return ;
	}
	isset_cnt = 0;
	isset();
};

void		Socket::isset(void)
{
	if (FD_ISSET (isset_cnt, &(read_fd_set)))
	{
		if (isset_cnt == fd)
			_accept();
		else if (!_read(isset_cnt))
		{
			std::cout << "Client " << isset_cnt << " left" << std::endl;
			close (isset_cnt);
			FD_CLR (isset_cnt, &active_fd_set);
			_nbClients -= 1;
		}
	}
	isset_cnt += 1;
	if (isset_cnt < FD_SETSIZE)
		isset();
}

Client *	Socket::_accept(void)
{
	Client *	c;

	c = new Client();
	c->setFd(accept(fd, c->getAddr(), c->getAddrsize()));
	if (c->getFd() < 0)
		std::cerr << "error accept" << std::endl;
	std::cout << "new client on " << c->getFd() << std::endl;
	_nbClients += 1;
	FD_SET(c->getFd(), &(active_fd_set));
	return (c);
}

void		Socket::_write(int fd, std::string str)
{
	str += '\n';
	write(fd, str.c_str(), str.size());
}

int			Socket::_read(int fd)
{
	char	buf[255];
	int		n;

	memset(buf, 0, 255);
	if (!(n = read(fd, buf, 255)))
	{
		std::cout << "exit ?" << std::endl;


		return 0;
	}
	else if (n < 0)
	{
		std::cerr << "read" << std::endl;
		return 0;
	}
	else
	{
		std::cout << "got message: \'" << buf << "\' by " << fd << std::endl;

		int out = dup(1);
		dup2(fd, 1);
		_L->exec(buf);
		dup2(out, 1);

		return 1;
	}
}

int		Socket::getFd(void) { return fd; }
int		Socket::getNbClients(void) { return _nbClients; }
void	Socket::setLua(Lua * _l) { _L = _l; }
