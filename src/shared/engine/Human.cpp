#include "Human.h"
#include <iostream>

using namespace std;
using namespace engine;

Human::Human (std::shared_ptr<state::Player> player) : engine::Actor(player){
}

void Human::updateState (std::shared_ptr<state::State> state){
	state->notifyObservers();
	// Empty commandBuffer (out of date)
	this->commandMutex.lock();
	this->commandBuffer = make_shared<engine::PickCommand>(-1,-1,player->name);
	this->commandMutex.unlock();
}

std::shared_ptr<engine::Command> Human::getCommand (){
    //return this->commandBuffer;
	lock_guard<mutex> lck(this->commandMutex);
	//shared_ptr<engine::Command> command = make_shared<engine::PickCommand>(0,0,player->name);
	return this->commandBuffer;
}

