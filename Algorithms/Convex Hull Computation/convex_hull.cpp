#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;


/* ==========================================================
  SOME BASIC GLOBAL DEFINITIONS
========================================================   */

unsigned int seed=1;  // the random generator seed

struct Point { 
	float x,y;
};    // define a structure to hold the point's x-coordinate and y-coordinate

struct Hull {
	float x,y;
	Hull* next;
}; // an immplementation of a stack to hold the points on the convex hull

/*
	An array can be used to save the points of the hull, however, that would consume extra memory as array
	is a static data structure. Therefore, we use a linked list and implement it as stack of points to represent the hull.
*/

// stack push function
Hull* PushtoHull(Hull* top, float x, float y){
	Hull* temp = new Hull; // create a new hull point
	temp->x = x;
	temp->y = y;
	temp->next = top; // add the new hull point to the top of the stack
	top = temp; // modify the stack
	
	return top;
}


Hull* PopfromHull(Hull* top, Point* p) {
	p->x = top->x;
	p->y = top->y;
	return (top->next);
}

// stack print function, Note: We don't actually call this function. 
// This is just to check whether the algorithms are working fine

void DisplayHull(Hull* top){
	Hull* index = top; // start from the top of the stack
	while (index!=NULL){
		cout << "[" << index->x << "," << index->y << "]" << endl;
		index = index->next; // index is modified
	}
}


int Orientation(Point p, Point q, Point r){
	/* this function checks whether the line segment -p-r- lies on the anti-clockwise direction of line -p-q-.
	To do that, we observe that, the line segment -q-r- should have more slope than the line -p-q-
	
	The slope of line -q-r- is (r.y - q.y)/(r.x - q.x)
	The slope of line -p-q- is (q.y - p.y)/(q.x - p.x)
	
	If the first quantity is more than the second one, then considering the numerator of the expression,
	(r.y - q.y)/(r.x - q.x) - (q.y - p.y)/(q.x - p.x), we obtain;
	the condition is to check whether the expression;
	(r.y - q.y) * (q.x - p.x) - (q.y - p.y) * (r.x - q.x) is greater than 0 or not   
	*/
	
	float anglediff = (r.y - q.y) * (q.x - p.x) - (q.y - p.y) * (r.x - q.x);
	if (anglediff>0) 
		return 1;  // that means counterclockwise
	else if (anglediff == 0)
		return 0; // collinear
	else
		return -1; // clockwise
}


float Distance(Point p, Point q) {
	// computes the squared distance between point p and q
	float dist = (p.x-q.x)*(p.x-q.x) + (p.y-q.y)*(p.y-q.y);
	return dist;
}

bool AngleCompare(Point base, Point p1, Point p2) {
	// returns 1 if point p2 makes more angle with base point than p1
	// returns 0 if point p2 makes less angle with base point than p1
	int temp = Orientation(base, p1, p2);
	if (temp == 0) {
		// that means collinear, tie should be broken using distance
		if (Distance(base, p1) < Distance(base, p2))
			return 1; // means p2 should be bigger in our order
		else
			return 0;
	}
	
	if (temp>0)
		return 1; // as p2 makes bigger angle
	else
		return 0;
}

/* ================================================================ 
						QUICKSORT,     // This is used as a fast sorting algorithm to sort the angles in SimplePolygon
   ================================================================ */


int partition(Point arr[], int left, int right) {
	// choose the leftmost element as pivot
	Point pivot = arr[left];
	int l = left; // the moving index on left side
	int r = right;  // the moving index on right side
	
	while (l < r) {
		
		while (AngleCompare(arr[0], pivot, arr[r])==1 && l < r) {
			// it is makes bigger angle with arr[0] than pivot or is collinear
			 	r--;		
		}
		
		
		while (AngleCompare(arr[0], pivot, arr[l])==0 && l < r) {
			// it is makes smaller angle with arr[0] than pivot or is collinear
				l++;
		}
		// now, there is an angle bigger than pivot on left, and smaller than pivot on right, so swap them,	
		Point temp = arr[l];
		arr[l] = arr[r];
		arr[r] = temp;
	}
	
	// now l=r, however, as r decreases first, so l = r will be somewhere where the element is less than pivot
	// so, swap the current arr[r] or arr[l] with the pivot
	
	
	arr[left] = arr[r];
	arr[r] = pivot;
	
	return l; // return the pivot index
}


void quicksort(Point arr[], int left, int right) {
	if (left < right) {
		// the array is of atleast length 1
		int pivotIndex = partition(arr, left, right);
		
		quicksort(arr, left, (pivotIndex - 1));
		quicksort(arr, (pivotIndex + 1), right);
	}
		
}



/* ==========================================================
  ALGORITHM JARVIS MARCH
========================================================   */

Hull* JarvisMarch(Point arr[], int n) {
	// the input is the array of points or the set of points, and n is the size of the array
	
	if (n < 3)
		cout << "Not Possible to construct a Convex Hull!"; 	// means it is not possible to create a convex hull
	else {
		
		// to find the point with minimum x coordinate let its index be called as 'left'
		int left = 0;
		for (int i=1; i<n; i++){
			if (arr[i].x < arr[left].x) {
				// that means the left most point should be updated
				left = i;
			}
		}
		
		/* Now we have the left most point, so we should calculate the angles 
		 that the line joining this point and any other point makes */
		int index1 = left;  // start with the left most point as pivot point
		int index2;
		Hull* top = NULL;
		
		do {
			top = PushtoHull(top, arr[index1].x, arr[index1].y); // the iterating point belongs to hull
			
			// we find the point that makes minimal angle with the index1 point
			// i.e. for any other point r, the segment -index1-r- should remain in anticlockwise direction -index1-index2-
			
			index2 = (index1 + 1)%n;  // index2 may exceed index1, so we loop back
			for (int i=0; i < n; i++){
				if(Orientation(arr[index1], arr[i], arr[index2])==1)
					index2 = i;  // if -index1-index2- remains in anticlockwise direction of -index1-i-, 
					// that means the line -index1-i- has lower angle
			}
			
			// Now that we have the next point with minimum angle
			index1 = index2;  // update the next point as next pivot point.
			
			
		} while (index1 != left);  // if index==left, then we have closed off the hull and we are done.
		
		return top;	
	}
	
}



/* ==========================================================
  ALGORITHM GRAHAM SCAN
========================================================   */

Hull* SimplePolygon(Point arr[], int n) {
	// returns a stack of points with ordering of simple polygon
	// firstly, we find the point with minimum x coordinate, if there is tie, then use minimum y-coordnite
	
	// to find the point with minimum x coordinate let its index be called as 'left'
	int left = 0;
	for (int i=1; i<n; i++){
		if (arr[i].x < arr[left].x) {
			// that means the left most point should be updated
			left = i;
		}
		else if (arr[i].x == arr[left].x)
			if (arr[i].y < arr[left].y)
				left = i; //update the minimum point if x-coord is same y-coord is less
	}
	
	// now we swap the left with arr[0]
	Point temp = arr[0];
	arr[0] = arr[left];
	arr[left] = temp;
	
	
	// now we should perform sorting of angles keeping arr[0] intact
	quicksort(arr, 1, n-1); // now we should have all points sorted
	
	
	// finally return by putting them in a stack in that order
	Hull* poly = NULL;
	for (int i = (n-1); i>=0; i--) {
		poly = PushtoHull(poly, arr[i].x, arr[i].y); // put them into stack in reverse order
	}
	
	return poly;
}


Hull* GrahamScan(Point arr[], int n){
	if (n < 3)
		cout << "Not possible to construct a convex hull!";
	else {
		Hull* poly = SimplePolygon(arr,n);
		Hull* top = NULL; // contains the actual hull
		
		Point iter; // point for iteration
		for (int i = 0; i < 3; i++){
			poly = PopfromHull(poly, &iter);
			top = PushtoHull(top, iter.x, iter.y);
		} // performing this three times creates a three point convex region, maybe not containing all the points
				
		
		while (poly!=NULL) {
			// there are still points to pursue
			// choose a new point from polygon, call it iter
			Point iter;
			poly = PopfromHull(poly, &iter);
			// choose two points from the hull, call them p_hull1 and p_hull2
			// The order of the points in the simple polygon is like p_hull1, p_hull2 and iter
			Point p_hull1, p_hull2;
			top = PopfromHull(top, &p_hull2); // pick p_hull2 first
			top = PopfromHull(top, &p_hull1);
			
			// now, we should check whether including new iter point still makes a convex region
			// this can be checked by checking the orientation counter-clockwise
			if (Orientation(p_hull1, p_hull2, iter) >= 0) {
				// that means the region is still convex, hence we should 
				// put p_hull1, p_hull2, and iter into the convex hull in this order
				top = PushtoHull(top, p_hull1.x, p_hull1.y);
				top = PushtoHull(top, p_hull2.x, p_hull2.y);
				top = PushtoHull(top, iter.x, iter.y);
			}
			
			else {
				// that means the region becomes concave, i.e. at p_hull2, there is a concave angle
				// therefore, p_hull2 is a bad point, and hence it should be discarded.
				// And, the next iteration should invlove iter, p_hull1 and the point behind p_hull1
				top = PushtoHull(top, p_hull1.x, p_hull1.y);
				poly = PushtoHull(poly, iter.x, iter.y);  // it is as if we are just deleting the point 
												  //  p_hull2 from further consideration
			}
		}
		
		return top;	
	}
	
}



/* ==========================================================
  SIMULATION FUNCTIONS
========================================================   */

void GeneratePoints(Point arr[], int n) {
	// this function generates n random points
	srand(seed); // set the random seed
	seed += 1; // so that, different calls of GeneratePoints generate different points, even if called within same time
	for (int i=0; i<n; i++){
		arr[i].x = (float)rand();
		arr[i].y = (float)rand();
	}
}

void SimulateTime(int n, int size) {
	//clock_t t1, t2, t3;
	float t1, t2, t3;
	
	t1 = clock(); 
	for (int i=0; i<size; i++) {
		Point arr[n]; // create an empty array of points
		GeneratePoints(arr,n); // fill with random points
		JarvisMarch(arr,n); // perform Jarvis March
	}
	
	t2 = clock(); 
	for (int i=0; i<size;i++) {
		Point arr[n];
		GeneratePoints(arr, n);
		GrahamScan(arr, n); // perform Graham Scan
	}
	t3 = clock(); 
	
	cout << "Time \tn = " << n <<"\t Jarvis March: " << (t2-t1)/size << "\t GrahamScan: " << (t3-t2)/size <<endl;
}

int main() {
	
	int n[10] = {10, 50, 100, 200, 500, 1000, 2000, 3000, 5000, 10000};
	
	for (int i=0; i<10; i++) {
		SimulateTime(n[i], 500); // simulate each for 1000 times and then take average
	}
	
	return 0;
}

















