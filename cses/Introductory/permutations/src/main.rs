/*
A permutation of integers 1,2,…,n is called beautiful if there are no adjacent elements whose difference is 1.

Given n, construct a beautiful permutation if such a permutation exists.
 
INPUT:

The only input line has an integer n.

OUTPUT:

Print a beautiful permutation of integers 1,2,…,n. If there are several solutions, you may print any of them.
If there are no solutions, print "NO SOLUTION".ode.
 
CONSTRAINTS:

1 <= n <= 10^6

EXAMPLE:

Input:

5

Output:

4 2 5 3 1

TEST HERE:

https://cses.fi/problemset/task/1070/

*/

use std::io;
use std::collections::VecDeque;

fn read_input() -> String {
	let mut user_input = String::new();
	let stdin = io::stdin();
	stdin.read_line(&mut user_input).expect("Failed");
	
	user_input
}

fn find_permutations(n: u32) {
	match n {
		1 => {
			print!("{}", n);
		}

		2 | 3  => {
			println!("NO SOLUTION");
		} 

		_ => {
			let range: Vec<u32> = (1..=n).collect();
			let mut result: VecDeque<u32> = VecDeque::new();

			match n%2 {
				1 => {
					result.push_back(range[(n / 2) as usize]);

					for i in 0..(n/2) {
						result.push_back(range[i as usize]);
						result.push_back(range[(n - i - 1) as usize]);
					}
				}

				_ => {
					for i in 0..(n/2 - 1) {
						result.push_back(range[i as usize]);
						result.push_back(range[(n - i - 1) as usize]);
					}

					result.push_back(range[(n/2 - 1) as usize]);
					result.push_front(range[((n/2)) as usize]);
				}
				
			}
			
			for element in result {
				print!("{} ", element);
			}
		}
	}
}

fn main() {
	let n = read_input().trim().parse::<u32>().unwrap();
    find_permutations(n);
}
