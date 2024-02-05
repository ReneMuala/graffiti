#pragma once

#include <blend2d.h>
#include <format>
#include <fstream>
#include <ios>
#include <iostream>
#include <regex>
#include <string>

using namespace std;

class FileReader {
  string filename;
  ifstream file;
  string result;

public:
  FileReader(string filename) : filename(filename) { file.open(filename); }
  string getResult() const { return result; }

  string getFilename() const { return filename; }

  string resolveContext(string line) {
    int tabsCount = 0;
    for (char _char : line)
      if (_char == '\t')
        tabsCount++;
    return tabsCount ? regex_replace(
                           line, regex("(\t)+\\."),
                           std::format("gg({}).", std::to_string(tabsCount)))
                     : line;
  }

  string resolveStrings(string line) {
    smatch match;
    while (regex_search(line, match, regex(R"(\(\s*[^\,(]+\.\w+\s*\))"))) {
      line = line.replace(
          line.find(match.str()), match.str().length(),
          std::format("{}", regex_replace(match.str(),
                                          regex(R"([^\(,]+\.\w+\s*)"),
                                          "\"$&\"")));
    }
    return line;
  }

  string resolveLeading(string line) {
    return line.find_first_of('.') == 0 ? "gg(1)" + line : line;
  }

  string resolvePx(string line) {
    smatch match;
    while (regex_search(line, match, regex("\\d+(\\.\\d+)?px"))) {
      const auto length = match.str().length();
      line = line.replace(
          line.find(match.str()), length,
          std::format("unit:pixel({})", match.str().substr(0, length - 2)));
    }
    return line;
  }

  string resolveCm(string line) {
    smatch match;
    while (regex_search(line, match, regex("\\d+(\\.\\d+)?cm"))) {
      const auto length = match.str().length();
      line = line.replace(
          line.find(match.str()), length,
          std::format("unit:cm({})", match.str().substr(0, length - 2)));
    }
    return line;
  }

  string resolveDeg(string line) {
    smatch match;
    while (regex_search(line, match, regex("\\d+(\\.\\d+)?deg"))) {
      const auto length = match.str().length();
      line = line.replace(
          line.find(match.str()), length,
          std::format("unit:deg({})", match.str().substr(0, length - 3)));
    }
    return line;
  }

  void read() {
    string line;
    while (getline(file, line)) {
      auto aux = resolveCm(
          resolvePx(resolveDeg(resolveLeading(resolveStrings(resolveContext(line))))));
      result += aux + "\n";
      // cout << aux << endl;
    }
  }
};