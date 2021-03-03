#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>

using namespace std;

enum class QueryType {
  NewBus,
  BusesForStop,
  StopsForBus,
  AllBuses
};

struct Query {
  QueryType type;
  string bus;
  string stop;
  vector<string> stops;
};

istream& operator >> (istream& is, Query& q) {
  string OPERATION;
  is >> OPERATION;

  if (OPERATION == "NEW_BUS") {
    int stop_count;
    q.type = QueryType::NewBus;
    q.stops.clear();

    is >> q.bus >> stop_count;
    for (int i = 0; i < stop_count; i++) {
      string stop;
      is >> stop;
      q.stops.push_back(stop);
    }

  } else if (OPERATION == "BUSES_FOR_STOP"){
    q.type = QueryType::BusesForStop;
    is >> q.stop;

  } else if (OPERATION == "STOPS_FOR_BUS") {
    q.type = QueryType::StopsForBus;
    is >> q.bus;

  } else if (OPERATION == "ALL_BUSES") {
    q.type = QueryType::AllBuses;
  }

  return is;
}

struct BusesForStopResponse {
  vector <string> buses_to_stop;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
  if (!r.buses_to_stop.empty()) {
    for (auto stop : r.buses_to_stop) {
      os << stop << " "; 
    }
  } else {
    os << "No stop";
  }

  return os;
}

struct StopsForBusResponse {
  vector<string> stops_to_bus = {};
  vector<vector<string>> buses = {};
  string bus;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
  int iter = 0;
  if (!r.stops_to_bus.empty()) {
    for (auto stop : r.stops_to_bus) {
      os << "Stop " << stop << ": ";

      if (r.buses[iter].size() != 1) {
        for (auto bus : r.buses[iter]) {
          if (bus != r.bus) {
            os << bus << " ";
          }
        }
      } else {
        os << "no interchange";
      }
      iter += 1;
      if (iter != r.stops_to_bus.size()) {
        os << endl;
      }
    }
    
  } else {
    os << "No bus";
  }

  return os;
}

struct AllBusesResponse {
  map <string, vector<string>> buses_to_stops;
};

ostream& operator << (ostream& os, const AllBusesResponse& r) {
  int iter = 0;

  if (!r.buses_to_stops.empty()) {
    for (auto [key, value] : r.buses_to_stops) {
      iter += 1;

      os << "Bus " << key << ": ";
      for (auto stop : value) {
        os << stop << " ";
      }
      
      if (iter != r.buses_to_stops.size()) {
        os << endl;
      }     
    } 
    
  } else {
      os << "No buses";
  }

  return os;
}

class BusManager {
public:
    void AddBus(const string& bus, const vector<string>& stops) {
        buses_to_stops[bus] = stops;

        for (auto stop : stops) {
            stops_to_buses[stop].push_back(bus);
        }
    }

    BusesForStopResponse GetBusesForStop(const string& stop) const {
        BusesForStopResponse b;

        if (stops_to_buses.count(stop) > 0) {
            b.buses_to_stop = stops_to_buses.at(stop);
        }
        else {
            b.buses_to_stop = {};
        }

        return b;
    }

    StopsForBusResponse GetStopsForBus(const string& bus) const {
        StopsForBusResponse s;

        if (buses_to_stops.count(bus) > 0) {
            for (auto stop : buses_to_stops.at(bus)) {
                s.stops_to_bus.push_back(stop);
                s.buses.push_back(stops_to_buses.at(stop));
            }
            s.bus = bus;
        }

        return s;
    }

    AllBusesResponse GetAllBuses() const {
        AllBusesResponse a;
        a.buses_to_stops = buses_to_stops;
        return a;
    }
private:
    map<string, vector<string>> buses_to_stops = {}, stops_to_buses = {};
};

// Не меняя тела функции main, реализуйте функции и классы выше

int main() {
  int query_count;
  Query q;

  cin >> query_count;

  BusManager bm;
  for (int i = 0; i < query_count; ++i) {
    cin >> q;
    switch (q.type) {
    case QueryType::NewBus:
      bm.AddBus(q.bus, q.stops);
      break;
    case QueryType::BusesForStop:
      cout << bm.GetBusesForStop(q.stop) << endl;
      break;
    case QueryType::StopsForBus:
      cout << bm.GetStopsForBus(q.bus) << endl;
      break;
    case QueryType::AllBuses:
      cout << bm.GetAllBuses() << endl;
      break;
    }
  }

  return 0;
}
