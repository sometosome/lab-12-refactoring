// Copyright 2021 Your Name <your_email>

#include <gmock/gmock.h>

#include <PageContainer.hpp>
#include "MockStatSender.h"
#include <UsedMemory.hpp>

TEST(MemoryUsage, MemUsingTest) {
  std::vector<std::string> old_raw_data{ "first" },
      new_raw_data {
          "first", "second", "third", "fourth"
      };
  UsedMemory memory;
  memory.OnRawDataLoad(old_raw_data, new_raw_data);
  EXPECT_EQ(memory.get_used(), 45);
}

void prepare_stringstream(std::stringstream& ss, size_t lines = 20){
  for (size_t i = 0; i < lines; ++i) {
    ss << "abs" << '\n';
  }
}

TEST(PageContainer_Test, Data_Test) {
  std::stringstream ss{};
  prepare_stringstream(ss);

  PageContainer page;
  page.Load(ss, 0.0);
  EXPECT_EQ(page.DataSize(), 0);
}

void prepare_stringstream1(std::stringstream& ss, size_t lines = 20){
  for (size_t i = 0; i < lines; ++i) {
    ss << (i + 1) << " cor " << (i < 6 ? 25 : 50) << '\n';
  }
  ss << 21 << " inc "
     << "ls" << '\n';
  ss << 22 << " inc "
     << "la" << '\n';
}

TEST(PageContainer_Test, AsyncSend_Test) {
  using ::testing::_;
  using ::testing::AtLeast;

  srand(time(nullptr));
  std::stringstream ss{};
  prepare_stringstream1(ss);

  UsedMemory* used = new UsedMemory();
  MockStatSender* sender = new MockStatSender();
  page_container<mock_stat_sender> page(used, sender);

  page.load_raw_data(ss);
  EXPECT_CALL(*sender, AsyncSend(_, std::string_view{"/items/loaded"}))
      .Times(2);
  EXPECT_CALL(*sender,
              async_send(_, std::string_view{"/items/skipped"}))
      .Times(12);
  page.load_data(0);
  page.load_data(30);
}

TEST(PageContainer_Test, AlreadySeen){
  std::stringstream ss{};
  prepare_stringstream(ss);
  ss << 20 << " cop " << 20 << '\n';

  page_container page{};
  page.load_raw_data(ss);
  EXPECT_THROW(page.load_data(0), std::runtime_error);
}

TEST(PageContainer_Test, EmptyFile){
  std::ifstream file_{"empty.txt"};
  std::ofstream empty{"empty.txt"};
  page_container page{};
  EXPECT_THROW(page.load_raw_data(file_), std::runtime_error);
  empty.close();
}
TEST(PageContainer_Test, CorruptedFile){
  std::ifstream file_;
  file_.close();
  page_container page{};
  EXPECT_THROW(page.load_raw_data(file_), std::runtime_error);
}

TEST(PageContainer_Test, TooSmallInputStream){
  std::stringstream ss{};
  prepare_stringstream(ss, 5);

  page_container page{};
  EXPECT_THROW(page.load_raw_data(ss), std::runtime_error);
}
TEST(PageContainer_Test, TooSmallInputStream_LoadData){
  std::stringstream ss{};
  prepare_stringstream(ss);

  page_container page{};
  page.load_raw_data(ss);
  EXPECT_THROW(page.load_data(1000),std::runtime_error);
}
