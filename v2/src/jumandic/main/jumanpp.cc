//
// Created by Arseny Tolmachev on 2017/03/09.
//

#include "jumanpp.h"
#include <fstream>
#include <iostream>
#include "jumanpp_args.h"

using namespace jumanpp;

int main(int argc, char** argv) {
  std::istream* inputSrc;
  std::unique_ptr<std::ifstream> filePtr;

  jumandic::JumanppConf conf;
  if (!jumandic::parseArgs(argc, argv, &conf)) {
    jumandic::parseArgs(0, nullptr, nullptr);
    return 1;
  }

  JumanppExec exec{conf};
  Status s = exec.init();
  if (!s.isOk()) {
    std::cerr << "failed to load model from disk: " << s.message;
    return 1;
  }

  if (conf.inputFile == "-") {
    inputSrc = &std::cin;
  } else {
    filePtr.reset(new std::ifstream{conf.inputFile});
    if (!*filePtr) {
      std::cerr << "could not open file " << conf.inputFile << " for reading";
      return 1;
    }
    inputSrc = filePtr.get();
  }

  std::string input;
  std::string comment;
  while (*inputSrc) {
    std::getline(*inputSrc, input);
    if (input.size() > 2 && input[0] == '#' && input[1] == ' ') {
      comment.clear();
      comment.append(input.begin() + 2, input.end());
      input.clear();
      std::getline(*inputSrc, input);
    }
    Status st = exec.analyze(input, comment);
    if (!st) {
      std::cerr << "error when analyzing sentence [ " << input
                << "] :" << st.message << "\n";
      std::cout << "EOS\n";
    } else {
      std::cout << exec.output();
    }
  }
  return 0;
}