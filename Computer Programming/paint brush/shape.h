#ifndef shape_h
#define shape_h
#include<vector>
#include<iostream>
#include<fstream>
#include"GP142.h"
using namespace std;
struct Point
{
	double x;
	double y;
};
struct Point1
{
	double x;
	double y;
	double z;
};
class shape
{
protected:
	Point** d;
	int color;
	int numberofPoint;
	int fillco;
	Point c;
public:
	shape();
	shape(int colo, Point* q, int n,int f,Point a);
	virtual void setf(int fill)=0;
	virtual void setc(Point p) = 0;
	virtual	void draw() = 0;
	virtual bool containspoint(Point) = 0;
    virtual int type() = 0;
    virtual void filesave() = 0;
    virtual void fill(int,int,int) = 0;
	virtual void fill1(int, int, int) = 0;
	void fileload();

};
class triangle :public shape
{

public:
	void draw();
	void fill(int x, int y, int colo);
	void fill1(int, int, int);
	bool containspoint(Point p);
	
	triangle();
	triangle(int col, Point* p, int number, int fil,Point a);
	void setc(Point p)
	{
		c.x = p.x;
		c.y = p.y;
	}
	int type();
	void filesave();
	void setf(int fill);
};
class polygon :public shape{

public:
	
	
	void fill(int x, int y, int colo);
	polygon();
	void setc(Point p)
	{
		c.x = p.x;
		c.y = p.y;
	}
	polygon(int col, Point*p, int k,int f,Point a);
	void fill1(int, int, int);
    void draw();
    bool containspoint(Point p);
    void changeColor(int);
	int type();
	void setf(int fill);
	void filesave();
 
};
class rectangle :public polygon{
public:
	rectangle();
	rectangle(int c, Point* p, int n,int f,Point a);
	int type();
	void filesave();
	


};
class Circle :public shape
{

private:
	double radius;
public:
	void draw();
	void fill1(int, int, int);
	bool containspoint(Point p);
	void fill(int x, int y, int colo);
	void setc(Point p)
	{
		c.x = p.x;
		c.y = p.y;
	}
	Circle();
	Circle(int col, Point*p, int number, double r,int f,Point a);
	int type();
	void filesave();
	void setf(int fill);
};
class openshape :public shape
{
protected:
	bool style;
public:
	 void changecolor() ;
	openshape() :shape()
	{
		style = 0;
	}
	openshape(int col, Point* p, int nu, bool styl,int f,Point a)
		:shape(col,p,nu,f,a)
	{
		style = styl;
	}
	void setc(Point p)
	{
		c.x = p.x;
		c.y = p.y;
	}
	int type()
	{
		return 100;
	}

	void draw();
	void fill1(int, int, int){}
	bool containspoint(Point);
	void setf(int fill){
		color = fill;
		draw();
	
	}
	void fill(int a, int b, int)
	{}

	
};
class line :public openshape
{
public:
	bool containpoint(Point);
	void changecolor()
	{}
	line():
		openshape()
	{

	}
	line(int col, Point* p, int nu,bool styl,int f,Point a)
		:openshape(col,p,nu,styl,f,a)
	{

	}
	int type()
	{
		return 5;
	}
	void filesave()
	{
		ofstream of;
		of.open("Example.txt", ios::app);
		of << 5 << endl;
		of << numberofPoint << endl;
		of << color << endl;
		of << fillco << endl;
		of << 0 << endl;
		of << c.x << endl;
		of << c.y << endl;

  		for (int j = 0; j < numberofPoint; j++)
		{
			of << d[j]->x << "," << d[j]->y << endl;
		}

	}
	
};
class curve :public openshape
{
public:
	
	bool containpoint(Point)
	{
		return 0;
	}
	void changecolor(){

	}
	curve(int col, Point* p, int nu, bool styl,int f,Point a)
		:openshape(col, p, nu, styl,f,a)
	{

	}
	curve()
		:openshape()
	{

	}
	int type()
	{
		return 6;
	}
	void filesave()
	{
		ofstream of;
		of.open("Example.txt", ios::app);
		of << 6 << endl;
		of << numberofPoint << endl;
		of << color << endl;
		of << fillco << endl;
		of << 0 << endl;
		of << c.x << endl;
		of << c.y << endl;

		for (int j = 0; j < numberofPoint; j++)
		{
			of << d[j]->x << "," << d[j]->y << endl;
		}
	  
	}
};
class text :public shape
{
	char* write;
	int zeal = 0;
public:
	void draw();
	bool containspoint(Point);
	text();
	int type();
	void fill(int, int, int);
	void fill1(int, int, int){}
	void filesave();
	void setf(int fill){
		color = fill;
		draw();
	}
	text(int colo, Point*p, int numbero, char* st, int z,int f,Point a);
	void setc(Point p)
	{
		c.x = p.x;
		c.y = p.y;
	}
};
#endif

