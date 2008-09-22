#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <cassert>
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
const int maxElementsForCalc = 15;
int eachsize = 0;
int divide = 1;

int sumCalced = 0;
int maxCalced = 0;
vector<int> boarders;
vector<int> begins;

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
	sumCalced+=numberOfElements;
	maxCalced = maxCalced<numberOfElements?numberOfElements:maxCalced;
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
	for(;eachsize>maxElementsForCalc;eachsize=size/divide, divide++);
	points = new Point[size];
	for(int i = 0; i<size; i++)
		in>>points[i].x>>points[i].y;
	in.close();
}

void finalize()
{
	ofstream of("triangle.out");
	of.precision(4);
	of<<rz;
	of.close();
}

void divideX(Point *start, int size)
{
	qsort(start, size, sizeof(Point), byX);
	int minX = start[0].x;
	int maxX = start[size-1].x;
	int stepX = (maxX+minX)/divide;
	int end = 0;
	int begin = 0;
	int boarder = start[0].x+stepX;
	while(end<size)
	{
		boarders.push_back(boarder);
		begins.push_back(begin);
		for(;end<size&&start[end].x<boarder;end++);
		calculate(start+begin, end-begin);
		begin=end;
		boarder += stepX;
	}
	boarder = start[0].x+stepX;
	begin = boarder+stepX+stepX;
	end = 0;
	assert(boarders.size() == begins.size());
	for(unsigned int index = 1; index<boarders.size(); index++)
	{
		assert(boarder == boarders[index-1]);
		double beginRange = boarder-rz/2;
		double endRange = boarder+rz/2;
		begin = begins[index];
		end = begins[index+1];
		for(;begin>=begins[index-1]&&start[begin].x>=beginRange;begin--);
		for(;end<size&&begins[index+2]&&start[end].x<=endRange;end++);
		calculate(start+begin, end-begin);
		boarder += stepX;
	}
}

int main (int argc, char * const argv[]) {
	init();
	divideX(points, size);
	finalize();
    return 0;
}

