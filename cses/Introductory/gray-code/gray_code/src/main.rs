/*
A Gray code is a list of all 2^n bit strings of length n,
where any two successive strings differ in exactly one bit (i.e., their Hamming distance is one).

Your task is to create a Gray code for a given length n.
 
INPUT:

The only input line has an integer n.

OUTPUT:

Print 2^n lines that describe the Gray code.
You can print any valid solution.
 
CONSTRAINTS:

1 <= n <= 16

EXAMPLE:

Input:

2

Output:

00
01
11
10

SOLUTION:

For each n gray code is a matrix of the size (2^n, n).
Let y = 0..n-1 be the index of the column in this matrix. 
Then, for each y the values under indices 0..(2^n/2^y)/2 - 1
are zeros, and the values under indices (2^n/2^y)/2..(2^n/2^y) - 1 are ones.

00
01
1
1

Exploit this pattern to form left upper triagular part of the matrix and then
form the lower triagle by reflecting the upper half.

TEST HERE:

https://cses.fi/problemset/task/2205

*/

use std::io;

fn read_input() -> String {
	let mut user_input = String::new();
	let stdin = io::stdin();
	stdin.read_line(&mut user_input).expect("Failed");
	
	user_input
}

fn solve(n: u32, code_length: u32) -> Vec<char> { 

	let mut result = vec!['0'; (n * code_length) as usize]; 

	for i in 0..n {

		let upper_part = code_length / u32::pow(2, i);
		let half_of_upper_part = code_length / u32::pow(2, i+1);

		for j in 0..half_of_upper_part {
			let index = i + j * n;
			result[index as usize] = '0';
		}

		for j in half_of_upper_part..upper_part {
			let index = i + j * n;
			result[index as usize] = '1';
		}

		let lower_part = code_length / upper_part;

		for k in 1..lower_part {
			let mut push = upper_part * k;
			let mut pull = upper_part * k;

			let stop = push + upper_part;

			while pull > 0 && push < stop {

				pull -= 1;

				result[(i + push * n) as usize] = result[(i + pull * n) as usize];

				push += 1;
			}
		}
	}

	result
}

fn main() {
	let n = read_input().trim().parse::<u32>().unwrap();
	let code_length = u32::pow(2, n);

	let answer = solve(n, code_length);
	for y in 0..code_length {
		for x in 0..n {
			print!("{}", answer[(x + y * n) as usize]);
		}
		print!("\n");
	}
}
