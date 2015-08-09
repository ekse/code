#[derive(PartialEq, Eq, Debug)]
pub struct RibonucleicAcid {
    rna : String,   
}

impl RibonucleicAcid {
    pub fn new(s : &str) -> RibonucleicAcid {
        RibonucleicAcid{rna : s.to_string()}        
    }
}

impl AsRef<str> for RibonucleicAcid {
    fn as_ref(&self) -> &str {
        self.rna.as_ref()
    }
}

fn dna_to_rna(c : char) -> char {
    match c {
        'G' => 'C',
        'C' => 'G',
        'T' => 'A',
        'A' => 'U',
        _   => c,
    }
}

#[derive(PartialEq, Eq, Debug)]
pub struct DeoxyribonucleicAcid {
    dna : String,    
}

impl DeoxyribonucleicAcid {
    pub fn new(s : &str) -> DeoxyribonucleicAcid {
        DeoxyribonucleicAcid{dna : s.to_string()}        
    }

    pub fn to_rna(&self) -> RibonucleicAcid {
        let rna : String = self.dna.chars().map(dna_to_rna).collect();
        RibonucleicAcid{rna : rna}
    }
}

impl AsRef<str> for DeoxyribonucleicAcid {
    fn as_ref(&self) -> &str {
        self.dna.as_ref()
    }
}
