#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <chrono>
#include <iostream>

class Benchmark {
public:
  static constexpr float ms = 0.001;
  using Clock = std::chrono::high_resolution_clock;
  using TimePoint = std::chrono::time_point<std::chrono::high_resolution_clock>;

public:
  Benchmark() { m_StartPoint = Clock::now(); }
  ~Benchmark() { Stop(); }

  Benchmark(const Benchmark &) = delete;
  Benchmark &operator=(const Benchmark &) = delete;

  Benchmark(Benchmark &&) = delete;
  Benchmark &operator=(Benchmark &&) = delete;

  float Stop() {
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
    return Result;
  }

private:
  TimePoint m_StartPoint;
};

#endif