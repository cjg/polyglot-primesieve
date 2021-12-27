package main

import (
	"fmt"
	"math"
	"time"
)

func countPrimes(n int) int {
	primeNumbers := make([]bool, n)
	for i := range primeNumbers {
		primeNumbers[i] = true
	}
	primeNumbers[0] = false
	primeNumbers[1] = false
	last := int(math.Sqrt(float64(n)))
	for i := 2; i < last; i++ {
		if !primeNumbers[i] {
			continue
		}
		for j := i * 2; j < n; j += i {
			primeNumbers[j] = false
		}
	}
	c := 0
	for i := range primeNumbers {
		if primeNumbers[i] {
			c += 1
		}
	}
	return c
}

func main() {
	durations := make([]time.Duration, 100)
	for i := range durations {
		start := time.Now()
		n := countPrimes(1000000)
		durations[i] = time.Since(start)
		if n != 78498 {
			panic(fmt.Sprintf("found %v instead of 78498 prime numbers", n))
		}
		fmt.Printf("Iteration %3d completed in %v\n", i, durations[i])
	}
	min := time.Duration(math.MaxInt64)
	max := time.Duration(0)
	total := time.Duration(0)
	for _, d := range durations {
		if d < min {
			min = d
		}
		if d > max {
			max = d
		}
		total += d
	}
	avg := time.Duration(total.Nanoseconds() / int64(len(durations)))
	fmt.Printf("%v iterations completed in %v, min: %v max: %v average: %v", 
		len(durations), total, min, max, avg)
}
