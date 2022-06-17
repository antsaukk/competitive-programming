#include <iostream>
#include <string>

using namespace std;

int main() {
 string next; 
 int rooms = 1; 

 cin >> next;

 if (next == "E") {
    next = "EW";
    while(next == "EW") {
        rooms++; 
        cout << "E" << endl;
        cin >> next;
    }
    cout << rooms << endl;
    return 0;
 } 

 if (next == "W") {
    next = "EW";
    while(next == "EW") {
        rooms++; 
        cout << "W" << endl;
        cin >> next;
    }
    cout << rooms << endl;
    return 0;
 } 


 if (next == "EW") {
    int steps_left = 0; 
    while(next == "EW") {
        rooms++;
        steps_left++;
        cout << "E" << endl;
        cin >> next;
    }
    while (steps_left!=0)  {
        steps_left--;
        cout << "W" << endl;
        cin >> next;
    }
    next = "EW";
    while(next == "EW") {
        rooms++;
        cout << "W" << endl;
        cin >> next;
    }
    cout << rooms << endl;
    return 0;
 }


 return 0;
}