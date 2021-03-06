// Copyright (c) 2015 Nuxi, https://nuxi.nl/
//
// SPDX-License-Identifier: BSD-2-Clause

#define _CLOUDLIBC_UNSAFE_STRING_FUNCTIONS

#include <string.h>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

TEST(stpcpy, example) {
  char buf[] = "AAAAAAAAAA";
  ASSERT_EQ(buf, stpcpy(buf, ""));
  ASSERT_THAT(buf, testing::ElementsAreArray("\0AAAAAAAAA"));
  ASSERT_EQ(buf + 5, stpcpy(buf, "Hello"));
  ASSERT_THAT(buf, testing::ElementsAreArray("Hello\0AAAA"));
  ASSERT_EQ(buf, stpcpy(buf, ""));
  ASSERT_THAT(buf, testing::ElementsAreArray("\0ello\0AAAA"));
  ASSERT_EQ(buf + 9, stpcpy(buf, "Example!!"));
  ASSERT_THAT(buf, testing::ElementsAreArray("Example!!\0"));
}
