#include "Level.h"

int Level::setupLevel()
{
	srand((unsigned)time(NULL));

	std::ifstream inputMap;
	inputMap.open(levelName); //reading the file

	if (inputMap.fail())
	{
		std::cout << "Check the file name\n";
		return 1; //failure
	}

	// loading the map into the vector
	std::string tempLineHolder;
	while (std::getline(inputMap, tempLineHolder))
	{
		map.push_back(tempLineHolder);
	}

	// scanning the level map and initializing the player and monsters struct instances
	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < map[i].size(); j++)
		{
			switch (map[i][j])
			{
			case '@':// player
			{
				player1->init(j, i, 100, 20, 30, 40, '@', "player1");
				break;
			}
			case 'g':// goblin
			{
				monster* goblin = new monster;
				goblin->init(j, i, 50, 30, 50, 30, 'g', "goblin");
				monsterVec.push_back(goblin);
				break;
			}
			case 'd':// dragon
			{
				monster* dragon = new monster;
				dragon->init(j, i, 1000, 70, 10, 70, 'd', "dragon");
				monsterVec.push_back(dragon);
				break;
			}
			default:
				break;
			}
		}
	}
	return 0; //success
}

void Level::print()
{
	system("CLS");//clearing the screen, can be a bit slow

	/*
	Alternative way -
	cout << string(100, '\n');
	*/

	for (auto& line : map)
	{
		for (auto& c : line)
		{
			std::cout << c;
		}
		std::cout << '\n';
	}
}

int Level::playerMove()
{
	int x = player1->xPos, y = player1->yPos;

	switch (_getch())
	{
	case 'w'://up
		if (map[y - 1][x] == '.')
		{
			map[y][x] = '.';
			map[y - 1][x] = player1->symbol;
			player1->moveUp();
		}
		break;
	case 's'://down
		if (map[y + 1][x] == '.')
		{
			map[y][x] = '.';
			map[y + 1][x] = player1->symbol;
			player1->moveDown();
		}
		break;
	case 'a'://left
		if (map[y][x - 1] == '.')
		{
			map[y][x] = '.';
			map[y][x - 1] = player1->symbol;
			player1->moveLeft();
		}
		break;
	case 'd'://right
		if (map[y][x + 1] == '.')
		{
			map[y][x] = '.';
			map[y][x + 1] = player1->symbol;
			player1->moveRight();
		}
		break;
	case 'q'://quit
		return 1;
	default:
		break;
	}
	return 0;
}

void Level::monsterAi()
{
	// monster movement, randomised up and down

	for (int i = 0; i < monsterVec.size(); i++) //loop through all monsters and update their position
	{
		int x = monsterVec[i]->xPos, y = monsterVec[i]->yPos, random = rand() % 4;

		switch (random)
		{
		case 0: // go left
			if (map[y][x - 1] == '.')
			{
				map[y][x] = '.';
				map[y][x - 1] = monsterVec[i]->symbol;
				monsterVec[i]->moveLeft();
			}
			break;
		case 1: // go down
			if (map[y + 1][x] == '.')
			{
				map[y][x] = '.';
				map[y + 1][x] = monsterVec[i]->symbol;
				monsterVec[i]->moveDown();
			}
			break;
		case 2: // go right
			if (map[y][x + 1] == '.')
			{
				map[y][x] = '.';
				map[y][x + 1] = monsterVec[i]->symbol;
				monsterVec[i]->moveRight();
			}
			break;
		case 3: // go up
			if (map[y - 1][x] == '.')
			{
				map[y][x] = '.';
				map[y - 1][x] = monsterVec[i]->symbol;
				monsterVec[i]->moveUp();
			}
			break;
		default:
			break;
		}
	}
}

int Level::battleSystem(monster* _monster)
{
	using std::cin;
	using std::cout;

	bool wannaFight = true;

	cout << "you wanna fight or run ? Answer in 1(true) and 0(false) [once the battle starts you won't be able to run] ";
	cin >> wannaFight;

	if (wannaFight)
	{
		std::string monsterName = _monster->name;
		int playerAttackChance, monsterAttackChance;
		//srand((unsigned)time(NULL));

		while (player1->health > 0 && _monster->health > 0) //while both are alive
		{
			playerAttackChance = rand() % 100 + 1; //random number between 1 and 100

			cout << "you rolled the dice\n";
			cout << "your chance of attacking is " << playerAttackChance << "\n\n";

			if (player1->attackChance <= playerAttackChance)
			{
				// player attacks
				int def = _monster->defense / 10 + 1;
				_monster->health = _monster->health - (player1->damage / def);

				cout << "you landed a hit !\n\n";
				waitOneSecond();

				if (_monster->health <= 0)
				{
					cout << monsterName << " died !! You won\n";
					waitOneSecond();
					return 1; // player won
				}
				else
				{
					cout << monsterName << " health : " << _monster->health << '\n';
					cout << "player health : " << player1->health << "\n\n";
					waitOneSecond();
				}
			}
			else
			{
				cout << "you didn't land a hit\n\n";
				waitOneSecond();
			}

			monsterAttackChance = rand() % 100 + 1;

			cout << "the " << monsterName << " rolled the dice\n";
			cout << monsterName << "'s chance of attacking " << monsterAttackChance << "\n\n";

			if (_monster->attackChance <= monsterAttackChance)
			{
				// monster attack
				int def = player1->defense % 10 + 1;
				player1->health = player1->health - (_monster->damage / def);

				cout << monsterName << " landed a hit !\n\n";
				waitOneSecond();

				if (player1->health <= 0)
				{
					cout << "you died !!\n";
					waitOneSecond();
					return 0; // player died
				}
				else
				{
					cout << monsterName << " health : " << _monster->health << '\n';
					cout << "player health : " << player1->health << "\n\n";
					waitOneSecond();
				}
			}
			else
			{
				cout << monsterName << " didn't land a hit\n\n";
				waitOneSecond();
			}
		}
	}
	else
		return 2; // didn't fight
}

void Level::waitOneSecond()
{
	Sleep(1000); // sleep for 1 second
}

int Level::check_if_monster_nearby()
{
	int deltaXpos, deltaYpos, battleOutCome;
	double distance_ithElment;
	std::vector<double> distance;

	for (int i = 0; i < monsterVec.size(); i++)
	{// calculating the distance between player and monsters
		deltaXpos = abs(player1->xPos - monsterVec[i]->xPos);
		deltaYpos = abs(player1->yPos - monsterVec[i]->yPos);
		distance_ithElment = deltaXpos * deltaXpos + deltaYpos * deltaYpos;
		distance.push_back(distance_ithElment);
	}

	for (int i = 0; i < distance.size(); i++)
	{
		if (distance[i] <= 1.5)
		{
			//monster nearby, fight!
			battleOutCome = battleSystem(monsterVec[i]);

			switch (battleOutCome)
			{
			case 0: // player died
				map[player1->yPos][player1->xPos] = '.';
				return 0; //GAME OVER
			case 1:// player won
				map[monsterVec[i]->yPos][monsterVec[i]->xPos] = '.';
				delete monsterVec[i];

				monsterVec[i] = monsterVec.back();
				monsterVec.pop_back();
				return 1;// continue

			default:
				return 1;// continue
			}
		}
	}
	return 1;// continue, no monsters nearby
}

void Level::deleteAllHeapVariables()
{
	for (auto& monster : monsterVec)
	{
		delete monster;
	}
	monsterVec.clear();
	delete player1;
}

int Level::management(std::string _levelName)
{
	levelName = _levelName;

	if (setupLevel() == 1) //error in reading the file
		return 1;

	bool isDone = false;

	while (isDone == false)
	{
		monsterAi();
		print();

		if (check_if_monster_nearby() == 0)//player died
			isDone = true;//game over

		if (playerMove() == 1)//quit
		{
			isDone = true;
			return 0;
		}
	}
	deleteAllHeapVariables();
	map.clear();

	return 0;
}
