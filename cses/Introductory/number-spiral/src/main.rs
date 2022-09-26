/*
A number spiral is an infinite grid whose upper-left square has number 1.
Here are the first five layers of the spiral:

1  2  8  10 25
4  3  8  11 24
5  6  7  12 23
16 15 14 13 22
17 18 19 20 21

Your task is to find out the number in row y and column x.

INPUT:

The first input line contains an integer t: the number of tests.

After this, there are t lines, each containing integers y and x.

OUTPUT:

For each test, print the number in row y and column x.
 
CONSTRAINTS:

1 <= t <= 10^5
1 <= y, x <= 10^9

EXAMPLE:

Input:

3
2 3
1 1
4 2

Output:

8
1
15

TEST HERE:

https://cses.fi/problemset/task/1071/

*/

#[warn(unused_variables)]

use std::io;

fn read_input() -> String {
	let mut user_input = String::new();
	let stdin = io::stdin();
	stdin.read_line(&mut user_input).expect("Failed");
	
	user_input
}

fn solve_number_spiral(y: u64, x: u64) {
	match x >= y {

		true => {

			match x%2 {

				1 => {
					let mut answer = x*x;

					for _ in 1..y {
						answer -= 1;
					}

					print!("{}\n", answer);
				}

				_ => {
					let mut answer = x - 1; 
					answer = answer*answer;
					answer += 1;

					for _ in 1..y {
						answer += 1;
					}

					print!("{}\n", answer);
				}
			}
		}

		false => {

			match y%2 {

				0 => {
					let mut answer = y*y;

					for _ in 1..x {
						answer -= 1;
					}

					print!("{}\n", answer);
				}

				_ => {
					let mut answer = y - 1; 
					answer = answer*answer;
					answer += 1;

					for _ in 1..x {
						answer += 1;
					}

					print!("{}\n", answer);
				}
			}
		}
	}
}

fn main() {
    let t = read_input().trim().parse::<u64>().unwrap();

    for _ in 0..t {
    	let pair = read_input()
    	.split_whitespace()
    	.map(|x| x.parse::<u64>())
        .collect::<Result<Vec<u64>, _>>()
        .unwrap();

    	let y = pair[0];
    	let x = pair[1];

    	solve_number_spiral(y, x);
    }
}
