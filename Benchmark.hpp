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
        double averageTime();

    private:
        T timer_;
        boost::function<void()> cb_;
};


template<typename Timer, unsigned int num_cycles>
void Benchmark<Timer, num_cycles>::start()
{
    Timer t1;
	
	for(int i = 0; i < num_cycles; i++)
    {
        t1.start();
		cb_();
        t1.stop();
	}
}

template<typename Timer, unsigned int num_cycle>
double Benchmark<Timer, num_cycle>::averageTime()
{
    return 0;
}

// [1, 2, 3, 4, 5]
