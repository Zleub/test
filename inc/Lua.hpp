//          `--::-.`
//      ./shddddddddhs+.
//    :yddddddddddddddddy:
//  `sdddddddddddddddddddds`
//  ydddh+sdddddddddy+ydddds  test:Lua
// /ddddy:oddddddddds:sddddd/ By adebray - adebray
// sdddddddddddddddddddddddds
// sdddddddddddddddddddddddds Created: 2015-03-24 10:27:00
// :ddddddddddhyyddddddddddd: Modified: 2015-05-17 05:12:51
//  odddddddd/`:-`sdddddddds
//   +ddddddh`+dh +dddddddo
//    -sdddddh///sdddddds-
//      .+ydddddddddhs/.
//          .-::::-`

#ifndef LUA_HPP
#define LUA_HPP

#include <iostream>
#include <functional>

extern "C" {
	#include <luaconf.h>
	#include <lua.h>
	#include <lualib.h>
	#include <lauxlib.h>
}

class	Lua {
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
		std::function<void()>	_ptr;
		char const		*_s;
		int				_i;
	}				Lunion;

	typedef struct s_luav
	{
		Lunion	var;
		Type	type;
	}				Bundle;


	Lua(void);
	~Lua(void);
	void		init(void);
	void		exec(std::string);
	Bundle *	getVar(std::string);
	void		printType(int);

private:
	Lua(Lua const &);
	Lua &	operator=(Lua const &);

	lua_State	*L;

	void			getError(int);
	Bundle *		getNestedVar(std::string);
	Bundle *		makeBundle(std::string);
};

std::ostream &		operator<<(std::ostream & os, Lua::Bundle * obj);

#endif
