#include <time.hpp>
namespace mytime {
// getters
int Time::days() const noexcept { return days_; }
int Time::hours() const noexcept { return hours_; }
int Time::minutes() const noexcept { return minutes_; }
int Time::seconds() const noexcept { return seconds_; }

int TimeSpan::days() const noexcept { return days_; }
int TimeSpan::hours() const noexcept { return hours_; }
int TimeSpan::minutes() const noexcept { return minutes_; }
int TimeSpan::seconds() const noexcept { return seconds_; }
int TimeSpan::sign() const noexcept { return sign_; }

int Time::total_seconds() const noexcept {
  return (seconds_ + minutes_ * 60 + hours_ * 3600 + days_ * 86400);
}
int TimeSpan::total_seconds() const noexcept {
  return (sign_ * (seconds_ + minutes_ * 60 + hours_ * 3600 + days_ * 86400));
}

// setters
void Time::set_days(int days) {
  if (days < 0) {
    throw std::invalid_argument("Days can't be negative");
  }
  days_ = days;
}
void Time::set_hours(int hours) {
  set_days(days_ + hours / 24);
  if (hours >= 0) {
    hours_ = hours % 24;
  } else if (days_ >= 0) {
    set_days(days_ - 1);
    hours_ = hours % 24 + 24;
  } else {
    throw std::invalid_argument("Hours can't be negative");
  }
}
void Time::set_minutes(int minutes) {

  set_hours(hours_ + minutes / 60);
  if (minutes >= 0) {
    minutes_ = minutes % 60;
  } else {
    if ((hours_ != 0) || (days_ != 0)) {
      set_hours(hours_ - 1);
      minutes_ = minutes % 60 + 60;
    } else {
      throw std::invalid_argument("Minutes can't be negative");
    }
  }
}
void Time::set_seconds(int seconds) {
  set_minutes(minutes_ + seconds / 60);
  if (seconds >= 0) {
    seconds_ = seconds % 60;
  } else {
    if ((hours_ != 0) || (days_ != 0) || (minutes_ != 0)) {
      set_minutes(minutes_ - 1);
      seconds_ = seconds % 60 + 60;
    } else {
      throw std::invalid_argument("Seconds can't be negative");
    }
  }
}

void TimeSpan::set_days(int days) noexcept {
  if (days < 0) {
    sign_ = -1;
  }
  int factor = days >= 0 ? 1 : -1;
  days_ = days * factor;
}
void TimeSpan::set_hours(int hours) noexcept {
  set_days(days_ + hours / 24);
  if (hours >= 0) {
    hours_ = hours % 24;
  } else {
    if (days_ == 0) {
      set_sign(-1);
      hours_ = -hours % 24;
    } else {
      set_days(days_ - 1);
      hours_ = hours % 24 + 24;
    }
  }
}
void TimeSpan::set_minutes(int minutes) noexcept {
  set_hours(hours_ + minutes / 60);
  if (minutes >= 0) {
    minutes_ = minutes % 60;
  } else {
    if ((hours_ == 0) && (days_ == 0)) {
      set_sign(-1);
      minutes_ = -minutes % 60;
    } else {
      set_hours(hours_ - 1);
      minutes_ = minutes % 60 + 60;
    }
  }
}
void TimeSpan::set_seconds(int seconds) noexcept {
  set_minutes(minutes_ + seconds / 60);
  if (seconds >= 0) {
    seconds_ = seconds % 60;
  } else {
    if ((hours_ == 0) && (days_ == 0) && (minutes_ == 0)) {
      set_sign(-1);
      seconds_ = -seconds % 60;
    } else {
      set_minutes(minutes_ - 1);
      seconds_ = seconds % 60 + 60;
    }
  }
}
void TimeSpan::set_sign(int sign) {
  if (sign == 1 || sign == -1) {
    sign_ = sign;
  } else {
    throw std::invalid_argument("Sign must be 1 or -1");
  }
}

// +- operators
TimeSpan operator-(const Time lt, const Time rt) noexcept {
  TimeSpan resultSpan;
  if (lt >= rt) {
    resultSpan.set_days(lt.days() - rt.days());
    resultSpan.set_hours(lt.hours() - rt.hours());
    resultSpan.set_minutes(lt.minutes() - rt.minutes());
    resultSpan.set_seconds(lt.seconds() - rt.seconds());
  } else {
    resultSpan.set_days(rt.days() - lt.days());
    resultSpan.set_hours(rt.hours() - lt.hours());
    resultSpan.set_minutes(rt.minutes() - lt.minutes());
    resultSpan.set_seconds(rt.seconds() - lt.seconds());

    resultSpan.set_sign(-1);
  }
  return resultSpan;
}
Time operator+(const Time lt, const TimeSpan rt) {
  Time resultTime(lt.days() + rt.days() * rt.sign(),
                  lt.hours() + rt.hours() * rt.sign(),
                  lt.minutes() + rt.minutes() * rt.sign(),
                  lt.seconds() + rt.seconds() * rt.sign());
  return resultTime;
}
Time operator-(const Time lt, const TimeSpan rt) {
  Time resultTime(lt.days() - rt.days() * rt.sign(),
                  lt.hours() - rt.hours() * rt.sign(),
                  lt.minutes() - rt.minutes() * rt.sign(),
                  lt.seconds() - rt.seconds() * rt.sign());
  return resultTime;
}
TimeSpan operator+(const TimeSpan lt, const TimeSpan rt) noexcept {
  TimeSpan resultSpan(lt.days() * lt.sign() + rt.days() * rt.sign(),
                      lt.hours() * lt.sign() + rt.hours() * rt.sign(),
                      lt.minutes() * lt.sign() + rt.minutes() * rt.sign(),
                      lt.seconds() * lt.sign() + rt.seconds() * rt.sign());
  return resultSpan;
}
TimeSpan operator-(const TimeSpan lt, const TimeSpan rt) noexcept {
  TimeSpan resultSpan(lt.days() * lt.sign() - rt.days() * rt.sign(),
                      lt.hours() * lt.sign() - rt.hours() * rt.sign(),
                      lt.minutes() * lt.sign() - rt.minutes() * rt.sign(),
                      lt.seconds() * lt.sign() - rt.seconds() * rt.sign());

  return resultSpan;
}

// // << operator
std::ostream &operator<<(std::ostream &os, const Time t) {
  os << std::setfill('0') << std::setw(2) << t.days() << "d ";
  os << std::setw(2) << t.hours() << "h ";
  os << std::setw(2) << t.minutes() << "m ";
  os << std::setw(2) << t.seconds() << "s";
  return os;
}

//<=> operators
// time time
bool operator==(const Time lt, const Time rt) noexcept {
  return (lt.days() == rt.days() && lt.hours() == rt.hours() &&
          lt.minutes() == rt.minutes() && lt.seconds() == rt.seconds());
}
bool operator<(const Time lt, const Time rt) noexcept {
  return (lt.total_seconds() < rt.total_seconds());
}
bool operator!=(const Time lt, const Time rt) noexcept { return !(lt == rt); }
bool operator>=(const Time lt, const Time rt) noexcept { return !(lt < rt); }
bool operator<=(const Time lt, const Time rt) noexcept { return !(rt < lt); }
bool operator>(const Time lt, const Time rt) noexcept { return rt < lt; }

// timespan timespan
bool operator==(const TimeSpan lt, const TimeSpan rt) noexcept {
  return (lt.days() == rt.days() && lt.hours() == rt.hours() &&
          lt.minutes() == rt.minutes() && lt.seconds() == rt.seconds());
}
bool operator<(const TimeSpan lt, const TimeSpan rt) noexcept {
  return (lt.total_seconds() < rt.total_seconds());
}
bool operator!=(const TimeSpan lt, const TimeSpan rt) noexcept {
  return !(lt == rt);
}
bool operator>=(const TimeSpan lt, const TimeSpan rt) noexcept {
  return !(lt < rt);
}
bool operator<=(const TimeSpan lt, const TimeSpan rt) noexcept {
  return !(rt < lt);
}
bool operator>(const TimeSpan lt, const TimeSpan rt) noexcept {
  return rt < lt;
}

// time timespan
bool operator==(const Time lt, const TimeSpan rt) noexcept {
  return (rt.sign() == -1)
             ? false
             : (lt.days() == rt.days() && lt.hours() == rt.hours() &&
                lt.minutes() == rt.minutes() && lt.seconds() == rt.seconds());
}
bool operator<(const Time lt, const TimeSpan rt) noexcept {
  return (lt.total_seconds() < rt.total_seconds());
}
bool operator!=(const Time lt, const TimeSpan rt) noexcept {
  return !(lt == rt);
}
bool operator>=(const Time lt, const TimeSpan rt) noexcept {
  return !(lt < rt);
}
bool operator<=(const Time lt, const TimeSpan rt) noexcept {
  return !(rt < lt);
}
bool operator>(const Time lt, const TimeSpan rt) noexcept { return rt < lt; }
// timespan time
bool operator==(const TimeSpan lt, const Time rt) noexcept {
  return (lt.sign() == -1)
             ? false
             : (lt.days() == rt.days() && lt.hours() == rt.hours() &&
                lt.minutes() == rt.minutes() && lt.seconds() == rt.seconds());
}
bool operator<(const TimeSpan lt, const Time rt) noexcept {
  return (lt.total_seconds() < rt.total_seconds());
}
bool operator!=(const TimeSpan lt, const Time rt) noexcept {
  return !(lt == rt);
}
bool operator>=(const TimeSpan lt, const Time rt) noexcept {
  return !(lt < rt);
}
bool operator<=(const TimeSpan lt, const Time rt) noexcept {
  return !(rt < lt);
}
bool operator>(const TimeSpan lt, const Time rt) noexcept { return rt < lt; }

Time operator"" _d(unsigned long long days) noexcept {
  return {static_cast<int>(days), 0, 0, 0};
}
Time operator"" _h(unsigned long long hours) noexcept {
  return {0, static_cast<int>(hours), 0, 0};
}
Time operator"" _m(unsigned long long minutes) noexcept {
  return {0, 0, static_cast<int>(minutes), 0};
}
Time operator"" _s(unsigned long long seconds) noexcept {
  return {0, 0, 0, static_cast<int>(seconds)};
}
} // namespace mytime
