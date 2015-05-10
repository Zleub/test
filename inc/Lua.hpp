//          `--::-.`
//      ./shddddddddhs+.
//    :yddddddddddddddddy:
//  `sdddddddddddddddddddds`
//  ydddh+sdddddddddy+ydddds  None:Lua
// /ddddy:oddddddddds:sddddd/ By adebray - adebray
// sdddddddddddddddddddddddds
// sdddddddddddddddddddddddds Created: 2015-03-24 10:27:00
// :ddddddddddhyyddddddddddd: Modified: 2015-05-10 18:27:45
//  odddddddd/`:-`sdddddddds
//   +ddddddh`+dh +dddddddo
//    -sdddddh///sdddddds-
//      .+ydddddddddhs/.
//          .-::::-`

#ifndef LUA_HPP
#define LUA_HPP

extern "C" {
	#include <lua.h>
	#include <lualib.h>
	#include <lauxlib.h>
}

class	Lua {
private:
	Lua(Lua const &);
	Lua &	operator=(Lua const &);

	lua_State	*L;

	void			getError(int);
	std::string		getString(std::string);
	int				getNumber(std::string);
	// int			getTable(std::string);

	std::string		getType(std::string);
public:
	enum Type
	{
		NBR,
		STR
	};
	union Test
	{
		char const	*_s;
		int			_i;
	};
	struct Caca
	{
		Test	var;
		Type	type;
	};


	Lua(void);
	~Lua(void);

	/** Lua in-interpret init */
	void		init(void);
	/** Lua exec */
	void		exec(std::string);

	union Test	getVar(std::string);
};

std::ostream &		operator<<(std::ostream & os, Lua::Test obj);

#endif
