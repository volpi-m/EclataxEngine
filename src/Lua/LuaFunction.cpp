#include "LuaFunction.hpp"

LuaFunction::LuaFunction(
    const std::string &fileName,
    const std::string &functionName,
    std::size_t nbParam,
    std::size_t nbReturn
) : _fileName(fileName), _functionName(functionName), _nbParam(nbParam), _nbReturn(nbReturn)
{
    _lua = luaL_newstate();
    if (!_lua)
        throw std::exception();
    luaL_openlibs(_lua);

    if (loadFile(_fileName) != LUA_OK)
        throw std::exception();
}

LuaFunction::~LuaFunction()
{
    lua_close(_lua);
}

bool LuaFunction::operator()()
{
    lua_getglobal(_lua, _functionName.c_str());

    std::cout << _functionName << " " << _nbParam << " " << _nbReturn << std::endl;

    lua_call(_lua, _nbParam, _nbReturn);
    return true;
}

int LuaFunction::loadFile(const std::string &name)
{
    _fileName = name;
    return luaL_dofile(_lua, _fileName.c_str());
}
