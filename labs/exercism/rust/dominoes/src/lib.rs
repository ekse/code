
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

fn try_piece(piece: Domino,
             tried_pieces: Vec<Domino>,
             mut pieces: Vec<Domino>,
             mut chain: Vec<Domino>)
             -> Option<Vec<Domino>> {
    chain.push(piece);
    pieces.extend(tried_pieces.iter().cloned());
    add_to_chain(pieces, chain)

}

// returns a new chain containing all the pieces or returns None
fn add_to_chain(pieces: Vec<Domino>, chain: Vec<Domino>) -> Option<Vec<Domino>> {
    
    // no more pieces left to add, we have a domino chain.
    if pieces.len() == 0 {
        return Some(chain)
    }

    let mut tried_pieces : Vec<Domino> = Vec::new();
    let mut _pieces = pieces.clone();

    while _pieces.len() != 0 {
        let mut piece = _pieces.pop().unwrap();

        if chain.len() == 0 || chain.last().unwrap().1 == piece.0 {
            match try_piece(piece, tried_pieces.clone(), _pieces.clone(), chain.clone()) {
                Some(o) => return Some(o),
                _ => false,
            };
        }

        // try flipping the piece
        piece = (piece.1, piece.0);
        if chain.last().unwrap().1 == piece.0 {
            match try_piece(piece, tried_pieces.clone(), _pieces.clone() , chain.clone()) {
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

    add_to_chain(pieces.clone(), vec![])

}
