#include "State.h"

using namespace state;
using namespace std;

State::State (int remainingTurns,std::string ressourcespath){
    this->remainingTurns = remainingTurns;
    
    shared_ptr<Player> player1 = make_shared<Player>(string("Player 1"));
    shared_ptr<Player> player2 = make_shared<Player>(string("Player 2"));

    players.push_back(player1);
    players.push_back(player2);

    shared_ptr<River> river1 = make_shared<River>();
    river1->load("tier1.json",ressourcespath);
	river1->refill();
    rivers.push_back(river1);

    shared_ptr<River> river2 = make_shared<River>();
    river2->load("tier2.json",ressourcespath);
	river2->refill();
    rivers.push_back(river2);

    shared_ptr<River> river3 = make_shared<River>();
    river3->load("tier3.json",ressourcespath);
	river3->refill();
    rivers.push_back(river3);
	
}

State::State (shared_ptr<State> state){
    this->remainingTurns = state->remainingTurns;
	this->activePlayerIndex = state->activePlayerIndex;
	this->winnerIndex = state->winnerIndex;
	
    for(uint i =0 ; i<state->players.size();i++){
    	shared_ptr<Player> player = make_shared<Player>(state->players[i]);
    	this->players.push_back(player);
	}

	for(uint i =0 ; i<state->rivers.size();i++){
    	shared_ptr<River> river = make_shared<River>(state->rivers[i]);
    	this->rivers.push_back(river);
	}

}

State::State (Json::Value value){
    this->unserialize(value);
}

void State::endTurn (){
	if(remainingTurns >0){
		remainingTurns--;
		refreshActivePlayer();

    	players[activePlayerIndex]->earnIncome();
	}
	else{
		if(players[0]->ressources->victoryPoint > players[1]->ressources->victoryPoint){
			winnerIndex = 0;
		}else{
			winnerIndex = 1;
		}
	}
}

void State::refreshActivePlayer (){
	activePlayerIndex = (activePlayerIndex +1) %2;
}


Json::Value State::serialize(){
	Json::Value value;
	value["remainingTurns"] = this->remainingTurns;
	value["activePlayerIndex"] = this->activePlayerIndex;
	value["winnerIndex"] = this->winnerIndex;

	value["players"].resize(this->players.size());
	for (size_t i(0); i<this->players.size(); i++) {
		value["players"][(Json::ArrayIndex) i] = this->players.at(i)->serialize();
	}

	value["rivers"].resize(this->rivers.size());
	for (size_t i(0); i<this->rivers.size(); i++) {
		value["rivers"][(Json::ArrayIndex) i] = this->rivers.at(i)->serialize();
	}

	return value;
}

void State::unserialize(Json::Value value){

	this->remainingTurns = value["remainingTurns"].asInt();
	this->activePlayerIndex = value["activePlayerName"].asUInt();
	this->winnerIndex = value["winnerName"].asInt();
	this->players.clear();
	for (Json::ArrayIndex i(0); i<value["players"].size(); i++) {
		this->players.push_back(make_shared<Player>(value["players"][i]));
	}

	this->rivers.clear();
	for (Json::ArrayIndex i(0); i<value["rivers"].size(); i++) {
		this->rivers.push_back(make_shared<River>(value["rivers"][i]));
	}
}


void State::registerObserver (std::shared_ptr<Observer> observer){
    this->observers.push_back(observer);
}

void State::notifyObservers (){
    for(auto it = observers.begin();it != observers.end();it++){
        std::shared_ptr<Observer> observer = *it;

        observer->update(this->shared_from_this());
    }
}