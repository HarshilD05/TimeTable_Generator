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

        for (auto p : sub_teacher_map) {
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

    void undo_fill(int day,int slot) {
        std::string val = TT[day][slot];
        if (val != "NULL") {
            int len = val.size()-1;

            TT[day][slot] = "NULL";
            if (val[len] == 'P') {
                TT[day][slot+1] = "NULL";
            }

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

    friend std::vector<std::vector<std::string>> uniq_teachers (std::vector<Division> divisions);

};

/*  Functions   */
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
        sub_teacher_map[sub.subject_code + "_T"] = sub.T_teacher_code;
        sub_teacher_map[sub.subject_code + "_B1_P"] = sub.P_B1_teacher_code;
        sub_teacher_map[sub.subject_code + "_B2_P"] = sub.P_B2_teacher_code;
    }

}

std::vector<Division> division_list (std::string folder_name) {
    /*  To be Returned  */
    std::vector<Division> div_list;
    /*  List of Files in folder */
    std::vector<std::string> file_list = get_all_files_from_folder(folder_name,"csv");

    for (std::string file : file_list) {
        Division div (folder_name + "/" + file);
        div_list.push_back(div);
    }

    return div_list;
}

std::vector<std::vector<std::string>> uniq_teachers (std::vector<Division> divisions) {
    /*  To be returned   */
    std::vector<std::vector<std::string>> t_list;

    /*  Itterating Divisions */
    for (auto div : divisions) {
        /*  Iterating All Subject for each Div  */
        for (Subject sub : div.subjects) {
            bool found = false;

            /*  For Theory Teacher  */
            /*  Checking for repetetion in the List */
            for (auto t : t_list) {
                if (t[1] == sub.T_teacher_code) {
                    found = true;
                    break;
                }
            }
            /*  Adding to list only if new Teacher  */
            if (!found) {
                t_list.push_back( {sub.T_teacher_name,sub.T_teacher_code} );
            }

            /*  For Practical Batch 1 Teacher   */
            /*  Checking for repetetion in the List */
            for (auto t : t_list) {
                if (t[1] == sub.P_B1_teacher_code) {
                    found = true;
                    break;
                }
            }
            /*  Adding to list only if new Teacher  */
            if (!found) {
                t_list.push_back( {sub.P_B1_teacher_name,sub.P_B1_teacher_code} );
            }

            /*  For Practical Batch 2 Teacher   */
            /*  Checking for repetetion in the List */
            for (auto t : t_list) {
                if (t[1] == sub.P_B2_teacher_code) {
                    found = true;
                    break;
                }
            }
            /*  Adding to list only if new Teacher  */
            if (!found) {
                t_list.push_back( {sub.P_B2_teacher_name,sub.P_B2_teacher_code} );
            }

        }

    }

    return t_list;
}

/*  Testing */
/*
int main () {
    Division div("../input/CSE_B.csv");

    div.print_Details();

    div.print_TT();

    div.sub_teacher_map["FCN"];

    return 0;
}
// */

#endif