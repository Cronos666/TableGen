#include <iostream>
#include <fstream>
#include <string>
#include <ranges>
#include <vector>

using namespace std;

  
int read_csv(string filename, char separator){

  ifstream F_input(filename);
  ofstream F_output(filename+".tex");

  F_output<<"\\begin{tabular}{c";

  string line;
  if (getline (F_input, line)){
    
    auto split = line | views::split(separator);
    vector<string_view> cells;
    for (const auto& cell : split){
      cells.emplace_back(cell.begin(), cell.end());
    }
    if (cells.empty()) return 0;
    for (size_t i=0; i<(cells.size()-1); i++){
      F_output<<"|c";
    }
    F_output<<"}\n";


    F_output<<cells.front();

    for (size_t i=1; i<(cells.size()); ++i){
      F_output<<" & "<<cells[i];
    }
    F_output<<"\\\n";

  }

  while (getline (F_input, line)) {

    
    auto split = line | views::split(separator);
    vector<string_view> cells;
    for (const auto& cell : split){
      cells.emplace_back(cell.begin(), cell.end());
    }
    if (cells.empty()) return 0;
    
    F_output <<"\\\\hline\n";
    F_output<<cells.front();

    for (size_t i=1; i<(cells.size()); ++i){
      F_output<<" & "<<cells[i];
    }
    F_output<<"\\\n";

    
    
    
  }
  F_output<<"\\end{tabular}\n";

  F_input.close();
  F_output.close();
  return 0;
}


int main(){

  read_csv("test.csv", ',');

  

  return 0;
}
