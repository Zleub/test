//          `--::-.`
//      ./shddddddddhs+.
//    :yddddddddddddddddy:
//  `sdddddddddddddddddddds`
//  ydddh+sdddddddddy+ydddds  None:main
// /ddddy:oddddddddds:sddddd/ By adebray - adebray
// sdddddddddddddddddddddddds
// sdddddddddddddddddddddddds Created: 2015-04-28 22:51:13
// :ddddddddddhyyddddddddddd: Modified: 2015-05-17 04:25:26
//  odddddddd/`:-`sdddddddds
//   +ddddddh`+dh +dddddddo
//    -sdddddh///sdddddds-
//      .+ydddddddddhs/.
//          .-::::-`

#include <iostream>
#include <Socket.hpp>
#include <Manager.hpp>

int		main(void)
{
	std::cout << "Hello Wolrd !" << std::endl;

	Manager		m;
	Socket		s("localhost", 4242);

	while (42)
		s._select();

	return (0);
}
