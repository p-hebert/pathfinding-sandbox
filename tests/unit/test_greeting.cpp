#include "app.hpp"
#include <gtest/gtest.h>

TEST(GreetingTest, ReturnsBanner)
{
    EXPECT_EQ(greeting(), "Hello World!");
}