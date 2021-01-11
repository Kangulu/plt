#include "Engine.h"
#include <iostream>
#include <fstream>

using namespace engine;
using namespace std;

Engine::Engine (std::vector<std::shared_ptr<Actor>> actors, std::shared_ptr<state::State> state){
    this->state = state;
    this->actors = actors;
}

void Engine::execute (std::shared_ptr<Command> command){
    command->execute(this->state);
}

bool Engine::verify (std::shared_ptr<Command> command){
    return command->verify(this->state);
}

void Engine::step (){
    vector<shared_ptr<state::Player>> players = state->players;
    shared_ptr<state::Player> activePlayer = state->players[state->activePlayerIndex];
    if(state->winnerIndex != -1){
        state->endTurn();
        return;
    }
            
    for(uint j =0;j<actors.size();j++){
                
        shared_ptr<Actor> actor = actors[j];
        actor->updateState(state);

        if(actor->player == activePlayer){
            shared_ptr<Command> command;
                    
            do{
                command = actor->getCommand();
            }
            while((verify(command) != true) || (command->getPlayerName() != activePlayer->name));
            commandHistoric.push_back(command);
            execute(command);
            
            state->endTurn();        
        }
    }   
}

void Engine::saveReplay (std::string filename){
    Json::Value replay;
    for(uint i = 0;i<commandHistoric.size();i++){
        replay["commands"][i] = commandHistoric[i]->serialize();
    }

    Json::StyledWriter styledWriter;
    std::ofstream replay_file_stream;
    replay_file_stream.open(filename);
    replay_file_stream << styledWriter.write(replay);
    replay_file_stream.close();

}

int Engine::loadReplay (std::string filename,std::string ressourcespath){
    Json::Reader reader;
    Json::Value replay;

    ifstream replay_file_stream;
    replay_file_stream.open(filename);
    if(replay_file_stream.is_open() != true){
        cout << "Cannot open "<< filename<< endl;
        return -1;
    }
    reader.parse(replay_file_stream,replay,false);
    Json::Value commands = replay["commands"];
    this->state = make_shared<state::State>(commands.size()-1,ressourcespath);
    vector<shared_ptr<Command>> P1commands,P2commands;
    for(uint i =0;i<commands.size();i++){

        shared_ptr<Command> command;
        CommandID id = (CommandID) commands[i]["id"].asUInt();;
        switch(id){
            case CommandID::PICK:
                command = make_shared<PickCommand>(commands[i]);
                break;
            default:
                cout << "bad command id" << endl;
                return -1;
        }
        if(i%2 ==0){
            P1commands.push_back(make_shared<PickCommand>(commands[i]));
        }else{
            P2commands.push_back(make_shared<PickCommand>(commands[i]));
        }
    }
    actors.push_back(make_shared<ReplayActor>(state->players[0],P1commands));
    actors.push_back(make_shared<ReplayActor>(state->players[1],P2commands));
    return 0;
}
