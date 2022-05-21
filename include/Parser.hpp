#ifndef PARSER_HPP_
#define PARSER_HPP_

#include <Source.hpp>

using boost::program_options::options_description;
using boost::program_options::value;
using boost::program_options::variables_map;

struct Arguments {
  std::string filename;
  float threshold;
};

Arguments parse_arguments(int argc, char* argv[]);

#endif // !PARSER_HPP_