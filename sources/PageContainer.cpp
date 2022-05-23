// Copyright 2021 Your Name <your_email>

#include <PageContainer.hpp>

PageContainer::PageContainer() : Histogram(),
                                 wasLogCreated(true),
                                 wasMemoryCounterCreated(true),
                                 wasStatSenderCreated(true),
                                 reloadNum(0),
                                 loadNum(0) {
  this->log_ = new Log;
  this->memory_counter_ = new UsedMemory;
  this->stat_sender_ = new StatSender;
}

PageContainer::PageContainer(const Log& log, UsedMemory* memory_counter) :
                             Histogram(),
                             wasLogCreated(false),
                             wasMemoryCounterCreated(false),
                             wasStatSenderCreated(false),
                             log_(&log),
                             memory_counter_(memory_counter),
                             stat_sender_(new StatSender(log)),
                             reloadNum(0),
                             loadNum(0) {}
PageContainer::PageContainer(StatSender* sender, UsedMemory* memory_counter):
                            Histogram(),
                            wasLogCreated(true),
                            wasMemoryCounterCreated(false),
                            wasStatSenderCreated(false),
                            memory_counter_(memory_counter),
                            stat_sender_(sender),
                            reloadNum(0),
                            loadNum(0) {
  this->log_ = new Log;
}

PageContainer::~PageContainer() {
  if ((this->wasLogCreated) && (this->log_))
  {
    delete this->log_;
  }
  if ((this->wasMemoryCounterCreated) && (this->memory_counter_))
  {
    delete this->memory_counter_;
  }
  if ((this->wasStatSenderCreated) && (this->stat_sender_))
  {
    delete this->stat_sender_;
  }
}

void PageContainer::Load(std::istream& io, float threshold) {
  bool flag = true;
  std::vector<std::string> raw_data;
  std::vector<Item> data;
  std::set<std::string> ids;

  std::string firstLine;
  std::getline(io, firstLine, '\n');
  if (firstLine.empty()){
    throw std::runtime_error("empty line");
  }else {
    while (!io.eof()) {
      std::string line;
      std::getline(io, line, '\n');
      raw_data.push_back(std::move(line));
    }
  }

  if (raw_data.size() < K_MIN_LINES)
  {
    throw std::runtime_error("too small input stream");
  }

  this->memory_counter_->OnRawDataLoad(this->raw_data_, raw_data);
  this->raw_data_ = std::move(raw_data);

  for (const auto& line : this->raw_data_)
  {
    std::stringstream stream(line);

    Item item;
    stream >> item.id >> item.name >> item.score;

    if (auto&& [_, inserted] = ids.insert(item.id); !inserted)
    {
      throw std::runtime_error("already seen");
    }

    if (item.score > threshold)
    {
      Histogram::add_score(item.score);
      data.push_back(std::move(item));
    } else{
      Histogram::add_thresholdLoad(flag, this->loadNum);
      if (flag)
      {
        flag = false;
      }
      this->stat_sender_->Skip(item);
    }
  }

  if (data.size() < K_MIN_LINES)
  {
    throw std::runtime_error("oops");
  }

  ++this->loadNum;

  this->memory_counter_->OnDataLoad(this->data_, data);
  this->stat_sender_->OnLoaded(data);
  this->data_ = std::move(data);
}

void PageContainer::Reload(const float& threshold) {
  bool flag = true;
  std::vector<Item> data;
  std::set<std::string> ids;

  for (const auto& line : this->raw_data_)
  {
    std::stringstream stream(line);

    Item item;
    stream >> item.id >> item.name >> item.score;

    if (auto&& [_, inserted] = ids.insert(item.id); !inserted)
    {
      throw std::runtime_error("already seen");
    }

    if (item.score > threshold)
    {
      Histogram::add_score(item.score);
      data.push_back(std::move(item));
    } else{
      Histogram::add_thresholdReLoad(flag, this->reloadNum);
      if (flag)
      {
        flag = false;
      }
      this->stat_sender_->Skip(item);
    }
  }

  if (data.size() < K_MIN_LINES)
  {
    throw std::runtime_error("oops");
  }

  ++this->reloadNum;

  this->memory_counter_->OnDataLoad(this->data_, data);
  this->stat_sender_->OnLoaded(data);
  this->data_ = std::move(data);
}

const Item& PageContainer::ByIndex(const size_t& i) const {
  return this->data_[i];
}

const Item& PageContainer::ById(const std::string& id) const {
  auto it = std::find_if(
      std::begin(this->data_),
      std::end(this->data_),
      [&id](const auto& i)
      { return id == i.id; });
  return *it;
}

size_t PageContainer::DataSize() const {
  return  data_.size();
}
