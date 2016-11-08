/*********************************************************************
*  location.cpp
*
*  Location stores a double tuple, plus some static useful operations on
*    locations.
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

#include "location.h"

Location::Location(double x, double y) {
  this->x = x;
  this->y = y;
}

Location Location::createLoc(double x, double y) {
  Location loc(x,y);
  return loc;
}

Location Location::addLocations(Location loc1, Location loc2) {
  double newX = loc1.x + loc2.x; 
  double newY = loc1.y + loc2.y;
  return createLoc(newX, newY);
}

double Location::distance(Location loc1, Location loc2) {
  double diffX = loc2.x - loc1.x;
  double diffY = loc2.y - loc1.y;
  return sqrt(diffX*diffX + diffY*diffY);
}

bool Location::equals(Location loc1, Location loc2) {
  return loc1.x ==loc2.x && loc1.y == loc2.y;
}

int Location::quadrant(Location loc1, Location loc2) {
  if (loc1.x < loc2.x && loc1.y <= loc2.y) return 1;
  if (loc1.x <= loc2.x && loc1.y > loc2.y) return 4;
  if (loc1.x > loc2.x && loc1.y >= loc2.y) return 3;
  return 2;
}
