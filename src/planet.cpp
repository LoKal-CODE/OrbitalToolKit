// Planet.cpp
#include "../include/planet.h"

Planet::Planet(std::string planetName, double planetMass, double eqRadius,
               double meRadius, double rotPeriod, double orbPeriod, double escVelocity) 
    : name(planetName), mass(planetMass), equitorialRadius(eqRadius),
      meanRadius(meRadius), rotationalPeriod(rotPeriod),
      orbitalPeriod(orbPeriod), escapeVelocity(escVelocity) {}
