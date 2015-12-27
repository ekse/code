use std::io;
use std::io::prelude::*;
use std::fs::File;

#[test]
fn test_get_level() {
    assert_eq!(get_level(&"()()".to_string()), 0);
    assert_eq!(get_level(&"((".to_string()), 2);
    assert_eq!(get_level(&")))".to_string()), -3);
    assert_eq!(get_level(&"()(".to_string()), 1);
}

fn get_level(s: &String) -> (isize, usize) {
    let mut level = 0;
    let mut position = 1;
    let mut first_report = true;
    for c in s.chars() {
        match c {
            '(' => level += 1,
            ')' => level -= 1,
            _ => panic!("invalid character in string"),
        }

        if level < 0 && first_report {
            println!("Going negative at position {}", position);
            first_report = false;
        }

        position += 1

    }
    level
}

fn main() {
    let mut f = File::open("data/input.txt").expect("failed to open file");
    let mut buffer = String::new();

    f.read_to_string(&mut buffer).expect("failed to read input file");
    println!("Level : {}", get_level(&buffer));
}
