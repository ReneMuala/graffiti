#pragma once
#include "libGraffiti.hpp"
#include "sol/sol.hpp"
#include "sol/state.hpp"
#include "sol/types.hpp"
#include <memory>
using namespace std;
class Runner {
  string source;
  sol::state lua;

public:
  Runner(string source) : source(source) {
    // resolveGraffitiLibrary();
    lua.open_libraries(
      sol::lib::base,
      sol::lib::string,
      sol::lib::math,
      sol::lib::table, 
      sol::lib::package,

      sol::lib::debug, 
      sol::lib::bit32, 
      sol::lib::io,
      sol::lib::os,
      sol::lib::count,
      sol::lib::coroutine);
    resolveGraffitiLibrary(lua);
    lua.do_file(".graffiti/colors.lua");
    lua.do_file(".graffiti/strokejoins.lua");
    lua.do_file(".graffiti/strokecaps.lua");
    lua.do_file(".graffiti/libGraffiti.lua");
    auto result = lua.do_string(source);
    for(const auto & item: result){
      std::cout << item.as<string>()<< endl;
    }
  }
};