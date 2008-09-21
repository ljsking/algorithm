#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

class Point
{
public:
	Point():x(0),y(0){}
	Point(const Point& other):x(other.x), y(other.y){}
	Point(int x_, int y_):x(x_), y(y_){}
	double distance(const Point &other)
	{
		double dx = x-other.x;
		double dy = y-other.y;
		return sqrt(dx*dx+dy*dy);
	}
	int x, y;
	
};

Point *points;
int size;
double rz=numeric_limits<double>::max();
const int maxElementsForCalc = 3;
int eachsize = 0;
int divide = 0;
int byX(const void *a, const void *b)
{
	return ((Point *)a)->x-((Point *)b)->x;
}

int byY(const void *a, const void *b)
{
	return ((Point *)a)->y-((Point *)b)->y;
}

void calculate(Point *begin, int numberOfElements)
{
	for(int i = 0; i<numberOfElements-2; i++)
	{
		for(int j=i+1; j<numberOfElements-1; j++)
		{
			double tmp1 = begin[i].distance(begin[j]);
			if(tmp1>rz)
				continue;
			for(int k=j+1;k<numberOfElements;k++)
			{				
				double tmp = max(tmp1, begin[i].distance(begin[k]));
				if(tmp>rz)
					continue;
				tmp = max(tmp, begin[j].distance(begin[k]));
				rz = min(rz, tmp);
			}
		}
	}
}

void init()
{
	ifstream in("triangle.inp");
	in>>size;
	eachsize = size;
	for(;eachsize>maxElementsForCalc;eachsize=eachsize/4, divide++);
	points = new Point[size];
	for(int i = 0; i<size; i++)
		in>>points[i].x>>points[i].y;
	in.close();
}

void finalize()
{
	FILE *out = fopen("triangle.out","w");
	fprintf(out, "%.3f",rz);
	fclose(out);
	cout<<rz<<endl;
}

void reCalcByY(Point *start, Point *boarder, int size)
{
	Point *begin = boarder-2;
	for(;begin!=start&&(boarder-1)->y-begin->y<rz/2;begin--);
	Point *end = boarder+1;
	for(;end!=start+size&&end->y-boarder->y<rz/2;end++);
	calculate(begin, end-begin);
}

void reCalcByX(Point *start, Point *boarder, int size)
{
	Point *begin = boarder-2;
	for(;begin!=start&&(boarder-1)->x-begin->x<rz/2;begin--);
	Point *end = boarder+1;
	for(;end!=start+size&&end->x-boarder->x<rz/2;end++);
	calculate(begin, end-begin);
}

void divideY(Point *start, int size)
{
	qsort(points, size, sizeof(Point), byY);
	int begin = 0;	
	for(;begin<size-eachsize;begin+=eachsize)
		calculate(start+begin, eachsize);
	calculate(start+begin, size-begin);
	
	begin = eachsize;
	for(;begin<size-eachsize;begin+=eachsize)
		reCalcByY(start, start+begin, eachsize);
	//reCalcByY(start, start+begin, size-begin);
}

void divideX(Point *start, int size)
{
	qsort(points, size, sizeof(Point), byX);
	int begin = 0;	
	for(;begin<size-eachsize*divide;begin+=eachsize*divide)
		divideY(start+begin, eachsize*divide);
	divideY(start+begin, size-begin);
	
	begin = eachsize*divide;
	for(;begin<size-eachsize*divide;begin+=eachsize*divide)
		reCalcByX(start, start+begin, eachsize*divide);
	//reCalcByX(start, start+begin, size-begin);
}

int main (int argc, char * const argv[]) {
	init();
	divideX(points, size);
	finalize();
    return 0;
}
