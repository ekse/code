pub fn hamming_distance(a : &str, b: &str) -> u32 {
    
    // the tests assume a and be of same length

    let mut differences = 0;
    
    let mut it_a = a.chars();
    let mut it_b = b.chars();
    for i in 0 .. a.len() {
        if it_a.next().unwrap() != it_b.next().unwrap() {
            differences += 1
        }
    }

    differences
}
