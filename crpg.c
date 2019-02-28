#include <stdio.h>
#include <string.h>
#include "crpg.h"

void instructions(){
	printf("\nReach the final room, and rescue the princess!\n");
	printf("\n-------------------\n");
	printf("Commands:\ngo [direction]\nget [item]\nattack\n");
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

		printf("\n> ");
		fgets(command, 100, stdin);
		char *ptr = strtok(command, " \n");
		move = strtok(NULL, "\n");

		if(strcmp(ptr, "go") == 0){
			go();
		}
		else if(strcmp(ptr, "get") == 0){
			printf("\n*Not implemented yet.\n\n");
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