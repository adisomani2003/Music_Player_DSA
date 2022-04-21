#include <iomanip>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

int seconds = 0;

void displayClock(int songlen)
{
    cout <<setfill(' ') <<setw(9) <<"Song PLaying\n";
    cout <<"| " <<setfill('0') <<setw(2) <<seconds<<"/"<<songlen <<" sec |" <<endl;
    cout <<setfill(' ') <<setw(9) <<"-----\n";
}

void timer(int songLen)

{
    int time = 0;
    while (time<songLen) {
        displayClock(songLen);
        sleep(1);
        seconds++;
        time = seconds;

    }

}

int main()

{
    timer(10);
    return 0;
}