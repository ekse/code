extern crate crypto;
extern crate rustc_serialize;

use crypto::md5::Md5;
use crypto::digest::Digest;
use rustc_serialize::hex::ToHex;

fn main() {
    let mut md5 = Md5::new();
    let mut md5_hash = [0u8; 16];
    let mut i = 0;
    let key = "iwrupvqb";
    loop {
        let attempt = format!("{}{}", key, i);
        if i % 100000 == 0 {
            println!("Trying {}...", attempt);
        }
        md5.input(attempt.as_bytes());
        md5.result(&mut md5_hash);

        /* 5 zeroes
        if md5_hash[0] == 0 && md5_hash[1] == 0 && md5_hash[2] >> 4 == 0 {
            break;
        }
        */
        if md5_hash[0] == 0 && md5_hash[1] == 0 && md5_hash[2] == 0 {
            break;
        }

        i += 1;
        md5.reset();
    }

    println!("MD5 : {} i : {}", md5_hash.to_hex(), i);
}
