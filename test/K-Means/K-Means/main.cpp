#include "K-means.h"

#ifdef _CHAR16T
#define CHAR16_T
#endif


#include <mat.h>
using namespace std;

int s[17];

int main(int argc, char *argv[])
{
	//char *argv[21] = {"", "c:/test/normal1.mat", "normal1", "2", "0.01", "1", "1","1", "1","1", "1","1", "1","1", "1","2", "1","2", "1","2", "1"};
	string filename(argv[1]);
	string matrixname(argv[2]);
	int n,m,k;
	
	double t;
	sscanf(argv[3], "%d", &k);
	sscanf(argv[4], "%lf", &t);
	//cout << filename  << "     " << matrixname<< "   k: "  << k << "   t: " << t << endl; 
	for(int i=1; i<=16; i++){
		sscanf(argv[4+i], "%d", &s[i]);
	}
	MATFile *pmatFile = NULL;  
	mxArray *pMxArray = NULL;  

	// 读取.mat文件（例：mat文件名为"initUrban.mat"，其中包含"initA"）  
	double *normal1;  

	pmatFile = matOpen(filename.c_str(),"r");  
	pMxArray = matGetVariable(pmatFile, matrixname.c_str());  
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
//	kmeans->Normalize();
	kmeans->init(s);
	kmeans->Lloyd();
	kmeans->print("Lloyd");
	kmeans->init(s);
	kmeans->online();
	kmeans->print("online");
	kmeans->init(s);
	kmeans->Hartigan();
	kmeans->print("Hartigan");
	cout << endl;
	return 0;
}

/*
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

*/

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