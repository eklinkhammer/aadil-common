/*********************************************************************
*  poi.h
*
*  POIs are point of interest in the world. They are used to determine
*    the global reward in the rover domain.
*
*  The default POI does not move, and calculates the reward according to
*  the D paper. However, supports a minimum number of agents and a maximum
*  distance in determining the reward.
*
*  Without any additional information, the default assumes there is no
*    maximum scoring distance, and only the closest agent will score.
*    The minimum default distance is 0.1. Default value is 1.
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

#ifndef _POI_H
#define _POI_H

#include <vector>
#include <limits>

#include "actor.h"
#include <float.h>

class POI : public Actor {
 public:
  bool isPOI() { return true; };
  bool isAgent() { return false; };

  /*
    Reward is the sum of the values of the poi / the distance of the closest actors,
      assuming the actors are within a certain distance, up to the number of required agents.
   */
  double determineReward(std::vector<Actor*>&,double);

  POI();
  POI(Location);

  virtual std::string toString() { return "P"; };
  /*
     Initializes the private variables of a POI.

     Args:
       Value - The relative weight of this poi.
       MinScoring Distance - the closest an agent can be (avoids collisions / div by 0 issues)
       MaxScoring Distance - the farthest an agent can be to still count as scoring
       Num agents - The number of agents required to return a score. Also the number of agents counted.
   */
  void init(double, double, double, double);

  double getValue() { return this->value; };
  double getScore() { return this->score; };
 private:
  double value;
  double minScoringDistance;
  double maxScoringDistance;
  double numberRequiredAgents;
  double score;
};

#endif
