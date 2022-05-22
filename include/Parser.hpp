// Copyright 2021 Your Name <your_email>

#ifndef INCLUDE_PARSER_HPP_
#define INCLUDE_PARSER_HPP_

#include <Source.hpp>
#include <string>

using boost::program_options::options_description;
using boost::program_options::value;
using boost::program_options::variables_map;

struct Arguments {
  std::string filename;
  float threshold;
};

Arguments parse_arguments(int argc, char* argv[]);

#endif // INCLUDE_PARSER_HPP_
