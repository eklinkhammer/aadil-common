/*********************************************************************
*  actor.cpp
*
*  Actor is an interface for all agents / pois / other changing components
*    of world in a simulation.
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

#include "actor.h"


Location Actor::getLocation() {
  return this->loc;
}

void Actor::setLocation(Location newLoc) {
  this->loc = newLoc;
}

bool Actor::isAgent() {
  return false;
}

bool Actor::isPOI() {
  return false;
}

/*
  Creates an Actor, with a default starting location of the origin. Unclear on non-test use cases.
 */
Actor::Actor() {
  Location l = Location::createLoc(0,0);
  this->loc = l;
}

Actor::Actor(Location location) {
  this->loc = location;
}

void Actor::setPolicy(FANN_Wrapper* net) {
  this->policy = net;
}

FANN_Wrapper* Actor::getPolicy() {
  return this->policy;
}
