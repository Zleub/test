//          `--::-.`
//      ./shddddddddhs+.
//    :yddddddddddddddddy:
//  `sdddddddddddddddddddds`
//  ydddh+sdddddddddy+ydddds  test:Manager
// /ddddy:oddddddddds:sddddd/ By adebray - adebray
// sdddddddddddddddddddddddds
// sdddddddddddddddddddddddds Created: 2015-05-10 19:54:36
// :ddddddddddhyyddddddddddd: Modified: 2015-05-10 23:10:49
//  odddddddd/`:-`sdddddddds
//   +ddddddh`+dh +dddddddo
//    -sdddddh///sdddddds-
//      .+ydddddddddhs/.
//          .-::::-`

#ifndef MANAGER_HPP
#define MANAGER_HPP

#include <Lua.hpp>

class Manager {
public:
	Manager(void);
	~Manager(void);

private:
	Lua			_L;

	Manager(Manager const &);
	Manager &	operator=(Manager const &);
};

#endif
