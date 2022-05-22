// Copyright 2021 Your Name <your_email>

#ifndef INCLUDE_HISTOGRAM_HPP_
#define INCLUDE_HISTOGRAM_HPP_

#include <Source.hpp>
#include <vector>

#define NEW_VALUE     true

class Histogram {
 private:
  float score;
  std::vector<size_t> thresholdLoad;
  std::vector<size_t> thresholdReload;
  size_t scoreNum;

 public:
  float get_score();
  size_t get_thresholdLoad(const size_t& pos);
  size_t get_thresholdReload(const size_t& pos);
  void add_score(const float& _score);
  void add_thresholdLoad(const bool& flag, const size_t& pos);
  void add_thresholdReLoad(const bool& flag, const size_t& pos);
};

#endif // INCLUDE_HISTOGRAM_HPP_
