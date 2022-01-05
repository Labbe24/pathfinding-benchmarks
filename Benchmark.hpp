#include <chrono>
#include <boost/function.hpp>
#include <boost/bind/bind.hpp>
#include <Timer.hpp>

#pragma once

/* Class responsible for starting banchmarking process and capturing measured durations */
template<typename T, unsigned int num_cycles = 10>
class Benchmark
{
    public:

        // possibilty for attaching a callbakc funtion
        void attach(const boost::function<void()>& cb) { cb_ = cb; };

        // starts benchmarking
        void start();

        // called by dijkstra using boost::signal2 when pathfinding is finished
        void done();

        void printDurations() const;
        void printAverageDuration() const;
        void printTotalDuration() const;

    private:
        T timer_;
        boost::function<void()> cb_;
};


template<typename T, unsigned int num_cycles>
void Benchmark<T, num_cycles>::start()
{
    timer_.reset();
	for(int i = 0; i < num_cycles; i++)
    {
        timer_.start();

        try
        {
            cb_();
        }
        catch(const boost::bad_function_call& e)
        {
            std::cout << e.what() << std::endl;
        }

        double duration = timer_.stop();
        std::cout << "run #"<< i << " duration: " << duration << " ms" << std::endl;
	}
}

template<typename T, unsigned int num_cycles>
void Benchmark<T, num_cycles>::done()
{  
    std::cout << "Finished ";
}

template<typename T, unsigned int num_cycles>
void Benchmark<T, num_cycles>::printDurations() const
{
    unsigned int avg = 0;
    for(int i = 0; i < num_cycles; i++)
    {
        double duration = timer_.elapsedInterval(i);
        std::cout << "Run #"<< i << " duration: " << duration << " ms" << std::endl;
	}
}

template<typename T, unsigned int num_cycles>
void Benchmark<T, num_cycles>::printAverageDuration() const
{
    double avg = timer_.elapsedTotal();;
    std::cout << "Average duration: " << avg/(double)num_cycles << " ms" << std::endl;
}

template<typename T, unsigned int num_cycles>
void Benchmark<T, num_cycles>::printTotalDuration() const
{
    double total = timer_.elapsedTotal();;
    std::cout << "Total duration: " << total << " ms" << std::endl;
}

