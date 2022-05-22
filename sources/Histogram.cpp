// Copyright 2021 Your Name <your_email>

#include <Histogram.hpp>

float Histogram::get_score() {
  return this->score;
}

size_t Histogram::get_thresholdLoad(const size_t& pos) {
  return this->thresholdLoad[pos];
}

size_t Histogram::get_thresholdReload(const size_t& pos) {
  return this->thresholdReload[pos];
}

void Histogram::add_score(const float& _score) {
  this->score += _score;
  this->scoreNum++;
}

void Histogram::add_thresholdLoad(const bool& flag, const size_t& pos) {
  if (flag == NEW_VALUE)
  {
    this->thresholdLoad.push_back(0);
  } else{
    ++this->thresholdLoad[pos];
  }
}

void Histogram::add_thresholdReLoad(const bool& flag, const size_t& pos) {
  if (flag == NEW_VALUE)
  {
    this->thresholdReload.push_back(0);
  } else{
    ++this->thresholdReload[pos];
  }
}

