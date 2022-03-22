/*
There is a large hotel, and n customers will arrive soon. Each customer wants to have a single room.

You know each customer's arrival and departure day. 
Two customers can stay in the same room if the departure day of the first customer is earlier 
than the arrival day of the second customer.

What is the minimum number of rooms that are needed to accommodate all customers?
And how can the rooms be allocated?

INPUT:
The first input line contains an integer n: the number of customers.

Then there are n lines, each of which describes one customer.
Each line has two integers a and b: the arrival and departure day.

OUTPUT:
Print first an integer k: the minimum number of rooms required.

After that, print a line that contains the room number of each customer in the same order as in the input.
The rooms are numbered 1,2,…,k. You can print any valid solution.

CONSTRAINTS:
1 <= n <= 2*10^5
1 <= a, b <= 10^9
RESULT:
https://cses.fi/alon/result/3711416/

DISCLAIMER: 
Clearly note the most efficient solution, bur works nice within the constains 
and show some tricks-n-tips of C++
*/

#include <iostream>
#include <vector>
#include <set>
#include <tuple>
#include <algorithm>

#define ui64 uint64_t

using namespace std;

typedef tuple<size_t, size_t, size_t> Arrival;

template<typename T>
void display(T val) {
        cout << val;
}

template <typename T>
class Hotel {
public:
        explicit Hotel(size_t N) :
        size_(N),
        bookings_history_(N, 0u),
        arrivals_history(N)
        {
                for(size_t i = 1; i <= N; i++)
                        free_rooms.insert(i);
                init_arrivals();
        }

        /* a: arrival start time
           b: arrival end time
           i: order of arrival 

           record arrival times and sort in 
           increasing order.
           */
        void init_arrivals() {
                size_t a, b;
                for(size_t i = 0; i < get_size(); i++) {
                        cin >> a >> b;
                        arrivals_history[i] = make_tuple(a, b, i);
                }
                sort(arrivals_history.begin(), arrivals_history.end());
        }

        /* greedy algorithm:
                (1) take the arrival which has earliest start time: a
                (2) check the room with the customer having the earliest finish time: b
                (3) if it free (a > b), book the room 
                (4) otherwise, book the next available room
        */
        void compute_optimal_times() {
                auto arrival = arrivals_history[0];

                stays_duration_.insert({get<1>(arrival), 1});
                free_rooms.erase(1);
                increase_number_of_bookings();
                book(1, get<2>(arrival));
                for(size_t i = 1; i < get_size(); i++) {
                        auto arrival = arrivals_history[i];
                        if (get<0>(arrival) > stays_duration_.begin()->first) {
                                size_t room = stays_duration_.begin()->second;
                                stays_duration_.erase(stays_duration_.begin());
                                stays_duration_.insert({get<1>(arrival),room});
                                book(room, get<2>(arrival));
                        } else {
                                auto room = free_rooms.begin();
                                stays_duration_.insert({get<1>(arrival), *room});
                                free_rooms.erase(free_rooms.begin());
                                increase_number_of_bookings();
                                book(*room, get<2>(arrival));
                        }
                }
                
        }

        const void show_booking_history() const {
                display(minimal_bookings);
                display("\n");
                for(size_t i = 0; i < get_size(); i++) {
                        display(bookings_history_[i]);
                        display(" ");
                }
        }

        void increase_number_of_bookings() { 
                minimal_bookings++; 
        }

        void book(T room_number, size_t index) { 
                bookings_history_[index] = room_number;
        }

        const T get_size() const { return size_; }

private:
        T minimal_bookings = 0;
        T size_            = 0;
        set<pair<T, size_t>> stays_duration_;
        vector<T> bookings_history_;
        vector<Arrival> arrivals_history;
        set<T> free_rooms;
};

// untie std in/out to speed up computation
void desyncio() {
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr);
}

int main() {
        desyncio();

        ui64 n; 
        cin >> n;

        Hotel<ui64> hotel(n);
        hotel.compute_optimal_times();
        hotel.show_booking_history();

        return 0;
}