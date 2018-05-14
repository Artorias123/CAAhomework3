#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "math.h"
using namespace std;
const extern double C[3]={0.1,0.6,0.3},q[3][3]={0.333333333333,0.857142857143,1.833333333333,0.166666666667,
0.833333333333,0.333333333333,0.333333333333,0.833333333333,0.1666666666667};

double f(double t)
{
	double y;
	y = exp(-log(2)*pow((t-15) / 3, 2))/2;
	return (y);
}
int mod(int a, int b)
{
 return (a + b) % b;
}

class grid
{
public:
	vector<double> g;
	double begin,end;
	grid(double begin, double end, unsigned m);
	grid(grid &x);
	grid(){};
	~grid(){};
	double space();
	int initial(grid &x);
	int initial(double* a,unsigned m);
	void prt_all(ofstream fout);
    void show();
	void result(ofstream &fout,int m = 1);
	void save(ofstream &fout);
	void load(ifstream &fin);
};
grid::grid(double b, double e, unsigned m){
	unsigned n = m + 1;
    begin=b;end=n;
	g.resize(n);
	for (int i = 0; i < n; i++)
	{
		g[i]=begin + i*(end - begin) / m;
	}
}
grid::grid(grid &x){
	g = x.g;
	begin = x.begin;
    end=x.end;
}
double grid::space(){
	return (end-begin)/(g.size()-1);
}
int grid::initial(grid &x){
	g = x.g;
	begin = x.begin;
    end =x.end;
	return 0;
}
int grid::initial(double* a,unsigned m){
	for (unsigned i = 0; i < m; i++)
	{
		g[i] = a[i];
	}
	return 0;
}
void grid::result(ofstream &fout,int m){
	for (unsigned i = 0; i < g.size(); i=i+m)
	{
		fout << g[i] << '\t';
	}
	fout << endl;
}
void grid::save(ofstream &fout){
    fout<<begin<<'t'<<end<<endl;
    for (unsigned i = 0; i < g.size(); i=i)
	{
		fout << g[i] << '\t';
	}
	fout << endl;
}
void grid::load(ifstream &fin){
    fin>>begin>>end;
    for (unsigned i = 0; i < g.size(); i=i)
	{
		fin >> g[i];
	}
}

class calculator
{
public:
	unsigned step = 0, total_step,ds;
	double c, d_t, t;
    grid *p;
	calculator(grid &x,double ic, double dt, unsigned m,unsigned autosave);
	~calculator(){};
	void save();
	void load(double ic, double dt, unsigned m,unsigned autosave);
	void advance();
	void iteration(int s = 0);
};
calculator::calculator(grid &x,double ic, double dt, unsigned m,unsigned autosave=0)
{
	p=&x;
	c=ic;
	d_t=dt;
	t=0;
	total_step=m;
	ds=autosave;
}
void calculator::save()
{
	ofstream fout("save.dat",ios::out|ios::trunc);
	fout<<t<<endl;
	p->save(fout);
}
void calculator::load(double ic, double dt, unsigned m,unsigned autosave=0)
{
	ifstream fin("save.dat",ios::in);
	fin>>t;
	c=ic;
	d_t=dt;
	total_step=m;
	ds=autosave;
}
void calculator::advance()
{
	
}