/*********************************************************************
*  globalAgentDpp.cpp
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

#include "globalAgentDpp.h"
#include <iostream>

GlobalAgentDpp::GlobalAgentDpp() : GlobalAgent() {

}

GlobalAgentDpp::GlobalAgentDpp(Location loc) : GlobalAgent(loc) {

}

GlobalAgentDpp::GlobalAgentDpp(Location loc, World* world) : GlobalAgent(loc, world) {

}

double GlobalAgentDpp::determineReward(std::vector<Actor*>& actors, double g) {
  std::vector<Actor*> others;
  Location loc = this->getLocation();
  int agentCount = 0;
  
  for (const auto actor : actors) {
    if (actor != this) {
      others.push_back(actor);
    }
    if (actor->isAgent()) {
      agentCount++;
    }
  }

  double counterfactual = this->getWorld()->calculateG(others);
  double D = g - counterfactual;

  if (D > 0) return D;
  
  double Dpp = 0;

  std::vector<Actor*> copy;
  for (const auto actor : actors) {
    copy.push_back(actor);
  }

  for (int i = 1; i <= agentCount; i++) {
    Agent a (Location::createLoc(loc.x + 0.05, loc.y + 0.05));
    copy.push_back(&a);
    double withAdditionalAgent = this->getWorld()->calculateG(copy);
    Dpp = (withAdditionalAgent - g) / i;
    if (Dpp > 0) {
      return Dpp;
    }
  }

  return (Dpp > D) ? Dpp : D;
}
