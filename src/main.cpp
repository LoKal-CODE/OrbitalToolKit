#include <iostream>
#include <string>
#include <fstream>

#include "../include/orbital.h"
#include "../include/planet.h"

#define DATA_ELEMENTS_LEN 7

using namespace std;

Planet CreatePlanet(string planetName, double planetMass, double eqRadius, double meRadius, double rotPeriod, double orbPeriod, double escapeVelocity)
{
    


}

int split(string s, char sep, string words[], int max_words) {
    int count = 0;
    string current = "";
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == sep) {
            if (count < max_words) {
                words[count++] = current;
                current = "";
            }
        } else {
            current += s[i];
        }
    }
    if (current != "" && count < max_words) {
        words[count++] = current;
    }
    return count;
}

int main(int argc, char* argv[])
{

    int userDecision;

    // variables that deal with taking in and parsing user data from a CSV or TXT file
    string userFile;
    ifstream userDataFile;
    string line;
    char userDelimiter; // lets user define the delimiter used in their data file

    // variables that deal with the elements of the data file
    string spacecraftName;
    double spacecraftMass;
    double currOrbitalRadius_km;
    string currentOrbitingBody;
    double currOrbitEccentricity;
    double currOrbitInclination;

    // Determine user desired operation
    cout << "Please choose a calculation to perform: (1) 2-Burn Hohmann Transfer (2) Exit Program \n";
    cin >> userDecision;

    switch (userDecision) {
    
        case 1: {

            // take in user file to store in userDataFile
            cout << "Please enter the name of the data file that you wish to use (.csv or .txt only)\n";
            cin >> userFile;

            // assign userDelimiter
            cout << "Please enter the delimiter used in your data file.\n";
            cin >> userDelimiter;

            userDataFile.open(userFile);

            if (userDataFile.fail()) {
                cout << "ERROR: Could not open specified file. Please check input and start program again.\n";
                return -1;
            }             

            while (getline(userDataFile, line)) {

                if (line.empty()) {
                    continue; 
                }

                string elements[DATA_ELEMENTS_LEN];
                int count = split(line, userDelimiter, elements, DATA_ELEMENTS_LEN);

                if (count == DATA_ELEMENTS_LEN - 1) {
                
                    spacecraftName = elements[0];
                    spacecraftMass = stod(elements[1]);
                    currOrbitalRadius_km = stod(elements[2]);
                    currentOrbitingBody = elements[3];
                    currOrbitEccentricity = stod(elements[4]); 
                    currOrbitInclination = stod(elements[5]);

                }
                 
            }

            userDataFile.close();

            // now that all necessary user data has been read in, being to gather the necessary class object data for the planet that is being analyzed 



        }
            
            break;
        
        case 2:
            cout << "Thank you for using OrbitalToolKit, goodbye!\n";
            return 0;
            break;

        default:
            cout << "ERROR. Please enter a valid input of 1 or 2!\n";
            return -1;
            break;

    }

    return 0;

}
