#ifndef SUBJECT_H
#define SUBJECT_H

#include<unordered_map>
#include<windows.h>
#include"read_csv.cpp"

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

    /*  Vector Storing Table data Values    */
    std::vector<std::vector<std::string>> csv_tab = csv_table(file_name);
    // std::cout<<"Table Created"<<std::endl;
    // std::cout<<"Table Dimensions : "<< csv_tab.size() <<"x"<< csv_tab[0].size() <<std::endl;

    /*  Skipping The first Row of Titles and Collecting data    */
    for (int i = 1;i<csv_tab.size();i++) {
        auto row = csv_tab[i];

        /*  Creating Subject based on info in Row   */
        Subject sub;
        
        sub.subject_name = row[0];
        sub.subject_code = row[1];

        
        sub.n_theory = stoi(row[2] );
        sub.T_teacher_name = row[3];
        sub.T_teacher_code = row[4];

        sub.n_practicals = stoi( row[5] );
        sub.P_B1_teacher_name = row[6];
        sub.P_B1_teacher_code = row[7];

        sub.P_B2_teacher_name = row[8];
        sub.P_B2_teacher_code = row[9];

        /*  Pushing this Subject in list of Subjects    */
        subjects.push_back(sub);
    }

    // std::cout<<"Subject Vector Created."<<std::endl;

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

void list_of_lecs (std::vector<Subject> subjects, std::vector<std::string> &lec_list, std::vector<std::string> &B2_p_list, std::unordered_map<std::string,int> &lec_count) {

    for (Subject sub : subjects) {
        /*  Adding Theory and Practical Lectures in 'list'   */
        if (sub.n_theory) {
            lec_list.push_back(sub.subject_code + "_T");
            lec_count[sub.subject_code + "_T"] = sub.n_theory;
        }
        if (sub.n_practicals) {
            lec_list.push_back(sub.subject_code + "_B1_P");
            lec_count[sub.subject_code + "_B1_P"] = sub.n_practicals;

            B2_p_list.push_back(sub.subject_code + "_B2_P");
            lec_count[sub.subject_code + "_B2_P"] = sub.n_practicals;
        }
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

#endif


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
