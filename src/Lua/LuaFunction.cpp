#include "LuaFunction.hpp"

ECL::LuaFunction::LuaFunction(
    const std::string &fileName, const std::string &funcName,
    const std::string &paramTypes, const std::size_t nbReturn
) : _fileName(fileName), _funcName(funcName), _paramTypes(paramTypes), _nbReturn(nbReturn), _currentArg(0)
{
    _lua = luaL_newstate();
    if (!_lua)
        throw std::exception();
    luaL_openlibs(_lua);

    if (luaL_dofile(_lua, _fileName.c_str()) != LUA_OK)
        throw std::exception();
}

ECL::LuaFunction::~LuaFunction()
{
    lua_close(_lua);
}

bool ECL::LuaFunction::operator()()
{
    Log &l = Log::get();

    if (_paramTypes.size() != 0)
    {
        l << Log::Color << Log::Error << Log::Time << "Bad argument number" << Log::Flush;
        return false;
    }

    lua_getglobal(_lua, _funcName.c_str());
    if (!lua_isfunction(_lua, -1))
    {
        l << Log::Color << Log::Error << Log::Time << "The string specified is not a function" << Log::Flush;
        return false;
    }

    lua_call(_lua, _paramTypes.size(), 0);

    return true;
}
