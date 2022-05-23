// Copyright 2021 Your Name <your_email>

#ifndef INCLUDE_STATSENDER_HPP_
#define INCLUDE_STATSENDER_HPP_

#include <Log.hpp>
#include <vector>

class StatSender {
 private:
  bool wasLogCreated;
  const Log* log_;
  std::ofstream out_{"network", std::ios::binary};

 public:
  virtual void AsyncSend(const std::vector<Item>& items,
                         const std::string_view& path);

 public:
  StatSender();
  explicit StatSender(const Log& log);
  virtual ~StatSender();

  void OnLoaded(const std::vector<Item>& new_items);
  void Skip(const Item& item);
};

#endif // INCLUDE_STATSENDER_HPP_
