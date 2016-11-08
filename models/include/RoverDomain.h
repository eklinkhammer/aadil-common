/*********************************************************************
*  RoverDomain.h
*
*  A rover domain is a bounded world with perfect visibility.
*
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

#ifndef _ROVERDOMAIN_H
#define _ROVERDOMAIN_H

#include <vector>

#include "world.h"

class RoverDomain : public World {
 public:

  /**
     A Rover domain is a bounded world (dimensions specified by location).
   **/
  RoverDomain(std::vector<Actor*>,Location);

  // Virtual functions from World that are being overwritten by Rover Domain
  std::vector<Actor*>& visibleFrom(Actor*);
  double calculateG(std::vector<Actor*>);
  double calculateG();
  bool inBounds(Actor*);
  
 private:
  Location upperRightCorner = Location::createLoc(0,0);
};

#endif
