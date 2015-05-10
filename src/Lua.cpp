//          `--::-.`
//      ./shddddddddhs+.
//    :yddddddddddddddddy:
//  `sdddddddddddddddddddds`
//  ydddh+sdddddddddy+ydddds  None:Lua
// /ddddy:oddddddddds:sddddd/ By adebray - adebray
// sdddddddddddddddddddddddds
// sdddddddddddddddddddddddds Created: 2015-03-24 10:27:00
// :ddddddddddhyyddddddddddd: Modified: 2015-04-30 15:11:45
//  odddddddd/`:-`sdddddddds
//   +ddddddh`+dh +dddddddo
//    -sdddddh///sdddddds-
//      .+ydddddddddhs/.
//          .-::::-`

#include <iostream>
#include <Lua.hpp>

Lua::Lua(void)
{
		std::cout << "Lua Constructor" << std::endl;

	this->L = luaL_newstate();
	luaL_openlibs(this->L);
	this->init();
}

Lua::~Lua(void) {}

void		Lua::init(void)
{
	this->exec("dofile('init.lua')\n");
}

void		Lua::exec(std::string str)
{
	this->getError(luaL_loadbuffer(this->L, str.c_str(), str.size(), "line")
		|| lua_pcall(this->L, 0, 0, 0)
	);
}

void		Lua::getError(int error)
{
	if (error)
	{
		std::cerr << lua_tostring(this->L, -1) << std::endl;
		lua_pop(this->L, 1);  /* pop error message from the stack */
	}
}

std::string	Lua::getString(std::string name)
{
	lua_getglobal(L, name.c_str());
	if (!lua_isstring(L, -1))
		std::cerr << "No " << name << " string" << std::endl;
	else
		return lua_tostring(L, -1);
	return ("");
}

int			Lua::getNumber(std::string name)
{
	lua_getglobal(L, name.c_str());
	if (!lua_isnumber(L, -1))
		std::cerr << "No " << name << " number" << std::endl;
	else
		return lua_tonumber(L, -1);
	return (0);
}

Lua::Test	Lua::getVar(std::string name)
{
	// Lua::Caca
	Lua::Test _u;

	_u._s = 0;
	lua_getglobal(L, name.c_str());
	if (lua_isnumber(L, -1))
		_u._i = lua_tonumber(L, -1);
	else if (lua_isstring(L, -1))
		_u._s = lua_tostring(L, -1);
	return (_u);
}

std::ostream &		operator<<(std::ostream & os, Lua::Test obj)
{
	(void)obj;
	// if (obj._s)
	// 	std::cout << obj._s << std::endl;
	// else if (obj._i)
	// 	std::cout << obj._i << std::endl;
	// else
	// 	std::cout << "Time for BULLSHIT" << std::endl;
	return os << "This is op surcharge" << std::endl;
}
