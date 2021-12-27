#include <chrono>
#include <cmath>
#include <iostream>
#include <ratio>
#include <vector>

int countPrimes(int n) {
	std::vector<bool> primeNumbers(n, true);
	primeNumbers[0] = false;
	primeNumbers[1] = false;
	auto last = static_cast<int>(sqrt(static_cast<double>(n)));
	for (auto i = 2; i < last; i++) {
		if (!primeNumbers[i]) {
			continue;
		}
		for (auto j = i * 2; j < n; j+=i) {
			primeNumbers[j] = false;
		}
	}
	auto c = 0;
	for (const auto & i : primeNumbers) {
		if (i) {
			c++;
		}
	}
	return c;
}

int main() {
	std::vector<double> durations(100, 0.0);
	for (auto i = 0U; i < durations.size(); i++) {
		auto start = std::chrono::high_resolution_clock::now();
		auto n = countPrimes(1000000);
		std::chrono::duration<float, std::milli> timeTaken = std::chrono::high_resolution_clock::now() - start;
		durations[i] = timeTaken.count();
		if (n != 78498) {
			std::cerr << "found " << n << " instead of 78498 prime numbers" << std::endl;
			return -1;
		}
		std::cout << "Iteration " << i << " completed in " << durations[i] << "ms" << std::endl;
	}

	auto max = durations[0];
	auto min = durations[0];
	auto total = 0.0;
	for (const auto &d : durations) {
		if (d < min) {
			min = d;
		}

		if (d > max) {
			max = d;
		}

		total += d;
	}

	auto avg = total / static_cast<double>(durations.size());

	std::cout << durations.size() << " iterations completed in " << (total / 1000.0) << "s, min: " << 
		min << "ms max: " << max << "ms avg: " << avg << "ms" << std::endl; 
}
