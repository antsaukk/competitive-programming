#[warn(unused_variables)]

use std::io;

fn read_input() -> String {
	let mut user_input = String::new();
	let stdin = io::stdin();
	stdin.read_line(&mut user_input).expect("Failed");
	
	user_input
}

fn empty_piles(mut a: u64, mut b: u64) {
	while a > 0 && b > 0 {
		if a > b {
			a -= 2;
			b -= 1;
		} else {
			a -= 1;
			b -= 2;
		}
	}

	if a==0 && b==0 {
		println!("YES");
	} else {
		println!("NO");
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

    	let a = pair[0];
    	let b = pair[1];

    	empty_piles(a, b);
    }
}
