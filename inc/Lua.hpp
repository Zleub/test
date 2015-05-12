//          `--::-.`
//      ./shddddddddhs+.
//    :yddddddddddddddddy:
//  `sdddddddddddddddddddds`
//  ydddh+sdddddddddy+ydddds  None:Lua
// /ddddy:oddddddddds:sddddd/ By adebray - adebray
// sdddddddddddddddddddddddds
// sdddddddddddddddddddddddds Created: 2015-03-24 10:27:00
// :ddddddddddhyyddddddddddd: Modified: 2015-05-12 04:08:52
//  odddddddd/`:-`sdddddddds
//   +ddddddh`+dh +dddddddo
//    -sdddddh///sdddddds-
//      .+ydddddddddhs/.
//          .-::::-`

#ifndef LUA_HPP
#define LUA_HPP

#include <iostream>

extern "C" {
	#include <luaconf.h>
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
	s_luav *		getNestedVar(std::string);

public:
	typedef enum	e_luav
	{
		TNIL,
		TBOOLEAN,
		TLIGHTUSERDATA,
		TNUMBER,
		TSTRING,
		TTABLE,
		TFUNCTION,
		TUSERDATA,
		TTHREAD
	}				Type;

	typedef union	u_luav
	{
		char const	*_s;
		int			_i;
	}				Lunion;

	struct s_luav
	{
		Lunion	var;
		Type	type;
	};


	Lua(void);
	~Lua(void);
	void		init(void);
	void		exec(std::string);
	s_luav *	getVar(std::string);
	void		printType(int);
};

std::ostream &		operator<<(std::ostream & os, Lua::s_luav * obj);

#endif
