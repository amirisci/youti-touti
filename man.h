#include <stdio.h>
#include <stdlib.h>
#define true 1
#define zero 0

struct likers
{
    char* username;
    struct likers* next_liker;
};

struct posts
    {
        char* text;
        int Id ;
        int like;
        struct likers* liker;
        struct posts* nextpost;
    };
//-------------------------------------------------------//
struct  users
{    char* usernam;
     char* password ;
     int post_number;
    struct posts* post;
    struct users* nextuser;  
};
///---------///
int sizeoff(char *data){
    int size = 0 ;
    for ( int i = 0 ; data[i]; i++){
        size++;
    }
    return size;
}
///----------------------------------------------------///



//-----------------------------------------------------//
char* enter_post(char* data){
     data = (char*)realloc(NULL,sizeof(char));
    char temp[1] ={' '};
    int i = 0;
    *(data) = '0';
    while(true){
        i++;
        scanf("%c",temp);
        data = (char*)realloc(data , sizeof(char) * i);
        data[i -1] = '\0';
        switch(temp[0]){
            case '\n':
                return data;
                break;
            default:
                data[i-1] = temp[0];
                break;
        }
       
    }
   
}
///-----------------------------------------------------///
int file_account(struct users* head){
    struct users* temp = head;
    FILE* accounts = fopen("accounts.txt" ,"w");
    while(temp!=NULL){
        fputs(temp->usernam , accounts);
        fputs(" " , accounts);
        fputs(temp->password , accounts);
        fputs(" " , accounts);
        fprintf( accounts , "%d" ,temp->post_number);
        fputs("\n" ,accounts);
        temp = temp->nextuser;  
    }
    fclose(accounts);
}
///------------------------------------------------///
int file_post(struct users* head){
    struct users* temp =  head;
    FILE* posts = fopen("posts.txt" ,"w");
    while(temp!= NULL){
        struct posts* post = temp->post;
        while(post!= NULL){
            fputs(temp->usernam , posts);
            fputs(" " ,posts);
            fputs(post->text , posts);
            fputs(" " , posts);
            fprintf(posts , "%d" , post->like);
            fputs("\n" , posts);
            post = post->nextpost;
        }
        temp = temp->nextuser;
    }
    fclose(posts);
}
///-------------------------------------------------//
///this function scans username , password and all the things exept the commnads and posts
char* enter_data_in_link(char* data){
    data = (char*)realloc(NULL, sizeof(char));
    char* you;
    int i = 0;
    *(data) = '0';
    char temp[1] ={' '};
    while(true){
       
        scanf("%c",temp);
        i++;
        //printf("%c\n" , temp[0]);
        data = (char*)realloc(data , sizeof(char) * i);
        //printf("after reallocc\n");
        data[i - 1] = '\0';
        switch(temp[0]){
            case '\n':
            //printf("i found \\n\\ \n");
                return data;
                break;
            case '\0':
            // printf("i found 0\n");
                return data;
                break;
            case ' ':
            //printf("i found ' '\n ");
                return data;
                 break;
            default:
                data[i-1] = temp[0];
                break;
        }
        //printf("outside swich\n");
    }
    printf("outside true\n");
   
   
}

//----------------------------------------------------//
///this function will signup a new user, it reciieves usernme and password , it checks if there is no similar username in the app.
/// return 0 in case of similar usernames , 1 for successful addition
struct users* signup(struct users* head  ){
     char* data2 = (char*)malloc(sizeof(char));
    char* data= (char*)malloc(sizeof(char));
    int check = 0 ;
    struct users* failur = NULL;
    struct users* newone = (struct users*)malloc(sizeof(struct users));
    newone->usernam = enter_data_in_link(data);
    newone->password= enter_data_in_link(data2);
    newone->post_number = 0;
    free(data);
    free(data2);
    struct users* temp = head;
    while(temp!= NULL){
        int size= sizeoff(newone->usernam)>sizeoff(temp->usernam)?sizeoff(newone->usernam):sizeoff(temp->usernam);
        for ( int i = 0 ; i < size ; i++){
            if( newone->usernam[i]==temp->usernam[i]){
                check ++;
            }
        }
        if ( check == size){
            printf("choose another username !\n");
            return NULL;
        }
        check = 0;
        temp = temp->nextuser;
    }

        if(head == NULL){
            head = newone;
            head->nextuser = NULL;
            head->post = NULL;
            return head;
                }
        else{
            newone->nextuser = head->nextuser;
            head->nextuser = newone;
            newone->post = NULL;
            return head;
            }
   
}
//---------------------------------------------------//
struct users* login(struct users* head){
    char* data = (char*)malloc(sizeof(char));
     char* data2 = (char*)malloc(sizeof(char));
    
    struct users* temp;
    temp =  head;
    char* username ;
    char* password ;
    int what=0;
    username = enter_data_in_link(data);
    
    password = enter_data_in_link(data2);
    free(data);
    free(data2);
   
    while (temp != NULL)
    {
        int size = sizeoff(username)> sizeoff(temp->usernam) ?sizeoff(username):sizeoff(temp->usernam);
        for(int i = 0 ; i < size ; i++){
            if( temp->usernam[i] == username[i]){
                what++;
            }
        }
        if( what == size){///iT found the username , now check thepassword
            
            int size2 = sizeoff(password)> sizeoff(temp->password)?sizeoff(password):sizeoff(temp->password);
            what = 0;
            for ( int i = 0 ; i < size2 ; i++){
                if ( password[i] == temp->password[i]){
                    what ++;
                }
            }
                if( what == size2 ){///the correct password
                
                    return temp;
                }
                else{
                    printf("%s , wrong password!\n", username);
                    return NULL;///why this mf is not workign ?
                }
           
        }
        else{
            what = 0 ;
            temp = temp->nextuser;
        }
   
    }
    printf("no simillar username was found!\n");
    return NULL
    ;//anf also this one
   
}



//-------------------------------------------------//
int what_is_the_order(char* order){
int sum =0 ;
for (int i = 0 ; order[i]; i++){
    sum+= (int)order[i];
}
return  sum ;
}


//------------------------------------------------//
struct posts* post(struct users* head, struct users* current_user ){
    char* data =  (char*)malloc(sizeof(char));
    int check = 0 ;
    struct users* temp = head;
    while(temp!= NULL){
        int size= sizeoff(current_user->usernam)>sizeoff(temp->usernam)?sizeoff(current_user->usernam):sizeoff(temp->usernam);
        for ( int i = 0 ; i < size ; i++){
            if( current_user->usernam[i]==temp->usernam[i]){
                check ++;
            }
        }
        if ( check == size){
            struct posts* newpost = (struct posts*)malloc(sizeof(struct posts));
            //struct likers* meme = (struct likers*)malloc(sizeof(struct likers));
            //meme = newpost->liker;
            if(current_user->post == NULL){
                current_user->post = newpost;
                current_user->post_number ++;
                newpost->nextpost =NULL;
                
                newpost->text = enter_post(data);
                
                free(data);
                newpost->Id = 1;
                newpost->like = 0;
                
                newpost->liker = NULL;

            }
            else{////post function , when user has already had a post!///es funktionirt nicht
                int id= 2 ;
                struct posts* temp ;
                temp = current_user->post;
                current_user->post_number ++;
                for(; temp->nextpost != NULL;){
                    temp = temp->nextpost;
                    id ++;
                }

                temp->nextpost = newpost;
                newpost->nextpost = NULL;
                newpost->text = enter_post(data);
                free(data);
               
                newpost->Id = id;
                newpost->like = 0;
                newpost->nextpost = NULL;
                
               newpost->liker = NULL;
            }
            return newpost;
            printf("%s" ,current_user->post->text );
        }
        check = 0 ;
        temp = temp->nextuser;
    }
    printf(" no user\n");
    return 0;
}
///--------------------------------//try this body :)
int deletee(struct users* current_user){
    char* data = (char*)malloc(sizeof(char));
    char* id = enter_data_in_link(data);
    free(data);
    struct posts* temp;
    temp = current_user->post;
    if( id[0] - 48 == 1){
        current_user->post = temp->nextpost;
        current_user->post_number--;
        free(temp);
        return 1;
    }
    else{
    while(temp != NULL){
        if( temp->Id == (id[0] - 48)){
            struct posts* pre = current_user->post;
            while (pre != NULL)
            {
             if(pre->nextpost = temp){
                pre->nextpost = temp->nextpost;
                printf("%s\n",pre->text);
                printf("%s\n", temp->text);
                current_user->post_number--;
                free(temp);
                printf("post deleted\n");
                return 1;
             }
             pre = pre->nextpost;
            }
        }
        temp = temp->nextpost;
    }}
    printf("invalid post ID\n");
    return 1;
}
////----------------------------//
int like(struct users* haed , struct users* current_user){
    int what =0;
    char* data = (char*)malloc(sizeof(char));
    char* data2 = (char*)malloc(sizeof(char));
    char* username = enter_data_in_link(data);
    char* id = enter_data_in_link(data2);
    free(data);
    free(data2);
    struct users* temp = haed;

while( true){///first  it wants to find the user
    int size = sizeoff(username)> sizeoff(temp->usernam) ?sizeoff(username):sizeoff(temp->usernam);
        for(int i = 0 ; i < size ; i++){
            if( temp->usernam[i] == username[i]){
                what++;
            }
        }
        if( what == size){//it  found the user
            struct posts* temp3 = temp->post;
            
            for(; temp3!= NULL;){
                if(temp3->Id == (int)(id[0])-48){
                    struct likers* temp1 = (struct likers*)malloc(sizeof(struct likers));
                    if(temp3->like == 0 ){
                    temp3->like++;
                    temp1->username = current_user->usernam;
                    temp1->next_liker = NULL;
                    temp3->liker = temp1;
                    printf("liked the post\n");
                    return 1;
                    }
                    struct likers* temp4;
                    temp4 =  temp3->liker ;
                    for(;temp4!= NULL;){
                        
                    int size = sizeoff(current_user->usernam)>sizeoff(temp4->username)?sizeoff(current_user->usernam):sizeoff(temp4->username);
                    
                    int check = 0;
                    for (int i = 0 ; i < size ; i++){
                        
                        if (current_user->usernam[i] == temp4->username[i]){
                            check++;
                        }
                    }
                   
                    if ( check== size){
                        printf("you have previosly liked this post\n");
                        return 1;
                    }
                    check =0;
                    temp4=temp4->next_liker;
                    }
                    struct likers* likee = (struct likers*)malloc(sizeof(struct likers));
                    temp3->like++;
                    likee->next_liker = temp3->liker->next_liker;
                    temp3->liker->next_liker =  likee;
                    likee->username = current_user->usernam;
                    
                    return 1;
                }
                temp3 = temp3->nextpost;
            }
            printf("invalid post ID\n");
            return 1;
        }
        what = 0;
        temp = temp->nextuser;
}
printf("invalid username\n");
return 1 ;

}
////-----------------------------------///
int info(struct users* head, struct users* current_user ){
    struct users* temp = head;
    int what =0 ;
    while( true){///first  it wants to find the user
    int size = sizeoff(current_user->usernam)> sizeoff(temp->usernam) ?sizeoff(current_user->usernam):sizeoff(temp->usernam);
        for(int i = 0 ; i < size ; i++){
            if( temp->usernam[i] == current_user->usernam[i]){
                what++;
            }
        }
        if( what == size){//when it finds the user
             struct posts* temp1 = temp->post;
             while(temp1 != NULL){
                printf("post ID:%d\n" , temp1->Id);
                printf("likes:%d\n"  ,temp1->like);
                printf("%s\n\n" , temp1->text);
                temp1= temp1->nextpost;
             }
             return 1;
           

        }
        what = 0 ;
        temp = temp->nextuser;
   
    }
    printf("error!\n");
    return 1;
}
////-----------------------------------------//
int search(struct users* head ){
    char* username;
    char* data = (char*)malloc(sizeof(char));
    username = enter_data_in_link(data);
    free(data);

    struct users* temp = head;
    int what =0 ;
    while( true){///first  it wants to find the user
    int size = sizeoff(username)> sizeoff(temp->usernam) ?sizeoff(username):sizeoff(temp->usernam);
        for(int i = 0 ; i < size ; i++){
            if( temp->usernam[i] == username[i]){
                what++;
            }
        }
        if( what == size){///when i found the user name
            printf("username: %s\n" ,temp->usernam);
            struct posts* temp1;
            temp1 = temp->post;
            while(temp1 != NULL){
                printf("postID:%d\n" , temp1->Id);
                printf("likes:%d\n" , temp1->like);
                printf("%s\n\n" , temp1->text);
                temp1 = temp1->nextpost;
            }
            return 1;
        }
        what = 0 ;
        temp = temp->nextuser;
    }
    printf("no user was found!\n");
    return 1;
}