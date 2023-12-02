use std::fs::File;
use std::io::{self, BufRead};
use std::path::Path;

fn main() -> io::Result<()>{
    let path = Path::new("input.txt");
    let input = File::open(path)?;
    let buffered = io::BufReader::new(input);

    let mut sum = 0;

    for line in buffered.lines() {
        let line = line?;
        let mut first_digit = -1;
        let mut last_digit = -1;

        for chr in line.chars() {
            if chr.is_digit(10) {
                let digit = chr.to_digit(10).unwrap() as i32;
                if first_digit == -1 {
                    first_digit = digit;
                }
                last_digit = digit;
            }
        }
        if first_digit != -1 && last_digit == -1 {
            last_digit = first_digit;
        }
        sum += first_digit * 10 + last_digit;
    }

    println!("Total sum: {}", sum);
    Ok(())
}
