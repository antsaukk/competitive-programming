#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <limits>

using namespace std;

struct point {
	point() = default;
	explicit point(double x, double y) : x_(x), y_(y) {}
	double x_; 
	double y_;

	double get_x() const { return x_; }
	double get_y() const { return y_; }

	bool operator < (const point&p) const {
		return x_ < p.get_x() || (x_ == p.get_x() && y_ < p.get_y());
	}
};

vector<point> convex_hull;
//vector<point> convex_hull_lower;
//set<point> convex_hull;

double inf = numeric_limits<double>::infinity();

double cross_product(const point& v, const point& u, const point& w) {
	return (u.get_x() - v.get_x()) * (w.get_y() - v.get_y()) - (u.get_y() - v.get_y()) * (w.get_x() - v.get_x());
}

ostream& operator<<(ostream& os, const point& p){
	os << p.get_x() << " " << p.get_y() << "\n";
	return os;
}

void display() {
	cout << convex_hull.size() << "\n";
	for(auto p : convex_hull)
		cout << p;
}

void build_convex_hull(vector<point>& points, size_t n, point& pinf) {
	if(n <= 3) {
		//for(auto p : points) 
		//	convex_hull.insert(p);
		convex_hull = points;
		return;
	}
	convex_hull.resize(2*n);
	//convex_hull_upper.resize(n, pinf);
	//convex_hull_lower.resize(n, pinf);

	sort(points.begin(), points.end());

	size_t j = 0;
	for (size_t i = 0; i < n; i++) {
		while (j >= 2 && cross_product(convex_hull[j-2], convex_hull[j-1], points[i]) <= 0) j--;
		convex_hull[j++] = points[i];
		//convex_hull_upper[j] = points[i];
		//j++;
	}

	size_t k = j + 1;
	for (size_t i = n - 1; i > 0; i--) {
		while (j >= k && cross_product(convex_hull[j-2], convex_hull[j-1], points[i-1]) <= 0) j--;
		convex_hull[j++] = points[i-1];
	}
	
	convex_hull.resize(j-1);
}

void get_data(vector<point>& points, size_t n) {
	double x, y;
	for(size_t i = 0; i < n; i++) {
		cin >> x >> y;
		points[i] = point{x, y};
	}
}

void desyncio(){
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
}

int main() {
	desyncio();

	size_t n;
	cin >> n;

	point pinf = point{inf, inf};
	vector<point> points(n, pinf);
	get_data(points, n);

	build_convex_hull(points, n, pinf);

	display();

	return 0;
}