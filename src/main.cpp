#include "FileReader.hpp"
#include "Runner.hpp"
#include "libGraffiti.hpp"
#include <iostream>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    _graffiti_native::show_version();
    std::cout << "Usage: graffiti <file1> <file2> ... <fileN>" << std::endl;
    return 1;
  }
  for (int i = 1; i < argc; i++) {
    std::string filename = argv[i];
    FileReader reader(filename);
    if (not reader.read()) continue;
    Runner runner(reader.getResult());
    if(not runner.run(filename)){
      std::cerr << "Error running file: " << filename << std::endl;
      continue;
    }
  }
  return 0;
}
