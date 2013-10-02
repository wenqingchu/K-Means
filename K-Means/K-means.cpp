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

X X::operator*(double multiplier)
{
	X tmp;
	tmp.data.resize(dimension+1);
	tmp.dimension = dimension;
	for(int i=1; i<=dimension; i++){
		tmp.data[i] = this->data[i]*multiplier;
	}
	return tmp;
}

X X::operator+(X add)
{
	X tmp;
	tmp.data.resize(dimension+1);
	tmp.dimension = dimension;
	for(int i=1; i<=dimension; i++){
		tmp.data[i] = this->data[i] + add.data[i];
	}
	return tmp;
}

X X::operator-(X add)
{
	X tmp;
	tmp.data.resize(dimension+1);
	tmp.dimension = dimension;
	for(int i=1; i<=dimension; i++){
		tmp.data[i] = this->data[i] - add.data[i];
	}
	return tmp;
}

X X::operator=(X add)
{
	for(int i=1; i<=dimension; i++){
		this->data[i] = add.data[i];
	}
	return (*this);
}

void X::swap(X& x)
{
	data.swap(x.data);
}


K_Means::K_Means(string s, int n, int m, int k, double t)
	:filename(s), nCluster(k), nSet(n), dimension(m), threshold(t)
{
	matrix.resize(nSet+1);
	vc.resize(nCluster+1);
	map.resize(nSet+1);
	nc.resize(nCluster+1);
	for(int i=1; i<=nSet; i++){
		matrix[i].data.resize(dimension+1);
		matrix[i].dimension = m;
	}
	for(int i=1; i<=nCluster; i++){
		vc[i].data.resize(dimension+1);
		vc[i].dimension = m;
	}

}

void K_Means::ReadData()
{
	ifstream infile(filename.c_str(), ios::in);

	for(int i=1; i<=nSet; i++){
		for(int j=1; j<=dimension; j++){
			infile >> matrix[i].data[j];
		}
	}
	infile.close();
}

void K_Means::RandomPartion()
{
	srand( (unsigned)time( NULL ) ); 
	int tmp,tmpmap;
	for(int i=1; i<nSet; i++){
		tmp = rand()%(nSet - i) + i + 1;
		matrix[i].swap(matrix[tmp]);
		tmpmap = map[tmp];
		map[tmp] = map[i];
		map[i] = tmpmap;
	}
	
}

double K_Means::TargetFunc()
{
	double re = 0;
	for(int i=1; i<=nSet; i++){
		re += matrix[i].Euclidean(vc[map[i]]);
	}
	return re/nSet;
}

void K_Means::Lloyd()
{
	bool isFirst = true;
	newfunc = oldfunc = -1;
	for(int i=1; i<=nCluster; i++){
		vc[i] = matrix[i];
	}
	while(abs(newfunc-oldfunc) >= threshold || isFirst)
	{
		double distance;
		int indexCluster;
		oldfunc = newfunc;
		for(int i=1; i<=nCluster; i++){
			nc[i] = 0;
		}

		for(int i=1; i<=nSet; i++){
			indexCluster = 1;
			distance = matrix[i].Euclidean(vc[1]);
			for(int j=2; j<=nCluster; j++){
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
		for(int i=1; i<=nSet; i++){
			vc[map[i]] = vc[map[i]] + matrix[i];
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

void K_Means::online()
{
	bool notDone = true;
	for(int i=1; i<=nCluster; i++){
		vc[i] = matrix[i];
	}
	for(int i=1; i<=nCluster; i++){
		nc[i] = 0;
	}
	for(int i=1; i<=nSet; i++){
		int indexCluster = 1;
		double distance = matrix[i].Euclidean(vc[1]);
		for(int j=2; j<=nCluster; j++){
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
	for(int i=1; i<=nSet; i++){
		vc[map[i]] = vc[map[i]] + matrix[i];
	}
	for(int i=1; i<=nCluster; i++){
		vc[i] = vc[i]*(1.0/nc[i]);
	}


	while(notDone){
		RandomPartion();
		notDone = false;
		for(int i=1; i<=nSet; i++){
			if(nc[map[i]] == 1)	continue;
			vc[map[i]] = (vc[map[i]]*nc[map[i]] - matrix[i])*(1.0/(nc[map[i]] - 1));
			nc[map[i]]--;
			int indexCluster = 1;
			double distance = matrix[i].Euclidean(vc[1]);
			for(int j=2; j<=nCluster; j++){
				if(distance > matrix[i].Euclidean(vc[j])){
					distance = matrix[i].Euclidean(vc[j]);
					indexCluster = j;
				}
			}
			if(indexCluster == map[i]){
				vc[map[i]] = (vc[map[i]]*nc[map[i]] + matrix[i])*(1.0/(nc[map[i]] + 1));
				nc[map[i]]++;
			}
			else{
				map[i] = indexCluster;
				vc[map[i]] = (vc[map[i]]*nc[map[i]] + matrix[i])*(1.0/(nc[map[i]] + 1));
				nc[map[i]]++;
				notDone = true;
				break;
			}
			

		}
		
	}
	newfunc = TargetFunc();
}

void K_Means::Hartigan()
{
	bool notDone = true;
	for(int i=1; i<=nCluster; i++){
		vc[i] = matrix[i];
	}
	for(int i=1; i<=nCluster; i++){
		nc[i] = 0;
	}
	for(int i=1; i<=nSet; i++){
		int indexCluster = 1;
		double distance = matrix[i].Euclidean(vc[1]);
		for(int j=2; j<=nCluster; j++){
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
	for(int i=1; i<=nSet; i++){
		vc[map[i]] = vc[map[i]] + matrix[i];
	}
	for(int i=1; i<=nCluster; i++){
		vc[i] = vc[i]*(1.0/nc[i]);
	}


	while(notDone){
		RandomPartion();
		notDone = false;
		for(int i=1; i<=nSet; i++){
			if(nc[map[i]] == 1)	continue;
			vc[map[i]] = (vc[map[i]]*nc[map[i]] - matrix[i])*(1.0/(nc[map[i]] - 1));
			nc[map[i]]--;

			int indexCluster = 1;
			double newDistance;
			X tmp;
			tmp.dimension = dimension;
			tmp.data.resize(dimension+1);
			tmp = (vc[1]*nc[1] + matrix[i])*(1.0/(nc[1] + 1));
			double distance = matrix[i].Euclidean(vc[1]) + matrix[i].Euclidean(tmp);
			for(int j=2; j<=nCluster; j++){
				tmp = (vc[j]*nc[j] + matrix[i])*(1.0/(nc[j] + 1));
				newDistance = matrix[i].Euclidean(vc[j]) + matrix[i].Euclidean(tmp);
				if(distance > newDistance){
					distance = newDistance;
					indexCluster = j;
				}
			}
			if(indexCluster == map[i]){
				vc[map[i]] = (vc[map[i]]*nc[map[i]] + matrix[i])*(1.0/(nc[map[i]] + 1));
				nc[map[i]]++;
			}
			else{
				map[i] = indexCluster;
				vc[map[i]] = (vc[map[i]]*nc[map[i]] + matrix[i])*(1.0/(nc[map[i]] + 1));
				nc[map[i]]++;
				notDone = true;
				break;
			}


		}

	}
	newfunc = TargetFunc();
}

void K_Means::print()
{
	cout << "filename:  " << filename ;
	cout << "              result: " << newfunc << endl;
}