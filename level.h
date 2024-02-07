#ifndef ASCII_RougueLike_VISUALSTUDIO2024_ADITYA
#define ASCII_RougueLike_VISUALSTUDIO2024_ADITYA

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <conio.h>
#include <random>
#include <ctime>
#include <cstdlib>
#include <math.h>
#include <Windows.h>

class Level
{
	// struct to encapsulate an entity, be it player or monster
	struct entity
	{
	public:
		int xPos = 0, yPos = 0; //coords
		int health = 0, damage = 0, attackChance = 0, defense = 0; //stats
		char symbol = ' '; //symbol to be displayed on map
		std::string name = "";

		void init(int _xPos, int _yPos, int _health, int _damage, int _defense, int _attackChance, char _symbol, std::string _name = "player1")
		{
			xPos = _xPos;
			yPos = _yPos;
			health = _health;
			damage = _damage;
			defense = _defense;
			attackChance = _attackChance;
			symbol = _symbol;
			name = _name;
		}
		void moveUp()
		{
			yPos--;
		}
		void moveDown()
		{
			yPos++;
		}
		void moveLeft()
		{
			xPos--;
		}
		void moveRight()
		{
			xPos++;
		}
	};
	struct player : public entity
	{
	};
	player* player1 = new player;// creating a new player instance

	struct monster : public entity
	{
	};

	int setupLevel(); // reads level.txt and sets up monster and player instances and populates monsterVec. Return 1 when failed and 0 when successful
	void print();// prints the map
	int playerMove(); //method for handeling wasd movement for player, returns 1 if player quits, 0 otherwise
	void monsterAi(); //method for random monster movement
	int battleSystem(monster* _monster);// return value => 1 for won, 0 for lost , 2 for didn't fight
	void waitOneSecond(); //waits for one second
	int check_if_monster_nearby();// 0 = player dead, 1 = means continue
	void deleteAllHeapVariables();

	std::vector<monster*> monsterVec;
	std::vector<std::string> map;
	std::string levelName;

public:
	int management(std::string _levelName);
};

#endif // !ASCII_RougueLike_VISUALSTUDIO2024_ADITYA
