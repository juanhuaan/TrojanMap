#include <map>
#include <vector>

#include "gtest/gtest.h"
#include "src/lib/trojanmap.h"

/**
 * 
 * Test for Autocomplete
 * 
 * */
TEST(TrojanMapStudentTest, Autocomplete1) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  // Test the simple case
  auto names = m.Autocomplete("Uni");
  std::unordered_set<std::string> gt1 = {"University Park", "University Seventh Day Adventist Church", "University SDA Church Food Pantry"}; // groundtruth for "Uni"
  int success = 0;
  for (auto& n: names) {
    EXPECT_EQ(gt1.count(n) > 0, true);
    if (gt1.count(n) > 0){
      success++;
    }
  }
  EXPECT_EQ(success, gt1.size());
  // Test the lower case
  names = m.Autocomplete("uni");
  std::unordered_set<std::string> gt2 = {"University Park", "University Seventh Day Adventist Church", "University SDA Church Food Pantry"}; // groundtruth for "uni"
  success = 0;
  for (auto& n: names) {
    EXPECT_EQ(gt2.count(n) > 0, true);
    if (gt2.count(n) > 0){
      success++;
    }
  }
  EXPECT_EQ(success, gt2.size());
  // Test the lower and upper case 
  names = m.Autocomplete("uNi"); 
  std::unordered_set<std::string> gt3 = {"University Park", "University Seventh Day Adventist Church", "University SDA Church Food Pantry"}; // groundtruth for "uNi"
  success = 0;
  for (auto& n: names) {
    EXPECT_EQ(gt3.count(n) > 0, true);
    if (gt3.count(n) > 0){
      success++;
    }
  }
  EXPECT_EQ(success, gt3.size());
  // Test the upper case 
  names = m.Autocomplete("UNI"); 
  std::unordered_set<std::string> gt4 = {"University Park", "University Seventh Day Adventist Church", "University SDA Church Food Pantry"}; // groundtruth for "UNI"
  success = 0;
  for (auto& n: names) {
    EXPECT_EQ(gt4.count(n) > 0, true);
    if (gt4.count(n) > 0){
      success++;
    }
  }
  EXPECT_EQ(success, gt4.size());
}

TEST(TrojanMapStudentTest, Autocomplete2) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  auto names = m.Autocomplete("tA");
  std::unordered_set<std::string> gt1 = {"Target", "Tap Two Blue"}; // groundtruth for "tA"
  int success = 0;
  for (auto& n: names) {
    EXPECT_EQ(gt1.count(n) > 0, true);
    if (gt1.count(n) > 0){
      success++;
    }
  }
  EXPECT_EQ(success, gt1.size());
}

TEST(TrojanMapStudentTest, Autocomplete3) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  auto names = m.Autocomplete("X");
  std::unordered_set<std::string> gt1 = {}; // groundtruth for "X"
  EXPECT_EQ(names.size(), gt1.size());
}

/**
 * 
 * Test for GetPosition
 * 
 * */


/**
 * 
 * Test for CalculateShortestPath
 * 
 * */


/**
 * 
 * Test for TravellingTrojan
 * 
 * */

TEST(TrojanMapStudentTest, TSP) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  std::vector<std::string> input{"6816305558", "4015372481", "4536993737", "6820972448"}; // Input location ids 
  auto result = m.TravellingTrojan(input);
  std::cout << "My path length: "  << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"6816305558", "6820972448", "4536993737", "4015372481", "6816305558"}; // Expected order
  std::cout << "GT path length: "  << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the gt path lengths
  bool flag = false;
  if (gt == result.second[result.second.size()-1]) // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (gt == result.second[result.second.size()-1]) 
    flag = true;
  
  EXPECT_EQ(flag, true);
}

// Test TSP function 2
TEST(TrojanMapStudentTest, TSP2) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  std::vector<std::string> input{"6816193709", "1855143753", "6808171386", "269635440", "6807905595", "7861033565", "1841883212", "6807553006", "4012842267"}; // Input location ids 
  auto result = m.TravellingTrojan(input);
  std::cout << "My path length: " <<result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"6816193709", "7861033565", "6808171386", "6807553006", "4012842267", "1841883212", "1855143753", "269635440", "6807905595", "6816193709"}; // Expected order
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the groundtruth path lengths
  bool flag = false;
  // for(auto &loc : result.second[result.second.size()-1]){
  //   std::cout << loc << ", ";
  // }
  // std::cout << std::endl;
  if (gt == result.second[result.second.size()-1]) // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (gt == result.second[result.second.size()-1]) // counterclockwise
    flag = true;
  
  EXPECT_EQ(flag, true);
}

// Test TSP function 3
TEST(TrojanMapStudentTest, TSP3) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  std::vector<std::string> input{"63068643", "5690152759", "7883578758", "1855143760", "2613117877", "5261316289", "4012541087", "1790748064", "2193435037", "4015486535", "6813379501", "4015203134"}; // Input location ids 
  auto result = m.TravellingTrojan(input);
  std::cout << "My path length: " << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"63068643", "1855143760", "2193435037", "2613117877", "4015203134", "5261316289", "5690152759", "4012541087", "1790748064", "4015486535", "7883578758", "6813379501", "63068643"}; // Expected order
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the groundtruth path lengths
  bool flag = false;
  // for(auto &loc : result.second[result.second.size()-1]){
  //   std::cout << loc << ", ";
  // }
  // std::cout << std::endl;
  if (gt == result.second[result.second.size()-1]) // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (gt == result.second[result.second.size()-1]) // counterclockwise
    flag = true;
  EXPECT_EQ(flag, true);
}


TEST(TrojanMapStudentTest, TopologicalSort1) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  std::vector<std::string> location_names = {"Cardinal Gardens", "Coffee Bean1", "CVS", "Target"};
  std::vector<std::vector<std::string>> dependencies = {{"Coffee Bean1", "CVS"}, {"Cardinal Gardens","CVS"}, {"Coffee Bean1","Target"}, {"CVS", "Target"}};
  auto result = m.DeliveringTrojan(location_names, dependencies);
  std::vector<std::string> gt1 ={"Cardinal Gardens", "Coffee Bean1","CVS", "Target"};
  std::vector<std::string> gt2 ={"Coffee Bean1","Cardinal Gardens","CVS", "Target"}; // have two start location without dependence
  bool flag = false;
  if(result == gt1) flag = true;
  else if(result == gt2) flag = true;
  else flag = false;
  EXPECT_EQ(flag, true);
}

TEST(TrojanMapStudentTest, TopologicalSort2) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  std::vector<std::string> location_names = {"Driveway", "University Park", "Holbox", "DASH F", "Leavey Library", "Ramen KenJo", "PED"};
  std::vector<std::vector<std::string>> dependencies = {{"Driveway", "PED"}, {"Driveway", "University Park"}, {"University Park", "Ramen KenJo"}, {"PED", "Ramen KenJo"}, {"PED", "Leavey Library"}, {"Ramen KenJo", "Leavey Library"}, {"Leavey Library", "DASH F"}, {"Leavey Library", "Holbox"}};
  auto result = m.DeliveringTrojan(location_names, dependencies);
  std::vector<std::string> gt1 ={"Driveway", "PED", "University Park,", "Ramen KenJo", "Leavey Library", "DASH F", "Holbox"};
  std::vector<std::string> gt2 ={"Driveway", "University Park", "PED", "Ramen KenJo", "Leavey Library", "DASH F", "Holbox"};
  std::vector<std::string> gt3 ={"Driveway", "University Park", "PED", "Ramen KenJo", "Leavey Library", "Holbox", "DASH F"};
  std::vector<std::string> gt4 ={"Driveway", "PED", "University Park", "Ramen KenJo", "Leavey Library", "Holbox", "DASH F"};
  // for(auto &loc : result){
  //   std::cout << loc << ", ";
  // }
  // std::cout << std::endl;
  bool flag = false;
  if(result == gt1) flag = true;
  else if(result == gt2) flag = true;
  else if(result == gt3) flag = true;
  else if(result == gt4) flag = true;
  else flag = false;
  EXPECT_EQ(flag, true);
}

TEST(TrojanMapStudentTest, TopologicalSort3) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  std::vector<std::string> location_names = {"7Eleven", "crosswalk3", "Metro 40", "DASH F", "Driveway", "Ramen KenJo", "PED", "Target", "CVS", "University Park", "Holbox", "Leavey Library"};
  std::vector<std::vector<std::string>> dependencies = {{"Driveway","Ramen KenJo"}, 
                                                        {"Driveway","crosswalk3"},
                                                        {"Driveway","PED"},
                                                        {"Ramen KenJo","PED"},
                                                        {"Ramen KenJo","Holbox"},
                                                        {"Ramen KenJo","Target"},
                                                        {"crosswalk3","Ramen KenJo"},
                                                        {"crosswalk3","University Park"},
                                                        {"PED","DASH F"},
                                                        {"Target","University Park"},
                                                        {"University Park","7Eleven"},
                                                        {"Target","CVS"},
                                                        {"7Eleven","CVS"},
                                                        {"DASH F","Leavey Library"},
                                                        {"DASH F","Holbox"},
                                                        {"Leavey Library","Holbox"},
                                                        {"CVS","Metro 40"},
                                                        {"Holbox","Metro 40"}};
  auto result = m.DeliveringTrojan(location_names, dependencies);
  std::vector<std::string> gt1 = {"Driveway", "crosswalk3", "Ramen KenJo", "Target", "University Park", "7Eleven", "CVS", "PED",  "DASH F", "Leavey Library", "Holbox", "Metro 40"};
  // std::vector<std::string> gt2 ={}; 
  for(auto &loc : result){
    std::cout << loc << ", ";
  }
  std::cout << std::endl;
  bool flag = false;
  if(result == gt1) flag = true;
  // else if(result == gt2) flag = true;
  // else flag = false;
  EXPECT_EQ(flag, true);
}

