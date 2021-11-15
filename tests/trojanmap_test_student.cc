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

//Test for GetPosition

TEST(TrojanMapTest, FindPosition) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  auto position = m.GetPosition("Tap Two Blue");
  std::pair<double, double> gt1(34.0311992,-118.2736016); 
  EXPECT_EQ(position, gt1);
  // Test Ralphs
  position = m.GetPosition("37th StreetUSC");
  std::pair<double, double> gt2(34.0177803,-118.2801096); // groundtruth for "Ralphs"
  EXPECT_EQ(position, gt2);
  // Test Target
  position = m.GetPosition("Security Checkpoint");
  std::pair<double, double> gt3(34.0257279,-118.2863862); // groundtruth for "Target"
  EXPECT_EQ(position, gt3);
  // Test Unknown
  position = m.GetPosition("XXY");
  std::pair<double, double> gt4(-1, -1);
  EXPECT_EQ(position, gt4);
}



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

TEST(TrojanMapTest, CalculateShortestPath_Dijkstra) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  // Test from Ralphs to ChickfilA
  auto path = m.CalculateShortestPath_Bellman_Ford("Ralphs", "ChickfilA");
  std::vector<std::string> gt{
      "2578244375", "5559640911", "6787470571", "6808093910", "6808093913", "6808093919", "6816831441",
      "6813405269", "6816193784", "6389467806", "6816193783", "123178876", "2613117895", "122719259",
      "2613117861", "6817230316", "3642819026", "6817230310", "7811699597", "5565967545", "123318572",
      "6813405206", "6813379482", "544672028", "21306059", "6813379476", "6818390140", "63068610", 
      "6818390143", "7434941012", "4015423966", "5690152766", "6813379440", "6813379466", "21306060",
      "6813379469", "6813379427", "123005255", "6807200376", "6807200380", "6813379451", "6813379463",
      "123327639", "6813379460", "4141790922", "4015423963", "1286136447", "1286136422", "4015423962",
      "6813379494", "63068643", "6813379496", "123241977", "4015372479", "4015372477", "1732243576",
      "6813379548", "4015372476", "4015372474", "4015372468", "4015372463", "6819179749", "1732243544",
      "6813405275", "348121996", "348121864", "6813405280", "1472141024", "6813411590", "216155217", 
      "6813411589", "1837212103", "1837212101", "6820935911", "4547476733"}; // Expected path
  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
  
  // Reverse the input from Ralphs to ChickfilA
  path = m.CalculateShortestPath_Dijkstra("ChickfilA", "Ralphs");
  std::reverse(gt.begin(),gt.end()); // Reverse the path

  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
}

// Test CalculateShortestPath_Dijkstra function 2
TEST(TrojanMapTest, CalculateShortestPath_Dijkstra2) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  auto path = m.CalculateShortestPath_Bellman_Ford("Target", "Popeyes Louisiana Kitchen");
  // Test from Target to Popeyes Louisiana Kitchen
  std::vector<std::string> gt{
      "5237417650", "6813379479", "5237381975", "4399698012", "4399698013", "4399698011", "4399698010", 
      "123044712", "4399698009", "4399698008", "123005253", "6813379513", "6813379517", "6813379521", 
      "123327627", "4399697999", "6813565290", "122719210", "6813379407", "2613117879", "6813379406", 
      "6807905595", "6787803635", "2613117867", "4835551110", "6813565296", "122719205", "6813565294", "4835551232", 
      "4835551104", "4012842272", "4835551103", "123178841", "6813565313", "122814435", "6813565311", "4835551228", 
      "6813513565", "4835551090", "4835551081", "6813513564", "20400292", "5556117120", "5556117115", "4835551064", 
      "4012842277", "6813565326", "123241961", "6813565322", "4835551070", "5695236164"}; // Expected path
  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
  
  // Reverse the input from Popeyes Louisiana Kitchen to Target
  path = m.CalculateShortestPath_Dijkstra("Popeyes Louisiana Kitchen", "Target");
  std::reverse(gt.begin(),gt.end()); // Reverse the path

  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
}