/*********************************************************************
*  ccea.h
*
*  CCEATest is a set of unit tests for the CCEA library.
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

#include <iostream>
#include <vector>

#include "ccea.h"

class CCEATest : public::testing::Test {
  protected:

  CCEA ccea;
  
  void callback(std::vector<FANN::neural_net*> nets, double scores[]) {

  }
};

TEST_F(CCEATest,testRunGeneration_popSizeConstant) {
  
}

TEST_F(CCEATest,testRunGeneration_variationWithinBounds) {

}

TEST_F(CCEATest,testRunGeneration_callsCallback) {

}


TEST_F(CCEATest,dummy) {
  const int expect = 5;
  int result = ccea.dummy();
  EXPECT_EQ(expect, result);
}

int main(int argc, char** argv) {
  std::cout << "Hello from Test\n";
  ::testing::InitGoogleTest(&argc,argv);
  return RUN_ALL_TESTS();
}
