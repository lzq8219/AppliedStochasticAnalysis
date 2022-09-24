#include <iostream>       
#include <atomic>         
#include <thread>         
#include <vector>         
#include <functional>
#include <random>
#include <fstream>

#include"point_model.h"

void rw(std::vector<unsigned char>& sigma, int begin, int end, int p)
{
	static std::default_random_engine gen;
	static std::uniform_int_distribution<int> b12(1, 2);
	for (int i = begin; i < end; i++)
	{
		sigma[i] = (((int)sigma[i]) + (b12(gen) == 1 ? -1 : 1) + p - 1) % p + 1;
	}
}




point2D::point2D() {};
point2D::point2D(const int& N, const int& p, const double& J, const double& h,const double & T)
{
	this->N = N;
	this->p = p;
	this->J = J;
	this->h = h;
	this->T = T;
}

void point2D::generate()
{
	static std::default_random_engine gen;
	std::uniform_int_distribution<int> uu(1, p);
	sigma.clear();
	for (int i = 0; i < N * N; i++) {
		//sigma.push_back(uu(gen));
		sigma.push_back(1);
	}
	this->compute_Hamilton();
}

void point2D::operator=(const point2D& x)
{
	N = x.N;
	p = x.p;
	sigma = x.sigma;
	J = x.J;
	h = x.h;
	T = x.T;
	H = x.H;
}

unsigned char& point2D::operator()(int i, int j)
{
	return sigma[i * N + j];
}

const unsigned char& point2D::operator()(int i, int j) const
{
	return sigma[i * N + j];
}


std::vector<unsigned char>& point2D::get()
{
	return sigma;
}



double point2D::compute_Hamilton(int rbegin,int rend)
{
	double H = 0;
	for (int i = rbegin; i < rend; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (this->operator()(i, j) == this->operator()(i, (j + 1) % p)) H -= J;
			if (this->operator()(i, j) == this->operator()((i+1)%p, j)) H -= J;
			H -= h * (int)this->operator()(i, j);
		}
	}
	return H;
}

void point2D::compute_Hamilton()
{
	H = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (this->operator()(i, j) == this->operator()(i, (j + 1) % N)) H -= J;
			if (this->operator()(i, j) == this->operator()((i + 1) % N, j)) H -= J;
			//H -= h * (int)this->operator()(i, j);
		}
	}
}

double point2D::energy() 
{ 
	return exp(-H/T); 
}

double point2D::relative_energy(const point2D& x)
{
	return exp(-(H - x.H) / T);
}

const double& point2D::Hamilton() const{ return H; }
const int& point2D::getN() const { return N; }

void point2D::transfer(point2D& x) //Ëæ»úÓÎ×ß
{
	x = *this;

	
	static std::default_random_engine gen;
	static std::uniform_int_distribution<int> b1N(0, N-1);
	static std::uniform_int_distribution<int> b1p(1, p);

	int is = b1N(gen), js = b1N(gen);

	unsigned temp = x(is,js);
	x(is, js) = b1p(gen);

	int count=0;
	for (int j = -1; j <= 1; j += 2)
	{
		if (temp == x(is, (js + N + j) % N)) count++;
		if (temp == x(((is + N + j) % N),js)) count++;
		if (x(is, js) == x(is, (js + N + j) % N)) count--;
		if (x(is, js) == x(((is + N + j) % N), js)) count--;
	}
	x.H = x.H + J * count + h * ((int)temp - (int)x(is, js));

	/*
	double HH = x.H;


	x.compute_Hamilton();
	if (x.H != HH) std::cout << "error" << "\n";
	*/

	/*
	unsigned int n = std::thread::hardware_concurrency();
	std::vector<std::thread> t(n);
	std::vector<std::vector<int>> count(n);

	int block_size = N * N / n;
	for (int i = 0; i < n - 1; i++)
	{
		t[i] = std::thread(rw, std::ref(x.sigma), (n - 1) * block_size, N * N, p);
	}
	t[n - 1] = std::thread(rw, std::ref(x.sigma), (n - 1) * block_size, N * N, p);

	for (int i = 0; i < n; i++)
	{
		t[i].join();
	}
	*/

}

void point2D::release()
{
	sigma.clear();
}

stat_p::stat_p(int NN, std::vector<int> kk)
{
	H.clear();
	N = NN;
	s_sigma = std::vector<double>(N * N, 0);
	k = kk;
	t = std::vector<double>(kk.size(), 0);
}

std::vector<double> stat_p::getH() { return H; }
std::vector<int> stat_p::getk() { return k; }
std::vector<double> stat_p::gett() { return t; }

void stat_p::compute(const class point2D& x)
{
	//compute H
	H.push_back(x.Hamilton());


	//s_sigma
	/*
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			s_sigma[i*N+j] += (int)x(i, j);
			for (int l = 0; l < k.size(); l++)
			{
				t[l] += (int)x(i, j) * (int)x((i + k[l]) % N, j);
				t[l] += (int)x(i, j) * (int)x(i, (j + k[l]) % N);
			}
		}
	}
	*/
	
}