#ifndef LUAFUNCTION_HPP_
#define LUAFUNCTION_HPP_

#include <string>
#include <iostream>
#include <exception>

#include "Log.hpp"

extern "C"
{
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
}

namespace ECL
{
    class LuaFunction
    {
    public:
        LuaFunction(const std::string &, const std::string &, const std::string &, const std::size_t);
        ~LuaFunction();

        constexpr static auto const NONE = "";
        constexpr static auto const INT = "i";
        constexpr static auto const CSTRING = "s";
        constexpr static auto const DOUBLE = "d";
        constexpr static auto const BOOL = "b";
/*
        template<typename T, typename ...Args>
        bool operator()(T first, Args... args)
        {
            Log &l = Log::get();

            if (_paramTypes.size() < 2)
            {
                l << Log::Color << Log::Error << Log::Time << "Bad argument number" << Log::Flush;
                return false;
            }

            pushOnStack(first);

            std::cout << "yeet" << std::endl;
            return operator()(args...);
        }

        template<typename T>
        bool operator()(T last)
        {
            Log &l = Log::get();

            if (_paramTypes.size() < 1)
            {
                l << Log::Color << Log::Error << Log::Time << "Bad argument number" << Log::Flush;
                return false;
            }

            pushOnStack(last);

            std::cout << "ending" << std::endl;
            return true;
        }*/

        bool operator()();

    private:
        template<typename T>
        void pushOnStack(T arg)           { lua_pushinteger(_lua, arg); }
        void pushOnStack(lua_Number arg)  { lua_pushnumber(_lua, arg); }
        void pushOnStack(float arg)       { lua_pushnumber(_lua, arg); }
        void pushOnStack(bool arg)        { lua_pushboolean(_lua, arg ? 1 : 0); }
        void pushOnStack(const char *arg) { lua_pushstring(_lua, arg); }

        const std::string _fileName;
        const std::string _funcName;
        const std::string _paramTypes;
        const std::size_t _nbReturn;
        std::size_t _currentArg;
        lua_State *_lua;
    };
}

#endif /* !LUAFUNCTION_HPP_ */
