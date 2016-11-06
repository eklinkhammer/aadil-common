/*********************************************************************
* location.h
*
*  Simple Tuple for Location, and some operations on locations
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

#ifndef _LOCATION_H
#define _LOCATION_H

#include <math.h>
class Location {
 public:
  double x;
  double y;

  static Location createLoc(double,double);
  static Location addLocations(Location,Location);
  static double distance(Location,Location);
  static bool equals(Location,Location);
 private:
  Location (double,double);
};

#endif
