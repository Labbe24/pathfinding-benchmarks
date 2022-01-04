#include <chrono>

#pragma once

class Timer
{
    using time_point = std::chrono::_V2::system_clock::time_point;

    public:
        Timer() : time_{0}{}

        Timer(Timer&& other) noexcept;

        Timer& operator=(Timer&& other) noexcept;

        Timer(const Timer& other);

        void start();
        double stop();
        void reset();
        double elapsedInterval(unsigned int i);
        double elapsedTotal();

    private:
        double time_;
        std::vector<double> intervals_;
        time_point started_;
        time_point stopped_;
};

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

Timer::Timer(const Timer& other)
{
    time_ = other.time_;
    intervals_ = other.intervals_;
    started_ = other.started_;
    stopped_ = other.stopped_;
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

double Timer::elapsedInterval(unsigned int i)
{
    return intervals_[i];
}

double Timer::elapsedTotal()
{
    return time_;
}
