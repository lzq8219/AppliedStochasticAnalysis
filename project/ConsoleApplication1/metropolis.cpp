#include <iostream>       
#include <atomic>         
#include <thread>         
#include <vector>         
#include <functional>
#include <random>

#include "metropolis.h"
#include "point_model.h"


stat_p metropolis(point2D& x0, int S, std::vector<int> kk)
{
	stat_p v(x0.getN(),kk);
	point2D xt = x0;
	point2D xtt;
	static std::default_random_engine gen;
	static std::uniform_real_distribution<double> u(0., 1.);
	std::cout << "running:";
	for (int i = 0; i < S; i++)
	{
		
		if (i % 100000 == 0)std::cout << "*";
		xt.transfer(xtt);
		double pi = xtt.relative_energy(xt);
		double alpha = fmin(1., pi);
		if (u(gen) < alpha) xt = xtt;
		v.compute(xt);
	}
	std::cout << "\n";
	return v;

}
