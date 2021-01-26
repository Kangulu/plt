# MagiX

## Game description

This project aims to make a game where players pick cards from 3 zones called rivers, each river is composed of 5 cards and each card cost ressources and grant you ressources.

Ressources are stone, water, wood and victory points.

When there is no turn left to play, the player with the most victory points wins the game. 

## Build instructions

### Environment

We use Ubuntu, but it also works on most Linux distributions.
Following instructions will install build dependencies on Debian.

```
sudo apt install git dia ghostscript cmake g++ lcov gcovr libxml2-dev libsfml-dev libboost-dev
git clone https://github.com/Kangulu/plt
```

### Build binaries

```
mkdir build
cd build
cmake ..
make all
```

Binaries are generated in *bin/* folder

You can also display a list of makefile targets with :
```
make help
```

### Features
Please make sure that you are in the top level folder of the project before trying to execute binaries.

You can test the rendering :
```
bin/client render
```

You can test the state evolution :

the active player will pick the first card of the first river when you press the spacebar.
```
bin/client engine
```

You can test the random ai :

each player will be an ai that pick a decision at random among possible decisions.
```
bin/client random_ai
```

You can test the heuristic ai :

each player will be an ai that pick a decision at random among possible decisions, favoring the cards in higher rivers.
```
bin/client heuristic_ai
```

You can test the deep ai :

The player 1 will be a random ai and the player 2 will be a deep ai who takes decision by exploring a decision tree.
```
bin/client deep_ai
```

You can compare the heuristic ai to the random_ai:

The heuristic ai will play 1000 times against the random one in game of 200 turns and a winrate will be printed.

In our experience the winrate is about 98.5%.
```
bin/client heuristic_ai_performance
```

You can compare the heuristic ai to the random_ai:

The deep ai will play 100 times against the random one in game of 200 turns and a winrate will be printed.

You can expect a 100% win rate.
```
bin/client deep_ai_performance
```

You can test the replay :

At the end of a game such as a game played by ai, a replay of the game is stored at the root of the project.

You can simply replay the game that has been played.
```
bin/client replay replay.json
```

You can play the game over the network :

Start the server using:
```
bin/network
```

Start clients using:
```
bin/client network
```
then enter your username and play the game.

Keep in mind that you need 2 clients to play.


## Authors

* [**Maxime Marroufin**](https://github.com/Kangulu)
* [**Quentin Chhean**](https://github.com/quenchhe)
* [**Abinaya Mathibala**](https://github.com/AbinayaM-coder)
* [**Alban Benmouffek**](https://github.com/sonibla)

See also the list of [contributors](https://github.com/Kangulu/plt/contributors) who participated in this project.
