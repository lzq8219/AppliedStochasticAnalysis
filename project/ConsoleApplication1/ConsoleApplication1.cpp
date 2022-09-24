#include <iostream>       
#include <atomic>         
#include <thread>         
#include <vector>         
#include <functional>
#include <random>
#include <fstream>

#include "metropolis.h"
#include "point_model.h"





int main() 
{
	static bool firstTime = true;
	static std::default_random_engine gen;
	if (firstTime) {
		std::random_device rd;
		gen.seed(rd());
		firstTime = false;
	}

	std::vector<double> ue,c;
	std::vector<double> T = { 1};
	for (int i=0;i<T.size();i++)
	{
		int N = 1000;
		point2D x(N, 3, 1.,0,T[i]);
		x.generate();
		int S = 3*1e7;
		stat_p s=metropolis(x,S);
		//stat_p ss = metropolis(x, S);
		std::vector<double> H = s.getH();
		//std::vector<double> HH = ss.getH();
		double U = 0;
		int SS = S;
		for (int j = H.size()-SS; j < H.size(); j++)
		{
		//	U += H[j]+HH[j];
			U += H[j];
		}
		double var = 0;
		U = U / SS;
		for (int j = H.size() - SS; j < H.size(); j++)
		{
			var += (H[j] - U) * (H[j] - U);
		//	var += (HH[j] - U) * (HH[j] - U);
		}
		ue.push_back(U/N/N);
		c.push_back(var / (SS - 1) / N / N / T[i] / T[i]);
	}

	for (int i=0;i<ue.size();i++)
	{
		std::cout <<T[i]<<" "<< ue[i]<<" "<<c[i] << "\n";
	}



	
	std::ofstream file;
	file.open("N=1e3_S=1e7.txt");
	file << "T,u,c," << "\n";
	for (int i = 0; i < ue.size(); i++) {
		file<< T[i] << "," << ue[i] << "," << c[i] << ",\n";
	}
	file.close();
	


 }