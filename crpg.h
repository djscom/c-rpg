struct Rooms{
	int danger;
	int north;
	int south;
	int east;
	int west;
	char name[100];
} map[15];

struct Player{
	int max;
	int strength;
	int health;
} monster, player;

void status();
void findmonster();
void go();
int attack();
int win();