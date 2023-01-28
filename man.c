#include <stdio.h>
#include "man.h"

int main(){
    struct posts* postt=NULL;
    const int constt = 1;
    struct users* currnet_user = NULL;
    struct users* head = NULL;
    char *jerk[1];
   
    char*useranme = (char*)malloc(sizeof(char*)* 30);
    //system("cls");
    printf("welocome to YoutiTouti!\n");
    printf("already a user? log in .....\n");
    printf("NO account yet ?sign up.....\n ");
    while(1){
    while(currnet_user == NULL ){
        char* order = (char*)malloc(sizeof(char*)* 50);
        scanf("%s" , order);
        //system("cls");
        scanf("%c", jerk);
        switch(what_is_the_order(order)){
            case 662 ://signup
                head = signup(head);
                file_account(head);
                //system("cls");
                free(order);
                if ( head!= NULL){
                    printf("you signed up successfully :)!\n"); }
            break;

            case 537://login function
                //system("cls");
                //system("cls");
                free(order);
                currnet_user = login(head);
                break;

            default: printf("sorry , invalid order !\ntry again [login \\ signup]\n");
            free(order);
            break;
            }    
        }
    while(currnet_user!= NULL){//now user can start other orders
    char* order = (char*)malloc(sizeof(char*)* 50);
   
    printf("*--------------------------------------------------*\n");
    printf("YoutiTouti            %s         \n", currnet_user->usernam);
    printf("*--------------------------------------------------*\n");
        scanf("%s",order);
        scanf("%c",jerk);
        //system("cls");
        switch(what_is_the_order(order)){
            case 666:
                currnet_user = NULL;
                free(order);
                printf("Hope see u soon!\n");
                break;
            case 454://post

                free(order);
                postt =post(head , currnet_user);
                file_account(head);
                file_post(head);
                printf("username:%s\n" ,currnet_user->usernam);
                printf("likes:%d\n",postt->like);
                printf("post ID:%d\n" , postt->Id);
                printf("%s\n" ,postt->text );
                break;
            case 421:///like
             like(head , currnet_user);
             free(order);
             file_post(head);
                break;
            case 428:
                 info(head , currnet_user);
                 free(order);
                 break;
            default:
               printf("invalid order!\n");
               free(order);
               break;

            case 630:
                search(head);
                free(order);
                break;
            case 627:
             deletee(currnet_user);
             file_post(head);
             free(order);
             break;
        }

    }    
    }
}

