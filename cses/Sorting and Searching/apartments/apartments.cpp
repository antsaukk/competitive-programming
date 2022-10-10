/*
There are n applicants and m free apartments. Your task is to distribute the apartments so that as many applicants as possible will get an apartment.

Each applicant has a desired apartment size, and they will accept any apartment whose size is close enough to the desired size.
 
INPUT:
The first input line has three integers n, m, and k: the number of applicants, the number of apartments, and the maximum allowed difference.

The next line contains n integers a1,a2,…,an: the desired apartment size of each applicant.
If the desired size of an applicant is x, he or she will accept any apartment whose size is between x−k and x+k.

The last line contains m integers b1,b2,…,bm: the size of each apartment.

OUTPUT:

Print one integer: the number of applicants who will get an apartment.
 
CONSTRAINTS:
1 <= n,m <= 2*10^5
0 <= k <= 10^9
1 <= ai,bi <= 10^9

EXAMPLE:

Input:
4 3 5
60 45 80 60
30 60 75

Output:
2

VERIFY HERE:

https://cses.fi/problemset/task/1084/

*/
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstdlib>
 
#define READ(x) (cin >> (x))
 
using namespace std;
using big_int64 = int64_t;
 
inline void desyncio() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}
 
template <typename T>
void PrintOut(T value, string const& delimeter = "") {
	cout << value << delimeter;
}
 
template <typename T>
void ReadStream(vector<T>& container) {
	for (size_t i = 0; i < container.size(); i++) {
		T x; 
		READ(x);
 
		container[i] = x;
	}
}
 
template <typename T>
void solve(const size_t n, const T k, priority_queue<T>& applicants, vector<T>& apartments) {
	sort(apartments.begin(), apartments.end());
 
	size_t matched = 0;
 
	auto lower_price_ap = apartments.begin();
 
	for (size_t i = 0; i < n; i++) {
		T applicant = -applicants.top();
 
		/*PrintOut("Applicant: ");
		PrintOut(applicant, "\n");
 		
 		PrintOut("Searching: [");
 		PrintOut(*lower_price_ap, ", ");
 		PrintOut(*(apartments.end()-1));
 		PrintOut(")\n");*/
 
		auto apartment_candidate = lower_bound(lower_price_ap, apartments.end(), applicant);

 
		if (apartment_candidate < apartments.end()) {
 
			auto lower_candidate = apartment_candidate;
 
			if ((abs(applicant - *lower_candidate) <= k)) {
				matched++; 
 
				while ((abs(applicant - *lower_candidate) <= k) && lower_candidate > lower_price_ap) { 
					lower_candidate--;
				}
 
				while (abs(applicant - *lower_candidate) > k) {
					lower_candidate++;
				}
 
				/*PrintOut("Appl and apart are matched 1: ");
				PrintOut(*(lower_candidate), " ");
				PrintOut(applicant, "\n");*/
 
				lower_price_ap = lower_candidate + 1;

				if (lower_price_ap == apartments.end()) break;
				
			} else if (lower_candidate != lower_price_ap && (abs(applicant - *(lower_candidate-1)) <= k)) {
				matched++; 
				lower_candidate--;
 
				while ((abs(applicant - *lower_candidate) <= k) && lower_candidate > lower_price_ap) {
					lower_candidate--;
				}
 
				while (abs(applicant - *lower_candidate) > k) {
					lower_candidate++;
				}
 
				/*PrintOut("Appl and apart are matched 2: ");
				PrintOut(*(lower_candidate), " ");
				PrintOut(applicant, "\n");*/
 
				lower_price_ap = lower_candidate + 1;

				if (lower_price_ap == apartments.end()) break;
			}
 
		} else {
			auto lower_candidate = apartment_candidate-1;
 
			while ((abs(applicant - *lower_candidate) <= k) && lower_candidate > lower_price_ap) {
				lower_candidate--;
			}
 
			if (lower_candidate != apartment_candidate-1) {
 
				matched++;
				while (abs(applicant - *lower_candidate) > k) {
					lower_candidate++;
				}
 
				/*PrintOut("Appl and apart are matched 4: ");
				PrintOut(*(lower_candidate), " ");
				PrintOut(applicant, "\n");*/
 
				lower_price_ap = lower_candidate + 1; // ?

				if (lower_price_ap == apartments.end()) break;
 
			} else if (abs(*lower_candidate - applicant) <= k) {
					matched++;
					/*PrintOut("Appl and apart are matched 5: ");
					PrintOut(*(lower_candidate), " ");
					PrintOut(applicant, "\n");*/
					break;
					
			}
		}
		
		applicants.pop();
	}
 
	PrintOut(matched, "\n");
}
 
void run() {
	size_t n, m;
	READ(n);
	READ(m);
 
	big_int64 k;
	READ(k);
 
	vector<big_int64> applicants(n);
	ReadStream(applicants);
 
	priority_queue<big_int64> inlined_applicants;
	for (const auto& app : applicants)
		inlined_applicants.push(-app);
 
	vector<big_int64> apartments(m);
	ReadStream(apartments);
 
	solve(n, k, inlined_applicants, apartments);
}
 
int main() {
	desyncio();
 
	try {
		run();
	} catch (const invalid_argument& exception) {
		cerr << exception.what() << "\n";
		return -1;
	}
    
    return 0;
}