/*********************************************************************
*  location_test.cpp
*
*  Unit tests for location.
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

#include "location.h"

class LocationTest : public::testing::Test {
  
};

TEST_F(LocationTest,testCreateLoc) {
  double x = 3;
  double y = 2;
  
  Location loc = Location::createLoc(x,y);

  EXPECT_EQ(x, loc.x);
  EXPECT_EQ(y, loc.y);
}

TEST_F(LocationTest, testAddLocationImmutable) {
  double x = 1;
  double y = 2;
  double x2 = 3;
  double y2 = 4;
  Location loc1 = Location::createLoc(x,y);
  Location loc2 = Location::createLoc(x2,y2);

  Location::addLocations(loc1, loc2);

  EXPECT_EQ(x, loc1.x);
  EXPECT_EQ(y, loc1.y);
  EXPECT_EQ(x2, loc2.x);
  EXPECT_EQ(y2, loc2.y);
  
}

TEST_F(LocationTest, testAddLocation) {
  double x = 1;
  double y = 2;
  double x2 = 3;
  double y2 = 4;
  Location loc1 = Location::createLoc(x,y);
  Location loc2 = Location::createLoc(x2,y2);

  Location sum = Location::addLocations(loc1, loc2);

  EXPECT_EQ(4, sum.x);
  EXPECT_EQ(6, sum.y);
}

TEST_F(LocationTest, testDistance) {
  double x = 0;
  double y = 0;
  double x2 = 3;
  double y2 = 4;
  Location loc1 = Location::createLoc(x,y);
  Location loc2 = Location::createLoc(x2,y2);

  double dist = Location::distance(loc1, loc2);

  EXPECT_EQ(5, dist);
}

TEST_F(LocationTest, testDistanceImmutable) {
  double x = 1;
  double y = 2;
  double x2 = 3;
  double y2 = 4;
  Location loc1 = Location::createLoc(x,y);
  Location loc2 = Location::createLoc(x2,y2);

  Location::distance(loc1, loc2);

  EXPECT_EQ(x, loc1.x);
  EXPECT_EQ(y, loc1.y);
  EXPECT_EQ(x2, loc2.x);
  EXPECT_EQ(y2, loc2.y);
}
TEST_F(LocationTest, testDistanceBackwards) {
  double x = 0;
  double y = 0;
  double x2 = 3;
  double y2 = 4;
  Location loc1 = Location::createLoc(x,y);
  Location loc2 = Location::createLoc(x2,y2);

  double dist = Location::distance(loc2, loc1);

  EXPECT_EQ(5, dist);
}

TEST_F(LocationTest, testEquals) {
  Location loc1 = Location::createLoc(1,1);
  Location loc2 = Location::createLoc(1,1);
  Location loc3 = Location::createLoc(2,2);

  EXPECT_TRUE(Location::equals(loc1,loc2));
  EXPECT_FALSE(Location::equals(loc1,loc3));
}

TEST_F(LocationTest, testEqualsNotReference) {
  Location loc1 = Location::createLoc(1,1);
  Location loc2 = Location::createLoc(1,1);

  loc1.x = 4;

  EXPECT_FALSE(Location::equals(loc1,loc2));
}
