#include <stdio.h>
extern int monsterhere, currentroom, points;

int win(){
    if(!monsterhere && currentroom == 6){
        if(points == 1)
            printf("You killed %d monster and you rescued the princess! YOU WIN\n", points);
        else
            printf("You killed %d monsters and you rescued the princess! YOU WIN\n", points);
        return 1;
    }
    return 0;
}