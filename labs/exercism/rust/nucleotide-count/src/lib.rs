use std::collections::HashMap;

pub fn count(e : char, s : &str ) -> usize {
    s.chars().filter(|&c| c == e).count() 
}

pub fn nucleotide_counts(s : &str) -> HashMap<char, usize> {
    let mut result = HashMap::new();
    result.insert('A', count('A', s));
    result.insert('T', count('T', s));
    result.insert('C', count('C', s));
    result.insert('G', count('G', s));
    result
}

