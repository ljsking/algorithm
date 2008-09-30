// calling.cpp : Defines the entry point for the console application.
//
#include <vector>
#include <list>
#include <algorithm>
#include <cassert>
#include <iostream>
#include <fstream>
#include <set>
using namespace std;

list<int> adjList;

class Edge
{
public:
	Edge(int From, int To):from(From), to(To)
	{}
	int from;
	int to;
};

class Student
{
public:
	Student(int ID):id(ID){adjList = new set<int>();group=new int(-1);}
	int id;
	int *group;
	set<int>* adjList;
	bool operator<(const Student& other)const
	{
		return id<other.id;
	}
	bool operator==(const Student& other)const
	{
		return id==other.id;
	}
};


int main(int argc, char* argv[])
{
	vector<Edge> edges;
	set<Student> students;
	ifstream inf("calling.inp");
	int edgesize;
	inf>>edgesize;
	for(int i = 0; i<edgesize; i++)
	{
		int from, to;
		inf>>from>>to;
		edges.push_back(Edge(from, to));
		students.insert(Student(from));
		students.insert(Student(to));
		
	}
	inf.close();
		
	for(vector<Edge>::iterator iter=edges.begin(); iter!=edges.end(); iter++)
	{
		students.find(Student(iter->from))->adjList->insert(iter->to);
		students.find(Student(iter->to))->adjList->insert(iter->from);
	}
	
	vector<int> groups;
	for(set<Student>::iterator iter = students.begin(); iter!=students.end(); iter++)
	{
		vector<int> stack;
		int group;
		if(*(iter->group) == -1)
		{
			group = groups.size();
			*(iter->group) = group;
			groups.push_back(1);
		}
		else
			group = *(iter->group);
		
		set<int> *adjList = iter->adjList;
		for(set<int>::iterator iter = adjList->begin(); iter!=adjList->end(); iter++)
			stack.push_back(*iter);

		while(stack.size())
		{
			set<Student>::iterator s = students.find(Student(stack.back()));
			stack.pop_back();
			if(*(s->group) == -1)
			{
				*(s->group) = group;
				groups[group]++;
				for(set<int>::iterator iter = s->adjList->begin(); iter!=s->adjList->end(); iter++)
					stack.push_back(*iter);
			}
		}
	}
	int maxNumber = *max_element(groups.begin(), groups.end());
	
	vector<int> rzGroups;
	for(vector<int>::iterator iter = groups.begin(); iter!=groups.end(); iter++)
		if(maxNumber==*iter)
			rzGroups.push_back(iter-groups.begin());
	
	for(set<Student>::reverse_iterator iter = students.rbegin(); iter!=students.rend(); iter++)
	{
		for(vector<int>::iterator g = rzGroups.begin();g!=rzGroups.end();g++)
			if(*g == *(iter->group))
			{
				ofstream of("calling.out");
				of<<iter->id;
				of.close();
				return 0;
			}
	}
	return -1;
}