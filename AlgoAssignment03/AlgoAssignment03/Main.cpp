#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>
#include <string>
#include <time.h>
#include <set>
#include <algorithm>
using namespace std;

struct gNode
{
	int vertex;
	list<gNode*> endpoints;
	gNode & operator=(const gNode &rhs)
	{
		if(this == &rhs)
			return *this;
		else 
		{
			this->vertex = rhs.vertex;
			this->endpoints.clear();
			for ( list<gNode*>::const_iterator i = rhs.endpoints.begin() ; i != rhs.endpoints.end();i++)
				this->endpoints.push_back((*i));
		}
	}
};
struct gEdge
{
	int endPoint[2];
};
typedef list<gNode*> tGraph;



void getInputAdjList(string filename, vector<vector<int>> &adjList)
{
	ifstream iFile(filename);
	string line; 
	int x,y;
	vector<int> temp;
	if(iFile.is_open())
	{
		while(getline(iFile,line))
		{
			istringstream iss(line);
			iss >> x;
			while(iss >> y)
			{
				temp.push_back(y);
			}
			adjList.push_back(temp);
			temp.clear();
		}
	}
	else
		cout << "unable to open file"<< endl;
}
class Graph
{
private:
	list<gNode*> mGraph;
public:

	Graph(vector<vector<int>> &adjList)
	{
		int count = 0; 
		for(unsigned int it = 0 ; it < adjList.size() ;it++)
		{
			gNode* newNode = new gNode();
			newNode->vertex = it+1;
			mGraph.push_back(newNode);
		}
		count = 0; 
		for(tGraph::iterator itg = mGraph.begin() ; itg != mGraph.end() ;itg++)
		{
			for(vector<int>::iterator itv = adjList[count].begin() ; itv != adjList[count].end() ;itv++)
			{
				int ept =  *(itv);
				tGraph::iterator itEP = mGraph.begin();
				advance(itEP, ept-1);
				(*itg)->endpoints.push_back(*itEP);
			}
			count++;
		}
		//return mGraph;
	}
	void gClear()
	{
		for(tGraph::iterator itg = mGraph.begin() ; itg != mGraph.end() ;itg++)
			(*itg)->endpoints.clear();
		mGraph.clear();		
	}
	void createGraph(vector<vector<int>> &adjList)
	{
		int count = 0; 
		for(unsigned int it = 0 ; it < adjList.size() ;it++)
		{
			gNode* newNode = new gNode();
			newNode->vertex = it+1;
			mGraph.push_back(newNode);
		}
		count = 0; 
		for(tGraph::iterator itg = mGraph.begin() ; itg != mGraph.end() ;itg++)
		{
			for(vector<int>::iterator itv = adjList[count].begin() ; itv != adjList[count].end() ;itv++)
			{
				int ept =  *(itv);
				tGraph::iterator itEP = mGraph.begin();
				advance(itEP, ept-1);
				(*itg)->endpoints.push_back(*itEP);
			}
			count++;
		}
		//return mGraph;
	}
	void printGraph()
	{
		for(tGraph::iterator itg = mGraph.begin() ; itg != mGraph.end() ;itg++)
		{
			cout<< (*itg)->vertex ;
			for(list<gNode*> ::iterator itep = (*itg)->endpoints.begin(); itep !=(*itg)->endpoints.end(); itep++)
				cout<<"-->"<<(*itep)->vertex;
			cout<< endl;
		}
	}
	tGraph:: iterator gFind( tGraph:: iterator first , tGraph:: iterator last , int value)
	{
		while(first != last)
		{
			if ((*first)->vertex == value) 
				return first;
			++first;
		}
		return last;
	}
	void contractGraphNodes(int vertexU, int vertexV )
	{

		tGraph::iterator itU = gFind(mGraph.begin(),mGraph.end(), vertexU);
		tGraph::iterator itV = gFind(mGraph.begin(),mGraph.end(), vertexV) ;
		//delete all edges between vertices u & v
		(*itU)->endpoints.remove((*itV));
		(*itV)->endpoints.remove((*itU));
		// create a superNode combining u & v
		//gNode* superNode = new gNode();
		//superNode->vertex = (*itU)->vertex;
		//superNode->endpoints.insert(superNode->endpoints.end(),(*itU)->endpoints.begin(),(*itU)->endpoints.end());
		//superNode->endpoints.insert(superNode->endpoints.end(),(*itV)->endpoints.begin(),(*itV)->endpoints.end());
		//(**itU)=(*superNode);
		(*itU)->endpoints.insert((*itU)->endpoints.end(),(*itV)->endpoints.begin(),(*itV)->endpoints.end());// = &superNode;
		//Remove all references for u & v
		for(tGraph::iterator itg = mGraph.begin() ; itg != mGraph.end() ;itg++)
		{
			//set<gNode*> s; 
			for(list<gNode*> ::iterator itep = (*itg)->endpoints.begin(); itep !=(*itg)->endpoints.end(); itep++)
			{
				if((*itep) == (*itV))
				{
					*itep = *itU;
				}
				//s.insert((*itep));
			}
			//sort( (*itg)->endpoints.begin(),(*itg)->endpoints.end());
			//(*itg)->endpoints.assign(s.begin(),s.end());
			//(*itg)->endpoints.erase(unique((*itg)->endpoints.begin(),(*itg)->endpoints.end()) , (*itg)->endpoints.end());
		}
		mGraph.remove(*itV);
	}
	void getEdges(vector<gEdge>& edgeList)
	{
		for(tGraph::iterator itg = mGraph.begin() ; itg != mGraph.end() ;itg++)
		{
			gEdge ep;
			ep.endPoint[0] = (*itg)->vertex ;
			for(list<gNode*> ::iterator itep = (*itg)->endpoints.begin(); itep !=(*itg)->endpoints.end(); itep++)
			{
				ep.endPoint[1] = (*itep)->vertex;
				edgeList.push_back(ep);
			}
		}
	}
	int getEdgeCount()
	{
		int edgeCount = 0 ; 
		for(tGraph::iterator itg = mGraph.begin() ; itg != mGraph.end() ;itg++)
			for(list<gNode*> ::iterator itep = (*itg)->endpoints.begin(); itep !=(*itg)->endpoints.end(); itep++)
				edgeCount++;
		return edgeCount;
	}
	int getVertexCount()
	{
		return mGraph.size();
	}
	int getMinCutValue()
	{
		tGraph::iterator itU = mGraph.begin();
		tGraph::iterator itV = mGraph.begin();
		itV++;
		//delete all edges between vertices u & v
		(*itV)->endpoints.remove((*itU));
		int res = getEdgeCount();
		//(*itU)->endpoints.insert((*itU)->endpoints.end(),(*itV)->endpoints.begin(),(*itV)->endpoints.end());
		return res;

	}
};
int main()
{
	vector<vector<int>> adjacencyList;
	getInputAdjList("C:\\TrainingCode\\AlgoAssignment03\\kargerMinCut.txt" , adjacencyList);
	Graph myGraph(adjacencyList);
	vector<gEdge> randEdge;	
	int minCutEdges = INT_MAX;
	cout<< "Starting graph";
	cout<< "--------------------------------------------------------------"<< endl; 
	myGraph.printGraph();
	cout<< endl;
	int n = myGraph.getVertexCount();
	int trials = (int)(n*(n-1)/2)*log(n);
	// do this once at the start of main:
	for(int i = 0 ; i<500; i++)
	{
		srand( (unsigned)time(0));
		//cout<< "Starting graph";
		//cout<< "--------------------------------------------------------------"<< endl; 
		//myGraph.printGraph();
		while(myGraph.getVertexCount() > 2)
		{
			int edgeCount = myGraph.getEdgeCount();
			// do this when you want a random number:
			int num = rand() % ((edgeCount-1)); 
			//cout<< "Edge Count "<< edgeCount << "Random number = " << num << endl; 
			if(randEdge.size()>0)
				randEdge.clear();
			myGraph.getEdges(randEdge);
			myGraph.contractGraphNodes(randEdge[num].endPoint[0], randEdge[num].endPoint[1]);		
			/*myGraph.printGraph();
			cout << " End Contraction between " << randEdge[num].endPoint[0] << " & " << randEdge[num].endPoint[1]<< endl; 
			cout << "----------------------------------------------------------" << endl;		*/	
		}
		int currMinCut = myGraph.getMinCutValue();
		minCutEdges = (minCutEdges> currMinCut)? currMinCut : minCutEdges;
		cout<< "MinCut  = " << minCutEdges << "  this cut =  "<< currMinCut <<endl;
		myGraph.gClear();
		myGraph.createGraph(adjacencyList);
	}
	//myGraph.printGraph();
	cout<< "Minimum cut is : "<< minCutEdges;
	int x;
	cin>>x;
	return 0; 
}
//
//tGraph createGraph(vector<vector<int>> &adjList)
//{
//	tGraph graph;
//	int count = 0; 
//	for(int it = 0 ; it < adjList.size() ;it++)
//	{
//		gNode* newNode = new gNode();
//		newNode->vertex = it+1;
//		graph.push_back(newNode);
//	}
//	count = 0; 
//	for(tGraph::iterator itg = graph.begin() ; itg != graph.end() ;itg++)
//	{
//		for(vector<int>::iterator itv = adjList[count].begin() ; itv != adjList[count].end() ;itv++)
//		{
//			int ept =  *(itv);
//			tGraph::iterator itEP = graph.begin();
//			advance(itEP, ept-1);
//			(*itg)->endpoints.push_back(*itEP);
//		}
//		count++;
//	}
//	return graph;
//}
//
//	void printGraph(tGraph graph)
//{
//	for(tGraph::iterator itg = graph.begin() ; itg != graph.end() ;itg++)
//	{
//		cout<< (*itg)->vertex ;
//		for(vector<gNode*> ::iterator itep = (*itg)->endpoints.begin(); itep !=(*itg)->endpoints.end(); itep++)
//			cout<<"-->"<<(*itep)->vertex;
//		cout<< endl;
//	}
//}
