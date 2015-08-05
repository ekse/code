#[derive(Copy, Clone, PartialEq, Debug)]
pub enum Allergen {
    Eggs = 1,
    Peanuts = 2,
    Shellfish = 4,
    Strawberries = 8,
    Tomatoes = 16,
    Chocolate = 32,
    Pollen = 64,
    Cats = 128,
}

pub struct Allergies {
    pub score : u32,
}

impl Allergies {
    
    pub fn is_allergic_to(&self, allergen : &Allergen) -> bool {
        self.score & (*allergen as u32) > 0
    }

    pub fn allergies(&self) -> Vec<Allergen> {
        let allergens = vec![Allergen::Eggs, Allergen::Peanuts, Allergen::Shellfish,
            Allergen::Strawberries, Allergen::Tomatoes, Allergen::Chocolate,
            Allergen::Pollen, Allergen::Cats];
        
        let mut retval = vec![]; 
        for allergen in allergens {
            if self.is_allergic_to(&allergen) {
                retval.push(allergen);
            }
        }

        retval
    }
}

pub fn Allergies(score : u32) -> Allergies {
    Allergies{score : score}
}

