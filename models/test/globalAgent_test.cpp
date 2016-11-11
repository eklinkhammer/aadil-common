/*********************************************************************
*  globalAgent_test.cpp
*
*  Unit tests for Global Agent. TODO - unit tests depend on knowledge of
*    POI evaluation. Must make more general.
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

#include <math.h>
#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "globalAgent.h"
#include "poi.h"
#include "roverDomain.h"

class GlobalAgentTest : public::testing::Test {
  
};

TEST_F(GlobalAgentTest, testDetermineRewardSingleAgent) {

  GlobalAgent a (Location::createLoc(1,0));
  POI poi (Location::createLoc(0,0));

  std::vector<Actor*> actors;
  actors.push_back(&a);
  actors.push_back(&poi);

  RoverDomain r (actors, Location::createLoc(10,10));

  a.setWorld(&r);
  
  double reward = a.determineReward(r.visibleFrom(&a), r.calculateG());

  EXPECT_EQ(r.calculateG(), reward);
}

TEST_F(GlobalAgentTest, testDetermineRewardCloserAgent) {
  GlobalAgent a (Location::createLoc(2,0));
  GlobalAgent b (Location::createLoc(1,0));
  POI poi (Location::createLoc(0,0));

  std::vector<Actor*> actors;
  actors.push_back(&a);
  actors.push_back(&b);
  actors.push_back(&poi);

  RoverDomain r(actors, Location::createLoc(10,10));

  a.setWorld(&r);
  b.setWorld(&r);

  double reward = a.determineReward(r.visibleFrom(&a), r.calculateG());

  EXPECT_EQ(0, reward);
}

TEST_F(GlobalAgentTest, testDetermineRewardMarginal) {
  GlobalAgent a (Location::createLoc(2,0));
  GlobalAgent b (Location::createLoc(1,0));
  POI poi (Location::createLoc(0,0));

  std::vector<Actor*> actors;
  actors.push_back(&a);
  actors.push_back(&b);
  actors.push_back(&poi);

  RoverDomain r(actors, Location::createLoc(10,10));

  a.setWorld(&r);
  b.setWorld(&r);

  double reward = b.determineReward(r.visibleFrom(&a), r.calculateG());

  EXPECT_TRUE(reward > 0);
  EXPECT_TRUE(reward < r.calculateG());
}

