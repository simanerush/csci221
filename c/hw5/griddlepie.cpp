//
//  griddlepie.cpp
//  
//
//  Created by Serafima Nerush on 10/10/21.
//

#include <iostream>
#include <cmath>

using namespace std;


double gridpi(unsigned npoints) {
    // a counter of all points inside the circle
    auto in_circle = 0u;
    
    // loop through all possible points in n \times n square
    for (auto i = 0u; i < npoints; i++) {
        // calculate the x coordinate
        auto x = double(i) / double(npoints - 1);
        for (auto j = 0.0; j < npoints; j++) {
            // calculate the y coordinate
            auto y = double(j) / double(npoints - 1);
            
            // check is the point is inside the circle
            if (hypot(x,y) <= 1.0) {
                
                // increase the counter
                in_circle++;
            }
        }
    }
    
    // return the pi, according to the provided formula
    return double(in_circle) / double(npoints * npoints) * 4.0;
}

// constexpr version of gridpi
constexpr double gridpi2(unsigned npoints) {
    auto in_circle = 0u;
    
    for (auto i = 0u; i < npoints; i++) {
        auto x = double(i) / double(npoints - 1);
        for (auto j = 0.0; j < npoints; j++) {
            auto y = double(j) / double(npoints - 1);
            // NOTE: hypot is not a constexpr, but it does compile on gcc. There is no way to create a constexpr from this function, because sqrt() is also not a constexpr.
            if (x*x + y*y <= 1.0) {
                in_circle++;
            }
        }
    }
    return double(in_circle) / double(npoints * npoints) * 4.0;
}

int main() {
    cout << "10: " << gridpi2(10) << endl;
    cout << "100: " << gridpi2(100) << endl;
    cout << "1000: " << gridpi2(1000) << endl;
    return 0;
}
