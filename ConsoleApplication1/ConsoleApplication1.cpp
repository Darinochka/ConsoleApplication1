#include <iostream>
#include <vector>
#include <map>
using namespace std;

enum class Lang {
  DE, FR, IT
};

struct Region {
  string std_name;
  string parent_std_name;
  map<Lang, string> names;
  int64_t population;
};

auto GetTuple(const Region& region) {
  return tie(region.std_name, region.parent_std_name, region.names, region.population);
}

bool operator<(const Region& lhs, const Region& rhs) {
    return GetTuple(lhs) < GetTuple(rhs);
}

map <int, Region> Reverse_Map(map<Region, int>& m) {
  map <int, Region> reverse_m;
  for (auto [key, value] : m) {
    reverse_m[value] = key;
    cout << "reverse: " << value << endl;
  }
  return reverse_m;
}

int FindMaxRepetitionCount(const vector<Region>& regions) {
  map <Region, int> region_counts;
  if (!regions.empty()) {
      for (auto& region : regions) {
          region_counts[region] += 1;
      }
      return Reverse_Map(region_counts).rbegin()->first;
  }
  return 0;
}

int main() {
  cout << FindMaxRepetitionCount({
      
  }) << endl;
  
  // cout << FindMaxRepetitionCount({
  //     {
  //         "Moscow",
  //         "Russia",
  //         {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
  //         89
  //     }, {
  //         "Russia",
  //         "Eurasia",
  //         {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
  //         89
  //     }, {
  //         "Moscow",
  //         "Russia",
  //         {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou deux"}, {Lang::IT, "Mosca"}},
  //         89
  //     }, {
  //         "Moscow",
  //         "Toulouse",
  //         {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
  //         89
  //     }, {
  //         "Moscow",
  //         "Russia",
  //         {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
  //         31
  //     },
  // }) << endl;
  
  return 0;
}