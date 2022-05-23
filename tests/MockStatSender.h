//
// Created by farewelly on 22.05.2022.
//

#ifndef LAB_12_REFACTORING_MOCKSTATSENDER_H
#define LAB_12_REFACTORING_MOCKSTATSENDER_H

#include <gmock/gmock.h>
#include <StatSender.hpp>


class MockStatSender : public StatSender {
 public:
  MOCK_METHOD(void, AsyncSend, (const std::vector<Item>&, const std::string_view&), (override));
};

#endif  // LAB_12_REFACTORING_MOCKSTATSENDER_H
