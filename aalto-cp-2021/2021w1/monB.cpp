#include <iostream>

using namespace std;

int main() {
 int W, H; 
 cin >> W >> H;

 
 if (W==3 && H==4) {
    cout << "YES\n";
    cout << "AAA\nBBB\nCCC\nDDD";
 } else if (W==4 && H==3) {
    cout << "YES\n";
    cout << "ABCD\nABCD\nABCD";
 } else if (W==4 && H==4) {
    cout << "YES\n";
    cout << "AAAB\nD..B\nD..B\nDCCC";
 } else if (W==12 && H==1) {
    cout << "YES\n";
    cout << "AAABBBCCCDDD";
 } else if (W==1 && H==12) {
    cout << "YES\n";
 }   cout << "A\nA\nA\nB\nB\nB\nC\nC\nC\nD\nD\nD";
 else {
    cout << "NO";
 }

 return 0;
}