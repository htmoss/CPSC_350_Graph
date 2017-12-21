#include "AdjacencyMatrix.h"
#include "GenStack.h"
#include <iostream>

using namespace std;

AdjacencyMatrix::AdjacencyMatrix(int n)			//Constructor for the matrix class.
{
	numNodes = n;
	wasVisited = new bool[numNodes];		//keep track of which nodes have been visited or not
	for(int i = 0; i < numNodes; ++i)
	{
		wasVisited[i] = false;			//Defaults every node to unvisited.
	}

	matrix = new int*[numNodes];			//Initialized a new array of arrays to set up matrix.
	for(int i = 0; i < numNodes; ++i)
	{
		matrix[i] = new int[numNodes];
		for(int j = 0; j < numNodes; ++j)
		{
			matrix[i][j] = 0;			// Defaults every edge in the matrix to weight 0.
		}
	}
}

AdjacencyMatrix::~AdjacencyMatrix()
{
	delete matrix;
	delete wasVisited;
	delete predecessor;
}

void AdjacencyMatrix::addEdge(int source, int dest)	//Creates unweighted edges
{
	if(source > numNodes || source < 1 || dest > numNodes || dest < 1)	//Error checking to prevent ArrayIndexOutOfBounds
	{
		cout << "This is not a valid edge." << endl;
		exit(EXIT_FAILURE);
	}
	else
	{
		matrix[source - 1][dest - 1] = 1;	//Sets the corresponding slot in the matrix to one
	}
}

//Prints the graph
void AdjacencyMatrix::print()
{
    int i,j;
    for(i = 0;i < numNodes;i++)
    {
        for(j = 0; j < numNodes; j++)
            cout<<matrix[i][j]<<"  ";
        cout<<endl;
    }
}

void AdjacencyMatrix::inputEdges()
{
	cout << "Enter edges (source index followed by destination index). Enter -1 for both to stop." << endl;

	bool done = false;
	while(!done)		//Keeps prompting for edges while done is false.
	{
		int source;
		int dest;

		cout << "Enter edge: ";
		cin >> source >> dest;

		if(source == -1 || dest == -1)		//Condition to exit the program
		{
			done = true;
			continue;
		}

		addEdge(source, dest);
	}
}

void AdjacencyMatrix::DFS()
{
	int startNode;
	cout << "Choose a node (#) to start a depth first-search of your graph: ";
	cin >> startNode;

	GenStack<int> nodeStack(numNodes);		//Initializes a stack used for DFS algorithm.

	int discovered[numNodes];				//Keeps track of nodes in order of discovery.
	for(int i = 0; i < numNodes; ++i)
	{
		discovered[i] = 0;
	}

	int order = 0;							//Index for discovered nodes array.

	int current = startNode;

	bool done = false;
	while(!done)
	{
		if(wasVisited[current - 1] == false)
		{
			discovered[order] = current;
			order++;
		}

		wasVisited[current - 1] = true;		//Marks the current node as visited (will only change unvisited nodes).

		bool nextNode = false;
		for(int i = 0; i < numNodes; ++i)
		{
			if(matrix[current - 1][i] == 1)
			{
				if(wasVisited[i] == false)
				{
					nodeStack.push(current);		//Pushes the current node onto a stack.

					current = ++i;			//If there is an unvisited adjacent node, sets that to current
					nextNode = true;		//and indicates that the search has progressed.

					break;
				}
			}
		}

		if(!nextNode)						//If there are no unvisited edges, pops a node off the stack and
		{									//sets current node to it.
			if(nodeStack.isEmpty() == 1)	//Stops the search once there is nothing left in the stack.
			{
				done = true;
			}
			else
			{
				current = nodeStack.pop();
			}
		}
	}

	cout << "The order of discovered nodes using Depth First-Search is: " << endl;
	for(int i = 0; i <= order; ++i)
	{
		cout << discovered[i] << " -> ";	//Prints out the order of discovered nodes.
	}
}

void AdjacencyMatrix::Prims()
{
  int selected[numNodes];
	int i;
	int j;
	int numEdges;
  int min;
  int x;
  int y;

  for(i=0;i<numNodes;++i)
	{
     selected[i] = false;
	}

  selected[0] = true;
  numEdges = 0;

  while(numEdges < numNodes-1)
	{
     min=10000; //large number to make sure that the next min is less than this and takes its place
     for(i=0; i < numNodes; ++i)
     {
       if(selected[i] == true)
       {
         for(j = 0;j < numNodes;++j)
         {
           if(selected[j] == false)
           {
             if(min > matrix[i][j])
             {
               min = matrix[i][j];
               x = i;
               y = j;
             }
           }
          }
        }
     }
     selected[y] = true;
     cout << "\n" << x+1 <<" --> " << y+1;
     numEdges = numEdges+1;
  }
  cout << endl;
}

void AdjacencyMatrix::Dijkstras()
{
	int distance[numNodes];
	predecessor = new int[numNodes];
	bool wasVisited[numNodes]; //keep track of visited nodes
	cout<<"Enter the source vertex\n";
  cin>>source;

	//initialize
	for(int i = 0 ;i < numNodes; ++i)
	{
    wasVisited[i] = false;
    predecessor[i] = -1;
    distance[i] = 10000;
  }
    distance[source]= 0;

	//calculate distance
	int minDistance = 10000;
	int closestUnmarkedNode;
	int count = 0;
	while(count < numNodes)
	{
		int minDistance = 10000;
 		for(int i = 0; i<numNodes; ++i)
		{
			if((!wasVisited[i]) && ( minDistance >= distance[i]))
			{
					 minDistance = distance[i];
					 closestUnmarkedNode = i;
			}
	 	}
		wasVisited[closestUnmarkedNode] = true;
		for(int i=0; i<numNodes; ++i)
		{
				if((!wasVisited[i]) && (matrix[closestUnmarkedNode][i]>0) )
				{
						if(distance[i] > distance[closestUnmarkedNode]+matrix[closestUnmarkedNode][i])
						{
								distance[i] = distance[closestUnmarkedNode]+matrix[closestUnmarkedNode][i];
								predecessor[i] = closestUnmarkedNode;
						}
				}
		}
		count++;
	}

	//print results
	for(int i=0; i<numNodes; ++i)
	{
        if(i == source)
            cout<<(char)(source + 97)<<".."<<source;
        else
            DijkstraPrint(i);
        cout<<"->"<<distance[i]<<endl;
	}
}

//helps to repeatedly print out Dijkstra output
void AdjacencyMatrix::DijkstraPrint(int node)
{
    if(node == source)
        cout<<(char)(node + 97)<<".";
    else if(predecessor[node] == -1)
        cout<<"No path from “<<source<<”to "<<(char)(node + 97)<<endl;
    else
		{
        DijkstraPrint(predecessor[node]);
        cout<<(char) (node + 97)<<".";
    }
}
