/*********************************************************************
*  actor.h
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

#ifndef _ACTOR_H
#define _ACTOR_H

#include <vector>

#include "fann.h"
#include "fann_cpp.h"

#include "location.h"

class Actor {
 public:
  virtual void move();

  /*
    Calculates the reward (may be difference, global, local, etc) of an actor, given a set of other actors

    Args:
      All actors visible to this actor.
      G - the global reward signal
   */
  virtual double determineReward (std::vector<Actor*>&,double);

  /*
    If applicable, do something with the global reward. Anticipated use case: update local approximations
      of G.

    Args:
      Broadcast value of G.
   */
  virtual void receiveBroadcastG(double);

  Location getLocation();
  
 private:
  Location loc;
};

#endif
