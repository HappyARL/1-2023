# ФИО: АЛИЕВ АРЛАН СЕИТОВИЧ
# Задача No2 - Алгоритмы

## Условие:

Думаем, все помнят всемирно известную игру Plague Inc., где Вы в роли смертельно опасного вируса пытаетесь уничтожить все человечество. В этой задаче Вам предстоит примерить аналогичную роль и заразить все города неизвестной болезнью.

В качестве входных данных Вам вводится карта городов, представляющая из себя некоторый граф, заданный списком из M ребер.
Город считается зараженным болезнью в двух случаях:

- он сразу заражен эпидемией
- его любые два соседа заражены эпидемией

Ваша задача - найти минимальное количество городов, которые нужно изначально заразить эпидемией, чтобы в итоге заразились все города, а также вывести номера этих городов.

## Решение:

Мое решение имеет два файла:
1) решение задачи на С++
2) Cmake файл для его запуска

Для решения задачи был реализован алгоритм DFS, с допольнительными проверками.

Был реализован класс который принимает массив ребер и переобразует его в список смежности для графа. После запускает на нем DFS (с особенностями).


```c++
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
```
