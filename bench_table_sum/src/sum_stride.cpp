#include <vector>
#include <iostream>
#include <chrono>
#include <cstdint>

int main() {
    constexpr size_t N = 500'000'000;
    constexpr size_t STRIDE = 16; // zmieniaj: 2, 4, 8, 16, 64, 512

    std::vector<uint64_t> v(N, 1);

    volatile uint64_t warmup = 0;
    for (size_t i = 0; i < N; i += STRIDE) {
        warmup += v[i];
    }

    auto start = std::chrono::high_resolution_clock::now();

    uint64_t sum = 0;
    size_t count = 0;

    for (size_t i = 0; i < N; i += STRIDE) {
        sum += v[i];
        ++count;
    }

    auto end = std::chrono::high_resolution_clock::now();

    double sec = std::chrono::duration<double>(end - start).count();
    double useful_gb = double(count * sizeof(uint64_t)) / 1e9;

    std::cout << "sum = " << sum << "\n";
    std::cout << "count = " << count << "\n";
    std::cout << "time = " << sec << " s\n";
    std::cout << "useful throughput = " << useful_gb / sec << " GB/s\n";
}