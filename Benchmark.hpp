#include <chrono>
#include <boost/function.hpp>
#include <boost/bind/bind.hpp>
#include <Timer.hpp>

#pragma once

template<typename Timer, unsigned int num_cycles = 10>
class Benchmark
{
    public:

        void attach(const boost::function<void()>& cb) { cb_ = cb; };
        void start();
        void done();

        void printDurations();
        void printAverageDuration();
        void printTotalDuration();

    private:
        Timer timer_;
        boost::function<void()> cb_;
};


template<typename Timer, unsigned int num_cycles>
void Benchmark<Timer, num_cycles>::start()
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
        std::cout << "Run #"<< i << " duration: " << duration << " ms" << std::endl;
	}
}

template<typename Timer, unsigned int num_cycles>
void Benchmark<Timer, num_cycles>::done()
{
    std::cout << "Finished benchmarking" << std::endl;
}

template<typename Timer, unsigned int num_cycles>
void Benchmark<Timer, num_cycles>::printDurations()
{
    unsigned int avg = 0;
    for(int i = 0; i < num_cycles; i++)
    {
        double duration = timer_.elapsedInterval(i);
        std::cout << "Run #"<< i << " duration: " << duration << " ms" << std::endl;
	}
}

template<typename Timer, unsigned int num_cycles>
void Benchmark<Timer, num_cycles>::printAverageDuration()
{
    double avg = timer_.elapsedTotal();;
    std::cout << "Average duration: " << avg/(double)num_cycles << " ms" << std::endl;
}

template<typename Timer, unsigned int num_cycles>
void Benchmark<Timer, num_cycles>::printTotalDuration()
{
    double total = timer_.elapsedTotal();;
    std::cout << "Total duration: " << total << " ms" << std::endl;
}

