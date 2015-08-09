use std::collections::BTreeMap;

pub fn transform(input : &BTreeMap<i32, Vec<String>>) -> BTreeMap<String, i32> {
    let mut output = BTreeMap::new();

    for (k, v) in input {
        for s in v {
            output.insert(s.to_lowercase(), k.clone());
        }
    }

    output
}
