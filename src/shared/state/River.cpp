#include "River.h"
#include <fstream>
#include <iostream>
#include <random>

using namespace state;
using namespace std;

River::River(){

}

void River::load(std::string filename,std::string path){
    Json::Reader reader;
    Json::Value cardPoolJson;
    std::string filepath  = path + filename;

    ifstream stream(filepath,ifstream::binary);
    reader.parse(stream,cardPoolJson,false);
    std::vector<Json::Value> cardPool;

    for(uint i =0; i<cardPoolJson["cards"].size();i++){
        Json::Value cardJson;
        std::string subFilepath = path +cardPoolJson["cards"][i].asString()+".json";
        ifstream subStream(subFilepath,ifstream::binary);
        reader.parse(subStream,cardJson,false);

        cardPool.push_back(cardJson);
    }

    this->cardPool = cardPool;
    
}

Json::Value River::serialize(){
    Json::Value riverValue;

    Json::Value cardsValue;
    for(uint i =0; i<this->cards.size();i++){
        cardsValue[i] = this->cards[i]->serialize();
    }
    riverValue["cards"] = cardsValue;

    Json::Value cardPoolValue;
    for(uint i =0; i<this->cardPool.size();i++){
        cardPoolValue[i] = this->cardPool[i];
    }
    riverValue["cardPool"] = cardPoolValue;

    return riverValue;
}

void River::unserialize(Json::Value value){

    std::vector<std::shared_ptr<Card>> cards;
    for(uint i =0; i<value["cards"].size();i++){
        this->cards.push_back(make_shared<Card>(value["cards"][i]));
    }
    this->cards = cards;

    std::vector<Json::Value> cardPool;
    for(uint i =0; i<value["cardPool"].size();i++){
        cardPool.push_back(value["cards"][i]);
    }
    this->cardPool = cardPool;
}

std::shared_ptr<Card> River::popCard(int position){
    std::shared_ptr<Card> card = this->cards[position];
    this->cards.erase(cards.begin()+position);
    return card;
}

void River::addCard(std::shared_ptr<Card> card){
    cards.push_back(card);
}

void River::refill(){
    while(this->cards.size()<5){
        Json::Value newCardJson = cardPool[rand()%(cardPool.size())];
        shared_ptr<Card> card = make_shared<Card>(newCardJson);
        addCard(card);
    }

}