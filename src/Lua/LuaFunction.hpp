#ifndef LUAFUNCTION_HPP_
#define LUAFUNCTION_HPP_

#include <string>
#include <iostream>
#include <exception>
#include <vector>
#include <any>
#include <cstring>

extern "C"
{
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
}

class LuaFunction
{
public:
    LuaFunction(const std::string &, const std::string &, std::size_t, std::size_t);
    ~LuaFunction();

    template<typename T, typename ... Args>
    bool operator()(T first, Args ... args);

    template<typename T>
    bool operator()(T last);

    bool operator()();

private:
    int loadFile(const std::string &);

    std::string _fileName;
    std::string _functionName;
    std::size_t _nbParam;
    std::size_t _nbReturn;
    lua_State *_lua;
};

#endif /* !LUAFUNCTION_HPP_ */
