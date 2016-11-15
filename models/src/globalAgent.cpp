/*********************************************************************
*  globalAgent.cpp
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

#include "globalAgent.h"
#include <iostream>

GlobalAgent::GlobalAgent() : Agent() {

}

GlobalAgent::GlobalAgent(Location loc) : Agent(loc) {

}

GlobalAgent::GlobalAgent(Location loc, World* world) : Agent(loc) {
  this->w = world;
}

void GlobalAgent::setWorld(World* world) {
  this->w = world;
}

World* GlobalAgent::getWorld() {
  return this->w;
}

double GlobalAgent::determineReward(std::vector<Actor*>& actors, double g) {
  std::vector<Actor*> others;

  for (const auto actor : actors) {
    if (actor != this) {
      others.push_back(actor);
    }
  }

  double counterfactual = this->getWorld()->calculateG(others);
  return g - counterfactual;
}


