#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

class X
{
public:
	double Euclidean(X);
	X& operator*(int);
	X& operator+(X);
	X& operator=(X);
	void init();
	int dimension;
	vector<double> data; 
}

class K_Means
{
public:
	K_Means(string s, int n, int m, int k, double t);
	void ReadData();
	void RandomPartion();
	double TargetFunc();
	void print();
	void Lloyd();
	void online();
	void Hartigan();
	string filename;
	int dimension;
	int nCluster;
	int nSet;
	double newfunc, oldfunc£¬threshold;
	vector <int> map;
	vector <X> matrix;
	vector <X> vc;
	vector <int> map;
	vector <int> nc;
}




