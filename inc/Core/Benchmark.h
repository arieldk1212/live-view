#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <chrono>
#include <iostream>

/**
 * @brief Utility class for benchmarking code execution time.
 *
 * Captures the starting time upon construction and computes the elapsed time in milliseconds
 * when the benchmark is stopped. The result is output to the console.
 */

/**
 * @brief Initializes the benchmark by recording the current high-resolution time.
 */

/**
 * @brief Finalizes the benchmark by stopping the measurement and printing the elapsed time.
 */

/**
 * @brief Computes and prints the elapsed time in milliseconds.
 *
 * Records the current time as the endpoint, calculates the duration from when the benchmark
 * started, converts the duration to milliseconds, and outputs the result to the console.
 */
class Benchmark {
public:
  static constexpr float ms = 0.001;
  using Clock = std::chrono::high_resolution_clock;
  using TimePoint = std::chrono::time_point<std::chrono::high_resolution_clock>;

public:
  Benchmark() { m_StartPoint = Clock::now(); }
  ~Benchmark() { Stop(); }

  void Stop() {
    auto EndPoint = Clock::now();

    auto Start =
        std::chrono::time_point_cast<std::chrono::microseconds>(m_StartPoint)
            .time_since_epoch()
            .count();
    auto End = std::chrono::time_point_cast<std::chrono::microseconds>(EndPoint)
                   .time_since_epoch()
                   .count();

    auto Result = static_cast<float>(End - Start) * ms;
    std::cout << "BENCHMARK RESULT -> " << Result << "ms\n";
  }

private:
  TimePoint m_StartPoint;
};

#endif