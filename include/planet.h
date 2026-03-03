#ifndef PLANET_H
#define PLANET_H

#include <string>

class Planet {
    private:
        std::string name;
        double mass;
        double equitorialRadius;
        double meanRadius;
        double rotationalPeriod;
        double orbitalPeriod;
        double escapeVelocity;

    public:
        Planet(std::string planetName, double planetMass, double eqRadius,
               double meRadius, double rotPeriod, double orbPeriod, double escVelocity);

        // Getters (const because they don't modify the object)
        std::string getName() const { return name; }
        double getMass() const { return mass; }
        double getEquitorialRadius() const { return equitorialRadius; }
        double getMeanRadius() const { return meanRadius; }
        double getRotationalPeriod() const { return rotationalPeriod; }
        double getOrbitalPeriod() const { return orbitalPeriod; }
        double getEscapeVelocity() const { return escapeVelocity; }
};

#endif

