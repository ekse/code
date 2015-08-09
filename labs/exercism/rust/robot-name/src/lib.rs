extern crate rand;

use rand::Rng;

fn generate_name() -> String {
    let mut rng = rand::thread_rng();
    let letter: char = rng.gen_range(b'A', b'Z') as char;
    let number: char = rng.gen_range(b'0', b'9') as char;
    format!("{}{}{}{}{}", letter, letter, number, number, number)
}

pub struct Robot {
    name : String,
}

impl Robot {
    pub fn new() -> Robot {
        Robot{name : generate_name()}    
    }
    
    pub fn name<'a>(&'a self) -> &'a str {
        self.name.as_ref()
    }
    
    pub fn reset_name(&mut self) {
        self.name = generate_name()        
    }
}

