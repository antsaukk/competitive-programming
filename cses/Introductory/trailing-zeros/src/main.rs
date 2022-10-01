/*
Your task is to calculate the number of trailing zeros in the factorial n!.

For example, 20!=2432902008176640000 and it has 4 trailing zeros.
 
INPUT:

The only input line has an integer n.

OUTPUT:

Print the number of trailing zeros in n!.
 
CONSTRAINTS:

1 <= n <= 10^9

EXAMPLE:

Input:

20

Output:

4

SOLUTION:



VERIFY HERE:

https://cses.fi/problemset/task/1618/

*/

#[warn(unused_variables)]

use std::io;

fn read_input() -> String {
	let mut user_input = String::new();
	let stdin = io::stdin();
	stdin.read_line(&mut user_input).expect("Failed");
	
	user_input
}

fn solve(n: u64) -> u64 {
	let mut answer = 0;
	let mut div = 5;

	while n/div > 0 {
		answer += n/div;
		div *= 5;
	}

	answer
}

fn main() {
	let n = read_input().trim().parse::<u64>().unwrap();

    println!("{}", solve(n));
}
