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

  // Used for unit tests. Will increment first element in scores by 1
  static void callback(std::vector<FANN::neural_net*>& nets, std::vector<double>& scores) {
    for (const auto net : nets) {
      scores.push_back(0);
    }
  }
};

TEST_F(CCEATest,testRunGeneration_popSizeConstant) {
  std::vector<std::vector<FANN::neural_net*> > initalPop = ccea.getPopulation();
  int popSizeInit = initalPop.size();
  int poolSizeInit = initalPop[0].size();

  ccea.runGeneration(callback);

  std::vector<std::vector<FANN::neural_net*> > afterPop = ccea.getPopulation();
  int popSizeAfter = afterPop.size();
  int poolSizeAfter = afterPop[0].size();

  EXPECT_EQ(popSizeInit, popSizeAfter);
  EXPECT_EQ(poolSizeInit, poolSizeAfter);
}

TEST_F(CCEATest,testRunGeneration_callsCallback) {

}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc,argv);
  return RUN_ALL_TESTS();
}
