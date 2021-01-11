#include <iostream>

// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>

void testSFML() {
    sf::Texture texture;
}

// Fin test SFML

#include <state.h>
#include <client.h>
#include <cstring>
#include <random>
#include <X11/Xlib.h>

using namespace std;
using namespace state;
using namespace render;
using namespace client;

int main(int argc,char* argv[])
{   
    XInitThreads();
    srand(time(NULL));
    Test test;
    if (argc > 1) {
        if (strcmp(argv[1], "hello") == 0) {
            cout << "Hello world !" << endl;
        }else if (strcmp(argv[1], "state") == 0) {
            test.state();
        }else if (strcmp(argv[1], "render") == 0) {
            test.render();
        } else if (strcmp(argv[1], "engine") == 0) {
            test.engine();
        } else if (strcmp(argv[1], "random_ai") == 0) {
            test.random_ai();
        } else if (strcmp(argv[1], "player_vs_ai") == 0) {
            test.player_vs_ai();
        } else if (strcmp(argv[1], "heuristic_ai") == 0) {
            test.heuristic_ai();
        } else if (strcmp(argv[1], "deep_ai") == 0) {
            test.deep_ai();
        } else if (strcmp(argv[1], "heuristic_ai_performance") == 0) {
            test.heuristic_ai_performance();
        } else if (strcmp(argv[1], "deep_ai_performance") == 0) {
            test.deep_ai_performance();
        } else if (strcmp(argv[1], "replay") == 0) {
            if(argc >2){
                test.replay(argv[2]);
            }
            else{
                cout << "Too few arguments" << endl;
            }
        }else{
            cout << "Unknown argument" << endl;
        }
    } else {
        cout << "Too few arguments" << endl;
    }

    return 0;
}
