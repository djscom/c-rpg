#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

void instructions(){
	printf("\nReach Level 3, and rescue princess!\n");
}

struct Rooms{
	int north;
	int south;
	int east;
	int west;
	char name[100];
} map[5];

int currentroom = 0;
int j = 0;

void init();

int main(){
	system("clear");
	init();
	instructions();
	printf("\n-------------------\n");
	printf("Commands:\ngo [direction]\nget [item]\n");
	printf("-------------------\n");
	char command[100];
	char *move;
	
	while(1){
		printf("You are in the %s.\n", map[currentroom].name);
		printf("> ");
		fgets(command, 100, stdin);
		char *ptr = strtok(command, " \n");
		move = strtok(NULL, "\n");
		if(strcmp(ptr, "go") == 0){
			if(move != NULL){
				if(strcmp(move, "north") == 0 && map[currentroom].north >= 0){
					currentroom = map[currentroom].north;
				}
				else if(strcmp(move, "south") == 0 && map[currentroom].south >= 0){
					currentroom = map[currentroom].south;
				}
				else if(strcmp(move, "east") == 0 && map[currentroom].east >= 0){
					currentroom = map[currentroom].east;
				}
				else if(strcmp(move, "west") == 0 && map[currentroom].west >= 0){
					currentroom = map[currentroom].west;
				}
				else{
					printf("Can't go that way!\n");
				}
			}
		}
		else if(strcmp(ptr, "get") == 0){
			printf("You entered get!\n");
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
		}
	}
}
