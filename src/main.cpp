#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

#include "../include/orbital.h"

#define DATA_ELEMENTS_LEN 7

using namespace std;

class Planet
{

    private:
        string name;
        double mass;
        double equitorialRadius;
        double meanRadius;
        double rotationalPeriod;
        double orbitalPeriod;
        double escapeVelocity;
        double G;

    public:

        Planet(string planetName, double planetMass, double eqRadius,
               double meRadius, double rotPeriod, double orbPeriod, double escVelocity, double G);

        // Getters (const because they don't modify the object)
        string getName() const { return name; }
        double getMass() const { return mass; }
        double getEquitorialRadius() const { return equitorialRadius; }
        double getMeanRadius() const { return meanRadius; }
        double getRotationalPeriod() const { return rotationalPeriod; }
        double getOrbitalPeriod() const { return orbitalPeriod; }
        double getEscapeVelocity() const { return escapeVelocity; }
        double getG() const { return G; }

};

Planet::Planet(string planetName, double planetMass, double eqRadius,
               double meRadius, double rotPeriod, double orbPeriod,
               double escVelocity, double G)
{
    name            = planetName;
    mass            = planetMass;
    equitorialRadius = eqRadius;
    meanRadius      = meRadius;
    rotationalPeriod = rotPeriod;
    orbitalPeriod   = orbPeriod;
    escapeVelocity  = escVelocity;
    this->G         = G;
}

int split(string s, char sep, string words[], int max_words) { // split function written by Claude, meant to mimic the functionality of the split function provided in the recitation assignments
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

    // Create the Earth object
    Planet Earth("Earth", 6371.0, 5.97e24, 6.37e6, 0.997, 365.0, 11.2, 6.67e-11);

    // for the switch-case statment that decides whether to proceed with the Hohmann calculation or exit the program
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

            currOrbitalRadius_km = 7045.55;

            double earthG = Earth.getG();
            double earthMass = Earth.getMass();
            
            double vvVelo = VisVivaVelocity(earthG, earthMass, currOrbitalRadius_km); // this is giving me some issue, diagnose beofre cont.
            cout << "You current orbital velocity is " << fixed << setprecision(4) << vvVelo << " km/s.\n";

            double semiMajorAxis = SemiMajorAxis(6778.0, 6778.0);
            cout << "Your semi major axis is " << semiMajorAxis << endl;

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
