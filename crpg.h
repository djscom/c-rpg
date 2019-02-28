struct Item{
	char name[50];
	int value;
};

struct Rooms{
	int danger;
	int north;
	int south;
	int east;
	int west;
	char name[100];
	struct Item floor;
} map[15];

struct Player{
	int max;
	int strength;
	int health;
	struct Item inventory[2];
} monster, player;

void status();
void findmonster();
void go();
void get();
void use();
int attack();
int win();