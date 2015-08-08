use std::collections::HashMap;

fn lowercase(s : &str) -> String {
    
    let mut out = String::with_capacity(s.len());
    for c in s.chars() {
        for lower in c.to_lowercase() {
            out.push(lower);
        }
    }
    
    out
    
}

pub fn word_count(text : &str) -> HashMap<String, u32> {

    let mut words : HashMap<String, u32> = HashMap::new();
    
    for word in text.split(|c : char| !c.is_alphanumeric()) {

        if word.len() == 0 {
            continue
        }

        let lowercase_word = lowercase(word);

        if words.contains_key(&lowercase_word) {
           *words.get_mut(&lowercase_word).unwrap() += 1; 
        } else {
            words.insert(lowercase_word, 1);
        }
    }
    
    words
}
