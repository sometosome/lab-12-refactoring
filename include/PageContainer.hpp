#ifndef PAGE_CONTAINER_HPP_
#define PAGE_CONTAINER_HPP_

#include <UsedMemory.hpp>
#include <StatSender.hpp>

#define K_MIN_LINES  10

class PageContainer {
 public:
  PageContainer();
  PageContainer(const Log& log, UsedMemory* memory_counter);
  ~PageContainer();

  void Load(std::istream& io, float threshold);
  const Item& ByIndex(const size_t& i) const;
  const Item& ById(const std::string& id) const;
  void Reload(const float& threshold);

 private:
  bool wasLogCreated;
  bool wasMemoryCounterCreated;
  const Log* log_;
  UsedMemory* memory_counter_;
  StatSender stat_sender_;
  std::vector<Item> data_;
  std::vector<std::string> raw_data_;
};

#endif // !PAGE_CONTAINER_HPP_
