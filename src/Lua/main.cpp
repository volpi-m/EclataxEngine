#include "LuaFunction.hpp"

/*
TODO
    find a way to load a file one time and execute different function from this file
    set and get variables from the lua state
    parse configuration files
*/

int main()
{
    LuaFunction greets("example.lua", "yeet", 0, 0);
    std::cout << greets() << std::endl;
}
