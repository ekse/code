use std::collections::HashMap;

pub fn word_count(text : &str) -> HashMap<String, u32> {
    let mut words : HashMap<String, u32> = HashMap::new();
    
    for word in text.split(|c : char| !c.is_alphanumeric()) {
        if word.is_empty() {
            continue
        }
        
        let lowercase_word = word.to_lowercase();
        *words.entry(lowercase_word).or_insert(0) += 1
    }
    
    words
}
