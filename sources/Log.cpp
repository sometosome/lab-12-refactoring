// Copyright 2021 Your Name <your_email>

#include <Log.hpp>
#include <algorithm>
#include <iostream>
#include <set>
#include <sstream>

Log::Log() : level_(LOG_DISABLE), out_(&std::cout) {}

Log::Log(const size_t& level) : level_(level), out_(&std::cout) {}

void Log::Write(const std::string_view& message) const {
  *this->out_ << message << std::endl;
}

void Log::WriteDebug(const std::string_view& message) const {
  if (this->level_ == LOG_ENABLE)
  {
    *this->out_ << message << std::endl;
  }
}
