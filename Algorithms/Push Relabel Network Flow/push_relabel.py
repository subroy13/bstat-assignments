# This is the implementation of Push Relabel Algorithm


class Graph:
    '''
    class that holds a graph with its capacity
    It also holds the residual capacities in the corresponding residual graph
    We assume,
            0 = index of source vertex
            (n-1) = index of sink vertex

    e_flow is the array of excess flows in the vertices
    '''

    def __init__(self, n, mat):
        self.nVertex = n  # the number of vertices
        self.residMatrix = mat

    def addEdge(self, u, v, cap):
        # add an residual edge in the forward direction as the flow is 0
        self.residMatrix[u][v] = cap

    def addFlow(self, u, v, flow):
        # increase the flow from u to v
        # reduce residual capacity of forward edge
        self.residMatrix[u][v] -= flow
        # increase flow to reverse edges
        self.residMatrix[v][u] += flow

    def preFlow(self):
        n = self.nVertex
        self.e_flow = [0 for i in range(n)]     # initialize the excess flow
        self.height = [0 for i in range(n)]     # initialize the heights
        self.height[0] = n
        # to find a vertex with excess flow and of maximum height,
        # we keep a list of buckets, sorted by heights
        # since the maximum possible height is (2n -1) for an vertex with positive excess
        self.hBuckets = [[] for i in range(2*n)]
        # maximum height of a vertex having positive excess in current graph
        self.maxheight = 0

        for v in range(1, n):
            if self.residMatrix[0][v] > 0:
                # the edge from source 0 to v exists
                self.e_flow[v] = self.residMatrix[0][v]
                # add a flow equal to the capacity in initialization step
                self.addFlow(0, v, self.residMatrix[0][v])
                # we add a vertex of height 0 to our bucket for height 0
                self.hBuckets[0].append(v)

    def findExcessVertex(self):
        # returns the index of the vertex with positive excess having maximum height
        if len(self.hBuckets[self.maxheight]) > 0:
            return self.hBuckets[self.maxheight][0]
        else:
            return -1

    def push(self, u, v):
        # pushes the excess flow from u to v, we must have h(u) = h(v) + 1
        n = self.nVertex
        cap = self.residMatrix[u][v]    # residual capacity of u to v
        excess = self.e_flow[u]         # excess flow at u
        if (cap < excess):
            # this means it is a saturating push, and there still remains some excess at u
            self.addFlow(u, v, cap)
            if self.e_flow[v] == 0 and v != 0 and v != (n-1):
                # if excess at end vertex was 0, then it is gonna increase, so we should
                # append v to the height buckets
                # we should not add source or sink to hBuckets for choice
                self.hBuckets[self.height[v]].append(v)

            self.e_flow[v] += cap   # excess at v is increased
            self.e_flow[u] -= cap   # excess at u reduces
        else:
            # this means it is a non saturating push, and the excess at vertex u vanishes
            self.addFlow(u, v, excess)
            if self.e_flow[v] == 0 and v != 0 and v != (n-1):
                # add v to bucket of excess vertices
                self.hBuckets[self.height[v]].append(v)

            self.e_flow[v] += excess
            self.e_flow[u] -= excess

            # since now excess at u is 0, we have to remove u from hBucket
            # Note that, by our choice of u, u = self.hBuckets[self.maxheight][0]

            # remove the vertex u from our bucket
            self.hBuckets[self.maxheight].pop(0)
            while len(self.hBuckets[self.maxheight]) == 0 and self.maxheight > -1:
                # if there is no other maximum height element
                self.maxheight -= 1
        return(min(cap, excess))

    def relabel(self, u):
        # relabels a specified vertex by height 1
        # since it is relabeled, we must have excess at vertex u and its height is maximum
        self.height[u] += 1
        # remove the vertex u from our basket
        self.hBuckets[self.maxheight].pop(0)
        self.maxheight += 1
        self.hBuckets[self.maxheight].append(
            u)         # add vertex u to new list

    def findMaxFlow(self):
        n = self.nVertex
        self.preFlow()
        print('Initialized heights are = ', self.height,
              'with max height = ', self.maxheight)
        iteration = 1
        u = self.findExcessVertex()
        while (u != -1):
            print(
                '------------------------------------------------------------------')
            print('---------------------- ITERATION ',
                  iteration, '-------------------------')
            print(
                '------------------------------------------------------------------')
            iteration += 1
            # check whether there is any downward edges
            downEdge = False
            for v in range(n):
                if u != v:
                    # we does not allow loops for now
                    if self.residMatrix[u][v] > 0:
                        # there is an edge in residual matrix
                        if self.height[u] == (self.height[v] + 1):
                            # if the edge goes downward by one unit
                            downEdge = True
                            pushed = self.push(u, v)
                            print('u = ', u, 'passes flow = ',
                                  pushed, ' to v = ', v)
                            break
            if not downEdge:
                print('u = ', u, 'got relabeled...')
                # relabel the vertex u as there is no downward edge
                self.relabel(u)

            u = self.findExcessVertex()
            print('Excess flows are = ', self.e_flow)
            print('heights are = ', self.height,
                  'with max height = ', self.maxheight)
        else:
            # means no excess vertex left
            return self.e_flow[(n-1)]       # excess at sink is the max flow

    def displayResidGraph(self):
        n = self.nVertex
        print('Residual Graph is as follows:')
        for i in range(n):
            print(self.residMatrix[i])


#graph = [[0, 16, 13, 0, 0, 0],
#         [0, 0, 10, 12, 0, 0],
#        [0, 4, 0, 0, 14, 0],
#         [0, 0, 9, 0, 0, 20],
#         [0, 0, 0, 7, 0, 4],
#         [0, 0, 0, 0, 0, 0]]

graph = [[0, 11, 12, 0, 0, 0],
        [0, 0, 0, 12, 0, 0],
        [0, 1, 0, 0, 11, 0],
        [0, 0, 0, 0, 0, 19],
        [0, 0, 0, 7, 0, 4],
        [0,0,0, 0, 0, 0]]


myGraph = Graph(6, graph)

print('\n\nMaximum possible Flow is =>', myGraph.findMaxFlow())
myGraph.displayResidGraph()
