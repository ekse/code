use std::collections::HashMap;

pub struct School {
    years : HashMap<u32, Vec<String>>,
}

impl School {
    pub fn new() -> School {
        School{years : HashMap::new()}
    }

    pub fn add(&mut self, grade : u32, name : &str) {
        let mut names = self.years.entry(grade).or_insert(Vec::new());
        names.push(name.to_string());
        names.sort();
    }

    pub fn grades(&self) -> Vec<u32> {
        let mut out = Vec::new();
        for k in self.years.keys() {
            out.push(*k);
        }
        out.sort();
        out
    }

    pub fn grade(&self, year : u32) -> Option<&Vec<String>> {
        self.years.get(&year)
    }
}
