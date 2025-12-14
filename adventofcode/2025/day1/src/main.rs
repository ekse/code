#[derive(PartialEq, Debug)]
enum Direction {
    Left,
    Right
}

struct Lock {
    position: i32
}

impl Lock {
    pub fn new() -> Lock {
        Lock{position: 50}
    }

    /// Rotate the lock and return the new position.
    pub fn rotate(&mut self, direction: &Direction, count: i32) -> i32 {
        if *direction == Direction::Right {
            self.position = (self.position + count) % 100;
        } else {
            let mut position = self.position - count;
            while position < 0 {
                position = 100 - position.abs();
            }
            self.position = position;
        }

        assert!(self.position >= 0 || self.position <= 99);
        self.position
    }
}

fn main() {
    let input = std::fs::read_to_string("input.txt").unwrap();   

    let mut lock = Lock::new();
    let mut times_at_zero = 0;

    for line in input.lines() {

        let direction = match line.chars().nth(0).unwrap() {
            'L' => Direction::Left,
            'R' => Direction::Right,
            _ => panic!("Invalid direction")
        };

        let count = line.get(1..).unwrap().parse::<i32>().unwrap();
        let position = lock.rotate(&direction, count);
        println!("direction: {:?} count: {} position: {}", direction, count, position);
        
        if position == 0
        {
            times_at_zero += 1;
        }
    } 
    
    println!("times_at_zero: {}", times_at_zero);
}
