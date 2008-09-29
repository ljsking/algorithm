// calling.cpp : Defines the entry point for the console application.
//
#include <vector>
#include <list>
#include <algorithm>
#include <cassert>
#include <iostream>
#include <fstream>
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


int _tmain(int argc, _TCHAR* argv[])
{
	int size = 0;
	vector<Edge> edges;
	ifstream inf("calling.inp");
	int edgesize;
	inf>>edgesize;
	for(int i = 0; i<edgesize; i++)
	{
		int from, to;
		inf>>from>>to;
		edges.push_back(Edge(from, to));
	}
	inf.close();
	for(vector<Edge>::iterator iter=edges.begin(); iter!=edges.end(); iter++)
		size = max(iter->to, size);
	vector< list<int>* > adjLists(size);
	for(int i = 0; i<size; i++)
		adjLists[i] = new list<int>;
	
	vector<int> rz(size);
	for(int i = 0; i<size; i++)
		rz[i] = -1;

	for(vector<Edge>::iterator iter=edges.begin(); iter!=edges.end(); iter++)
	{
		adjLists[iter->from-1]->push_back(iter->to-1);
		adjLists[iter->to-1]->push_back(iter->from-1);
	}
	int maxgroup = 0;
	for(int i = 0; i<size; i++)
	{
		list<int> *adjList = adjLists[i];
		int group = rz[i] == -1?maxgroup++:rz[i];
		
		vector<int> stack;
		for(list<int>::iterator iter = adjList->begin(); iter!=adjList->end(); iter++)
			stack.push_back(*iter);

		while(stack.size())
		{
			int val = stack.back();
			stack.pop_back();
			if(rz[val] == -1)
			{
				rz[val] = group;
				adjList = adjLists[val];
				for(list<int>::iterator iter = adjList->begin(); iter!=adjList->end(); iter++)
					stack.push_back(*iter);
			}
		}
	}
	assert(3==maxgroup);
	vector<int> groups(maxgroup);
	vector<int> leaders(maxgroup);
	int maxNumberOfPeople = -1;
	for(int i=0; i<size; i++){
		groups[rz[i]]++;
		maxNumberOfPeople = max(maxNumberOfPeople, groups[rz[i]]);
		leaders[rz[i]]=i+1;
	}
	int finalLeader = -1;
	for(int i=0; i<maxgroup;i++)
	{
		if(maxNumberOfPeople == groups[i])
			finalLeader = max(finalLeader, leaders[i]);
	}
	ofstream of("calling.out");
	of<<finalLeader;
	of.close();
	return 0;
}