#include <gtest/gtest.h>
#include <time.hpp>
using namespace mytime;

TEST(TimeMethods, SetTime) {
  // constructor test
  Time t1;
  EXPECT_EQ(t1.days(), 0);
  EXPECT_EQ(t1.hours(), 0);
  EXPECT_EQ(t1.minutes(), 0);
  EXPECT_EQ(t1.seconds(), 0);
  // setter test
  t1.set_days(1);
  t1.set_hours(2);
  t1.set_minutes(3);
  t1.set_seconds(4);
  EXPECT_EQ(t1.days(), 1);
  EXPECT_EQ(t1.hours(), 2);
  EXPECT_EQ(t1.minutes(), 3);
  EXPECT_EQ(t1.seconds(), 4);

  t1.set_hours(-1);
  EXPECT_EQ(t1.days(), 0);
  EXPECT_EQ(t1.hours(), 23);
  // exception test
  EXPECT_THROW(t1.set_days(-1), std::invalid_argument);
  EXPECT_THROW(t1.set_hours(-25), std::invalid_argument);
  EXPECT_THROW(t1.set_minutes(-1441), std::invalid_argument);
  EXPECT_THROW(t1.set_seconds(-86401), std::invalid_argument);
}
TEST(TimeMethods, Translation) {
  Time t2(1, 23, 59, 61);
  EXPECT_EQ(t2.days(), 2);
  EXPECT_EQ(t2.hours(), 0);
  EXPECT_EQ(t2.minutes(), 0);
  EXPECT_EQ(t2.seconds(), 1);
}

TEST(TimeSpanMethods, SetTimeSpan) {
  // constructor test
  TimeSpan ts1;
  EXPECT_EQ(ts1.days(), 0);
  EXPECT_EQ(ts1.hours(), 0);
  EXPECT_EQ(ts1.minutes(), 0);
  EXPECT_EQ(ts1.seconds(), 0);
  EXPECT_EQ(ts1.sign(), 1);
  // setter test
  ts1.set_days(1);
  ts1.set_hours(2);
  ts1.set_minutes(3);
  ts1.set_seconds(4);
  EXPECT_EQ(ts1.days(), 1);
  EXPECT_EQ(ts1.hours(), 2);
  EXPECT_EQ(ts1.minutes(), 3);
  EXPECT_EQ(ts1.seconds(), 4);

  // negative setter test
  ts1.set_days(-1);
  ts1.set_hours(-2);
  ts1.set_minutes(-3);
  ts1.set_seconds(-4);
  EXPECT_EQ(ts1.sign(), -1);
  EXPECT_EQ(ts1.days(), 0);
  EXPECT_EQ(ts1.hours(), 21);
  EXPECT_EQ(ts1.minutes(), 56);
  EXPECT_EQ(ts1.seconds(), 56);
}

TEST(TimeSpanMethods, PositiveTranslation) {
  TimeSpan ts2(1, 47, 119, 61);
  EXPECT_EQ(ts2.days(), 3);
  EXPECT_EQ(ts2.hours(), 1);
  EXPECT_EQ(ts2.minutes(), 0);
  EXPECT_EQ(ts2.seconds(), 1);
}
TEST(TimeSpanMethods, NegativeTranslation) {
  TimeSpan ts3(1, 23, 59, 61, -1);
  EXPECT_EQ(ts3.sign(), -1);
  EXPECT_EQ(ts3.days(), 2);
  EXPECT_EQ(ts3.hours(), 0);
  EXPECT_EQ(ts3.minutes(), 0);
  EXPECT_EQ(ts3.seconds(), 1);

  TimeSpan ts4(0, 0, -65, -61, 1);
  EXPECT_EQ(ts4.sign(), -1);
  EXPECT_EQ(ts4.days(), 0);
  EXPECT_EQ(ts4.hours(), 0);
  EXPECT_EQ(ts4.minutes(), 53);
  EXPECT_EQ(ts4.seconds(), 59);
}

TEST(Operators, TimeTimeSubtraction) {
  Time lt1(2, 4, 6, 8);
  Time rt1(1, 2, 3, 4);
  TimeSpan res = lt1 - rt1;
  EXPECT_EQ(res.days(), 1);
  EXPECT_EQ(res.hours(), 2);
  EXPECT_EQ(res.minutes(), 3);
  EXPECT_EQ(res.seconds(), 4);

  Time lt2(2, 4, 6, 8);
  Time rt2(1, 2, 20, 54);
  res = lt2 - rt2;
  EXPECT_EQ(res.sign(), 1);
  EXPECT_EQ(res.days(), 1);
  EXPECT_EQ(res.hours(), 1);
  EXPECT_EQ(res.minutes(), 45);
  EXPECT_EQ(res.seconds(), 14);

  Time lt3(0, 1, 2, 3);
  Time rt3(2, 4, 6, 8);
  res = lt3 - rt3;
  EXPECT_EQ(res.sign(), -1);
  EXPECT_EQ(res.days(), 2);
  EXPECT_EQ(res.hours(), 3);
  EXPECT_EQ(res.minutes(), 4);
  EXPECT_EQ(res.seconds(), 5);
}
TEST(Operators, TimeTimeSpanAddition) {
  Time lt1(2, 4, 6, 8);
  TimeSpan rt1(1, 2, 3, 4);
  Time res = lt1 + rt1;
  EXPECT_EQ(res.days(), 3);
  EXPECT_EQ(res.hours(), 6);
  EXPECT_EQ(res.minutes(), 9);
  EXPECT_EQ(res.seconds(), 12);

  Time lt2(1, 0, 0, 0);
  TimeSpan rt2(0, 2, 20, 0, -1);
  res = lt2 + rt2;
  EXPECT_EQ(res.days(), 0);
  EXPECT_EQ(res.hours(), 21);
  EXPECT_EQ(res.minutes(), 40);
  EXPECT_EQ(res.seconds(), 0);

  TimeSpan rt3(2, 0, 0, 0, -1);
  EXPECT_THROW(res = lt2 + rt3, std::invalid_argument);
}

TEST(Operators, TimeTimeSpanSubtraction) {
  Time lt1(2, 4, 6, 8);
  TimeSpan rt1(1, 2, 3, 4);
  Time res = lt1 - rt1;
  EXPECT_EQ(res.days(), 1);
  EXPECT_EQ(res.hours(), 2);
  EXPECT_EQ(res.minutes(), 3);
  EXPECT_EQ(res.seconds(), 4);

  Time lt2(2, 4, 6, 8);
  TimeSpan rt2(1, 2, 20, 54);
  res = lt2 - rt2;
  EXPECT_EQ(res.days(), 1);
  EXPECT_EQ(res.hours(), 1);
  EXPECT_EQ(res.minutes(), 45);
  EXPECT_EQ(res.seconds(), 14);

  Time lt3(0, 1, 2, 3);
  TimeSpan rt3(2, 4, 6, 8, -1);
  res = lt3 - rt3;
  EXPECT_EQ(res.days(), 2);
  EXPECT_EQ(res.hours(), 5);
  EXPECT_EQ(res.minutes(), 8);
  EXPECT_EQ(res.seconds(), 11);

  TimeSpan rt4(2, 0, 0, 0);
  EXPECT_THROW(res = lt3 - rt4, std::invalid_argument);
}

TEST(Operators, TimeSpanTimeSpanAddition) {
  TimeSpan lt1(0, 1, 2, 3);
  TimeSpan rt1(1, 2, 3, 4);
  TimeSpan res = lt1 + rt1;
  EXPECT_EQ(res.days(), 1);
  EXPECT_EQ(res.hours(), 3);
  EXPECT_EQ(res.minutes(), 5);
  EXPECT_EQ(res.seconds(), 7);
  EXPECT_EQ(res.sign(), 1);

  TimeSpan rt2(1, 2, 3, 4, -1);
  res = rt1 + rt2;
  EXPECT_EQ(res.days(), 0);
  EXPECT_EQ(res.hours(), 0);
  EXPECT_EQ(res.minutes(), 0);
  EXPECT_EQ(res.seconds(), 0);
  EXPECT_EQ(res.sign(), 1);

  TimeSpan rt3(2, 3, 4, 5, -1);
  res = rt1 + rt3;
  EXPECT_EQ(res.days(), 0);
  EXPECT_EQ(res.hours(), 22);
  EXPECT_EQ(res.minutes(), 58);
  EXPECT_EQ(res.seconds(), 59);
  EXPECT_EQ(res.sign(), -1);
}

TEST(Operators, TimeSpanTimeSpanSubtraction) {
  TimeSpan lt1(0, 1, 2, 3, 1);
  TimeSpan rt1(1, 2, 3, 4, 1);
  TimeSpan res = lt1 - rt1;
  EXPECT_EQ(res.days(), 0);
  EXPECT_EQ(res.hours(), 22);
  EXPECT_EQ(res.minutes(), 58);
  EXPECT_EQ(res.seconds(), 59);
  EXPECT_EQ(res.sign(), -1);

  TimeSpan rt2(1, 2, 3, 4, -1);
  res = lt1 - rt2;
  EXPECT_EQ(res.days(), 1);
  EXPECT_EQ(res.hours(), 3);
  EXPECT_EQ(res.minutes(), 5);
  EXPECT_EQ(res.seconds(), 7);
  EXPECT_EQ(res.sign(), 1);

  TimeSpan rt3(2, 3, 4, 5);
  res = lt1 - rt3;
  EXPECT_EQ(res.days(), 1);
  EXPECT_EQ(res.hours(), 21);
  EXPECT_EQ(res.minutes(), 57);
  EXPECT_EQ(res.seconds(), 58);
  EXPECT_EQ(res.sign(), -1);
}

TEST(Operators, TimePrint) {
  Time lt1(2, 4, 6, 8);
  std::stringstream ss;
  ss << lt1;
  EXPECT_EQ(ss.str(), "02d 04h 06m 08s");
}

TEST(Operators, TimeLiterals) {
  Time t1 = 3_d;
  Time t2 = 5_h;
  Time t3 = 62_m;
  Time t4 = 86409_s;
  EXPECT_EQ(t1.days(), 3);
  EXPECT_EQ(t1.hours(), 0);
  EXPECT_EQ(t1.minutes(), 0);
  EXPECT_EQ(t1.seconds(), 0);

  EXPECT_EQ(t2.days(), 0);
  EXPECT_EQ(t2.hours(), 5);
  EXPECT_EQ(t2.minutes(), 0);
  EXPECT_EQ(t2.seconds(), 0);

  EXPECT_EQ(t3.days(), 0);
  EXPECT_EQ(t3.hours(), 1);
  EXPECT_EQ(t3.minutes(), 2);
  EXPECT_EQ(t3.seconds(), 0);

  EXPECT_EQ(t4.days(), 1);
  EXPECT_EQ(t4.hours(), 0);
  EXPECT_EQ(t4.minutes(), 0);
  EXPECT_EQ(t4.seconds(), 9);
}

TEST(Operators, TimeTimeComparison) {
  Time t1(1, 2, 3, 4);
  Time t2(2, 3, 4, 5);
  Time t3(0, 1, 2, 3);
  Time t4(1, 2, 3, 4);

  EXPECT_EQ(t1 == t4, true);
  EXPECT_EQ(t1 <= t2, true);
  EXPECT_EQ(t1 < t2, true);
  EXPECT_EQ(t1 >= t3, true);
  EXPECT_EQ(t1 > t3, true);
  EXPECT_EQ(t1 != t2, true);

  EXPECT_EQ(t1 != t4, false);
  EXPECT_EQ(t1 < t3, false);
  EXPECT_EQ(t1 <= t3, false);
  EXPECT_EQ(t1 > t2, false);
  EXPECT_EQ(t1 >= t2, false);
  EXPECT_EQ(t1 == t2, false);
}
TEST(Operators, TimeTimeSpanComparison) {
  Time t1(1, 2, 3, 4);
  TimeSpan t2(2, 3, 4, 5);
  TimeSpan t3(0, 1, 2, 3);
  TimeSpan t4(1, 2, 3, 4);
  TimeSpan t5(1, 2, 3, 4, -1);

  EXPECT_EQ(t1 == t4, true);
  EXPECT_EQ(t1 <= t2, true);
  EXPECT_EQ(t1 < t2, true);
  EXPECT_EQ(t1 >= t3, true);
  EXPECT_EQ(t1 > t3, true);
  EXPECT_EQ(t1 != t2, true);
  EXPECT_EQ(t1 >= t5, true);
  EXPECT_EQ(t1 > t5, true);

  EXPECT_EQ(t1 != t4, false);
  EXPECT_EQ(t1 < t3, false);
  EXPECT_EQ(t1 <= t3, false);
  EXPECT_EQ(t1 > t2, false);
  EXPECT_EQ(t1 >= t2, false);
  EXPECT_EQ(t1 == t2, false);
  EXPECT_EQ(t1 < t5, false);
  EXPECT_EQ(t1 <= t5, false);
}
TEST(Operators, TimeSpanTimeSpanComparison) {
  TimeSpan t1(1, 2, 3, 4);
  TimeSpan t2(2, 3, 4, 5);
  TimeSpan t3(0, 1, 2, 3);
  TimeSpan t4(1, 2, 3, 4);
  TimeSpan t5(1, 2, 3, 4, -1);

  EXPECT_EQ(t1 == t4, true);
  EXPECT_EQ(t1 <= t2, true);
  EXPECT_EQ(t1 < t2, true);
  EXPECT_EQ(t1 >= t3, true);
  EXPECT_EQ(t1 > t3, true);
  EXPECT_EQ(t1 != t2, true);
  EXPECT_EQ(t1 >= t5, true);
  EXPECT_EQ(t1 > t5, true);

  EXPECT_EQ(t1 != t4, false);
  EXPECT_EQ(t1 < t3, false);
  EXPECT_EQ(t1 <= t3, false);
  EXPECT_EQ(t1 > t2, false);
  EXPECT_EQ(t1 >= t2, false);
  EXPECT_EQ(t1 == t2, false);
  EXPECT_EQ(t1 < t5, false);
  EXPECT_EQ(t1 <= t5, false);
}
TEST(Operators, TimeSpanTimeComparison) {
  TimeSpan t1(1, 2, 3, 4);
  Time t2(2, 3, 4, 5);
  Time t3(0, 1, 2, 3);
  Time t4(1, 2, 3, 4);
  TimeSpan t5(1, 2, 3, 4, -1);

  EXPECT_EQ(t1 == t4, true);
  EXPECT_EQ(t1 <= t2, true);
  EXPECT_EQ(t1 < t2, true);
  EXPECT_EQ(t1 >= t3, true);
  EXPECT_EQ(t1 > t3, true);
  EXPECT_EQ(t1 != t2, true);
  EXPECT_EQ(t5 < t2, true);
  EXPECT_EQ(t5 <= t3, true);

  EXPECT_EQ(t1 != t4, false);
  EXPECT_EQ(t1 < t3, false);
  EXPECT_EQ(t1 <= t3, false);
  EXPECT_EQ(t1 > t2, false);
  EXPECT_EQ(t1 >= t2, false);
  EXPECT_EQ(t1 == t2, false);
  EXPECT_EQ(t5 > t2, false);
  EXPECT_EQ(t5 >= t3, false);
}
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
