#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#include<vector>
#include<cstring> 

using namespace std;

typedef long long ll;

ll sum=0;
ll correct=0;

int main()
{
	FILE *f1=fopen("pjout.out","r");
	FILE *f2=fopen("sample.out","r");
	
	int x,y;
	while(fscanf(f1,"%d",&x)>0)
	{
		fscanf(f2,"%d",&y);
		if(x==y)correct++;
		sum++;
	}
	cout<<"sum="<<sum<<" correct="<<correct<<endl; 
	cout<<correct/(double)sum;
	return 0;
} 
