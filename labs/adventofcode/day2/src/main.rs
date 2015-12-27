use std::io;
use std::io::prelude::*;
use std::fs::File;

fn smallest(a : usize, b : usize, c : usize) -> usize {
    let mut smallest = a;
    if b < smallest {
        smallest = b;
    }
    if c < smallest {
        smallest = c;
    }
    smallest
}

#[test]
fn test_ribbon_length() {
    assert_eq!(ribbon_length(2,3,4), 34);
    assert_eq!(ribbon_length(1,1,10), 14);
    
}

fn ribbon_length(length : usize, height : usize, width : usize) -> usize {
    let side_a = (length + width) * 2;
    let side_b = (width + height) * 2;
    let side_c = (height + length) * 2;
    let side_length = smallest(side_a, side_b, side_c);
    
    let bow_length = length * height * width;
    
    side_length + bow_length 
}


#[test]
fn test_paper_length() {
    assert_eq!(paper_length(1, 1, 10), 43);
    assert_eq!(paper_length(2, 3, 4), 58);
}

fn paper_length(length : usize, height: usize, width : usize) -> usize {
    let side_a = length * width;
    let side_b = width * height;
    let side_c = height * length;
    let needed_length = 2 * side_a + 2 * side_b + 2 * side_c;
    let extra_length = smallest(side_a, side_b, side_c);

    needed_length + extra_length
}

fn main() {
    let mut f = File::open("data/input.txt").expect("failed to open file");
    let mut buffer = String::new();

    f.read_to_string(&mut buffer).expect("failed to read input file");

    let mut total_paper_length = 0;
    let mut total_ribbon_length = 0;
    for line in buffer.lines() {
            let v : Vec<_> = line.split("x").collect();
            if v.len() != 3 {
                panic!("Invalid input : {}", line);
            }

            let l = v[0].parse::<usize>().expect("failed conversion");
            let h = v[1].parse::<usize>().expect("failed conversion");
            let w = v[2].parse::<usize>().expect("failed conversion");

            total_paper_length += paper_length(l, h, w);
            total_ribbon_length += ribbon_length(l, h, w);
    }

    println!("Needed paper length : {}", total_paper_length);
    println!("Needed ribbon length : {}", total_ribbon_length);
}
