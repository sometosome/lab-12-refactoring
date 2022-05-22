// Copyright 2021 Your Name <your_email>

#include <Parser.hpp>

Arguments parse_arguments(int argc, char* argv[]) {
  std::string filename;
  float threshold;
  variables_map vm;

  options_description desc("Allowed options");
  desc.add_options()
      ("help", "printing help information")
      ("input", value<std::string>(&filename)->default_value("data.txt"),
       "add file_name")
      ("threshold", value<float>(&threshold)->
          default_value(0.1), "add threshold");
  store(parse_command_line(argc, argv, desc), vm);
  notify(vm);
  if (vm.count("help"))
  {
    std::cout << desc << "\n";
    exit(0);
  }
  return { filename, threshold };
}
