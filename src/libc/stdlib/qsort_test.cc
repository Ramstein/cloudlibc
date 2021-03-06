// Copyright (c) 2015 Nuxi, https://nuxi.nl/
//
// SPDX-License-Identifier: BSD-2-Clause

#include <stdint.h>
#include <stdlib.h>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

static int compare_uint32(const void *a, const void *b) {
  if (*(uint32_t *)a < *(uint32_t *)b)
    return -1;
  if (*(uint32_t *)a > *(uint32_t *)b)
    return 1;
  return 0;
}

TEST(qsort, example) {
  // Sort an example dataset.
  uint32_t input[100] = {
      0x125aa004, 0x6a366171, 0x8910ab73, 0x87aa8e00, 0xa7d1d701, 0x4f16f856,
      0xd81691a2, 0x617c4d0f, 0xf3706fb4, 0x2e817498, 0xe6437087, 0x57a8e6d8,
      0x2865ffa2, 0xac77426d, 0x981f32c9, 0x0dd3aed5, 0x36529288, 0xde0ad5d5,
      0xfdbdac63, 0xe45814ac, 0xe11827cd, 0x6c4518f0, 0x0b8c4287, 0x661ed74a,
      0xfb069a52, 0x1813dfd1, 0x68dfb692, 0xdd15518e, 0xa618025d, 0xc6a71fc1,
      0x5d22a254, 0x974e0c15, 0xa14fb4c0, 0x5d9623c3, 0x45f78eea, 0x5af342b0,
      0xe112e4cc, 0xead1adca, 0x4e83c0aa, 0x2a687581, 0xf2d30c8a, 0x3bec4ece,
      0x3cf25f27, 0x770c63ed, 0xd9dfa913, 0x2498fd54, 0x41d44f7f, 0x95d5d188,
      0x88a624e7, 0x594fd520, 0xa38fc8a3, 0x82f06732, 0xc8b85da4, 0x5d92acef,
      0x05d95fbf, 0xcb18850a, 0xa4baf2b7, 0x891617c1, 0xe7bcd2f7, 0x916ec264,
      0xf2fee0dd, 0x0e93db5b, 0xd62f0803, 0x8ea4bfe6, 0x4994670f, 0x457f7eed,
      0x3da4920c, 0xc075ece6, 0x2b41b0e8, 0x9c217654, 0xf8f79dae, 0xb193f044,
      0x98805700, 0xbf95e340, 0x845dc034, 0x86c52f67, 0x193f575d, 0xd4d28c25,
      0x2132ccf9, 0x20825bf8, 0x27b515b6, 0x3d1bf61a, 0xdd100644, 0x661f0546,
      0xb5e81966, 0x0bfc4974, 0x7c3f232b, 0x95f8f870, 0x3ebaed5a, 0xe679fbc6,
      0x3553fb8f, 0xc2dac073, 0x2c698e2e, 0x585bf5b1, 0x3205a3d1, 0x17894379,
      0xb030abca, 0x51e50386, 0xa63132b8, 0x11ce3177,
  };
  const uint32_t expected_output[100] = {
      0x05d95fbf, 0x0b8c4287, 0x0bfc4974, 0x0dd3aed5, 0x0e93db5b, 0x11ce3177,
      0x125aa004, 0x17894379, 0x1813dfd1, 0x193f575d, 0x20825bf8, 0x2132ccf9,
      0x2498fd54, 0x27b515b6, 0x2865ffa2, 0x2a687581, 0x2b41b0e8, 0x2c698e2e,
      0x2e817498, 0x3205a3d1, 0x3553fb8f, 0x36529288, 0x3bec4ece, 0x3cf25f27,
      0x3d1bf61a, 0x3da4920c, 0x3ebaed5a, 0x41d44f7f, 0x457f7eed, 0x45f78eea,
      0x4994670f, 0x4e83c0aa, 0x4f16f856, 0x51e50386, 0x57a8e6d8, 0x585bf5b1,
      0x594fd520, 0x5af342b0, 0x5d22a254, 0x5d92acef, 0x5d9623c3, 0x617c4d0f,
      0x661ed74a, 0x661f0546, 0x68dfb692, 0x6a366171, 0x6c4518f0, 0x770c63ed,
      0x7c3f232b, 0x82f06732, 0x845dc034, 0x86c52f67, 0x87aa8e00, 0x88a624e7,
      0x8910ab73, 0x891617c1, 0x8ea4bfe6, 0x916ec264, 0x95d5d188, 0x95f8f870,
      0x974e0c15, 0x981f32c9, 0x98805700, 0x9c217654, 0xa14fb4c0, 0xa38fc8a3,
      0xa4baf2b7, 0xa618025d, 0xa63132b8, 0xa7d1d701, 0xac77426d, 0xb030abca,
      0xb193f044, 0xb5e81966, 0xbf95e340, 0xc075ece6, 0xc2dac073, 0xc6a71fc1,
      0xc8b85da4, 0xcb18850a, 0xd4d28c25, 0xd62f0803, 0xd81691a2, 0xd9dfa913,
      0xdd100644, 0xdd15518e, 0xde0ad5d5, 0xe112e4cc, 0xe11827cd, 0xe45814ac,
      0xe6437087, 0xe679fbc6, 0xe7bcd2f7, 0xead1adca, 0xf2d30c8a, 0xf2fee0dd,
      0xf3706fb4, 0xf8f79dae, 0xfb069a52, 0xfdbdac63,
  };
  qsort(input, 100, sizeof(uint32_t), compare_uint32);
  ASSERT_THAT(input, testing::ElementsAreArray(expected_output));
}

TEST(qsort, empty) {
  // Both the list and the compare function should not be accessed.
  qsort_r(NULL, 0, 123, NULL, NULL);
}
