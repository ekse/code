use std::collections::HashMap;

pub type Domino = (usize, usize);

fn all_number_occurences_are_even(input : &Vec<Domino>) -> bool {

    let mut occurences : HashMap<usize, usize> = HashMap::new();

    for domino in input {
        *occurences.entry(domino.0).or_insert(0) += 1; 
        *occurences.entry(domino.1).or_insert(0) += 1;
    }

    occurences.values().all(|&v| v % 2 == 0)
    
}

fn add_to_chain(pieces : Vec<Domino>, mut chain : Vec<Domino>) -> Option<Vec<Domino>> {
    
    println!("add_to_chain({:?},{:?})", pieces, chain);
    
    if pieces.len() == 0 {
        return Some(chain)
    }

    let mut tried_pieces : Vec<Domino> = Vec::new();
    let mut _pieces = pieces.clone();
    

    println!("_pieces.len() = {}", _pieces.len());
    while _pieces.len() != 0 {
        let mut piece = _pieces.pop().unwrap();
        println!("trying with piece : {:?}", piece); 

        if chain.len() == 0 || chain.last().unwrap().1 == piece.0 {
            chain.push(piece);
            let mut temp = _pieces.clone();
            temp.extend(tried_pieces.iter().cloned());
            match add_to_chain(temp, chain.clone()) {
                Some(o) => return Some(o),
                _ => false,
            };
        }
    
        // try flipping the piece
        piece = (piece.1, piece.0); 
        if chain.last().unwrap().1 == piece.0 {
            chain.push(piece);
            let mut temp = _pieces.clone();
            temp.extend(tried_pieces.iter().cloned());
            match add_to_chain(temp, chain.clone()) {
                Some(o) => return Some(o),
                _ => false,
            };
        }

        tried_pieces.push(piece);
    }

    return None
    
}

pub fn chain(pieces : &Vec<Domino>) -> Option<Vec<Domino>> {
    
    if pieces.len() == 0 {
        return Some(Vec::new())
    }

    // count occurences of each number, if we have an odd occurence count
    // then there is no possible domino chain.
    if !all_number_occurences_are_even(pieces) {
        println!("odd occurences");
        return None
    }

    add_to_chain(pieces.clone(), vec![])
    
}
