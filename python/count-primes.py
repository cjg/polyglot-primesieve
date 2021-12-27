import math
import sys
import time

def count_primes(n):
    prime_numbers = [True for i in range(n)]
    prime_numbers[0] = False
    prime_numbers[1] = False

    last = int(math.sqrt(n))

    for i in range(2, last):
        if not prime_numbers[i]:
            continue
        j = i * 2
        while j < n:
            prime_numbers[j] = False
            j += i

    c = 0
    for i in prime_numbers:
        if i:
            c += 1

    return c


if __name__ == '__main__':
    durations = [0.0 for i in range(100)]
    for i in range(len(durations)):
        start = time.time()
        n = count_primes(1000000)
        durations[i] = (time.time() - start) * 1000
        if n != 78498:
            print(f"found {n} instead of 78498 prime numbers")
            sys.exit(-1)
        print(f"Iteration {i} completed in {durations[i]}ms")

    min_duration = durations[0]
    max_duration = durations[0]
    total = durations[0]
    for i in range(1, len(durations)):
        if durations[i] < min_duration:
            min_duration = durations[i]

        if durations[i] > max_duration:
            max_duration = durations[i]

        total += durations[i]
    avg = total / len(durations)

    print(f"{len(durations)} iterations completed in {total / 1000}s, min: {min_duration}ms max: {max_duration}ms average: {avg}ms")

