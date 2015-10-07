use std::collections::HashMap;

pub type Domino = (usize, usize);

fn all_number_occurrences_are_even(input: &Vec<Domino>) -> bool {

    let mut occurrences : HashMap<usize, usize> = HashMap::new();

    for domino in input {
        *occurrences.entry(domino.0).or_insert(0) += 1;
        *occurrences.entry(domino.1).or_insert(0) += 1;
    }
    
    occurrences.values().all(|&v| v % 2 == 0)
}

// returns a new chain containing all the pieces or returns None
fn add_to_chain(pieces: &Vec<Domino>, chain: &Vec<Domino>) -> Option<Vec<Domino>> {
    
    // no more pieces left to add, we have a domino chain.
    if pieces.is_empty() {
        return Some(chain.clone())
    }

    let mut tried_pieces : Vec<Domino> = Vec::new();
    let mut new_pieces = pieces.clone();

    while !new_pieces.is_empty() {
        let mut piece = new_pieces.pop().unwrap();

        if chain.is_empty() || chain.last().unwrap().1 == piece.0 || chain.last().unwrap().1 == piece.1 {
            if !chain.is_empty() && chain.last().unwrap().1 == piece.1 {
                piece = (piece.1, piece.0) // flip the piece
            }
           
            let mut candidate_chain = chain.clone();
            candidate_chain.push(piece);
            let mut candidate_pieces = new_pieces.clone();
            candidate_pieces.extend(tried_pieces.iter().cloned());
            if let Some(found_chain) = add_to_chain(&candidate_pieces, &candidate_chain) {
                return Some(found_chain);
            };
        }

        tried_pieces.push(piece);
    }

    return None
}

pub fn chain(pieces: &Vec<Domino>) -> Option<Vec<Domino>> {

    if pieces.is_empty() {
        return Some(Vec::new())
    }

    // count occurrences of each number, if we have an odd occurence count
    // then there is no possible domino chain.
    if !all_number_occurrences_are_even(pieces) {
        return None
    }

    add_to_chain(&pieces, &vec![])
}
