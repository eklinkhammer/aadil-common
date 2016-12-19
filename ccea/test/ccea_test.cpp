/*********************************************************************
*  ccea_test.h
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

#include <gtest/gtest.h>
#include "gmock/gmock.h"

#include <iostream>
#include <vector>

#include "ccea.h"
#include "netEvaluator.h"

class CCEATest : public::testing::Test {
};

class MockNetEval : public NetEvaluator {
public:
  bool stateVar = false;
  
  std::vector<double> evaluateNNs(std::vector<FANN::neural_net*> nets) {
    std::vector<double> results;

    for (int i = 0; i < nets.size(); i++) {
      results.push_back(i);
    }

    stateVar = true;
    return results;
  }
  
};

TEST_F(CCEATest,testRunGeneration_popSizeConstant) {
   CCEA ccea;
  std::vector<std::vector<FANN::neural_net*> > initalPop = ccea.getPopulation();
  int popSizeInit = initalPop.size();
  int poolSizeInit = initalPop[0].size();

  MockNetEval eval;
  ccea.runGeneration(&eval);

  
  std::vector<std::vector<FANN::neural_net*> > afterPop = ccea.getPopulation();
  int popSizeAfter = afterPop.size();
  int poolSizeAfter = afterPop[0].size();

  EXPECT_EQ(popSizeInit, popSizeAfter);
  EXPECT_EQ(poolSizeInit, poolSizeAfter);
}

TEST_F(CCEATest,testRunGeneration_callsCallback) {
  CCEA ccea;
  MockNetEval eval;
  std::vector<FANN::neural_net*> nets;
  EXPECT_FALSE(eval.stateVar);
  
  ccea.runGeneration(&eval);

  EXPECT_TRUE(eval.stateVar);
}

TEST_F(CCEATest, testCurrentBestTeam) {
  CCEA ccea;
  MockNetEval eval;

  std::vector<FANN::neural_net*> currentBest = ccea.getCurrentBestTeam();
  EXPECT_EQ(0, currentBest.size());

  ccea.runGeneration(&eval);

  // 5 is the default number of pools. The best team returns the best network per pool.
  EXPECT_EQ(5, ccea.getCurrentBestTeam().size());
}
