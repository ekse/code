use std::collections::HashMap;

pub fn frequency(texts : &[&str], works : usize) -> HashMap<char, usize> {
    let mut letters = HashMap::new();
    for text in texts {
        for c in text.chars() {
            if c.is_alphabetic() {
                *letters.entry(c.to_lowercase().next().unwrap()).or_insert(0) += 1;
            }
        }
    }
    letters
}

