/*
There are n apples with known weights.
Your task is to divide the apples into two groups so that the difference between the weights of the groups is minimal.
 
INPUT:

The first input line has an integer n: the number of apples.

The next line has n integers p1,p2,…,pn: the weight of each apple.

OUTPUT:

Print one integer: the minimum difference between the weights of the groups.
 
CONSTRAINTS:

1 <= n <= 20
1 <= pi <= 10^9

EXAMPLE:

Input:

5
3 2 7 4 1

Output:

1

Explanation:
Group 1 has weights 2, 3 and 4 (total weight 9), and group 2 has weights 1 and 7 (total weight 8). 

SOLUTION:

Complete search: Let X be the full set, then represent X = A + X\A. 
Compute all sets A, X\A and find minimum difference.

VERIFY HERE:

https://cses.fi/problemset/task/1623/

*/

#[warn(unused_variables)]

use std::io;

trait Summable<T>
{
	fn sum(&self) -> T;
} 

impl Summable<i64> for Vec<i64>
{
	fn sum(&self) -> i64 {
		let mut res: i64 = 0;
		for element in self {
			res += *element;
		}
		res
	}
}

fn read_input() -> String {
	let mut user_input = String::new();
	let stdin = io::stdin();
	stdin.read_line(&mut user_input).expect("Failed");
	
	user_input
}

fn solve(n: u64, container: &mut Vec<i64>) -> i64 {
	let all_subsets = 1 << n;

	let mut min_diff = i64::MAX;
	let set_sum = container.sum();

	for i in 0..all_subsets {

		let mut subset: Vec<i64> = Vec::new();

		for j in 0..n { 
			if i&(1<<j) != 0 { 
				subset.push(container[j as usize]);
			}
		}

		let subset_sum1 = subset.sum();
		let subset_sum2 = set_sum - subset_sum1;
		let diff = subset_sum2 - subset_sum1;

		min_diff = if diff.abs() < min_diff { diff.abs() } else { min_diff };

	}

	min_diff
}

fn main() {
	let n = read_input().trim().parse::<u64>().unwrap();

	let mut apples = read_input()
		.split_whitespace()
    	.map(|x| x.parse::<i64>())
        .collect::<Result<Vec<i64>, _>>()
        .unwrap();

 	println!("{}", solve(n, &mut apples));
}
