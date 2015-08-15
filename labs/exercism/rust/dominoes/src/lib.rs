
use std::collections::HashMap;

pub type Domino = (usize, usize);

fn all_number_occurences_are_even(input: &Vec<Domino>) -> bool {

    let mut occurences : HashMap<usize, usize> = HashMap::new();

    for domino in input {
        *occurences.entry(domino.0).or_insert(0) += 1;
        *occurences.entry(domino.1).or_insert(0) += 1;
    }

    occurences.values().all(|&v| v % 2 == 0)

}

// returns a new chain containing all the pieces or returns None
fn add_to_chain(pieces: &Vec<Domino>, chain: &Vec<Domino>) -> Option<Vec<Domino>> {
    
    // no more pieces left to add, we have a domino chain.
    if pieces.len() == 0 {
        return Some(chain.clone())
    }

    let mut tried_pieces : Vec<Domino> = Vec::new();
    let mut new_pieces = pieces.clone();

    while new_pieces.len() != 0 {
        let mut piece = new_pieces.pop().unwrap();

        if chain.len() == 0 || chain.last().unwrap().1 == piece.0 || chain.last().unwrap().1 == piece.1 {
            if chain.len() != 0 && chain.last().unwrap().1 == piece.1 {
                piece = (piece.1, piece.0) // flip the piece
            }
           
            let mut new_chain = chain.clone();
            new_chain.push(piece);
            new_pieces.extend(tried_pieces.iter().cloned());
            match add_to_chain(&new_pieces, &new_chain) {
                Some(o) => return Some(o),
                _ => false,
            };
        }

        tried_pieces.push(piece);
    }

    return None

}

pub fn chain(pieces: &Vec<Domino>) -> Option<Vec<Domino>> {

    if pieces.len() == 0 {
        return Some(Vec::new())
    }

    // count occurences of each number, if we have an odd occurence count
    // then there is no possible domino chain.
    if !all_number_occurences_are_even(pieces) {
        return None
    }

    add_to_chain(&pieces, &vec![])

}
