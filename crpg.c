#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

void instructions(){
	printf("\nReach Level 3, and rescue princess!\n");
}

struct Rooms{
	int chance;
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

int currentroom = 0;
int monsterhere;
int points = 0;

void init();
void getmonster();

int main(){
	system("clear");
	init();
	instructions();
	printf("\n-------------------\n");
	printf("Commands:\ngo [direction]\nget [item]\nattack\n");
	printf("-------------------\n");
	getmonster();
	char command[100];
	char *move;
	
	while(1){
		printf("You are in the %s.\n", map[currentroom].name);
		if(monsterhere == 1){
			printf("There is a monster in the room.\n");	
			printf("-------------------\n");
			printf("Monster health: %d/%d Strength: %d\nPlayer health: %d/%d Strength: %d\n", monster.health, monster.max, monster.strength, player.health, player.max, player.strength);
			printf("-------------------\n");
		}
		printf("\n> ");
		fgets(command, 100, stdin);
		char *ptr = strtok(command, " \n");
		move = strtok(NULL, "\n");
		if(strcmp(ptr, "go") == 0){
			if(move != NULL && monsterhere != 1){
				if(strcmp(move, "north") == 0 && map[currentroom].north >= 0){
					currentroom = map[currentroom].north;
					getmonster();
				}
				else if(strcmp(move, "south") == 0 && map[currentroom].south >= 0){
					currentroom = map[currentroom].south;
					getmonster();
				}
				else if(strcmp(move, "east") == 0 && map[currentroom].east >= 0){
					currentroom = map[currentroom].east;
					getmonster();
				}
				else if(strcmp(move, "west") == 0 && map[currentroom].west >= 0){
					currentroom = map[currentroom].west;
					getmonster();
				}
				else{
					printf("Can't go that way!\n");
				}
			}
			else{
				printf("\n*Can't escape until the monster is defeated!\n\n");
			}
		}
		else if(strcmp(ptr, "get") == 0){
			printf("You entered get!\n");
		}
		else if(strcmp(ptr, "attack") == 0){
			if(monsterhere == -1){
				printf("\n  There is no monster here to attack!\n");
			}
			else{
				int monsterdamage = rand()%player.strength;
				monster.health -= monsterdamage;
				printf("\n*You did %d points of damage!\n", monsterdamage);
				if(monster.health <= 0){
					monsterhere = -1;
					points++;
					printf("\nYou killed the monster!\n");
				}
				else{
					int playerdamage = rand()%monster.strength;
					player.health -= playerdamage;
					printf("*The monster did %d points of damage!\n\n", playerdamage);
					if(player.health <= 0){
						printf("The monster has beaten you! GAME OVER\n");
						if(points == 1)
							printf("You scored 1 point.\n");
						else
							printf("You scored %d points.\n", points);				
						break;
					}
				}
			}
		}
		else if(strcmp(ptr, "exit") == 0){
			break;
		}
		else{
			printf("Invalid command.\n");
		}
	}
	return 0;
}

void init(){
	FILE *init;
	char *line;
	char read;
	size_t len;
	init = fopen("rooms.map", "r");
	int i = -1;
	while ((read = getline(&line, &len, init)) != -1) {
		char *ptr = strtok(line, " ");
		char *def;
		def = strtok(NULL, "\n");
		if(strcmp(ptr, "name") == 0){
			i++;
			strcpy(map[i].name, def);
		}else if(strcmp(ptr, "north") == 0){
			map[i].north = atoi(def);
		}else if(strcmp(ptr, "south") == 0){
			map[i].south = atoi(def);
		}else if(strcmp(ptr, "east") == 0){
			map[i].east = atoi(def);				
		}else if(strcmp(ptr, "west") == 0){
			map[i].west = atoi(def);
		}else if(strcmp(ptr, "chance") == 0){
			map[i].chance = atoi(def);
		}
	}
	srand(time(NULL));
	player.max = rand()%50 + 10;
	player.health = player.max;
	player.strength = rand()%10 + 10;
}

void getmonster(){
	int roll = rand()%map[currentroom].chance;
	if(roll == 1){
		monsterhere = 1;
		monster.max = rand()%40 + 10;
		monster.health = monster.max;
		monster.strength = rand()%25;
	}
	else{
		monsterhere = -1;
	}
}