#include <iostream>
#include <cstring>
#include "split.h"

void split(const char* input, char delimeter, char*** output, int& output_length) {
    // Step1 ; calculate amount of delimeters - setup output length, allocate memory for output
    // Step2 find next delimeter or EOS
    //       allocate memory in output[i]
    //       copy string from current position to next delimeter or EOS input output[i]
    // Step3 iterate unless end of string

    size_t const total_length{strlen(input)};

    // Step1
    size_t delim_counter{0};
    for(size_t i{0}; i  <total_length; ++i) {
        if(input[i] == delimeter || input[i] == '\0') {
            ++delim_counter;
        }
    }

    // Step2
    output_length=delim_counter+1;
    size_t indices[output_length]{0}, lengths[output_length];
    delim_counter = 0;
    for(size_t i{0}; i<total_length; ++i) {
        if(input[i] == delimeter || input[i] == '\0') {
            lengths[delim_counter]=i-indices[delim_counter];
            indices[++delim_counter]=++i;
        }
    }
    lengths[delim_counter]=total_length-indices[delim_counter];

    // Step3
    *output = new char*[output_length];
    for(size_t i{0}; i < output_length; ++i) {
        (*output)[i] = new char[lengths[i] + 1];
        strncpy((*output)[i], &input[indices[i]], lengths[i]);
        (*output)[i][lengths[i]] = '\0';
    }
}
