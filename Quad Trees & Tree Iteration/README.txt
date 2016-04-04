HOMEWORK 8: QUAD TREES AND TREE ITERATION


NAME:  < XU CHAI >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< insert collaborators / resources >

TA: Sidd Tom Salles

LMS:Matthew Cordone ,Shanny Lin ,Shanjeetha Kirupananthan 

Collaborators: Hao Chen, Wen Cai

Websites:
1.http://www.cs.rpi.edu/academics/courses/spring15/csci1200/calendar.php
2.http://stackoverflow.com/questions/tagged/c%2B%2B
3.http://www.cplusplus.com


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 12 >



ORDER NOTATION ANALYSIS: 
Give the big O notation of each of the QuadTree operations and justify
your answer for the non trivial operations (please be concise!)
Analyze both the running time and the additional memory usage needed
(beyond the space allocated for the existing tree structure).  You may
assume that the tree is reasonably well balanced for all operations.


n = the number of elements in the tree


size()
  running time:O(1)
  memory usage:O(1)
 

insert()
  running time:O(log(n))  base 4
  memory usage:O(1)
  insert finds the quandrant that can properly put the input Node
  so the runtime is O(log4(n))
  and memory usage is O(1) for storing the new node

find()
  running time:O(log(n))  base 4
  memory usage:O(1)
  find has a similar algorith with insert, which also takes O(log(n))
  for runtime, but O(1) for storing the local iterator within the function

height()
  running time: O(n)
  memory usage: O(log(n))
  height goes into all four quandrant of the root node in the tree 
  and returns the max height, the sub-tree with max height requires 
  one memory to store the height so the memory usage is O(log(n))

begin()
  running time:O(1)
  memory usage:O(1)
  return one variable

end()
  running time: O(1)
  memory usage: O(1)
  return one variable

bf_begin()
  running time:O(1)
  memory usage:O(1)
  return one variable

bf_end()
  running time:O(1)
  memory usage:O(1)
  return one variable

operator++()  for depth first
  running time:O(log n)
  memory usage:O(1)
  the worse case scenerio for depth++ is when we are at the right-most leaf
  of the left sub-tree, which we need to go up too root. This takes log(n) 
  run time( same for quadtree but with a base of 4). 
  But we onlt need O(1) for storing the returning iterator

operator++()  for breadth first
  running time:O(log n)
  memory usage:O(n)
  the worse case for breadth++ if when we are at the middle of the bottom level,
  then we have to go up to the root and traverse back down to collect all nodes
  in the bottom level. By doing so, we need maximum of O(n) memory to store all
  nodes in the bottom level


operator*()
  running time:O(1)
  memory usage:O(1)
  return one variable

getLabel()
  running time:O(1)
  memory usage:O(1)
  return one variable

getDepth()
  running time:O(log(n))
  memory usage:O(log(n))
  getDepth only goes back to the root node with O(log(n)) for running time
  and one memory for each level, so O(log(n)) memory usage

copy constructor
  running time:O(n)
  memory usage:O(n)
 visit all nodes in the tree, so run time and memory usage are all O(n)

assignment operator
  running time:O(n)
  memory usage:O(n)
 visit all nodes in the tree, so run time and memory usage are all O(n)

destructor
  running time:O(n)
  memory usage:O(n)
 visit all nodes in the tree, so run time and memory usage are all O(n)



EXTRA CREDIT:  TREE BALANCING
How does the point insertion order affect the shape of the resulting
QuadTree object? What are specific examples of the worst case and best
case?  Discuss your stratgy for reordering the input to rebalance the
tree.  Paste example output with and without your rebalancing.






MISC. COMMENTS TO GRADER:  
(optional, please be concise!)


