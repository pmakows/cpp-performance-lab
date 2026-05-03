#include <vector>
#include <iostream>
#include <chrono>
#include <cstdint>

int main() {
    constexpr size_t N = 500'000'000;

    std::vector<uint64_t> v(N, 1);

    volatile uint64_t warmup = 0;
    for (size_t i = 0; i < N; ++i) {
        warmup += v[i];
    }

    auto start = std::chrono::high_resolution_clock::now();

    uint64_t sum = 0;
    for (size_t i = 0; i < N; ++i) {
        sum += v[i];
    }

    auto end = std::chrono::high_resolution_clock::now();

    double sec = std::chrono::duration<double>(end - start).count();
    double gb = double(N * sizeof(uint64_t)) / 1e9;

    std::cout << "sum = " << sum << "\n";
    std::cout << "time = " << sec << " s\n";
    std::cout << "throughput = " << gb / sec << " GB/s\n";
}