PART 1:

1.main & cmake(Jerry Wu)
input: source of airport/routes/airlines pleca od departure/destination
output:minimum distance route and airlines to select
Set the command in the main clearly 

2.readfile & cleanup
Algorithm(Jerry Wu & Yilin Zhang):
Used unordered map to improve the eficiency of seraching data 
Set the part of cleaning data and the part of calculating distance in different classes
Testcase(Jerry Wu & Yilin Zhang):
We used erase to vector in cleanup at first, so each time the test erase a character in the vector, it used erase once and turn out to be slow. 
It took 30s to read the data when testing.
We changed the earse into marking the vector and delete them after the whole process, it speed up to 3s in total.

3.BFS O(n)
Algorithm(Jerry Wu):
Used queue and vistied for BFS.
Can find the path for unweighted graph clearly but can not solve weighted path.
Testcase(Jerry Wu):
Set up a samll graph to test for the shortest unweighted path.
Set up a large graph to test for the shortest unwegihted path.

4.Dijkstra's O(mlogn)
Algorithm(Sherry Chen):
Used priority queue and queue and vistied to solve the shortest weighted and unweighted.
Met the problems of not finding the path and it turned out to be unlimited. 
Solved it by checking for maximum cases.
Testcase(Sherry Chen & Zonghan Yang):
Based on the testcase for BFS, added distance and set up cases for less vertex but more distance.
Passed the testcases of unweighted at first and passed the testcases of weighted after debugged.

5.Delta Stepping O(n+m+dL) O((d^2)L(logn^2))(if parallelizeble)
Algorithm(Yilin Zhang):
Used dalta stepping to find the shortest weighted path.
Used unordered map to store bucket and resize automatically, to avoid unlimited loop caused size(), used a size_t to record bucket size.
Testcase(Yilin Zhang):
Based on the testcase for BFS, added distance and set up cases for less vertex but more distance.
Passed the testcases of unweighted at first and passed the testcases of weighted after debugged.
Used testcase to find unlimited loop (caused by changing of size) solved it by adding new size_t to record.

PART 2:

