# 8-puzzle-game
 Implemented 8-Puzzle using C++ using the following search algorithms: 
  
    a. Depth first with iterative deepening. Depth bound would be provided by the user.
          Initial and goal state of the grid is hard coded. User is asked to enter the ‘depth bound’. 
          Program calls the DFID function starting from 0 till this depth bound. 
          In the recursive DFID function, if the array passed to the function is the goal state itself, then the function returns SUCCESS.
          And if the array is not a goal state, then it checks the depth bound. 
          If the depth bound value in the function is equal to zero, then the function returns FAILURE,
          otherwise it calls the function recursively with the up, down, left and right possibilities of the array respectively
          and depth bound = depth bound -1.
          User is shown the hard coded initial and goal state at the start of the program. 
          Then user is asked a depth bound after which the program starts to search for the goal state from the initial state, 
          staying in the depth bound provided.
          If the goal state is found, the program outputs the moves that are to be taken while going from initial to goal state
          in the given depth bound. 
          And it also outputs the depth at which goal state is found. i.e., the minimum number of moves to complete the 8-puzzle game.
          The program outputs an error message saying that the goal state wasn’t found in the provided depth bound, 
          if there exists no path from initial state to the goal state in the given depth bound.
           
    b. Best first search. Using at least two different admissible heuristics.
          Initial and goal state of the grid is hard coded. 
          User is asked which heuristic he want to choose for solving the 8-puzzle game. 
          Both the heuristics are admissible but h2 (n) < h1 (n). Program calls the BFS function. 
          In the function, if the node passed to the function is the goal node itself, then the function returns SUCCESS. 
          And if the node is not a goal node, then the function inserts the up, down, left and right successors of the node to the Queue.
          It then sorts the Queue.
          If the start node of the Queue is the initial state itself then it returns FAILURE, 
          as no path goes to goal node and by not doing this it will go into a loop. 
          The function returns FAILURE also when the Queue is empty, i.e., there is no path available to reach to goal state. 
          If the function doesn’t returns FAILURE or SUCCESS, then it copies the first node of the Queue to the start state, 
          for iteration from this state and also removes that node from Queue.
          User is asked about what heuristic to choose from, at the start of the program. 
          Once chosen, the user is shown the hard coded initial and goal state at the start of the program. 
          If the goal state is found, the program returns SUCCESS and outputs the depth at which goal state is found. 
          i.e., the minimum number of moves to complete the 8-puzzle game.
          The program returns FAILURE and outputs an error message saying that the goal state wasn’t found, 
          if there exists no path from initial state to the goal state in the given depth bound. 
