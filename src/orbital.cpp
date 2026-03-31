/*
 *
 * Author: Devin Grush
 * Purpose: This script aims to provide the examples of the algorithms and formulas that will be used to calculate the necessary parameters for 2-burn Hohmann Transfers about a central body.
 *
 */

#include <cmath>

#include "../include/orbital.h"

#define PI 3.14159265358979323846 

using namespace std;

// Vis-Viva function
double VisVivaVelocity(double G, double planetMass, double orbitalRadius)
{
    double orbitalVelocity = sqrt( (G * planetMass) / orbitalRadius );
    return orbitalVelocity;
}

// Semi-major axis from initial and final orbit
double SemiMajorAxis(double r_init, double r_final)
{
    double a = (r_init + r_final) / 2;
    return a;
}

// Velocity at periapsis of transfer orbit
double TransferPeriapsisVelocity(double G, double planetMass, double transferSemiMajorAxis, double r_init)
{
    double periapsisVelocity = sqrt( (G * planetMass) * ( (2 / r_init) - (1 / transferSemiMajorAxis) ));
    return periapsisVelocity;
}

// Hohmann burn 1 delta-V (departure/initial burn)
double Burn1DeltaV(double initOrbitalVelocity, double periapsisVelocity)
{
    double deltaV1 = abs(periapsisVelocity - initOrbitalVelocity);
    return deltaV1;
}

// Velocity at apoapsis of transfer orbit 
double TransferApoapsisVelocity(double G, double planetMass, double transferSemiMajorAxis, double r_final)
{
    double apoapsisVelocity = sqrt( (G * planetMass) * ( (2 / r_final) - (1 / transferSemiMajorAxis) ));
    return apoapsisVelocity;
}

// Velocity on target circular orbit
double TargetVelocity(double G, double planetMass, double r_final)
{
    double targetVelo = sqrt( (G * planetMass) / r_final );
    return targetVelo;
}

// Hohmann burn 2 delta-v (arrival/insertion burn)
double Burn2DeltaV(double targetVelo, double transferApoapsisVelo)
{
    double deltaV2 = abs(targetVelo - transferApoapsisVelo);
    return deltaV2;
}

// Total delta-v for the manuver incl. intial/departure burn and arrival burn
double TotalDeltaV(double burn1DeltaV, double burn2DeltaV)
{
    double deltaVTotal = burn1DeltaV + burn2DeltaV;
    return deltaVTotal;
}

// Transfer time
double TransferTime(double semiMajorAxis, double G, double planetMass)
{
    double time = PI * sqrt( (pow(semiMajorAxis, 3)) / (G * planetMass) );
    return time;
}

