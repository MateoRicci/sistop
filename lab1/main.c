#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main(){
    char user_commnad[100];
    char commnad[100];
    char flags[100];
    int j;
    bool c_check = false;


    while(strcmp(user_commnad, "exit()") != 0){
        j = 0;
        printf("$: ");
        scanf("%s", user_commnad);
        printf("len: %ld\n", strlen(user_commnad));
        for(int i = 0; i < strlen(user_commnad);i++){
            if(user_commnad[i] != ' ' && c_check == false){
                commnad[i] = user_commnad[i];
                printf("i: %d\n", i);
            }
            else{
                c_check = true;
            }

        }
        printf("command: %s\n", commnad);
    }

    return 0;
}