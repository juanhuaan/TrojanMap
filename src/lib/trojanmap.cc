#include "trojanmap.h"
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <set>
#include <algorithm>
#include <fstream>
#include <locale>
#include <stack>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <sstream>
#include <string>
#include <utility>
// #include <bits/stdc++.h>
#include <cmath>
#include <iostream>
#include <cctype>
#include <unordered_set>
#include <stack>
#include <chrono>

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"

//-----------------------------------------------------
// TODO (Students): You do not and should not change the following functions:
//-----------------------------------------------------

/**
 * PrintMenu: Create the menu
 * 
 */
void TrojanMap::PrintMenu() {

  std::string menu =
      "**************************************************************\n"
      "* Select the function you want to execute.                    \n"
      "* 1. Autocomplete                                             \n"
      "* 2. Find the position                                        \n"
      "* 3. CalculateShortestPath                                    \n"
      "* 4. Travelling salesman problem                              \n"
      "* 5. Cycle Detection                                          \n"
      "* 6. Topological Sort                                         \n"
      "* 7. Find K Closest Points                                    \n"
      "* 8. Exit                                                     \n"
      "**************************************************************\n";
  std::cout << menu << std::endl;
  std::string input;
  getline(std::cin, input);
  char number = input[0];
  switch (number)
  {
  case '1':
  {
    menu =
        "**************************************************************\n"
        "* 1. Autocomplete                                             \n"
        "**************************************************************\n";
    std::cout << menu << std::endl;
    menu = "Please input a partial location:";
    std::cout << menu;
    getline(std::cin, input);
    auto start = std::chrono::high_resolution_clock::now();
    auto results = Autocomplete(input);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    menu = "*************************Results******************************\n";
    std::cout << menu;
    if (results.size() != 0) {
      for (auto x : results) std::cout << x << std::endl;
    } else {
      std::cout << "No matched locations." << std::endl;
    }
    menu = "**************************************************************\n";
    std::cout << menu;
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl << std::endl;
    PrintMenu();
    break;
  }
  case '2':
  {
    menu =
        "**************************************************************\n"
        "* 2. Find the position                                        \n"
        "**************************************************************\n";
    std::cout << menu << std::endl;
    menu = "Please input a location:";
    std::cout << menu;
    getline(std::cin, input);
    auto start = std::chrono::high_resolution_clock::now();
    auto results = GetPosition(input);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    menu = "*************************Results******************************\n";
    std::cout << menu;
    if (results.first != -1) {
      std::cout << "Latitude: " << results.first
                << " Longitude: " << results.second << std::endl;
      PlotPoint(results.first, results.second);
    } else {
      std::cout << "No matched locations." << std::endl;
    }
    menu = "**************************************************************\n";
    std::cout << menu;
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl << std::endl;
    PrintMenu();
    break;
  }
  case '3':
  {
    menu =
        "**************************************************************\n"
        "* 3. CalculateShortestPath                                    \n"
        "**************************************************************\n";
    std::cout << menu << std::endl;
    menu = "Please input the start location:";
    std::cout << menu;
    std::string input1;
    getline(std::cin, input1);
    menu = "Please input the destination:";
    std::cout << menu;
    std::string input2;
    getline(std::cin, input2);
    auto start = std::chrono::high_resolution_clock::now();
    auto results = CalculateShortestPath_Dijkstra(input1, input2);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    
    auto start2 = std::chrono::high_resolution_clock::now();
    auto results2 = CalculateShortestPath_Bellman_Ford(input1, input2);
    auto stop2 = std::chrono::high_resolution_clock::now();
    auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(stop2 - start2);

    auto start3 = std::chrono::high_resolution_clock::now();
    auto results3 = CalculateShortestPath_Bellman_Ford_no_dfs(input1, input2);
    auto stop3 = std::chrono::high_resolution_clock::now();
    auto duration3 = std::chrono::duration_cast<std::chrono::microseconds>(stop3 - start3);

    
    menu = "*************************Results******************************\n";
    std::cout << menu;
    if (results.size() != 0) {
      for(int i = 0; i < results.size(); ++i){
        std::cout << results[i] << "\t" << results2[i] <<"\t" << results3[i] << std::endl;
      }
      std::cout << "The distance of the path(DJ) is:" << CalculatePathLength(results) << " miles" << std::endl;
      PlotPath(results);
    } else {
      std::cout << "No route from the start point to the destination."
                << std::endl;
    }
    
    if (results2.size() != 0) {
      
      std::cout << "The distance of the path(BF) is:" << CalculatePathLength(results2) << " miles" << std::endl;
    } else {
      std::cout << "No route from the start point to the destination."
                << std::endl;
    }

    if (results3.size() != 0) {
      
      std::cout << "The distance of the path(BF) without_dfs is:" << CalculatePathLength(results3) << " miles" << std::endl;
    } else {
      std::cout << "No route from the start point to the destination."
                << std::endl;
    }
    menu = "**************************************************************\n";
    std::cout << menu;
    std::cout << "Time taken by function Dijkstra: " << duration.count() << " microseconds" << std::endl << std::endl;
    std::cout << "Time taken by function Bellman_Ford: " << duration2.count() << " microseconds" << std::endl << std::endl;
    std::cout << "Time taken by function Bellman_Ford(no_dfs): " << duration3.count() << " microseconds" << std::endl << std::endl;
    PrintMenu();
    break;
  }
  case '4':
  {
    menu =
        "**************************************************************\n"
        "* 4. Traveling salesman problem                              \n"
        "**************************************************************\n";
    std::cout << menu << std::endl;
    menu = "In this task, we will select N random points on the map and you need to find the path to travel these points and back to the start point.";
    std::cout << menu << std::endl << std::endl;
    menu = "Please input the number of the places:";
    std::cout << menu;
    getline(std::cin, input);
    int num = std::stoi(input);
    std::vector<std::string> keys;
    for (auto x : data) {
      keys.push_back(x.first);
    }
    std::vector<std::string> locations;
    srand(time(NULL));
    for (int i = 0; i < num; i++)
      locations.push_back(keys[rand() % keys.size()]);
    PlotPoints(locations);
    
    std::cout << "Calculating (using Brute_Force)..." << std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    //auto results_bf = TravellingTrojan_Brute_force(locations);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration_bf = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::cout << "Calculating (using Backtracking)..." << std::endl;
    start = std::chrono::high_resolution_clock::now();
    auto results = TravellingTrojan(locations);
    stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::cout << "Calculating (using 2-opt)..." << std::endl;
    start = std::chrono::high_resolution_clock::now();
    auto results_2opt = TravellingTrojan_2opt(locations);
    stop = std::chrono::high_resolution_clock::now();
    auto duration_2opt = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::cout << "Calculating (using 3-opt)..." << std::endl;
    start = std::chrono::high_resolution_clock::now();
    auto results_3opt = TravellingTrojan_3opt(locations);
    stop = std::chrono::high_resolution_clock::now();
    auto duration_3opt = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    //CreateAnimation(results_bf.second, "output0");
    CreateAnimation(results.second, "TSP_output_001");
    CreateAnimation(results_2opt.second, "TSP_output_002");
    CreateAnimation(results_3opt.second, "TSP_output_003");

    menu = "*************************Results******************************\n";
    std::cout << menu;
    if (results.second.size() != 0) {
      for (auto x : results.second[results.second.size()-1]) std::cout << x << std::endl;
      menu = "**************************************************************\n";
      std::cout << menu;
      //std::cout << "The distance of the path is(Brute Force):" << results_bf.first << " miles" << std::endl;
      std::cout << "The distance of the path is:" << results.first << " miles" << std::endl;
      std::cout << "The distance of the path is(2-opt):" << results_2opt.first << " miles" << std::endl;
      std::cout << "The distance of the path is(3-opt):" << results_3opt.first << " miles" << std::endl;
      PlotPath(results.second[results.second.size()-1]);
     

    } else {
      std::cout << "The size of the path is 0" << std::endl;
    }
    menu = "**************************************************************\n"
           "You could find your animation at src/lib/output.avi.          \n";
    std::cout << menu;
    std::cout << "Time taken by function(Brute Force): " << duration_bf.count() << " microseconds" << std::endl << std::endl;
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl << std::endl;
    std::cout << "Time taken by function(2-opt): " << duration_2opt.count() << " microseconds" << std::endl << std::endl;
    std::cout << "Time taken by function(3-opt): " << duration_3opt.count() << " microseconds" << std::endl << std::endl;
    PrintMenu();
    break;
  }
  case '5':
  {
    menu =
        "**************************************************************\n"
        "* 5. Cycle Detection                                          \n"
        "**************************************************************\n";
    std::cout << menu << std::endl;
    menu = "Please input the left bound longitude(between -118.299 and -118.264):";
    std::cout << menu;
    getline(std::cin, input);
    std::vector<double> square;
    square.push_back(atof(input.c_str()));

    menu = "Please input the right bound longitude(between -118.299 and -118.264):";
    std::cout << menu;
    getline(std::cin, input);
    square.push_back(atof(input.c_str()));

    menu = "Please input the upper bound latitude(between 34.011 and 34.032):";
    std::cout << menu;
    getline(std::cin, input);
    square.push_back(atof(input.c_str()));

    menu = "Please input the lower bound latitude(between 34.011 and 34.032):";
    std::cout << menu;
    getline(std::cin, input);
    square.push_back(atof(input.c_str()));

    auto start = std::chrono::high_resolution_clock::now();
    auto results = CycleDetection(square);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    menu = "*************************Results******************************\n";
    std::cout << menu;
    if (results == true)
      std::cout << "there exists cycle in the subgraph " << std::endl;
    else
      std::cout << "there exist no cycle in the subgraph " << std::endl;
    menu = "**************************************************************\n";
    std::cout << menu;
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl << std::endl;
    PrintMenu();
    break;
  }
  case '6':
  {
    menu =
        "**************************************************************\n"
        "* 6. Topological Sort                                         \n"
        "**************************************************************\n";
    std::cout << menu << std::endl;
    menu = "Please input the locations filename:";
    std::cout << menu;
    std::string locations_filename;
    getline(std::cin, locations_filename);
    menu = "Please input the dependencies filename:";
    std::cout << menu;
    std::string dependencies_filename;
    getline(std::cin, dependencies_filename);
    
    // Read location names from CSV file
    std::vector<std::string> location_names;
    if (locations_filename == "") 
      location_names = {"Cardinal Gardens", "Coffee Bean1","CVS"};
    else
      location_names = ReadLocationsFromCSVFile(locations_filename);
    
    // Read dependencies from CSV file
    std::vector<std::vector<std::string>> dependencies;
    if (dependencies_filename == "")
      dependencies = {{"Coffee Bean1","Cardinal Gardens"}, {"CVS","Cardinal Gardens"}, {"CVS","Coffee Bean1"}};
    else
      dependencies = ReadDependenciesFromCSVFile(dependencies_filename);

    // std::vector<std::string> location_names = {"Cardinal Gardens", "Coffee Bean1","CVS"};
    // std::vector<std::vector<std::string>> dependencies = {{"Coffee Bean1","Cardinal Gardens"}, {"CVS","Cardinal Gardens"}, {"CVS","Coffee Bean1"}};
    auto start = std::chrono::high_resolution_clock::now();
    auto result = DeliveringTrojan(location_names, dependencies);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    menu = "*************************Results******************************";
    std::cout << menu << std::endl;
    std::cout << "Topological Sorting Results:" << std::endl;
    for (auto x : result) std::cout << x << std::endl;
    std::vector<std::string> node_ids;
    for (auto x: result) {
      std::string id = GetID(x);
      node_ids.push_back(id);
    }
    PlotPointsOrder(node_ids);
    menu = "**************************************************************\n";
    std::cout << menu;
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl << std::endl;
    PrintMenu();
    break;
  }
    case '7':
  {
    menu =
        "**************************************************************\n"
        "* 7. Find K Closest Points                                    \n"
        "**************************************************************\n";
    std::cout << menu << std::endl;
    
    menu = "Please input the locations:";
    std::cout << menu;
    std::string origin;
    getline(std::cin, origin);
    menu = "Please input k:";
    std::cout << menu;
    getline(std::cin, input);
    int k = std::stoi(input);
    
    auto start = std::chrono::high_resolution_clock::now();
    auto result = FindKClosestPoints(origin, k);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    menu = "*************************Results******************************";
    std::cout << menu << std::endl;
    std::cout << "Find K Closest Points Results:" << std::endl;
    int cnt = 1;
    for (auto x : result) { 
      std::cout << cnt << " " << data[x].name << std::endl;
      cnt++;
    }
    PlotPointsLabel(result, GetID(origin));
    menu = "**************************************************************\n";
    std::cout << menu;
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl << std::endl;
    PrintMenu();
    break;
  }
  case '8':
    break;
  default:
  {
    std::cout << "Please select 1 - 8." << std::endl;
    PrintMenu();
    break;
  }
  }
}


/**
 * CreateGraphFromCSVFile: Read the map data from the csv file
 * 
 */
void TrojanMap::CreateGraphFromCSVFile() {
  std::fstream fin;
  fin.open("src/lib/map.csv", std::ios::in);
  std::string line, word;

  getline(fin, line);
  while (getline(fin, line)) {
    std::stringstream s(line);

    Node n;
    int count = 0;
    while (getline(s, word, ',')) { //using comma to seperate
      word.erase(std::remove(word.begin(), word.end(), '\''), word.end());
      word.erase(std::remove(word.begin(), word.end(), '"'), word.end());
      word.erase(std::remove(word.begin(), word.end(), '['), word.end());
      word.erase(std::remove(word.begin(), word.end(), ']'), word.end());
      if (count == 0)
        n.id = word;
      else if (count == 1)
        n.lat = stod(word);
      else if (count == 2)
        n.lon = stod(word);
      else if (count == 3)
        n.name = word;
      else {
        word.erase(std::remove(word.begin(), word.end(), ' '), word.end());
        n.neighbors.push_back(word);
      }
      count++;
    }
    data[n.id] = n;
    name2id[n.name]=n.id;
  }
  fin.close();
}

/**
 * PlotPoint: Given a location id, plot the point on the map
 * 
 * @param  {std::string} id : location id
 */
void TrojanMap::PlotPoint(std::string id) {
  std::string image_path = cv::samples::findFile("src/lib/input.jpg");
  cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);
  auto result = GetPlotLocation(data[id].lat, data[id].lon);
  cv::circle(img, cv::Point(result.first, result.second), DOT_SIZE,
             cv::Scalar(0, 0, 255), cv::FILLED);
  cv::imshow("TrojanMap", img);
  cv::waitKey(1);
}
/**
 * PlotPoint: Given a lat and a lon, plot the point on the map
 * 
 * @param  {double} lat : latitude
 * @param  {double} lon : longitude
 */
void TrojanMap::PlotPoint(double lat, double lon) {
  std::string image_path = cv::samples::findFile("src/lib/input.jpg");
  cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);
  auto result = GetPlotLocation(lat, lon);
  cv::circle(img, cv::Point(int(result.first), int(result.second)), DOT_SIZE,
             cv::Scalar(0, 0, 255), cv::FILLED);
  cv::startWindowThread();
  cv::imshow("TrojanMap", img);
  cv::waitKey(1);
}

/**
 * PlotPath: Given a vector of location ids draws the path (connects the points)
 * 
 * @param  {std::vector<std::string>} location_ids : path
 */
void TrojanMap::PlotPath(std::vector<std::string> &location_ids) {
  std::string image_path = cv::samples::findFile("src/lib/input.jpg");
  cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);
  auto start = GetPlotLocation(data[location_ids[0]].lat, data[location_ids[0]].lon);
  cv::circle(img, cv::Point(int(start.first), int(start.second)), DOT_SIZE,
             cv::Scalar(0, 0, 255), cv::FILLED);
  for (auto i = 1; i < location_ids.size(); i++) {
    auto start = GetPlotLocation(data[location_ids[i - 1]].lat, data[location_ids[i - 1]].lon);
    auto end = GetPlotLocation(data[location_ids[i]].lat, data[location_ids[i]].lon);
    cv::circle(img, cv::Point(int(end.first), int(end.second)), DOT_SIZE,
               cv::Scalar(0, 0, 255), cv::FILLED);
    cv::line(img, cv::Point(int(start.first), int(start.second)),
             cv::Point(int(end.first), int(end.second)), cv::Scalar(0, 255, 0),
             LINE_WIDTH);
  }
  cv::startWindowThread();
  cv::imshow("TrojanMap", img);
  cv::waitKey(1);
}

/**
 * PlotPoints: Given a vector of location ids draws the points on the map (no path).
 * 
 * @param  {std::vector<std::string>} location_ids : points
 */
void TrojanMap::PlotPoints(std::vector<std::string> &location_ids) {
  std::string image_path = cv::samples::findFile("src/lib/input.jpg");
  cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);
  for (auto x : location_ids) {
    auto result = GetPlotLocation(data[x].lat, data[x].lon);
    cv::circle(img, cv::Point(result.first, result.second), DOT_SIZE,
               cv::Scalar(0, 0, 255), cv::FILLED);
  }
  cv::imshow("TrojanMap", img);
  cv::waitKey(1);
}

/**
 * PlotPoints: Given a vector of location ids draws the points on the map (no path).
 * 
 * @param  {std::vector<std::string>} location_ids : points inside square
 * @param  {std::vector<double>} square : boundary
 */
void TrojanMap::PlotPointsandEdges(std::vector<std::string> &location_ids, std::vector<double> &square) {
  std::string image_path = cv::samples::findFile("src/lib/input.jpg");
  cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);
  auto upperleft = GetPlotLocation(square[2], square[0]);
  auto lowerright = GetPlotLocation(square[3], square[1]);
  cv::Point pt1(int(upperleft.first), int(upperleft.second));
  cv::Point pt2(int(lowerright.first), int(lowerright.second));
  cv::rectangle(img, pt2, pt1, cv::Scalar(0, 0, 255));
  for (auto x : location_ids) {
    auto result = GetPlotLocation(data[x].lat, data[x].lon);
    cv::circle(img, cv::Point(result.first, result.second), DOT_SIZE,
               cv::Scalar(0, 0, 255), cv::FILLED);
    for(auto y : data[x].neighbors) {
      auto start = GetPlotLocation(data[x].lat, data[x].lon);
      auto end = GetPlotLocation(data[y].lat, data[y].lon);
      cv::line(img, cv::Point(int(start.first), int(start.second)),
              cv::Point(int(end.first), int(end.second)), cv::Scalar(0, 255, 0),
              LINE_WIDTH);
    }
  }
  cv::imshow("TrojanMap", img);
  cv::waitKey(1);
}

/**
 * PlotPointsOrder: Given a vector of location ids draws the points on the map (no path).
 * 
 * @param  {std::vector<std::string>} location_ids : points
 */
void TrojanMap::PlotPointsOrder(std::vector<std::string> &location_ids) {
  std::string image_path = cv::samples::findFile("src/lib/input.jpg");
  cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);
  for (auto x : location_ids) {
    auto result = GetPlotLocation(data[x].lat, data[x].lon);
    cv::putText(img, data[x].name, cv::Point(result.first, result.second), cv::FONT_HERSHEY_DUPLEX, 1.0, CV_RGB(255, 0, 0), 2);
  }
  // Plot dots and lines
  auto start = GetPlotLocation(data[location_ids[0]].lat, data[location_ids[0]].lon);
  cv::circle(img, cv::Point(int(start.first), int(start.second)), DOT_SIZE,
             cv::Scalar(0, 0, 255), cv::FILLED);
  for (auto i = 1; i < location_ids.size(); i++) {
    auto start = GetPlotLocation(data[location_ids[i - 1]].lat, data[location_ids[i - 1]].lon);
    auto end = GetPlotLocation(data[location_ids[i]].lat, data[location_ids[i]].lon);
    cv::circle(img, cv::Point(int(end.first), int(end.second)), DOT_SIZE,
               cv::Scalar(0, 0, 255), cv::FILLED);
    cv::arrowedLine(img, cv::Point(int(start.first), int(start.second)),
             cv::Point(int(end.first), int(end.second)), cv::Scalar(0, 255, 0),
             LINE_WIDTH);
  }
  cv::imshow("TrojanMap", img);
  cv::waitKey(1);
}

/**
 * PlotPoints: Given a vector of location ids draws the points on the map (no path).
 * 
 * @param  {std::vector<std::string>} location_ids : points
 */
void TrojanMap::PlotPointsLabel(std::vector<std::string> &location_ids, std::string origin) {
  std::string image_path = cv::samples::findFile("src/lib/input.jpg");
  cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);
  int cnt = 1;
  auto result = GetPlotLocation(data[origin].lat, data[origin].lon);
  cv::circle(img, cv::Point(result.first, result.second), DOT_SIZE,
               cv::Scalar(0, 255, 0), cv::FILLED);
  for (auto x : location_ids) {
    auto result = GetPlotLocation(data[x].lat, data[x].lon);
    cv::circle(img, cv::Point(result.first, result.second), DOT_SIZE,
               cv::Scalar(0, 0, 255), cv::FILLED);
    cv::putText(img, std::to_string(cnt), cv::Point(result.first, result.second), cv::FONT_HERSHEY_DUPLEX, 1.0, CV_RGB(255, 0, 0), 2);
    cnt++;
  }
  cv::imshow("TrojanMap", img);
  cv::waitKey(1);
}

/**
 * CreateAnimation: Create the videos of the progress to get the path
 * 
 * @param  {std::vector<std::vector<std::string>>} path_progress : the progress to get the path
 */
void TrojanMap::CreateAnimation(std::vector<std::vector<std::string>> &path_progress, std::string filename){
  std::string filepath = "src/lib/" + filename + ".avi"; 
  cv::VideoWriter video(filepath, cv::VideoWriter::fourcc('M','J','P','G'), 10, cv::Size(1248,992));
  for(auto location_ids: path_progress) {
    std::string image_path = cv::samples::findFile("src/lib/input.jpg");
    cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);
    auto start = GetPlotLocation(data[location_ids[0]].lat, data[location_ids[0]].lon);
    cv::circle(img, cv::Point(int(start.first), int(start.second)), DOT_SIZE,
              cv::Scalar(0, 0, 255), cv::FILLED);
    for (auto i = 1; i < location_ids.size(); i++) {
      auto start = GetPlotLocation(data[location_ids[i - 1]].lat, data[location_ids[i - 1]].lon);
      auto end = GetPlotLocation(data[location_ids[i]].lat, data[location_ids[i]].lon);
      cv::circle(img, cv::Point(int(end.first), int(end.second)), DOT_SIZE,
                cv::Scalar(0, 0, 255), cv::FILLED);
      cv::line(img, cv::Point(int(start.first), int(start.second)),
              cv::Point(int(end.first), int(end.second)), cv::Scalar(0, 255, 0),
              LINE_WIDTH);
    }
    video.write(img);
    cv::imshow("TrojanMap", img);
    cv::waitKey(1);
  }
	video.release();
}
/**
 * GetPlotLocation: Transform the location to the position on the map
 * 
 * @param  {double} lat         : latitude 
 * @param  {double} lon         : longitude
 * @return {std::pair<double, double>}  : position on the map
 */
std::pair<double, double> TrojanMap::GetPlotLocation(double lat, double lon) {
  std::pair<double, double> bottomLeft(34.01001, -118.30000);
  std::pair<double, double> upperRight(34.03302, -118.26502);
  double h = upperRight.first - bottomLeft.first;
  double w = upperRight.second - bottomLeft.second;
  std::pair<double, double> result((lon - bottomLeft.second) / w * 1248,
                                   (1 - (lat - bottomLeft.first) / h) * 992);
  return result;
}

//-----------------------------------------------------
// TODO: Student should implement the following:
//-----------------------------------------------------
/**
 * GetLat: Get the latitude of a Node given its id.
 * 
 * @param  {std::string} id : location id
 * @return {double}         : latitude
 */
double TrojanMap::GetLat(std::string id) {
  return data[id].lat;
}


/**
 * GetLon: Get the longitude of a Node given its id. 
 * 
 * @param  {std::string} id : location id
 * @return {double}         : longitude
 */
double TrojanMap::GetLon(std::string id) { 
  return data[id].lon;
}

/**
 * GetName: Get the name of a Node given its id.
 * 
 * @param  {std::string} id : location id
 * @return {std::string}    : name
 */
std::string TrojanMap::GetName(std::string id) { 
  return data[id].name;
}

/**
 * GetNeighborIDs: Get the neighbor ids of a Node.
 * 
 * @param  {std::string} id            : location id
 * @return {std::vector<std::string>}  : neighbor ids
 */
std::vector<std::string> TrojanMap::GetNeighborIDs(std::string id) {
  return data[id].neighbors;

}

/**
 * CalculateDistance: Get the distance between 2 nodes. 
 * 
 * @param  {std::string} a  : a_id
 * @param  {std::string} b  : b_id
 * @return {double}  : distance in mile
 */
double TrojanMap::CalculateDistance(const std::string &a_id, const std::string &b_id) {
  // Do not change this function
  // TODO: Use Haversine Formula:
  // dlon = lon2 - lon1;
  // dlat = lat2 - lat1;
  // a = (sin(dlat / 2)) ^ 2 + cos(lat1) * cos(lat2) * (sin(dlon / 2)) ^ 2;
  // c = 2 * arcsin(min(1, sqrt(a)));
  // distances = 3961 * c;

  // where 3961 is the approximate radius of the earth at the latitude of
  // Washington, D.C., in miles
  Node a = data[a_id];
  Node b = data[b_id];
  double dlon = (b.lon - a.lon) * M_PI / 180.0;
  double dlat = (b.lat - a.lat) * M_PI / 180.0;
  double p = pow(sin(dlat / 2),2.0) + cos(a.lat * M_PI / 180.0) * cos(b.lat * M_PI / 180.0) * pow(sin(dlon / 2),2.0);
  double c = 2 * asin(std::min(1.0,sqrt(p)));
  return c * 3961;
}

/**
 * CalculatePathLength: Calculates the total path length for the locations inside the vector.
 * 
 * @param  {std::vector<std::string>} path : path
 * @return {double}                        : path length
 */
double TrojanMap::CalculatePathLength(const std::vector<std::string> &path) {
  // Do not change this function
  double sum = 0;
  for (int i = 0;i < path.size()-1; i++) {
    sum += CalculateDistance(path[i], path[i+1]);
  }
  return sum;
}

/**
 * Autocomplete: Given a parital name return all the possible locations with
 * partial name as the prefix.
 *
 * @param  {std::string} name          : partial name
 * @return {std::vector<std::string>}  : a vector of full names
 */
bool TrojanMap::match(std::string str, std::string target){
  int n = target.size();
  if(n > str.size()) return false;
  for(int i = 0; i < n; ++i){
    if(std::tolower(str[i]) != std::tolower(target[i])){
      return false;
    }
  }
  return true;
}

std::vector<std::string> TrojanMap::Autocomplete(std::string name){
  std::vector<std::string> res;
  int n = name.size();
  for(auto &item : data){
    std::string result = GetName(item.first);
    if(result.size() < n) continue;
    if(match(result, name)){
      res.push_back(result);
    }
  }
  return res;
}


/**
 * GetPosition: Given a location name, return the position.
 *
 * @param  {std::string} name          : location name
 * @return {std::pair<double,double>}  : (lat, lon)
 */
std::pair<double, double> TrojanMap::GetPosition(std::string name) {
  std::pair<double, double> results(-1, -1);
  
  std::string ID=GetID(name);
  if(ID==""){return results;}
  results.first=data[ID].lat;
  results.second=data[ID].lon;
  
  return results;
}

  
/**
 * GetID: Given a location name, return the id. 
 * If the node does not exist, return an empty string. 
 *
 * @param  {std::string} name          : location name
 * @return {int}  : id
 */
std::string TrojanMap::GetID(std::string name) {
  if(name2id.count(name)<=0){return "";}
  std::string res = name2id[name];
  return res;
}

/**
 * CalculateShortestPath_Dijkstra: Given 2 locations, return the shortest path which is a
 * list of id.
 *
 * @param  {std::string} location1_name     : start
 * @param  {std::string} location2_name     : goal
 * @return {std::vector<std::string>}       : path
 */
std::vector<std::string> TrojanMap::CalculateShortestPath_Dijkstra(
    std::string location1_name, std::string location2_name) {
  std::vector<std::string> path;
  std::string a_id=GetID(location1_name);
  std::string b_id=GetID(location2_name);
  std::unordered_map<std::string,double> dist; // store the shortest distance in visited
  std::unordered_map<std::string,std::string>prev;// return the prev node
  std::unordered_set<std::string> visited; // check if the location had been popped from the heap
  auto compare=[](DJNode a,DJNode b){return a.dist > b.dist;};
  std::priority_queue<DJNode,std::vector<DJNode>,decltype(compare)> dist_heap(compare);
  dist_heap.emplace(DJNode(a_id,0.0));
  dist[a_id]=0.0;
  while (!dist_heap.empty()){
    DJNode temp=dist_heap.top();
    dist_heap.pop();
    // if the top of the heap had been popped, just ignore it, until find the first not pooped one
    while(visited.count(temp.id)>0){
      temp=dist_heap.top();
      dist_heap.pop();
      if(dist_heap.empty()) return path;
    }
   
    visited.insert(temp.id);
    if(temp.id==b_id)break;
    for(auto &neigh : data[temp.id].neighbors){
      if(visited.count(neigh)<=0){
        if(dist.count(neigh)<=0){
          dist[neigh]=std::numeric_limits<double>::max();
        }
        double original_dist=dist[neigh];
        double updated_dist=dist[temp.id]+CalculateDistance(temp.id,neigh);
        if(original_dist>updated_dist){
          dist[neigh] =updated_dist;
          prev[neigh]=temp.id;
          dist_heap.emplace(DJNode(neigh,dist[neigh]));
        }
      }
    }
  }
  std::string temp_loc=b_id;
  while(temp_loc!=a_id){
    path.emplace_back(temp_loc);
    temp_loc=prev[temp_loc];
  }
  path.emplace_back(a_id);
  std::reverse(path.begin(),path.end());
  return path;

}


/**
 * CalculateShortestPath_Bellman_Ford: Given 2 locations, return the shortest path which is a
 * list of id.
 *
 * @param  {std::string} location1_name     : start
 * @param  {std::string} location2_name     : goal
 * @return {std::vector<std::string>}       : path
 */


void TrojanMap::Bellman_dfs(std::string u,std::unordered_map<std::string,bool>&visited,
    std::unordered_map<std::string,std::unordered_map<std::string,double>>&mp){
  visited[u]=true;
  //res.push_back(u);
  for(auto &i:data[u].neighbors){
    mp[u][i]=CalculateDistance(i,u);
    if(!visited[i]){
      Bellman_dfs(i,visited,mp);
    }
  }
}
void TrojanMap::Bellman_bfs(std::string loca,std::string locb,
    std::unordered_map<std::string,std::unordered_map<std::string,double>>&mp){
  std::queue<std::string> q;
  std::unordered_set<std::string> visited;
  q.push(loca);
  visited.insert(loca);
  while(!q.empty()){
    std::string temp=q.front();
    q.pop();
    for(auto &neigh :data[temp].neighbors){
      mp[temp][neigh]=CalculateDistance(temp,neigh);
      if(visited.count(neigh)==0){
        if(neigh!=locb){
          q.push(neigh);
        }
        visited.insert(neigh);
      }
    }
  }
}
std::vector<std::string> TrojanMap::CalculateShortestPath_Bellman_Ford_no_dfs(
                std::string location1_name, std::string location2_name){
  std::string loc1_id=GetID(location1_name);
  std::string loc2_id=GetID(location2_name);
  std::vector<std::string> path;
  std::unordered_map<std::string,bool> visited;
  //std::unordered_map<std::string,std::unordered_map<std::string,double>>mp;
  std::vector<std::string> node_store;//store the ids of dfs
  std::unordered_map<std::string,double>distance;//store the distance from the source to every node;
  std::unordered_map<std::string,std::string>prev;//store the prev node of the shortest path;
  //initialize
  for(auto &items:data){
    distance[items.second.id]=std::numeric_limits<double>::max();
  }
  distance[loc1_id]=0.0;
  for(int i=0;i<data.size()-1;i++){
    for(auto &u:data){
      for(auto &item:u.second.neighbors){
        double d= CalculateDistance(u.second.id,item);
        if(distance[item]+d<distance[u.second.id]){
          distance[u.second.id]=distance[item]+d;
          prev[u.second.id]=item;
        }
      }
    }
  }
  path.push_back(loc2_id);
  std::string temp=loc2_id;
  while(temp!=loc1_id){
    path.push_back(prev[temp]);
    temp=prev[temp];
  }
  std::reverse(path.begin(),path.end());
  return path;
}

std::vector<std::string> TrojanMap::CalculateShortestPath_Bellman_Ford(
                std::string location1_name, std::string location2_name){
  std::string loc1_id=GetID(location1_name);
  std::string loc2_id=GetID(location2_name);
  std::vector<std::string> path;
  std::unordered_map<std::string,bool> visited;
  std::unordered_map<std::string,std::unordered_map<std::string,double>>mp;
  std::vector<std::string> node_store;//store the ids of dfs
  // Bellman_bfs(loc1_id,loc2_id,mp);
  //using dfs to create a subgraph
  Bellman_dfs(loc1_id,visited,mp);
  if(visited[loc2_id]==false) return path;  
  std::unordered_map<std::string,double>distance;//store the distance from the source to every node;
  std::unordered_map<std::string,std::string>prev;//store the prev node of the shortest path;
  //initialize
  for(auto &items:mp){
    distance[items.first]=std::numeric_limits<double>::max();
  }
  distance[loc1_id]=0.0;
  for(int i=0;i<mp.size()-1;i++){
    for(auto &u:mp){
      for(auto &item:u.second){
        if(distance[item.first]+mp[u.first][item.first]<distance[u.first]){
          distance[u.first]=distance[item.first]+mp[u.first][item.first];
          prev[u.first]=item.first;
        }
      }
    }
  }
  path.push_back(loc2_id);
  std::string temp=loc2_id;
  while(temp!=loc1_id){
    path.push_back(prev[temp]);
    temp=prev[temp];
  }
  std::reverse(path.begin(),path.end());
  return path;
}

//not used
std::unordered_map<std::string,std::vector<std::string>>TrojanMap::Getpredecessor(std::string u,
    std::unordered_map<std::string,std::unordered_map<std::string,double>>mp){
    std::unordered_map<std::string,std::vector<std::string>>prev;
    for(auto &it :mp[u]){
      prev[u].push_back(it.first);
    }
    return prev;
}
//not used
double TrojanMap::Bellman_helper(std::string s,int i,std::string v,
    std::unordered_map<std::string,std::unordered_map<std::string,double>>mp,
    std::vector<std::string>&path){
  std::stack<std::string>stk;
  path.push_back(v);
  if(i==0){
    if(s==v){
      //path.push_back(v);
      path.push_back(s);
      return 0;   
    }else{
      path.clear();
      return std::numeric_limits<double>::max();
    } 
  }else{
    auto prev=Getpredecessor(v,mp);
    double d =std::numeric_limits<double>::max();
    for(auto u:prev[v]){
      if(d>Bellman_helper(s,i-1,u,mp,path)+CalculateDistance(u,v)){
        d=Bellman_helper(s,i-1,u,mp,path)+CalculateDistance(u,v);
        stk.push(u);
      }
    }
    if(Bellman_helper(s,i-1,v,mp,path)>d){
      std::string p=stk.top();
      path.push_back(p); 
    }
    return std::min(d,Bellman_helper(s,i-1,v,mp,path));
  }
}

/**
 * Travelling salesman problem: Given a list of locations, return the shortest
 * path which visit all the places and back to the start point.
 *
 * @param  {std::vector<std::string>} input : a list of locations needs to visit
 * @return {std::pair<double, std::vector<std::vector<std::string>>} : a pair of total distance and the all the progress to get final path
 */

/**
 * use the backtracking to slove the TSP
 * 
 *
 * @param  {const std::vector<std::vector<double>>&} adjacent_matrix : adjacent matrix of the nodes
 * @param  {std::vector<std::vector<std::string>>&} paths : store all the paths
 * @return {std::pair<double, std::vector<std::vector<std::string>>} : a pair of total distance and the all the progress to get final path (ids)
 */
std::vector<std::vector<double>> TrojanMap::CreateAdjMatrix(std::vector<std::string> &location_ids){
  
  int n = location_ids.size();
  // initialize a matrix with infinity
  std::vector<std::vector<double>> adjacent_matrix(n, std::vector<double>(n, std::numeric_limits<double>::max()));

  // creat a matrix to store the distance between evey node
  for(int i  = 0; i < n; ++i){
		std::string source_loc = location_ids[i];
		for(int j = i + 1; j < n; ++j){
			std::string destination_loc = location_ids[j];
			adjacent_matrix[i][j] = adjacent_matrix[j][i] = CalculateDistance(source_loc, destination_loc);
		}
  }
  return adjacent_matrix;
}

void TrojanMap::Backtracking(const std::vector<std::vector<double>> &adjacent_matrix, std::vector<std::vector<std::string>> &paths, std::vector<std::string> &path, std::vector<bool> &visit, double &mincost, double cost, int current, const std::vector<std::string> &location_ids, int &count){
  if(path.size() == adjacent_matrix.size()){
    ++count;
		cost += adjacent_matrix[0][current];
		if(cost < mincost){
			mincost = cost;
			path.emplace_back(location_ids[0]); 
			paths.emplace_back(path);
			path.pop_back();
		} 
		return;
	}
	for(int i = 0; i < adjacent_matrix.size(); ++i){
		if(!visit[i]){
			if(cost + adjacent_matrix[i][current] > mincost) continue; // early break
			visit[i] = true;
			path.emplace_back(location_ids[i]);
			Backtracking(adjacent_matrix, paths, path, visit, mincost, cost + adjacent_matrix[i][current], i, location_ids, count);
			visit[i] = false;
			path.pop_back();
		}
	}
}

std::pair<double, std::vector<std::vector<std::string>>> TrojanMap::TravellingTrojan(std::vector<std::string> &location_ids){
  
  std::pair<double, std::vector<std::vector<std::string>>> results;
  
  int n = location_ids.size();
  //creat a matrix to store the distance between evey node
  std::vector<std::vector<double>> adjacent_matrix = CreateAdjMatrix(location_ids);

	std::vector<bool> visit(n);
	visit[0] = true;
	std::vector<std::vector<std::string>> paths;
	std::vector<std::string> path;
	path.emplace_back(location_ids[0]);
	double mincost = std::numeric_limits<double>::max();
  int count = 0;
	Backtracking(adjacent_matrix, paths, path, visit, mincost, 0, 0, location_ids, count);
	results = make_pair(mincost, paths);
  std::cout << "the backtracking have iterated " << count << " times." << std::endl; 
  return results;
}

void TrojanMap::Brute_Force(const std::vector<std::vector<double>> &adjacent_matrix, std::vector<std::vector<std::string>> &paths, std::vector<std::string> &path, std::vector<bool> &visit, double &mincost, double cost, int current, const std::vector<std::string> &location_ids, int &count){
  if(path.size() == adjacent_matrix.size()){
    ++count;
		cost += adjacent_matrix[0][current];
		if(cost < mincost){
			mincost = cost;
			path.emplace_back(location_ids[0]); 
			paths.emplace_back(path);
			path.pop_back();
		} 
		return;
	}
	for(int i = 0; i < adjacent_matrix.size(); ++i){
		if(!visit[i]){
			visit[i] = true;
			path.emplace_back(location_ids[i]);
			Brute_Force(adjacent_matrix, paths, path, visit, mincost, cost + adjacent_matrix[i][current], i, location_ids, count);
			visit[i] = false;
			path.pop_back();
		}
	}
}


std::pair<double, std::vector<std::vector<std::string>>> TrojanMap::TravellingTrojan_Brute_force(
      std::vector<std::string> &location_ids){
  std::pair<double, std::vector<std::vector<std::string>>> results;

  int n = location_ids.size();
  //creat a matrix to store the distance between evey node
  std::vector<std::vector<double>> adjacent_matrix = CreateAdjMatrix(location_ids);

	std::vector<bool> visit(n);
	visit[0] = true;
	std::vector<std::vector<std::string>> paths;
	std::vector<std::string> path;
	path.emplace_back(location_ids[0]);
	double mincost = std::numeric_limits<double>::max();
  int count = 0;
	Brute_Force(adjacent_matrix, paths, path, visit, mincost, 0, 0, location_ids, count);
	results = make_pair(mincost, paths);
  std::cout << "the brute_force have iterated " << count << " times." << std::endl; 
  return results;
}

double TrojanMap::CalculatePathDis(const std::vector<std::vector<double>> &adjacent_matrix, 
                        std::unordered_map<std::string, int> &id2index, std::vector<std::string> &path){
  double distance = 0.0;
  int n = path.size();
  int locA, locB;
  for(int i = 0; i < n - 1; ++i){
    locA = id2index[path[i]];
    locB = id2index[path[i+1]];
    distance += adjacent_matrix[locA][locB];
  }
  return distance;
}

// time complexity: k*n^2
std::pair<double, std::vector<std::vector<std::string>>> TrojanMap::TravellingTrojan_2opt(
      std::vector<std::string> &location_ids){
  std::pair<double, std::vector<std::vector<std::string>>> results;
  int n = location_ids.size();
  std::unordered_map<std::string, int> id2index;
  for(int i = 0; i < n; ++i) id2index[location_ids[i]] = i;
  std::vector<std::vector<double>> adjacent_matrix = CreateAdjMatrix(location_ids);

  std::vector<std::string> path_start = location_ids;
  path_start.emplace_back(location_ids[0]);
  results.first = CalculatePathDis(adjacent_matrix, id2index, path_start);
  results.second.emplace_back(path_start);

  TPS_2opt(adjacent_matrix, results.first, results.second, path_start, id2index);
  return results;
}

void TrojanMap::TPS_2opt(const std::vector<std::vector<double>> &adjacent_matrix, 
                        double &mincost, std::vector<std::vector<std::string>> &paths, 
                        std::vector<std::string> &path_start, std::unordered_map<std::string, int> &id2index){

  int n = path_start.size();
  std::vector<std::string> path_copy = path_start;
  bool improve = true; // check if it still can be improved
  while(improve){
    improve = false;
    for(int start = 1; start < n - 1; ++start){
      for(int end = start + 1; end < n; ++end){
        int start_0 = id2index[path_copy[start-1]], start_1 = id2index[path_copy[start]];
        int end_0 = id2index[path_copy[end-1]], end_1 = id2index[path_copy[end]];
        //double d1 = CalculateDistance(path_copy[start-1], path_copy[start]) + CalculateDistance(path_copy[end-1], path_copy[end]);
        //double d2 = CalculateDistance(path_copy[start-1], path_copy[end-1]) + CalculateDistance(path_copy[start], path_copy[end]);
        double d1 = adjacent_matrix[start_0][start_1] + adjacent_matrix[end_0][end_1];
        double d2 = adjacent_matrix[start_0][end_0] + adjacent_matrix[start_1][end_1];
        if(d2 < d1){
          std::reverse(path_copy.begin() + start, path_copy.begin() + end);
          paths.emplace_back(path_copy);
          mincost = CalculatePathDis(adjacent_matrix, id2index, path_copy);
          path_start.assign(path_copy.begin(), path_copy.end());
          improve = true;
          break;
        }
      }
      if(improve) break;
    }
  }         
}

std::pair<double, std::vector<std::vector<std::string>>> TrojanMap::TravellingTrojan_3opt(
      std::vector<std::string> &location_ids){
  std::pair<double, std::vector<std::vector<std::string>>> results;
  int n = location_ids.size();
  std::unordered_map<std::string, int> id2index;
  for(int i = 0; i < n; ++i) id2index[location_ids[i]] = i;
  std::vector<std::vector<double>> adjacent_matrix = CreateAdjMatrix(location_ids);

  std::vector<std::string> path_start = location_ids;
  path_start.emplace_back(location_ids[0]);
  results.first = CalculatePathDis(adjacent_matrix, id2index, path_start);
  results.second.emplace_back(path_start);

  TPS_3opt(adjacent_matrix, results.first, results.second, path_start, id2index);
  return results;
}

void TrojanMap::TPS_3opt(const std::vector<std::vector<double>> &adjacent_matrix, 
                        double &mincost, std::vector<std::vector<std::string>> &paths, 
                        std::vector<std::string> &path_start, std::unordered_map<std::string, int> &id2index){

  int n = path_start.size();
  std::vector<std::string> path_copy = path_start;
  bool improve = true; // check if it still can be improved
  while(improve){
    improve = false;
    for(int start = 1; start < n - 2; ++start){
      for(int mid = start + 1; mid < n - 1; ++mid){
        for(int end = mid + 1; end < n; ++end){
          int start_0 = id2index[path_copy[start-1]], start_1 = id2index[path_copy[start]];
          int mid_0 = id2index[path_copy[mid-1]], mid_1 = id2index[path_copy[mid]];
          int end_0 = id2index[path_copy[end-1]], end_1 = id2index[path_copy[end]];
          //double d0 = CalculateDistance(path_copy[start-1], path_copy[start]) + CalculateDistance(path_copy[mid-1], path_copy[mid]) + CalculateDistance(path_copy[end-1], path_copy[end]);
          double d0 = adjacent_matrix[start_0][start_1] + adjacent_matrix[mid_0][mid_1] + adjacent_matrix[end_0][end_1];

          //double d1 = CalculateDistance(path_copy[start-1], path_copy[mid-1]) + CalculateDistance(path_copy[start], path_copy[end-1]) + CalculateDistance(path_copy[mid], path_copy[end]);
          double d1 = adjacent_matrix[start_0][mid_0] + adjacent_matrix[start_1][end_0] + adjacent_matrix[mid_1][end_1];

          //double d2 = CalculateDistance(path_copy[start-1], path_copy[mid]) + CalculateDistance(path_copy[end-1], path_copy[mid-1]) + CalculateDistance(path_copy[start], path_copy[end]);
          double d2 = adjacent_matrix[start_0][mid_1] + adjacent_matrix[end_0][mid_0] + adjacent_matrix[start_1][end_1];

          //double d3 = CalculateDistance(path_copy[start-1], path_copy[end-1]) + CalculateDistance(path_copy[mid], path_copy[start]) + CalculateDistance(path_copy[mid-1], path_copy[end]);
          double d3 = adjacent_matrix[start_0][end_0] + adjacent_matrix[mid_1][start_1] + adjacent_matrix[mid_0][end_1];

          //double d4 = CalculateDistance(path_copy[start-1], path_copy[mid]) + CalculateDistance(path_copy[end-1], path_copy[start]) + CalculateDistance(path_copy[mid-1], path_copy[end]);
          double d4 = adjacent_matrix[start_0][mid_1] + adjacent_matrix[end_0][start_1] + adjacent_matrix[mid_0][end_1];

          std::vector<double> dist{d0, d1, d2, d3, d4};
          int min_change = std::min_element(dist.begin(), dist.end()) - dist.begin();
          if(min_change == 0){
            continue;
          }
          if(min_change == 1){
            // the shortest cahnge is the 1st one
            // 1. ab'c'
            std::reverse(path_copy.begin() + start, path_copy.begin() + mid);
            std::reverse(path_copy.begin() + mid , path_copy.begin() + end);
          }else if(min_change == 2){
            // 2. a'b'c
            std::reverse(path_copy.begin() + start, path_copy.begin() + end);
            std::reverse(path_copy.begin() + start, path_copy.begin() + start + end - mid);
          }else if(min_change == 3){
            // 3. a'bc'
            std::reverse(path_copy.begin() + start, path_copy.begin() + end);
            std::reverse(path_copy.begin() + start + end - mid, path_copy.begin() + end);
          }else if(min_change == 4){
            // 4. a'b'c'
            std::reverse(path_copy.begin() + start, path_copy.begin() + end);
            std::reverse(path_copy.begin() + start, path_copy.begin() + start + end - mid);
            std::reverse(path_copy.begin() + start + end - mid, path_copy.begin() + end);
          }
          mincost = CalculatePathDis(adjacent_matrix, id2index, path_copy);
          paths.emplace_back(path_copy);
          improve = true;
          break;
        }
        if(improve) break;
      }
      if(improve) break;
    }
    if(!improve) break;
  }   
}

/**
 * Given CSV filename, it read and parse locations data from CSV file,
 * and return locations vector for topological sort problem.
 *
 * @param  {std::string} locations_filename     : locations_filename
 * @return {std::vector<std::string>}           : locations 
 */
std::vector<std::string> TrojanMap::ReadLocationsFromCSVFile(std::string locations_filename){
  std::vector<std::string> location_names_from_csv;
  std::fstream fin;
  fin.open(locations_filename, std::ios::in);
  std::string line, word;

  getline(fin, line);
  while(getline(fin, line)){
    line.erase(line.end() - 1);
    location_names_from_csv.emplace_back(line);
  }
  fin.close();
  return location_names_from_csv;
}

/**
 * Given CSV filenames, it read and parse dependencise data from CSV file,
 * and return dependencies vector for topological sort problem.
 *
 * @param  {std::string} dependencies_filename     : dependencies_filename
 * @return {std::vector<std::vector<std::string>>} : dependencies
 */
std::vector<std::vector<std::string>> TrojanMap::ReadDependenciesFromCSVFile(std::string dependencies_filename){
  std::vector<std::vector<std::string>> dependencies_from_csv;
  std::fstream fin;
  fin.open(dependencies_filename, std::ios::in);
  std::string line, word;

  getline(fin, line);
  while(getline(fin, line)){
    std::stringstream s(line);
    std::vector<std::string> dependency;
    while(getline(s, word, ',')){
      dependency.emplace_back(word);
    }
    dependencies_from_csv.emplace_back(dependency);
  }
  fin.close();
  return dependencies_from_csv;
}

/**
 * DeliveringTrojan: Given a vector of location names, it should return a sorting of nodes
 * that satisfies the given dependencies.
 *
 * @param  {std::vector<std::string>} locations                     : locations
 * @param  {std::vector<std::vector<std::string>>} dependencies     : prerequisites
 * @return {std::vector<std::string>} results                       : results
 */
std::vector<std::string> TrojanMap::DeliveringTrojan(std::vector<std::string> &locations,
                                                     std::vector<std::vector<std::string>> &dependencies){
  std::vector<std::string> result;
  int n = locations.size();
  std::unordered_map<std::string, int> loc2index;
  for(int i = 0; i < n; ++i) loc2index[locations[i]] = i;

  std::unordered_map<int, std::vector<int>> DAG;
  std::vector<bool> visit(n);
  std::vector<bool> being_visited(n);

  for(auto &dependency : dependencies){
    int i = loc2index[dependency[0]], j = loc2index[dependency[1]];
    DAG[i].emplace_back(j); // construst the DAG
    visit[j] = true; // mark j has dependency
  }

  std::vector<int> start_locations;
  for(int i = 0; i < n; ++i){
    if(!visit[i]){
      start_locations.emplace_back(i); // get the locations which has no dependency
    }
  }
  if(start_locations.size() == 0) return result; // if cannot find the start location return empty;
  visit.assign(n, false); // clear visit
  std::vector<int> topo_list;
  for(auto &start_loc : start_locations){
    if(!visit[start_loc]){
      if(TopoSort(DAG, visit, being_visited, start_loc, topo_list) == true) return result; // if there is a cycle
    }
  } 
  if(topo_list.size() != n) return result; // if no feasible route exists
  for(int i = n-1; i >= 0; --i) result.emplace_back(locations[topo_list[i]]);
  return result;                                                     
}

bool TrojanMap::TopoSort(std::unordered_map<int, std::vector<int>> &DAG, std::vector<bool> &visit, std::vector<bool> &being_visited, int cur, std::vector<int> &topo_list){
  // DFS
  being_visited[cur] = true;
  for(auto &loc : DAG[cur]){
    if(being_visited[loc]) return true;
    if(!visit[loc]){
      being_visited[loc] = true;
      if(TopoSort(DAG, visit, being_visited, loc, topo_list) == true) return true;
      being_visited[loc] = false;
    }
  }
  visit[cur] = true;
  topo_list.emplace_back(cur);
  return false;
}

/**
 * Cycle Detection: Given four points of the square-shape subgraph, return true if there
 * is a cycle path inside the square, false otherwise.
 * 
 * @param {std::vector<double>} square: four vertexes of the square area
 * @return {bool}: whether there is a cycle or not
 */
bool TrojanMap::CycleDetection(std::vector<double> &square) {
//establish an map with all node in square
  std::unordered_map<std::string,std::vector<std::string>> adj;
  for(auto &item:data){
    if(item.second.lon>=square[0] && item.second.lon<=square[1] && item.second.lat<=square[2] && item.second.lat>=square[3]){
      adj[item.first]=item.second.neighbors;
    }
  }
  //stored the visited nodes on the map
  std::vector<std::string>local_ids;
  //some preparation
  std::map<std::string,bool>isvisited;
  for(auto &items:local_ids){
    isvisited[items]=false;
  }
  for(auto &node:adj){
    if(isvisited[node.first]==false){
      if(IsCyclicUtil(node.first,isvisited,"",adj)==true){ 
        return true;
      }
    }
  }
  return false;
  //plot the graph
  for(auto items:isvisited){
    if(items.second==true){
      local_ids.push_back(items.first);
      PlotPointsandEdges(local_ids,square);
    }
  }
}

//using DFS to find cycle
 bool TrojanMap::IsCyclicUtil(std::string node,std::map<std::string,bool>&isvisited,
     std::string parent,std::unordered_map<std::string,std::vector<std::string>> adj){
  isvisited[node]=true;
  for(auto &nei:adj[node]){
    if (isvisited[nei]==false){
      if(IsCyclicUtil(nei,isvisited,node,adj)==true) return true;
    }else if(isvisited[nei]==true && nei!=parent ) return true;  
  }
  return false;
 }
//O(n^2)


/**
 * FindKClosetPoints: Given a location id and k, find the k closest points on the map
 * 
 * @param {std::string} name: the name of the location
 * @param {int} k: number of closest points
 * @return {std::vector<std::string>}: k closest points
 */
std::vector<std::string> TrojanMap::FindKClosestPoints(std::string name, int k) {
  std::vector<std::string> res;
  //std::vector<std::string> location_ids;
  std::string loc_id=GetID(name);
  auto compare=[](DJNode a,DJNode b){return a.dist < b.dist;};
  std::priority_queue<DJNode,std::vector<DJNode>,decltype(compare)> dist_heap(compare);

  for(auto &items:data){
    if(data[items.first].name.empty()) continue;
    double dis= CalculateDistance(loc_id,items.first);
    if(dist_heap.size()<k+1){
      dist_heap.emplace(DJNode(items.first,dis));
    }else{
      if(dis<dist_heap.top().dist){
        dist_heap.pop();
        dist_heap.emplace(DJNode(items.first,dis));
      }
    }
  }
  // dist_heap.pop();
  while (k--){
    DJNode temp=dist_heap.top();
    dist_heap.pop();
    res.push_back(temp.id);
  }
  std::reverse(res.begin(),res.end());
  return res;
}
