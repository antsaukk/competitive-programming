/*
You are given a list of n integers, and your task is to calculate the number of distinct values in the list.
 
INPUT:

The first input line has an integer n: the number of values.

The second line has n integers x1,x2,…,xn.

OUTPUT:

Print one integers: the number of distinct values.
 
CONSTRAINTS:

1 <= n <= 2*10^5
1 <= xi <= 10^9

EXAMPLE:

Input:

5
2 3 2 2 3

Output:

2

VERIFY HERE:

https://cses.fi/problemset/task/1621/

*/

#[warn(unused_variables)]

use std::io;
use std::collections::HashSet;

fn read_input() -> String {
	let mut user_input = String::new();
	let stdin = io::stdin();
	stdin.read_line(&mut user_input).expect("Failed");
	
	user_input
}

fn solve(numbers: &mut Vec<i64>) -> usize {
	let mut hashable_numbers = HashSet::new();

	for number in numbers{
		hashable_numbers.insert(*number);
	}

	hashable_numbers.len()
}

fn main() {
	let _ = read_input().trim().parse::<u64>().unwrap();

	let mut numbers = read_input()
		.split_whitespace()
    	.map(|x| x.parse::<i64>())
        .collect::<Result<Vec<i64>, _>>()
        .unwrap();

    println!("{}", solve(&mut numbers));
}
