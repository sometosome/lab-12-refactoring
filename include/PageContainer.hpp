// Copyright 2021 Your Name <your_email>

#ifndef INCLUDE_PAGECONTAINER_HPP_
#define INCLUDE_PAGECONTAINER_HPP_

#include <UsedMemory.hpp>
#include <StatSender.hpp>
#include <Histogram.hpp>
#include <string>
#include <vector>

#define K_MIN_LINES  10

class PageContainer : public Histogram {
 public:
  PageContainer();
  PageContainer(const Log& log, UsedMemory* memory_counter);
  PageContainer(StatSender* sender, UsedMemory* memory_counter);
  ~PageContainer();

  void Load(std::istream& io, float threshold);
  void Reload(const float& threshold);

  const Item& ByIndex(const size_t& i) const;
  const Item& ById(const std::string& id) const;

  size_t DataSize() const;

 private:
  bool wasLogCreated;
  bool wasMemoryCounterCreated;
  bool wasStatSenderCreated;
  const Log* log_;
  UsedMemory* memory_counter_;
  StatSender* stat_sender_;
  std::vector<Item> data_;
  std::vector<std::string> raw_data_;
  size_t reloadNum;
  size_t loadNum;
};

#endif // INCLUDE_PAGECONTAINER_HPP_
