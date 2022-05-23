// Copyright 2021 Your Name <your_email>

#include <StatSender.hpp>

StatSender::StatSender() : wasLogCreated(true) {
  this->log_ = new Log;
}

StatSender::StatSender(const Log& log) : wasLogCreated(false), log_(&log) {}

StatSender::~StatSender() {
  if ((this->wasLogCreated) && (this->log_))
  {
    delete this->log_;
  }
}

 void StatSender::AsyncSend(
    const std::vector<Item>& items,
    const std::string_view& path) {
  this->log_->Write(path);
  this->log_->Write("send stat " + std::to_string(items.size()));

  for (const auto& item : items)
  {
    this->log_->WriteDebug("send: " + item.id);
    // ... some code
    this->out_ << item.id << item.name << item.score;
    this->out_.flush();
  }
}

void StatSender::OnLoaded(const std::vector<Item>& new_items) {
  log_->WriteDebug("StatSender::OnDataLoad");

  AsyncSend(new_items, "/items/loaded");
}

void StatSender::Skip(const Item& item) {
  AsyncSend({ item }, "/items/skipped");
}
