#![feature(plugin)]
#![plugin(clippy)]

extern crate threadpool;

use std::collections::HashMap;
use std::sync::mpsc;
use threadpool::ThreadPool;

pub type Histogram = HashMap<char, usize>;

fn count_letters(text : &str) -> Histogram {
    let mut letters = HashMap::new();
    for c in text.chars().filter(|c| c.is_alphabetic()) {
        *letters.entry(c.to_lowercase().next().unwrap()).or_insert(0) += 1;
    }
    letters
}

fn merge_histograms(a : &mut Histogram, b : &Histogram ) {
    for (k,v) in b.iter() {
        *a.entry(*k).or_insert(0) += *v;
    }
}

pub fn frequency(texts : &[&str], workers : usize) -> Histogram {
    let pool = ThreadPool::new(workers);
    let mut letters = HashMap::new();
    let (tx, rx) = mpsc::channel();

    let mut nb_texts = 0;
    for text in texts {
        let tx = tx.clone();
        let data = text.to_string();
        pool.execute(move || { 
            tx.send(count_letters(&data));
        });
        nb_texts += 1;
    }

    for _ in 0..nb_texts { 
        let text_letters = rx.recv().unwrap();
        merge_histograms(&mut letters, &text_letters);
    }

    letters
}

