/*
Принц-Полукровка оставил в своем учебнике по зельеварению огромное число подсказок и заметок. 
Одна из заметок содержала "Закон несохранения массы". Далее идет ее текст.
Посмотрим на веса каждого из ингредиентов в рецепте и каждому из них сопоставим столбик единичной 
ширины и высоты, равной числу граммов соответствующего ингредиента. Выровняем их снизу по одной линии и 
получим "гистограмму ингредиентов". Тогда масса полученного зелья будет равняться площади самого большого 
прямоугольника в гистограмме, одна из сторон которого лежит на общей нижней линии.

  Формат ввода
В первой строке входного файла записано число N(0<N≤10^6) — количество ингредиентов зелья. Затем следует N
 целых чисел h1…hn, где 0≤hi≤10^9. Эти числа обозначают веса каждого из ингредиентов в граммах.
  Формат вывода
Выведите площадь самого большого прямоугольника в гистограмме. 
Помните, что этот прямоугольник должен быть на общей базовой линии.

  Пример 1
Ввод	
7 2 1 4 5 1 3 3
Вывод
8
  Пример 2
Ввод
3 2 1 2
Вывод
3
  Пример 3
Ввод
1 0
Вывод
0
*/

#include <iostream>
#include <stack>

int long long mas[1000000];
std::pair<int, int> sep[1000000];

void Alg(int num_of) {
  std::stack<int> l;
  for (int i = 0; i < num_of; ++i) {
    while (!l.empty() && mas[l.top()] >= mas[i]) {
      l.pop();
    }
    if (l.empty()) {
      sep[i].first = -1;
    } else {
      sep[i].first = l.top();
    }
    l.push(i);
  }
  std::stack<int> r;
  for (int i = num_of - 1; i >= 0; --i) {
    while (!r.empty() && mas[r.top()] >= mas[i]) {
      r.pop();
    }
    if (r.empty()) {
      sep[i].second = num_of;
    } else {
      sep[i].second = r.top();
    }
    r.push(i);
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int num_els;
  std::cin >> num_els;
  for (int i = 0; i < num_els; ++i) {
    std::cin >> mas[i];
  }
  Alg(num_els);
  int long long tmp = 0;
  for (int i = 0; i < num_els; ++i) {
    int long long current = mas[i] * (sep[i].second - sep[i].first - 1);
    if (current > tmp) {
      tmp = current;
    }
  }
  std::cout << tmp;
  return 0;
}
