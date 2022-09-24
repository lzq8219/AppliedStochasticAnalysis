#include <iostream>       
#include <atomic>         
#include <vector>         
#include <functional>
#include <random>
#include <thread>


void rw(std::vector<unsigned char>& sigma, int begin, int end, int p);
class point2D
{
private:
	int N;
	int p;
	std::vector<unsigned char> sigma;
	double H, E, J, h, T;

public:
	point2D();
	point2D(const int& N, const int& p, const double& J, const double& h,const double &T);



	void generate();

	void operator=(const point2D& x);
	unsigned char& operator()(int i,int j);//0 to N-1
	const unsigned char& operator()(int i, int j) const;


	std::vector<unsigned char>& get();


	void compute_Hamilton();
	double compute_Hamilton(int rbegin, int rend);

	double energy();
	double relative_energy(const point2D &x);
	const double& Hamilton() const;
	const int& getN() const;

	void transfer(point2D& x); //Ëæ»úÓÎ×ß
	void release();
};

class stat_p
{
private:
	int N;
	std::vector<double> t;
	std::vector<double> H;
	std::vector<double> s_sigma;
	std::vector<int> k;

public:
	stat_p(int N, std::vector<int> kk);
	std::vector<double> getH();
	std::vector<int> getk();
	std::vector<double> gett();
	std::vector<double> gets();

	void compute(const point2D&);
};
