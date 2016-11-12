/*********************************************************************
*  agent.h
*
*  Agents are the moving actors in the world. They have policies for
*    determining how they should change their location.
*
*  The base agent returns the global reward when determining its reward.
*
*  Agent is assumed to always face north (for the purposes of quadrant scores).
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

#ifndef _AGENT_H
#define _AGENT_H

#include <vector>

#include "actor.h"
#include "poi.h"

class Agent : public Actor {
 public:
  bool isPOI() { return false; };
  bool isAgent() { return true; };

  void move(std::vector<Actor*>&);

  double determineReward(std::vector<Actor*>&,double);
  
  Agent();
  Agent(Location);

  Location getLastCommand();
  void setLastCommand(Location);
 protected:
  std::vector<double> createState(std::vector<Actor*>&);
  virtual Location queryState(std::vector<double>) { return Location::createLoc(0,0); };
  Location lastCommand = Location::createLoc(0,0);
};

#endif
