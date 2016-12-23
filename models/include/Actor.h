/*********************************************************************
*  actor.h
*
*  Actor is an interface for all agents / pois / other changing components
*    of world in a simulation.
*
*  TODO: Identify a better way of classifying subclasses in parent class.
*  Goal - Have a way to ask actors if they are of subclass type _
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
#include "wrapper.h"

#include "location.h"

class Actor {
 public:
  
  // Getter for location
  Location getLocation();

  // setter for location
  void setLocation(Location);

  // default constructor
  Actor();

  Actor(Location);
  /*
    Whether or not this actor is an agent.
   */
  virtual bool isAgent();

  /*
    Whether or not this actor is a POI.
  */
  virtual bool isPOI();
  
  virtual void move(std::vector<Actor*>&) {};

  /*
    Calculates the reward (may be difference, global, local, etc) of an actor, given a set of other actors

    Args:
      All actors visible to this actor.
      G - the global reward signal
   */
  virtual double determineReward (std::vector<Actor*>&,double) {return 0;};

  /*
    If applicable, do something with the global reward. Anticipated use case: update local approximations
      of G.

    Args:
      Broadcast value of G.
   */
  virtual void receiveBroadcastG(double,std::vector<Actor*>&) {};

  virtual std::string toString() {return ""; };
  
  void setPolicy(FANN_Wrapper*);
  FANN_Wrapper* getPolicy();
 private:
  Location loc = Location::createLoc(0,0);
  FANN_Wrapper* policy;
};

#endif
