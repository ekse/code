fn sort_string(s : &str) -> String {
    let mut sorted : Vec<char> = s.chars().collect();
    sorted.sort();
    
    let mut out : String = String::with_capacity(sorted.len());
    for c in sorted {
        out.push(c);
    }
    
    out
}

fn lowercase(s : &str) -> String {
    
    let mut out = String::with_capacity(s.len());
    for c in s.chars() {
        for lower in c.to_lowercase() {
            out.push(lower);
        }
    }
    
    out
    
}


pub fn anagrams_for<'a>(word: &str, inputs: &[&'a str]) -> Vec<&'a str> {
    let mut result : Vec<&str> = vec![];
   
    let lowercase_word = lowercase(word);
    let sorted_word = sort_string(&lowercase_word);

    for input in inputs {
        let lowercase_input = lowercase(input);
        if lowercase_word == lowercase_input {
            continue;
        }
        let sorted_input = sort_string(&lowercase_input);
        if sorted_word == sorted_input {
            result.push(input);
        }
    }

    result
}
