/*
Given a string, your task is to reorder its letters in such a way that it becomes a palindrome
(i.e., it reads the same forwards and backwards).
 
INPUT:

The only input line has a string of length n consisting of characters A–Z.

OUTPUT:

Print a palindrome consisting of the characters of the original string.
You may print any valid solution.
If there are no solutions, print "NO SOLUTION".
 
CONSTRAINTS:

1 <= n <= 10^6

EXAMPLE:

Input:

AAAACACBA

Output:

AACABACAA

SOLUTION:

Create a collection of <Key, Value> type where Key is the letter and value
is its frequency of occurence. The string is a palindrome if and only if 
the number of keys with frequency less than or equal to one is at most one.

TEST HERE:

https://cses.fi/problemset/task/1755/

*/

use std::io;
use std::collections::HashMap;

fn read_input() -> String {
	let mut user_input = String::new();
	let stdin = io::stdin();
	stdin.read_line(&mut user_input).expect("Failed");
	
	user_input
}

fn count_letters(input: &str) -> HashMap<char, u32> {
	let mut bucket: HashMap<char, u32> = HashMap::new();

	for c in input.chars() {
		match c {
			'\n' => { break; }
			_ => { *bucket.entry(c).or_insert(0) += 1; }
		}
	}

	bucket
}

fn split_letters_by_parity(bucket: &HashMap<char, u32>) -> (Vec<(char, u32)>, Vec<(char, u32)>) {
	let mut odd = Vec::new();
	let mut even = Vec::new();

	for (key, value) in bucket {
		match value % 2 {
			1 => { odd.push((*key, *value)); }
			_ => { even.push((*key, *value)); }
		}

	}

	(odd, even)
}

fn find_solution(odd: &Vec<(char, u32)>, even: &Vec<(char, u32)>) -> String {
	let mut result = String::new();

	match odd.len() {
		0 | 1 => {
			for (key, value) in even {
				let substring = (0..*value/2).map(|_| *key).collect::<String>();
				result.push_str(&substring);
			}

			let second_half = result.chars().rev().collect::<String>();

			if let Some((key, value)) = odd.get(0) {
				let middle_part = (0..*value).map(|_| *key).collect::<String>();
				result.push_str(&middle_part);
			}

			result.push_str(&second_half);
		}
	

		_ => {
			result.push_str(&"NO SOLUTION".to_string());
		}
	}

	result
}

fn solve() -> String {
	let input = read_input();

	let bucket = count_letters(&input);

	let (odd, even) = split_letters_by_parity(&bucket);

	find_solution(&odd, &even)
}

fn main() {
    println!("{}", solve());
}
