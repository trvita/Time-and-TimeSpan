#pragma once
#include <iomanip>
#include <sstream>

namespace mytime {
class Time {
public:
  Time(int days = 0, int hours = 0, int minutes = 0, int seconds = 0) {
    set_days(days);
    set_hours(hours);
    set_minutes(minutes);
    set_seconds(seconds);
  }
  [[nodiscard]] int days() const noexcept;
  [[nodiscard]] int hours() const noexcept;
  [[nodiscard]] int minutes() const noexcept;
  [[nodiscard]] int seconds() const noexcept;

  int total_seconds() const noexcept;

  void set_days(int days);
  void set_hours(int hours);
  void set_minutes(int minutes);
  void set_seconds(int seconds);

private:
  int days_, hours_, minutes_, seconds_;
};
[[nodiscard]] Time operator"" _d(unsigned long long days) noexcept; // noexcept
[[nodiscard]] Time operator"" _h(unsigned long long hours) noexcept;
[[nodiscard]] Time operator"" _m(unsigned long long minutes) noexcept;
[[nodiscard]] Time operator"" _s(unsigned long long seconds) noexcept;

class TimeSpan {
public:
  TimeSpan(int days = 0, int hours = 0, int minutes = 0, int seconds = 0,
           int sign = 1) {
    set_sign(sign);
    set_days(days);
    set_hours(hours);
    set_minutes(minutes);
    set_seconds(seconds);
  }

  [[nodiscard]] int days() const noexcept; // noexcept nodiscard
  [[nodiscard]] int hours() const noexcept;
  [[nodiscard]] int minutes() const noexcept;
  [[nodiscard]] int seconds() const noexcept;
  [[nodiscard]] int sign() const noexcept;

  void set_days(int days) noexcept;
  void set_hours(int hours) noexcept;
  void set_minutes(int minutes) noexcept;
  void set_seconds(int seconds) noexcept;
  void set_sign(int sign);

  int total_seconds() const noexcept;

private:
  int days_, hours_, minutes_, seconds_;
  int sign_; // "1" - pos, "-1" - neg
};

[[nodiscard]] TimeSpan operator-(Time lt, Time rt) noexcept;
[[nodiscard]] Time operator+(Time lt, TimeSpan rt);
[[nodiscard]] Time operator-(Time lt, TimeSpan rt);
[[nodiscard]] TimeSpan operator+(TimeSpan lt, TimeSpan rt) noexcept;
[[nodiscard]] TimeSpan operator-(TimeSpan lt, TimeSpan rt) noexcept;

std::ostream &operator<<(std::ostream &os, Time t);

bool operator==(Time lt, Time rt) noexcept; // noexcept
bool operator!=(Time lt, Time rt) noexcept;
bool operator>=(Time lt, Time rt) noexcept;
bool operator<(Time lt, Time rt) noexcept;
bool operator<=(Time lt, Time rt) noexcept;
bool operator>(Time lt, Time rt) noexcept;

bool operator==(Time lt, TimeSpan rt) noexcept;
bool operator!=(Time lt, TimeSpan rt) noexcept;
bool operator>=(Time lt, TimeSpan rt) noexcept;
bool operator<(Time lt, TimeSpan rt) noexcept;
bool operator<=(Time lt, TimeSpan rt) noexcept;
bool operator>(Time lt, TimeSpan rt) noexcept;

bool operator==(TimeSpan lt, TimeSpan rt) noexcept;
bool operator!=(TimeSpan lt, TimeSpan rt) noexcept;
bool operator>=(TimeSpan lt, TimeSpan rt) noexcept;
bool operator<(TimeSpan lt, TimeSpan rt) noexcept;
bool operator<=(TimeSpan lt, TimeSpan rt) noexcept;
bool operator>(TimeSpan lt, TimeSpan rt) noexcept;

bool operator==(TimeSpan lt, Time rt) noexcept;
bool operator!=(TimeSpan lt, Time rt) noexcept;
bool operator>=(TimeSpan lt, Time rt) noexcept;
bool operator<(TimeSpan lt, Time rt) noexcept;
bool operator<=(TimeSpan lt, Time rt) noexcept;
bool operator>(TimeSpan lt, Time rt) noexcept;

} // namespace mytime

/*
 Реализуйте классы :
     Time — момент времени
     TimeSpan — интервал.
 Перегрузите операторы для реализации следующих операций :
     Time - Time = TimeSpan
     Time + TimeSpan = Time
     Time - TimeSpan = Time
     TimeSpan + TimeSpan = TimeSpan
     TimeSpan - TimeSpan = TimeSpan

     Перегрузите оператор << для вывода в формате
     : XXd XXh XXm XXs(пример : 01d 23h 10m 11s`)
     Реализуйте пользовательские литералы в пространестве
 имен <your_namespace>::literals : _d, _h, _m, _s.
     Перегрузите операторы сравнения.Если вы используете С++ 17,
     то операторы ==, !=, <, <=, >,
     >=.Для С++ 20 достаточно определить оператор <=>.
 */

// мои правила - timeSpan может быть отрицательным, это его
// отличие от Time, у TimeSpan отдельное поле знака, остальные
// поля могут быть только положительными
// операторы принимают аргументы по значению, возвращают новый
// экземпляр класса
// сеттеры Time отвечают за корректность значений в Time -
// они бросают исключения при отрицательных и переводят при
// слишком больших значениях
// сеттеры TimeSpan умеют переводить отрицательные значения
// я не стала делать constexpr noexcept, так как требовался
// constexpr конструтор, а у меня в сеттерах проверки на валидность значений,
// также в операциях +- конструкторами создаются экземпляры time и могут
// появиться отрицательные значения - сеттеры выбросят ошибку
