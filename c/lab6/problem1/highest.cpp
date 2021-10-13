//
//  lab6.cpp
//  
//
//  Created by Serafima on 10/8/21.
//

#include <iostream>
using namespace std;

const int* highest(int val, const int* start, const int* finish) {
    
    if (start == finish) {
        return nullptr;
    }
    // Since we can subtract two pointers and get a number, we can compute the length.
    auto length = finish - start;
    
    // Base case: If the length of the array is 1, then the value we're looking for is either that value or not in the array.
    if (length == 1) {
        if (val == *start) {
            return start;
        } else {
            return nullptr;
        }
    }
    auto middle = length / 2;
    
    if (start[middle] > val) {
        // Pass a pointer to the value in the middle.
        return highest(val, start, &start[middle]);
    } else {
        // Call the function on the other part of the array.
        return highest(val, &start[middle], finish);
    }
}

int main()
{
    const int DATA_LEN = 6;
    const int data[DATA_LEN] = { 1, 3, 3, 5, 5, 5 };

    for (auto search : { 1, 2, 3, 4, 5, 6 }) {
        const auto where = highest(search, data, data + DATA_LEN);
        cout << "Index of elem: " << search << " is: ";
        if (where == nullptr) {
            cout << "not found!" << endl;
        } else {
            cout << (where-data) << endl;
        }

    }
    return 0;

}
