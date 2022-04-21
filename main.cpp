#include<iostream>
using namespace std;


class DoublyLinkedNode{
    public:
    string data;
    DoublyLinkedNode *next;
    DoublyLinkedNode *prev;

    //constructor
    DoublyLinkedNode(string data, DoublyLinkedNode *next, DoublyLinkedNode *prev);
};
DoublyLinkedNode::DoublyLinkedNode(string data, DoublyLinkedNode *next, DoublyLinkedNode *prev){
        this->data = data;
        this->next = next;
        this->prev = prev;
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
    void deleteSongLocation();
    void deleteSongEnd();
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
        head = new DoublyLinkedNode(newSongName, NULL, NULL);
        current = head;

    }
    else{
        DoublyLinkedNode *newNode = new DoublyLinkedNode(newSongName, NULL, current);
        current->next = newNode;
        current = current->next;
        
    }
    totalSongs++;
}

void DoublyLinkedList::addSongBeginning(const string &newSongName){
    DoublyLinkedNode *newNode = new DoublyLinkedNode(newSongName, head, NULL);
    head->prev = newNode;
    head = newNode;
    totalSongs++;

}

void DoublyLinkedList::addSongLocation(const string &newSongName, int position){
    DoublyLinkedNode *newNode = new DoublyLinkedNode(newSongName, NULL, NULL); //seting up NULL for now
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



int main(){
    DoublyLinkedList *testPlaylist = new DoublyLinkedList();
    testPlaylist->addSong("Song1");
    testPlaylist->addSong("Song2");
    testPlaylist->addSongBeginning("Song start");
    testPlaylist->addSongLocation("Song in between", 2);

}
