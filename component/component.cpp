#include <list>
#include <vector>
#include <algorithm>
#include <stack>
#include <iostream>
#include <ostream>
#include <fstream>

using namespace std;

class Vertex;
typedef vector<Vertex> Vertices;

class Vertex
{
public:
	Vertex():pre(0), post(0), low(0), erased(false)
	{
	}
	
	Vertex(const Vertex &other):pre(other.pre),post(other.post), low(other.low), erased(other.erased)
	{
		if(other.adjList.size()>0)
			copy(other.adjList.begin(), other.adjList.end(), adjList.begin());
	}
	
	void insert(int vertex)
	{
		adjList.push_back(vertex);
	}
	
	int getPre(){return pre;}
	int getPost(){return post;}
	void setPre(int Pre){ pre = Pre; }
	void setPost(int Post){ post = Post; }
	void erase(){ erased = true; adjList.clear(); }
	bool isErased() { return erased; }
	Vertices::iterator next(Vertices &vertices)
	{
		list<int>::iterator next = adjList.begin();
		while(next != adjList.end()){
			if(!vertices[*next].getPre()) return vertices.begin()+*next;
			next++;
		}
		return vertices.end();
	}
	void print(ostream &o) const
	{
		if(erased)
			o<<"deleted";
		else{
			o<<"pre: "<<pre<<", post: "<<post<<" List:";
			for(list<int>::const_iterator it=adjList.begin(); it!=adjList.end(); it++)
				o<<(*it)<<" ";
		}
	}
	list<int>::const_iterator begin() const {return adjList.begin();}
	list<int>::const_iterator end() const {return adjList.end();}
	void eraseAdj(int vertex)
	{
		for(list<int>::iterator it = adjList.begin();it!=adjList.end();)
		{
			if(vertex == *it)
				it = adjList.erase(it);
			else
				it++;
		}
	}
	void updateLow(Vertices &vertices)
	{
		for(list<int>::iterator it = adjList.begin();it!=adjList.end();)
		{
			int pre = vertices[*it].getPre();
			if(pre == 0) continue;
			low = min(low, pre);
		}
	}
private:
	list< int > adjList;
	int pre, post, low;
	bool erased;
};

ostream& operator<< (ostream& o, const Vertex& v)
{
	v.print(o);
	return o;
}

/*
1 3 0
2 1 0
3 8 4 0
4 6 0
5 4 0
6 7 0
7 5 0
8 1 0
*/
void read(Vertices &vertices)
{
	ifstream ifs("component.inp");
	int size, tmp;
	ifs>>size;
	vertices.resize(size);
	for(int i = 0; i<size; i++)
	{
		ifs>>tmp;
		while(tmp!=0)
		{
			vertices[i].insert(tmp-1);
			ifs>>tmp;
		}
	}
	ifs.close();
}

void digg(Vertices::iterator iter, Vertices &vertices, int &pre, stack<Vertices::iterator> &st)
{
	Vertices::iterator cur = iter;
	while(cur!=vertices.end()){
		cur->setPre(pre++);
		st.push(cur);
		cur = cur->next(vertices);
	}
}

int DFS(Vertices &vertices)
{
	for(Vertices::iterator iter = vertices.begin(); 
				iter!=vertices.end(); iter++)
	{
		iter->setPre(0); iter->setPost(0);
	}
	stack< Vertices::iterator > st;
	int index = 1;
	int rz = -1;
	for(Vertices::iterator iter = vertices.begin(); 
				iter!=vertices.end(); iter++)
	{
		if(iter->isErased() || iter->getPre()) continue;
		digg(iter, vertices, index, st);
		while(st.size())
		{
			Vertices::iterator top = st.top();
			st.pop();
			Vertices::iterator next = top->next(vertices);
			digg(next, vertices, index, st);
			top->setPost(index++);
			rz = top-vertices.begin();
		}
	}
	return rz;
}

void reverse(Vertices &reversed, Vertices &vertices)
{
	for(Vertices::iterator iter = vertices.begin(); iter!=vertices.end(); iter++)
	{
		if(iter->isErased())
			reversed[iter-vertices.begin()].erase();
		else
			for(list<int>::const_iterator it = iter->begin(); it!=iter->end(); it++){
				reversed[*it].insert(iter-vertices.begin());
			}
	}
}

void erase(int vertex, Vertices &vertices)
{
	vertices[vertex].erase();
	for(Vertices::iterator iter = vertices.begin(); iter!=vertices.end(); iter++)
		iter->eraseAdj(vertex);
}

void print(Vertices &vs)
{
	for(Vertices::const_iterator iter = vs.begin(); iter!=vs.end(); iter++)
		cout<<iter-vs.begin()<<". "<<*iter<<endl;
}

int deleteSinkCompleteNode(int sink, Vertices &vertices)
{
	for(Vertices::iterator iter = vertices.begin(); 
				iter!=vertices.end(); iter++)
	{
		iter->setPre(0); iter->setPost(0);
	}
	vector<int> deleteNodes;
	stack< Vertices::iterator > st;
	int leader = sink;
	int index = 1;
	Vertices::iterator iter = vertices.begin()+sink;
	digg(iter, vertices, index, st);
	while(st.size())
	{
		Vertices::iterator top = st.top();
		st.pop();
		Vertices::iterator next = top->next(vertices);
		digg(next, vertices, index, st);
		top->setPost(index++);
		deleteNodes.push_back(top-vertices.begin());
		leader = max(leader, top-vertices.begin());
	}
	for(vector<int>::iterator it = deleteNodes.begin(); it!=deleteNodes.end(); it++)
		erase(*it, vertices);
	return leader;
}

int getSinkNode(Vertices &vertices)
{
	Vertices reversed(vertices.size());
	reverse(reversed, vertices);
	return DFS(reversed);
}

int main()
{
	Vertices vertices;
	read(vertices);
	int sink = 0;
	vector<int> results;
	while((sink=getSinkNode(vertices))!=-1)
		results.push_back(deleteSinkCompleteNode(sink, vertices)+1);
	sort(results.begin(), results.end());
	ofstream ofs("component.out");
	for(vector<int>::iterator it = results.begin(); it!=results.end()-1; it++)
		ofs<<*it<<" ";
	ofs<<*(results.end()-1);
	ofs.close();
	return 0;
}
