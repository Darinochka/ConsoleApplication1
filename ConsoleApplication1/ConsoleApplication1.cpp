#include <iostream>
#include <vector>
#include <limits>
using namespace std;

int main() {
  int n, w, d, h, r;
  uint64_t mass = 0;
  
  cin >> n >> r;
  for (uint32_t i = 0; i < n; i++) {
    cin >> w >> d >> h;
    mass += static_cast<uint64_t>(w)* d * h;  
  }

  cout << mass * r;
  return 0;
}