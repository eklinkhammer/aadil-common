/*********************************************************************
*  world.h
*
*  Worlds are containers for all of the actors in a simulation, responsible
*    for moving all agents and calculating global rewards.
*
*  World is an interface for the various domains (rover, bar) used.
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

#ifndef _WORLD_H
#define _WORLD_H

#include <vector>

#include "actor.h"

class World {
 public:

  /*
    Calculates the global reward of the world, given its current state.
      Default is to call calculateG with current actor list.
   */
  virtual double calculateG();

  /*
    Calculates the global reward of the world, given some set of actors.
      Anticipated use case is for querying counterfactuals if global information
      is available. If applicable for the domain, all other world information will
      be the same (ie, only the actor information changes).

    Args:
      The counterfactual list of actors.
   */
  virtual double calculateG(std::vector<Actor*>) { return 0;} ;


  /*
    Calculates the score of the individual agents. Used by CCEA to assign scores to policies.

    Independent of world implementation, relies on Actor's determineReward and isAgent
      functions. 
   */
  virtual std::vector<double> getAgentRewards();

  /*
    The world progresses a single timestep. While potentially different for different worlds,
      the default implementation involves moving all actors and broadcasting G to them. If an
      actor moves to a location that is not within bounds, move the actor back to its previous
      location.
   */
  virtual void timestep();

  /*
    Returns all actors visible to the given actor. Generally, returns what is necessary to move
      and determine rewards. Visiblity (if applicable) is modified here. An actor is visible to itself.
   */
  virtual std::vector<Actor*>& visibleFrom(Actor*) {return actors; };
  
  World(std::vector<Actor*>);

  bool hasBounds;
  
  virtual bool inBounds(Actor*) { return true; };

  std::vector<Actor*>& getActors();
 private:
  std::vector<Actor*> actors;
};

#endif
