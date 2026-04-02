#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

#include "../include/orbital.h"

#define DATA_ELEMENTS_LEN 6  // spacecraftName, mass, orbitalRadius, orbitingBody, eccentricity, inclination

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

        // Constructor argument order: name, eqRadius, mass, meRadius, rotPeriod, orbPeriod, escVelocity, G
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
    name             = planetName;
    mass             = planetMass;
    equitorialRadius = eqRadius;
    meanRadius       = meRadius;
    rotationalPeriod = rotPeriod;
    orbitalPeriod    = orbPeriod;
    escapeVelocity   = escVelocity;
    this->G          = G;
}

int split(string s, char sep, string words[], int max_words) { // split function written by Claude, meant to mimic the functionality of the split function provided in the recitation assignments
    int count = 0;
    string current = "";
    for (int i = 0; i < (int)s.length(); i++) {
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

    // Earth: mass = 5.97e24 kg, equatorial radius = 6.378e6 m, mean radius = 6.371e6 m
    // rotational period = 0.997 days, orbital period = 365.0 days,
    // escape velocity = 11.2 km/s, G = 6.67e-11 N m^2 kg^-2
    Planet Earth("Earth", 5.97e24, 6.378e6, 6.371e6, 0.997, 365.0, 11.2, 6.67e-11);

    // for the switch-case statement that decides whether to proceed with the Hohmann calculation or exit
    int userDecision;

    // variables that deal with taking in and parsing user data from a CSV or TXT file
    string userFile;
    ifstream userDataFile;
    string line;
    char userDelimiter; // lets user define the delimiter used in their data file

    // variables that deal with the elements of the data file
    string spacecraftName;
    double spacecraftMass       = 0.0;
    double currOrbitalRadius_km = 0.0;
    string currentOrbitingBody;
    double currOrbitEccentricity = 0.0;
    double currOrbitInclination  = 0.0;

    // Determine user desired operation
    cout << "Please choose a calculation to perform: (1) 2-Burn Hohmann Transfer (2) Exit Program\n";
    cin >> userDecision;

    switch (userDecision) {

        case 1: {

            // Take in user file
            cout << "Please enter the name of the data file that you wish to use (.csv or .txt only)\n";
            cin >> userFile;

            // Assign userDelimiter
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

                if (count == DATA_ELEMENTS_LEN) {

                    spacecraftName        = elements[0];
                    spacecraftMass        = stod(elements[1]);
                    currOrbitalRadius_km  = stod(elements[2]);
                    currentOrbitingBody   = elements[3];
                    currOrbitEccentricity = stod(elements[4]);
                    currOrbitInclination  = stod(elements[5]);

                }

            }

            userDataFile.close();

            // Convert orbital radius from km to meters for SI calculations
            double r_init_m = currOrbitalRadius_km * 1000.0;

            // Prompt user for target orbital radius
            double targetOrbitalRadius_km;
            cout << "Please enter the target orbital radius in km (measured from Earth's center): ";
            cin >> targetOrbitalRadius_km;
            double r_final_m = targetOrbitalRadius_km * 1000.0;

            double earthG    = Earth.getG();
            double earthMass = Earth.getMass();

            // --- Hohmann Transfer Calculations ---

            // Step 1: Current circular orbit velocity (vis-viva at r_init)
            double initOrbitalVelocity = VisVivaVelocity(earthG, earthMass, r_init_m);

            // Step 2: Semi-major axis of the transfer ellipse
            double transferSMA = SemiMajorAxis(r_init_m, r_final_m);

            // Step 3: Velocity at periapsis of transfer orbit (departure point)
            double periapsisVelocity = TransferPeriapsisVelocity(earthG, earthMass, transferSMA, r_init_m);

            // Step 4: First burn delta-V (kick into transfer orbit)
            double deltaV1 = Burn1DeltaV(initOrbitalVelocity, periapsisVelocity);

            // Step 5: Velocity at apoapsis of transfer orbit (arrival point)
            double apoapsisVelocity = TransferApoapsisVelocity(earthG, earthMass, transferSMA, r_final_m);

            // Step 6: Target circular orbit velocity (vis-viva at r_final)
            double targetVelocity = TargetVelocity(earthG, earthMass, r_final_m);

            // Step 7: Second burn delta-V (circularize at target orbit)
            double deltaV2 = Burn2DeltaV(targetVelocity, apoapsisVelocity);

            // Step 8: Total delta-V for the maneuver
            double totalDeltaV = TotalDeltaV(deltaV1, deltaV2);

            // Step 9: Transfer time (half the period of the transfer ellipse)
            double transferTime_s = TransferTime(transferSMA, earthG, earthMass);
            double transferTime_min = transferTime_s / 60.0;
            double transferTime_hr  = transferTime_s / 3600.0;

            // --- Output Results ---
            cout << "\n========== Hohmann Transfer Results for " << spacecraftName << " ==========\n";
            cout << fixed << setprecision(4);
            cout << "Spacecraft mass           : " << spacecraftMass        << " kg\n";
            cout << "Orbiting body             : " << currentOrbitingBody   << "\n";
            cout << "Initial orbit eccentricity: " << currOrbitEccentricity << "\n";
            cout << "Initial orbit inclination : " << currOrbitInclination  << " deg\n";
            cout << "\n--- Orbital Radii ---\n";
            cout << "Initial orbital radius    : " << currOrbitalRadius_km  << " km  ("
                 << r_init_m << " m)\n";
            cout << "Target orbital radius     : " << targetOrbitalRadius_km << " km  ("
                 << r_final_m << " m)\n";
            cout << "\n--- Transfer Orbit ---\n";
            cout << "Transfer semi-major axis  : " << transferSMA / 1000.0  << " km\n";
            cout << "\n--- Velocities (m/s) ---\n";
            cout << "Initial circular velocity : " << initOrbitalVelocity   << " m/s\n";
            cout << "Transfer periapsis vel.   : " << periapsisVelocity     << " m/s\n";
            cout << "Transfer apoapsis vel.    : " << apoapsisVelocity      << " m/s\n";
            cout << "Target circular velocity  : " << targetVelocity        << " m/s\n";
            cout << "\n--- Delta-V Budget ---\n";
            cout << "Burn 1 (departure) dV     : " << deltaV1               << " m/s\n";
            cout << "Burn 2 (insertion) dV     : " << deltaV2               << " m/s\n";
            cout << "Total delta-V             : " << totalDeltaV           << " m/s\n";
            cout << "\n--- Transfer Time ---\n";
            cout << "Transfer time             : " << transferTime_s        << " s\n";
            cout << "                          : " << transferTime_min      << " min\n";
            cout << "                          : " << transferTime_hr       << " hr\n";
            cout << "=====================================================\n";

            break;
        }

        case 2:
            cout << "Thank you for using OrbitalToolKit, goodbye!\n";
            return 0;

        default:
            cout << "ERROR. Please enter a valid input of 1 or 2!\n";
            return -1;
    }

    return 0;

}
