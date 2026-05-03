#include <vector>
#include <iostream>
#include <chrono>
#include <random>
#include <algorithm>
#include <cstdint>

int main() {
    constexpr size_t N = 100'000'000;

    std::vector<uint64_t> v(N, 1);
    std::vector<size_t> idx(N);

    for (size_t i = 0; i < N; ++i) {
        idx[i] = i;
    }

    std::mt19937_64 rng(123);
    std::shuffle(idx.begin(), idx.end(), rng);

    volatile uint64_t warmup = 0;
    for (size_t i = 0; i < N; ++i) {
        warmup += v[idx[i]];
    }

    auto start = std::chrono::high_resolution_clock::now();

    uint64_t sum = 0;
    for (size_t i = 0; i < N; ++i) {
        sum += v[idx[i]];
    }

    auto end = std::chrono::high_resolution_clock::now();

    double sec = std::chrono::duration<double>(end - start).count();
    double gb = double(N * sizeof(uint64_t)) / 1e9;

    std::cout << "sum = " << sum << "\n";
    std::cout << "time = " << sec << " s\n";
    std::cout << "useful throughput = " << gb / sec << " GB/s\n";
}