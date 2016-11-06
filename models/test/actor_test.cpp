/*********************************************************************
*  actor_test.cpp
*
*  Unit tests for actor (generic interface of agents, poi, obstacles)
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

#include "actor.h"

class ActorTest : public::testing::Test {
  
};

TEST_F(ActorTest,testSetLocation) {
  double x = 3;
  double y = 2;
  Location loc = Location::createLoc(x,y);
  Actor a1;

  a1.setLocation(loc);
  Location aLoc = a1.getLocation();
  
  EXPECT_EQ(x, aLoc.x);
  EXPECT_EQ(y, aLoc.y);
}

TEST_F(ActorTest,testSetLocationByValue) {
  double x = 3;
  double y = 2;
  Location loc = Location::createLoc(x,y);
  Actor a1;

  a1.setLocation(loc);
  loc = Location::createLoc(y,x);
  Location aLoc = a1.getLocation();
  
  EXPECT_EQ(x, aLoc.x);
  EXPECT_EQ(y, aLoc.y);
}

TEST_F(ActorTest,testIsAgent) {
  Actor a;
  EXPECT_EQ(false, a.isAgent());
}

TEST_F(ActorTest,testIsPOI) {
  Actor a;
  EXPECT_EQ(false, a.isPOI());
}

TEST_F(ActorTest,testDefaultMove) {
  Actor a;
  Location loc = a.getLocation();

  std::vector<Actor*> actors;
  
  a.move(actors);
  Location loc2 = a.getLocation();

  EXPECT_EQ(loc.x, loc2.x);
  EXPECT_EQ(loc.y, loc2.y);
}
