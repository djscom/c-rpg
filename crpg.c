#include <stdio.h>
#include <string.h>
#include "crpg.h"

void instructions(){
	printf("\nReach the final room, and rescue the princess!\n");
	printf("\n-------------------\n");
	printf("Commands:\ngo [direction]\nget [item]\nuse [item]\nattack\n");
	printf("-------------------\n");
}

int currentroom = 0;
int monsterhere;
int points = 0;
char *move;

void init();

int main(){
	char command[100];

	init();
	instructions();
	findmonster();
	
	while(1){
		status();
		do{
			printf("\n> ");
			fgets(command, 100, stdin);
		}
		while(command[0] == '\n');

		char *ptr = strtok(command, " \n");
		move = strtok(NULL, "\n");

		if(strcmp(ptr, "go") == 0){
			go();
		}
		else if(strcmp(ptr, "get") == 0){
			get();
		}
		else if(strcmp(ptr, "use") == 0){
			use();
		}
		else if(strcmp(ptr, "attack") == 0){
			if(!attack())
				break;
		}
		else if(strcmp(ptr, "exit") == 0){
			break;
		}
		else{
			printf("Invalid command.\n");
		}
		if(win()){
			break;
		}
	}
	return 0;
}