#include <iostream>
using namespace std;


// define a node for containing the sparse matrix elements
struct MatrixNode {
	int row;  // it holds the row number of the nonzero element
	int col;   // it holds the column number of the nonzero element
	double elem;   // it actually holds the nonzero number
	MatrixNode *next;   // pointer to the next node
};



MatrixNode* AddElem(MatrixNode* head, int row, int col, double element) {
	// A function that adds an element to the passed linked list and returns the head pointer to the linked list
	
	MatrixNode* newNode = new MatrixNode;  // create a new node
	newNode->row = row;  // add row value
	newNode->col = col;   // add column value
	newNode->elem = element;   // add the element at that position
	newNode->next = NULL;   // point next pointer to newNode to be NULL by default
	
	if (head == NULL) {
		head = newNode;  // make newNode as the head
	}
	else {
		// we actually add the newNode at the head postion. 
		newNode->next = head;  // add newNode after the head
		head = newNode;  // change the head to the newNode
	}
	
	// observe that the end of the linked list always points to NULL
	
	return head;
}


MatrixNode* transpose(MatrixNode* head) {
	MatrixNode *transhead = NULL; // head pointer to point the linked list containing transposed matrix
	
	MatrixNode* temp;  
	for (temp = head; temp != NULL; temp=temp->next) {
		// that means in the original matrix linked list, there are still some nonzero elements to consider
		
		int row = temp->row;  // the row index of original matrix
		int col = temp->col;  // the col index of original matrix
		double elem = temp->elem; // the element of the original matrix
		
		transhead = AddElem(transhead, col, row, elem);  // add the element to the transposed matrix,
		// with the column index being passed as row and row index being passed as column.
		
	} 
	
	return transhead;  // return the transposed matrix linked list.
}


double FindElem(MatrixNode* head, int i, int j) {
	// Finds whether there is an element in (i,j)-th position of the matrix, if there is one, display it
	MatrixNode *temp = head;
	for (temp = head; temp != NULL; temp=temp->next) {
		// there are still nonzero elements in the linked list
		if (temp->row == i && temp->col == j) {
			// if the row and the column matches, then return the element as it is.
			double element = temp->elem;
			return element;
		}
		
	}
	
	return 0;  // if nothing returns and no row column is matched, then we return 0
}


void displayMatrix(MatrixNode* head, int maxrow, int maxcol) {
	// this function displays the matrix
	for (int i=0; i<maxrow; i++){
		for (int j=0; j<maxcol; j++) {
			cout << " " << FindElem(head, i,j) << " ";	
		}
		cout << endl;
	}
}



int main() {
	int maxrow;  // the number of rows to take
	int maxcol;   // the number of columns to take
	int addmore;
	
	int rowindex;
	int colindex;
	double element;
	
	cout << "How many rows does the matrix have? ";
	cin >> maxrow;
	cout << "How many columns does the maxtrix have? ";
	cin >> maxcol;
	
	cout << "By convention, you should consider the row and the column indices starting at 0.";
	cout << " Please add the nonzero elements as specified in the following instruction";
	
	MatrixNode *originhead = NULL; // the head pointer of the linked list containing original matrix
	MatrixNode *transhead = NULL; // the head pointer of the linked list containing transposed matrix
	
	while (1!=0) {
		// produces an infinite loop
		cout << "Does the sparse matrix has more nonzero elements? Type 1 for yes, 0 for no. -- :";
		cin >> addmore;
		if (addmore == 0) {
			break;
		}
		
		else if (addmore == 1) {
			cout << "Enter the description of nonzero element as follows: \n";
			cout << "Row index: ";
			cin >> rowindex;
			cout << "Column index: ";
			cin >> colindex;
			cout << "The matrix element: ";
			cin >> element;
			
			originhead = AddElem(originhead, rowindex, colindex, element);
			
		}
	}
	
	cout << "\nNow we shall display the matrix and its transpose.\n\n\n";
	
	transhead = transpose(originhead);
	
	cout << "The original matrix is as follows\n";
	displayMatrix(originhead, maxrow, maxcol); // display the original matrix
	
	cout << "\nThe transposed matrix is as follows\n";
	displayMatrix(transhead, maxcol, maxrow);
	
	return 0;
}







