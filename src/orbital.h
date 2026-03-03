#ifndef ORBITAL_H

#define ORBITAL_H

// Function declarations
double VisVivaVelocity(double G, double planetMass, double orbitalRadius);

double SemiMajorAxis(double r_init, double r_final);

double TransferPeriapsisVelocity(double G, double planetMass, double transferSemiMajorAxis, double r_init);

double Burn1DeltaV(double initOrbitalVelocity, double periapsisVelocity);

double TransferApoapsisVelocity(double G, double planetMass, double transferSemiMajorAxis, double r_final);

double TargetVelocity(double G, double planetMass, double r_final);

double Burn2DeltaV(double targetVelo, double transferApoapsisVelo);

double TotalDeltaV(double burn1Delta, double burn2Delta);

double TransferTime(double semiMajorAxis, double G, double planetMass);

#endif
