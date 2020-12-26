#include <boost/test/unit_test.hpp>
#include <memory>
#include <iostream>

#include "../../src/shared/state.h"

using namespace state;
using namespace std;


BOOST_AUTO_TEST_SUITE(state_State)

BOOST_AUTO_TEST_CASE(State_constructor){
    shared_ptr<State> state = make_shared<State>(42,"../../../res/cardsData/");
	BOOST_TEST(state->remainingTurns == 42);
	BOOST_TEST(state->players.size() == 2);
	BOOST_TEST(state->rivers.size() = 3);
}

BOOST_AUTO_TEST_CASE(State_serialization){
	shared_ptr<State> state1 = make_shared<State>(42,"../../../res/cardsData/");
	shared_ptr<State> state2 = make_shared<State>(10,"../../../res/cardsData/"); // Different from state1

	Json::Value valueState1 = state1->serialize();
	state2->unserialize(valueState1);
	
	BOOST_TEST(state1->remainingTurns == state2->remainingTurns);
}

BOOST_AUTO_TEST_CASE(State_endOfTurn){
	shared_ptr<State> state = make_shared<State>(1,"../../../res/cardsData/");
	
	BOOST_TEST(state->remainingTurns == 1);
	state->endTurn();
	BOOST_TEST(state->remainingTurns == 0);

	state->players[0]->ressources->victoryPoint = 1;
	state->endTurn();
	BOOST_TEST(state->remainingTurns == 0);
	BOOST_TEST(state->winnerIndex == 0);
	state->players[1]->ressources->victoryPoint = 2;
	state->endTurn();
	BOOST_TEST(state->remainingTurns == 0);
	BOOST_TEST(state->winnerIndex == 1);
}

BOOST_AUTO_TEST_SUITE_END();
