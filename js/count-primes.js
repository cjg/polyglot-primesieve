function countPrimes(n) {
  let primeNumbers = Array(n);
  for (let i = 0; i < n; i++) {
    primeNumbers[i] = true;
  }
  primeNumbers[0] = false;
  primeNumbers[1] = false;
  let last = parseInt(Math.sqrt(n));
  for (let i = 2; i < last; i++) {
    if (!primeNumbers[i]) {
      continue;
    }
    for (let j = i * 2; j < n; j += i) {
      primeNumbers[j] = false;
    }
  }
  let c = 0;
  for (let i = 0; i < n; i++) {
    if (primeNumbers[i]) {
      c += 1;
    }
  }
  return c;
}

function main() {
  let durations = Array(100);
  for (let i = 0; i < durations.length; i++) {
    let start = new Date().getTime();
    let n = countPrimes(1000000);
    durations[i] = (new Date().getTime()) - start;
    if (n != 78498) {
      console.log(`found ${n} instead of 78498 prime numbers`);
      return -1;
    }
    console.log(`Iteration ${i} completed in ${durations[i]}ms`);
  }

  let min = durations[0];
  let max = durations[0];
  let total = durations[0];
  for (let i = 1; i < durations.length; i++) {
    if (durations[i] < min) {
      min = durations[i];
    }

    if (durations[i] > max) {
      max = durations[i];
    }

    total += durations[i];
  }
  console.log(`${durations.length} iterations completed in ${total/1000.0}s, min: ${min}ms ` + 
    `max: ${max}ms average: ${total / durations.length}ms`);
}

main();

