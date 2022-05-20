#include <PageContainer.hpp>

PageContainer::PageContainer() : wasLogCreated(true), wasMemoryCounterCreated(true) {
  this->log_ = new Log;
  this->memory_counter_ = new UsedMemory;
}

PageContainer::PageContainer(const Log& log, UsedMemory* memory_counter)
    : wasLogCreated(false), wasMemoryCounterCreated(false),
      log_(&log), memory_counter_(memory_counter), stat_sender_(*log_) {}

PageContainer::~PageContainer() {
  if ((this->wasLogCreated) && (this->log_))
  {
    delete this->log_;
  }
  if ((this->wasMemoryCounterCreated) && (this->memory_counter_))
  {
    delete this->memory_counter_;
  }
}

//TODO: Maybe change treshold
void PageContainer::Load(std::istream& io, float threshold) {
  std::vector<std::string> raw_data;
  std::vector<Item> data;
  std::set<std::string> ids;

  while (!io.eof())
  {
    std::string line;
    std::getline(io, line, '\n');
    raw_data.push_back(std::move(line));
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
      data.push_back(std::move(item));
    } else
    {
      this->stat_sender_.Skip(item);
    }
  }

  if (data.size() < K_MIN_LINES)
  {
    throw std::runtime_error("oops");
  }

  this->memory_counter_->OnDataLoad(this->data_, data);
  this->stat_sender_.OnLoaded(data);
  this->data_ = std::move(data);
}

const Item& PageContainer::ByIndex(const size_t& i) const {
  return this->data_[i];
}

const Item& PageContainer::ById(const std::string& id) const {
  auto it = std::find_if (
      std::begin(this->data_),
      std::end(this->data_),
      [&id](const auto& i)
      { return id == i.id; }
      );
  return *it;
}

void PageContainer::Reload(const float& threshold) {
  std::vector<Item> data;
  std::set<std::string> ids;

  for (const auto& line : this->raw_data_)
  {
    std::stringstream stream(line);

    Item item;
    stream >> item.id >> item.name >> item.score;

    if (auto&& [_, inserted] = ids.insert(item.id); !inserted) {
      throw std::runtime_error("already seen");
    }

    if (item.score > threshold) {
      data.push_back(std::move(item));
    } else {
      this->stat_sender_.Skip(item);
    }
  }

  if (data.size() < K_MIN_LINES) {
    throw std::runtime_error("oops");
  }

  this->memory_counter_->OnDataLoad(this->data_, data);
  this->stat_sender_.OnLoaded(data);
  this->data_ = std::move(data);
}
