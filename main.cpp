#include<iostream>
#include<unordered_map>
#include<unordered_set>
#include<vector>
#include<cctype>
#include<algorithm>
#include <iomanip>
#include "student_analytics.hpp"

int main(){
    std::unordered_map<std::string,double>list;
    std::vector<Analytics>final_list;
    while(true){
        showMainMenu();
        int ch;
        std::cout<<"Enter Choice: "; std::cin>>ch;
        std::cin.ignore();
        if(ch==8) break;
        switch(ch){
            case 1: addStudents(list); break;
            case 2: displayAllStudents(list); break;
            case 3: searchStudent(list); break;
            case 4: updateMarks(list); break;
            case 5: showRankings(list,final_list); break;
            case 6: showAnalytics(list); break;
            case 7: scoreDistribution(list); break;
            default: std::cout<<"Wrong Input"<<std::endl<<std::endl;
        }
    }
    return 0;
}