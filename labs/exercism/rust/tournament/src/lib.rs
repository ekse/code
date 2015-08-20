use std::fs::File;
use std::path::Path;
use std::error::Error;
use std::io::Read;
use std::io::Write;
use std::collections::HashMap;
use std::cmp::Ordering;

pub struct Roster {
    roster: HashMap<String, TeamStats>,
}

pub struct TeamStats {
    team_name: String,
    played: usize,
    wins: usize,
    draws: usize,
    losses: usize,
}

impl TeamStats {
    pub fn points(&self) -> usize {
        self.wins * 3 + self.draws
    }
}

impl Roster {
    fn get_team_stats(&mut self, team: String) -> &mut TeamStats {
        self.roster.entry(team.clone()).or_insert(
            TeamStats{team_name : team, 
                played : 0, 
                wins : 0, 
                draws: 0, 
                losses: 0
                })
    }

    pub fn new() -> Roster {
        Roster { roster: HashMap::new() }
    }

    pub fn add_win(&mut self, team: String) {
        let ref mut stats =  *self.get_team_stats(team);
        stats.played += 1;
        stats.wins += 1;
    }

    pub fn add_loss(&mut self, team: String) {
        let ref mut stats =  *self.get_team_stats(team);
        stats.played += 1;
        stats.losses += 1;
    }

    pub fn add_draw(&mut self, team: String) {
        let ref mut stats =  *self.get_team_stats(team);
        stats.played += 1;
        stats.draws += 1;
    }

    pub fn ordered_roster(&self) -> Vec<&TeamStats> {

        let mut teams : Vec<&TeamStats> = Vec::new();

        for teamstats in self.roster.values() {
            teams.push(teamstats);
        }

        teams.sort_by(|a,b| {
            let mut ord = b.points().cmp(&a.points());
            if ord == Ordering::Equal {
                ord = b.wins.cmp(&a.wins);
                if ord == Ordering::Equal {
                    ord = a.team_name.cmp(&b.team_name);
                }
            }
            ord
        });

        teams
    }
    
    pub fn from_game_records(content : String) -> (Roster, usize) {
        let mut roster = Roster::new();
        let mut nb_lines = 0;
        
        for line in content.lines() {
            let v : Vec<_> = line.split(";").collect();
            if v.len() != 3 {
                continue;
            }

            let team1  = v[0].to_string();
            let team2  = v[1].to_string();
            let result = v[2];

            match result {
                "win"  => {roster.add_win(team1); roster.add_loss(team2); nb_lines += 1},
                "loss" => {roster.add_loss(team1); roster.add_win(team2); nb_lines += 1},
                "draw" => {roster.add_draw(team1); roster.add_draw(team2); nb_lines += 1},
                _ => {}, // ignore bad lines
            }
        }
        
        (roster, nb_lines)
    }
}


pub fn tally(infile: &Path, outfile: &Path) -> Option<usize> {
    let mut file = match File::open(infile) {
        Ok(file) => file,
        Err(reason) => panic!("failed to open {} : {}", infile.display(), Error::description(&reason)), 
    };

    let mut content = String::new();
    match file.read_to_string(&mut content) {
        Ok(_) => (),
        Err(reason) => panic!("failed to read from {} : {}", infile.display(), Error::description(&reason)), 

    }

    let (roster, nb_lines) = Roster::from_game_records(content);
    let teams = roster.ordered_roster(); 

    // write the Roster and output it to a file
    let mut output = String::new();
    output.push_str("Team                           | MP |  W |  D |  L |  P\n");

    for team in teams {
        output.push_str(&format!("{:<30} |  {} |  {} |  {} |  {} |  {}\n", 
        team.team_name, 
        team.played, 
        team.wins, 
        team.draws, 
        team.losses, 
        team.points()));
    }

    let mut outfile = match File::create(outfile) { 
        Ok(file) => file,
        Err(reason) => panic!("failed to open {} : {}", infile.display(), Error::description(&reason)), 
    };

    match outfile.write_all(output.as_bytes()) {
        Ok(_) => (),
        Err(reason) => panic!("failed to read from {} : {}", infile.display(), Error::description(&reason)), 

    }

    Some(nb_lines)
}
