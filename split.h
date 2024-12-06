#include "Player.h"
#ifndef SPLIT_H
#define SPLIT_H

int split(std::string input_string, char separator, std::string arr[], const int ARR_SIZE) {
    int splitIndex = 0;
    int arrayCount = 0;
    int length = input_string.length();
    int currentSize = 1;

    if (input_string == "") {
        return 0;
    } else {
        for (int i = 1; i <= length; i++) {
            currentSize++;
            if (input_string[i] == separator || i == length) {
                arr[arrayCount] = input_string.substr(splitIndex, currentSize - 1);
                arrayCount++;
                if (arrayCount == ARR_SIZE && i < length) {
                    return -1; // this is for if u exceed the array size
                }
                splitIndex = i + 1;
                currentSize = 0;
            }
        }
        return arrayCount;
    }
}

#endif
