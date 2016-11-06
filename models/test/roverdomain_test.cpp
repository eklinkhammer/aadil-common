/*********************************************************************
*  roverdomain_test.cpp
*
*  Unit tests for rover domain.
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

#include "roverdomain.h"

class RoverDomainTest : public::testing::Test {
  
};

TEST_F(RoverDomainTest, testInBoundsWithinBounds) {
  Location bound = Location::createLoc(5,5);
  std::vector<Actor*> actors;
  RoverDomain r(actors,bound);
  
  Location inBound = Location::createLoc(3,3);
  Actor a;
  a.setLocation(inBound);
  
  EXPECT_TRUE(r.inBounds(&a));
}

TEST_F(RoverDomainTest, testInBoundsOutOfBounds) {
  Location bound = Location::createLoc(5,5);
  std::vector<Actor*> actors;
  RoverDomain r(actors,bound);
  
  Location outOfBoundsX = Location::createLoc(6,1);
  Actor a;
  a.setLocation(outOfBoundsX);

  Location outOfBoundsY = Location::createLoc(1,6);
  Actor b;
  b.setLocation(outOfBoundsY);
  
  EXPECT_FALSE(r.inBounds(&a));
  EXPECT_FALSE(r.inBounds(&b));
}

TEST_F(RoverDomainTest, testInBoundsOnBoundary) {
  Location bound = Location::createLoc(5,5);
  std::vector<Actor*> actors;
  RoverDomain r(actors,bound);
  
  Location onBound = Location::createLoc(5,5);
  Actor a;
  a.setLocation(onBound);
  
  EXPECT_FALSE(r.inBounds(&a));
}
