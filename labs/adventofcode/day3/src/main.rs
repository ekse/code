use std::io::prelude::*;
use std::fs::File;
use std::collections::HashMap;

type Houses = HashMap<(isize, isize), usize>;

fn move_position(position: (isize, isize), move_x: isize, move_y: isize) -> (isize, isize) {
    let (mut x, mut y) = position;
    x += move_x;
    y += move_y;
    (x, y)
}

#[test]
fn test_parse_itinerary_part2() {
    let houses1 = parse_itinerary_part2(&"^v".to_string());
    assert_eq!(houses1.keys().count(), 3);
    let houses2 = parse_itinerary_part2(&"^>v<".to_string());
    assert_eq!(houses2.keys().count(), 3);
    let houses3 = parse_itinerary_part2(&"^v^v^v^v^v".to_string());
    assert_eq!(houses3.keys().count(), 11);
}

fn parse_itinerary_part2(s: &String) -> Houses {
    let mut houses = Houses::new();

    // Santa and RoboSanta always starts at (0,0)
    let mut turn = 0;
    let mut pos_santa = (0, 0);
    let mut pos_robosanta = (0, 0);
    *houses.entry(pos_santa).or_insert(0) = 1;
    *houses.entry(pos_robosanta).or_insert(0) += 1;

    for c in s.chars() {
        let position = if turn % 2 == 0 {
            &mut pos_santa
        } else {
            &mut pos_robosanta
        };

        match c {
            '>' => *position = move_position(*position, 1, 0),
            '<' => *position = move_position(*position, -1, 0),
            '^' => *position = move_position(*position, 0, 1),
            'v' => *position = move_position(*position, 0, -1),
            _ => panic!("unexpected character in input"),
        }

        *houses.entry(*position).or_insert(0) += 1;
        turn += 1;


    }

    houses
}

#[test]
fn test_parse_itinerary() {
    let houses1 = parse_itinerary(&">".to_string());
    assert_eq!(houses1.keys().count(), 2);
    let houses2 = parse_itinerary(&"^>v<".to_string());
    assert_eq!(houses2.keys().count(), 4);
    let houses3 = parse_itinerary(&"^v^v^v^v^v".to_string());
    assert_eq!(houses3.keys().count(), 2);
}

fn parse_itinerary(s: &String) -> Houses {
    let mut houses = Houses::new();

    // Santa always starts at (0,0)
    let mut position = (0, 0);
    *houses.entry(position).or_insert(0) = 1;

    for c in s.chars() {
        match c {
            '>' => position = move_position(position, 1, 0),
            '<' => position = move_position(position, -1, 0),
            '^' => position = move_position(position, 0, 1),
            'v' => position = move_position(position, 0, -1),
            _ => panic!("unexpected character in input"),
        }

        *houses.entry(position).or_insert(0) += 1;

    }

    houses
}

fn main() {
    let mut f = File::open("data/input.txt").expect("failed to open file");
    let mut buffer = String::new();

    f.read_to_string(&mut buffer).expect("failed to read input file");
    let houses = parse_itinerary(&buffer);
    println!("Houses visited : {}", houses.keys().count());

    let houses2 = parse_itinerary_part2(&buffer);
    println!("Houses visited (part2) : {}", houses2.keys().count());
}
