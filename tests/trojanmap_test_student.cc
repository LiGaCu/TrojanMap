#include <map>
#include <vector>

#include "gtest/gtest.h"
#include "src/lib/trojanmap.h"

// Test Autocomplete function
TEST(TrojanMapTest, Autocomplete) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  // Test the simple case
  auto names = m.Autocomplete("Us");
  std::vector<std::string> gt1 = { "USC Fisher Museum of Art", "USC Parking", "USC Village Gym", "USC Village Dining Hall" }; // groundtruth for "Us"
  EXPECT_EQ(names, gt1);
  // Test the lower case
  names = m.Autocomplete("us");
  std::vector<std::string> gt2 = { "USC Fisher Museum of Art", "USC Parking", "USC Village Gym", "USC Village Dining Hall" }; // groundtruth for "us"
  EXPECT_EQ(names, gt2);
  // Test the lower and upper case 
  names = m.Autocomplete("uS"); 
  std::vector<std::string> gt3 = { "USC Fisher Museum of Art", "USC Parking", "USC Village Gym", "USC Village Dining Hall" }; // groundtruth for "us"
  EXPECT_EQ(names, gt3);
}

// Test FindPosition function
TEST(TrojanMapTest, FindPosition) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  // Test ChickfilA
  auto position = m.GetPosition("USC Village Gym");
  std::pair<double, double> gt1(34.0252392, -118.2858186); // groundtruth for "ChickfilA"
  EXPECT_EQ(position, gt1);
  // Test Ralphs
  position = m.GetPosition("Leavey Library");
  std::pair<double, double> gt2(34.0217677, -118.2828496); // groundtruth for "Ralphs"
  EXPECT_EQ(position, gt2);
  // Test Target
  position = m.GetPosition("Department of Motor Vehicles");
  std::pair<double, double> gt3(34.0180476, -118.2791616); // groundtruth for "Target"
  EXPECT_EQ(position, gt3);
}

// Test CalculateShortestPath_Dijkstra function 1
TEST(TrojanMapTest, CalculateShortestPath_Dijkstra) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  // Test from Ralphs to ChickfilA
  auto path = m.CalculateShortestPath_Dijkstra("Department of Motor Vehicles", "JeffersonUSC");
  std::vector<std::string> gt{ "4732965439", "1932939400", "7249047942", "123292049", "122470423", "4399914023", "4399914025", "1837202707", "1837202710", "1837202714", "4399914037", "4399914040", "1837202706", "123292047", "6939732877", "123292045", "123292100", "1378231753", "2193435032", "1841835270", "4011837222", "1841835282", "4400281328" }; // Expected path
  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
  
  // Reverse the input from Ralphs to ChickfilA
  path = m.CalculateShortestPath_Dijkstra("JeffersonUSC", "Department of Motor Vehicles");
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
  auto path = m.CalculateShortestPath_Dijkstra("JeffersonUSC", "Target");
  // Test from Target to Popeyes Louisiana Kitchen
  std::vector<std::string> gt{
    "4400281328","1841835282","4400281388","7930461030","4835551244",
    "123241967","5690152762","6813379534","4015372482","4015372483",
    "5690152760","123241965","6813379501","6787803628","6285409682",
    "6813379531","4141790934","123327636","6807200379","123327627",
    "6813379521","6813379517","6813379513","123005253","4399698008",
    "4399698009","123044712","4399698010","4399698011","4399698013",
    "4399698012","5237381975","6813379479","5237417650"};
  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
  
  // Reverse the input from Popeyes Louisiana Kitchen to Target
  path = m.CalculateShortestPath_Dijkstra( "Target","JeffersonUSC");
  std::reverse(gt.begin(),gt.end()); // Reverse the path

  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
}

// Test CalculateShortestPath_Dijkstra function 3
TEST(TrojanMapTest, CalculateShortestPath_Dijkstra3) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  auto path = m.CalculateShortestPath_Dijkstra("Ralphs", "Target");
  // Test from Target to Popeyes Louisiana Kitchen
  std::vector<std::string> gt{ "2578244375", "5559640911", "6787470571", "6808093910", "6808093913", "6808093919", "6816831441", "6813405269", "6816193784", "6389467806", "6816193783", "123178876", "2613117895", "122719259", "6807243574", "6807243576", "213332111", "441895337", "441895335", "122719255", "2613117893", "6813405231", "122719216", "6813405232", "4015372486", "7071032399", "4015372485", "6813379479", "5237417650" };
  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
  
  // Reverse the input from Popeyes Louisiana Kitchen to Target
  path = m.CalculateShortestPath_Dijkstra( "Target","Ralphs");
  std::reverse(gt.begin(),gt.end()); // Reverse the path

  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
}

// Test CalculateShortestPath_Bellman_Ford function 1
TEST(TrojanMapTest, CalculateShortestPath_Bellman_Ford) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  // Test from Ralphs to ChickfilA
  auto path = m.CalculateShortestPath_Bellman_Ford("Department of Motor Vehicles", "JeffersonUSC");
  std::vector<std::string> gt{ "4732965439", "1932939400", "7249047942", "123292049", "122470423", "4399914023", "4399914025", "1837202707", "1837202710", "1837202714", "4399914037", "4399914040", "1837202706", "123292047", "6939732877", "123292045", "123292100", "1378231753", "2193435032", "1841835270", "4011837222", "1841835282", "4400281328" }; // Expected path
  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
  
  // Reverse the input from Ralphs to ChickfilA
  path = m.CalculateShortestPath_Bellman_Ford("JeffersonUSC", "Department of Motor Vehicles");
  std::reverse(gt.begin(),gt.end()); // Reverse the path

  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
}

// Test CalculateShortestPath_Bellman_Ford function 2
TEST(TrojanMapTest, CalculateShortestPath_Bellman_Ford2) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  auto path = m.CalculateShortestPath_Bellman_Ford("JeffersonUSC", "Target");
  // Test from Target to Popeyes Louisiana Kitchen
  std::vector<std::string> gt{
    "4400281328","1841835282","4400281388","7930461030","4835551244",
    "123241967","5690152762","6813379534","4015372482","4015372483",
    "5690152760","123241965","6813379501","6787803628","6285409682",
    "6813379531","4141790934","123327636","6807200379","123327627",
    "6813379521","6813379517","6813379513","123005253","4399698008",
    "4399698009","123044712","4399698010","4399698011","4399698013",
    "4399698012","5237381975","6813379479","5237417650"};
  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
  
  // Reverse the input from Popeyes Louisiana Kitchen to Target
  path = m.CalculateShortestPath_Bellman_Ford( "Target","JeffersonUSC");
  std::reverse(gt.begin(),gt.end()); // Reverse the path

  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
}

// Test CalculateShortestPath_Bellman_Ford function 3
TEST(TrojanMapTest, CalculateShortestPath_Bellman_Ford3) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  auto path = m.CalculateShortestPath_Bellman_Ford("Ralphs", "Target");
  // Test from Target to Popeyes Louisiana Kitchen
  std::vector<std::string> gt{ "2578244375", "5559640911", "6787470571", "6808093910", "6808093913", "6808093919", "6816831441", "6813405269", "6816193784", "6389467806", "6816193783", "123178876", "2613117895", "122719259", "6807243574", "6807243576", "213332111", "441895337", "441895335", "122719255", "2613117893", "6813405231", "122719216", "6813405232", "4015372486", "7071032399", "4015372485", "6813379479", "5237417650" };
  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
  
  // Reverse the input from Popeyes Louisiana Kitchen to Target
  path = m.CalculateShortestPath_Bellman_Ford( "Target","Ralphs");
  std::reverse(gt.begin(),gt.end()); // Reverse the path

  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
}

// Test TSP function
TEST(TrojanMapTest, TSP) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  std::vector<std::string> input{"269635814","6813379442","6816288743","6807583648","4012726919","122719213","4015203128","6813379427","1614922635","1837212101","6437589508","1832234140"}; // Input location ids 
  auto result = m.TravellingTrojan(input);
  std::cout << "My path length: "  << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"269635814","6807583648","4012726919","1614922635","6816288743",
"1832234140","122719213","6813379427","6813379442","4015203128","6437589508","1837212101","269635814"}; // Expected order
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
TEST(TrojanMapTest, TSP2) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  std::vector<std::string> input{"4015405538","122817160","4400281325","123209602","6799196824","123009684","4015203136","63068643"}; // Input location ids  
  auto result = m.TravellingTrojan(input);
  std::cout << "My path length: " << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"4015405538","4400281325","6799196824","123209602","4015203136","63068643","122817160","123009684","4015405538"}; // Expected order
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the groundtruth path lengths
  bool flag = false;
  if (gt == result.second[result.second.size()-1]) // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (gt == result.second[result.second.size()-1]) // counterclockwise
    flag = true;
  EXPECT_EQ(flag, true);
}

// Test TSP function 3
TEST(TrojanMapTest, TSP3) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  std::vector<std::string> input{"6813379442","269635814","6816288743","4012726919","6813379427","122719213","4015203128","6807583648","1614922635","1837212101","6437589508","1832234140"}; // Input location ids 
  auto result = m.TravellingTrojan(input);
  std::cout << "My path length: " <<result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"6813379442","4015203128","6437589508","1837212101","269635814","6807583648","4012726919","1614922635","6816288743","1832234140","122719213","6813379427","6813379442"}; // Expected order
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the groundtruth path lengths
  bool flag = false;
  if (gt == result.second[result.second.size()-1]) // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (gt == result.second[result.second.size()-1]) // counterclockwise
    flag = true;
  
  EXPECT_EQ(flag, true);
}

// Test cycle detection function
TEST(TrojanMapTest, CycleDetection) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  // Test case 1
  std::vector<double> square1 = {-118.280, -118.270, 34.022, 34.015};
  bool result1 = m.CycleDetection(square1);
  EXPECT_EQ(result1, true);

  // Test case 2
  std::vector<double> square2 = {-118.291, -118.283, 34.022, 34.020};
  bool result2 = m.CycleDetection(square2);
  EXPECT_EQ(result2, false);

  // Test case 1
  std::vector<double> square3 = {-118.286, -118.280, 34.022, 34.021};
  bool result3 = m.CycleDetection(square3);
  EXPECT_EQ(result3, false);
}



// Test topological sort function
TEST(TrojanMapTest, TopologicalSort) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  std::vector<std::string> location_names = {"USC Village Gym","USC Village Dining Hall","Department of Motor Vehicles","Leavey Library","CVS"};
  std::vector<std::vector<std::string>> dependencies = {{"USC Village Gym","USC Village Dining Hall"},{"Department of Motor Vehicles","USC Village Gym"},{"Leavey Library","USC Village Gym"},{"Department of Motor Vehicles","CVS"}};
  auto result = m.DeliveringTrojan(location_names, dependencies);
  std::vector<std::string> gt ={"Leavey Library", "Department of Motor Vehicles","CVS","USC Village Gym","USC Village Dining Hall"};
  EXPECT_EQ(result, gt);

  location_names = {"USC Village Gym","USC Village Dining Hall","Department of Motor Vehicles","Leavey Library","CVS"};
  dependencies = {{"Leavey Library", "Department of Motor Vehicles"},{"Department of Motor Vehicles","USC Village Gym"},{"Department of Motor Vehicles","CVS"}};
  result = m.DeliveringTrojan(location_names, dependencies);
  gt ={ "Leavey Library", "Department of Motor Vehicles", "CVS", "USC Village Dining Hall", "USC Village Gym" };
  EXPECT_EQ(result, gt);

  location_names = {"USC Village Gym","USC Village Dining Hall","Department of Motor Vehicles","Leavey Library","CVS"};
  dependencies = {{ "USC Village Gym","USC Village Dining Hall"},{"USC Village Dining Hall","Department of Motor Vehicles"},{"Department of Motor Vehicles","Leavey Library"},{"Leavey Library","CVS"},{"CVS","USC Village Gym"}};
  result = m.DeliveringTrojan(location_names, dependencies);
  gt ={};
  EXPECT_EQ(result, gt);
}