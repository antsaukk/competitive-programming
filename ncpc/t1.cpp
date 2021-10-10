#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int main() {
	double sKx, sKy, sOx, sOy, eKx, eKy, eOx, eOy; 

	cin >> sKx; 
	cin >> sKy;
	cin >> sOx; 
	cin >> sOy; 
	cin >> eKx;
	cin >> eKy; 
	cin >> eOx; 
	cin >> eOy;

	double res = max(hypot((sKx-sOx), (sKy-sOy)), hypot((eKx-eOx), (eKy-eOy)));
	cout << setprecision(11) << res;

	return 0;
}