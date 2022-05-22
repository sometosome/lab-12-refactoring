// Copyright 2021 Your Name <your_email>

#ifndef INCLUDE_USEDMEMORY_HPP_
#define INCLUDE_USEDMEMORY_HPP_

#include <Log.hpp>
#include <string>
#include <vector>

class UsedMemory {
 private:
  bool wasLogCreated;
  const Log* log_;
  size_t used_;

 public:
  UsedMemory();
  explicit UsedMemory(const Log& log);
  ~UsedMemory();

  void OnDataLoad(const std::vector<Item>& old_items,
                  const std::vector<Item>& new_items);
  void OnRawDataLoad(const std::vector<std::string>& old_items,
                     const std::vector<std::string>& new_items);
  [[nodiscard]] size_t get_used() const;
};

#endif // INCLUDE_USEDMEMORY_HPP_
