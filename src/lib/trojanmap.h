#ifndef TROJAN_MAP_H
#define TROJAN_MAP_H
#define DOT_SIZE 5
#define LINE_WIDTH 3

#include <iostream>
#include <map>
#include <vector>
#include <unordered_map>
#include <unordered_set>
// A Node is the location of one point in the map.
class Node {
  public:
    Node(){};
    Node(const Node &n){id = n.id; lat = n.lat; lon = n.lon; name = n.name; neighbors = n.neighbors;};
    std::string id;    // A unique id assign to each point
    double lat;        // Latitude
    double lon;        // Longitude
    std::string name;  // Name of the location. E.g. "Bank of America".
    std::vector<std::string> neighbors;  // List of the ids of all neighbor points.
};
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

class TrojanMap {
 public:
  // A map of ids to Nodes.
  std::unordered_map<std::string, Node> data;
  std::unordered_map<std::string, std::string> name2id;
  //std::unordered_map<std::string,std::map<std::string,Edge>> graph;
  
  //-----------------------------------------------------
  // TODO: You do not and should not change the following functions:

  // Create the menu.
  void PrintMenu();

  // Create the Dynamic menu.
  // void DynamicPrintMenu();

  // Read in the data
  void CreateGraphFromCSVFile();

  // Visualization
  // Given a location id, plot the point on the map.
  void PlotPoint(std::string id);

  // Given a lat and lon, plot the point on the map.
  void PlotPoint(double lat, double lon);

  // Given a vector of location ids draws the path (connects the points)
  void PlotPath(std::vector<std::string> &location_ids);

  // Given a vector of location ids draws the points on the map (no path).
  void PlotPoints(std::vector<std::string> &location_ids);

  // Given a vector of location ids draws the points on the map with path.
  void PlotPointsandEdges(std::vector<std::string> &location_ids, std::vector<double> &square);

  // Given a vector of location ids draws the points with their order on the map (no path).
  void PlotPointsOrder(std::vector<std::string> &location_ids);

  // Given a vector of location ids and origin, draws the points with their label.
  void PlotPointsLabel(std::vector<std::string> &location_ids, std::string origin);

  // Create the videos of the progress to get the path
  // void CreateAnimation(std::vector<std::vector<std::string>>);
  void CreateAnimation(std::vector<std::vector<std::string>> &path_progress, std::string filename);

  // Transform the location to the position on the map
  std::pair<double, double> GetPlotLocation(double lat, double lon);
  //-----------------------------------------------------
  // TODO: Implement these functions and create unit tests for them:

  // Get the Latitude of a Node given its id.
  double GetLat(std::string id);

  // Get the Longitude of a Node given its id.
  double GetLon(std::string id);

  // Get the name of a Node given its id.
  std::string GetName(std::string id);

  // Get the id given its name.
  std::string GetID(std::string name);

  // Get the neighbor ids of a Node.
  std::vector<std::string> GetNeighborIDs(std::string id);

  // Get the distance between 2 nodes.
  double CalculateDistance(const std::string &a, const std::string &b);

  // Calculates the total path length for the locations inside the vector.
  double CalculatePathLength(const std::vector<std::string> &path);

  // Returns a vector of names given a partial name.
  bool match(std::string str, std::string target);
  std::vector<std::string> Autocomplete(std::string name);

  // Returns lat and long of the given the name.
  std::pair<double, double> GetPosition(std::string name);

  //Given the name of one locaion, find the grapgh, and judge if location2 is in the graph
  void FindGraph_helper(std::string temp,std::map<std::string,int>&nodestore);
  //void FindGraph(std::string temp,std::string temp2,std::map<std::string,int>&nodestore,std::map<std::string,std::vector<std::string>>&graph);
  void FindGraph(std::string temp,std::string temp2,std::map<std::string,int>&nodestore,std::map<std::string,Node>&graph);
  int FindMinIndButNotVisited(std::vector<long>d,std::unordered_set<int>visited);
  // Given the name of two locations, it should return the **ids** of the nodes
  // on the shortest path.
  //static bool Smaller(Edge&a,Edge&b);
  std::vector<std::string> CalculateShortestPath_Dijkstra(std::string location1_name,
                                                 std::string location2_name);
  std::vector<std::string> CalculateShortestPath_Bellman_Ford(std::string location1_name,
                                                 std::string location2_name);
  std::vector<std::string> CalculateShortestPath_Bellman_Ford_no_dfs(
                std::string location1_name, std::string location2_name);
  void Bellman_dfs(std::string u,std::unordered_map<std::string,bool>&visited,
              std::unordered_map<std::string,std::unordered_map<std::string,double>>&mp);
  std::unordered_map<std::string,std::vector<std::string>> Getpredecessor(std::string u,
               std::unordered_map<std::string,std::unordered_map<std::string,double>>mp);
  double Bellman_helper(std::string s,int i,std::string v,
    std::unordered_map<std::string,std::unordered_map<std::string,double>>mp,
    std::vector<std::string>&path);
  void Bellman_bfs(std::string loca,std::string locb,
    std::unordered_map<std::string,std::unordered_map<std::string,double>>&mp);
  //void Bellman_Matrix(std::unordered_map<std::string,std::unordered_map<std::string,double>>&mp,
                              //  std::vector<std::string>node,std::map<std::string,int>&node2index,
                              //  std::map<int,std::string>&index2node);
  // Given CSV filename, it read and parse locations data from CSV file,
  // and return locations vector for topological sort problem.
  std::vector<std::string> ReadLocationsFromCSVFile(std::string locations_filename);
  
  // Given CSV filenames, it read and parse dependencise data from CSV file,
  // and return dependencies vector for topological sort problem.
  std::vector<std::vector<std::string>> ReadDependenciesFromCSVFile(std::string dependencies_filename);

  // Given a vector of location names, it should return a sorting of nodes
  // that satisfies the given dependencies.
  bool TopoSort(std::unordered_map<int, std::vector<int>> &DAG, std::vector<bool> &visit, std::vector<bool> &being_visited, int cur, std::vector<int> &topo_list);

  std::vector<std::string> DeliveringTrojan(std::vector<std::string> &location_names,
                                            std::vector<std::vector<std::string>> &dependencies);

  // Given a vector of location ids, it should reorder them such that the path
  // that covers all these points has the minimum length.
  // The return value is a pair where the first member is the total_path,
  // and the second member is the reordered vector of points.
  // (Notice that we don't find the optimal answer. You can return an estimated
  // path.)
  std::vector<std::vector<double>> CreateAdjMatrix(std::vector<std::string> &location_ids);
  void Backtracking(const std::vector<std::vector<double>> &adjacent_matrix, std::vector<std::vector<std::string>> &paths, std::vector<std::string> &path, std::vector<bool> &visit, double &mincost, double cost, int current, const std::vector<std::string> &location_ids, int &count);
  std::pair<double, std::vector<std::vector<std::string>>> TravellingTrojan(std::vector<std::string> &location_ids);
  
  void Brute_Force(const std::vector<std::vector<double>> &adjacent_matrix, std::vector<std::vector<std::string>> &paths, std::vector<std::string> &path, std::vector<bool> &visit, double &mincost, double cost, int current, const std::vector<std::string> &location_ids, int &count);
  std::pair<double, std::vector<std::vector<std::string>>> TravellingTrojan_Brute_force(
      std::vector<std::string> &location_ids);
  double CalculatePathDis(const std::vector<std::vector<double>> &adjacent_matrix, std::unordered_map<std::string, int> &id2index, std::vector<std::string> &path);
  
  void TPS_2opt(const std::vector<std::vector<double>> &adjacent_matrix, 
              double &mincost, std::vector<std::vector<std::string>> &paths, 
              std::vector<std::string> &path_start, std::unordered_map<std::string, int> &id2index);
  std::pair<double, std::vector<std::vector<std::string>>> TravellingTrojan_2opt(std::vector<std::string> &location_ids);

  void TPS_3opt(const std::vector<std::vector<double>> &adjacent_matrix, 
                        double &mincost, std::vector<std::vector<std::string>> &paths, 
                        std::vector<std::string> &path_start, std::unordered_map<std::string, int> &id2index);
  std::pair<double, std::vector<std::vector<std::string>>> TravellingTrojan_3opt(std::vector<std::string> &location_ids);

  // Given a subgraph specified by a square-shape area, determine whether there is a
  // cycle or not in this subgraph.
  // vector square has 4 elements: left/right/top/bottom bound in order.
  bool CycleDetection(std::vector<double> &square);
  //bool IsCyclicUtil(std::string u,std::map<std::string,int>&visited,std::string parent);
  bool IsCyclicUtil(std::string node,std::map<std::string,bool>&isvisited,
     std::string parent,std::unordered_map<std::string,std::vector<std::string>> adj,std::vector<std::string>&store_node);
  // Given a location id and k, find the k closest points on the map
  std::vector<std::string> FindKClosestPoints(std::string name, int k);
  void FindNodes_DFS(std::string u,std::unordered_map<std::string,bool>&visited,
                            std::vector<std::string>&res);
  std::vector<std::vector<double>> CreateMatrix(std::vector<std::string> &location_ids);
  void BackTracking_helper(int start,std::vector<std::vector<double>> weights,
              int cur_node,double cur_cost,std::vector<int>&cur_path,double &min_cost,
              std::vector<int>&min_path,int k);
  //----------------------------------------------------- User-defined functions
  void TSP_aux(const std::vector<std::vector<double>> &adj_matrix, int cur_node,
  double cur_cost,double &min_cost,std::vector<std::string>&path,std::vector<std::vector<std::string>>&paths,std::vector<std::string> &location_ids);
};

#endif