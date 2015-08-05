#[derive(PartialEq, Debug)]
pub enum Allergen {
    Eggs,
    Peanuts,
    Shellfish,
    Strawberries,
    Tomatoes,
    Chocolate,
    Pollen,
    Cats,
}

pub struct Allergies {
    pub score : i32,
}

impl Allergies {
    
    pub fn is_allergic_to(&self, allergen : &Allergen) -> bool {
        let retval = match allergen {
            &Allergen::Eggs         => self.score & 1,
            &Allergen::Peanuts      => self.score & 2,
            &Allergen::Shellfish    => self.score & 4,
            &Allergen::Strawberries => self.score & 8,
            &Allergen::Tomatoes     => self.score & 16,
            &Allergen::Chocolate    => self.score & 32,
            &Allergen::Pollen       => self.score & 64,
            &Allergen::Cats         => self.score & 128,
        };
        
        retval > 0
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

pub fn Allergies(score : i32) -> Allergies {
    Allergies{score : score}
}

