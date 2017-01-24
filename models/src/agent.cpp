/*********************************************************************
*  agent.cpp
*
* Agent moves in the world according to a policy. Agent is a wrapper for
*   agents with and without global knowledge.
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

#include "agent.h"
#include <iostream>

Agent::Agent() : Actor() {

}

Agent::Agent(Location loc) : Actor(loc) {

}

void Agent::move(std::vector<Actor*>& actors) {
  std::vector<float> state = this->createState(actors);
  std::vector<float> output = this->getPolicy()->run(state);
  float x = output[0], y = output[1];

  // Neural network will always output a positive value between 0 and 1

  // Scale so that all values between -1 and 1 are possible
  x = 2 * x - 1;
  y = 2 * y - 1;
  
  Location current = this->getLocation();
  Location move = Location::createLoc(x, y);
  this->setLastCommand(move);
  this->setLocation(Location::addLocations(current, move));
}

double Agent::determineReward(std::vector<Actor*>& actors, double G) {
  return G;
}

std::vector<float> Agent::createState(std::vector<Actor*>& visibleActors) {
  std::vector<float> states;

  for (int i = 0; i < 8; i++) {
    states.push_back(0.0);
  }

  Location loc = this->getLocation();
  
  for (auto const actor : visibleActors) {
    if (actor == this) continue;

    if (!actor->isAgent() && !actor->isPOI()) continue;
    
    Location other = actor->getLocation();
    
    //double distance = Location::distance(loc, other);

    /*    if (distance < 1) {
	  distance = 1;
	  }*/
    int quad = Location::quadrant(loc, other) - 1;
    double val = 1.0;
    
    if (actor->isPOI()) {
      quad += 4;
      POI* p = (POI*) actor;
      val = p->getValue();
    }

    states[quad] += (float) 1;//(val / (distance));
  }
  
  return states;
}

void Agent::setLastCommand(Location loc) {
  this->lastCommand = loc;
}

Location Agent::getLastCommand() {
  return this->lastCommand;
}
