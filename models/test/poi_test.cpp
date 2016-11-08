/*********************************************************************
*  poi_test.cpp
*
*  Unit tests for POI. Contain bulk of G calculations.
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

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "poi.h"
#include "agent.h"

class POITest : public::testing::Test {
  
};

TEST_F(POITest, testIsPOI) {
  POI poi;

  EXPECT_TRUE(poi.isPOI());
}

TEST_F(POITest, testIsAgent) {
  POI poi;

  EXPECT_FALSE(poi.isAgent());
}

TEST_F(POITest, testActorIsPOI) {
  POI poi;
  std::vector<Actor*> actors;
  actors.push_back(&poi);

  EXPECT_TRUE(actors[0]->isPOI());
}

TEST_F(POITest, testReward) {
  Location oneAway = Location::createLoc(0,1);
  Agent a(oneAway);
  std::vector<Actor*> actors;
  actors.push_back(&a);

  POI poi;
  
  double reward = poi.determineReward(actors, 0);

  EXPECT_EQ(1, reward);
}

TEST_F(POITest, testRewardValue) {
  Location oneAway = Location::createLoc(0,1);
  Agent a(oneAway);
  std::vector<Actor*> actors;
  actors.push_back(&a);

  POI poi;
  poi.init(10,0.1,10,1);
  
  double reward = poi.determineReward(actors, 0);

  EXPECT_EQ(10, reward);
}

TEST_F(POITest, testRewardMinDistance) {
  Location oneAway = Location::createLoc(0,0.01);
  Agent a(oneAway);
  std::vector<Actor*> actors;
  actors.push_back(&a);

  POI poi;
  
  double reward = poi.determineReward(actors, 0);

  EXPECT_EQ(10, reward);
}

TEST_F(POITest, testRewardMaxDistance) {
  Location oneAway = Location::createLoc(0,2);
  Agent a(oneAway);
  std::vector<Actor*> actors;
  actors.push_back(&a);

  POI poi;
  poi.init(1,1,1,1);
  
  double reward = poi.determineReward(actors, 0);

  EXPECT_EQ(0, reward);
}

TEST_F(POITest, testRewardCoupling) {
  Location oneAway = Location::createLoc(0,1);
  Agent a(oneAway);
  std::vector<Actor*> actors;
  actors.push_back(&a);

  POI poi;
  poi.init(1,0.1,10,10);
  
  double reward = poi.determineReward(actors, 0);

  EXPECT_EQ(0, reward);
}

TEST_F(POITest, testRewardCouplingMultipleAgents) {
  Location oneAway = Location::createLoc(0,1);
  Agent a(oneAway);
  std::vector<Actor*> actors;
  actors.push_back(&a);
  actors.push_back(&a);

  POI poi;
  poi.init(1,0.1,10,2);
  
  double reward = poi.determineReward(actors, 0);

  EXPECT_EQ(2, reward);
}

TEST_F(POITest, testRewardCouplingExtraAgents) {
  Location oneAway = Location::createLoc(0,1);
  Agent a(oneAway);
  std::vector<Actor*> actors;
  actors.push_back(&a);
  actors.push_back(&a);
  actors.push_back(&a);

  POI poi;
  poi.init(1,0.1,10,2);
  
  double reward = poi.determineReward(actors, 0);

  EXPECT_EQ(2, reward);
}

TEST_F(POITest, testRewardCouplingExtraAgentsOrdering) {
  Location oneAway = Location::createLoc(0,1);
  Agent a(oneAway);
  std::vector<Actor*> actors;
  actors.push_back(&a);
  Agent b(Location::createLoc(0,2));
  actors.push_back(&b);
  actors.push_back(&a);


  POI poi;
  poi.init(1,0.1,10,2);
  
  double reward = poi.determineReward(actors, 0);

  EXPECT_EQ(2, reward);
}
