/*********************************************************************
*  world.cpp
*
*  World is a container for all of the actors in a simulation, responsible
*    for timesteps and calculating global rewards.

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

#include "world.h"

std::vector<double> World::getAgentRewards() {
  std::vector<double> rewards;

  double globalReward = this->calculateG();
  
  for (const auto& actor: this->actors) {
    if (actor->isAgent()) {
      rewards.push_back(actor->determineReward(this->visibleFrom(actor), globalReward));
    }
  }

  return rewards;
}

void World::timestep() {

  for (auto& actor: this->actors) {
    Location init = actor->getLocation();
    actor->move(this->visibleFrom(actor));
    if (this->hasBounds && !this->inBounds(actor)) {
      actor->setLocation(init);
    }
  }

  double globalReward = this->calculateG();
  
  for (auto& actor: this->actors) {
    actor->receiveBroadcastG(globalReward);
  }
}

World::World(std::vector<Actor*> actors) {
  this->actors = actors;
  this->hasBounds = false;
}

std::vector<Actor*>& World::getActors() {
  return this->actors;
}

double World::calculateG() {
  return this->calculateG(this->getActors());
}
