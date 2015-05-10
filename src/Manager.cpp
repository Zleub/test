//          `--::-.`
//      ./shddddddddhs+.
//    :yddddddddddddddddy:
//  `sdddddddddddddddddddds`
//  ydddh+sdddddddddy+ydddds  test:Manager
// /ddddy:oddddddddds:sddddd/ By adebray - adebray
// sdddddddddddddddddddddddds
// sdddddddddddddddddddddddds Created: 2015-05-10 19:54:49
// :ddddddddddhyyddddddddddd: Modified: 2015-05-10 23:04:40
//  odddddddd/`:-`sdddddddds
//   +ddddddh`+dh +dddddddo
//    -sdddddh///sdddddds-
//      .+ydddddddddhs/.
//          .-::::-`

#include <Manager.hpp>

Manager::Manager(void)
{
	Lua::s_luav *	val;

	val = _L.getVar("Socket.host");
	std::cout << val << std::endl;
	val = _L.getVar("hello");
	std::cout << val << std::endl;
}

Manager::~Manager(void) {}
