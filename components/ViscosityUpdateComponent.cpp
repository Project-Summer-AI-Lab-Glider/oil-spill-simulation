//
// Created by Mateusz Święszek on 09/09/2020.
//

#include "ViscosityUpdateComponent.h"
#include <cmath>

ViscosityUpdateComponent::ViscosityUpdateComponent(Configurations& config): config(config) {}

void ViscosityUpdateComponent::update(Cell& cell, OilPoint& op,
                                      const int &timestep) {
    double actualVis = op.viscosity;
    double deltaVis = config.viscosityParameter * actualVis * op.lastDeltaF +
                      2.5 * actualVis * op.lastDeltaY /
                      std::pow(1 + config.mousseViscosity * op.getEmulsification(), 2);
    op.viscosity = actualVis + deltaVis;
}
