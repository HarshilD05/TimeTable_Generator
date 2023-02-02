#ifndef DIVISION_H
#define DIVISION_H

#include"subject.cpp"
#include<unordered_map>
#include<algorithm>     // std::shuffle
#include<random>        // std::default_random_engine
#include<time.h>        // to generate seed of current time

class Division {
    std::vector<std::vector<std::string>> TT;
    std::vector<Subject> subjects;

    std::unordered_map<std::string,int> lec_count_map;

    public : 
    std::string div_name;
    std::vector<std::string> lec_list;
    std::unordered_map<std::string,std::string> sub_teacher_map;

    Division (std::string file_name);

    void print_Details () {
        std::cout<<"Division Name : "<< div_name <<std::endl;
        std::cout<<"List of Lectures : "<<std::endl;
        for (std::string l : lec_list) {
            std::cout<< l <<" ";
        }
        
        std::cout<<"\nLecture Counts : "<<std::endl;
        for (auto p : lec_count_map) {
            std::cout<< p.first <<"\t"<< p.second <<std::endl;
        }
    }

    void fill_slot(int day,int slot,std::string val) {
        int len = val.size()-1;
        if (val[len] == 'T') {
            TT[day][slot] = val;
        }
        else if (val[len] == 'P') {
            TT[day][slot] = val;
            TT[day][slot+1] = val;
        }
    }

    void print_TT () {
        std::vector<std::string> DAYS = {"MON","TUE","WED","THU","FRI","SAT"};

        for (int d = 0;d<6;d++) {
            std::cout<<std::endl;
            std::cout<< DAYS[d] <<" : ";
            for (auto l : TT[d]) {
                std::cout<< l <<", ";
            }
        }

        std::cout<<"\n\n";
    }

};

/*  Functions   */

/*  Testing */
// /*
int main () {
    Division div("../input/CSE_B.csv");

    div.print_Details();

    div.print_TT();

    return 0;
}
// */

/*  Function Definition */
Division :: Division (std::string file_name) {
    /*  Initializing Data   */
    div_name = get_Div_Name(file_name);
    subjects = read_subjects_from_file(file_name);
    TT = create_blank_TT(6,6);

    /*  Lecture List and count map */
    list_of_lecs(subjects,lec_list,lec_count_map);
    /*  Randomising Lec List    */
    std::default_random_engine e( time(0) );
    std::shuffle(lec_list.begin(),lec_list.end(),e);

    /*  Subject and Teacher Map */
    for (Subject sub : subjects) {
        sub_teacher_map[sub.subject_code] = sub.teacher_code;
    }

}

#endif