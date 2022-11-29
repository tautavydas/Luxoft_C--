#include "split.h"
#include <gtest/gtest.h>


TEST(split, hellp_world) {
    const char* input = "Hello, world!";
    char** output = nullptr;
    int output_length = 0;
    split(input, ',', &output, output_length);
    ASSERT_EQ(output_length, 2);
    ASSERT_STREQ(output[0], "Hello");
    ASSERT_STREQ(output[1], " world!");
    for (int i = 0; i < output_length; i++) {
        delete[] output[i];
    }
    delete[] output;
}

TEST(split, lorem_ipsum) {
    const char* input = "Lorem ipsum dolor sit amet";
    char** output = nullptr;
    int output_length = 0;
    split(input, ' ', &output, output_length);
    ASSERT_EQ(output_length, 5);
    ASSERT_STREQ(output[0], "Lorem");
    ASSERT_STREQ(output[1], "ipsum");
    ASSERT_STREQ(output[2], "dolor");
    ASSERT_STREQ(output[3], "sit");
    ASSERT_STREQ(output[4], "amet");
    for (int i = 0; i < output_length; i++) {
        delete[] output[i];
    }
    delete[] output;
}