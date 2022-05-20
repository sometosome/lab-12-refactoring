// Copyright 2021 Your Name <your_email>

#include <stdexcept>
#include <thread>

#include <gtest/gtest.h>

#include <example.hpp>

TEST(Example, EmptyTest) {
    EXPECT_NO_THROW(Log{1});
}

TEST(DISABLED_Snapshot, Speen) {
  for (;;) std::this_thread::yield();
}
