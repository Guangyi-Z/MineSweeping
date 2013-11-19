#include<iostream>
#include<ctime>
#include<cstdlib>
using namespace std;


//全局变量
const int size=9;

class Point
{
public:
	int x,y;
};



class Mine
{
public:
	int Mtime;
	int num_mine;
	int bar;
	int length;
	int side,upside;
	//有雷为-1，未翻开为-2，有雷且标记为-11，无雷且标记为-12，有雷且问号为-21，无雷且问号为-22，无信息为0，其余为周围雷的个数
	int m[size][size];


	//Functions----------------
	Mine()
	{
		Mtime=0;
		num_mine=10;                        //10
		bar=5;
		length=40;
		side=30;
		upside=50;
		for(int i=0;i<size ;i++)
			for(int j=0;j<size;j++)
				m[i][j]=-2;

	};
	//产生num_mine个雷，赋为-1
	void Initial()
	{
		srand ( time(0) );
		int count=0,temp,a,b;
		while(count< num_mine)
		{
			temp=rand()%81;
			a=temp/9;
			b=temp%9;
			if( m[a][b]==-1 )
				continue;
			else {
				count++;
				m[a][b]=-1;
			}
		}
	};
	//将数组下标转换为坐标
	Point retransform( int x,int y)
	{
		int xx=x*( length+bar)+side;
		int yy=y*( length+bar)+upside;
		Point p;
		p.x=xx;
		p.y=yy;
		return p;
	};
	
	//sym 0 for L；1 for LR,翻开周围的8块除了标记和问号的方块
	void Sweep( int xx, int yy,int sym )
	{
		Point p;
		p.x=xx;
		p.y=yy;
		if( m[p.x][p.y]== -1 || m[p.x][p.y]==-11 || m[p.x][p.y]==-21 )
			over();                                                          //?
		else if(  m[p.x][p.y]== -2 || m[p.x][p.y]==-12 || m[p.x][p.y]==-22 )
		{
			//回增雷数
			if(m[p.x][p.y]==-12)
				num_mine++;
			int count=0;
			int line=p.x-1, line2=p.x+1;
			int vertical=p.y-1, vertical2= p.y+1;
			for(int i=line;i<= line2; i++)
			{
				if(i<0 || i>8)
					continue;
				for(int j=vertical; j<=vertical2; j++)
				{
					if(j<0 || j>8)
						continue;
					if( m[i][j]==-1 || m[i][j]==-11 || m[i][j]==-21)
						count++;
					if(sym ==1)
					{
						if ( m[i][j]==-1)
							over();
						else if( m[i][j]==-11 || m[i][j]==-21 )
							;
						else if( m[i][j]==-2)
							Sweep(i,j,0);	
						else ;
					}
				}
			}
			m[p.x][p.y]=count;

			if(count ==0)
			{
				for(int i=line;i<= line2; i++)
				{
					if(i<0 || i>8)
						continue;
					for(int j=vertical; j<=vertical2; j++)
					{
						if(j<0 || j>8)
							continue;
						if( i==p.x && j==p.y )
							continue;
						else if( m[i][j]==-2 )
							Sweep(i,j,0);
						else ;
					}
				}
			}
		}
		//已经翻开的方格
		else;
	};
	//将坐标转换为数组下标
	Point transform( int x,int y)
	{
		int xx=(x-side)/(length+bar);
		int yy=(y-upside)/(length+bar);
		Point p;
		p.x=xx;
		p.y=yy;
		return p;
	};
	void Rdown( int xx,int yy)
	{
		Point p=transform( xx,yy);

		if( m[p.x][p.y]==-1 || m[p.x][p.y]== -21)
		{
			m[p.x][p.y]=-11;
			num_mine--;
		}
		else if( m[p.x][p.y]==-22 || m[p.x][p.y]==-2 )
		{
			m[p.x][p.y]=-12;
			num_mine--;
		}
		else ;
	};
	void Question( int xx,int yy)
	{
		Point p=transform( xx,yy);

		if( m[p.x][p.y]==-1 || m[p.x][p.y]== -11)
		{
			m[p.x][p.y]=-21;
		}
		else if( m[p.x][p.y]==-12 || m[p.x][p.y]==-2 )
		{
			m[p.x][p.y]=-22;
		}
		else ;
	};
	void firstclick(int x,int y )
	{
		if( m[x][y]== -1 )
			over();
		else
		{
			int count=0;
			int line=x-1,line2=x+1;
			int vertical=y-1,vertical2=y+1;
			for(int i=line;i<= line2; i++)
			{
				if(i<0 || i>8)
					continue;
				for(int j=vertical; j<=vertical2; j++)
				{
					if(j<0 || j>8)
						continue;
					if ( m[i][j]== -1 )
						count++;
				}
			}
			m[x][y]=count;

			if(count==0 )
			for(int i=line;i<= line2; i++)
			{
				if(i<0 || i>8)
					continue;
				for(int j=vertical; j<=vertical2; j++)
				{
					if(j<0 || j>8)
						continue;
					if ( m[i][j]== -2)
						firstclick( i,j);
				}
			}
		}
	
	};

	//-4 for bomp
	void over()
	{
		for(int i=0;i<size;i++)
			for(int j=0;j<size;j++)
			{
				//flag
				if( m[i][j]==-1|| m[i][j]==-11 || m[i][j]==-21 )
					m[i][j]=-4;
			}

	};

	
	

	////0 for blank,-1 for flag,-2 for question, -3for black
	//paint( char sym, point);
	//stoptime();
	//restarttime();*/

};

//扩展->更大规模
//退出函数