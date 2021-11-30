# EE538 Final Project - Fall 2021 - TrojanMap

## Deadline: 

Video Presentation: Friday, December 3 by 2 pm

Code submission: Monday, December 5 by 23:59 pm

## Task List
| Task Name | Functions | Tests |
| :--- | :---: | :---: |
| 1. `Autocomplete` | Done :white_check_mark: | Done :white_check_mark: | 
| 2. `GetPosition` | Done :white_check_mark: | Done :white_check_mark: | 
| 3.1 `CalculateShortestPath_Dijkstra` | Done :white_check_mark: | Done :white_check_mark: | 
| 3.2 `CalculateShortestPath_Bellman_Ford` | Done :white_check_mark: | Done :white_check_mark: | 
| 4.1 `TravellingTrojan` | Done :white_check_mark: | Done :white_check_mark: | 
| 4.2 `TravellingTrojan_2opt` | Done :white_check_mark: | Done :white_check_mark: | 
| 5. `CycleDetection` | Done :white_check_mark: | Done :white_check_mark: | 
| 6. `DeliveringTrojan` | Done :white_check_mark: | Done :white_check_mark: | 
| 7. `FindKClosestPoints` | Done :white_check_mark: | Done :white_check_mark: | 
| 8. `Video presentation and report` | To Be Done :golf: | To Be Added :heavy_exclamation_mark: | 
| 8. `Extra credit items(3-opt)` | Done :white_check_mark: | Done :white_check_mark: | 


## TrojanMap

This project focuses on using data structures in C++ and implementing various graph algorithms to build a map application.

<p align="center"><img src="img/TrojanMap.png" alt="Trojan" width="500" /></p>

- Please clone the repository, look through [README.md](README.md) and fill up functions to finish in the project.
- Please make sure that your code can run `bazel run/test`.
- In this project, you will need to fill up [trojanmap.cc](src/lib/trojanmap.cc) and add unit tests in the `tests` directory.

---

## The data Structure

Each point on the map is represented by the class **Node** shown below and defined in [trojanmap.h](src/lib/trojanmap.h).

```cpp
class Node {
  public:
    std::string id;    // A unique id assign to each point
    double lat;        // Latitude
    double lon;        // Longitude
    std::string name;  // Name of the location. E.g. "Bank of America".
    std::vector<std::string>
        neighbors;  // List of the ids of all neighbor points.
};

```
Establish a new data structure class **DJNode** shown below and defined in [trojanmap.h]
DJNode have two member variables, the first is the id of the node, the second is a ``double`` type dist.
DJNode will be used by **CalculateShortestPath_Dijkstra** to calculate the shortest path and 
**FindKClosestPoints** to find the find the Kth closest points.
```cpp
class DJNode{
  public:
  std::string id;
  double dist;
  DJNode(){};
  DJNode(const DJNode &n):id(n.id), dist(n.dist){}
  DJNode(std::string id, double dist=std::numeric_limits<double>::max()): id(id),dist(dist){}
  DJNode &operator=(const DJNode&n){
    if(this==&n) return *this;
    this->id=n.id;
    this->dist=n.dist;
    return *this;
  }
};
```

An example of the DJNodes applied in **CalculateShortestPath_Dijkstra**
<p align="center"><img src="report/3_heap.png" alt="3_heap" width="500" /></p>

Given node's id, all the information of node could be obtained through **data**; In order to find the id of the node, using **name2id**.
```cpp
  std::unordered_map<std::string, Node> data;
  std::unordered_map<std::string, std::string> name2id;
```

---

## Step 1: Autocomplete the location name

```c++
bool match(std::string str, std::string target); // check if str and target have the same prefix, regardless of whether the letters are uppercase or lowercase
std::vector<std::string> Autocomplete(std::string name); // first discard all the locations whose size is less than name, then do the match() for them
```

We consider the names of nodes as the locations. Implement a method to type the partial name of the location and return a list of possible locations with partial name as prefix. Please treat uppercase and lower case as the same character.

<p align="center"><img src="report/1_1.png" alt="1_1" width="500"/></p>
<p align="center"><img src="report/1_2.png" alt="1_2" width="500"/></p>
<p align="center"><img src="report/1_3.png" alt="1_3" width="500"/></p>

### Time complexity: 
1. Let n be the length of name, m be the number of all locations, ```match``` need to check every character in target(name), so it is O(n), and we need to apply ```match``` to every locations, so the totally time complexity is O(n*m).  
2. The longer the name, the less locatins need to be chech in ```match``` , the shorter the time it takes, like the last case.

## Step 2: Find the place's Coordinates in the Map

```c++
std::pair<double, double> GetPosition(std::string name);
std::string TrojanMap::GetID(std::string name);
```

Given a location name, in order to find the information of the node, find the id of the node first by using function `std::string TrojanMap::GetID(std::string name)`, then all the information of the node could be knew through ``std::unordered_map<std::string, Node> data`` Return the latitude and longitude. If could not find ID, return (-1, -1).


<p align="center"><img src="report/2_1.png" alt="2_1" width="500"/></p>
<p align="center"><img src="report/2_2.png" alt="2_2" width="500"/></p>
<p align="center"><img src="report/2_3.png" alt="2_3" width="500"/></p>
<p align="center"><img src="report/2_4.png" alt="2_4" width="500"/></p>
<p align="center"><img src="report/2_5.png" alt="2_5" width="500"/></p>
<p align="center"><img src="report/2_6.png" alt="2_6" width="500"/></p>

## Step 3: CalculateShortestPath between two places

```c++
std::vector<std::string> CalculateShortestPath_Dijkstra(std::string &location1_name,
                                               std::string &location2_name);
std::vector<std::string> CalculateShortestPath_Bellman_Ford(std::string &location1_name,
                                               std::string &location2_name);
void Bellman_dfs(std::string u,std::unordered_map<std::string,bool>&visited,
                 std::unordered_map<std::string,std::unordered_map<std::string,double>>&mp);
```

Given 2 locations A and B, find the best route from A to B.(A is src location and B is dst location) The distance between 2 points is the euclidean distance using latitude and longitude. Use both Dijkstra algorithm and Bellman-Ford algorithm. Compare the time for the different methods. Show the routes on the map. If there is no path, please return empty vector.


### Parameters List1 (CalculateShortestPath_Dijkstra)
| Parameter Name | Meaning |
| :--- | :--- |
| `std::vector<std::string> path` | Store the final shortest path|
| `std::unordered_map<std::string,double> dist` | key: node ; val: the shortest distance from the node to the src |
| `std::unordered_map<std::string,std::string>prev` | key: the node ; val is the prev node |
| `std::unordered_set<std::string> visited;` | store the shortest distance node in visited |
| `std::priority_queue<DJNode,std::vector<DJNode>, decltype(compare)> dist_heap(compare)` | using a heap to sort the node in the graph |

### Parameters List2 (CalculateShortestPath_Bellman_Ford)
| Parameter Name | Meaning |
| :--- | :--- |
| `std::vector<std::string> path` | Store the final shortest path|
| ` std::unordered_map<std::string,bool> visited` | store the node visited in DFS|
| `std::unordered_map<std::string,std::unordered_map<std::string,double>>mp` | use DFS iterate the graph, store the relationship of nodes in the graph |
| `std::unordered_map<std::string,double> distance` | key: node ; val: the shortest distance from the node to the src |
| `std::unordered_map<std::string,std::string>prev` | key: the node ; val is the prev node |

<p align="center"><img src="report/3_Bellman_mp.png" alt="3_Bellman_mp" width="500"/></p>

### Runtime Comparison
| NO. | Src Loc | Dst Loc | Dist(miles) | DJ-runtime(usec)| BF-runtime(usec) |
| :--- | :--- | :--- | :--- | :--- | :--- |
| 0 | 7Eleven |  Popeyes Louisiana Kitchen| 0.107757 | 489 | 15,032,881 |
| 1 | Tap Two Blue | 7Eleven | 0.259747 | 994 | 14,186068 |
| 2 | CVS | Target | 0.351751 | 1,844 | 14,708,495 |
| 3 | 7Eleven | CVS | 0.463025 | 4,338 | 13,974,720 |
| 4 | Tap Two Blue | CVS | 0.684286 | 4,782 | 14,463,257 |
| 5 | 7Eleven | Target | 0.788389 | 7,976 | 15,537,051 |
| 6 | Target | Ralphs | 0.839235 | 21,308 | 14,822,822 |
| 7 | Ralphs | CVS | 1.14497 | 9,330 | 14,655,557 |
| 8 | Ralphs | 7Eleven | 1.3303 | 14,042 | 15,988,243 |
| 9 | Metro 40 | Driveway | 1.77417 | 54,777 | 15,715,079 |

From the table above, we could found that the speed of Dijkstra is exceeded Bellman Ford to great extent. That is because Bellman ford need to iterate each node in the data using DFS to find the graph. However, Dijstra doesn't need to do that. Dijstra using priority_queue to find the shortest distance, it only need to sort the relevant node.

### Time Complxity
CalculateShortestPath_Dijkstra: O(m+nlogn)

CalculateShortestPath_Bellman_Ford: O(m*n)

### Sample Sreenshot
<p align="center"><img src="report/3_1.png" alt="3_1" width="500"/></p>
<p align="center"><img src="report/3_2.png" alt="3_2" width="500"/></p>
<p align="center"><img src="report/3_3.png" alt="3_3" width="500"/></p>
<p align="center"><img src="report/3_4.png" alt="3_4" width="500"/></p>
<p align="center"><img src="report/3_5.png" alt="3_5" width="500"/></p>
<p align="center"><img src="report/3_6.png" alt="3_6" width="500"/></p>

## Step 4: The Traveling Trojan Problem (AKA Traveling Salesman!)

In this section, we assume that a complete graph is given to you. That means each node is a neighbor of all other nodes.
Given a vector of location ids, assume every location can reach all other locations in the vector (i.e. assume that the vector of location ids is a complete graph).
Find the shortest route that covers all the locations exactly once and goes back to the start point. 

You will need to return the progress to get the shortest route which will then be converted to an animation.  

We will use the following algorithms:

- Backtracking
```c++
std::vector<std::vector<double>> CreateAdjMatrix(std::vector<std::string> &location_ids); // create the weights matrix for all locations
void Backtracking(...); // do the backtracking to get the optimal result, and every time getting a shorter path, push it in paths, the detailed parameters are shown in the following diagram
std::pair<double, std::vector<std::vector<std::string>>> TravellingTrojan(std::vector<std::string> &location_ids);
```
### Parameters List ("shorter" in the diagram means less cost)
| Parameter Name | Meaning |
| :--- | :--- |
| `const std::vector<std::vector<double>> &adjacent_matrix` | Store the distance weight between all points |
| `std::vector<std::vector<std::string>> &paths` | Store every shorter path |
| `std::vector<std::string> &path` | Store current path |
| `std::vector<bool> &visit` | Check if a location is visited |
| `double &mincost` | Store the cost of the shortest path |
| `double cost` | Store the cost of current path |
| `int current` | Store the index of current location |
| `const std::vector<std::string> &location_ids` | The input vector to map location's index to its id |
| `std::unordered_map<std::string, int> &id2index` | A unordered_map to map location's id to its index |

- [2-opt Heuristic](https://en.wikipedia.org/wiki/2-opt). Also see [this paper](http://cs.indstate.edu/~zeeshan/aman.pdf)
- 3-opt
```c++
// Calculate the distance for each adjusted path
double CalculatePathDis(const std::vector<std::vector<double>> &adjacent_matrix, std::unordered_map<std::string, int> &id2index, std::vector<std::string> &path);
// 1. Starting from the default path,;
// 2. iterate to choose two points to reverse the path;
// 3. if the reversed path is shorter, improve = true, repeat step 2, start a new iteration;
// 4. if not, continue to iterate;
// 5. if there is no improvement during the whole iteration, return the result.
std::pair<double, std::vector<std::vector<std::string>>> TravellingTrojan_2opt(std::vector<std::string> &location_ids); 
void TrojanMap::TPS_2opt(const std::vector<std::vector<double>> &adjacent_matrix, 
                        double &mincost, std::vector<std::vector<std::string>> &paths, 
                        std::vector<std::string> &path_start, std::unordered_map<std::string, int> &id2index);
// Similar to 2-opt, but in 3-opt, you need to choose 3 points, and have 7 way to change the path, and 3 of them are the same as 2-opt, so apply the left 4 ways in 3-opt
std::pair<double, std::vector<std::vector<std::string>>> TrojanMap::TravellingTrojan_3opt(std::vector<std::string> &location_ids);
void TrojanMap::TPS_3opt(const std::vector<std::vector<double>> &adjacent_matrix, 
                        double &mincost, std::vector<std::vector<std::string>> &paths, 
                        std::vector<std::string> &path_start, std::unordered_map<std::string, int> &id2index);
// key of 3-opt:
  // a = [end, start - 1], b = [start, mid - 1], c = [mid, end - 1]
  // a' means reverse a, especially reverse a == reverse(b+c) = c'b'
  // 1. ab'c'
  std::reverse(path_copys[0].begin() + start, path_copys[0].begin() + mid);
  std::reverse(path_copys[0].begin() + mid , path_copys[0].begin() + end);
  // 2. a'b'c
  std::reverse(path_copys[1].begin() + start, path_copys[1].begin() + end);
  std::reverse(path_copys[1].begin() + start, path_copys[1].begin() + start + end - mid);
  // 3. a'bc'
  std::reverse(path_copys[2].begin() + start, path_copys[2].begin() + end);
  std::reverse(path_copys[2].begin() + start + end - mid, path_copys[2].begin() + end);
  // 4. a'b'c'
  std::reverse(path_copys[3].begin() + start, path_copys[3].begin() + end);
  std::reverse(path_copys[3].begin() + start, path_copys[3].begin() + start + end - mid);
  std::reverse(path_copys[3].begin() + start + end - mid, path_copys[3].begin() + end);
```
<p align="center"><img src="report/TSP_3_opt.jpeg" alt="3-opt" width="600"/></p>


Please report and compare the time spent by these 2 algorithms. 2-opt algorithm may not get the optimal solution. Please show how far your solution is from the optimal solution.

Show the routes on the map. For each intermediate solution, create a new plot. Your final video presentation should include the changes to your solution.

We will randomly select N points in the map and run your program.

Case 1: 6 locations
For a few locations, all the 3 methods can find the optimal result in an acceptable time. These two heuristic algorithms have to do some redundant iterators, so in this case they cost more time than Backtracking.
<p align="center"><img src="report/TSP_6.png" alt="Runtime" width="800"/></p>
<p align="center"><img src="report/TSP_6loc.png" alt="Visualization" width="500"/></p>

Case 2: 9 locations
When the locations become more, the time increase of Backtracking is greater than 2-opt and 3-opt, the time cost by Backtracking and 3-opt is silimar.
<p align="center"><img src="report/TSP_9.png" alt="Runtime" width="800"/></p>
<p align="center"><img src="report/TSP_9loc.png" alt="Visualization" width="500"/></p>

Case 3: 12 locations
When the locations become more, 2-opt and 3-opt gradually show their advantages in time consumption. 
<p align="center"><img src="report/TSP_12.png" alt="Runtime" width="800"/></p>
<p align="center"><img src="report/TSP_12loc.png" alt="Visualization" width="500"/></p>

Case 4: 15 locations
At this case, the time cost by backtracking is gradually unacceptable, the two heuristic algorithms can dramatically decrease the time consumption，and can get the same or very close results.
<p align="center"><img src="report/TSP_15.png" alt="Runtime"  width="800"/></p>
<p align="center"><img src="report/TSP_15loc.png" alt="Visualization" width="500"/></p>

| `Backtracking` | `2-opt` | `3-opt` |
| :---: | :---: | :---: |
| <img src="report/TSP_6loc.gif" alt="TSP_6loc videos" width="300"/> | <img src="report/TSP_6loc_2opt.gif" alt="TSP_6loc_2opt videos" width="300"/> | <img src="report/TSP_6loc_3opt.gif" alt="TSP_6loc_3opt videos" width="300"/> |
| <img src="report/TSP_9loc.gif" alt="TSP_9loc videos" width="300"/> | <img src="report/TSP_9loc_2opt.gif" alt="TSP_9loc_2opt videos" width="300"/> | <img src="report/TSP_9loc_3opt.gif" alt="TSP_9loc_3opt videos" width="300"/> |
| <img src="report/TSP_12loc.gif" alt="TSP_12loc videos" width="300"/> | <img src="report/TSP_12loc_2opt.gif" alt="TSP_12loc_2opt videos" width="300"/> | <img src="report/TSP_12loc_3opt.gif" alt="TSP_12loc_3opt videos" width="300"/> |
| <img src="report/TSP_15loc.gif" alt="TSP_15loc videos" width="300"/> | <img src="report/TSP_15loc_2opt.gif" alt="TSP_15loc_2opt videos" width="300"/> | <img src="report/TSP_15loc_3opt.gif" alt="TSP_15loc_3opt videos" width="300"/> |

### Examples (dis: miles, time: microseconds)
| # of the places | dis(Backtracking) | time(Backtracking) | dis(2-opt) | time(2-opt) | dis(3-opt) | time(3-opt) |
| :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| 4 | 2.68747 | 33 | 2.68747 | 59 | 2.68747 | 115 |
| 5 | 3.67029 | 52 | 3.67029 | 133 | 3.67029 | 433 |
| 6 | 4.05083 | 95 | 4.15358 | 380 | 4.05083 | 1363 |
| 6 | 3.23573 | 69 | 3.23573 | 191 | 3.23573 | 710 |
| 6 | 2.95252 | 95 | 2.95399 | 225 | 2.95252 | 1200 |
| 7 | 3.29827 | 299 | 3.29827 | 289 | 3.29827 | 1115 |
| 8 | 3.74217 | 952 | 3.74217 | 414 | 3.74217 | 2455 |
| 9 | 4.3105 | 1891 | 4.3105 | 944 | 4.3105 | 2533 |
| 9 | 4.25536 | 3778 | 4.25536 | 1154 | 4.25536 | 2770 |
| 9 | 4.00037 | 3664 | 4.00037 | 815 | 4.00037 | 3006 |
| 10 | 4.15441 | 4833 | 4.15441 | 1490 | 4.15441 | 4157 |
| 11 | 5.17885 | 68106 | 5.58581 | 1324 | 5.17885 | 9395 |
| 12 | 4.53812 | 102178 | 4.53812 | 3023 | 4.53812 | 10376 |
| 12 | 4.11525 | 48704 | 4.11525 | 2141 | 4.11525 | 5303 |
| 12 | 5.17578 | 161429 | 5.25541 | 1870 | 5.17578 | 6282 |
| 13 | 5.48798 | 1074349 | 6.35786 | 2598 | 5.48798 | 17837 |
| 14 | 4.44515 | 1417832 | 4.48261 | 4129 | 4.44515 | 9714 |
| 15 | 5.0912 | 4605515 | 5.17081 | 3429 | 5.0912 | 16316 |
| 15 | 5.43451 | 10375847 | 5.45486 | 2732 | 5.45486 | 13028 |
| 15 | 5.25523 | 3167399 | 5.25523 | 3717 | 5.25523 | 26053 |
| 15 | 5.16767 | 1624167 | 5.18942 | 3359 | 5.16767 | 14690 |

### Runtime Comparison
1. When the number of locations is larger than 13, the time cost by Backtracking is more than 50 times than 2-opt, while 2-opt/3-opt can have very close or the same results.
2. In addition, from the cases with same number of locations, we can find the early break can decrease dramatically the time in some special cases. 2-opt and 3-opt would not have some very large changes for the same scale cases.

### Time complexity
Let n be the number of the locations. 
1. For the Backtracking, we need to iterate every path, so it is O(n!), while in fact, due to the early break, the time it cost practically would be less than O(n!);
2. Let the K be the number of iterations until the iteration cannot improve the cost, for every iteration, we have O(n^2) ways to choose two locations to reverse the path, so the whole time complexity is (K*n^2).
3. Similarly to 2-opt, for every iteration, we have O(n^3) ways to choose three locations to change the path in 4 pattern, so the whole time complexity is (K*n^3). 


## Step 5: Cycle Detection

```c++
bool CycleDetection(std::vector<double> &square);
//using DFS to find cycle
bool IsCyclicUtil(std::string node,std::map<std::string,bool>&isvisited,
        std::string parent,std::unordered_map<std::string,std::vector<std::string>> adj);
```

In this section, we use a square-shaped subgraph of the original graph by using four coordinates stored in ```std::vector<double> square```, which follows the order of left, right, upper, and lower bounds.
Firstly, we iterate the  ```data``` to find out all the node inside the 
```std::vector<double> square```, and establish a map to store the node and its neighbors
```std::unordered_map<std::string,std::vector<std::string>> adj```
Then using DFS to find is there remains a cycle, call the recursive function ```IsCyclicUtil()```
If there is a cycle return true, and  path will appears on the map. Otherwise return false.

Case1:
<p align="center"><img src="report/5_1.png" alt="5_1" width="500"/></p>
<p align="center"><img src="report/5_2.png" alt="5_2" width="500"/></p>
Case2:
<p align="center"><img src="report/5_3.png" alt="5_3" width="500"/></p>
<p align="center"><img src="report/5_4.png" alt="5_4" width="500"/></p>
Case3:The Full map
<p align="center"><img src="report/5_fullmap.png" alt="5_fullmap" width="500"/></p>
<p align="center"><img src="report/5_fullmap2.png" alt="5_fullmap2" width="500"/></p>
Case4:No cycle
<p align="center"><img src="report/5_no_cycle.png" alt="5_no_cycle" width="500"/></p>
<p align="center"><img src="report/5_no_cycle2.png" alt="5_no_cycle2" width="500"/></p>

### Time complexity: 
Iterate the data O(n), DFS recursive 0(n+m);
Total complexity: O(n);


## Step 6: Topological Sort

```c++
std::vector<std::string> DeliveringTrojan(std::vector<std::string> &location_names,
                                            std::vector<std::vector<std::string>> &dependencies);
```

Tommy Trojan got a part-time job from TrojanEats, for which he needs to pick up and deliver food from local restaurants to various location near the campus. Tommy needs to visit a few different location near the campus with certain order, since there are some constraints. For example, he must first get the food from the restaurant before arriving at the delivery point. 

The TrojanEats app will have some instructions about these constraints. So, Tommy asks you to help him figure out the feasible route!

Here we will give you a vector of location names that Tommy needs to visit, and also some dependencies between those locations.


Case 1: 4 locations
<p align="center"><img src="report/6_1.png" alt="TopoSort_4loc" width="500"/></p>
<p align="center"><img src="report/6_2.png" alt="TopoSort_4loc" width="500"/></p>
Case 2: 7 locations
<p align="center"><img src="report/6_3.png" alt="TopoSort_7loc" width="500"/></p>
<p align="center"><img src="report/6_4.png" alt="TopoSort_7loc" width="500"/></p>
Case 3: 12 locations
<p align="center"><img src="report/6_5.png" alt="TopoSort_12loc" width="500"/></p>
<p align="center"><img src="report/6_6.png" alt="TopoSort_12loc" width="500"/></p>

### Time complexity
Let V be the number of locations, E be the number of dependencies. Because it just is similar to the DFS, and I use a adjencent list(map) to store all the edge, so the time complexity is O(V+E)


## Step 7: Find K closest points

Given a location name and a integer k , find the k closest locations with name on the map and return a vector of string ids. 

We will use the following algorithms:

- Heap Sort
```c++
std::vector<std::string> FindKClosestPoints(std::string name, int k);
```
In this function, we will use the data stureture DJNode again to establish the priority_queue, to
sort the distance from the from to each node in the map.
```c++
  auto compare=[](DJNode a,DJNode b){return a.dist > b.dist;};
  std::priority_queue<DJNode,std::vector<DJNode>,decltype(compare)> dist_heap(compare); 
```
Case1: CVS 5 locations
<p align="center"><img src="report/7_1.png" alt="7_1" width="500"/></p>
<p align="center"><img src="report/7_2.png" alt="7_2" width="500"/></p>
Case2: Lyons Center 12 locations 
<p align="center"><img src="report/7_3.png" alt="7_3" width="500"/></p>
<p align="center"><img src="report/7_4.png" alt="7_4" width="500"/></p>
Case3: HolBox 8 locations
<p align="center"><img src="report/7_5.png" alt="7_5" width="500"/></p>
<p align="center"><img src="report/7_6.png" alt="7_6" width="500"/></p>

### Time complexity:
Firstly, using a for loop to iterate the `data` to calculate the distance between each node and the source O(n);
Then push the node into priority_queue to sort the nodes O(nlogn);
Total O(nlogn);






### Report:

Your README file should include two sections:

1. High-level overview of your design (Use diagrams and pictures for your data structures).
2. Detailed description of each function and its time complexity.
3. Time spent for each function.
4. Discussion, conclusion, and lessons learned.
