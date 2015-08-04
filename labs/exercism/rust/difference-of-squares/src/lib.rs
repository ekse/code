
pub fn square_of_sum(n : i32) -> i32 {
    ((n * (n + 1)) / 2).pow(2)
}

pub fn sum_of_squares(n : i32) -> i32 {
    (n * (n + 1) * (2 * n + 1)) / 6
}

pub fn difference(n : i32) -> i32 {
    square_of_sum(n) - sum_of_squares(n)
}
