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
  std::vector<double> state = this->createState(actors);

  double* a = &state[0];

  fann_type* input = (fann_type*) a;

  FANN::neural_net* net = this->getPolicy();

  
  fann_type* output = net->run(input);
  fann_type fSum = output[0] + output[1];

  fSum = fSum == 0 ? 1 : fSum;
  
  double normX = (double) (output[0] / fSum);
  double normY = (double) (output[1] / fSum);

  // Neural network will always output a positive value between 0 and 1
  normX = 2 * normX - 1;
  normY = 2 * normY - 1;

  Location current = this->getLocation();
  Location move = Location::createLoc(normX, normY);
  /*for (auto s : state) std::cout << s << " ";
  std::cout << "\n";
  std::cout << normX << ", " << normY << "\n";*/
  if (rand() % 100 < 5) {
    int x = rand() % 50;
    int y = rand() % 50;
    double xM = (double) x / (x + y);
    double yM = (double) y / (x + y);
    yM = rand() % 2 == 0 ? yM : yM * -1;
    xM = rand() % 2 == 0 ? xM : xM * -1;
    move = Location::createLoc(xM, yM);
  }
  this->setLastCommand(move);
  this->setLocation(Location::addLocations(current, move));
}

double Agent::determineReward(std::vector<Actor*>& actors, double G) {
  return G;
}

std::vector<double> Agent::createState(std::vector<Actor*>& visibleActors) {
  std::vector<double> states;

  for (int i = 0; i < 8; i++) {
    states.push_back(0.0);
  }

  Location loc = this->getLocation();
  
  for (auto const actor : visibleActors) {
    if (actor == this) continue;

    if (!actor->isAgent() && !actor->isPOI()) continue;
    
    Location other = actor->getLocation();
    double distance = Location::distance(loc, other);

    if (distance < 1) {
      distance = 1;
    }
    int quad = Location::quadrant(loc, other) - 1;
    double val = 1.0;
    
    if (actor->isPOI()) {
      quad += 4;
      POI* p = (POI*) actor;
      val = p->getValue();
    }

    states[quad] += val / (distance * distance);
  }
  
  return states;
}

void Agent::setLastCommand(Location loc) {
  this->lastCommand = loc;
}

Location Agent::getLastCommand() {
  return this->lastCommand;
}
