#include "PickCommand.h"
#include <iostream>

using namespace engine;
using namespace std;

/*
    int riverPosition;
    int cardPosition;
    CommandID getId() const;
    const std::string& getPlayerName() const;
*/

PickCommand::PickCommand (int riverPosition, int cardPosition, std::string playerName){
    this->setId(CommandID::PICK);
    this->riverPosition = riverPosition;
    this->cardPosition = cardPosition;
    this->setPlayerName(playerName);
}
PickCommand::PickCommand (Json::Value value){
    this->unserialize(value);
}

void PickCommand::execute (std::shared_ptr<state::State> state){
    vector<shared_ptr<state::Player>> players = state->players;
    vector<shared_ptr<state::River>> rivers = state->rivers;

    for(auto it = players.begin();it != players.end();it++){
        shared_ptr<state::Player> player = (*it);
        shared_ptr<state::River> river = rivers[riverPosition];
        if((player->name == this->getPlayerName())){
            shared_ptr<state::Card> card = river->popCard(cardPosition);
            player->pick(card);
            river->refill();

            return;
        }
    }
}

bool PickCommand::verify (std::shared_ptr<state::State> state){
    vector<shared_ptr<state::Player>> players = state->players;
    vector<shared_ptr<state::River>> rivers = state->rivers;

    for(auto it = players.begin();it != players.end();it++){
        shared_ptr<state::Player> player = (*it);
        if((player->name == this->getPlayerName()) &&
            (this->riverPosition < rivers.size()) &&
            (this->cardPosition  < rivers[riverPosition]->cards.size())){

            shared_ptr<state::Card> card = rivers[riverPosition]->cards[cardPosition];
            if(player->ressources->isGreaterOrEqual(card->cost)){
                return true;
            }

        }
    }
    return false;
}

Json::Value PickCommand::serialize (){
    Json::Value value = this->Command::serialize();
    value["riverPosition"] = this->riverPosition;
    value["cardPosition"] = this->cardPosition;
    return value;
}

void PickCommand::unserialize (Json::Value value){
    this->id = (CommandID) value["id"].asUInt();
    this->riverPosition = value["riverPosition"].asUInt();
    this->cardPosition = value["cardPosition"].asUInt();
    this->setPlayerName(value["playerName"].asString());
}
