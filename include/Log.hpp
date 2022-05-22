// Copyright 2021 Your Name <your_email>

#ifndef INCLUDE_LOG_HPP_
#define INCLUDE_LOG_HPP_

#include <Source.hpp>
#include <string>

#define LOG_ENABLE    0x10000000
#define LOG_DISABLE   0x00000000

struct Item {
  std::string id;
  std::string name;
  float score = 0;
};

class Log {
 private:
  size_t level_;
  mutable std::ostream* out_;

 public:
  Log();
  explicit Log(const size_t& level);

  void Write(const std::string_view& message) const;
  void WriteDebug(const std::string_view& message) const;
};

#endif // INCLUDE_LOG_HPP_
