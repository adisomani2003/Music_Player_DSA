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

    public:
    DoublyLinkedList();
    void addSong(const string &newSongName);
    void printAll();
    void getCurrentSong();
    void addSongBeginning(const string &newSongName);
    void addSongLocation(const string &newSongName, int position);
    void deleteSongBeginning();
    void deleteSongLocation(int position);
    void deleteSongEnd();
    void getTotalSong();
    void playPlaylist();
    void playCurrentSong();
};

DoublyLinkedList::DoublyLinkedList(){
    
        head = NULL;
        tail = NULL;
        totalSongs = 0;

};

void DoublyLinkedList::getCurrentSong(){
    cout<<current->data<<endl;
}

void DoublyLinkedList::addSong(const string &newSongName){
    
    
    if(totalSongs==0){
        head = new DoublyLinkedNode(newSongName, NULL, NULL, generateRandomInteger());
        current = head;

    }
    else{
        DoublyLinkedNode *newNode = new DoublyLinkedNode(newSongName, NULL, current, generateRandomInteger());
        current->next = newNode;
        tail = newNode;
        current = current->next;
        
    }
    totalSongs++;
}

void DoublyLinkedList::addSongBeginning(const string &newSongName){
    DoublyLinkedNode *newNode = new DoublyLinkedNode(newSongName, head, NULL, generateRandomInteger());
    head->prev = newNode;
    head = newNode;
    totalSongs++;
    current = newNode;

}

void DoublyLinkedList::addSongLocation(const string &newSongName, int position){
    DoublyLinkedNode *newNode = new DoublyLinkedNode(newSongName, NULL, NULL, generateRandomInteger()); //seting up NULL for now
    if(position <0){
        cout<<"Position should be >=0"<<endl;

    }
    else if (position == 0)//basically new node is head
    {
        addSongBeginning(newSongName);

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

    DoublyLinkedNode *temp = head;
    while (temp != NULL)
    {
        cout<<temp->data<<endl;
        temp = temp->next;
    }
    
}

void DoublyLinkedList::deleteSongBeginning(){
    DoublyLinkedNode* temp = head;
    head = head->next;
    head->prev = NULL;
    delete(temp);
    totalSongs--;
}

void DoublyLinkedList::deleteSongEnd(){
    DoublyLinkedNode* temp = tail;
    tail = tail->prev;
    tail->next = NULL;
    delete(temp);
    totalSongs--;
}

void DoublyLinkedList::deleteSongLocation(int position){
    if(position <0){
        cout<<"Position should be >=0"<<endl;

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
        }
    }

}

void DoublyLinkedList::getTotalSong(){
    cout<<totalSongs<<endl;
}

void DoublyLinkedList::playCurrentSong(){
    if(current == NULL){
        cout<<"Playlist Over"<<endl;
        //Add a restart option here later
    }
    else{
    cout<<current->data<<endl;
    timer(current->duration);
    current = current->next;

    }
    
    
}

void DoublyLinkedList::playPlaylist(){

    DoublyLinkedNode* temp = head;
    while(temp != NULL){
        cout<<temp->data<<endl;
        timer(temp->duration);
        temp = temp->next;
    }
}

int main(){
    DoublyLinkedList *testPlaylist = new DoublyLinkedList();
    testPlaylist->addSong("Song1");
    testPlaylist->addSong("Song2");
    testPlaylist->addSongBeginning("Song start");
    testPlaylist->addSongLocation("Song in between", 1);
    testPlaylist->getCurrentSong();
    testPlaylist->printAll();

}
