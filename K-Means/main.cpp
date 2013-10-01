#include "K-means.h"

using namespace std;

int main()
{
	string filename;
	int n,m,k;
	double t;
	cin >> filename >> n >> m >> k >> t;
	K_Means * k =new K_Means(filename,n,m,k,t);
	k->ReadData();
	k->RandomPartion();
	k->Lloyd();
	k->print();
	k->online();
	k->print();
	k->Hartigan();
	k->print();
	return 0;
}