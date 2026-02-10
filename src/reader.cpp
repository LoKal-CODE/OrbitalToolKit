/*
 *  Credit Jalynn Nicoly, CU Boulder, for the example file reading code
 *  GitHub Link: https://github.com/Jalynnn/CSCI1300_SP26/blob/main/Week4/Checkpoint2/FileInputOutputExample.cpp
 */

#include <iostream>

// For file input/output
#include <fstream>

using namespace std;

int main() {
    // Create an input file stream
    ifstream inFile;

    // Open your file
    inFile.open("planetdata_reformatted.csv"); // change this to the name of the .csv file to be read

    // Check if the file opened successfully
    // If an error is printed - make sure you file is in the same file location
    if (!inFile.is_open()) {
        cout << "Error opening file!" << endl;
        return 1; // True
    }

    // Read and display each line in the file
    string line;
    while(getline(inFile, line)) { // getline(cin, line)
        // Delimiters: Not relevant to everyone's data
        cout << line << endl;
    }

    inFile.close();

    return 0; // False
}
