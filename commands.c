#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "crpg.h"

extern struct Rooms map[];
extern struct Player monster;
extern int monsterhere, currentroom, points;
extern char *ptr, *move;

void findmonster(){
	int roll = rand()%map[currentroom].danger;
	if(roll == 0){
		monsterhere = 1;
		monster.max = rand()%40 + 1;
		monster.health = monster.max;
		monster.strength = rand()%10 + 1;
	}
	else{
		monsterhere = 0;
	}
}

void go(){
	if(move != NULL && monsterhere != 1){
		if(strcmp(move, "north") == 0 && map[currentroom].north >= 0){
			currentroom = map[currentroom].north;
			findmonster();
		}
		else if(strcmp(move, "south") == 0 && map[currentroom].south >= 0){
			currentroom = map[currentroom].south;
			findmonster();
		}
		else if(strcmp(move, "east") == 0 && map[currentroom].east >= 0){
			currentroom = map[currentroom].east;
			findmonster();
		}
		else if(strcmp(move, "west") == 0 && map[currentroom].west >= 0){
			currentroom = map[currentroom].west;
			findmonster();
		}
		else{
			printf("Can't go that way!\n");
		}
	}
	else if(move == NULL && monsterhere != 1){
		printf("\n*You haven't specified a direction.\n\n");
	}
	else{
		printf("\n*Can't escape until the monster is defeated!\n\n");
	}
}

int attack(){
	if(!monsterhere){
		printf("\n  There is no monster here to attack!\n");
	}
	else{
		int monsterdamage = rand()%player.strength;
		monster.health -= monsterdamage;
		printf("\n*You did %d points of damage!\n", monsterdamage);
		if(monster.health <= 0){
			monsterhere = 0;
			points++;
			printf("*You killed the monster!\n\n");
		}
		else{
			int playerdamage = rand()%monster.strength;
			player.health -= playerdamage;
			printf("*The monster did %d points of damage!\n\n", playerdamage);
			if(player.health <= 0){
				printf("The monster has beaten you! GAME OVER\n");
				if(points == 1)
					printf("You killed 1 monster.\n");
				else
					printf("You killed %d monsters.\n", points);				
				return 0;
			}
		}
	}
	return 1;
}

void get(){
	if(move != NULL){
		if(strcmp(move, "potion") == 0){
			if(strcmp(player.inventory[1].name, "") == 0){
				strcpy(player.inventory[1].name, "potion");
				strcpy(map[currentroom].floor.name, "");
			}
			else{
				printf("\n*Your hands are full.\n\n");
			}
		}
	}
}

void use(){
	if(move != NULL){
		if(strcmp(move, "potion") == 0 && strcmp(player.inventory[1].name, "potion") == 0){
				strcpy(player.inventory[1].name, "");
				if((player.health += 15) > player.max){
					player.health = player.max;
				}
		}
	}
}

void status(){
    printf("You are in the %s.\n", map[currentroom].name);
    if(strcmp(map[currentroom].floor.name, "potion") == 0){
			printf("There is a potion on the floor.\n");
		}
		printf("-------------------\n");
		printf("Right hand: [%s]\nLeft hand: [%s]\n", player.inventory[0].name, player.inventory[1].name);
		if(monsterhere){
			printf("There is a monster in the room.\n");	
			printf("-------------------\n");
			printf("Monster health: %d/%d Strength: %d\nPlayer health: %d/%d Strength: %d\n", monster.health, monster.max, monster.strength, player.health, player.max, player.strength);
			printf("-------------------\n");
    }
		else{
			printf("-------------------\n");
			printf("Player health: %d/%d Strength: %d\n", player.health, player.max, player.strength);
			printf("-------------------\n");
		}
}