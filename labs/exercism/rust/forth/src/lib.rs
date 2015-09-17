use std::iter::Iterator;
use std::collections::HashMap;

pub type Value = i32;
pub type ForthResult = Result<(), Error>;

#[derive(Debug, PartialEq)]
pub enum Error {
    DivisionByZero,
    StackUnderflow,
    UnknownWord,
    InvalidWord,
}

pub fn is_number(s : &String) -> bool {
    match s.parse::<i32>() {
        Ok(_) => true,
        Err(_) => false,
    }
}

pub struct Forth {
    stack: Vec<i32>,
    words: HashMap<String, Vec<String>>,
}

impl Forth {
    pub fn new() -> Forth {
        Forth { stack: vec![], words : HashMap::new() }

    }

    pub fn format_stack(&self) -> String {
        let mut out = String::new();
        for v in self.stack.iter() {
            out.push_str(&(format!("{}", v)));
            out.push_str(" ");
        }
        out.pop();
        out
    }

    pub fn eval(&mut self, s: &'static str) -> ForthResult {
        let input = s.to_uppercase();
        let mut tokens : Vec<String> = vec![];
        for w in input.split_whitespace() {
            tokens.push(w.to_string());
        }
        self.eval_tokens(&tokens)
    }
    
    pub fn eval_tokens(&mut self, tokens : &Vec<String>) -> ForthResult {

        let mut it = tokens.iter(); 
        loop {
            // TODO: change this block to an if-let
            let t = it.next();
            if t == None {
               return Ok(());
            } 
             
            let mut w = t.unwrap();

            // handle operator +
            if w == "+" {
                if self.stack.len() < 2 {
                    return Err(Error::StackUnderflow);
                }

                let b = self.stack.pop().unwrap();
                let a = self.stack.pop().unwrap();
                self.stack.push(a + b);

            // handle operator -
            } else if w == "-" {
                if self.stack.len() < 2 {
                    return Err(Error::StackUnderflow);
                }

                let b = self.stack.pop().unwrap();
                let a = self.stack.pop().unwrap();
                self.stack.push(a - b);
            
            // handle operator *
            } else if w == "*" {
                if self.stack.len() < 2 {
                    return Err(Error::StackUnderflow);
                }

                let b = self.stack.pop().unwrap();
                let a = self.stack.pop().unwrap();
                self.stack.push(a * b);

            // handle operator /
            } else if w == "/" {
                if self.stack.len() < 2 {
                    return Err(Error::StackUnderflow);
                }

                let b = self.stack.pop().unwrap();
                let a = self.stack.pop().unwrap();

                if b == 0 {
                    return Err(Error::DivisionByZero);
                }

                self.stack.push(a / b);

            // handle defined words
            } else if self.words.contains_key(&w.to_string()) {
                let tokens = &self.words.get(&w.to_string()).unwrap().clone();
                match self.eval_tokens(tokens) {
                    Ok(_) => (),
                    Err(e) => return Err(e),
                }

            // handle DUP word
            } else if w == "DUP" {
                if self.stack.len() < 1 {
                    return Err(Error::StackUnderflow);
                }

                let a = self.stack.pop().unwrap();
                self.stack.push(a);
                self.stack.push(a);
        
            // handle DROP word
            } else if w == "DROP" {
                if self.stack.len() < 1 {
                    return Err(Error::StackUnderflow);
                }

                self.stack.pop();

            // handle SWAP word
            } else if w == "SWAP" {
                if self.stack.len() < 2 {
                    return Err(Error::StackUnderflow);
                }

                let b = self.stack.pop().unwrap();
                let a = self.stack.pop().unwrap();

                self.stack.push(b);
                self.stack.push(a);

            // handle OVER word
            } else if w == "OVER" {
                if self.stack.len() < 2 {
                    return Err(Error::StackUnderflow);
                }

                let b = self.stack.pop().unwrap();
                let a = self.stack.pop().unwrap();

                self.stack.push(a);
                self.stack.push(b);
                self.stack.push(a);
            
            // handle numbers
            } else if is_number(&w) {
                let v = w.parse::<i32>().unwrap();
                self.stack.push(v);
                
            // handle word definitions
            } else if w == ":" {
                let t = it.next();
                if t == None {
                    return Err(Error::InvalidWord);  
                }
                
                let word : String = t.unwrap().to_string();
                if is_number(&word) {
                    return Err(Error::InvalidWord);  
                }
                
                let mut definition : Vec<String> = vec![];
                
               loop {
                    let t = it.next();
                    if t == None {
                        return Err(Error::InvalidWord);  
                    }
                    
                    w = t.unwrap();

                    if w == ";" {
                        break;
                    }
                    
                    definition.push(w.to_string());
                }

                if definition.len() == 0 {
                    return Err(Error::InvalidWord);  
                }

                self.words.insert(word, definition);

            } else {
                return Err(Error::UnknownWord);        
            }
        }
    }
}
