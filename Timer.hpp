#include <chrono>

#pragma once

/* Simple timer class used by Benchmark to capture time durations using chronos time_points */
class Timer
{
    using time_point = std::chrono::_V2::system_clock::time_point;

    public:
        // Constructor
        Timer() : time_{0}{} 

        // Copy constructor
        Timer(const Timer& other);
        // Copy assignemtn operator
        Timer& operator=(const Timer& other);

        // Move constructor
        Timer(Timer&& other) noexcept;
        // Move assignment operator
        Timer& operator=(Timer&& other) noexcept;

        // Start time
        void start();

        // Stop time add time to intervals vector and return time
        double stop();

        // Reset time and clear intercals
        void reset();

        // Returns time for specific interval
        double elapsedInterval(const int i);

        // Returns total time for all intervals
        double elapsedTotal() const;

    private:
        double time_;                       // Captures total time
        std::vector<double> intervals_;     // Captures time for each run
        time_point started_;
        time_point stopped_;
};

Timer::Timer(const Timer& other)
{
    time_ = other.time_;
    intervals_ = other.intervals_;
    started_ = other.started_;
    stopped_ = other.stopped_;
}
Timer& Timer::operator=(const Timer& other)
{
    time_ = other.time_;
    intervals_ = other.intervals_;
    started_ = other.started_;
    stopped_ = other.stopped_;
    return *this;   
}

Timer::Timer(Timer&& other) noexcept
:   time_{std::move(other.time_)}, 
    intervals_{std::move(other.intervals_)},  
    started_{std::move(other.started_)}, 
    stopped_{std::move(other.stopped_)}
{}

Timer& Timer::operator=(Timer&& other) noexcept
{
    if(this != &other)
    {
        time_= std::move(other.time_);
        intervals_ = std::move(other.intervals_);
        started_ = std::move(other.started_);
        stopped_ = std::move(other.stopped_);
    }
    return *this;
}

void Timer::start()
{
    started_ = std::chrono::high_resolution_clock::now();
}

double Timer::stop()
{   
    stopped_ = std::chrono::high_resolution_clock::now();

    double duration = std::chrono::duration_cast<std::chrono::milliseconds>(stopped_ - started_).count();

    intervals_.emplace_back(duration);
    time_ +=  duration;
    return duration;
}

void Timer::reset()
{
    time_ = 0;
    intervals_.clear();
}

double Timer::elapsedInterval(const int i)
{
    return intervals_[i];
}

double Timer::elapsedTotal() const
{
    return time_;
}
