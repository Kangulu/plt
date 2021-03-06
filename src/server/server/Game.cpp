#include "Game.h"

#include <boost/asio.hpp>
#include <iostream>

#include "Human.h"

using namespace server;
using namespace std;
using namespace boost;

Game::Game (std::list<std::shared_ptr<Client>> clients){
    if(clients.size() ==2){
        this->clients.push_back(clients.front());
        this->clients.push_back(clients.back());
    }
}

void Game::start (){
    cout << "Game: " << clients[0]->username <<" vs "<< clients[1]->username<<"has started !" << endl;

    std::shared_ptr<state::State> state = make_shared<state::State>(20,"res/cardsData/");
    state->players[0]->name = clients[0]->username;
    state->players[1]->name = clients[1]->username;

    std::vector<std::shared_ptr<engine::Actor>> actors;

    actors.push_back(make_shared<Human>(state->players[0],clients[0]));
    actors[0]->updateState(state);
    cout << "sent first state to J1" << endl;
    actors.push_back(make_shared<Human>(state->players[1],clients[1]));
    actors[1]->updateState(state);
    cout << "sent first state to J2" << endl;

    this->engine = make_shared<engine::Engine>(actors,state);

    std::thread th(([this](){this->run();}));      
	th.detach(); 
}

void Game::run (){
    while(engine->state->winnerIndex == -1){
        engine->step();
    }
    cout << "end of game"<< endl;
}

void Game::stop (){
    clients[0]->socket->close();
    clients[1]->socket->close();
    delete this;
}
