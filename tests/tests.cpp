// Copyright 2021 Your Name <your_email>

#include <gmock/gmock.h>
#include <gtest/gtest.h>
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
    ss << "abs" << (i+1) << "\n" << (i+1) << " req " << (i+1) << "\n";
  }
}
TEST(PageContainer_Test, Data_Test) {
  std::stringstream ss{};
  prepare_stringstream(ss);

  PageContainer page;
  page.Load(ss, 0.0);
  EXPECT_EQ(page.DataSize(), 20);
}


//void prepare_stringstream1(std::stringstream& ss, size_t lines = 20){
//  for (size_t i = 0; i < lines; ++i) {
//    ss << (i + 1) << " cor " << (i < 6 ? 25 : 50) << '\n';
//  }
//  ss << 21 << " inc "
//     << "ls" << '\n';
//  ss << 22 << " inc "
//     << "la" << '\n';
//}

TEST(PageContainer_Test, AsyncSend_Test) {
  using ::testing::_;
  using ::testing::AtLeast;

  srand(time(nullptr));
  std::stringstream ss{};
  prepare_stringstream(ss);
  UsedMemory* used = new UsedMemory();
  MockStatSender* sender = new MockStatSender();
  PageContainer page(sender, used);
  EXPECT_CALL(*sender, AsyncSend(_, _))
      .Times(21);
  page.Load(ss, 0.0);
  delete sender;
  delete used;
}

TEST(PageContainer_Test, AlreadySeen){
  std::stringstream ss{};
  prepare_stringstream(ss);
  ss << 20 << " cop " << 20 << '\n';

  PageContainer page;
  EXPECT_THROW(page.Load(ss, 0.0), std::runtime_error);
}

TEST(PageContainer_Test, EmptyFile){
  std::ifstream file_{"empty.txt"};
  std::ofstream empty{"empty.txt"};
  PageContainer page{};
  EXPECT_THROW(page.Load(file_, 0.0), std::runtime_error);
  empty.close();
}
TEST(PageContainer_Test, CorruptedFile){
  std::ifstream file_;
  file_.close();

  PageContainer page{};
  EXPECT_THROW(page.Load(file_, 0.0), std::runtime_error);
}

TEST(PageContainer_Test, TooSmallInputStream){
  std::stringstream ss{};
  prepare_stringstream(ss, 5);

  PageContainer page{};
  EXPECT_THROW(page.Load(ss, 0.0), std::runtime_error);
}
TEST(PageContainer_Test, TooSmallInputStream_LoadData){
  std::stringstream ss{};
  prepare_stringstream(ss);

  PageContainer page{};
  EXPECT_THROW(page.Load(ss, 1000),std::runtime_error);
}
