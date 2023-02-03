#ifndef SUBJECT_H
#define SUBJECT_H

#include<iostream>
#include<vector>
#include<unordered_map>
#include<fstream>
#include<windows.h>

struct Subject {
    std::string subject_name;
    std::string subject_code;
    std::string T_teacher_name;
    std::string T_teacher_code;

    std::string P_B1_teacher_name;
    std::string P_B1_teacher_code;

    std::string P_B2_teacher_name;
    std::string P_B2_teacher_code;

    int n_theory;
    int n_practicals;    

    void display () {
        std::cout<<"\nSubject Name : "<< subject_name <<std::endl;
        std::cout<<"Subject Code : "<< subject_code <<std::endl;

        std::cout<<"Theory : "<< n_theory <<std::endl;
        std::cout<<"Theory Teacher Name : "<< T_teacher_name <<std::endl;
        std::cout<<"Theory Teacher Code : "<< T_teacher_code <<std::endl;

        std::cout<<"Practicals : "<< n_practicals <<std::endl;
        std::cout<<"Practicals Batch 1 Teacher Name : "<< P_B1_teacher_name <<std::endl;
        std::cout<<"Practicals Batch 1 Teacher Code : "<< P_B1_teacher_code <<std::endl;

        std::cout<<"Practicals Batch 2 Teacher Name : "<< P_B2_teacher_name <<std::endl;
        std::cout<<"Practicals Batch 2 Teacher Code : "<< P_B2_teacher_code <<std::endl<<std::endl;

    }
};

/*  Functions   */
std::vector<Subject> read_subjects_from_file(std::string file_name) {
    /*  Creating File of the file name */
    std::ifstream file(file_name);

    /*  To be returned  */
    std::vector<Subject> subjects;

    /*  Run till reach end of file  */
    while ( !file.eof() ) {
        /*  Storing each line of file in string row */
        std::string row;
        getline(file,row);

        /*  Creating new Subject for each new Line 
            and a string 'data' to store values 
            and a counter 'i' to itterate through the string    */
        Subject sub;
        std::string data = "";
        short i = 0;


        /*  Itterating Through the line till ',' is reached 
            Input for Subject Name   */
        for (i;i<row.size() ;i++) {
            if (row[i] == ',') {

                sub.subject_name = data;
                data = "";

                i++;
                break;
            }
            data += row[i];
        }

        /*  input for Subject Code   */
        for (i;i<row.size() ;i++) {
            if (row[i] == ',') {

                sub.subject_code = data;
                data = "";

                i++;
                break;
            }
            data += row[i];
        }

        /*  input for number of Theory lectures  */
        for (i;i<row.size() ;i++) {
            if (row[i] == ',') {

                sub.n_theory = stoi(data);
                data = "";

                i++;
                break;
            }
            data += row[i];
        }

        /*  Input of Theory Teacher Name   */
        for (i;i<row.size() ;i++) {
            if (row[i] == ',') {

                sub.T_teacher_name = data;
                data = "";

                i++;
                break;
            }
            data += row[i];
        }

        /*  Input of Theory Teacher Code   */
        for (i;i<row.size() ;i++) {
            if (row[i] == ',') {

                sub.T_teacher_code = data;
                data = "";

                i++;
                break;
            }
            data += row[i];
        }

        /*  input for number of Practicals   */
        for (i;i<row.size() ;i++) {
            if (row[i] == ',') {

                sub.n_practicals = stoi(data);
                data = "";

                i++;
                break;
            }
            data += row[i];
        }

        /*  Input of Batch 1 Practical Teacher Name   */
        for (i;i<row.size() ;i++) {
            if (row[i] == ',') {

                sub.P_B1_teacher_name = data;
                data = "";

                i++;
                break;
            }
            data += row[i];
        }

        /*  Input of Batch 1 Practical Teacher Code  */
        for (i;i<row.size() ;i++) {
            if (row[i] == ',') {

                sub.P_B1_teacher_code = data;
                data = "";

                i++;
                break;
            }
            data += row[i];
        }

        /*  Input of Batch 2 Practical Teacher Name   */
        for (i;i<row.size() ;i++) {
            if (row[i] == ',') {

                sub.P_B2_teacher_name = data;
                data = "";

                i++;
                break;
            }
            data += row[i];
        }

        /*  Input of Batch 2 Practicals Teacher Code   */
        for (i;i<row.size() ;i++) {
            data += row[i];
        }
        sub.P_B2_teacher_code = data;

        /*  Pushing Sub in vector   */
        subjects.push_back(sub);
    }

    return subjects;
}

std::vector<std::vector<std::string>> create_blank_TT (int days,int slots) {
    /*  To be returned  */
    std::vector<std::vector<std::string>> tt;
    
    for (int d = 0;d<days;d++) {
        std::vector<std::string> day (slots,"NULL");

        tt.push_back(day);
    }

    return tt;
}

void list_of_lecs (std::vector<Subject> subjects, std::vector<std::string> &list, std::unordered_map<std::string,int> &lec_count) {

    for (Subject sub : subjects) {
        /*  Adding Theory and Practical Lectures in 'list'   */
        if (sub.n_theory) {
            list.push_back(sub.subject_code + "_T");
            lec_count[sub.subject_code + "_T"] = sub.n_theory;
        }
        if (sub.n_practicals) {
            list.push_back(sub.subject_code + "_P");
            lec_count[sub.subject_code + "_P"] = sub.n_practicals;
        }
    }

}

void reverse_string(std::string &str) {
    int len = str.size()-1;

    for (int x = 0;x < len / 2 ;x++) {
        char temp = str[x];
        str[x] = str[len - x];
        str[len - x] = temp;
    }
}

std::string get_Div_Name (std::string file_path) {
    std::string n = "";

    /*  Getting File Name   */    
    for (int s = file_path.size()-1;s>=0;s--) {
        if (file_path[s] == '/' || file_path[s] == '\\') break;
        n += file_path[s];
    }

    /*  Removing Extension  */
    std::string name = "";
    for (int i = n.size()-1;i>=0;i--) {
        if (n[i] == '.') break;
        name += n[i];
    }

    return name;
}

std::vector<std::string> get_all_files_from_folder (std::string folder,std::string extension = "*") {
    /*  To be returned  */
    std::vector<std::string> names;

    std::string search_path = folder + "/*." + extension;
    WIN32_FIND_DATA fd; 
    HANDLE hFind = ::FindFirstFile(search_path.c_str(), &fd); 
    if(hFind != INVALID_HANDLE_VALUE) { 
        do { 
            // read all (real) files in current folder
            // , delete '!' read other 2 default folder . and ..
            if(! (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) ) {
                names.push_back(fd.cFileName);
            }
        }while(::FindNextFile(hFind, &fd)); 
        ::FindClose(hFind); 
    } 
    return names;
}

/*  Testing */
/*
int main () {
    std::vector<Subject> subs = read_subjects_from_file("../input/CSE_B.csv");

    for (Subject s : subs) {
        s.display();
    }

    return 0;
}
// */

#endif