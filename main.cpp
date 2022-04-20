#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<fstream>

using namespace std;

struct node
{
    char song_name[100];
    struct node *next;
    struct node *prev;
}*top, *temp, *top1;

void convertToFile(char a[]){
    fstream f1; //fstream helps us both read and write to files
    f1.open("playlist.txt",ios::out|ios::app); //out helps us open file for output operations and app for adding content to current file
    f1<<a<<endl;
    f1.close();//Closing the file
};
void addNode(struct node*temp1)
{
    char user_song[100];
    while (temp1->next !=NULL)//Traverse the whole LL to add a node in the end
    {
        temp1 = temp1->next;

    }
    temp1->next = (struct node*)malloc(sizeof(struct node)); //a node pointer gets memory allocated equivalent to size of node
    
    temp1->prev = temp1;
    temp1 = temp1->next;
    cout<<"\nEnter Song-  ";
    cin>>user_song;
    strcpy(temp1->song_name, user_song);
    convertToFile(user_song);
    temp1->next = NULL;

};
void addFile(struct node*temp1, string user_song){
    while(temp1->next!=NULL){
        temp1 = temp1->next;
    }

    temp1->next = (struct node*)malloc(sizeof(struct node));
    temp1->prev = temp1;
    temp1 = temp1->next;
    strcpy(temp1->song_name, user_song.c_str()); //c_str converts the usersong to c type string
    temp1->next = NULL;
}

int main(){
    char song[100];
    struct node *start,*hold;
    start=(struct node *) malloc(sizeof(struct node));
    cout<<"**WELCOME**"<<endl;

    cout<<"Enter your playlist name-  "<<endl;
    cout<<"Replace speces with _"<<endl;

}