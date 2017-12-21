#include<string>
#include<iostream>
#include "AdjacencyMatrix.h"

using namespace std;

int main(int argc, char** argv)
{
  int nodes;
  cout<<"Enter number of nodes/verticies for your graph: ";
  cin>>nodes;
  AdjacencyMatrix am(nodes);
  am.inputEdges();
  am.print();
  cout<<"DFS: ";
  am.DFS();
  cout<<"Prims: ";
  am.Prims();
  cout<<"Dijkstras: ";
  am.Dijkstras();
  return 0;
}
