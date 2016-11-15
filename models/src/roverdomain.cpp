/*********************************************************************
*  roverdomain.cpp
*
*  Rover domain is a bounded stateful world with perfect visibility. Global 
*    reward function determined as in <PAPER HERE>
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

#include "roverdomain.h"
#include "poi.h"
#include <random>
#include <math.h>
#include <iostream>

RoverDomain::RoverDomain(std::vector<Actor*> actors, Location bounds) : World (actors) {
  this->hasBounds = true;
  this->upperRightCorner = bounds;
}

std::vector<Actor*>& RoverDomain::visibleFrom(Actor*) {
  return this->getActors();
}

double RoverDomain::calculateG() {
  return World::calculateG();
}
double RoverDomain::calculateG(std::vector<Actor*> actors) {
  double globalReward = 0;
  for (const auto& actor : actors) {
    if (actor->isPOI()) {
      globalReward += actor->determineReward(actors,0); // second param is not used
    }
  }

  return globalReward;
}
  
bool RoverDomain::inBounds(Actor* actor) {
  Location loc = actor->getLocation();

  return loc.x <  this->upperRightCorner.x && loc.y <  this->upperRightCorner.y
    &&   loc.x >= 0                        && loc.y >= 0;
}

Location RoverDomain::randomLocation() {
  double x = ((double) rand() / INT_MAX) * this->upperRightCorner.x;
  double y = ( (double) rand() / INT_MAX)  * this->upperRightCorner.y;
  return Location::createLoc(x,y);
}

void RoverDomain::display() {
  std::vector<std::vector<Actor*> > actorsByRow;
  for (int i = 0; i < this->upperRightCorner.y; i++) {
    std::vector<Actor*> row;
    actorsByRow.push_back(row);
  }
  for (const auto actor : this->getActors()) {
    Location actorLoc = actor->getLocation();
    int y = floor(actorLoc.y);
    actorsByRow[y].push_back(actor);
  }

  for (int i = 0; i < this->upperRightCorner.y; i++) {
    std::cout << "|";
    for (int j = 0; j < this->upperRightCorner.x; j++) {
      for (const auto actor : actorsByRow[i]) {
	Location actorLoc = actor->getLocation();
	if (floor(actorLoc.x) == j) {
	  if (actor->isAgent()) {
	    std::cout << "A";
	  } else if (actor->isPOI()) {
	    std::cout << "P";
	  } else {
	    std::cout << "_";
	  }
	}
      }
    }
    std:: cout << "|\n";
  }
}
