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

Agent::Agent() : Actor() {

}

Agent::Agent(Location loc) : Actor(loc) {

}

void Agent::move(std::vector<Actor*>& actors) {

}

double Agent::determineReward(std::vector<Actor*>& actors, double G) {
  return G;
}

void Agent::setPolicy(FANN::neural_net* net) {

}

std::vector<double> Agent::createState(std::vector<Actor*>& visibleActors) {
  std::vector<double> states;
  return states;
}

Location Agent::queryState(std::vector<double>) {
  return Location::createLoc(1,1);
}
