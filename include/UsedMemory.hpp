#ifndef USED_MEMORY_HPP_
#define USED_MEMORY_HPP_

#include <Log.hpp>

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

#endif // !USED_MEMORY_HPP_