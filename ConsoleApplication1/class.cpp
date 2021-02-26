#include <iostream>
#include <vector>
#include <map>
using namespace std;

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
