#include <iostream>
using namespace std;

class AdjacencyMatrix
{
	private:
		int numNodes;			//Used to initialize the matrix and other collections.
		int source; 			//Used for Dijkstras algo
		bool* wasVisited;	//Array used to mark visited nodes.
		int* predecessor;
		int** matrix;			//2D int array used as the matrix; ints will be 0/1 for unweighted edges.

	public:
		AdjacencyMatrix(int n);
		~AdjacencyMatrix();

    void print();
		void addEdge(int source, int dest);
		void inputEdges();
		void DFS();
		void Prims();
		void Dijkstras();
		void DijkstraPrint(int node);

};
