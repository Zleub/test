//          `--::-.`
//      ./shddddddddhs+.
//    :yddddddddddddddddy:
//  `sdddddddddddddddddddds`
//  ydddh+sdddddddddy+ydddds  None:main
// /ddddy:oddddddddds:sddddd/ By adebray - adebray
// sdddddddddddddddddddddddds
// sdddddddddddddddddddddddds Created: 2015-04-28 22:51:13
// :ddddddddddhyyddddddddddd: Modified: 2015-04-30 14:16:03
//  odddddddd/`:-`sdddddddds
//   +ddddddh`+dh +dddddddo
//    -sdddddh///sdddddds-
//      .+ydddddddddhs/.
//          .-::::-`

#include <iostream>
#include <Socket.hpp>

int		main(void)
{
	std::cout << "Hello Wolrd !" << std::endl;

	Lua			L;
	Socket		s("pollier.me", 4242);

	s.setLua(&L);
	while (42)
		s._select();

	return (0);
}
