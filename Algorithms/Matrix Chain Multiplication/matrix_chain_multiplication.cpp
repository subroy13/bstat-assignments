#include <iostream>
#include <cstdlib>
#include <conio.h>

using namespace std;

/* =======================================================
				THE IDEA
	Consider the matrices as A1, A2, ... An.
	The order of the matrices are p0*p1, p1*p2,... p(n-1)*pn, i.e. Ai is of order p(i-1)*pi
	Therefore, we can store these orders in a single array of size (n+1)
	
	To find the optimal order to multiplication of A1*A2*...*An, let this optimal order to multiplication is;
	(A1*A2*...Ak)*(A(k+1)*...An)
	Then, each of the subproblem, (A1*A2*...Ak) and (A(k+1)*...An) needs to be solved optimally, 
	and we need another O(p0*pk*pn) multiplication to multiply these two matrices.
	
	So, we use a dynamic programming, based on the recursion,
	
	M(i,j) = 0 , if i=j
		   = min{M(i,k)+M(k+1,j)+p(i-1)*pk*pj} if i<j and minimum over all i<=k<=j
		   
	where M(i,j) denotes the optimal number of multiplications required for multiplying Ai*...Aj
	this convention is followed for ease of understanding, clearly the entries M(0,j) remains empty.
	Hence, M(i,j) becomes an (n+1)*(n+1) size matrix.
	

=========================================================== */

void matrixchain(int n, int order[], unsigned int** mult, int** position) {
	for (int i=0; i<=n; i++) {
		position[0][i] = 0;
		position[i][0] = 0;
		mult[0][i] = 0;
		mult[i][0] = 0; //since, these are not computed.
	}
	for (int i=1; i<=n; i++) {
		for (int j=1; j<=i; j++){
			mult[i][j] = 0;  // requires no multiplication
			position[i][j]= 0;
		}
	}
	
	
	int length;  // the loop goes inductively on the length of the chain i.e. (j-i)+1 = length
	for (length = 2; length<= n; length++) {
		for (int i=1; i<= (n-length+1); i++) {
			int j = i+length-1;  // simply from the definition of length
			//mult[i][j] = 18446744073709551615; // the maximum integer that c++ compiler supports
			position[i][j] = i;
			mult[i][j] = mult[(i+1)][j] + (order[(i-1)]*order[i]*order[j]); // initialize the mult[i][j] for k=i
			for (int k=(i+1); k<j; k++) {
				unsigned int current_mult = mult[i][k] + mult[(k+1)][j] + (order[(i-1)]*order[k]*order[j]);
				if (current_mult < mult[i][j]) {
					mult[i][j] = current_mult;
					position[i][j] = k;
				}
			}
		}
	}
}

void displayParenthesis (int** position, int i, int j) {
	// display the parenthesis for the multiplication, Ai *...*Aj
	if (i == j) {
		cout << "A" << i;
	}
	else {
		//figure out the breakpoint
		int k = position[i][j];
		cout << "(";  // put the opening parenthesis
		
		displayParenthesis(position, i, k);  // put parenthesis for the multiplication Ai*...*Ak
		displayParenthesis(position, k+1, j);  // put parenthesis for the multiplication A(k+1)*...*Aj
		
		cout << ")";  // put the closing parenthesis
	}
}


int main() {
	int n=-1;
	
	while (n<2) {
		cout << "Please enter the number of matrices:\t";
		cin >> n;
	}
	
	int order[(n+1)]; // create an array of orders of matrices of size n+1;
	
	for (int i=0; i<n; i++) {
		cout << "Please enter the row size of " << (i+1) << "-th matrix:\t";
		cin >> order[i];
	}
	cout << "Please enter the column size of " << n << "-th matrix:\t";
	cin >> order[n];
	
	unsigned int ** mult_arr;
	mult_arr = new unsigned int *[(n+1)];
	for (int i=0; i<=n; i++) {
		mult_arr[i] = new unsigned int[(n+1)];
	}
	
	int ** pos;
	pos = new int *[(n+1)];
	for (int i=0; i<=n; i++) {
		pos[i] = new int[(n+1)]; 
	}
	
	matrixchain(n, order, mult_arr, pos);
	
	cout << "The optimal number of multiplications required is " << mult_arr[1][n];
	
	cout << "\nand\n";
	cout << "The optimal parenthesis scheme is: ";
	displayParenthesis(pos, 1, n);
	
	getch(); //wait for keypress
	
	return 0;
}






