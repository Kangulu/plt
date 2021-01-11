#include "Node.h"
#include <iostream>

using namespace ai;
using namespace state;
using namespace std;

void Node::generateChilds(int depth){
    shared_ptr<state::Player> activePlayer = this->state->players[this->state->activePlayerIndex];

    if(this->state->winnerIndex == -1){
        if(depth != 0){
            std::vector<std::shared_ptr<engine::Command>> validCommands = AI::validCommands(this->state,activePlayer);
            uint highestRiverAvailable =0;
            for(uint i =0 ;i<validCommands.size();i++){
                if(shared_ptr<engine::PickCommand> pickCommand = dynamic_pointer_cast<engine::PickCommand>(validCommands[i])){
                    if(pickCommand->riverPosition > highestRiverAvailable){
                        highestRiverAvailable = pickCommand->riverPosition;
                    }
                }
            }
            vector<shared_ptr<engine::Command>> bestCommands;
            for(uint i =0 ;i<validCommands.size();i++){
                if(shared_ptr<engine::PickCommand> pickCommand = dynamic_pointer_cast<engine::PickCommand>(validCommands[i])){
                    if(pickCommand->riverPosition == highestRiverAvailable){
                        bestCommands.push_back(validCommands[i]);
                    }
                }
            }
            for(uint i =0; i<bestCommands.size();i++){
                std::shared_ptr<engine::PickCommand> childCommand = std::dynamic_pointer_cast<engine::PickCommand>(bestCommands[i]);
                std::shared_ptr<Node> child = make_shared<Node>(this->state,bestCommands[i],depth-1);
                childs.push_back(child);
            }
        }

    }
    else{
        this->terminalNode = true;
        //terminal node
    }
}

//Root of the tree
Node::Node (std::shared_ptr<state::State> state, int depth){
    
    this->state = make_shared<State>(state);
    
    this->generateChilds(depth);
}

Node::Node (std::shared_ptr<state::State> state, std::shared_ptr<engine::Command> command , int depth){
    this->state = make_shared<State>(state);
    this->command = command;

    command->execute(this->state);
    this->state->endTurn();

    this->generateChilds(depth);
}

int Node::heuristicValue (){
    std::shared_ptr<state::Player> player1 = state->players[0];
    std::shared_ptr<state::Player> player2 = state->players[1];
    int player1Score = (player1->ressources->victoryPoint + player1->ressources->victoryPointIncome * state->remainingTurns);
    player1Score += 1000*(min<int>(2,player1->ressources->woodIncome));
    player1Score += 1000*(min<int>(2,player1->ressources->stoneIncome));
    player1Score += 1000*(min<int>(2,player1->ressources->waterIncome));

    int player2Score = (player2->ressources->victoryPoint + player2->ressources->victoryPointIncome * state->remainingTurns);
    player2Score += 1000*(min<int>(2,player2->ressources->woodIncome));
    player2Score += 1000*(min<int>(2,player2->ressources->stoneIncome));
    player2Score += 1000*(min<int>(2,player2->ressources->waterIncome));

    return player1Score -player2Score;
    //difference de point de victoires
}
