//          `--::-.`
//      ./shddddddddhs+.
//    :yddddddddddddddddy:
//  `sdddddddddddddddddddds`
//  ydddh+sdddddddddy+ydddds  None:Lua
// /ddddy:oddddddddds:sddddd/ By adebray - adebray
// sdddddddddddddddddddddddds
// sdddddddddddddddddddddddds Created: 2015-03-24 10:27:00
// :ddddddddddhyyddddddddddd: Modified: 2015-05-12 04:11:35
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

void				Lua::init(void)
{
	this->exec("dofile('lua/init.lua')");
}

void				Lua::exec(std::string str)
{
	this->getError(luaL_loadbuffer(this->L, str.c_str(), str.size(), "line")
		|| lua_pcall(this->L, 0, 0, 0)
	);
}

void				Lua::getError(int error)
{
	if (error)
	{
		std::cerr << lua_tostring(this->L, -1) << std::endl;
		lua_pop(this->L, 1);  /* pop error message from the stack */
	}
}

Lua::s_luav *		Lua::getNestedVar(std::string name)
{
	lua_getglobal(L, name.c_str());

}

Lua::s_luav *		Lua::getVar(std::string name)
{
	Lua::s_luav *	tmp;

	if (name.find('.') != std::string::npos)
		std::cout << "nested va;" << std::endl;

	tmp = new Lua::s_luav();
	lua_getglobal(L, name.c_str());

	if (lua_isnumber(L, -1))
	{
		tmp->var._i = lua_tonumber(L, -1);
		tmp->type = Lua::TNUMBER;
	}
	else if (lua_isstring(L, -1))
	{
		tmp->var._s = lua_tostring(L, -1);
		tmp->type = Lua::TSTRING;
	}
	else
	{
		std::cout << "Unable to convert such value " << name << ": ";
		printType(lua_type (L, -1));
	}
	lua_pop(L, 1);
	return (tmp);
}

void				Lua::printType(int t)
{
	if (t == Lua::TNIL)
		std::cout << "TNIL type" << std::endl;
	if (t == Lua::TBOOLEAN)
		std::cout << "TBOOLEAN type" << std::endl;
	if (t == Lua::TLIGHTUSERDATA)
		std::cout << "TLIGHTUSERDATA type" << std::endl;
	if (t == Lua::TNUMBER)
		std::cout << "TNUMBER type" << std::endl;
	if (t == Lua::TSTRING)
		std::cout << "TSTRING type" << std::endl;
	if (t == Lua::TTABLE)
		std::cout << "TTABLE type" << std::endl;
	if (t == Lua::TFUNCTION)
		std::cout << "TFUNCTION type" << std::endl;
	if (t == Lua::TUSERDATA)
		std::cout << "TUSERDATA type" << std::endl;
	if (t == Lua::TTHREAD)
		std::cout << "TTHREAD type" << std::endl;
}

std::ostream &		operator<<(std::ostream & os, Lua::s_luav * obj)
{
	if (obj->type == Lua::TSTRING)
		os << obj->var._s;
	else if (obj->type == Lua::TNUMBER)
		os << obj->var._i;
	return os ;
}
