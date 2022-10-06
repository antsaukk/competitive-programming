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
	//sort(apartments.begin(), apartments.end(), greater<T>());
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
 
		/*if (apartment_candidate==lower_price_ap && (abs(applicant - *apartment_candidate) <= k)) {
			matched++;
			lower_price_ap++;
			PrintOut
			continue;
		}*/
 
		if (apartment_candidate < apartments.end()) {
 
			auto lower_candidate = apartment_candidate;
 
			if ((abs(applicant - *lower_candidate) <= k)) {
				matched++; 
 
				while ((abs(applicant - *lower_candidate) <= k) && lower_candidate > lower_price_ap) { //here is the trouble
					lower_candidate--;
				}
 
				while (abs(applicant - *lower_candidate) > k) {
					lower_candidate++;
				}
 
				PrintOut("Appl and apart are matched 1: ");
				PrintOut(*(lower_candidate), " ");
				PrintOut(applicant, "\n");
 
				lower_price_ap = lower_candidate + 1;
				
			} else if (lower_candidate != lower_price_ap && (abs(applicant - *(lower_candidate-1)) <= k)) {
				matched++; 
				lower_candidate--;
 
				while ((abs(applicant - *lower_candidate) <= k) && lower_candidate > lower_price_ap) { //here is the trouble
					lower_candidate--;
				}
 
				while (abs(applicant - *lower_candidate) > k) {
					lower_candidate++;
				}
 
				PrintOut("Appl and apart are matched 2: ");
				PrintOut(*(lower_candidate), " ");
				PrintOut(applicant, "\n");
 
				lower_price_ap = lower_candidate + 1;
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
 
				PrintOut("Appl and apart are matched 4: ");
				PrintOut(*(lower_candidate), " ");
				PrintOut(applicant, "\n");
 
				lower_price_ap = lower_candidate + 1; // ?
 
			} else if (abs(*lower_candidate - applicant) <= k) {
					matched++;
					PrintOut("Appl and apart are matched 5: ");
					PrintOut(*(lower_candidate), " ");
					PrintOut(applicant, "\n");
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