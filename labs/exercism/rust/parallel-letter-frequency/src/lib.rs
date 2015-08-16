use std::collections::HashMap;
use std::thread;

pub type Histogram = HashMap<char, usize>;

fn count_letters(text : &str) -> Histogram {
    let mut letters = HashMap::new();
    for c in text.chars() {
        if c.is_alphabetic() {
            *letters.entry(c.to_lowercase().next().unwrap()).or_insert(0) += 1;
        }
    }
    letters
}

fn merge_histograms(a : &mut Histogram, b : &Histogram ) {
    for (k,v) in b.iter() {
        *a.entry(*k).or_insert(0) += *v;
    }
}

pub fn frequency(texts : &[&str], works : usize) -> Histogram {
    let mut letters = HashMap::new();
    
    for text in texts {
        let text_letters = count_letters(text);
        merge_histograms(&mut letters, &text_letters);
    }
    letters
}

