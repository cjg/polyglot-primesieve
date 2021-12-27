use std::time::Instant;

fn count_primes(n:i32) -> i32 {
    let mut prime_numbers: Vec<bool> = Vec::new();
    prime_numbers.resize(n.try_into().unwrap(), true);
    prime_numbers[0] = false;
    prime_numbers[1] = false;
    let last = f64::from(n).sqrt() as i32;
    for i in 2..last {
        if !prime_numbers[i as usize] {
            continue;
        }
        let mut j = i * 2;
        while j < n {
            prime_numbers[j as usize] = false;
            j += i;
        }
    }
    let mut c: i32 = 0;
    for i in prime_numbers {
        if i {
            c += 1;
        }
    }
    return c;
}

fn main() {
    let mut durations: Vec<u128> = Vec::new();
    durations.resize(100, 0);
    for i in 0..durations.len() {
        let start = Instant::now();
        let n = count_primes(1000000);
        durations[i] = start.elapsed().as_millis();
        if n != 78498 {
            println!("found {} instead of 78498 prime numbers", n);
            std::process::exit(-1);
        }
        println!("Iteration {} completed in {:0.2}ms", i, durations[i]);
    }
    
    let mut min: u128 = durations[0];
    let mut max: u128 = durations[0];
    let mut total: u128 = 0;
    for d in &durations {
        if *d < min {
            min = *d;
        }
        if *d > max {
            max = *d;
        }
        total += *d;
    }
    let avg: f64 = (total as f64) / (durations.len() as f64);
    println!("{} iterations completed in {:.2}s, min: {}ms max: {}ms average: {:.2}ms", 
        durations.len(), (total as f64) / 1000.0, min, max, avg);
}
