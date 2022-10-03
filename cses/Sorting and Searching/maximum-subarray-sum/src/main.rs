/*
Given an array of n integers, your task is to find the maximum sum of values in a contiguous, nonempty subarray.
 
INPUT:

The first input line has an integer n: the size of the array.

The second line has n integers x1,x2,…,xn: the array values.

OUTPUT:

Print one integer: the maximum subarray sum.
 
CONSTRAINTS:

1 <= n <= 2*10^5
-10^9 <= xi <= 10^9

EXAMPLE:

Input:

8
-1 3 -2 5 3 -5 2 2

Output:

9

VERIFY HERE:

https://cses.fi/problemset/task/1643

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

fn solve(array: &mut Vec<i64>) {
	let mut max_sum = std::i64::MIN;
	let mut current_sum = 0;

	for sum_k in array {
		current_sum = cmp::max(*sum_k, *sum_k + current_sum);
		max_sum = cmp::max(max_sum, current_sum);
	}

	println!("{:?}", max_sum);

} 

fn main() {
    let _ = read_input().trim().parse::<u64>().unwrap();

    let mut array = read_input()
		.split_whitespace()
    	.map(|x| x.parse::<i64>())
        .collect::<Result<Vec<i64>, _>>()
        .unwrap();

    solve(&mut array);
}
