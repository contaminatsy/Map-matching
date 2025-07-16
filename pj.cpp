#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#include<vector>
#include<map>
#include<set>
#include<queue> 
#include<cstring>
#define R (6371000)
#define PI (acos(-1))
#define XR 	121
#define YR	30.5
#define DIS (5e-4)
#define SIGZ 1.4826 
using namespace std;

typedef struct point{
	double latitude,longtitude;
	int time;
}point;

typedef struct road{
	int id,start,end,level,segnum;
	vector<point> seg;
	double len;
}road;
vector<point> track;
vector<road> roadmap;
vector<road> intersect[500000];

set<int> block[2000][3000]={};

int N,M;
double maxlati=0,minlati=90,maxlongti=0,minlongti=360;

double spheredis(point x,point y)//�����Բ���� 
{
	double delx,dely;
	dely=R*(abs(x.latitude-y.latitude)/180*PI);
	delx=R*(abs(x.longtitude-y.longtitude)/180*PI);
	return sqrt(delx*delx+dely*dely);//��������С�����н��ƴ��� 
}

point ptrnearest(point p,road r)//�㵽·������� 
{
	double minn=-1,adis,dis,a,b;
	point ret={0,0,-1};
	a=p.longtitude;
	b=p.latitude;
	for(int i=1;i<r.segnum;i++)
	{
		point segp;
		point x=r.seg[i-1],y=r.seg[i];
		if(x.latitude==y.latitude)
		{
			if(p.longtitude>x.longtitude&&p.longtitude>y.longtitude)
			{
				segp.latitude=x.latitude;
				segp.longtitude=max(x.longtitude,y.longtitude);
			}
			else if(p.longtitude<x.longtitude&&p.longtitude<y.longtitude)
			{
				segp.latitude=x.latitude;
				segp.longtitude=min(x.longtitude,y.longtitude);
			}
			else
			{
				segp.latitude=x.latitude;
				segp.longtitude=p.longtitude;
			}
		}
		else if(x.longtitude==y.longtitude)
		{
			if(p.latitude>x.latitude&&p.latitude>y.latitude)
			{
				segp.latitude=max(x.latitude,y.latitude);
				segp.longtitude=x.longtitude;
			}
			else if(p.latitude<x.latitude&&p.latitude<y.latitude)
			{
				segp.latitude=min(x.latitude,y.latitude);
				segp.longtitude=x.longtitude;
			}
			else
			{
				segp.latitude=p.latitude;
				segp.longtitude=x.longtitude;
			}
		}
		else
		{
			double k=(x.longtitude-y.longtitude)/(x.latitude-y.latitude);
			double d=x.longtitude-x.latitude*k;
			segp.latitude=(segp.longtitude+1/k*segp.latitude-d)/(k+1/k);
			if(segp.longtitude>x.longtitude&&segp.longtitude>y.longtitude)
			{
				segp.latitude=max(x.latitude,y.latitude);
			}
			else if(segp.longtitude<x.longtitude&&segp.longtitude<y.longtitude)
			{
				segp.latitude=min(x.latitude,y.latitude);
			}
			segp.longtitude=k*segp.latitude+d;
		}
		if(ret.time==-1)
		{
			ret.time=0; ret.latitude=segp.latitude; ret.longtitude=segp.longtitude;
		}
		else if(spheredis(p,ret)>spheredis(p,segp))
		{
			ret.latitude=segp.latitude; ret.longtitude=segp.longtitude;
		}
	//	if(minn==-1||minn)
	}
	return ret;
}

void measured_p(point p,double mprob[],set<int> blo)
{
	int blen=blo.size();
	double distr[100],distrst[100];
	for(int i=0;i<blen;i++)
	{
		distr[i]=spheredis(p,ptrnearest(p,roadmap[*(blo.begin()+i)]));
		distrst[i]=distr[i];
	}
		
	sort(distr,distr+blen);
	double mid=(distr[blen/2]+distr[(blen+1)/2])/2;
	for(int i=0;i<blen;i++)
	{
		double mult1,mult2;
		mult1=1/(sqrt(2*PI)*SIGZ*mid);
		mult2=exp(-0.5*pow(spheredis(p,ptrnearest(p,roadmap[*(blo.begin()+i)]))/(SIGZ*mid),2));
		mprob[i]=mult1*mult2;
	}
	return;
}

double roaddis(point p1,int id1,point p2,int id2,set<int> blo)
{
	int blen=blo.size;
	double cost[100]={};
	double len1b=0,len1e=0,len2b=0,len2e=0;
	int bp1,bp2,ep1,ep2;
	road r;
	r=roadmap[*(blo.begin()+id1)]
	for(int i=1;i<r.segnum;i++)			//get the dis to begin point and end point
	{
		point x=r.seg[i-1],y=r.seg[i];
		if((p1.latitude-x.latitude)*(p1.longtitude-y.longtitude)-(p1.latitude-y.latitude)*(p1.longtitude-x.longtitude)<1e-7)
		{
			len1b+=spheredis(x,p1);
			break;
		}
		len1b+=spheredis(x,y);
	}
	len1e=r.len-len1b;
	bp1=r.start;	ep1=r.end;

	r=roadmap[*(blo.begin()+id2)]
	for(int i=1;i<r.segnum;i++)
	{
		point x=r.seg[i-1],y=r.seg[i];
		if((p2.latitude-x.latitude)*(p2.longtitude-y.longtitude)-(p2.latitude-y.latitude)*(p2.longtitude-x.longtitude)<1e-7)
		{
			len2b+=spheredis(x,p2);
			break;
		}
		len2b+=spheredis(x,y);
	}
	len2e=r.len-len2b;
	bp2=r.start;	ep2=r.end;
	vector<int> vis;
	for(int i=0;i<blen;i++)
	{
		vis.push_back(roadmap[*(blo.begin()+i)].id);
	}

	for(int i=0;i<blen;i++)
	{

	}

}




double sectsec(int s1,int s2,vector<road> rmap)//�㵽����·���ϵľ���
{
	int size=rmap.size();
	int *visited;
	 
} 

void input_measured_point(vector<point> &track)//����켣����ʱû�ã� 
{
	point x;
	while(scanf("%d %lf %lf",&x.time,&x.latitude,&x.longtitude)>0)
		track.push_back(x);
	return;
}

void input_road(vector<road> &roadmap)		//����·�� 
{
	road x;
	point y;
	int xb,yb;
	double len=0;
	char c[20];
		scanf("%d",&x.id);
		scanf("%d%d",&x.start,&x.end);
		scanf("%s",&c);
		//���Կ��ǵ�·�ȼ�������c
		scanf("%d",&x.level); 
		scanf("%d",&x.segnum);
		for(int i=0;i<x.segnum;i++)
		{
			scanf("%lf%lf",&y.latitude,&y.longtitude);
			x.seg.push_back(y);
			xb=(y.longtitude-XR)/DIS;
			yb=(y.latitude-YR)/DIS;
			for(int j=-1;j<=1;j++)
				for(int k=-1;k<=1;k++)
					block[xb+j][yb+k].insert(x.id);
		//	maxlongti=max(maxlongti,y.longtitude);
		//	minlongti=min(minlongti,y.longtitude);
		//	maxlati=max(maxlati,y.latitude);
		//	minlati=min(minlati,y.latitude);
		}
		for(int i=1;i<x.segnum;i++)
		{
			len+=spheredis(x.seg[i],x.seg[i-1]);
		}
		roadmap.push_back(x);
		intersect[x.start].push_back(x);
		intersect[x.end].push_back(x);
		/*for(int i=1;i<x.segnum;i++)
			if(abs(x.seg[i].latitude-x.seg[i-1].latitude)<1e-8)printf("id:%d x1=%lf, x2=%lf\n",x.id,x.seg[i].latitude,x.seg[i-1].latitude);
		/*check if there's a road segment still on the same latitude*/
}


int main()
{
	freopen("sample.in","r",stdin);
	freopen("pjout.out","w",stdout);
	scanf("%d",&N);
	for(int i=0;i<N;i++)
	{
		input_road(roadmap);
	}
	scanf("%d",&M);
	printf("maxlati=%lf, minlati=%lf, maxlongti=%lf, minlongti=%lf/n",maxlati,minlati,maxlongti,minlongti);
	for(int i=0;i<M;i++)
	{
		int t,x,y;
		point temp;
		track.clear();
		while(1)
		{
			scanf("%d",&t);
			if(t==i)break;
			scanf("%lf%lf",&temp.latitude,&temp.longtitude);
			temp.time=t;
			track.push_back(temp);
		}
		int tlen=track.size();
		int xb,yb;
		double *mprob;
		double *pnear;// previous 
		double tprob[100]={};
		
		for(int j=0;j<tlen;j++)
		{
			double tempprob[100]={};
			double temppnear[100]={};// now
			xb=(track[j].longtitude-XR)/DIS;
			yb=(track[j].latitude-YR)/DIS;
			
			int blen=block[xb][yb].size();			//only consider trasition in one area
			for(int k=0;k<blen;k++)
				temppnear[k]=ptrnearest(p,roadmap[*(block[xb][yb].begin+k)]);
			
			
			measured_p(track[j],tempprob,block[xb][yb]);//complete the measured probability
			
			if(j==0)
			{
				mprob=tempprob;					//store for next cycle
                pnear=temppnear;
				break;
			}
			
			for(int k=0;k<blen;k++)
			{
				
			}
            double mult[100]={};
            for(int k=0;k<blen;k++)
            {
				double rodis[100];
				for(int l=0;l<blen;l++)
				{
					double s_dis=spheredis(pnear[k],temppnear[l]);

					rodis[l]=routedis(pnear[k],k,temppnear[l],l,block[xb][yb]);
					rodistemp[l]=rodis[l];
				}

				sort(rodistemp,rodistemp+blen);
				double midsdis=(rodistemp[blen/2]+todistemp[(blen+1)/2])/2;
				double beta=midsdis/log(2);
				for(int l=0;l<blen;l++)
				{
					double dt=spheredis(pnear[k],temppnear[l]);
					tprob[l]=1.0/beta*exp(-dt/beta);
				}
																//complete trasition probability				
                mult[k]=0;
                for(int l=0;l<blen;l++)
                    mult[k]+=mprob[l]*tprob[k];
                tempprob[k]*=mult[k];
            }
			int maxn=0,u=0;
			for(int k=0;k<ble;k++)
			{
				if(maxn<tempprob[k])
				{
					maxn=tempprob[k];
					u=k;
				}
			}
			printf("%d ",k);
			mprob=tempprob;
            pnear=temppnear;
		}
		printf("\n");
	}
	return 0;
}
