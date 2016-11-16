/*********************************************************************
*  simulation.cpp
*
*  Container for actors and world. Runs simulation for a certain number of timesteps
*   and is able to preserve actor and world state across simulation runs.
*
*  A network evaluator uses a simulation.
*
*  Copyright (C) 2016 Eric Klinkhammer
*
*  This program is free software: you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation, either version 3 of the License, or
*  (at your option) any later version.
*
*  This program is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*********************************************************************/

#include "simulation.h"
#include <iostream>

Simulation::Simulation(SimulationConfig config) {
  this->init(config);
}

void Simulation::init(SimulationConfig config) {
  this->world = config.w;
  this->timesteps = config.timesteps;

  for (auto i: config.actors) {
    this->actors.push_back(i);
  }
}

void Simulation::run() {

  // randomize starting locations
  // TODO - World may in the future have non-point actors. How to handle without
  // needing to know. Possibly in setLocation? Alternatively, obstacles are set across
  // simulated runs? So, same world?

  for (auto actor : this->actors) {
    Location random = this->world->randomLocation();
    actor->setLocation(random);
  }

  // run simulation
  for (int i = 0; i < this->timesteps; i++) {
    this->world->timestep();
  }

  // Store G data for run
  double g = this->world->calculateG();
  this->gValues.push_back(g);
}

void Simulation::assignPolicies(std::vector<FANN::neural_net*> nets) {
  int net = 0;
  for (auto actor : this->getActors()) {
    if (actor->isAgent()) {
      actor->setPolicy(nets[net]);
      net++;
    }
  }
}

std::vector<double> Simulation::getRewards() {
  return this->world->getAgentRewards();
}

std::vector<double> Simulation::getG() {
  return this->gValues;
}

std::vector<Actor*> Simulation::getActors() {
  return this->actors;
}
