/*********************************************************************
*  agent_test.cpp
*
*  Unit tests for Agent. Contains neural network, ability to query it
*    to determine next location.
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

#include "agent.h"
#include "poi.h"

class AgentTest : public::testing::Test {
  
};

class ExposedAgent : public Agent {
public:
  using Agent::createState;
  using Agent::queryState;
};

TEST_F(AgentTest, testIsAgent) {
  Agent a;

  EXPECT_TRUE(a.isAgent());
}

TEST_F(AgentTest, testIsPOI) {
  Agent a;

  EXPECT_FALSE(a.isPOI());
}

TEST_F(AgentTest, testIsActorAgent) {
  Agent a;
  std::vector<Actor*> actors;
  actors.push_back(&a);

  EXPECT_TRUE(actors[0]->isAgent());
}

TEST_F(AgentTest, testCreateStateAgent) {
  ExposedAgent a;
  Agent b;
  b.setLocation(Location::createLoc(1,1));

  std::vector<Actor*> actors;
  actors.push_back(&a);
  actors.push_back(&b);

  std::vector<float> state = a.createState(actors);

  EXPECT_EQ(8, state.size());
  if (state.size() == 8) {
    EXPECT_FLOAT_EQ(1/sqrt(2), state[0]);
    EXPECT_EQ(0, state[1]);
    EXPECT_EQ(0, state[2]);
    EXPECT_EQ(0, state[3]);
    EXPECT_EQ(0, state[4]);
    EXPECT_EQ(0, state[5]);
    EXPECT_EQ(0, state[6]);
    EXPECT_EQ(0, state[7]);
  }
}

TEST_F(AgentTest, testCreateStatePOI) {
  ExposedAgent a;
  POI b;
  b.setLocation(Location::createLoc(1,1));
  b.init(5,0,0,0);

  std::vector<Actor*> actors;
  actors.push_back(&a);
  actors.push_back(&b);

  std::vector<float> state = a.createState(actors);

  EXPECT_EQ(8, state.size());
  if (state.size() == 8) {
    EXPECT_EQ(0, state[0]);
    EXPECT_EQ(0, state[1]);
    EXPECT_EQ(0, state[2]);
    EXPECT_EQ(0, state[3]);
    EXPECT_FLOAT_EQ(5 / sqrt(2), state[4]);
    EXPECT_EQ(0, state[5]);
    EXPECT_EQ(0, state[6]);
    EXPECT_EQ(0, state[7]);
  }
}

TEST_F(AgentTest, testCreateStateMultipleAgents) {
  ExposedAgent a;
  Agent b;
  b.setLocation(Location::createLoc(1,1));

  std::vector<Actor*> actors;
  actors.push_back(&a);
  actors.push_back(&b);
  actors.push_back(&b);

  std::vector<float> state = a.createState(actors);

  EXPECT_EQ(8, state.size());
  if (state.size() == 8) {
    EXPECT_FLOAT_EQ(sqrt(2), state[0]);
    EXPECT_EQ(0, state[1]);
    EXPECT_EQ(0, state[2]);
    EXPECT_EQ(0, state[3]);
    EXPECT_EQ(0, state[4]);
    EXPECT_EQ(0, state[5]);
    EXPECT_EQ(0, state[6]);
    EXPECT_EQ(0, state[7]);
  }
}

TEST_F(AgentTest, testCreateStateOrientation) {
  ExposedAgent a;
  Agent b;
  b.setLocation(Location::createLoc(1,1));
  Agent c;
  c.setLocation(Location::createLoc(-1,1));
  std::vector<Actor*> actors;
  actors.push_back(&a);
  actors.push_back(&b);
  actors.push_back(&c);

  std::vector<float> state = a.createState(actors);

  EXPECT_EQ(8, state.size());
  if (state.size() == 8) {
    EXPECT_FLOAT_EQ(1/sqrt(2), state[0]);
    EXPECT_FLOAT_EQ(1/sqrt(2), state[1]);
    EXPECT_EQ(0, state[2]);
    EXPECT_EQ(0, state[3]);
    EXPECT_EQ(0, state[4]);
    EXPECT_EQ(0, state[5]);
    EXPECT_EQ(0, state[6]);
    EXPECT_EQ(0, state[7]);
  }
}

TEST_F(AgentTest, testDetermineReward) {
  Agent a;
  std::vector<Actor*> actors;
  
  EXPECT_EQ(5, a.determineReward(actors,5));
}
