#include <iostream>
#include <cmath>
using namespace std;
#include <vector>
#include <algorithm>

int findOdd(const std::vector<int>& numbers){
  std::vector<int> averages;
  std::vector<int> odds;
  std::vector<int> check;
  if (numbers.size() == 1) return numbers.back();
  int avr;
  for (int i : numbers) {
    if (std::find(check.begin(), check.end(), i) == check.end()) {
      int rep = std::count(numbers.begin(), numbers.end(), i);
      if (averages.empty()) { avr = rep; averages.push_back(i); }
      else if (rep == avr) averages.push_back(i);
      else odds.push_back(i); 
      check.push_back(i);
    }
  }
  cout << odds.size();
  if (odds.size() == 1) { cout << "odds"; return odds.back();}
  return averages.back();
}
int main () {
	
	cout << (int)'A' << (int)'a';
}