#include <boost/test/unit_test.hpp>
#include <memory>
#include <iostream>

#include "../../src/shared/state.h"
#include "../../src/shared/engine.h"
#include "../../src/shared/ai.h"

using namespace state;
using namespace engine;
using namespace ai;
using namespace std;

BOOST_AUTO_TEST_SUITE(test_AI);

BOOST_AUTO_TEST_CASE(ai_validCommandsInit){
    shared_ptr<State> state = make_shared<State>(42,"../../../res/cardsData/");
    
    BOOST_TEST(1);
}

BOOST_AUTO_TEST_SUITE_END();