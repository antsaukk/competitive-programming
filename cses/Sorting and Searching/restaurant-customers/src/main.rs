/*
You are given the arrival and leaving times of n customers in a restaurant.

What was the maximum number of customers in the restaurant at any time?
 
INPUT:

The first input line has an integer n: the number of customers.

After this, there are n lines that describe the customers. Each line has two integers a and b: the arrival and leaving times of a customer.

You may assume that all arrival and leaving times are distinct.

OUTPUT:

Print one integer: the maximum number of customers.
 
CONSTRAINTS:

1 <= n <= 2*10^5
1 <= a <= b <= 10^9

EXAMPLE:

Input:

3
5 8
2 4
3 9

Output:

2

VERIFY HERE:

https://cses.fi/problemset/task/1619/

*/

#[warn(unused_variables)]

use std::io;
use std::cmp;

fn read_input() -> String {
	let mut user_input = String::new();
	let stdin = io::stdin();
	stdin.read_line(&mut user_input).expect("Failed");
	
	user_input
}

fn solve(times: &mut Vec<(i64, i64)>) {
	times.sort();

	let mut max_cust = 0;
	let mut cur_cust = 0;

	for (_, y) in times {
		cur_cust += *y;
		max_cust = cmp::max(max_cust, cur_cust);
	}

	println!("{:?}", max_cust);

} 

fn main() {
    let n = read_input().trim().parse::<u64>().unwrap();
    let mut times: Vec<(i64, i64)> = Vec::new();

    for _ in 0..n {
    	let pair = read_input().split_whitespace()
    	.map(|x| x.parse::<i64>())
        .collect::<Result<Vec<i64>, _>>()
        .unwrap();

        let a = pair[0];
        let b = pair[1];

    	times.push((a,1));
    	times.push((b,-1));
    }

    solve(&mut times);
}
