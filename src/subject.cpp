#ifndef SUBJECT_H
#define SUBJECT_H

#include<iostream>
#include<vector>
#include<fstream>

struct Subject {
    std::string subject_name;
    std::string subject_code;
    std::string teacher_name;
    std::string teacher_code;

    int n_theory;
    int n_practicals;    
};

/*  Functions   */
std::vector<Subject> read_subjects_from_file(std::string file_name);
std::vector<std::vector<std::string>> create_blank_TT (short days,short slots);

/*  Testing */
/*
int main () {

    return 0;
}
// */

/*  Function Definition */
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

        /*  Input of Teacher Name   */
        for (i;i<row.size() ;i++) {
            if (row[i] == ',') {

                sub.teacher_name = data;
                data = "";

                i++;
                break;
            }
            data += row[i];
        }

        /*  INput of Teacher Code   */
        for (i;i<row.size() ;i++) {
            if (row[i] == ',') {

                sub.teacher_code = data;
                data = "";

                i++;
                break;
            }
            data += row[i];
        }

        /*  Pushing Sub in vector   */
        subjects.push_back(sub);
    }

    return subjects;
}

std::vector<std::vector<std::string>> create_blank_TT (short days,short slots) {
    /*  To be returned  */
    std::vector<std::vector<std::string>> tt;
    
    for (int d = 0;d<days;d++) {
        std::vector<std::string> day {slots,"NULL"};

        tt.push_back(day);
    }

    return tt;
}

#endif
