/*********************************************************************
*  poi.cpp
*
*  POI (Point of Interest) is the reward calculating objectives of the 
*    rover domain.
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

#include "poi.h"

POI::POI() {
  this->setLocation(Location::createLoc(0,0));
  init(1,0.1,DBL_MAX,1);
}

POI::POI(Location loc) : Actor(loc) {
  init(1.0, 0.1, DBL_MAX, 1);
}

double POI::determineReward(std::vector<Actor*>& actors, double unused) {

  Location poiLoc = this->getLocation();
  
  std::vector<double> distances;

  std::vector<Actor*> actorsCopy = actors;
  
  for (int requiredAgents = 0; requiredAgents < this->numberRequiredAgents; requiredAgents++) {

    double min = this->maxScoringDistance;
    int index_min = -1;

    for (int a = 0; a < actorsCopy.size(); a++) {
      Location actorLoc = actorsCopy[a]->getLocation();
      double distance = Location::distance(poiLoc, actorLoc);

      if (distance < min) {
	min = distance;
	index_min = a;
      }
    }

    if (index_min > -1) {
      actorsCopy.erase(actorsCopy.begin() + index_min);
      if (min > this->minScoringDistance) {
	distances.push_back(min);
      } else {
	distances.push_back(this->minScoringDistance);
      }
    }
  }

  if (distances.size() < this->numberRequiredAgents) {
    return 0;
  }

  double reward = 0;
  for (int d = 0; d < this->numberRequiredAgents; d++) {
    reward += (this->value / distances[d]);
  }

  return reward;
}

void POI::init(double val, double min, double max, double numAgents) {
  this->value = val;
  this->minScoringDistance = min;
  this->maxScoringDistance = max;
  this->numberRequiredAgents = numAgents;
}
