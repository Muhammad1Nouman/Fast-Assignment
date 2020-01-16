# include"shape.h"
# include"GP142.H"
int k = 0;
int shap = 0;
int demo_handle_mouse(int x, int y);
int checkonShapes(int x, int y);
double dis(Point p, Point a);
struct fPoint
{
	float x;
	float y;

};
double CalcTriArea(fPoint v1, fPoint v2, fPoint v3);
shape::shape()                     /*constructor for main class*/
{
	d = nullptr;
	color = 0;
	numberofPoint = 0;
	fillco = 0;
	c.x = 0;
	c.y = 0;
}
shape::shape(int colo, Point* q, int n,int f,Point a)
{
	color = colo;
	numberofPoint = n;
	fillco = f;
	c.x = a.x;
	c.y = a.y;
	d = new Point*[n];

	for (int j = 0; j < n; j++)
		d[j] = new Point;
	for (int k = 0; k < n; k++)
	{
		d[k]->x = q[k].x;
		d[k]->y = q[k].y;
	}
	
}
void shape::fill(int x, int y, int colo)
{
	int g = GP142_GetColor(x, y);
	if (g == fillco)
	{
		//Sleep(1);
		GP142_pixelXY(colo, x, y);
		fill(x, y + 1, colo);
		fill1(x + 1, y, colo);

		fill1(x - 1, y, colo);
	}
	else
	{
		//	fillco = colo;
		return;
	}
}
void shape::fill1(int x, int y, int colo){
	int g = GP142_GetColor(x, y);
	if (g == fillco)
	{

	
		GP142_pixelXY(colo, x, y);
		fill1(x - 1, y, colo);
		fill(x, y - 1, colo);


		fill(x, y + 1, colo);
	}
	else
	{
		//fillco = colo;
		return;
	}
}
triangle::triangle()
:shape()
{
}
triangle::triangle(int col, Point* p, int number, int fil,Point a)
:shape(col, p, number,fil,a)
{
	
}
int triangle::type()
{
	return 1;
}
void triangle::filesave()
{
	ofstream of;
	of.open("Example.txt", ios::app);
	of << 1 << endl;
	of << numberofPoint << endl;
	of << color << endl;
	of << fillco << endl;
	of << c.x << endl;
	of << c.y << endl;
	for (int j = 0; j < numberofPoint; j++)
	{
		of << d[j]->x << "," << d[j]->y << endl;
	}
}
void triangle::draw()
{
	GP142_lineXY(color, d[0]->x, d[0]->y, d[1]->x, d[1]->y, 1);
	GP142_lineXY(color, d[1]->x, d[1]->y, d[2]->x, d[2]->y, 1);
	GP142_lineXY(color, d[0]->x, d[0]->y, d[2]->x, d[2]->y, 1);
	int po = GP142_GetColor(c.x,c.y);
	int cpu = fillco;
	if (cpu != 1)
	{
		setf(po);

		fill(c.x, c.y, cpu);
		fill1(c.x, c.y, cpu);
		setf(cpu);
	}

}
void Circle::draw()
{
	GP142_circleXY(color, d[0]->x, d[0]->y, radius);
	int po = fillco;
	if (po != 1)
	{
		setf(1);

		fill(c.x, c.y, po);
		fill1(c.x, c.y, po);
		setf(po);
	}
}
Circle::Circle()
:shape()
{
	radius = 0;
}
Circle::Circle(int col, Point*p, int number, double r,int f,Point a)
:shape(col, p, number,f,a)
{
	radius = r;
}
int Circle::type()
{
	return 3;
}
void Circle::filesave()
{
	ofstream of;
	of.open("Example.txt", ios::app);
	of << 3 << endl;
	of << numberofPoint << endl;
	of << color << endl;
	of << fillco << endl;
	of << c.x << endl;
	of << c.y << endl;
	of << radius << endl;
	
	for (int j = 0; j < numberofPoint; j++)
	{
		of << d[j]->x << "," << d[j]->y << endl;
	}
}
polygon::polygon()
:shape()
{

}
polygon::polygon(int col, Point*p, int k,int f,Point a)
:shape(col, p, k,f,a)
{

}
int polygon::type()
{
	return 4;
}
void polygon::filesave()
{
	ofstream of;
	of.open("Example.txt", ios::app);
	of << 4 << endl;
	of << numberofPoint << endl;
	of << color << endl;
	of << fillco << endl;
	of << c.x << endl;
	of << c.y << endl;

	for (int j = 0; j < numberofPoint; j++)
	{
		of << d[j]->x << "," << d[j]->y << endl;
	}
}
void polygon::draw()
{
	if (numberofPoint == 2)
	{

		GP142_lineXY(color, d[0]->x, d[0]->y, d[0]->x, d[1]->y, 1);
		GP142_lineXY(color, d[1]->x, d[1]->y, d[0]->x, d[1]->y, 1);
		GP142_lineXY(color, d[1]->x, d[1]->y, d[1]->x, d[0]->y, 1);
		GP142_lineXY(color, d[1]->x, d[0]->y, d[0]->x, d[0]->y, 1);
	}
	else
	{
		int k = 0;

		for (int j = 0; j < numberofPoint ; j++)
		{
			if ((k+1) < numberofPoint)
			{
		
				GP142_lineXY(color, d[k]->x, d[k]->y, d[k + 1]->x, d[k + 1]->y, 1);
				k++;
			}
			else
			{
				GP142_lineXY(color,d[k]->x,d[k]->y,d[0]->x,d[0]->y,1);
			}

		}

	}
	

}
rectangle::rectangle() :
polygon()
{

}
rectangle::rectangle(int c, Point* p, int n,int f,Point a) :
polygon(c, p, n,f,a)
{

}
int rectangle::type()
{
	return 2;
}
void rectangle::filesave()
{
	ofstream of;
	of.open("Example.txt", ios::app);
	of << 2 << endl;
	of << numberofPoint << endl;
	of << color << endl;
	of << fillco << endl;
	of << c.x << endl;
	of << c.y << endl;

	for (int j = 0; j < numberofPoint; j++)
	{
		of << d[j]->x << "," << d[j]->y << endl;
	}
}
void text::draw()
{
	  int typing_width = d[0]->x;      /* pixels   */
	  int typing_y = d[0]->y;       /* pixels   */
	const  int point_size = 20;
	static int key_count = 0;        /* count number of keypresses   */
	for (int i = 0; write[i]!='\0'; i++)
	{

		GP142_printfXY(color, typing_width, typing_y, point_size, "%c", write[i]);
		typing_width = typing_width + 20;
		if (typing_width >= 280)
		{
			typing_y= typing_y - 20;
			typing_width = -280;
			typing_width= typing_width + 50;
		}
		key_count = (key_count + 1);
	}
}
void openshape::draw()
{
	if (numberofPoint == 2)
	{
		GP142_lineXY(color, d[0]->x, d[0]->y, d[1]->x, d[1]->y, 1);
	}
	else
	{
		int k=0;
		for (int j = 0; j < numberofPoint; j++)
		{
			if ((k + 1) < numberofPoint)
			{

				GP142_lineXY(color, d[k]->x, d[k]->y, d[k + 1]->x, d[k + 1]->y, 1);
				k++;
			}
		}
	}
}
bool openshape::containspoint(Point p)
{
	Point a, a1;
	int k = 0;
	int yoyo = 0;
	if (numberofPoint == 2){
		
	
		a.x = d[0]->x;
		a.y = d[0]->y;
		a1.x = d[1]->x;
		a1.y = d[1]->y;

		int k = dis(a, p);
		int k1 = dis(a, a1);
		int k2 = dis(p, a1);
		if (k1 == k + k2)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		
		for (int j = 0; j < numberofPoint; j++)
		{
			if ((k + 1) < numberofPoint)
			{

				a.x = d[k]->x;
				a.y = d[k]->y;
				a1.x = d[k+1]->x;
				a1.y = d[k+1]->y;
				if (p.x == d[k]->x&&p.y == d[k]->y)
				{
					
					return true;
					break;
				}
				if (p.x == d[k+1]->x&&p.y == d[k+1]->y)
				{

					return true;
					break;
				}
				int k3 = dis(a, p);
				int k1 = dis(a, a1);
				int k2 = dis(p, a1);
				if (k1 == k3 + k2)
				{
					yoyo++;
					//return true;
				}
				
				k++;
			}
			
		}
		if (yoyo > 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}
bool triangle::containspoint(Point p)
{

	fPoint p1, p2, p3, p4;
		p1.x = p.x;
		p1.y = p.y;
		p2.x = d[0]->x;
		p2.y = d[0]->y;
		p3.x = d[1]->x;
		p3.y = d[1]->y;
		p4.x = d[2]->x;
		p4.y = d[2]->y;
		bool	b1 = CalcTriArea(p1, p2, p3) < 0.0f;
		bool	b2 = CalcTriArea(p1, p3, p4) < 0.0f;
		bool	b3 = CalcTriArea(p1, p4, p2) < 0.0f;
		return ((b1 == b2) && (b2 == b3));


}
void triangle::fill(int x, int y, int colo)
{
	int g = GP142_GetColor(x, y);
	if (g == 1)
	{
		//Sleep(1);
		GP142_pixelXY(colo, x, y);
		fill(x, y + 1, colo);
		fill1(x + 1, y, colo);

		fill1(x-1 , y, colo);
	}
	else
	{
		return;
	}
}
void triangle::fill1(int x, int y, int colo){
	int g = GP142_GetColor(x, y);
	if (g == 1)
	{

		GP142_pixelXY(colo, x, y);
		fill1(x - 1, y, colo);
		fill(x, y - 1, colo);


		fill(x, y + 1, colo);
	}
	else
	{
		return;
	}
}
void triangle::setf(int fill)
{
	fillco = fill;
}
void Circle::setf(int fill)
{
	fillco = fill;
}
void polygon::setf(int fill)
{
	fillco = fill;
}
void polygon::fill(int x, int y, int colo)
{
	int g = GP142_GetColor(x, y);
	if (g == 1)
	{
		GP142_pixelXY(colo, x, y);
		fill(x, y + 1, colo);
		fill1(x + 1, y, colo);

		fill1(x - 1, y, colo);
	}
	else
	{
		return;
	}
}
void polygon::fill1(int x, int y, int colo){
	int g = GP142_GetColor(x, y);
	if (g == 1)
	{
		//Sleep(1);
		GP142_pixelXY(colo, x, y);
		fill1(x - 1, y, colo);
		fill(x, y - 1, colo);


		fill(x, y + 1, colo);
	}
	else
	{
		//fillco = colo;
		return;
	}
}
bool polygon::containspoint(Point p)
{
	int yoyo = 0;
	if (numberofPoint == 2)
	{
		fPoint p1, p2, p3, p4, p5;
		p1.x = p.x;
		p1.y = p.y;
		p2.x = d[0]->x;//2
		p2.y = d[0]->y;//5
		p5.x = d[1]->x; //4
		p5.y = d[1]->y;//-5
		p3.y = d[0]->y;
		p3.x = d[1]->x;
		p4.x = d[0]->x;
		p4.y = p5.y;
		    bool	b1 = CalcTriArea(p1, p2, p3) < 0.0f;
			bool	b2 = CalcTriArea(p1, p3, p4) < 0.0f;
			bool	b3 = CalcTriArea(p1, p4, p2) < 0.0f;

			bool	b4 = CalcTriArea(p1, p3, p4) < 0.0f;
			bool	b5 = CalcTriArea(p1, p4, p5) < 0.0f;
			bool	b6 = CalcTriArea(p1, p5, p3) < 0.0f;

		return ((b1 == b2) && (b2 == b3) || ((b4 == b5) && (b5 == b6)));
	}
	else
	{
		
			int i, j, c = 0;
			for (i = 0, j = numberofPoint - 1; i < numberofPoint; j = i++) 
			{
				// right side pr projection hai ray ki
				//	Aur  lines calculate krta hai
				//	Lines ki intersection

	            if((((d[i]->y)>p.y) != (d[j]->y>p.y)) &&(p.x < ((d[j]->x) - (d[i]->x)) * (p.y - (d[i]->y)) / ((d[j]->y) - (d[i]->y)) + (d[i]->x)))
				 c = !c;
			}
			 return c;
		}

	}
bool text::containspoint(Point p)
{
	if ((p.x == d[0]->x) && (p.y == d[0]->y) || (p.x >= d[0]->x+5) && (p.y >= d[0]->y+5))
	{
		return true;

	}
	else
	{
		return false;
	}
}
text::text() :
shape()
{
	write = nullptr;
	zeal = 0;
}
int text:: type()
{
	return 7;
}
void text::fill(int, int, int) {}
void text::filesave()
{
	ofstream of;
	of.open("Example.txt", ios::app);
	of << 7 << endl;
	of << numberofPoint << endl;
	of << color << endl;
	of << fillco << endl;
	of << 0 << endl;
	of << 0 << endl;
	of << 0 << endl;
	of << zeal << endl;
	
	for (int j = 0; j <numberofPoint; j++)
	{
		of << d[j]->x << "," << d[j]->y << endl;
	}

	of << write << endl;


}
text::text(int colo, Point*p, int numbero, char* st, int z,int f,Point a)
:shape(colo, p, numbero,f,a)
{
	write = new char[z];
	write = st;
	zeal = z;
	write[z] = '\0';

}
bool Circle:: containspoint(Point p)
{
	double u = (d[0]->x - p.x);
	double v = (d[0]->y - p.y);
	u = pow(u, 2);
	v = pow(v, 2);
	u = u + v;
	u = sqrt(u);
	if (u <= radius)
	{
		return true;
	}
	else
	{
		return false;
	}
}
void Circle::fill(int x, int y, int colo)
{
	
	int g = GP142_GetColor(x, y);
	if (g ==1)
	{
		//Sleep(1);
		GP142_pixelXY(colo, x, y);
		fill(x, y + 1, colo);
		fill1(x + 1, y, colo);

		fill1(x - 1, y, colo);
	}
	else
	{
		return;
	}
}
void Circle::fill1(int x, int y, int colo){
	int g = GP142_GetColor(x, y);
	if (g ==1)
	{
		//Sleep(1);
		GP142_pixelXY(colo, x, y);
		fill1(x - 1, y, colo);
		fill(x, y - 1, colo);


		fill(x, y + 1, colo);
	}
	else
	{
		//fillco = colo;
		return;
	}
}
int demo_handle_mouse(int x, int y)
{
	
	if ((x >= -280 && y <= 222) && (x <= -249 && y >= 209))
	{
		k = RED;
		return RED;
	}

	else if ((x >= -280 && y <= 200) && (x <= -249 && y >= 187))
	{
		k = PINK;
		return  PINK;
	}
	else if ((x >= -280 && y <= 178) && (x <= -249 && y >= 165))
	{
		k = BLACK;
		return  BLACK;
	}
	else if ((x >= -280 && y <= 156) && (x <= -249 && y >= 143))
	{
		k = BLUE;
		return  BLUE;
	}
	else if ((x >= -280 && y <= 134) && (x <= -249 && y >= 121))
	{
		k = YELLOW;
		return  YELLOW;
	}
	else if ((x >= -280 && y <= 112) && (x <= -249 && y >= 99))
	{
		k = GREEN;
		return  GREEN;
	}
	else if ((x >= -280 && y <= 90) && (x <= -249 && y >= 77))
	{
		k = MED_GRAY;
		return  MED_GRAY;
	}
	else
	{
		//GP142_printfXY(MED_GRAY, x, y, 9, "%d %d", x, y);

		return k;
	}



}
int checkonShapes(int x, int y)
{
	if ((x >= -280 && y <= 57) && (x <= -249 && y >= 45))
	{
		shap = 1; //triangle
		return shap;
	}
	else if ((x >= -280 && y <= 42) && (x <= -249 && y >= 29))
	{
		shap = 2;  //rect
		return shap;
	}
	else if ((x >= -280 && y <= 20) && (x <= -249 && y >= 3))
	{
		shap = 3; //circle
		return shap;
	}
	else if ((x >= -280 && y <= -10) && (x <= -249 && y >= -23))
	{
		shap = 4; //polygon
		return shap;

	}
	else if ((x >= -280 && y <= -32) && (x <= -249 && y >= -45))
	{
		shap = 5; //curve;
		return shap;

	}
	else if ((x >= -280 && y <= -54) && (x <= -249 && y >= -67))
	{
		shap = 6;
		return shap;

	}
	else if ((x >= -280 && y <= -91) && (x <= -249 && y >= -105))
	{
		shap = 7;
		return shap;
	}
	else if ((x >= -280 && y <= -111) && (x <= -249 && y >= -124))
	{
		shap = 8;
		return shap;
	}
	else if ((x >= -280 && y <= -148) && (x <= -249 && y >= -162))
	{
		shap = 9;
		return shap;
	}

	else if ((x >= -280 && y <= -180) && (x <= -249 && y >= -193))
	{
		shap = 10;
		return shap;

	}
	else if ((x >= -280 && y <= -198) && (x <= -249 && y >= -211))
	{
		shap = 11;
		return shap;
	}
	else if ((x >= -280 && y <= -215) && (x <= -249 && y >= -227))
	{
		shap = 12;
		return shap;
	}
	else
	{
		return shap;
	}

}
void demo_draw_stuff(void)
{

	GP142_rectangleXY(WHITE, -GP142_XMAX, -GP142_YMAX, GP142_XMAX, GP142_YMAX, 0);
	GP142_rectangleXY(BLACK, -291, 241, -233, -237, 1);

	GP142_printfXY(BLACK, -288, 222, 15, "Colour");
	GP142_rectangleXY(RED, -280, 222, -249, 209, 0);
	GP142_rectangleXY(PINK, -280, 200, -249, 187, 0);
	GP142_rectangleXY(BLACK, -280, 178, -249, 165, 0);
	GP142_rectangleXY(BLUE, -280, 156, -249, 143, 0);
	GP142_rectangleXY(YELLOW, -280, 134, -249, 121, 0);
	GP142_rectangleXY(GREEN, -280, 112, -249, 99, 0);
	GP142_rectangleXY(MED_GRAY, -280, 90, -249, 77, 0);


	GP142_printfXY(BLACK, -288, 60, 15, "Shape");
	GP142_rectangleXY(BLACK, -280, 57, -249, 45, 1);
	GP142_printfXY(BLACK, -280, 47, 8, "Triangle");
	GP142_rectangleXY(BLACK, -280, 42, -249, 29, 1);
	GP142_printfXY(BLACK, -278, 32, 8, "Rect");
	GP142_rectangleXY(BLACK, -280, 20, -249, 3, 1);
	GP142_printfXY(BLACK, -278, 5, 8, "circle");
	GP142_rectangleXY(BLACK, -280, -10, -250, -23, 1);
	GP142_printfXY(BLACK, -278, -20, 8, "n-polygo");
	GP142_rectangleXY(BLACK, -280, -32, -249, -45, 1);
	GP142_printfXY(BLACK, -278, -42, 8, "n-curve");
	GP142_rectangleXY(BLACK, -280, -54, -249, -67, 1);
	GP142_printfXY(BLACK, -278, -65, 8, "T-Line");

	GP142_printfXY(BLACK, -288, -85, 15, "Tools");
	GP142_rectangleXY(BLACK, -280, -91, -249, -105, 1);
	GP142_printfXY(BLACK, -278, -102, 8, "Erase");
	GP142_rectangleXY(BLACK, -280, -111, -249, -124, 1);
	GP142_printfXY(BLACK, -278, -123, 8, "BUCKE");

	GP142_printfXY(BLACK, -288, -140, 15, "Menu");
	GP142_rectangleXY(BLACK, -280, -148, -249, -162, 1);
	GP142_printfXY(BLACK, -278, -159, 8, "Save");
	GP142_rectangleXY(BLACK, -280, -180, -249, -193, 1);
	GP142_printfXY(BLACK, -278, -190, 8, "New");

	GP142_rectangleXY(BLACK, -280, -198, -249, -211, 1);
	GP142_printfXY(BLACK, -278, -208, 8, "Load");

	GP142_rectangleXY(BLACK, -280, -215, -249, -227, 1);
	GP142_printfXY(BLACK, -280, -226, 8, "Text");

	//GP142_rectangleXY(BLACK, 249, -280, 200, -220, 1);
	//GP142_printfXY(BLACK, 207, -235, 12, "Dotted");

}
double CalcTriArea(fPoint v1, fPoint v2, fPoint v3)
{
	double det = 0.0;
	det = ((v1.x - v3.x) * (v2.y - v3.y)) - ((v2.x - v3.x) * (v1.y - v3.y));
	return (det / 2.0);
}
double dis(Point p, Point a)
{
	double u = (a.x - p.x);
	double v = (a.y - p.y);
	u = pow(u, 2);
	v = pow(v, 2);
	u = u + v;
	u = sqrt(u);
	return u;

}
//function for file loading
