#pragma once
#include "libGraffiti.hpp"
#include "sol/sol.hpp"
#include "sol/state.hpp"
#include "sol/types.hpp"
#include <iostream>
#include <memory>
#include <string>
#include "scripts/colors.lua.hpp"
#include "scripts/strokejoins.lua.hpp"
#include "scripts/strokecaps.lua.hpp"
#include "scripts/libGraffiti.lua.hpp"

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
    // lua.do_file(".graffiti/colors.lua");
    if(not lua.do_string(scripts::colors0).valid()){
      std::cerr << "Error loading colors.0" << endl;
    }
    if(not lua.do_string(scripts::colors1).valid()){
      std::cerr << "Error loading colors.1" << endl;
    }
    // lua.do_file(".graffiti/strokejoins.lua");
    if(not lua.do_string(scripts::strokejoins).valid()){
      std::cerr << "Error loading strokejoins" << endl;
    }
    // lua.do_file(".graffiti/strokecaps.lua");
    if(not lua.do_string(scripts::strokecaps).valid()){
      std::cerr << "Error loading strokecaps" << endl;
    }
    // lua.do_file(".graffiti/libGraffiti.lua");
    if(not lua.do_string(scripts::libGraffiti).valid()){
      std::cerr << "Error loading libGraffiti" << endl;
    }
  }

  bool run(std::string filename) {
    auto result = lua.do_string(source);
    if (not result.valid()) {
      std::cerr << result.get<sol::error>().what() << endl;
      return false;
    } return true;
  }
};