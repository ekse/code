use std::iter::Iterator;

pub type Value = i32;
pub type ForthResult = Result<(), Error>;

#[derive(Debug, PartialEq)]
pub enum Error {
    DivisionByZero,
    StackUnderflow,
    UnknownWord,
    InvalidWord,
}

pub struct Forth {
    stack: Vec<i32>,
}

impl Forth {
    pub fn new() -> Forth {
        Forth { stack: vec![] }

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
        let mut input = s.to_uppercase();
        input = input.chars().map(|c| {
            if c.is_alphanumeric() || "+-*/".find(c) != None {
                c
            } else {
                ' '
            }
        }).collect();


        for w in input.split_whitespace() {
            println!("w : {}", w);

            if w == "+" {
                if self.stack.len() < 2 {
                    return Err(Error::StackUnderflow);
                }

                let b = self.stack.pop().unwrap();
                let a = self.stack.pop().unwrap();
                self.stack.push(a + b);

            } else if w == "-" {
                if self.stack.len() < 2 {
                    return Err(Error::StackUnderflow);
                }

                let b = self.stack.pop().unwrap();
                let a = self.stack.pop().unwrap();
                self.stack.push(a - b);

            } else if w == "*" {
                if self.stack.len() < 2 {
                    return Err(Error::StackUnderflow);
                }

                let b = self.stack.pop().unwrap();
                let a = self.stack.pop().unwrap();
                self.stack.push(a * b);

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

            } else if w == "DUP" {
                if self.stack.len() < 1 {
                    return Err(Error::StackUnderflow);
                }

                let a = self.stack.pop().unwrap();
                self.stack.push(a);
                self.stack.push(a);

            } else if w == "DROP" {
                if self.stack.len() < 1 {
                    return Err(Error::StackUnderflow);
                }

                self.stack.pop();

            } else if w == "SWAP" {
                if self.stack.len() < 2 {
                    return Err(Error::StackUnderflow);
                }

                let b = self.stack.pop().unwrap();
                let a = self.stack.pop().unwrap();


                self.stack.push(b);
                self.stack.push(a);

            } else if w == "OVER" {
                if self.stack.len() < 2 {
                    return Err(Error::StackUnderflow);
                }

                let b = self.stack.pop().unwrap();
                let a = self.stack.pop().unwrap();


                self.stack.push(a);
                self.stack.push(b);
                self.stack.push(a);

            } else {
                let v = w.parse::<i32>().unwrap();
                self.stack.push(v);
            }
        }

        Ok(())
    }
}
