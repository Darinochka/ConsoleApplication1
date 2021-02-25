#include <iostream>
#include <vector>
#include <limits>
using namespace std;

int main() {
  uint32_t n;
  uint16_t w, d, h, r;
  uint64_t mass = 0;
  
  cin >> n >> r;
  for (auto i = 0; i < n; i++) {
    cin >> w >> d >> h;
    mass += static_cast<uint64_t>(w * d * h) * r;  
  }

  cout << mass;
  return 0;
}