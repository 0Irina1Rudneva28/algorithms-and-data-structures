/* Мандрагоры — безопасные растения, но их корни могут издавать оглушающие звуки. На втором курсе студенты Хогвартса в качестве одного из занятий
пересаживают уже подросших мандрагор из маленьких горшков в горшки побольше. Горшки с мандрагорами стоят в ряд, поэтому их пронумеровали от 1 до N.
Профессор Стебль рассказала, что каждая из мандрагор кричит с громкостью ai децибел.
Гермиона, как самая одаренная студентка, узнала, что можно за раз пересадить несколько подряд идущих мандрагор, при этом их усредненный шум будет
звучать как среднее геометрическое их громкостей по отдельности. Так как математика в Хогвартсе не преподается, вам придется ей помочь.
Напомним, что среднее геометрическое вычисляется по формуле: (al*a(l+1)*...*ar)^(1/(r-l+1))
Формат ввода:
В первой строке дано число N (1 ≤ N ≤ 3 ⋅ 10^5) — число мандрагор. На второй строке идут N вещественных чисел (0.01 ≤ ai ≤ 10^3)
с двумя знаками после десятичной точки — громкость i-й мандрагоры.
На третьей строке идет единственное число Q (1 ≤ Q ≤ 10^5) — число запросов подсчета среднего шума на подотрезке от Гермионы.
Далее идет Q строк запросов в формате «i j» (0 ≤ i ≤ j ≤ N - 1): i, j — индексы массива, задающие отрезок для запроса.
Формат вывода:
Для каждого запроса на новой строке выведите полученную среднюю громкость результат с точностью до не менее шестого знака после запятой.
ПРИМЕР1:
Ввод
8
79.02 36.68 79.83 76.00 95.48 48.84 49.95 91.91
10
0 0
0 1
0 2
0 3
0 4
0 5
0 6
0 7
1 7
2 7
Вывод
79.0200000000
53.8372881932
61.3918650506
64.7569698060
69.9860845089
65.9131939292
63.3529861609
66.3691949553
64.7354537009
71.1641075963
ПРИМЕР2:
Ввод
1
1.00
1
0 0
Вывод
1.0000000000
ПРИМЕР3:
Ввод
8
1.34 1.37 1.40 1.44 1.91 1.95 1.96 1.97
5
1 4
2 7
4 6
0 3
2 6
Вывод
1.5155180581
1.7527237330
1.9398791862
1.3870080234
1.7122332072
*/

#include <cmath>
#include <iomanip>
#include <iostream>

int main() {
  int n, q, i, j;
  std::cin >> n;
  double a;
  double* b = new double[n + 1];
  a[0] = b[0] = 1;
  for (int iter = 1; iter <= n; ++iter) {
    std::cin >> a;
    b[iter] = b[iter - 1] * pow(a, 1.0 / n);
  }
  std::cin >> q;
  for (int iter = 0; iter < q; ++iter) {
    std::cin >> i >> j;
    std::cout << std::setprecision(9)
              << pow(b[j + 1] / b[i], static_cast<double>(n) / (j - i + 1)) << '\n';
  }
  delete[] b;
  return 0;
}
