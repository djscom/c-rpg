#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "crpg.h"

extern char *ptr;
extern struct Player player;
extern struct Rooms map[];

void init(){
	FILE *init;
	char *line;
	char read;
	size_t len;
	int i = -1;
	
	system("clear");

	//Parse rooms.map into map struct array 
	init = fopen("rooms.map", "r");
	
	while ((read = getline(&line, &len, init)) != -1) {
		char *ptr = strtok(line, " ");
		char *value;
		value = strtok(NULL, "\n");

		if(strcmp(ptr, "name") == 0){
			i++;
			strcpy(map[i].name, value);
			int roll = rand()%5;
			if(roll==0){
				strcpy(map[i].floor.name, "potion");
			}
		}else if(strcmp(ptr, "north") == 0){
			map[i].north = atoi(value);
		}else if(strcmp(ptr, "south") == 0){
			map[i].south = atoi(value);
		}else if(strcmp(ptr, "east") == 0){
			map[i].east = atoi(value);				
		}else if(strcmp(ptr, "west") == 0){
			map[i].west = atoi(value);
		}else if(strcmp(ptr, "danger") == 0){
			map[i].danger = atoi(value);
		}
	}

	//Setup Player
	srand(time(NULL));
	player.max = rand()%50 + 10;
	player.health = player.max;
	player.strength = rand()%10 + 10;
	strcpy(player.inventory[0].name, "Sword");
	strcpy(player.inventory[1].name, "");
}