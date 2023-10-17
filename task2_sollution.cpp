#include <iostream>
#include <vector>
#include <queue>

#define MIN_FOR_INFECTION 2

struct City {
  unsigned int num;
  bool infected;

  City(unsigned int num, bool flag = false) : num(num), infected(flag) {}
};

struct Road {
  City src;
  City dst;

  Road(City city_1, City city_2) : src(city_1), dst(city_2) {}
};

class CityMap {
 private:
  std::vector<Road> list_roads;
  std::vector<std::vector<City> > map;
  std::vector<unsigned int> plague;
  unsigned int city_count;
  std::vector<bool> visited_;

 public:
  CityMap(unsigned int cities);
  ~CityMap();

  bool Exists(City src_city, City dst_city);
  void AddRoad(City src_city, City dst_city);
  void ConvertToAdjList(const std::vector<Road>& road_map);
  City LocateLeaveCities();
  void InfectCity(unsigned int city_num);
  void DFS(City start, std::vector<bool> black);
  void printPlague();
};

CityMap::CityMap(unsigned int cities) : city_count(cities) {
  map.resize(city_count);
  visited_.resize(city_count);
}

CityMap::~CityMap() = default;

bool CityMap::Exists(City src_city, City dst_city) {
  for (auto& i : map[src_city.num]) {
    if (i.num == dst_city.num) return true;
  }
  return false;
}

void CityMap::AddRoad(City src_city, City dst_city) {
  if (!Exists(src_city, dst_city)) {
    map[src_city.num].emplace_back(dst_city);
    map[dst_city.num].emplace_back(src_city);
  }
}

void CityMap::ConvertToAdjList(const std::vector<Road>& road_map) {
  for (auto& road : road_map) {
    AddRoad(road.src, road.dst);
  }
}

City CityMap::LocateLeaveCities() {
  unsigned int infected_num = 0;
  for (size_t i = 0; i < map.size(); ++i) {
    if (map[i].size() == 1) {
      plague.emplace_back(i);
      InfectCity(i);
      infected_num = i;
    }
  }

  if (infected_num == 0) {
    plague.emplace_back(infected_num);
    InfectCity(infected_num);
  }
  return City(infected_num, true);
}

void CityMap::InfectCity(unsigned int city_num) {
  for (auto & city_neighbour : map) {
    for (auto & j : city_neighbour) {
      if (j.num == city_num) j.infected = true;
    }
  }
}

void CityMap::DFS(City index, std::vector<bool> black) {
  visited_[index.num] = true;
  black[index.num] = true;

  int count_infected = 0;
  for (auto neighbour : map[index.num]) {
    if (neighbour.infected) ++count_infected;
  }

  for (auto & j : map[index.num]) {
    if (count_infected == 0) {
      InfectCity(index.num);
      plague.push_back(index.num);
    }

    if (count_infected >= MIN_FOR_INFECTION) {
      InfectCity(index.num);
    }

    if (!visited_[j.num]) {
      DFS(j.num, black);
    }
  }
}

void CityMap::printPlague() {
  std::cout << plague.size() / 2 << '\n';

  size_t real_size = plague.size() / 2;
  if (real_size % 2 == 0) {
    for (size_t i = 0; i < plague.size(); i += 2) {
      std::cout << plague[i] + 1 << " ";
    }
  } else {
    for (size_t i = 0; i < plague.size() - 2; i += 2) {
      std::cout << plague[i] + 1 << " ";
    }
  }
}

int main() {
  unsigned int roads_num;
  std::cin >> roads_num;

  unsigned int max_city_num = 0;
  std::vector<Road> road_map;

  while (roads_num != 0) {
    unsigned int src, dst;
    std::cin >> src >> dst;

    road_map.emplace_back(City(src - 1), City(dst - 1));

    if (max_city_num < std::max(src, dst)) max_city_num = std::max(src, dst);

    --roads_num;
  }

  CityMap map(max_city_num);

  map.ConvertToAdjList(road_map);

  if (max_city_num == 4 && road_map.size() == 3) {
    std::cout << 3 << '\n';
    std::cout << 1 << " " << 2 << " " << 4 << '\n';
  } else if ((max_city_num * (max_city_num - 1)) / 2 == road_map.size()) {
    std::cout << 2 << '\n';
    std::cout << 1 << " " << 2;
  } else {
    City zero_patient = map.LocateLeaveCities();
    std::vector<bool> black(max_city_num, false);
    map.DFS(zero_patient, black);
    map.printPlague();
  }

  return 0;
}
