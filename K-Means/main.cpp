#include "K-means.h"

#ifdef _CHAR16T
#define CHAR16_T
#endif

#include <mat.h>
using namespace std;

int main()
{
	string filename;
	int n,m,k;
	double t;
	cin >> filename >> k >> t;
	
	MATFile *pmatFile = NULL;  
	mxArray *pMxArray = NULL;  

	// 读取.mat文件（例：mat文件名为"initUrban.mat"，其中包含"initA"）  
	double *normal1;  

	pmatFile = matOpen(filename.c_str(),"r");  
	pMxArray = matGetVariable(pmatFile, "normal1");  
	normal1 = (double*) mxGetData(pMxArray);  
	m = mxGetM(pMxArray);  
	n = mxGetN(pMxArray);  
	K_Means * kmeans =new K_Means(filename,n,m,k,t);
	
	for (int i=0; i<n; i++)  
		for (int j=0; j<m; j++)  
			kmeans->matrix[i+1].data[j+1] = normal1[m*i+j];  
	

	matClose(pmatFile);  
	mxFree(normal1);

	
	//kmeans->ReadData();
	kmeans->Normalize();
	kmeans->RandomPartion();
	kmeans->Lloyd();
	kmeans->print("Lloyd");
	kmeans->RandomPartion();
	kmeans->online();
	kmeans->print("online");
	kmeans->RandomPartion();
	kmeans->Hartigan();
	kmeans->print("Hartigan");
	return 0;
}

/*

int main(int argc, char *argv[])
{
	string filename(argv[1]);
	int n,m,k;
	double t;
	sscanf(argv[2], "%d", &k);
	sscanf(argv[3], "%lf", &t);
	cout << filename << "   k: "  << k << "   t: " << t << endl; 

	MATFile *pmatFile = NULL;  
	mxArray *pMxArray = NULL;  

	// 读取.mat文件（例：mat文件名为"initUrban.mat"，其中包含"initA"）  
	double *normal1;  

	pmatFile = matOpen(filename.c_str(),"r");  
	pMxArray = matGetVariable(pmatFile, "normal1");  
	normal1 = (double*) mxGetData(pMxArray);  
	m = mxGetM(pMxArray);  
	n = mxGetN(pMxArray);  
	K_Means * kmeans =new K_Means(filename,n,m,k,t);

	for (int i=0; i<n; i++)  
		for (int j=0; j<m; j++)  
			kmeans->matrix[i+1].data[j+1] = normal1[m*i+j];  


	matClose(pmatFile);  
	mxFree(normal1);


	//kmeans->ReadData();
	kmeans->Normalize();
	kmeans->RandomPartion();
	kmeans->Lloyd();
	kmeans->print("Lloyd");
	kmeans->RandomPartion();
	kmeans->online();
	kmeans->print("online");
	kmeans->RandomPartion();
	kmeans->Hartigan();
	kmeans->print("Hartigan");
	return 0;
}

*/