#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <cctype>
#include <algorithm>
#include <iomanip>
#include "student_analytics.hpp"

void normalizedName(std::string &n)
{
    if (n.empty())
        return;
    n[0] = toupper(n[0]);
    int len = n.length();
    for (int i = 1; i < len; i++)
    {
        n[i] = tolower(n[i]);
    }
    return;
}

void showMainMenu()
{
    std::cout << "========== Student Analytics & Ranking System ==========" << std::endl
              << std::endl;
    std::cout << "1 to Add Students" << std::endl;
    std::cout << "2 to Display All Students" << std::endl;
    std::cout << "3 to Search Student" << std::endl;
    std::cout << "4 to Update Marks" << std::endl;
    std::cout << "5 to Show Rankings" << std::endl;
    std::cout << "6 to Show Analytics" << std::endl;
    std::cout << "7 to Score Distribution" << std::endl;
    std::cout << "8 to Exit" << std::endl
              << std::endl;
    std::cout << "========================================================" << std::endl;
}

void addStudents(std::unordered_map<std::string, double> &list)
{
    std::cout << "Enter Number of Students you want to Add: ";
    int n;
    std::cin >> n;
    std::cin.ignore();
    for (int i = 0; i < n; i++)
    {
        double marks;
        std::string name;
        std::cout << "Enter Name: ";
        getline(std::cin, name);
        normalizedName(name);
        std::cout << "Enter Marks: ";
        std::cin >> marks;
        std::cin.ignore();
        if (marks < 0 || marks > 100)
        {
            std::cout << "Invalid marks! Please enter marks between 0 and 100.\n";
            i--;
            continue;
        }
        auto it = list.find(name);
        if (it != list.end())
        {
            if (marks > it->second)
            {
                list[name] = marks;
            }
        }
        else
        {
            list[name] = marks;
        }
    }
    if (n == 1)
        std::cout << "Student Added Successfully" << std::endl
                  << std::endl;
    if (n > 1)
        std::cout << "Students Added Successfully" << std::endl
                  << std::endl;
}

void displayAllStudents(std::unordered_map<std::string, double> &list)
{
    if (list.empty())
    {
        std::cout << "No Data Present" << std::endl
                  << std::endl;
        return;
    }
    std::cout << std::left << std::setw(20) << "Name"
              << "Marks" << std::endl;

    std::cout << std::string(30, '-') << std::endl;

    for (const auto &x : list)
    {
        std::cout << std::left << std::setw(20) << x.first
                  << x.second << std::endl;
    }
    std::cout << std::endl
              << std::endl;
}

void searchStudent(std::unordered_map<std::string, double> &list)
{
    if (list.empty())
    {
        std::cout << "No Data Present" << std::endl
                  << std::endl;
        return;
    }
    std::string name;
    std::cout << "Enter Name: ";
    getline(std::cin, name);
    normalizedName(name);
    auto it = list.find(name);
    if (it != list.end())
    {
        std::cout << std::left << std::setw(20) << it->first
                  << it->second << std::endl;
    }
    else
    {
        std::cout << "No Student Present" << std::endl
                  << std::endl;
    }
}

void updateMarks(std::unordered_map<std::string, double> &list)
{
    if (list.empty())
    {
        std::cout << "No Data Present" << std::endl
                  << std::endl;
        return;
    }
    double marks;
    std::string name;
    std::cout << "Enter Name: ";
    getline(std::cin, name);
    normalizedName(name);
    std::cout << "Enter Marks: ";
    std::cin >> marks;
    std::cin.ignore();
    if (marks < 0 || marks > 100)
    {
        std::cout << "Invalid marks! Please enter marks between 0 and 100.\n";
        return;
    }
    auto it = list.find(name);
    if (it != list.end())
    {
        it->second = marks;
        std::cout << "Marks Updated Successfully" << std::endl
                  << std::endl;
    }
    else
    {
        std::cout << "No Student Present" << std::endl
                  << std::endl;
    }
}

void showRankings(std::unordered_map<std::string, double> &list, std::vector<Analytics> &final_list)
{
    if (list.empty())
    {
        std::cout << "No Data Present" << std::endl
                  << std::endl;
        return;
    }
    final_list.clear();
    for (const auto &x : list)
    {
        final_list.emplace_back(x.first, x.second);
    }
    sort(final_list.begin(), final_list.end(), Comparator());
    int len = final_list.size();
    for (int i = 0; i < len; i++)
    {
        final_list[i].display();
    }
    std::cout << std::endl
              << std::endl;
}

void showAnalytics(std::unordered_map<std::string, double> &list)
{
    if (list.empty())
    {
        std::cout << "No Data Present" << std::endl
                  << std::endl;
        return;
    }
    double topperMarks = 0;
    std::string topper;
    double lowestScorer = 100;
    std::string lowest;
    double total = 0;
    for (const auto &x : list)
    {
        double value = x.second;
        total += value;
        if (value > topperMarks)
        {
            topperMarks = value;
            topper = x.first;
        }
        if (value < lowestScorer)
        {
            lowestScorer = value;
            lowest = x.first;
        }
    }
    std::cout << "----------Topper Student Details----------" << std::endl
              << std::endl;
    std::cout << "Name: " << topper << std::endl;
    std::cout << "Marks: " << topperMarks << std::endl
              << std::endl;
    std::cout << std::endl;
    std::cout << "----------Lowest Scorer Student Details----------" << std::endl
              << std::endl;
    std::cout << "Name: " << lowest << std::endl;
    std::cout << "Marks: " << lowestScorer << std::endl
              << std::endl;
    std::cout << std::endl;
    std::cout << "Average Marks: " << total / list.size() << std::endl
              << std::endl;
    std::cout << std::endl;
    std::cout << "Total Student Records: " << list.size() << std::endl
              << std::endl;
    std::cout << std::endl;
}

void scoreDistribution(std::unordered_map<std::string, double> &list)
{
    if (list.empty())
    {
        std::cout << "No Data Present" << std::endl
                  << std::endl;
        return;
    }
    int count90 = 0, count80 = 0, count70 = 0, count60 = 0, countbelow = 0;
    for (const auto &x : list)
    {
        double value = x.second;
        if (value >= 90)
            count90++;
        else if (value >= 80)
            count80++;
        else if (value >= 70)
            count70++;
        else if (value >= 60)
            count60++;
        else
            countbelow++;
    }
    std::cout << "----------Score Distribution----------" << std::endl
              << std::endl;
    std::cout << "90-100 :" << count90 << std::endl;
    std::cout << "80-90 :" << count80 << std::endl;
    std::cout << "70-80 :" << count70 << std::endl;
    std::cout << "60-70 :" << count60 << std::endl;
    std::cout << "Below 60 :" << countbelow << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
}