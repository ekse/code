extern crate serde_json;

use std::io;
use std::io::Read;
use std::fs::File;
use serde_json::Value;

#[test]
fn test_json_add_all_numbers() {
    assert_eq!(json_add_all_numbers(&serde_json::from_str("{\"a\":2,\"b\":4}").unwrap()),
               6);
    assert_eq!(json_add_all_numbers(&serde_json::from_str("{\"a\":{\"b\":4},\"c\":-1}").unwrap()),
               3);
    assert_eq!(json_add_all_numbers(&serde_json::from_str("{\"a\":[-1,1]}").unwrap()),
               0);
}

fn json_add_all_numbers(data: &Value) -> i64 {
    let mut total = 0;
    
    if data.is_array() {
        for x in data.as_array().unwrap() {
            total += json_add_all_numbers(x);
        }
    } else if data.is_object() {
        for x in data.as_object().unwrap().values() {
        total += json_add_all_numbers(x);
        }
    } else {
        match data {
            &Value::I64(v) => total += v,
            &Value::U64(v) => total += v as i64,
            &Value::String(ref s) => (),
            ref v => println!("ignored value : {:?}", v),
        }
    }
    
    total
}

fn main() {
    let mut f = File::open("data/input.txt").expect("failed to open file");
    let mut buffer = String::new();
    let obj = serde_json::from_reader(f).unwrap();
    println!("Total : {}", json_add_all_numbers(&obj));
}
