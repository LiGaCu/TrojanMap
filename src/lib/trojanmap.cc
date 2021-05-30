#include "trojanmap.h"
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <algorithm>
#include <fstream>
#include <locale>
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
#include <ncurses.h>
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
      "* 7. Exit                                                     \n"
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
    menu = "*************************Results******************************\n";
    std::cout << menu;
    if (results.size() != 0) {
      for (auto x : results) std::cout << x << std::endl;
      std::cout << "The distance of the path is:" << CalculatePathLength(results) << " miles" << std::endl;
      PlotPath(results);
    } else {
      std::cout << "No route from the start point to the destination."
                << std::endl;
    }
    menu = "**************************************************************\n";
    std::cout << menu;
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl << std::endl;
    PrintMenu();
    break;
  }
  case '4':
  {
    menu =
        "**************************************************************\n"
        "* 4. Travelling salesman problem                              \n"
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
    std::cout << "Calculating ..." << std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    auto results = TravellingTrojan(locations);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    CreateAnimation(results.second);
    menu = "*************************Results******************************\n";
    std::cout << menu;
    if (results.second.size() != 0) {
      for (auto x : results.second[results.second.size()-1]) std::cout << x << std::endl;
      menu = "**************************************************************\n";
      std::cout << menu;
      std::cout << "The distance of the path is:" << results.first << " miles" << std::endl;
      PlotPath(results.second[results.second.size()-1]);
    } else {
      std::cout << "The size of the path is 0" << std::endl;
    }
    menu = "**************************************************************\n"
           "You could find your animation at src/lib/output.avi.          \n";
    std::cout << menu;
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl << std::endl;
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
    std::cout << "Topological Sorting Reults:" << std::endl;
    for (auto x : result) std::cout << x << std::endl;
    std::vector<std::string> node_ids;
    for (auto x: result) {
      Node node = GetNode(x);
      node_ids.push_back(node.id);
    }
    PlotPointsOrder(node_ids);
    menu = "**************************************************************\n";
    std::cout << menu;
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl << std::endl;
    PrintMenu();
    break;
  }
  case '7':
    break;
  default:
  {
    std::cout << "Please select 1 - 7." << std::endl;
    PrintMenu();
    break;
  }
  }
}

bool TrojanMap::MyMenu(){
  std::string menu;
  initscr();     // Start curses mode
  start_color(); // Start color

  int  OFFSET_LEFT = 5;
  // Initialize some color pairs (foreground, background)
  init_pair(1, COLOR_RED, COLOR_BLACK);
  init_pair(2, COLOR_GREEN, COLOR_BLACK);
  init_pair(3, COLOR_YELLOW, COLOR_BLACK);

  attron(COLOR_PAIR(3)); // Change color
  menu = "                    TrojanMap by Jiatong Li                   \n";
  mvwprintw(stdscr, 0, OFFSET_LEFT, "%s", menu.c_str());
  menu = "**************************************************************\n";
  mvwprintw(stdscr, 1, OFFSET_LEFT, "%s", menu.c_str());
  menu = "* Select the function you want to execute.                    \n";
  mvwprintw(stdscr, 2, OFFSET_LEFT, "%s", menu.c_str());
  menu = "* 1. Autocomplete                                             \n";
  mvwprintw(stdscr, 3, OFFSET_LEFT, "%s", menu.c_str());
  menu = "* 2. Find the position                                        \n";
  mvwprintw(stdscr, 4, OFFSET_LEFT, "%s", menu.c_str());
  menu = "* 3. CalculateShortestPath                                    \n";
  mvwprintw(stdscr, 5, OFFSET_LEFT, "%s", menu.c_str());
  menu = "* 4. Travelling salesman problem                              \n";
  mvwprintw(stdscr, 6, OFFSET_LEFT, "%s", menu.c_str());
  menu = "* 5. Cycle Detection                                          \n";
  mvwprintw(stdscr, 7, OFFSET_LEFT, "%s", menu.c_str());
  menu = "* 6. Topological Sort                                         \n";
  mvwprintw(stdscr, 8, OFFSET_LEFT, "%s", menu.c_str());
  menu = "* 7. Exit                                                     \n";
  mvwprintw(stdscr, 9, OFFSET_LEFT, "%s", menu.c_str());
  menu = "**************************************************************\n";
  mvwprintw(stdscr, 10, OFFSET_LEFT, "%s", menu.c_str());
  move(11,OFFSET_LEFT);
  refresh(); // Print it on to the real screen
  
  char selectItem;
  selectItem = getch();
  switch(selectItem){
    case '1':{
      clear();
      menu = "**************************************************************\n";
      mvwprintw(stdscr, 0, OFFSET_LEFT, "%s", menu.c_str());
      menu = "* 1. Autocomplete                                             \n";
      mvwprintw(stdscr, 1, OFFSET_LEFT, "%s", menu.c_str());
      menu = "**************************************************************\n";
      mvwprintw(stdscr, 2, OFFSET_LEFT, "%s", menu.c_str());
      
      menu = "Please input a partial location:";
      int x,y;
      getyx(stdscr,y,x);
      mvwprintw(stdscr, y, OFFSET_LEFT, "%s", menu.c_str());
      refresh();
      char input_c_arr [256];
      getstr(input_c_arr);
      std::string input(input_c_arr);
      auto start = std::chrono::high_resolution_clock::now();
      auto results = Autocomplete(input);
      auto stop = std::chrono::high_resolution_clock::now();
      auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
      menu = "*************************Results******************************\n";
      getyx(stdscr,y,x);
      mvwprintw(stdscr, y+1, OFFSET_LEFT, "%s", menu.c_str());
      if (results.size() != 0) {
        for (auto result : results) {
          getyx(stdscr,y,x);
          mvwprintw(stdscr, y, OFFSET_LEFT, "%s", result.c_str());
          move(y+1,0);
        }
      } else {
        std::string temp_str = "No matched locations.\n";
        getyx(stdscr,y,x);
        mvwprintw(stdscr, y, OFFSET_LEFT, "%s", temp_str.c_str());
      }
      menu = "**************************************************************\n";
      getyx(stdscr,y,x);
      mvwprintw(stdscr, y, OFFSET_LEFT, "%s", menu.c_str());
      std::ostringstream stringStream;
      stringStream << "Time taken by function: " << duration.count() << " microseconds\n\n";
      mvwprintw(stdscr, y+1, OFFSET_LEFT, "%s", stringStream.str().c_str());
      menu = "(Press Any Key to return main menu)";
      mvwprintw(stdscr, y+3, OFFSET_LEFT, "%s", menu.c_str());
      refresh();
      getch();
      break;
    }
    case '2':{
      clear();
      menu = "**************************************************************\n";
      mvwprintw(stdscr, 0, OFFSET_LEFT, "%s", menu.c_str());
      menu = "* 2. Find the position                                        \n";
      mvwprintw(stdscr, 1, OFFSET_LEFT, "%s", menu.c_str());
      menu = "**************************************************************\n";
      mvwprintw(stdscr, 2, OFFSET_LEFT, "%s", menu.c_str());

      menu = "Please input a location's full name:";
      int x,y;
      getyx(stdscr,y,x);
      mvwprintw(stdscr, y, OFFSET_LEFT, "%s", menu.c_str());
      refresh();
      char input_c_arr [256];
      getstr(input_c_arr);
      std::string input(input_c_arr);
      auto start = std::chrono::high_resolution_clock::now();
      auto results = GetPosition(input);
      auto stop = std::chrono::high_resolution_clock::now();
      auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
      menu = "*************************Results******************************\n";
      getyx(stdscr,y,x);
      mvwprintw(stdscr, y+1, OFFSET_LEFT, "%s", menu.c_str());
      if (results.first != -1) {
        std::ostringstream stringStream;
        stringStream << "Latitude: " << results.first
                  << " Longitude: " << results.second << std::endl;
        getyx(stdscr,y,x);
        mvwprintw(stdscr, y, OFFSET_LEFT, "%s", stringStream.str().c_str());
        PlotPoint(results.first, results.second);
      } else {
        std::string temp_str = "No matched locations.\n";
        getyx(stdscr,y,x);
        mvwprintw(stdscr, y, OFFSET_LEFT, "%s", temp_str.c_str());
      }
      menu = "**************************************************************\n";
      getyx(stdscr,y,x);
      mvwprintw(stdscr, y, OFFSET_LEFT, "%s", menu.c_str());
      std::ostringstream stringStream;
      stringStream << "Time taken by function: " << duration.count() << " microseconds\n\n";
      mvwprintw(stdscr, y+1, OFFSET_LEFT, "%s", stringStream.str().c_str());
      menu = "(Press Any Key to return main menu)";
      mvwprintw(stdscr, y+3, OFFSET_LEFT, "%s", menu.c_str());
      refresh();
      getch();
      break;
    }
    case '3':{
      clear();
      menu = "**************************************************************\n";
      mvwprintw(stdscr, 0, OFFSET_LEFT, "%s", menu.c_str());
      menu = "* 3. CalculateShortestPath                                    \n";
      mvwprintw(stdscr, 1, OFFSET_LEFT, "%s", menu.c_str());
      menu = "**************************************************************\n";
      mvwprintw(stdscr, 2, OFFSET_LEFT, "%s", menu.c_str());

      char searchEngine = '!';
      while(searchEngine!='1' && searchEngine!='2'){
        menu = "Please choose algorithm 1(Dijkstra) or 2(Bellman-Ford):";
        mvwprintw(stdscr, 4, OFFSET_LEFT, "%s", menu.c_str());
        searchEngine = getch();
      }
      menu = "Please input the start location:";
      int x,y;
      getyx(stdscr,y,x);
      mvwprintw(stdscr, y+1, OFFSET_LEFT, "%s", menu.c_str());
      refresh();
      char input_c_arr [256];
      getstr(input_c_arr);
      std::string input1(input_c_arr);
      menu = "Please input the destination:";
      getyx(stdscr,y,x);
      mvwprintw(stdscr, y, OFFSET_LEFT, "%s", menu.c_str());
      refresh();
      getstr(input_c_arr);
      std::string input2(input_c_arr);
      auto start = std::chrono::high_resolution_clock::now();
      std::vector<std::string> results;
      if(searchEngine=='1')
        results = CalculateShortestPath_Dijkstra(input1, input2);
      else
        results = CalculateShortestPath_Bellman_Ford(input1, input2);
      auto stop = std::chrono::high_resolution_clock::now();
      auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
      menu = "*************************Results******************************\n";
      getyx(stdscr,y,x);
      mvwprintw(stdscr, y+1, OFFSET_LEFT, "%s", menu.c_str());
      if (results.size() != 0) {
        menu = "The path is:\n";
        getyx(stdscr,y,x);
        mvwprintw(stdscr, y, OFFSET_LEFT, "%s", menu.c_str());
        for (auto result : results) {
          getyx(stdscr,y,x);
          mvwprintw(stdscr, y, OFFSET_LEFT, "%s", result.c_str());
          move(y+1,0);
        }
        std::ostringstream stringStream;
        stringStream << "The distance of the path is:" << CalculatePathLength(results) << " miles" << std::endl;
        getyx(stdscr,y,x);
        mvwprintw(stdscr, y, OFFSET_LEFT, "%s", stringStream.str().c_str());
        PlotPath(results);
      } else {
        menu = "No route from the start point to the destination.\n";
        getyx(stdscr,y,x);
        mvwprintw(stdscr, y, OFFSET_LEFT, "%s", menu.c_str());
      }
      menu = "**************************************************************\n";
      getyx(stdscr,y,x);
      mvwprintw(stdscr, y, OFFSET_LEFT, "%s", menu.c_str());
      std::ostringstream stringStream;
      stringStream << "Time taken by function: " << duration.count() << " microseconds\n\n";
      mvwprintw(stdscr, y+1, OFFSET_LEFT, "%s", stringStream.str().c_str());
      menu = "(Press Any Key to return main menu)";
      mvwprintw(stdscr, y+3, OFFSET_LEFT, "%s", menu.c_str());
      refresh();
      getch();
      break;
    }
    case '4':{
      clear();
      menu = "**************************************************************\n";
      mvwprintw(stdscr, 0, OFFSET_LEFT, "%s", menu.c_str());
      menu = "* 4. Travelling salesman problem                              \n";
      mvwprintw(stdscr, 1, OFFSET_LEFT, "%s", menu.c_str());
      menu = "**************************************************************\n";
      mvwprintw(stdscr, 2, OFFSET_LEFT, "%s", menu.c_str());
      menu = "In this task, we will select N random points on the map and \n";
      mvwprintw(stdscr, 3, OFFSET_LEFT, "%s", menu.c_str());
      menu = "you need to find the path to travel these points and back to \n";
      mvwprintw(stdscr, 4, OFFSET_LEFT, "%s", menu.c_str());
      menu = "the start point.\n\n";
      mvwprintw(stdscr, 5, OFFSET_LEFT, "%s", menu.c_str());

      char searchEngine = '!';
      while(searchEngine!='1' && searchEngine!='2' && searchEngine!='3'){
        menu = "1(Brute-Force) or 2(2-Opt) or 3(3-Opt)?:";
        mvwprintw(stdscr, 7, OFFSET_LEFT, "%s", menu.c_str());
        searchEngine = getch();
      }

      menu = "Please input the number of the places:";
      int x,y;
      getyx(stdscr,y,x);
      mvwprintw(stdscr, y+1, OFFSET_LEFT, "%s", menu.c_str());
      refresh();
      char input_c_arr [256];
      getstr(input_c_arr);
      std::string input(input_c_arr);
      int num = std::stoi(input);
      std::pair<double, std::vector<std::vector<std::string>>> results;
      
      std::vector<std::string> keys;
      for (auto x : data) {
        keys.push_back(x.first);
      }
      std::vector<std::string> locations;
      srand(time(NULL));
      for (int i = 0; i < num; i++)
        locations.push_back(keys[rand() % keys.size()]);
      PlotPoints(locations);
      menu = "Calculating ...";
      getyx(stdscr,y,x);
      mvwprintw(stdscr, y, OFFSET_LEFT, "%s", menu.c_str());
      refresh();
      auto start = std::chrono::high_resolution_clock::now();
      if(num>1){
        if(searchEngine=='1'){
          results = TravellingTrojan(locations);
        }else if(searchEngine=='2'){
          results = TravellingTrojan_2opt(locations);
        }else if(searchEngine=='3'){
          results = TravellingTrojan_3opt(locations);
        }
      }
      auto stop = std::chrono::high_resolution_clock::now();
      auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
      CreateAnimation(results.second);
      
      menu = "*************************Results******************************\n";
      getyx(stdscr,y,x);
      mvwprintw(stdscr, y+1, OFFSET_LEFT, "%s", menu.c_str());

      if (results.second.size() != 0) {
        for (auto result : results.second[results.second.size()-1]){
          getyx(stdscr,y,x);
          mvwprintw(stdscr, y, OFFSET_LEFT, "%s", result.c_str());
          move(y+1,0);
        }
        menu = "**************************************************************\n";
        getyx(stdscr,y,x);
        mvwprintw(stdscr, y, OFFSET_LEFT, "%s", menu.c_str());
        std::ostringstream stringStream;
        stringStream << "The distance of the path is:" << results.first << " miles" << std::endl;
        getyx(stdscr,y,x);
        mvwprintw(stdscr, y, OFFSET_LEFT, "%s", stringStream.str().c_str());
        PlotPath(results.second[results.second.size()-1]);
      } else {
        menu = "The size of the path is 0\n";
        getyx(stdscr,y,x);
        mvwprintw(stdscr, y, OFFSET_LEFT, "%s", menu.c_str());
      }
      getyx(stdscr,y,x);
      menu = "**************************************************************\n";      
      mvwprintw(stdscr, y, OFFSET_LEFT, "%s", menu.c_str());
      menu = "You could find your animation at src/lib/output001.avi.       \n";
      mvwprintw(stdscr, y+1, OFFSET_LEFT, "%s", menu.c_str());
      std::ostringstream stringStream;
      stringStream << "Time taken by function: " << duration.count() << " microseconds\n\n";
      mvwprintw(stdscr, y+2, OFFSET_LEFT, "%s", stringStream.str().c_str());
      menu = "(Press Any Key to return main menu)";
      mvwprintw(stdscr, y+4, OFFSET_LEFT, "%s", menu.c_str());
      refresh();
      getch();
      break;
    }
    case '5':{
      clear();
      menu = "**************************************************************\n";
      mvwprintw(stdscr, 0, OFFSET_LEFT, "%s", menu.c_str());
      menu = "* 5. Cycle Detection                                          \n";
      mvwprintw(stdscr, 1, OFFSET_LEFT, "%s", menu.c_str());
      menu = "**************************************************************\n";
      mvwprintw(stdscr, 2, OFFSET_LEFT, "%s", menu.c_str());

      int x,y;
      char input_c_arr [256];
      std::vector<double> square;

      getyx(stdscr,y,x);
      menu = "Please input the left bound longitude\n";
      mvwprintw(stdscr, y+1, OFFSET_LEFT, "%s", menu.c_str());
      menu = "(between -118.299 and -118.264):";
      mvwprintw(stdscr, y+2, OFFSET_LEFT, "%s", menu.c_str());
      refresh();
      getstr(input_c_arr);
      std::string input(input_c_arr);
      square.push_back(atof(input.c_str()));

      getyx(stdscr,y,x);
      menu = "Please input the right bound longitude\n";
      mvwprintw(stdscr, y+1, OFFSET_LEFT, "%s", menu.c_str());
      menu = "(between -118.299 and -118.264):";
      mvwprintw(stdscr, y+2, OFFSET_LEFT, "%s", menu.c_str());
      refresh();
      getstr(input_c_arr);
      input = std::string(input_c_arr);
      square.push_back(atof(input.c_str()));

      getyx(stdscr,y,x);
      menu = "Please input the upper bound latitude\n";
      mvwprintw(stdscr, y+1, OFFSET_LEFT, "%s", menu.c_str());
      menu = "(between 34.011 and 34.032):";
      mvwprintw(stdscr, y+2, OFFSET_LEFT, "%s", menu.c_str());
      refresh();
      getstr(input_c_arr);
      input = std::string(input_c_arr);
      square.push_back(atof(input.c_str()));

      getyx(stdscr,y,x);
      menu = "Please input the lower bound latitude\n";
      mvwprintw(stdscr, y+1, OFFSET_LEFT, "%s", menu.c_str());
      menu = "(between 34.011 and 34.032):";
      mvwprintw(stdscr, y+2, OFFSET_LEFT, "%s", menu.c_str());
      refresh();
      getstr(input_c_arr);
      input = std::string(input_c_arr);
      square.push_back(atof(input.c_str()));

      auto start = std::chrono::high_resolution_clock::now();
      auto results = CycleDetection(square);
      auto stop = std::chrono::high_resolution_clock::now();
      auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
      menu = "*************************Results******************************\n";
      getyx(stdscr,y,x);
      mvwprintw(stdscr, y+1, OFFSET_LEFT, "%s", menu.c_str());
      if (results == true){
        std::ostringstream stringStream;
        stringStream << "there exists cycle in the subgraph " << std::endl;
        getyx(stdscr,y,x);
        mvwprintw(stdscr, y, OFFSET_LEFT, "%s", stringStream.str().c_str());
        PlotPointsandEdges(circle_ids,square);
      }else{
        std::ostringstream stringStream;
        stringStream << "there exist no cycle in the subgraph " << std::endl;
        getyx(stdscr,y,x);
        mvwprintw(stdscr, y, OFFSET_LEFT, "%s", stringStream.str().c_str());
      }
      menu = "**************************************************************\n";
      getyx(stdscr,y,x);
      mvwprintw(stdscr, y, OFFSET_LEFT, "%s", menu.c_str());
      std::ostringstream stringStream;
      stringStream << "Time taken by function: " << duration.count() << " microseconds\n\n";
      mvwprintw(stdscr, y+1, OFFSET_LEFT, "%s", stringStream.str().c_str());
      menu = "(Press Any Key to return main menu)";
      mvwprintw(stdscr, y+3, OFFSET_LEFT, "%s", menu.c_str());
      refresh();
      getch();
      break;
    }
    case '6':{
      clear();
      menu = "**************************************************************\n";
      mvwprintw(stdscr, 0, OFFSET_LEFT, "%s", menu.c_str());
      menu = "* 6. Topological Sort                                         \n";
      mvwprintw(stdscr, 1, OFFSET_LEFT, "%s", menu.c_str());
      menu = "**************************************************************\n";
      mvwprintw(stdscr, 2, OFFSET_LEFT, "%s", menu.c_str());
      
      int x,y;
      char input_c_arr [256];

      menu = "Please input the locations filename:\n";
      getyx(stdscr,y,x);
      mvwprintw(stdscr, y, OFFSET_LEFT, "%s", menu.c_str());
      refresh();
      move(y+1,OFFSET_LEFT);
      getstr(input_c_arr);
      std::string locations_filename(input_c_arr);

      menu = "Please input the dependencies filename:\n";
      getyx(stdscr,y,x);
      mvwprintw(stdscr, y+1, OFFSET_LEFT, "%s", menu.c_str());
      refresh();
      move(y+2,OFFSET_LEFT);
      getstr(input_c_arr);
      std::string dependencies_filename(input_c_arr);

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

      auto start = std::chrono::high_resolution_clock::now();
      auto result = DeliveringTrojan(location_names, dependencies);
      auto stop = std::chrono::high_resolution_clock::now();
      auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
      menu = "*************************Results******************************\n";
      getyx(stdscr,y,x);
      mvwprintw(stdscr, y+1, OFFSET_LEFT, "%s", menu.c_str());
      menu = "Topological Sorting Reults:\n";
      mvwprintw(stdscr, y+2, OFFSET_LEFT, "%s", menu.c_str());

      std::vector<std::string> node_ids;
      if(result.size()!=0){
        for (auto n : result){
            getyx(stdscr,y,x);
            mvwprintw(stdscr, y, OFFSET_LEFT, "%s", n.c_str());
            move(y+1,0);

            Node node = GetNode(n);
            node_ids.push_back(node.id);
        }
        PlotPointsOrder(node_ids);
      }else{
        menu = "There is no feasible topological sort\n";
        getyx(stdscr,y,x);
        mvwprintw(stdscr, y, OFFSET_LEFT, "%s", menu.c_str());
      }
      
      menu = "**************************************************************\n";
      getyx(stdscr,y,x);
      mvwprintw(stdscr, y, OFFSET_LEFT, "%s", menu.c_str());
      std::ostringstream stringStream;
      stringStream << "Time taken by function: " << duration.count() << " microseconds\n\n";
      mvwprintw(stdscr, y+1, OFFSET_LEFT, "%s", stringStream.str().c_str());
      menu = "(Press Any Key to return main menu)";
      mvwprintw(stdscr, y+3, OFFSET_LEFT, "%s", menu.c_str());
      refresh();
      getch();
      break;
    }
    case '7':{
      clear();
      endwin();  // End curses mode
      return false;
    }
    default:
    {
      menu = "Please select 1 - 7. (Press Any Key to Re-select)";
      int x,y;
      getyx(stdscr,y,x);
      mvwprintw(stdscr, y, OFFSET_LEFT, "%s", menu.c_str());
      refresh(); // Print it on to the real screen
      getch();
      break;
    }
  }
  clear();
  endwin();  // End curses mode
  return true;
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
    while (getline(s, word, ',')) {
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
  cv::startWindowThread();
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
  cv::startWindowThread();
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
  cv::startWindowThread();
  cv::imshow("TrojanMap", img);
  cv::waitKey(1);
}


/**
 * CreateAnimation: Create the videos of the progress to get the path
 * 
 * @param  {std::vector<std::vector<std::string>>} path_progress : the progress to get the path
 */
void TrojanMap::CreateAnimation(std::vector<std::vector<std::string>> path_progress){
  cv::VideoWriter video("src/lib/output001.avi", cv::VideoWriter::fourcc('M','J','P','G'), 10, cv::Size(1248,992));
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
    cv::startWindowThread();
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
    return data.count(id)==0?-1:data[id].lat;
}


/**
 * GetLon: Get the longitude of a Node given its id. 
 * 
 * @param  {std::string} id : location id
 * @return {double}         : longitude
 */
double TrojanMap::GetLon(std::string id) { 
    return data.count(id)==0?-1:data[id].lon;
}

/**
 * GetName: Get the name of a Node given its id.
 * 
 * @param  {std::string} id : location id
 * @return {std::string}    : name
 */
std::string TrojanMap::GetName(std::string id) { 
    return data.count(id)==0?"":data[id].name;
}

/**
 * GetNeighborIDs: Get the neighbor ids of a Node.
 * 
 * @param  {std::string} id            : location id
 * @return {std::vector<std::string>}  : neighbor ids
 */
std::vector<std::string> TrojanMap::GetNeighborIDs(std::string id) {
    return data.count(id)==0?std::vector<std::string>() : data[id].neighbors;
}

/**
 * CalculateDistance: Get the distance between 2 nodes. 
 * 
 * @param  {Node} a  : node a
 * @param  {Node} b  : node b
 * @return {double}  : distance in mile
 */
double TrojanMap::CalculateDistance(const Node &a, const Node &b) {
  // Do not change this function
  // TODO: Use Haversine Formula:
  // dlon = lon2 - lon1;
  // dlat = lat2 - lat1;
  // a = (sin(dlat / 2)) ^ 2 + cos(lat1) * cos(lat2) * (sin(dlon / 2)) ^ 2;
  // c = 2 * arcsin(min(1, sqrt(a)));
  // distances = 3961 * c;

  // where 3961 is the approximate radius of the earth at the latitude of
  // Washington, D.C., in miles
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
  if(path.size()<2 || data.count(path[0])==0) return 0;

  double sum = 0;
  for(auto it=path.begin()+1;it!=path.end();it++){
    if(data.count(*it)==0) return 0;
    sum += CalculateDistance(data[*(it-1)],data[*it]);
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
std::vector<std::string> TrojanMap::Autocomplete(std::string name){
  if(name=="") return {};

  std::transform(name.begin(), name.end(), name.begin(),[](unsigned char c){ return std::tolower(c); });

  if(!getNodebyNamePopulated){
    for(auto &node:data){
      if(node.second.name != ""){
        getNodebyNameMap[node.second.name] = node.second;
      }
    }
    getNodebyNamePopulated = true;
  }

  std::vector<std::string> results;
  for(auto &node:getNodebyNameMap){
    if(WordBeginWith(node.first,name))
      results.push_back(node.first);
  }
  return results;
}

/**
 * GetPosition: Given a location name, return the position.
 *
 * @param  {std::string} name          : location name
 * @return {std::pair<double,double>}  : (lat, lon)
 */
std::pair<double, double> TrojanMap::GetPosition(std::string name) {
  Node n = GetNode(name);

  if(n.id=="") return std::pair<double, double>(-1,-1);
  return std::pair<double, double>(n.lat,n.lon);
}

/**
 * GetNode: Given a location name, return the node.
 *
 * @param  {std::string} name          : location name
 * @return {Node}  : node
 */
Node TrojanMap::GetNode(std::string name) {
  if(!getNodebyNamePopulated){
    for(auto &node:data){
      if(node.second.name != ""){
        getNodebyNameMap[node.second.name] = node.second;
      }
    }
    getNodebyNamePopulated = true;
  }

  Node n;
  n.id = "";
  return getNodebyNameMap.count(name)==0?n:getNodebyNameMap[name];
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
  
  Node n1 = GetNode(location1_name);
  Node n2 = GetNode(location2_name);
  if(n1.id=="" || n2.id=="") return {};
  if(n1.id == n2.id) return {n1.id};
  typedef std::pair<std::string,double> node_dist;
  auto comp = []( node_dist a, node_dist b ) { return a.second > b.second; };
  typedef std::priority_queue<node_dist,std::vector<node_dist>,decltype(comp)> mypq_type;

  mypq_type min_heap(comp);
  std::unordered_map<std::string,double> distTo;
  std::unordered_map<std::string,std::string> ParentIs;
  std::unordered_set<std::string> seen;

  min_heap.push(node_dist(n1.id,0));
  distTo[n1.id] = 0;
  while(!min_heap.empty()){
    // Discard the ones already processed
    while(seen.count(min_heap.top().first)){
      min_heap.pop();
    }
    node_dist curr_node_dist = min_heap.top();
    min_heap.pop();
    seen.insert(curr_node_dist.first);
    if(curr_node_dist.first == n2.id)
      break;

    Node curr_node = data[curr_node_dist.first];
    for(std::string& adj:curr_node.neighbors){
      if(data.count(adj) == 0)
        continue; // In case there is no such Node, invalid data point
      double dist_between = CalculateDistance(curr_node, data[adj]);
      if(distTo.count(adj)==0 || distTo[adj] > dist_between+distTo[curr_node.id] ){
        distTo[adj] = dist_between+distTo[curr_node.id];
        ParentIs[adj] = curr_node.id;
        min_heap.push(node_dist(adj,distTo[adj]));
      }
    }
  }
  if(ParentIs.count(n2.id)==0)  return {};

  std::vector<std::string> path;
  std::string id_pointer = n2.id;
  while(id_pointer!=n1.id){
    path.push_back(id_pointer);
    id_pointer = ParentIs[id_pointer];
  }
  path.push_back(id_pointer);

  std::reverse(path.begin(), path.end());
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
std::vector<std::string> TrojanMap::CalculateShortestPath_Bellman_Ford(
    std::string location1_name, std::string location2_name){

  Node n1 = GetNode(location1_name);
  Node n2 = GetNode(location2_name);
  if(n1.id=="" || n2.id=="") return {};
  if(n1.id == n2.id) return {n1.id};

  std::unordered_map<std::string,double> weight_map;
  std::unordered_map<std::string,double> distTo;
  std::unordered_map<std::string,std::string> ParentIs;

  distTo[n1.id] = 0;
  bool changed = true;
  int time = 0;
  while(changed && time<data.size()-1){
    time++;
    changed = false;
    for(auto &node_dist:distTo){
      Node curr_node = data[node_dist.first];
      for(std::string &adj:curr_node.neighbors){
        if(data.count(adj) == 0)
          continue; // In case there is no such Node, invalid data point

        // Generate key for the Link Weight Map
        std::string weight_map_key = curr_node.id;
        weight_map_key.append(",");
        weight_map_key.append(adj);

        if(weight_map.count(weight_map_key)==0){
          // Generate another key for the Link Weight Map
          std::string key_alt = adj;
          key_alt.append(",");
          key_alt.append(curr_node.id);
          weight_map[weight_map_key] = CalculateDistance(curr_node, data[adj]);
          weight_map[key_alt] = weight_map[weight_map_key];
        }

        if(distTo.count(adj)==0 || distTo[adj] > weight_map[weight_map_key]+distTo[curr_node.id] ){
          distTo[adj] = weight_map[weight_map_key] + distTo[curr_node.id];
          ParentIs[adj] = curr_node.id;
          changed = true;
        }
      }
    }
  }
  
  if(ParentIs.count(n2.id)==0)  return {};

  std::vector<std::string> path;
  std::string id_pointer = n2.id;
  while(id_pointer!=n1.id){
    path.push_back(id_pointer);
    id_pointer = ParentIs[id_pointer];
  }
  path.push_back(id_pointer);

  std::reverse(path.begin(), path.end());
  return path;
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
  std::string line;

  getline(fin, line);
  while (getline(fin, line)) {
    line.erase(std::remove(line.begin(),line.end(),','), line.end());
    if(line!="")
      location_names_from_csv.push_back(line);
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
  std::string line;

  getline(fin, line);
  while (getline(fin, line)) {
    std::string firstpos , secondpos;
    auto pos = line.find(',');
    if(pos==-1 || pos==0 || pos==line.size()-1) continue;
    firstpos = line.substr(0,pos);
    secondpos = line.substr(pos+1);
    secondpos.erase(std::remove(secondpos.begin(),secondpos.end(),','), secondpos.end());
    dependencies_from_csv.push_back({firstpos,secondpos});
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
  // Create Ajacency Vector
  std::unordered_map<std::string,std::vector<std::string>> adjacencies;
  for(auto &location:locations){
    adjacencies[location] = std::vector<std::string>();
  }
  for(auto &edge:dependencies){
    if(adjacencies.count(edge[0])==0 || adjacencies.count(edge[1])==0)
      return {};
    adjacencies[edge[0]].push_back(edge[1]);
  }

  std::vector<std::string> result;
  std::unordered_map<std::string,int> seen;
  for(auto &location:locations){
    seen[location] = 0;
  }
  for(auto &location:locations){
    if(seen[location]==0 && !DeliveringTrojan_helper(location,adjacencies,seen,result))
      return {};
  }
  std::reverse(result.begin(),result.end());

  return result;                                                     
}

/**
 * Travelling salesman problem: Given a list of locations, return the shortest
 * path which visit all the places and back to the start point.
 *
 * @param  {std::vector<std::string>} input : a list of locations needs to visit
 * @return {std::pair<double, std::vector<std::vector<std::string>>} : a pair of total distance and the all the progress to get final path
 */
std::pair<double, std::vector<std::vector<std::string>>> TrojanMap::TravellingTrojan(
                                    std::vector<std::string> &location_ids) {
  // std::unordered_set<std::string> rmDuplicate(location_ids.begin(),location_ids.end());
  // location_ids = std::vector<std::string>(rmDuplicate.begin(),rmDuplicate.end());

  std::pair<double, std::vector<std::vector<std::string>>> results;
  if(location_ids.size()<2) return results;

  std::vector<std::vector<double>> weights(location_ids.size(),std::vector<double>(location_ids.size()));
  for(auto i=0;i<location_ids.size();i++){
    for(auto j=i+1;j<location_ids.size();j++){
      weights[i][j] = CalculateDistance(data[location_ids[i]],data[location_ids[j]]);
      weights[j][i] = weights[i][j];
    }
  }
  std::vector<std::vector<std::string>> allPath;
  double minDist = DBL_MAX;
  std::vector<int> currPath;
  std::unordered_set<int> seen;
  currPath.push_back(0);
  seen.insert(0);

  TravellingTrojan_helper(location_ids,weights,allPath,minDist,currPath,0,seen);
  return std::pair<double, std::vector<std::vector<std::string>>>(minDist,allPath);
}

std::pair<double, std::vector<std::vector<std::string>>> TrojanMap::TravellingTrojan_2opt(
      std::vector<std::string> &location_ids){
  std::pair<double, std::vector<std::vector<std::string>>> results;
  if(location_ids.size()<2) return results;

  std::vector<std::vector<std::string>> allPath;
  std::vector<std::string> currPath;
  for(std::string &location:location_ids)
    currPath.push_back(location);
  currPath.push_back(location_ids[0]);
  double minDist = CalculatePathLength(currPath);
  allPath.push_back(currPath);

  bool stop = false;
  while(!stop){
    stop = true;
    // currPath has at least three nodes
    for(auto i=1;i<currPath.size()-1;i++){
      for(auto k=i+1;k<currPath.size();k++){
        std::reverse(currPath.begin()+i,currPath.begin()+k);
        double currDist = CalculatePathLength(currPath);
        if(currDist<minDist){
          minDist = currDist;
          allPath.push_back(currPath);
          stop = false;
        }else{
          // Recover the change on the original path
          std::reverse(currPath.begin()+i,currPath.begin()+k);
        }
      }
    }
  }
  return std::pair<double, std::vector<std::vector<std::string>>>(minDist,allPath);
}

std::pair<double, std::vector<std::vector<std::string>>> TrojanMap::TravellingTrojan_3opt(
      std::vector<std::string> &location_ids){
  std::pair<double, std::vector<std::vector<std::string>>> results;
  if(location_ids.size()<2) return results;

  std::vector<std::vector<std::string>> allPath;
  std::vector<std::string> currPath;
  for(std::string &location:location_ids)
    currPath.push_back(location);
  currPath.push_back(location_ids[0]);
  double minDist = CalculatePathLength(currPath);
  allPath.push_back(currPath);

  int l = currPath.size();

  bool stop = false;
  while(!stop){
    stop = true;
    // currPath has at least three nodes
    for(auto i=0;i<l-3;i++){
      for(auto j=i+1;j<l-2;j++){
        int k = l - 2;
        std::vector<std::string> partA(currPath.begin(),currPath.begin()+i+1);
        std::vector<std::string> partB(currPath.begin()+i+1,currPath.begin()+j+1);
        std::vector<std::string> partC(currPath.begin()+j+1,currPath.begin()+k+1);

        int whichone = 0;
        std::vector<std::string> newPath1;
        newPath1.insert(newPath1.end(),partA.begin(),partA.end());
        newPath1.insert(newPath1.end(),partC.begin(),partC.end());
        newPath1.insert(newPath1.end(),partB.begin(),partB.end());
        newPath1.push_back(newPath1[0]);
        double newDist1 = CalculatePathLength(newPath1);
        if(newDist1<minDist){
          whichone = 1;
          minDist = newDist1;
        }
        std::vector<std::string> newPath2;
        newPath2.insert(newPath2.end(),partA.begin(),partA.end());
        newPath2.insert(newPath2.end(),partC.begin(),partC.end());
        newPath2.insert(newPath2.end(),partB.begin(),partB.end());
        std::reverse(newPath2.begin()+j+1,newPath2.begin()+k+1);
        newPath2.push_back(newPath2[0]);
        double newDist2 = CalculatePathLength(newPath2);
        if(newDist2<minDist){
          whichone = 2;
          minDist = newDist2;
        }
        std::vector<std::string> newPath3;
        newPath3.insert(newPath3.end(),partA.begin(),partA.end());
        newPath3.insert(newPath3.end(),partC.begin(),partC.end());
        newPath3.insert(newPath3.end(),partB.begin(),partB.end());
        std::reverse(newPath3.begin()+i+1,newPath3.begin()+j+1);
        newPath3.push_back(newPath3[0]);
        double newDist3 = CalculatePathLength(newPath3);
        if(newDist3<minDist){
          whichone = 3;
          minDist = newDist3;
        }
        std::vector<std::string> newPath4;
        newPath4.insert(newPath4.end(),partA.begin(),partA.end());
        newPath4.insert(newPath4.end(),partC.begin(),partC.end());
        newPath4.insert(newPath4.end(),partB.begin(),partB.end());
        std::reverse(newPath4.begin()+i+1,newPath4.begin()+k+1);
        newPath4.push_back(newPath4[0]);
        double newDist4 = CalculatePathLength(newPath4);
        if(newDist4<minDist){
          whichone = 4;
          minDist = newDist4;
        }
        std::vector<std::string> newPath5;
        newPath5.insert(newPath5.end(),partA.begin(),partA.end());
        newPath5.insert(newPath5.end(),partB.begin(),partB.end());
        newPath5.insert(newPath5.end(),partC.begin(),partC.end());
        std::reverse(newPath5.begin()+j+1,newPath5.begin()+k+1);
        newPath5.push_back(newPath5[0]);
        double newDist5 = CalculatePathLength(newPath5);
        if(newDist5<minDist){
          whichone = 5;
          minDist = newDist5;
        }
        std::vector<std::string> newPath6;
        newPath6.insert(newPath6.end(),partA.begin(),partA.end());
        newPath6.insert(newPath6.end(),partB.begin(),partB.end());
        newPath6.insert(newPath6.end(),partC.begin(),partC.end());
        std::reverse(newPath6.begin()+i+1,newPath6.begin()+j+1);
        newPath6.push_back(newPath6[0]);
        double newDist6 = CalculatePathLength(newPath6);
        if(newDist6<minDist){
          whichone = 6;
          minDist = newDist6;
        }
        std::vector<std::string> newPath7;
        newPath7.insert(newPath7.end(),partA.begin(),partA.end());
        newPath7.insert(newPath7.end(),partB.begin(),partB.end());
        newPath7.insert(newPath7.end(),partC.begin(),partC.end());
        std::reverse(newPath7.begin()+i+1,newPath7.begin()+j+1);
        std::reverse(newPath7.begin()+j+1,newPath7.begin()+k+1);
        newPath7.push_back(newPath7[0]);
        double newDist7 = CalculatePathLength(newPath7);
        if(newDist7<minDist){
          whichone = 7;
          minDist = newDist7;
        }
        switch (whichone)
        {
          case 1: currPath = std::move(newPath1);break;
          case 2: currPath = std::move(newPath2);break;
          case 3: currPath = std::move(newPath3);break;
          case 4: currPath = std::move(newPath4);break;
          case 5: currPath = std::move(newPath5);break;
          case 6: currPath = std::move(newPath6);break;
          case 7: currPath = std::move(newPath7);break;
        }
        if(whichone!=0){
          allPath.push_back(currPath);
          stop = false;
        }
      }
    }
  }
  return std::pair<double, std::vector<std::vector<std::string>>>(minDist,allPath);
}

/**
 * Cycle Detection: Given four points of the square-shape subgraph, return true if there
 * is a cycle path inside the square, false otherwise.
 * 
 * @param {std::vector<double>} square: four vertexes of the square area
 * @return {bool}: whether there is a cycle or not
 */
bool TrojanMap::CycleDetection(std::vector<double> &square) {
  if(square.size()<4) return false;
  std::vector<std::string> location_ids;
  for(auto &node:data){
    if(node.second.lon>=square[0] && node.second.lon<=square[1] && node.second.lat<=square[2] && node.second.lat>=square[3]){
      location_ids.push_back(node.first);
    }
  }
  // cv::startWindowThread();
  // PlotPointsandEdges(location_ids,square);
  circle_ids = location_ids;

  std::unordered_map<std::string,int> seen;
  for(auto &point:location_ids){
    seen[point] = 0;
  }
  for(auto &point:seen){
    if(point.second==0 && CycleDetection_helper(point.first,seen,""))
      return true;
  }
  return false;
}


//-----------------------------------------------------
// Belows are newly defined functions.
//-----------------------------------------------------
/*
 * To check if word begins with key. ( Word Case Insensitive. Key is Lowercase. ).
 */
bool TrojanMap::WordBeginWith(const std::string &word, const std::string &key){
  if(key.length()>word.length()) return false;
  
  for(int i = 0;i<key.length();i++){
    if(std::tolower(word[i])!=key[i])
      return false;
  }
  return true;
}

/*
 * Recursively run to help solve Travelling Sales Man Problem via Brute Force.
 */
void TrojanMap::TravellingTrojan_helper(
  std::vector<std::string> &location_ids,
  std::vector<std::vector<double>> &weights,
  std::vector<std::vector<std::string>> &allPath,
  double &minDist, 
  std::vector<int> &currPath,
  double currDist,
  std::unordered_set<int> &seen){

  // Arrive at the leaf
  if(currPath.size()==location_ids.size()){
    double finalDist = currDist + weights[currPath.back()][0];
    if(finalDist<minDist){
      std::vector<std::string> tempPath;
      for(auto i:currPath)
        tempPath.push_back(location_ids[i]);
      tempPath.push_back(location_ids[0]);
      allPath.push_back(std::move(tempPath));
      minDist = finalDist;
    }
  }

  // Early proning
  if(currDist>=minDist) return;

  for(auto i=1;i<location_ids.size();i++){
    if(seen.count(i)==0){
      seen.insert(i);
      double deltaDist = weights[currPath.back()][i];
      currPath.push_back(i);
      TravellingTrojan_helper(location_ids,weights,allPath,minDist,currPath,currDist+deltaDist,seen);
      currPath.pop_back();
      seen.erase(i);
    }
  }
}

/*
 * Recursively run to help solve Cycle Detection Problem.
 */
bool TrojanMap::CycleDetection_helper(const std::string &currID,std::unordered_map<std::string,int> &seen,const std::string &parentID){
  seen[currID] = 1;
  Node curr_Node = data[currID];
  for(std::string &adj:curr_Node.neighbors){
    if(data.count(adj) == 0 || seen.count(adj)==0 || adj==parentID)
      continue; // In case there is no such Node in the area, invalid data point
    if(seen[adj]==1 || (seen[adj]==0 && CycleDetection_helper(adj,seen,currID)))
      return true;
  }
  seen[currID] = 2;
  return false;
}
/*
 * Recursively run to help solve Cycle Detection Problem.
 * @return bool                       : true if success, false if there is a cycle and failed
 */
bool TrojanMap::DeliveringTrojan_helper(
  std::string &location,
  std::unordered_map<std::string,std::vector<std::string>> &adjacencies,
  std::unordered_map<std::string,int> &seen,std::vector<std::string> &result){
  seen[location] = 1;
  for(std::string &adj:adjacencies[location]){
    if(seen[adj]==1 || (seen[adj]==0 && DeliveringTrojan_helper(adj,adjacencies,seen,result)==false))
      return false;
  }
  seen[location] = 2;
  result.push_back(location);
  return true;
}

