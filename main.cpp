#include <bits/stdc++.h>
#include <iomanip>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <stack>
#include <chrono>
#include <thread>
#include <random>

using namespace std;

void displayClock(int songlen, int seconds)
{
    cout <<setfill(' ') <<setw(9) <<"Song PLaying\n";
    cout <<"| " <<setfill('0') <<setw(2) <<seconds<<"/"<<songlen <<" sec |" <<endl;
    cout <<setfill(' ') <<setw(9) <<"-----\n";
}

void timer(int songLen)

{
    int seconds = 0;
    while (seconds<songLen) {
        displayClock(songLen, seconds);
        sleep(1);
        seconds++;
    }
}

int generateRandomInteger(){
    std::random_device rd;     // only used once to initialise (seed) engine
    std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
    std::uniform_int_distribution<int> uni(1,9); // guaranteed unbiased
    auto random_integer = uni(rng);
    return random_integer;

}

void shuffle_array(int arr[], int n)
{
    // To obtain a time-based seed
    unsigned seed = generateRandomInteger();
    shuffle(arr, arr + n,
            default_random_engine(seed));
 
}

class DoublyLinkedNode{
    public:
    string data;
    DoublyLinkedNode *next;
    DoublyLinkedNode *prev;
    int duration;

    //constructor
    DoublyLinkedNode(string data, DoublyLinkedNode *next, DoublyLinkedNode *prev, int duration);
};

DoublyLinkedNode::DoublyLinkedNode(string data, DoublyLinkedNode *next, DoublyLinkedNode *prev, int duration){
        this->data = data;
        this->next = next;
        this->prev = prev;
        this->duration = duration;
}

class DoublyLinkedList{
    protected:

    DoublyLinkedNode *current;
    DoublyLinkedNode *head;
    DoublyLinkedNode *tail;
    int totalSongs;
    stack<string> st;
    queue<string> qu;

    public:
    DoublyLinkedList();
    void addSong(const string &newSongName);
    void addSong(const string &newSongName, int dur);
    void printAll();
    void getCurrentSong();
    void addSongBeginning(const string &newSongName);
    void addSongBeginning(const string &newSongName, int duration);
    void addSongLocation(const string &newSongName, int position);
    void addSongLocation(const string &newSongName, int position, int duration);
    void deleteSongBeginning();
    void deleteSongLocation(int position);
    void deleteSongEnd();
    void getTotalSong();
    void playPlaylist();
    void playCurrentSong();
    void playSongPosition(int position);
    void lastPlayed();
    DoublyLinkedList* shufflePlaylist();
    void sharePlaylist();
    void orderAddition();
};

DoublyLinkedList::DoublyLinkedList(){
    
        head = NULL;
        tail = NULL;
        totalSongs = 0;

};

void DoublyLinkedList::getCurrentSong(){
    cout<<current->data<<endl; //Get the song where current pointer is
}

void DoublyLinkedList::addSong(const string &newSongName){
    if(totalSongs==0){
        head = new DoublyLinkedNode(newSongName, NULL, NULL, generateRandomInteger());
        current = head;
        //Case when first song is being added, need to do it at head
    }
    else{
        DoublyLinkedNode *newNode = new DoublyLinkedNode(newSongName, NULL, current, generateRandomInteger());
        current->next = newNode;
        tail = newNode;
        current = current->next;
        //When a song is already present, just add one more node after current
    }
    qu.push(newSongName);
    totalSongs++;
    
}

void DoublyLinkedList::addSong(const string &newSongName, int dur){
    //Overloaded function when user also inputs duration
    if(totalSongs==0){
        head = new DoublyLinkedNode(newSongName, NULL, NULL, dur);
        current = head;

    }
    else{
        DoublyLinkedNode *newNode = new DoublyLinkedNode(newSongName, NULL, current, dur);
        current->next = newNode;
        tail = newNode;
        current = current->next;
        
    }
    qu.push(newSongName);
    totalSongs++;
    
}

void DoublyLinkedList::addSongBeginning(const string &newSongName){
    //Adding the song at the beginning
    DoublyLinkedNode *newNode = new DoublyLinkedNode(newSongName, head, NULL, generateRandomInteger());
    head->prev = newNode ;
    head = newNode;
    totalSongs++;
    current = newNode;
    qu.push(newSongName);  
}

void DoublyLinkedList::addSongBeginning(const string &newSongName, int duration){
    //Overloaded Function
    DoublyLinkedNode *newNode = new DoublyLinkedNode(newSongName, head, NULL, duration);
    head->prev = newNode;
    head = newNode;
    totalSongs++;
    current = newNode;
    qu.push(newSongName);
    
}

void DoublyLinkedList::addSongLocation(const string &newSongName, int position){
    //Adding sing at a position specified by the user
    DoublyLinkedNode *newNode = new DoublyLinkedNode(newSongName, NULL, NULL, generateRandomInteger()); //seting up NULL for now
    if(position <0){
        cout<<"Position should be >=0"<<endl;
        return;
    }
    if(position>totalSongs){
        cout<<"Position specified is out of Bounds"<<endl;
        return;
    }
    else if (position == 0)//basically new node is head
    {
        //Using the function to add song at the beginning itself
        addSongBeginning(newSongName);
    }
    else{
        DoublyLinkedNode*temp = head;
        for(int i = 0; i < position-1; i++){//Traversing thriugh the list to the location where we need to add a node
            if(temp != NULL)
                temp = temp->next;
            if(temp == NULL){
                cout<<"Position entered is greater then current length of linked list"<<endl;
            }

        }

        if(temp != NULL){
            totalSongs++;
            qu.push(newSongName);
            if(temp->next == NULL){//Edge case when the position specified is the last point
                temp->next = newNode;
                newNode->prev = temp;
                newNode->next = NULL;
            }
            else{
                temp->next->prev = newNode;
                newNode->next = temp->next;
                newNode->prev = temp;
                temp->next = newNode;
            }
            current = newNode;
            
        }
    }
}

void DoublyLinkedList::addSongLocation(const string &newSongName, int position, int duration){
    //Overloaded function
    DoublyLinkedNode *newNode = new DoublyLinkedNode(newSongName, NULL, NULL, duration); //seting up NULL for now
    if(position <0){
        cout<<"Position should be >=0"<<endl;
        return;
    }
    if(position>totalSongs){
        cout<<"Position specified is out of Bounds"<<endl;
        return;
    }
    else if (position == 0)//basically new node is head
    {
        addSongBeginning(newSongName, duration);

    }
    else{
        DoublyLinkedNode*temp = head;
        for(int i = 0; i < position-1; i++){//Maybe need to add a case to add node at end using this function
            if(temp != NULL)
                temp = temp->next;
            if(temp == NULL){
                cout<<"Position entered is greater then current length of linked list"<<endl;
            }

        }

        if(temp != NULL){
            totalSongs++;
            qu.push(newSongName);
            if(temp->next == NULL){
                temp->next = newNode;
                newNode->prev = temp;
                newNode->next = NULL;
            }
            else{
                temp->next->prev = newNode;
                newNode->next = temp->next;
                newNode->prev = temp;
                temp->next = newNode;
            }
            current = newNode;
            
        }
    }
}

void DoublyLinkedList::printAll(){
    //Traverse the list and print each name
    DoublyLinkedNode *temp = head;
    while (temp != NULL)
    {
        cout<<temp->data<<endl;
        temp = temp->next;
    }
    
}

void DoublyLinkedList::deleteSongBeginning(){
    //Deleting the song at the beginning using head itself
    DoublyLinkedNode* temp = head;
    head = head->next;
    head->prev = NULL;
    delete(temp);
    totalSongs--;
    cout<<"Song Deleted"<<endl;
}

void DoublyLinkedList::deleteSongEnd(){
    //Delete song at the end usig the tail
    DoublyLinkedNode* temp = tail;
    tail = tail->prev;
    tail->next = NULL;
    delete(temp);
    totalSongs--;
    cout<<"Song Deleted"<<endl;
}

void DoublyLinkedList::deleteSongLocation(int position){
    //Deleting the song at the location specefied by the user
    if(position <0){
        cout<<"Position should be >=0"<<endl;
        return;
    }
    if(position>totalSongs){
        cout<<"Position specified is greater than total Songs in playlist"<<endl;
        return;
    }
    else if (position == 0)
    {
        deleteSongBeginning();
    }
    else{
        DoublyLinkedNode*temp = head;
        for(int i = 0; i < position; i++){//Maybe need to add a case to add node at end using this function
            if(temp != NULL)
                temp = temp->next;
            if(temp == NULL){
                cout<<"Position entered is greater then current length of Playlist"<<endl;
            }
        }
        if(temp!= NULL){
            if(temp->next == NULL){
                temp->prev->next = NULL;
                tail->prev = temp->prev;
                delete(temp);
            } else{
            
            temp->next->prev = temp->prev;
            temp->prev->next = temp->next;
            delete(temp);
            }
            totalSongs--;
            cout<<"Song Deleted"<<endl;
        }
    }

}

void DoublyLinkedList::getTotalSong(){
    //Getting total number of sings using the protected parameter
    cout<<totalSongs<<endl;
}

void DoublyLinkedList::playCurrentSong(){
    //Playing song pointed by the current node
    if(current == NULL){
        cout<<"Playlist Over"<<endl;
    }
    else{
    cout<<current->data<<endl;
    timer(current->duration);
    st.push(current->data);
    current = current->next;

    }
}

void DoublyLinkedList::playPlaylist(){
    //Play the whole playlist by traversing through the doubly linked list
    DoublyLinkedNode* temp = head;
    while(temp != NULL){
        cout<<temp->data<<endl;
        timer(temp->duration);
        st.push(temp->data);
        temp = temp->next;
    }
}

void DoublyLinkedList::playSongPosition(int position){
    //Playing song at the position specified by the user
    if(position>totalSongs-1){
        cout<<"Greater than total number of songs in the playlist"<<endl;
        return;
    }
    else if (position<0)
    {
        cout<<"Position must be greater than 0"<<endl;
        return;
    }
    
    else{
        DoublyLinkedNode* temp = head;
        cout<<temp->data<<endl;
        for(int i =0; i<position;i++){
            temp = temp->next;
        }
        timer(temp->duration);
        st.push(temp->data);
    }

}

void DoublyLinkedList::lastPlayed(){
    //Getting the last played song from the top of the stack
    if(st.empty()){
        cout<<"No song played yet"<<endl;
        return;
    }
    cout<< st.top()<<endl;
}

DoublyLinkedList* DoublyLinkedList::shufflePlaylist(){
    int len[totalSongs];
    for(int i = 0; i<totalSongs;i++){
        len[i] = i;
    }
    shuffle_array(len, totalSongs);
    DoublyLinkedList *shuffledPlaylist = new DoublyLinkedList();
    DoublyLinkedNode *temp = head;
    for(int i = 0; i<totalSongs;i++){
        temp = head;
        int current = len[i];
        for(int j =0; j<current;j++){ 
            temp = temp->next;
        }
        shuffledPlaylist->addSong(temp->data, temp->duration);
    }
    return shuffledPlaylist;
}

void DoublyLinkedList::orderAddition(){
    fstream fout;
    fout.open("Order_of_Addition.csv", ios::out);
    
    for(int i = 0; i<totalSongs; i++){
        string current = qu.front();
        fout<<current<<"\n";
        qu.pop();
        qu.push(current);
    }
    fout.close();
}

void DoublyLinkedList::sharePlaylist(){
    DoublyLinkedNode* temp = head;
    fstream fout;
    fout.open("Sharable_File.csv", ios::out);
    for(int i = 0; i<totalSongs; i++){
        fout<<temp->data<<","<<temp->duration<<"\n";
        temp = temp->next;


    }
    fout.close();
}

void printChoices(){
    cout<<"Please enter one of the following choices:\n";
    cout<<"1 : Add Song\n";
    cout<<"2 : Add song with specified duration\n";
    cout<<"3 : Add Song at beginning\n";
    cout<<"4 : Add Song at beginning with specified duration\n";
    cout<<"5 : Add Song at a particular position\n";
    cout<<"6 : Add Song at a particular position with specified duration\n";
    cout<<"7 : Delete Song at Beginning\n";
    cout<<"8 : Delete Song at End\n";
    cout<<"9 : Delete Song at a Specified Position\n";
    cout<<"10 : Get Total Number of Songs in the Playlist\n";
    cout<<"11 : Get Current Song in the Playlist\n";
    cout<<"12 : Play Current Song\n";
    cout<<"13 : Play Song at a specefic Position\n";
    cout<<"14 : Play whole playlist\n";
    cout<<"15 : Get last played Song\n";
    cout<<"16 : Play Shuffled playlist\n";
    cout<<"17 : Order in which songs were added\n";
    cout<<"18 : Share Playlist\n";
    cout<<"19 : Print whole Playlist\n";
    cout<<"20 : Exit\n";

}

int main(){
    DoublyLinkedList List;
    int choice = 0;
    string songName;
    int duration;
    int position;

    printChoices();
    while(choice != 20){
        cin>>choice;
        switch(choice){
            case 1:{
                cout<<"Enter Songname"<<endl;
                cin>>songName;
                List.addSong(songName);
                cout<<"Song Added"<<endl;

                break;
            }
            case 2:{
                cout<<"Enter Songname"<<endl;
                cin>>songName;
                cout<<"Enter Duration"<<endl;
                cin>>duration;
                List.addSong(songName, duration);
                cout<<"Song Added"<<endl;

                break;
            }
            case 3:
                cout<<"Enter Songname"<<endl;
                cin>>songName;
                List.addSongBeginning(songName);
                cout<<"Song Added"<<endl;

                break;
            case 4:
                cout<<"Enter Songname"<<endl;
                cin>>songName;
                cout<<"Enter Duration"<<endl;
                cin>>duration;
                List.addSongBeginning(songName, duration);
                cout<<"Song Added"<<endl;

                break;
            case 5:
                cout<<"Enter Songname"<<endl;
                cin>>songName;
                cout<<"Enter Position"<<endl;
                cin>>position;
                List.addSongLocation(songName, position);
                cout<<"Song Added"<<endl;
                break;
            case 6:
                cout<<"Enter Songname"<<endl;
                cin>>songName;
                cout<<"Enter Duration"<<endl;
                cin>>duration;
                cout<<"Enter Position"<<endl;
                cin>>position;
                List.addSongLocation(songName, position, duration);
                cout<<"Song Added"<<endl;
                break;
            case 7:
                List.deleteSongBeginning();
                break;
            case 8:
                List.deleteSongEnd();
                break;
            case 9:
                cout<<"Enter position of the song to be deleted"<<endl;
                cin>>position;
                List.deleteSongLocation(position);
                break;
            case 10:
                List.getTotalSong();
                break;
            case 11:
                List.getCurrentSong();
                break;
            case 12:
                List.playCurrentSong();
                break;
            case 13:
                cout<<"Enter position of the song to be played"<<endl;
                cin>>position;
                List.playSongPosition(position);
                break;
            case 14:
                List.playPlaylist();
                break;
            case 15:
                List.lastPlayed();
                break;
            case 16:
                List.shufflePlaylist()->playPlaylist();
                break;
            case 17:
                List.orderAddition();
                break;
            case 18:
                List.sharePlaylist();
                break;
            case 19:
                List.printAll();
                break;
            case 20:
                cout<<"Exiting the program"<<endl;
                break;
            default:
                cout<<"Not a valid entry!\n";
                break;
        }
    }
    
}