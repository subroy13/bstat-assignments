#include <iostream>
#include <cstdlib>

using namespace std;

/* ===================================================================
	THE IDEA
	
	We represent the vertices by 0,1,2,...(n-1). For each vertex, there is an array of linked list headers;
	Each of this linked list contains an ordering of the edges incident to the vertex in consideration.
	Such headers are contained in the array 'FirstEdge' and edge.next points to the next edge in that linked list.
	
	We maintain two seperate stacks, one to push to edges and another to push the vertices in consideration.
	
	There remains another array of booleans called 'unmarked' which contains whether that node is visited or not

*/

struct Edge {
	int startpoint;
	int endpoint;
	Edge* next;
}; // define an edge structure containing the starting points and the ending points 

/* ===================================================================
                      STACK UTILITY FUNCTIONS
====================================================================== */

int Edgetop = -1; // the global pointer to edge stack top
int Vertextop = -1; // the global pointer to vertex stack top

void PushtoEdgeStack(Edge* elem, Edge *stack[]) {
	Edgetop++; // increase the top position
	stack[Edgetop] = elem;  // put the element at the top position of the stack 
} // push function into the edgestack

Edge* PopfromEdgeStack(Edge *stack[]) {
	Edge* temp = stack[Vertextop];
	Edgetop--; // decrease the stack top
	return temp; // return the stack top
}

void PushtoVertexStack(int v, int stack[]) {
	Vertextop++;
	stack[Vertextop] = v;
} // push function into the vertex stack

int PopfromVertexStack(int stack[]) {
	int v = stack[Vertextop];
	Vertextop--;
	return v;
}// pop the vertex from the top of the stack


/* ===================================================================
                      GENERATING THE GRAPH
====================================================================== */

int BuildMyGraph(int serial, Edge *First[]) {
	// serial denotes which graph we do want to build among the given L1, L2, L3, L4, L5.
	// this builds the graph with building the First and return the number of vertices.
	
	// by default we choose a First of size 10, since none of the graph has more than 10 vertices
	switch (serial){
		case 1: {
			Edge* temp = new Edge;
			
			// for vertex 0
			temp->startpoint = 0; temp->endpoint = 1; temp->next = new Edge;
			temp->next->startpoint = 0; temp->next->endpoint = 2; temp->next->next = new Edge;
			temp->next->next->endpoint = -1; First[0] = temp;
			
			// for vertex 1
			temp = new Edge;
			temp->startpoint = 1; temp->endpoint = 0; temp->next = new Edge;
			temp->next->startpoint = 1; temp->next->endpoint = 3; temp->next->next = new Edge;
			temp->next->next->startpoint = 1; temp->next->next->endpoint = 4; temp->next->next->next = new Edge;
			temp->next->next->next->endpoint = -1; First[1] = temp;
			
			// for vertex 2, 3 and 4
			for (int i=2; i<5; i++) {
				temp = new Edge;
				temp->startpoint = i; temp->endpoint = ((i-1)/2); temp->next = new Edge;
				temp->next->endpoint = -1; First[i] = temp;
			}
			
			return 5;  // return the number of vertices
			
			break;
		}
		
		case 2: {
			Edge* temp;
			
			// for vertex 0
			temp = new Edge;
			temp->startpoint = 0; temp->endpoint = 1; temp->next = new Edge;
			temp->next->startpoint = 0; temp->next->endpoint = 7; temp->next->next = new Edge;
			temp->next->next->endpoint = -1; First[0] = temp;
			
			// for other vertices till v6
			for (int i=1; i<7; i++) {
				temp = new Edge;
				temp->startpoint = i; temp->endpoint = (i-1); temp->next = new Edge;
				temp->next->startpoint = i; temp->next->endpoint = (i+1); temp->next->next = new Edge;
				temp->next->next->endpoint = -1; First[i] = temp;
			}
			
			// for vertex v7
			temp = new Edge;
			temp->startpoint = 7; temp->endpoint = 0; temp->next = new Edge;
			temp->next->startpoint = 7; temp->next->endpoint = 6; temp->next->next = new Edge;
			temp->next->next->endpoint = -1; First[7] = temp;
			 
			
			return 8;
			break;
		}
	
		case 3: {
			Edge* temp;
			for (int i=0; i<5; i++) {
				temp = new Edge;
				First[i] = temp;
				for (int j=0; j<5; j++) {
					if (j!=i) {
						temp->startpoint = i; temp->endpoint = j; temp->next = new Edge;
						temp = temp->next;
					}
				}
				temp->endpoint = -1;
			}
			return 5;
			break;
		}
	
		case 4: {
			Edge* temp;
			for (int i=0; i<4; i+=2) { // for vertecies v0 and v2
				temp = new Edge;
				temp->startpoint = i; temp->endpoint = 1; temp->next = new Edge;
				temp->next->startpoint = i; temp->next->endpoint = 3; temp->next->next = new Edge;
				temp->next->next->endpoint = -1;
				First[i] = temp;
			}
			
			// for vertex v1
			temp = new Edge;
			temp->startpoint = 1; temp->endpoint = 0; temp->next = new Edge;
			temp->next->startpoint = 1; temp->next->endpoint = 2; temp->next->next = new Edge;
			temp->next->next->startpoint = 1; temp->next->next->endpoint = 3; temp->next->next->next = new Edge;
			temp->next->next->next->endpoint = -1; First[1] = temp;
			
			// for vertex v3
			temp = new Edge;
			temp->startpoint = 3; temp->endpoint = 0; temp->next = new Edge;
			temp->next->startpoint = 3; temp->next->endpoint = 1; temp->next->next = new Edge;
			temp->next->next->startpoint = 3; temp->next->next->endpoint = 2; temp->next->next->next = new Edge;
			temp->next->next->next->endpoint = -1; First[3] = temp;
			
			return 4;
			break;
		}
	
		case 5: {
			Edge* temp;
			// for vertex v0, v1, v2
			for (int i=0; i<3; i++) {
				temp = new Edge;
				temp->endpoint = -1;
				First[i] = temp;
			}
			
			// for vertex v3
			temp = new Edge;
			temp->startpoint = 3; temp->endpoint = 4; temp->next = new Edge; temp->next->endpoint = -1;
			First[3] = temp;
			
			// for vertex v4
			temp = new Edge;
			temp->startpoint = 4; temp->endpoint = 3; temp->next = new Edge; temp->next->endpoint = -1;
			First[4] = temp;
			
			return 5;
			break;
		}
	
		default: {
			cout << "Please choose a number between 1 and 5...";
			return 0;
			break;
		}
	}
}


/* This FUNCTION randomly builds a graph

void BuildGraph(int n, Edge *First[], int seed=1){
	srand(seed); // set the seed for generating array
	for (int i=0; i<n; i++){
		Edge* temp = new Edge;
		First[i] = temp;
		for (int j=0; j<n; j++){
			// we consider directed graphs here
			if (j!=i) {
				int random_number = rand()%2; // returns 0 or 1
				seed++; // increase the seed each time a random number is generated
				if (random_number==1){
					temp->startpoint = i;
					temp->endpoint = j;
					temp->next = new Edge; // new blank edge
					temp = temp->next;
				}
			}
		}
		// at the end we should add NULL, rather we make the endpoint as -1, which does not exist
		temp->endpoint = -1; //since now temp holds the identity of last node's next
		
	}
	
}*/


void DisplayGraph(Edge *First[], int n){
	// prints the adjacency matrix
	// in (i,j)-th entry, there is an 1 means there is an edge from v_i to v_j
	for (int i=0; i<n; i++){
		Edge* temp = First[i]; // the first edge to consider
		int j_old = 0;
		while (temp->endpoint!= -1){
			int j_cur = temp->endpoint;
			// we need to print (j_cur-j_old) many 0's at first, then print 1 at j_cur's position, update j_old to j_cur+1
			for (int k=0; k<(j_cur-j_old);k++){
				cout << " 0 ";
			}
			cout << " 1 "; //prints 1 at j_cur position
			j_old = j_cur+1;
			temp = temp->next; // update temp for next iteration 
		}
		// now we need to print (n-j_old) many 0's, and then an end of line
		for (int k=0; k<(n-j_old);k++){
			cout << " 0 ";
		}
		// finally print an end of line
		cout << endl;
	}
	
	cout << endl;// just to make some spacing
}


/* ===================================================================
                      UTILITY FUNCTION TO CHECK WHETHER ALL VERTICES ARE MARKED
====================================================================== */

bool marked[10];  // defined in global environment so that it can be accessed everywhere

int Findunmarked(int n) {
	for (int i=0; i<n; i++){
		if (marked[i]==false)
			return i;
	}
	return -1; // if the loop is executed and it does not return anything, then it returns -1
}//return an unmarked vertex

int Parents[10]; // contains the name of the parent in DFS tree
	

/* ===================================================================
                      NON - RECURSIVE DFS to check cycle
====================================================================== */

bool DFS_CheckCycle(Edge *First[], int n) {
	// input is the first edges to visit, the rest of the edges follow and the number of vertices
	int VertexStack[n]; // there can be at most n vertices, so a stack of n vertices would suffice
	Edge *EdgeStack[(n*n)];   // there can be O(n^2) vertices, so a stack of n^2 would suffice
	
	while (Findunmarked(n)!= -1){
		int v = Findunmarked(n);  // the index of unmarked vertex
		
		marked[v] = true; // mark it so that it remains visited
		Edge* edge = First[v];  // consider the first edge to be visited from v
		PushtoVertexStack(v, VertexStack); // push vertex v to the stack
		PushtoEdgeStack(edge, EdgeStack); // push edge to the stack
		
		//define something called parent as a running variable
		int parent = v; // current vertex is the parent
		int child; // make child is none, will be updated
		while (Vertextop!=-1 && Edgetop!=-1) {
			// that means some vertex or some edge should be considered
			 
			edge = PopfromEdgeStack(EdgeStack); // pop the edge from the stack
			
			while (edge->endpoint!=-1){
				// that means we can go further down
				child = edge->endpoint; // child is the next operating vertex
				//update its Parent
				Parents[child] = parent;
				
				cout << endl << "Going from - " << parent << "\t to - " << child ;
				
				
				if (marked[child]==true){
					// that means child has been visited previously, 
					// that means it can be either the reverse edge or the backedge. If it is a backedge then we have a cycle.
					// if it is the reverse edge, that means the child I am now considering 
					// is actually marked exactly before the parent, i.e. the child is actually Parents[parent]
					if (Parents[parent]==child)
						{	edge = edge->next; // just continue
							cout << "<--- This edge has been counted already!!!" << endl;
						}
					else
						return true; // that there is a cycle						
				
				}
				else {
					// that means the child is an unmarked vertex
					marked[child] = true; // so we mark it
					PushtoEdgeStack(edge->next, EdgeStack);  //this enables us to return to child after we are done with it
					edge = First[child]; // the first edge from the child to be visited
					parent = child; // modify the parent
					PushtoVertexStack(parent, VertexStack); // push the vertex to vertex stack
				}
				
			}
			child = PopfromVertexStack(VertexStack); // if you are done with the current child remove it from stack
			if (Vertextop!= -1){
				// we should update the parent which is now at the top of stack
				parent = PopfromVertexStack(VertexStack); // however we should retain the parent in the stack
				PushtoVertexStack(parent, VertexStack);
			}
		}
	}
	
	// if even after DFS we find no cycle, return false
	return false;
}



int main() {
	Edge *First[10];
	int n;
	n = BuildMyGraph(2, First);  // change the serial number 1,2,3,4 or 5 to see DFS for different graphs
	
	if (n>0) {
		DisplayGraph(First, n);	
		cout << endl;
	
		for (int i=0;i<10;i++)
			marked[i]=false;
	
		bool temp = DFS_CheckCycle(First, n);
		if (temp)
			cout << "\nThere is a cycle....";
		else
			cout << "\nThere is no cycle";	
	}
	
	return 0;
}
