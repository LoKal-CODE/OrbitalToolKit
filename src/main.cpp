#include <iostream>
#include <string>

#include "orbital.h"

using namespace std;


int main(int argc, char* argv[])
{
    
    int userDecision;
    // Determine user desired operation
    cout << "Please choose a calculation to perform: (1) xxx (2) xxx (3) xxx (4) xxx\n";
    cin >> userDecision;

    switch (userDecision) {
    
        case 1:
            // do the thing
            break;
        
        case 2:
            // do another thing
            break;

        case 3:
            // do in
            break;

        case 4:
            // sfsdfsdfsdfsdf
            break;

        default:
            cout << "ERROR. Please enter a valid input!\n";
            break;

    }

    return 0;

}
