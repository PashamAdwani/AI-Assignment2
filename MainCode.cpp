#include<iostream>
#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include<fstream>
#include<chrono>

using namespace std;

int np,kp,qp,qpp,kpp,finalkpp; //number of knights Queens and board dimensions
int posQ[10][2],posK[10][2],finalposK[10][2];
int conflict[1000];
int timediff[1000];
int xo[100][2];
double tmax;

struct CB //chessbord structure
{
	int r;
	int c;
	int canQueen; //bool -> 0 - No and 1-yes
	int canKnight;//bool -> 0 - No and 1-yes
}cb[10][10];

void checkConflict(int h)
{
	int i,j,k,l;
	conflict[h]=0;
	for(i=0;i<qpp;i++)
	{
		for(j=0;j<finalkpp;j++)
		{
			if(finalposK[j][0]==posQ[i][0] || finalposK[j][1]==posQ[i][1] || finalposK[j][0]==posQ[i][1] ||finalposK[j][1]==posQ[i][0])
			conflict[h]=conflict[h]+1;
			
			for(l=0;l<np;l++)
			{
				if(finalposK[j][0]+l==posQ[i][0] && finalposK[j][1]+l==posQ[i][1])
				conflict[h]=conflict[h]+1;
				if(finalposK[j][0]-l==posQ[i][0] && finalposK[j][1]-l==posQ[i][1])
				conflict[h]=conflict[h]+1;
				if(finalposK[j][0]-l==posQ[i][0] && finalposK[j][1]+l==posQ[i][1])
				conflict[h]=conflict[h]+1;
				if(finalposK[j][0]+l==posQ[i][0] && finalposK[j][1]-l==posQ[i][1])
				conflict[h]=conflict[h]+1;
			}
			
		}
	}
}

void GameRule3()
{
	int i,r,c,j;
	for(i=2;i<kpp;i++)
    {
   	     if(posK[i][0]-2>=0)
		{
			if(posK[i][1]+1<np)
			{
				r=posK[i][0]-2;
				c=posK[i][1]+1;
				//cout<<"\nYo1-1";
				cb[r][c].canKnight=0;
			}
			if(posK[i][1]-1>=0)
			{
				r=posK[i][0]-2;
				c=posK[i][1]-1;
				//cout<<"\nYo1-2";
				cb[r][c].canKnight=0;
			}
		}
		if(posK[i][0]+2<np)
		{
			if(posK[i][1]+1<np)
			{
				r=posK[i][0]+2;
				c=posK[i][1]+1;
				//cout<<"\nYo1-3";
				cb[r][c].canKnight=0;
			}
			if(posK[i][1]-1>=0)
			{
				r=posK[i][0]+2;
				c=posK[i][1]-1;
				//cout<<"\nYo1-4";
				cb[r][c].canKnight=0;
			}
		}
		if(posK[i][1]-2>=0)
		{
			if(posK[i][0]+1<np)
			{
				r=posK[i][0]+1;
				c=posK[i][1]-2;
				//cout<<"\nYo1-5";
				cb[r][c].canKnight=0;
			}
			if(posK[i][0]-1>=0)
			{
				r=posK[i][0]-1;
				c=posK[i][1]-2;
				//cout<<"\nYo1-6";
				cb[r][c].canKnight=0;
			}
		}
		if(posK[i][1]+2<np)
		{
			if(posK[i][0]+1<np)
			{
				r=posK[i][0]+1;
				c=posK[i][1]+2;
				//cout<<"\nYo1-7";
				cb[r][c].canKnight=0;
			}
			if(posK[i][0]-1>=0)
			{
				r=posK[i][0]-1;
				c=posK[i][1]+2;
				//cout<<"\nYo1-8";
				cb[r][c].canKnight=0;
			}
		} 	
	}	
	
	for(i=0;i<np;i++)
	{
		for(j=0;j<np;j++)
		{
			if(cb[i][j].canKnight==1)
			{
				//cout<<"\nYo";
				posK[finalkpp][0]=i;
				posK[finalkpp][1]=j;
				finalkpp=finalkpp+1;
			}
		}
	}
}


void GameRule2()
{
	int i,j,r,c;
	for(i=0;i<=qpp;i++)
	{
		if(posQ[i][0]-2>=0)
		{
			if(posQ[i][1]+1<np)
			{
				r=posQ[i][0]-2;
				c=posQ[i][1]+1;
				//cout<<"\nYo1-1";
				cb[r][c].canKnight=0;
			}
			if(posQ[i][1]-1>=0)
			{
				r=posQ[i][0]-2;
				c=posQ[i][1]-1;
				//cout<<"\nYo1-2";
				cb[r][c].canKnight=0;
			}
		}
		if(posQ[i][0]+2<np)
		{
			if(posQ[i][1]+1<np)
			{
				r=posQ[i][0]+2;
				c=posQ[i][1]+1;
				//cout<<"\nYo1-3";
				cb[r][c].canKnight=0;
			}
			if(posQ[i][1]-1>=0)
			{
				r=posQ[i][0]+2;
				c=posQ[i][1]-1;
				//cout<<"\nYo1-4";
				cb[r][c].canKnight=0;
			}
		}
		if(posQ[i][1]-2>=0)
		{
			if(posQ[i][0]+1<np)
			{
				r=posQ[i][0]+1;
				c=posQ[i][1]-2;
				//cout<<"\nYo1-5";
				cb[r][c].canKnight=0;
			}
			if(posQ[i][0]-1>=0)
			{
				r=posQ[i][0]-1;
				c=posQ[i][1]-2;
				//cout<<"\nYo1-6";
				cb[r][c].canKnight=0;
			}
		}
		if(posQ[i][1]+2<np)
		{
			if(posQ[i][0]+1<np)
			{
				r=posQ[i][0]+1;
				c=posQ[i][1]+2;
				//cout<<"\nYo1-7";
				cb[r][c].canKnight=0;
			}
			if(posQ[i][0]-1>=0)
			{
				r=posQ[i][0]-1;
				c=posQ[i][1]+2;
				//cout<<"\nYo1-8";
				cb[r][c].canKnight=0;
			}
		}
	}
	
	for(i=0;i<np;i++)
	{
		for(j=0;j<np;j++)
		{
			if(cb[i][j].canKnight==1)
			{
				//cout<<"\nYo";
				posK[kpp][0]=i;
				posK[kpp][1]=j;
				kpp=kpp+1;
			}
		}
	}
}


void GameRule1(int r,int c)
{
	posQ[qpp][0]=r;
	posQ[qpp][1]=c;
	for(int n=0;n<np;n++)
	{
		cb[r][c].canQueen=0;
		cb[r][n].canQueen=0;
		cb[n][c].canQueen=0;
		if(r+n<np)
		{
		    cb[r+n][c+n].canQueen=0;
			//cout<<"\nYo";
		    if(r-n>=0)
		    {
		    	cb[r+n][c-n].canQueen=0;
		    	cb[r-n][c+n].canQueen=0;
			}
		}
		
		
		if(r-n>=0)//diagonals
		{
			cb[r-n][c-n].canQueen=0;
			//cout<<"\nYo";
		}
	}

}

void experimental(int randQC,int randQR)
{
	int i,j,k;
	qpp=0;
	kpp=0;
	finalkpp=0;
	
	for(k=0;k<np*np;k++)
	{
	for(i=0;i<np;i++)
	{
		for(j=0;j<np;j++)
		{
		  cb[i][j].r=i;
		  cb[i][j].c=j;
		  cb[i][j].canQueen=1;
		  cb[i][j].canKnight=1;	
		}
	}
	}
	
//for first Queen
GameRule1(randQR,randQC);
qpp=qpp+1;	
for(i=0;i<np;i++)
{
	for(j=0;j<np;j++)
	{
		if(cb[i][j].canQueen==1)
		{
			GameRule1(i,j);
			//cout<<"\n"<<i<<j;
			
			qpp=qpp+1;
			
			cb[i][j].canKnight=0;//so that the knight doesnt co-incide with queen
		}
	}
}

	for(i=0;i<qp;i++)
	{
		cout<<"\nPos Queen:"<<i<<":"<<posQ[i][0]<<posQ[i][1];
	}
	
	GameRule2();
	//for(i=0;i<kpp;i++)
	//{
	//	cout<<"\nPos Knight:"<<i<<":"<<posK[i][0]<<posK[i][1];
	//}

	cout<<"\nExperimental after Game3:";
	GameRule3();
	for(i=0;i<kp;i++)
	{
		cout<<"\nPos Knight:"<<i<<":"<<posK[i][0]<<posK[i][1];
	}	
}

int HillClimbing(int k)//k is total number of samples
{
	 int i,j,smallind;
	 	smallind=0;
	 	for(j=1;j<k;j++)
	 	{
	 		if(timediff[j]<=tmax)
			 {
			 	if(conflict[smallind]>=conflict[j])
			 	{
			 	  smallind=j;	
				}
			 }	
		}
		return smallind;
}
	

int main()
{
	int i,j,k,sindex,m,cnt;
	cout<<"\nEnter n - Board Dimensions:";
	cin>>np;
	cout<<"\nEnter number of Queen:";
	cin>>qp;
	cout<<"\nEnter number of Knights:";
	cin>>kp;
	cout<<"\nEnter tmax in microseconds (enter 25000 if not sure):";
	cin>>tmax;
	k=0;
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
			experimental(i,j);
			xo[k][0]=i;
			xo[k][1]=j;
			std::chrono::steady_clock::time_point end= std::chrono::steady_clock::now();
			timediff[k]=std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
			checkConflict(k);
			cout<<"\nTime Taken:"<<timediff[k];
			cout<<"\nNumber of Conflicts:"<<conflict[k];
			k=k+1;
		}
	}
	sindex=HillClimbing(k);
	cout<<"\n============================";
	cout<<"\nIndex That has least number of Conflicts:"<<sindex;
	cout<<"\nConflicts:"<<conflict[sindex];
	experimental(xo[sindex][0],xo[sindex][1]);
	cout<<endl;
	ofstream fout;
	fout.open("solution.txt",ios::out);
	for(i=0;i<np;i++)
	{
		for(j=0;j<np;j++)
		{
			cnt=0;
		  for(m=0;m<kp;m++)
		  {
		  	if(cb[i][j].r==posK[m][0] && cb[i][j].c==posK[m][1])
		  	{
		  		cout<<"|K";
		  		fout<<"|K";
		  		cnt=1;
			}
			
		  }
		  for(m=0;m<qp;m++)
		  {
		  	if(cb[i][j].r==posQ[m][0] && cb[i][j].c==posQ[m][1])
		  	{
		  		cout<<"|Q";
		  		fout<<"|Q";
				cnt=1;	
			}
		  }
		  if(cnt==0)
		  {
		  	cout<<"| ";
		  	fout<<"| ";
		  }
		}
		cout<<"|"<<endl;
		fout<<"|"<<endl;
	}
	fout.close();
	cout<<"\nThis Solution can also be seen in file solution.txt";
	return 0;
}
