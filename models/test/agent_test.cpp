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

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "agent.h"

class AgentTest : public::testing::Test {
  
};

TEST_F(AgentTest, testIsAgent) {
  Agent a;

  EXPECT_TRUE(a.isAgent());
}

TEST_F(AgentTest, testIsPOI) {
  Agent a;

  EXPECT_FALSE(a.isPOI());
}
