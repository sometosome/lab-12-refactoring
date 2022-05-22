#ifndef STAT_SENDER_HPP_
#define STAT_SENDER_HPP_

#include <Log.hpp>

class StatSender {
 private:
  bool wasLogCreated;
  const Log* log_;
  std::ofstream out_{"network", std::ios::binary};

 protected:
 virtual void AsyncSend(const std::vector<Item>& items, const std::string_view& path);

 public:
  StatSender();
  explicit StatSender(const Log& log);
  virtual ~StatSender();

  void OnLoaded(const std::vector<Item>& new_items);
  void Skip(const Item& item);
};

#endif // !STAT_SENDER_HPP_