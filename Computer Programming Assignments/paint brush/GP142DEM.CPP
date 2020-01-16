
#pragma comment(linker,"/STACK:30000000")
#include "GP142.h"
#include <stdio.h>
#include <math.h>
#include"shape.h"
#include<stdlib.h>
#include<fstream>
#include<Windows.h>

void demo_handle_kbd(char key_pressed, int& x, int& y, int co);
int checkonShapes(int x, int y);
int demo_handle_mouse(int x, int y);
void demo_draw_stuff(void);
void fill1(int x, int y, int colo, int olc);
void fill(int x, int y, int colo, int olc);
void distructor(vector<shape*> p, int size);
Point* extendbyone(Point* p, int& size);
char* extendbyones(char* p, int& size);
int main(void)
{
	int y = 0;  //storing of x vlaue
	int gp1 = 0; //storing of y value
	int quit = 0;
	int mouse_x, mouse_y;
	char key_pressed;
	int col = 0;
	char* s;
	int c = 0;
	Point1 storeC[3000];
	int so = 0;
	s = new char[3];
	int i = 0;
	int u = 0;
	int t = 0;  //counting of element
	int z = 3;    //extending array elemeny
	int po;
	Point *j;
	Point ajo;
	ajo.x = 0;
	ajo.y = 0;
	j = new Point[z];
	vector<shape*> Allshape;
	GP142_open();
	GP142_logging(LOG_OFF);
	demo_draw_stuff();
	while (!quit) {

		switch (GP142_await_event(&mouse_x, &mouse_y, &key_pressed)) {
		case GP142_QUIT:
			quit = 1;
			break;

		case GP142_MOUSE:
			col = demo_handle_mouse(mouse_x, mouse_y);
			po = GP142_GetColor(mouse_x, mouse_y);
			u = checkonShapes(mouse_x, mouse_y);
			y = mouse_x;
			gp1 = mouse_y;
			if (!(mouse_x >= -291 && mouse_y <= 241) || (!(mouse_x <= -233 && mouse_y >= -237)) || u == 10 || u == 9 || u == 11)
			{

				if (u == 12)
				{
					j[0].x = y;
					j[0].y = gp1;
					mouse_x = 0;
					mouse_y = 0;
					while (mouse_x == 0 && mouse_y == 0)
					{
						switch (GP142_await_event(&mouse_x, &mouse_y, &key_pressed))

						{

						case GP142_MOUSE:


							i = 0;
							i++;
							col = demo_handle_mouse(mouse_x, mouse_y);
							u = checkonShapes(mouse_x, mouse_y);
							Allshape.push_back(new text(col, j, i, s, c, 0, ajo));
							mouse_y = 10;
							i = 0;
							c = 0;
							break;
						case GP142_KBD:
							demo_handle_kbd(key_pressed, y, gp1, col);
							s[c] = key_pressed;
							j[i].x = y;
							j[i].y = gp1;
							i++;
							if (i + 1 > 3)
							{
								j = extendbyone(j, z);
							}
							c++;
							if (c > 3)
							{
								extendbyones(s, z);
							}
							break;


						}

					}
					t++;
				}
				else if (u == 1)  //for triangle
				{
					j[i].x = mouse_x;
					j[i].y = mouse_y;
					i++;
					if (i == 3)
					{

						Allshape.push_back(new triangle(col, j, i, 1, ajo));
						Allshape[t]->draw();

						i = 0;
						t++;
					}

				}
				else if (u == 7)  //for erase
				{
					Point p;
					p.x = mouse_x;
					p.y = mouse_y;
					for (int iz = Allshape.size() - 1; iz >= 0; iz--)
					{

						if (Allshape[iz]->containspoint(p))
						{
							for (int j = 0; j < so; j++)
							{
								Point storfor;
								storfor.x = storeC[j].x;
								storfor.y = storeC[j].y;
								if (Allshape[iz]->containspoint(p) && (Allshape[iz]->containspoint(storfor)))
								{

									for (int i = j; i < so; i++)
									{
										storeC[i].x = storeC[i + 1].x;
										storeC[i].y = storeC[i + 1].y;
										storeC[i].z = storeC[i + 1].z;
									}

									if (so < 0)
										so = 0;
									else
										so--;
									break;
								}


							}
							Allshape.erase(Allshape.begin() + iz);
							demo_draw_stuff();
							if (t == 0)
								t = 0;
							else
								t = t - 1;
							for (int i = 0; i < Allshape.size(); i++)
							{
								Allshape[i]->draw();
								col = 0;
							}
							for (int i = 0; i < so; i++)
							{

								int pagia = GP142_GetColor(storeC[i].x, storeC[i].y);
								fill(storeC[i].x, storeC[i].y, storeC[i].z, pagia);
								fill1(storeC[i].x, storeC[i].y, storeC[i].z, pagia);

							}
							break;
						}
					}

				}
				else if (u == 2)  //for rectangle
				{
					j[i].x = mouse_x;
					j[i].y = mouse_y;
					i++;


					if (i == 2)
					{
						Allshape.push_back(new rectangle(col, j, i, 1, ajo));
						Allshape[t]->draw();
						i = 0;
						t++;


					}
				}
				else if (u == 3)       //for circle
				{
					j[i].x = mouse_x;
					j[i].y = mouse_y;
					i++;
					if (i == 2)
					{
						double x = j[1].x - j[0].x;
						double y = j[1].y - j[0].y;
						double dist;
						dist = pow(x, 2) + pow(y, 2);           //calculating distance by euclidean formula
						dist = sqrt(dist);
						Allshape.push_back(new Circle(col, j, i, dist, 1, ajo));
						Allshape[t]->draw();
						t++;
						i = 0;
					}
				}
				else if (u == 4)   //for polygon
				{

					if (i + 1 > 3)
					{
						j = extendbyone(j, z);
					}
					if (GetAsyncKeyState(VK_RBUTTON))
					{
						Allshape.push_back(new polygon(col, j, i, 1, ajo));
						Allshape[t]->draw();
						t++;
						i = 0;
					}
					else
					{
						j[i].x = mouse_x;
						j[i].y = mouse_y;
						i++;

					}

				}
				else if (u == 5)   //for curve
				{
					if (i + 1 > 3)
					{
						j = extendbyone(j, z);
					}

					if (GetAsyncKeyState(VK_RBUTTON))
					{
						Allshape.push_back(new curve(col, j, i, 0, 1, ajo));
						Allshape[t]->draw();
						t++;
						i = 0;
					}
					else
					{
						j[i].x = mouse_x;
						j[i].y = mouse_y;
						i++;

					}

				}
				else if (u == 6)  //for line
				{
					j[i].x = mouse_x;
					j[i].y = mouse_y;
					i++;
					if (i == 2){
						Allshape.push_back(new line(col, j, i, 0, 1, ajo));
						Allshape[t]->draw();
						t++;
						i = 0;
					}
				}
				else if (u == 8)   //for points storing of colors
				{
					Point pagi;
					pagi.x = mouse_x;
					pagi.y = mouse_y;
					int pd = 0;
					for (int i = Allshape.size() - 1; i >= 0; i--)
					{
						if (Allshape[i]->containspoint(pagi))
						{
							if (Allshape[i]->type() == 5 || Allshape[i]->type() == 6)
							{
								Allshape[i]->setf(col);
								pd++;
								break;
							}

						}


					}
					if (pd == 0)
					{
						storeC[so].x = mouse_x;
						storeC[so].y = mouse_y;
						storeC[so].z = col;

						so++;
						int pagi = GP142_GetColor(mouse_x, mouse_y);
						if (pagi == col)
						{


						}
						else
						{
							fill(mouse_x, mouse_y, col, pagi);
							fill1(mouse_x, mouse_y, col, pagi);
						}
					}
					pd = 0;

				}
				else if (u == 9)
				{
					ofstream fn;
					fn.open("Exampleq.txt");
					fn << Allshape.size() << endl;
					for (int i = 0; i < Allshape.size(); i++)
					{
						int g = Allshape[i]->type();
						if (g == 1)
						{
							Allshape[i]->filesave();
						}
						else if (g == 2)
						{
							Allshape[i]->filesave();
						}
						else if (g == 3)
						{
							Allshape[i]->filesave();
						}
						else if (g == 4)
						{
							Allshape[i]->filesave();
						}
						else if (g == 5)
						{
							Allshape[i]->filesave();
						}
						else if (g == 6)
						{
							Allshape[i]->filesave();
						}
						else if (g == 7)
						{
							Allshape[i]->filesave();

						}

					}
					if (so != 0)
					{

						fn << so << endl;
						for (int j = 0; j < so; j++)
						{
							fn << storeC[j].x << endl << storeC[j].y << endl << storeC[j].z << endl;
						}
					}

				}
				else if (u == 10)   //for new paint
				{
					demo_draw_stuff();
					while (!Allshape.empty())
					{
						Allshape.pop_back();
						t = 0;
					}
					ofstream fin;
					t = 0;
					fin.open("Example.txt");
					fin.close();
					fin.open("Exampleq.txt");
				}

				else if (u == 11)
				{
					int g = 0;
					int nup = 0;
					int co = 0;
					int fi = 0;
					int number;
					ifstream fin;

					fin.open("Example.txt");
					fin >> number;
					t = number;
					while (!fin.eof())
					{

						fin >> g;
						fin >> nup;
						fin >> co;
						fin >> fi;
						fin >> ajo.x;
						fin >> ajo.y;
						if (g == 1)
						{
							char* p;
							char n[10];
							fin.getline(n, 10);
							int o = 0;
							for (int i = 0; i < nup; i++)
							{
								fin.getline(n, 10);
								p = strtok(n, ",");
								while (p != nullptr)
								{
									int k = atoi(p);
									j[o].x = k;
									p = strtok(nullptr, ",");
									k = atoi(p);
									j[o].y = k;
									p = strtok(nullptr, ",");
									o++;
								}

								if (o == 3)
								{

									Allshape.push_back(new triangle(co, j, nup, fi, ajo));
									Allshape[t]->draw();
									o = 0;
									t++;
								}


							}
						}
						else if (g == 2)
						{
							char* p;
							char n[10];
							fin.getline(n, 10);
							int o = 0;
							int w = 0;
							for (int i = 0; i < nup; i++)
							{
								fin.getline(n, 10);
								p = strtok(n, ",");
								while (p != nullptr)
								{
									int k = atoi(p);
									j[o].x = k;
									p = strtok(nullptr, ",");
									k = atoi(p);
									j[o].y = k;
									p = strtok(nullptr, ",");
									o++;
								}

								if (o == 2)
								{

									Allshape.push_back(new rectangle(co, j, nup, fi, ajo));
									Allshape[t]->draw();
									o = 0;
									t++;
								}


							}

						}
						else if (g == 3)
						{
							double zo;
							fin >> zo;
							char* p;
							char n[10];
							fin.getline(n, 10);
							int o = 0;

							for (int i = 0; i < nup; i++)
							{
								fin.getline(n, 10);
								p = strtok(n, ",");
								while (p != nullptr)
								{
									int k = atoi(p);
									j[o].x = k;
									p = strtok(nullptr, ",");
									k = atoi(p);
									j[o].y = k;
									p = strtok(nullptr, ",");
									o++;
								}



							}

							if (o == 2)
							{
								Allshape.push_back(new Circle(co, j, o, zo, fi, ajo));
								Allshape[t]->draw();
								t++;
								i = 0;
							}

						}
						else if (g == 4)
						{
							char* p;
							char n[10];
							fin.getline(n, 10);
							int o = 0;

							for (int i = 0; i < nup; i++)
							{
								fin.getline(n, 10);
								p = strtok(n, ",");
								while (p != nullptr)
								{
									if (o + 1 > 3)
									{
										j = extendbyone(j, z);
									}
									int k = atoi(p);
									j[o].x = k;
									p = strtok(nullptr, ",");
									k = atoi(p);
									j[o].y = k;
									p = strtok(nullptr, ",");
									o++;
								}

								if (o == nup)
								{
									Allshape.push_back(new polygon(co, j, o, fi, ajo));
									Allshape[t]->draw();
									t++;
									o = 0;
								}



							}

						}
						else if (g == 6)
						{
							char* p;
							char n[10];
							fin.getline(n, 10);
							int o = 0;
							int zo = 0;
							fin >> zo;
							for (int i = 0; i < nup + 1; i++)
							{
								fin.getline(n, 10);
								p = strtok(n, ",");
								while (p != nullptr)
								{
									if (o + 1 > 3)
									{
										j = extendbyone(j, z);
									}
									int k = atoi(p);
									j[o].x = k;
									p = strtok(nullptr, ",");
									k = atoi(p);
									j[o].y = k;
									p = strtok(nullptr, ",");
									o++;
								}

								if (o == nup)
								{
									Allshape.push_back(new curve(co, j, o, zo, fi, ajo));
									Allshape[t]->draw();
									t++;
									o = 0;
								}

							}
						}
						else if (g == 5)
						{
							char* p;
							char n[10];
							fin.getline(n, 10);
							int o = 0;
							int zo = 0;
							fin >> zo;
							for (int i = 0; i <= nup; i++)
							{
								fin.getline(n, 10);
								fin.getline(n, 10);
								p = strtok(n, ",");
								while (p != nullptr)
								{


									int k = atoi(p);
									j[o].x = k;
									p = strtok(nullptr, ",");
									k = atoi(p);
									j[o].y = k;
									p = strtok(nullptr, ",");
									o++;
								}

								if (o == 2)
								{
									Allshape.push_back(new line(co, j, o, zo, fi, ajo));
									Allshape[t]->draw();
									t++;
									o = 0;
								}

							}

						}
						else if (g == 7)
						{
							int ko;
							char* p;
							fin >> ko;
							int po;
							fin >> po;
							int o = 0;
							char n[10];
							fin.getline(n, 10);
							fin.getline(n, 10);

							p = strtok(n, ",");
							while (p != nullptr)
							{
								int k = atoi(p);
								j[o].x = k;
								p = strtok(nullptr, ",");
								k = atoi(p);
								j[o].y = k;
								p = strtok(nullptr, ",");
								o++;
							}

							p = new char[po];
							fin.getline(p, 100);
							Allshape.push_back(new text(co, j, 1, p, po, fi, ajo));

							Allshape[t]->draw();
							t++;
						}

						u = 100;


					}
					fin.close();
					ifstream ofp;
					fin.open("Exampleq.txt");
					int jam, x1, y1, z1;
					fin >> jam;
					so = 0;
					for (int k = 0; k <jam; k++)
					{
						fin >> x1;
						storeC[so].x = x1;

						fin >> y1;
						storeC[so].y = y1;
						fin >> z1;
						storeC[so].z = z1;
						int pagiq = GP142_GetColor(x1, y1);
						fill(x1, y1, z1, pagiq);
						fill1(x1, y1, z1, pagiq);
						so++;

					}


				}
			}



			break;
		case GP142_KBD:
//			demo_handle_kbd(key_pressed);
			break;

		default:
			break;
		}
	}
	distructor(Allshape, t);

	GP142_close();          /* Clean up and close graphics window */

	return 0;
}
Point* extendbyone(Point* p, int& size)   //pointer is extended
{
	Point *q;
	size = size + 1;
	q = new Point[size];
	for (int j = 0; j < size - 1; j++)
	{
		q[j].x = p[j].x;
		q[j].y = p[j].y;
	}
	return q;
}
char* extendbyones(char* p, int& size)
{
	char *q;
	size = size + 1;
	q = new char[size];
	for (int j = 0; j < size - 1; j++)
	{
		q[j] = p[j];

	}
	return q;

}
void demo_handle_kbd(char c, int& x, int& y, int co)
{
	static  int typing_width = x;      /* pixels   */
	const  int typing_y = y;       /* pixels   */
	const  int point_size = 20;
	static int key_count = 0;        /* count number of keypresses   */
	static int typing_w = x;

	GP142_printfXY(co, x,
		y, point_size, "%c", c);
	x = x + 20;
	if (x >= 280)
	{
		y = y - 20;
		x = -280;
		x = x + 50;
	}
	key_count = (key_count + 1);
}
void fill(int x, int y, int colo, int olc)
{
	int g = GP142_GetColor(x, y);
	if (g == olc)
	{

		GP142_pixelXY(colo, x, y);
		fill(x, y + 1, colo, olc);
		fill1(x + 1, y, colo, olc);
		fill1(x - 1, y, colo, olc);
	}
	else
	{
		return;
	}
}
void fill1(int x, int y, int colo, int ol){
	int g = GP142_GetColor(x, y);
	if (g == ol)
	{

		GP142_pixelXY(colo, x, y);
		fill1(x - 1, y, colo, ol);
		fill(x, y - 1, colo, ol);
		fill(x, y + 1, colo, ol);
	}
	else
	{

		return;
	}
}
void distructor(vector<shape*> p, int size)
{
	for (int i = 0; i < p.size(); i++)
	{
		p.clear();
	}
}