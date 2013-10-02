#include "K-means.h"

using namespace std;

int main()
{
	string filename;
	int n,m,k;
	double t;
	cin >> filename >> n >> m >> k >> t;
	K_Means * kmeans =new K_Means(filename,n,m,k,t);
	kmeans->ReadData();
	kmeans->RandomPartion();
	kmeans->Lloyd();
	kmeans->print();
	kmeans->RandomPartion();
	kmeans->online();
	kmeans->print();
	kmeans->RandomPartion();
	kmeans->Hartigan();
	kmeans->print();
	return 0;
}