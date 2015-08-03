fn divided_by(x : i32, y : i32) -> bool {
    x % y == 0 
}

pub fn is_leap_year(year : i32) -> bool { 
    divided_by(year, 4) && (!divided_by(year, 100) || divided_by(year, 400))
}
