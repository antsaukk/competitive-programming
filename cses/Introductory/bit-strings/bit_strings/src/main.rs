/*
Your task is to calculate the number of bit strings of length n.

For example, if n=3, the correct answer is 8, because the possible bit strings are 000, 001, 010, 011, 100, 101, 110, and 111.
 
INPUT:

The only input line has an integer n.

OUTPUT:

Print the result modulo 10^9+7.
 
CONSTRAINTS:

1 <= n <= 10^9

EXAMPLE:

Input:

3

Output:

8

SOLUTION:

Clearly, the number of strings is 2^n. 
We compute them using modular exponentiation algorithm to avoid overflows

VERIFY HERE:

https://cses.fi/problemset/task/1617/
*/

use std::io;

fn read_input() -> String {
	let mut user_input = String::new();
	let stdin = io::stdin();
	stdin.read_line(&mut user_input).expect("Failed");
	user_input
}

// modular exponentiation
fn solve() -> u64 {
	let mut power: u32 = read_input().trim().parse::<u32>().unwrap();
	let mut solution = 1;
	let mut base = 2;

	let modulus = u64::pow(10, 9) + 7;

	while power > 0 {
		if power % 2 == 1 {
			solution = (solution * base) % modulus;
		}
		power = power >> 1;
		base = (base * base) % modulus;
	}

	solution
}

fn main() {
    println!("{}", solve());
}
