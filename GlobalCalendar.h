#pragma once

#include <iostream>
#include <string>

class GlobalCalendar {
private:
    int day_;
    int month_;
    int year_;
    const std::string weekdays[7] = { "Понедельник", "Вторник", "Среда", "Четверг", "Пятница", "Суббота", "Воскресенье" };
    int currentWeekdayIdx = 0;

public:
    GlobalCalendar() {
        day_ = 1;
        month_ = 7;
        year_ = 2003;
    }

    GlobalCalendar& operator=(const GlobalCalendar& other) {
        if (this != &other) {
            day_ = other.day_;
            month_ = other.month_;
            year_ = other.month_;
        }
        return *this;
    }

    GlobalCalendar& operator=(GlobalCalendar&& other) noexcept {
        if (this != &other) {
            day_ = other.day_;
            month_ = other.month_;
            year_ = other.month_;
        }
        return *this;
    }

    void incrementDay() {
        day_++;
        if (day_ > getDaysInMonth()) {
            day_ = 1;
            incrementMonth();
        }
        incrementWeekday();
    }

    void incrementMonth() {
        month_++;
        if (month_ > 12) {
            month_ = 1;
            incrementYear();
        }
    }

    void incrementYear() {
        year_++;
    }

    void incrementWeekday() {
        currentWeekdayIdx++;
        if (currentWeekdayIdx >= 7) {
            currentWeekdayIdx = 0;
        }
    }

    std::string getCurrentWeekday() {
        return weekdays[currentWeekdayIdx];
    }

    int getDaysInMonth() {
        int daysInMonth;

        if (month_ == 2) {
            if ((year_ % 4 == 0 && year_ % 100 != 0) || (year_ % 400 == 0))
                daysInMonth = 29;
            else
                daysInMonth = 28;
        }
        else if (month_ == 4 || month_ == 6 || month_ == 9 || month_ == 11) {
            daysInMonth = 30;
        }
        else {
            daysInMonth = 31;
        }

        return daysInMonth;
    }

    void printDate() {
        std::cout << day_ << "." << month_ << "." << year_ << ", " << getCurrentWeekday() << std::endl;
    }

    const int getYear() const {
        return year_;
    }

    const int getMonth() const {
        return month_;
    }

    const int getDay() const {
        return day_;
    }
};
