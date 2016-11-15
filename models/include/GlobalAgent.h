/*********************************************************************
*  globalAgent.h
*
*  Global agents are agents with access to world - they can query the 
*    world's calculateG function, as well as anything else they might need.
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

#ifndef _GLOBALAGENT_H
#define _GLOBALAGENT_H

#include <vector>

#include "agent.h"
#include "poi.h"
#include "world.h"

class GlobalAgent : public Agent {
 public:

  virtual double determineReward(std::vector<Actor*>&,double);
  
  GlobalAgent();
  GlobalAgent(Location);
  GlobalAgent(Location,World*);

  void setWorld(World*);
  
 protected:
  World* getWorld();
 private:
  World* w;
};

#endif
