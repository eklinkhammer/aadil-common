/*********************************************************************
*  localAgent.h
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

#ifndef _LOCALAGENT_H
#define _LOCALAGENT_H

#include <vector>

#include "agent.h"
#include "poi.h"

class LocalAgent : public Agent {
 public:
  double determineReward(std::vector<Actor*>&,double);
  
  LocalAgent();
  LocalAgent(Location);
  LocalAgent(Location,FANN::neural_net*);
  
  void receiveBroadcastG(double,std::vector<Actor*>&);

  FANN::neural_net* getApproximation();
  
  
 private:
  FANN::neural_net* gApproximation;
  void initNetwork();
};

#endif
