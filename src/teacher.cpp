#ifndef TEACHER_H
#define TEACHER_H

#include"division.cpp"

class Teacher {
    std::vector<std::vector<std::string>> TT;

    public : 
    std::string name;
    std::string code;

    Teacher (std::string n,std::string c);

    void display () {
        std::cout<<"Name : "<< name <<std::endl;
        std::cout<<"Code : "<< code <<std::endl;
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


};

/*  Functions   */
Teacher::Teacher (std::string name,std::string code) : name(name), code(code){
    TT = create_blank_TT(6,6);
}

void create_Teacher_vector (std::vector<std::vector<std::string>> t_list,std::vector<Teacher> &teachers,std::unordered_map<std::string,int> &t_map) {
    int counter = 0;
    for (auto t : t_list) {
        Teacher T (t[0],t[1]);

        teachers.push_back(T);
        t_map[t[1]] = counter++;
    }
}

/*  Testing */
/*
int main() {
    std::vector<Division> div_list = division_list("../input");

    std::vector<std::vector<std::string>> t_list = uniq_teachers(div_list);

    std::vector<Teacher> teachers;
    std::unordered_map<std::string,int> t_map;

    create_Teacher_vector(t_list,teachers,t_map);

    for (Teacher t : teachers) {
        t.display();
    }

    std::cout<< t_map["SUM"] <<std::endl;
    
    return 0;
}
// */

#endif