// Copyright 2021 Your Name <your_email>

#include <UsedMemory.hpp>

UsedMemory::UsedMemory() : wasLogCreated(true), used_(0) {
  this->log_ = new Log;
}

UsedMemory::UsedMemory(const Log& log) : wasLogCreated(false),
                                         log_(&log), used_(0) {}

UsedMemory::~UsedMemory() {
  if ((this->wasLogCreated) && (this->log_))
  {
    delete this->log_;
  }
}

void UsedMemory::OnDataLoad(const std::vector<Item>& old_items,
                            const std::vector<Item>& new_items) {
  this->log_->WriteDebug("UsedMemory::OnDataLoad");

  for (const auto& item : old_items)  // Huinya!
  {
    this->used_ -= item.id.capacity();
    this->used_ -= item.name.capacity();
    this->used_ -= sizeof(item.score);
  }

  for (const auto& item : new_items)
  {
    this->used_ += item.id.capacity();
    this->used_ += item.name.capacity();
    this->used_ += sizeof(item.score);
  }

  this->log_->Write("UsedMemory::OnDataLoad: new size = " +
                    std::to_string(used_));
}

void UsedMemory::OnRawDataLoad(const std::vector<std::string>& old_items,
                               const std::vector<std::string>& new_items) {
  this->log_->WriteDebug("UsedMemory::OnRawDataLoads");

  for (const auto& item : old_items)  // Huinya!
  {
    this->used_ -= item.capacity();
  }

  for (const auto& item : new_items) {
    this->used_ += item.capacity();
  }

  this->log_->Write("UsedMemory::OnDataLoad: new size = " +
                    std::to_string(this->used_));
}

size_t UsedMemory::get_used() const {
  return this->used_;
}
