//          `--::-.`
//      ./shddddddddhs+.
//    :yddddddddddddddddy:
//  `sdddddddddddddddddddds`
//  ydddh+sdddddddddy+ydddds  test:Lua
// /ddddy:oddddddddds:sddddd/ By adebray - adebray
// sdddddddddddddddddddddddds
// sdddddddddddddddddddddddds Created: 2015-03-24 10:27:00
// :ddddddddddhyyddddddddddd: Modified: 2015-05-17 05:11:39
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

Lua::Bundle *		Lua::makeBundle(std::string name)
{
	Lua::Bundle *	tmp;

	tmp = new Lua::Bundle();
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
	else if (lua_istable(L, -1))
	{
		tmp->var._ptr = new std::function<void()>();
		tmp->type = Lua::TFUNCTION;
	}
	else
	{
		std::cout << "Unable to convert such value in Bundle " << name << ": ";
		printType(lua_type (L, -1));
	}
	return (tmp);
}

void				Lua::init(void)
{
	exec("require 'lua.init'");
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

Lua::Bundle *		Lua::getNestedVar(std::string name)
{
	Lua::Bundle *	tmp;
	std::string		table;
	std::string		remain;
	size_t			test;

	if ((test = name.find('.')) != std::string::npos)
	{
		table = name.substr(0, test);
		remain = name.substr(test + 1, std::string::npos);
	}

	if (!lua_istable(L, -1))
	{
		std::cout << table << " is no table !" << std::endl;
		return NULL;
	}
	if ((test = remain.find('.')) != std::string::npos)
	{
		lua_pushstring(L, remain.substr(0, test).c_str());
		lua_gettable(L, -2);
		tmp = getNestedVar(remain);
		lua_pop(L, 2);
		return tmp;
	}
	lua_pushstring(L, remain.c_str());
	lua_gettable(L, -2);
	tmp = makeBundle(remain);
	lua_pop(L, 2);
	return tmp;
}

Lua::Bundle *		Lua::getVar(std::string name)
{
	size_t			i;
	Lua::Bundle *	tmp;

	if ((i = name.find('.')) != std::string::npos)
	{
		lua_getglobal(L, name.substr(0, i).c_str());
		return getNestedVar(name);
	}

	lua_getglobal(L, name.c_str());
	tmp = makeBundle(name);
	lua_pop(L, 1);


	printType(lua_type(L, -1));
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
