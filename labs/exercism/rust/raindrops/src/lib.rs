pub fn raindrops(n : usize) -> String {
    let mut output = String::new();
    if n % 3 == 0 { output.push_str("Pling"); }
    if n % 5 == 0 { output.push_str("Plang"); }
    if n % 7 == 0 { output.push_str("Plong"); } 
    
    if output.len() == 0 {
        output = format!("{}", n);
    }

    output
}
