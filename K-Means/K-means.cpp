#include "K-means.h"
#include <cmath>
#include <time.h>
using namespace std;

double X::Euclidean(X x)
{
	double re = 0;
	for(int i=1; i<=dimension; i++){
		re += (data[i] - x.data[i])*(data[i] - x.data[i]);
	}
	return re/2;
}

void X::init()
{
	for(int i=1; i<=dimension; i++){
		this->data[i] = 0;
	}
}

X& X::operator*(int multiplier)
{
	X tmp = new X();
	tmp.data.resize(dimension+1);
	for(int i=1; i<=dimension; i++){
		tmp.data[i] = this->data[i]*multiplier;
	}
	return tmp;
}

X& X::operator+(X add)
{
	X tmp = new X();
	tmp.data.resize(dimension+1);
	for(int i=1; i<=dimension; i++){
		tmp.data[i] = this->data[i] + add.data[i];
	}
	return tmp;
}

X& X::operator=(X add)
{
	X tmp = new X();
	tmp.data.resize(dimension+1);
	for(int i=1; i<=dimension; i++){
		tmp.data[i] = this->data[i];
	}
	return tmp;
}

K_Means::K_Means(string s, int n, int m, int k, double t)
	:filename(s), nCluster(k), nSet(n), dimension(m), threshold(t)
{
	matrix.resize(nSet+1);
	vc.resize(nCluster+1);
	map.resize(nSet+1);
	nc.resize(nCluster+1);
	for(int i=1; i<nSet; i++){
		matrix[i].data.resize(dimension+1);
	}
}

void K_Means::ReadData()
{
	ifstream infile(s.c_str(), ios::in);

	for(int i=1; i<nSet; i++){
		for(int j=1; j<dimension; j++){
			infile >> matrix[i][j];
		}
	}
	infile.close();
}

void K_Means::RandomPartion()
{
	srand( (unsigned)time( NULL ) ); 
	int tmp;
	for(int i=1; i<=nCluster; i++){
		tmp = rand()%(nCluster - i) + i + 1;
		matrix[i].swap(matrix[tmp]);
	}

	for(int i=1; i<=nCluster; i++){
		vc[i] = matrix[i];
	}
	
}

double K_Means::TargetFunc()
{
	double re = 0;
	for(int i=1; i<nSet; i++){
		re += matrix[i].Euclidean(vc[map[i]]);
	}
	return re;
}

void K_Means::Lloyd()
{
	bool isFirst = true;
	newfunc = oldfunc = -1;
	while(abs(newfunc-oldfunc) >= threshold || isFirst)
	{
		double distance;
		int indexCluster;

		for(int i=1; i<=nCluster; i++){
			nc[i] = 0;
		}

		for(int i=1; i<nSet; i++){
			indexCluster = 1;
			distance = matrix[i].Euclidean(vc[1]);
			for(int j=2; j<nCluster; j++){
				if(distance > matrix[i].Euclidean(vc[j])){
					distance = matrix[i].Euclidean(vc[j]);
					indexCluster = j;
				}
			}
			map[i] = indexCluster;
			nc[indexCluster]++;
		}
		for(int i=1; i<=nCluster; i++){
			vc[i].init();
		}
		for(int i=1; i<nSet; i++){
			vc[map[i]] += matrix[i];
		}
		for(int i=1; i<=nCluster; i++){
			vc[i] = vc[i]*(1.0/nc[i]);
		}
		
		newfunc = TargetFunc();
		if(isFirst){
			isFirst = false;// maybe error!!
		}
	}
}

void K_Means::print()
{
	cout << "filename:  " << filename ;
	cout << "              result: " << newfunc << endl;
}