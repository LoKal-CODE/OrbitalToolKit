#include <iostream>
#include <string>
#include <fstream>

#include "../include/orbital.h"

using namespace std;


int main(int argc, char* argv[])
{
    
    int userDecision;
    string userFile;
    ifstream userDataFile;
    // Determine user desired operation
    cout << "Please choose a calculation to perform: (1) 2-Burn Hohmann Transfer (2) Exit Program \n";
    cin >> userDecision;

    switch (userDecision) {
    
        case 1:

            // take in user file to store in userDataFile
             
            
            break;
        
        case 2:
            cout << "Thank you for using OrbitalToolKit, goodbye!\n";
            return 0;
            break;

        default:
            cout << "ERROR. Please enter a valid input!\n";
            break;

    }

    return 0;

}
