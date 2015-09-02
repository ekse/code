enum Direction {
    Up,
    Down,
    Left,
    Right,
}

// I use signed values for Point so that negative values indicate
// that a point is outside the grid. It simplifies bound-checking.
#[derive(Debug, Clone, Copy)]
struct Point {
    x : isize,
    y : isize,
}

#[derive(Debug, Clone, Copy)]
struct Rectangle {
    a : Point,
    b : Point,
    c : Point,
    d : Point
}

#[derive(Debug)]
struct Grid {
    grid : Vec<char>,
    columns : usize,
    rows : usize,
}

impl Grid {

    fn from_string(lines : &Vec<&str>) -> Option<Grid> {
        
        if lines.len() == 0 || lines[0].len() == 0 {
            return None;
        }
        
        let nb_rows = lines.len();
        let nb_columns = lines[0].len();
        
        let mut grid : Vec<char> = Vec::with_capacity(nb_rows * nb_columns);
        for i in 0..nb_rows {
            if lines[i].len() != nb_columns {
                return None;
            }
            for c in lines[i].chars() {
                grid.push(c);
            }
        }

        let ret = Grid{grid: grid, columns : nb_columns, rows: nb_rows};
        Some(ret)

    }

    fn at_coords(&self, x : usize, y : usize) -> char {
        self.grid[y * self.columns + x]
    }
    
    fn at(&self, p : &Point) -> char {
        self.grid[(p.y as usize) * self.columns + (p.x as usize)]
    }

    fn is_inbounds(&self, p : &Point) -> bool {
        (p.x >= 0) && (p.y >= 0) && 
        ((p.y as usize) * self.columns + (p.x as usize)) < self.grid.len()
    }

    // returns true if we can move 1 step direction specified starting from the
    // point p.
    fn can_go_from(&self, direction : Direction, p: &Point) -> bool {
        match direction {
            Direction::Left  => { 
                let p = Point{x : p.x - 1, y : p.y};
                return self.is_inbounds(&p) && (self.at(&p) == '-' || self.at(&p) == '+');
            },
            Direction::Right =>  { 
                let p = Point{x : p.x + 1, y : p.y};
                return self.is_inbounds(&p) && (self.at(&p) == '-' || self.at(&p) == '+');
            },
            Direction::Up    => {
                let p = Point{x : p.x, y : p.y - 1};
                return self.is_inbounds(&p) && (self.at(&p) == '|' || self.at(&p) == '+');
            },
            Direction::Down  => {
                let p = Point{x : p.x, y : p.y + 1};
                return self.is_inbounds(&p) && (self.at(&p) == '|' || self.at(&p) == '+');
            },
        }
    }


    fn print(&self) {
        for y in 0..self.rows {
            for x in 0..self.columns { 
                print!("{}", self.at_coords(x,y))
            }
            println!("");
        }
    }
}


// return the list of rectangles that have 'point' in the the top-left corner
// and that are to the right side of 'point'.
fn rectangles_from_point(grid : &Grid, point : &Point) -> Vec<Rectangle> {
    let mut candidates : Vec<(Direction, Rectangle)> = Vec::new();
    let mut rectangles : Vec<Rectangle> = Vec::new();
    candidates.push((Direction::Right, 
                 Rectangle{
                   a : point.clone(), 
                   b : Point{x : -1, y : -1}, 
                   c : Point{x : -1, y : -1}, 
                   d : Point{x : -1, y : -1}}));

    while !candidates.is_empty() {
        let (direction, mut rect) = candidates.pop().unwrap();
        match direction {
            Direction::Right => {
                rect.b = rect.a.clone();
                rect.b.x += 1;
                
                while grid.can_go_from(Direction::Right, &rect.b) {
                    rect.b.x += 1;
                    if grid.at(&rect.b) == '+' && grid.can_go_from(Direction::Down, &rect.b) {
                        candidates.push((Direction::Down, rect.clone()));
                    }
                }
            },
            Direction::Down => {
                rect.c = rect.b.clone();
                rect.c.y += 1;
                
                while grid.can_go_from(Direction::Down, &rect.c) {
                    rect.c.y += 1;
                    if grid.at(&rect.c) == '+' && grid.can_go_from(Direction::Left, &rect.c) {
                        candidates.push((Direction::Left, rect.clone()));
                    }
                }
            },

            Direction::Left => {
                rect.d = rect.c.clone();
                rect.d.x -= 1;
                while (rect.d.x > rect.a.x) && grid.can_go_from(Direction::Left, &rect.d) {
                    rect.d.x -= 1;
                }   
                
                if (rect.d.x == rect.a.x) && grid.at(&rect.c) == '+' {
                    candidates.push((Direction::Up, rect.clone()));
                }
                
            },

            Direction::Up => {
                let mut p = rect.d.clone();
                while (p.y > rect.a.y) && grid.can_go_from(Direction::Up, &p) {
                    p.y -= 1;
                }    
                
                if rect.a.y == p.y {
                    println!("Rectangle! : {:?}", rect);
                    rectangles.push(rect);
                }
            }

        }

    }

    rectangles

}

/*  We scan each line of the grid for a start corner. The scanning is
    done left to right starting from the top left corner of the grid. 
    
    When we find a corner, we collect the rectangles that have this corner
    in the top left position (a) by scanning in the following order :
    Right, Down, Left, Up. Always scanning in this direction makes sure
    we do not count doubles.

    Let's take the following grid as an example.
    
    +-----+----+
    |     |    |
    +-----+----+

    The first pass starting at the point a will find 2 rectangles.

    a-----b----b
    |     |    |
    d-----c----c

    The second pass will find the 3rd rectangle.

          a----b
          |    |
          d----c


*/
pub fn count(lines : &Vec<&str>) -> usize {

    let grid = match Grid::from_string(lines) {
        Some(x) => x,
        None => return 0,
    };
    
    //grid.print();
    let mut nb_rectangles = 0;

    for i in 0..grid.columns {
        for j in 0..grid.rows {
            if grid.at_coords(i, j) == '+' {
                // we have a corner, next we check if we can at least go one step
                // to the right.
                let point = Point{x : (i as isize), y : (j as isize)};
                if grid.can_go_from(Direction::Right, &point) {
                    nb_rectangles += rectangles_from_point(&grid, &point).len();
                }
            }
        }
    }


    return nb_rectangles;
}
