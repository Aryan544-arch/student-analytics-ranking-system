#ifndef STUDENT_ANALYTICS_HPP
#define STUDENT_ANALYTICS_HPP

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <cctype>
#include <iomanip>

void normalizedName(std::string &);
void showMainMenu();
void addStudents(std::unordered_map<std::string, double> &);
void displayAllStudents(std::unordered_map<std::string, double> &);
void searchStudent(std::unordered_map<std::string, double> &);
void updateMarks(std::unordered_map<std::string, double> &);
void showRankings(std::unordered_map<std::string, double> &,std::vector<Analytics>&);
void showAnalytics(std::unordered_map<std::string, double> &);
void scoreDistribution(std::unordered_map<std::string, double> &);

class Analytics
{
    std::string name;
    double marks;

public:
    Analytics(std::string name, double marks)
    {
        if (name.empty())
            this->name = "Unknown";
        else
            this->name = name;
        if (marks > 0)
            this->marks = marks;
        else
            this->marks = 0;
    }
    double getMarks() const
    {
        return marks;
    }
    std::string getName() const
    {
        return name;
    }
    void display() const
    {
        std::cout << name << " -> " << marks << std::endl;
    }
};

class Comparator
{
public:
    bool operator()(const Analytics &a, const Analytics &b)
    {
        if (a.getMarks() != b.getMarks())
        {
            return a.getMarks() > b.getMarks();
        }
        else if (a.getName().length() != b.getName().length())
        {
            return a.getName().length() < b.getName().length();
        }
        else
        {
            return a.getName() < b.getName();
        }
    }
};

#endif