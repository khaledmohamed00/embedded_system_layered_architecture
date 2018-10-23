# search.py
# ---------
# Licensing Information:  You are free to use or extend these projects for
# educational purposes provided that (1) you do not distribute or publish
# solutions, (2) you retain this notice, and (3) you provide clear
# attribution to UC Berkeley, including a link to http://ai.berkeley.edu.
# 
# Attribution Information: The Pacman AI projects were developed at UC Berkeley.
# The core projects and autograders were primarily created by John DeNero
# (denero@cs.berkeley.edu) and Dan Klein (klein@cs.berkeley.edu).
# Student side autograding was added by Brad Miller, Nick Hay, and
# Pieter Abbeel (pabbeel@cs.berkeley.edu).


"""
In search.py, you will implement generic search algorithms which are called by
Pacman agents (in searchAgents.py).
"""

import util

class SearchProblem:
    """
    This class outlines the structure of a search problem, but doesn't implement
    any of the methods (in object-oriented terminology: an abstract class).

    You do not need to change anything in this class, ever.
    """

    def getStartState(self):
        """
        Returns the start state for the search problem.
        """
        util.raiseNotDefined()

    def isGoalState(self, state):
        """
          state: Search state

        Returns True if and only if the state is a valid goal state.
        """
        util.raiseNotDefined()

    def getSuccessors(self, state):
        """
          state: Search state

        For a given state, this should return a list of triples, (successor,
        action, stepCost), where 'successor' is a successor to the current
        state, 'action' is the action required to get there, and 'stepCost' is
        the incremental cost of expanding to that successor.
        """
        util.raiseNotDefined()

    def getCostOfActions(self, actions):
        """
         actions: A list of actions to take

        This method returns the total cost of a particular sequence of actions.
        The sequence must be composed of legal moves.
        """
        util.raiseNotDefined()


def tinyMazeSearch(problem):
    """
    Returns a sequence of moves that solves tinyMaze.  For any other maze, the
    sequence of moves will be incorrect, so only use this for tinyMaze.
    """
    from game import Directions
    s = Directions.SOUTH
    w = Directions.WEST
    return  [s, s, w, s, w, w, s, w]


global found
found=False
visited=[]
st=util.Stack()

def DFS(problem,start,path):
   
   if start not in visited:
       visited.append(start)
   
   if  problem.isGoalState(start):
       found=True
       print "True"
       return 
   print(problem.getSuccessors(start))
   suc=problem.getSuccessors(start)
   if suc == None:
       print "no sucessor"
       return path
   i=0
   for item in suc:
       print("ok")
       if item[0]not in visited:
         st.push(item)
         print "pushed",item
         i=i+1
       if i==0:
         print "no push"
         continue 
   
       global found
       if st.isEmpty() !=True and found==False:
         
         it=st.pop()
         print st.list
         path.append(it[1])
         print(it[1],it[0])
         newpath=DFS(problem,it[0],path)
         if found==False:
            path.pop()
         print st.list
         print path
         if newpath !=None:
             path=newpath
   return path

def depthFirstSearch(problem):
    """
    Search the deepest nodes in the search tree first.

    Your search algorithm needs to return a list of actions that reaches the
    goal. Make sure to implement a graph search algorithm.

    To get started, you might want to try some of these simple commands to
    understand the search problem that is being passed in:

    print "Start:", problem.getStartState()
    print "Is the start a goal?", problem.isGoalState(problem.getStartState())
    print "Start's successors:", problem.getSuccessors(problem.getStartState())
    """
    "*** YOUR CODE HERE ***"
    '''
    print "Start:", problem.getStartState()
    print "Is the start a goal?", problem.isGoalState((2,2))
    print "Start's successors:", problem.getSuccessors((1,1))
    suc=problem.getSuccessors(problem.getStartState())
    actionList=[]
    stateList=[]
    import random
    randomNum=random.randrange(0,len(suc),1)
    
    
    print len(suc)
    #for i in range(1000):
    while not problem.isGoalState(suc[randomNum][0]):
	print randomNum
	randomNum=random.randrange(0,len(suc),1)
	randomAction=suc[randomNum][1]
	
   	#print randomNum
	if suc[randomNum][0] not in stateList:
		stateList.append(suc[randomNum][0])
		actionList.append(randomAction)
    		suc=problem.getSuccessors(suc[randomNum][0])    
    
    #actionList.append(suc[randomNum][0])
    #if kiki==0:
    print actionList
   
    return actionList


    #util.raiseNotDefined()
    '''
    return DFS(problem,problem.getStartState(),[])

qu=util.Queue()
lis=[]   
def getPath(problem,node):
   

    actions = []
    #print qu.list
   
    while node["direction"] != None:
      #print node
      actions.append(node["direction"])
      for n in lis:
      
        if n['state']==node['parent']:
          node = n
          break

    return actions[::-1] 


    
def breadthFirstSearch(problem):
    """Search the shallowest nodes in the search tree first."""
    "*** YOUR CODE HERE ***"
    visited=[]
    
    node=dict()
    start=problem.getStartState()
    node['parent']=None
    node['direction']=None
    node['state']=start
    
    
    qu.push(node)
    lis.append(node)
    
    print qu.list
    while qu.isEmpty()!=True:
         node=qu.pop()
         pos=node['state']
         visited.append(pos)
         print visited
         if problem.isGoalState(pos):
           print "found"
           return getPath(problem,node)
           #break
         suc=problem.getSuccessors(pos)
         if suc ==None:
           continue  
            
         print suc
         for step in suc:
            #if step not in dic :
              if step[0] not in visited:
                childnode={}
                childnode['parent']=pos
                childnode['direction']=step[1]
                childnode['state']=step[0]
                qu.push(childnode)
                lis.append(childnode)
    

    #util.raiseNotDefined()

def uniformCostSearch(problem):
    """Search the node of least total cost first."""
    "*** YOUR CODE HERE ***"
    q_p=util.PriorityQueue()
    #nodes=[]
    visited=[]
    
    node=dict()
    start=problem.getStartState()
    node['parent']=None
    node['direction']=None
    node['state']=start
    node['cost']=0
    
    q_p.push(node,node['cost'])
    lis.append(node)
   
    while q_p.isEmpty()!=True:
          node=q_p.pop()
          print node
          state=node['state']
          visited.append(state)
          #lis.append(node)
          if problem.isGoalState(state):
              print "found"
              return getPath(problem,node)
                       
          suc=problem.getSuccessors(state)
          if suc ==None:
            continue  
          for child in suc:
             if child[0] not in visited:
                childnode={}
                childnode['parent']=state
                childnode['direction']=child[1]
                childnode['state']=child[0]
                childnode['cost']=node['cost']+1
                q_p.push(childnode,childnode['cost'])
                lis.append(childnode)
            

   




   

     
    
    #util.raiseNotDefined()

def nullHeuristic(state, problem=None):
    """
    A heuristic function estimates the cost from the current state to the nearest
    goal in the provided SearchProblem.  This heuristic is trivial.
    """
    return 0

def aStarSearch(problem, heuristic=nullHeuristic):
    """Search the node that has the lowest combined cost and heuristic first."""
    "*** YOUR CODE HERE ***"
    util.raiseNotDefined()


# Abbreviations
bfs = breadthFirstSearch
dfs = depthFirstSearch
astar = aStarSearch
ucs = uniformCostSearch
