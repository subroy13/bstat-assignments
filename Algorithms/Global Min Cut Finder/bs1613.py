############################################################################
# Implementation of Karger's Randomized Algorithm for Finding Global Minimum Cut
# Author: Subhrajyoty Roy (BS1613)
# Student, B.Stat Year III, Indian Statistical Institute, Kolkata

# THE PROBLEM
# ----------------------------------------------
# Given an undirected graph, the goal is to output the global minimum cut, i.e. a nonempty set of vertices,
# such that it's complement is also nonempty, and there are minimum number of edges joining between these two 
# sets. Stated differently, the goal is to find the minimum number of edges required to make a network disconnected
# into two connected components.  

############################################################################

# importing necessary modules
import random   # for generating random sequence
import copy     # for making deepcopy of objects

# We represent the graph using a class
class Graph:
        """
        A class representing a graph
        The edges are kept in a list of tuples, tuple (i,j) implies an edge between set S_i and set S_j
        The Sets defines the sets containing respective vertices
        """

        def __init__(self, n):
                self.nEdges = 0   # store the number of edges
                self.nSet = n   # initialize the number of sets to be the number of vertices
                self.edges = []   # initialize with no edges
                self.Sets = [[i] for i in range(n)]    # Sets[i] denotes the i-th set

        def addEdge(self, v1, v2):
                # add an edge between vertex v1 and vertex v2
                self.edges.append((v1, v2))   # insert the tuple (v1, v2) in the list of edges
                self.nEdges += 1   # increase the number of edges

        def ContractEdge(self, e):
                # this function contracts an edge e between set S1 and set S2
                startSet, endSet = e
                # for all vertices in endSet, we set them in startSet
                for v in self.Sets[endSet]:
                        self.Sets[startSet].append(v)
                self.Sets[endSet] = []
                self.nSet -= 1   # decrease the number of sets by 1, as only two sets get merged at a time

                # redirect the edges which ends in endSet, to startSet
                # means for each edge, if it was between some set S_i and S_j
                for i in range(self.nEdges):
                        s1, s2 = self.edges[i]
                        if s1 == endSet:
                                self.edges[i] = (startSet, s2)   # these edges gets redirected to startSet
                        elif s2 == endSet:
                                self.edges[i] = (s1, startSet)   # these edges also get redirected to startSet
                
                # now, for the edges like (startSet, endSet) or (endSet, startSet), these gets converted to (startSet, startSet), self loops
                # we should remove such self loops 
                while (startSet, startSet) in self.edges:
                        self.edges.remove((startSet, startSet))
                        self.nEdges -= 1     # decrease the number of edges


        def KargerMinCut(self):
                while (self.nSet > 2):
                        edgeNo = random.randint(0, self.nEdges-1)   # choose a random edge to contract
                        e = self.edges[edgeNo]
                        self.ContractEdge(e)
                return({'Cut': self.Sets, 'EdgeCount' : self.nEdges})    # return a dictionary with the cut and the value of the cut


def FindMinCut(Graph, nIter):
        # graph is passed to the function 
        # it repeatedly calls Karger's algorithm to find the Global minimum cut
        MinCount = Graph.nEdges   # keep the number of edges as initial minimum value of cut
        MinCut = None
        for i in range(nIter):
                temp = copy.deepcopy(Graph)   # make a deepcopy, so that changing temp does not change the original Graph
                output = temp.KargerMinCut()
                
                if output['EdgeCount'] < MinCount:
                        # update the current minimum cut
                        MinCount = output['EdgeCount']
                        MinCut = output['Cut']
                print('Iteration ',i,' is completed...')
                print('It finds the output:', output, '\n')
        return({'Cut': MinCut, 'EdgeCount' : MinCount})



def MainFunc(n, AdjList, nIter):
        # input is n vertex, Adjacency List and the number of iteration to apply Karger's algorithm
        graph = Graph(n)   # create an object of class Graph
        for i in range(n):
                for j in AdjList[i]:
                        graph.addEdge(i, j)   # add an edge between i and j
        result = FindMinCut(graph, nIter)
        MinCut = result['Cut']
        MinCount = result['EdgeCount']
        MinCut = list(filter(None, MinCut))   # filter out the empty lists

        print('The Possible Minimum Cut is ', MinCut, ' with the value ', MinCount)



# Some Easy Graph (True Answer Value = 2)
n = 4
AdjList = [[1, 2, 3], [3], [3], []]
nIter = 4

# Another Instance (True Answer Value = 2, with cut 0,1,4,5 and 2,3,6,7)
n = 8
AdjList = [[1, 4, 5], [2, 4, 5], [3,6,7], [6,7], [5], [6], [7], []]
#          A           B         C           D     E     F    G    H
#          0           1         2           3     4     5    6    7
nIter = 5

MainFunc(n, AdjList, nIter)



                

                



                        










        






