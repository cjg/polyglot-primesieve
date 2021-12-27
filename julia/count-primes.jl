using Printf 

function countPrimes(n)
  primeNumbers = map(i->true, 1:n-1)
	primeNumbers[1] = false
	last = Int(trunc(sqrt(n)))
	for i in 2:last
		if !primeNumbers[i]
			continue
		end
		j = i * 2
		while j < n 
			primeNumbers[j] = false
			j += i
		end
	end
	c = 0
	for i in primeNumbers
		if i
			c += 1
		end
	end
	return c
end

function main()
	durations = map(i->0.0, 1:100)
	for i in 1:length(durations)
		start = time()
		n = countPrimes(1000000)
		durations[i] = (time() - start) * 1000
		if n != 78498
			@printf("found %d instead of 78498 prime numbers\n", n)
			return nothing
		end
		@printf("Iteration %3d completed in %0.2fms\n", i, durations[i])
	end

	@printf("%d iterations completed in %0.2fs, min: %0.2fms max: %0.2fms average: %0.2fms", 
					length(durations), sum(durations) / 1000, minimum(durations), maximum(durations),
					sum(durations) / length(durations))
end

main()

