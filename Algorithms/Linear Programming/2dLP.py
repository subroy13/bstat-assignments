############################################################################
# Implementation of Randomized Incremental Algorithm for Linear Programming
# Author: Subhrajyoty Roy (BS1613)
############################################################################

# importing necessary modules
import random   # for generating random sequence


# input the coefficient for the objective function,
# say objective is x0 = c1*x1 + c2*x2, then input c1, c2
print('\nInput the coefficients of objective function separated by comma')
objective = list(map(int, input().split(',')))

# the input has to be in the standard form , i.e. Ax <= b form
# It does not assume the non-negativity constraints
print('How many constraints are there? (Including non-negativity constraints)')
n = int(input())
constraints = []

print('\nFor example, if you want x1 >= 0, you should type -1,0,0, (all in Ax <= b form)\nAgain, if you want 2*x1 + 5*x2 <= 19, you should type 2,5,19\n')

for i in range(n):
    print('\nInput the ', (i+1),
          '-th constraint coefficients and constant term, seperated by commas')
    cons = input().split(',')
    if len(cons) != 3:
        print('You entered something wrong!')
    else:
        cons = list(map(int, cons))
        constraints.append(cons)


def Randomize(constraints):
    """
    Randomize the set of constraints in an arbitrary order
    """
    # we can simply use ----      random.shuffle(constraints)
    # however, the shuffling is also implemented here from scratch, which would take additional O(n) time.
    for i in range(n-1, 0, -1):
        # starting from the last element, we generate a random index between 0 to i (including i), 
        # and then swap it with i-th element
        j = random.randint(0, i+1)
        constraints[j], constraints[i] = constraints[i], constraints[j]  # swap the elements
        
    return constraints

def Initial_Solution(objective, M = 1000000):
    """
    Finds an initial point by bounding the whole region
    i.e. using some artificial bounding region
    """
    if objective[0] > 0:
        cons1 = [1, 0, M]
        x1 = M
    else:
        cons1 = [-1, 0, M]
        x1 = -M
    if objective[1] > 0:
        cons2 = [0, 1, M]
        x2 = M
    else:
        cons2 = [0, -1, M]
        x2 = -M

    point = [x1, x2]
    return (point, cons1, cons2)

def SolveLP(objective, constraints, M = 1000000):
    """
    Main wrapper function to solve LP
    """
    constraints = Randomize(constraints)
    if (len(constraints)) < 2:
        return 'The problem is Unbounded'
    else:
        point, cons1, cons2 = Initial_Solution(objective, M)  # get the initial corner vertex
        constraints = [cons1, cons2] + constraints   # add the artificial constraints to the constraint set
        for i in range(2, len(constraints)):
            # there are two cases,
            # one -- the current optimum vertex is feasible after adding new constraint
            # two -- the current optimum vertex is infeasible after adding new constraint
            infeasible = bool(point[0] * constraints[i][0] + point[1] * constraints[i][1] > constraints[i][2])
            if not infeasible:
                # the point is not changed, so nothing happens
                pass
            else:
                # current optimum vertex lies on the boundary of constraints[i]
                a1 = constraints[i][0]
                a2 = constraints[i][1]
                b = constraints[i][2]

                # the boundary line is  a1*x1 + a2*x2 = b
                # solving we get, x1 = (b - a2*x2)/a1  if a1 is not equal to 0
                # similar for x2 and a2
                upperBounds = []
                lowerBounds = []  # contains the upper and lower boundaries of the reduced problem (explained below)
                if a1 != 0:
                    # then we need to change the objective function and the constraints
                    # objective function changes to; c1*(b - a2*x2)/a1 + c2*x2 = c1*b/a1 + (c2 - c1*a2/a1)*x2
                    # therefore, whether to increase or decrease x2 depends on the sign of (c2 - c1*a2/a1)
                    # now consider the constraints;
                    # p1*x1 + p2*x2 <= c transforms to p1*b/a1 + (p2 - p1*a2/a1)*x2 <= c
                    for j in range(i):
                        temp = constraints[j][1] - constraints[j][0]*a2/a1
                        if temp > 0:
                            # then x2 <= (c- p1*b/a1)/(p2 - p1*a2/a1)
                            upperBound = (constraints[j][2] - constraints[j][0] * b/a1)/temp
                            upperBounds.append(upperBound)
                        elif temp == 0:
                            # then we should have p1*b/a1 <= c, if not, then the problem is infeasible
                            if (constraints[j][0] * b/ a1) > constraints[j][2]:
                                return 'The problem is infeasible'
                        else:
                            # therefore, temp < 0
                            lowerBound = (constraints[j][2] - constraints[j][0] * b/a1)/temp
                            lowerBounds.append(lowerBound)
                    
                    #if the minimum of upperBounds is less than the maximum of lower Bounds, 
                    # then the problem is infeasible
                    if max(lowerBounds) > min(upperBounds):
                        return 'The problem is infeasible'
                    temp = objective[1] - objective[0]*a2/a1
                    if temp > 0:
                        # therefore, we should choose the maximum value of x2, i.e. the minimum of upperBounds
                        if len(upperBounds) == 0:
                            # the reduced problem is unbounded
                            return 'The problem is unbounded'
                        else:
                            x2 = min(upperBounds)
                            x1 = (b - a2*x2)/a1
                    else:
                        # if temp == 0, then the objective function does not 
                        # change over this line, so we can choose any point on this bounded line as optimum
                        # if temp < 0, we should choose the minimum value of x2, i.e. the max of lowerBounds
                        if len(lowerBounds) == 0:
                            return 'The problem is unbounded'
                        else:
                            x2 = max(lowerBounds)
                            x1 = (b - a2*x2)/a1
                
                else:
                    # the same holds, with roles of a1 and a2 interchanged
                    # here, x2 = (b - a1*x1)/a2
                    # p1*x1 + p2*x2 <= c means (p1 - p2*a1/a2)*x1 <= (c - p2*b/a2)
                    for j in range(i):
                        temp = constraints[j][0] - constraints[j][1]*a1/a2
                        if temp > 0:
                            # then x1 <= (c- p2*b/a2)/(p1 - p2*a1/a2)
                            upperBound = (constraints[j][2] - constraints[j][1] * b/a2)/temp
                            upperBounds.append(upperBound)
                        elif temp == 0:
                            # then we should have p2*b/a2 <= c, if not, then the problem is infeasible
                            if (constraints[j][1] * b/ a2) > constraints[j][2]:
                                return 'The problem is infeasible'
                        else:
                            # therefore, temp < 0
                            lowerBound = (constraints[j][2] - constraints[j][1] * b/a2)/temp
                            lowerBounds.append(lowerBound)
                    
                    #if the minimum of upperBounds is less than the maximum of lower Bounds, 
                    # then the problem is infeasible
                    if max(lowerBounds) > min(upperBounds):
                        return 'The problem is infeasible'
                    temp = objective[0] - objective[1]*a1/a2

                    if temp > 0:
                        # therefore, we should choose the maximum value of x1, i.e. the minimum of upperBounds
                        if len(upperBounds) == 0:
                            # the reduced problem is unbounded
                            return 'The problem is unbounded'
                        else:
                            x1 = min(upperBounds)
                            x2 = (b - a1*x1)/a2
                    else:
                        if len(lowerBounds) == 0:
                            return 'The problem is unbounded'
                        else:
                            x1 = max(lowerBounds)
                            x2 = (b - a1*x1)/a2
                
                point = [x1, x2]
            
        #if the optimum point, in some way, lies of the boundary, it is assumed to be unbounded
        if point[0]== M or point[0]==(-M) or point[1] == M or point[1] == (-M):
            return 'The problem is unbounded (approximately)'
        else:
            opt_objective = objective[0]*point[0] + objective[1]*point[1]
            result = 'The optimum value of the objective function is', opt_objective, 'and the optimum solution is', point
            return result        


output = SolveLP(objective, constraints)
print(output)
print('Thank you!')










