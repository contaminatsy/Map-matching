#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#include<vector>
#include<cstring>
#define R 6371000
#define PI acos(-1)
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
vector<int> intersect[500000];

int N,M;

double spheredis(point x,point y)//地球大圆距离 
{
	double delx,dely;
	dely=R*(abs(x.latitude-y.latitude)/180*PI);
	delx=R*(abs(x.longtitude-y.longtitude)/180*PI);
	return sqrt(delx*delx+dely*dely);//由于相差较小，进行近似处理 
}

point ptrnearest(point p,road r)//点到路的最近点 
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

double ptpviar(point x,point y,int r1,int r2)//点到点在路径上的距离
{
	
} 

void input_measured_point(vector<point> &track)//读入轨迹（暂时没用） 
{
	point x;
	while(scanf("%d %lf %lf",&x.time,&x.latitude,&x.longtitude)>0)
		track.push_back(x);
	return;
}

void input_road(vector<road> &roadmap)		//读入路段 
{
	road x;
	point y;
	double len=0;
	char c[20];
		scanf("%d",&x.id);
		scanf("%d%d",&x.start,&x.end);
		intersect[x.start].push_back(x.id);
		intersect[x.end].push_back(x.id);
		scanf("%s",&c);
		//可以考虑道路等级，处理c
		scanf("%d",&x.level); 
		scanf("%d",&x.segnum);
		for(int i=0;i<x.segnum;i++)
		{
			scanf("%lf%lf",&y.longtitude,&y.latitude);
			x.seg.push_back(y);
		}
		for(int i=1;i<x.segnum;i++)
		{
			len+=spheredis(x.seg[i],x.seg[i-1]);
		}
		roadmap.push_back(x);
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
	
	for(int i=0;i<M;i++)
	{
		int t,x,y;
		point temp;
		track.clear();
		while(1)
		{
			scanf("%d",&t);
			if(t==i)break;
			scanf("%lf%lf",&temp.longtitude,&temp.latitude);
			temp.time=t;
			track.push_back(temp);
		}
		int tlen=track.size();
		{	for(int i=0;i<tlen;i++)//direct pair with the distance to the road
		{
			point ans={0,0,-1};
			int rid=0;
			for(int j=0;j<N;j++)
			{
				point update;
				update=ptrnearest(track[i],roadmap[j]);
				//printf("update %lf %lf\n",)
				if(ans.time==-1)
				{
					ans=update;
					rid=j;
				}
				else if(spheredis(ans,track[i])>spheredis(update,track[i]))
				{
					ans.latitude=update.latitude;
					ans.longtitude=update.longtitude;
					rid=j;
				}
			}
			printf("%d ",rid);
		}
		printf("\n");}
	}
	return 0;
}
