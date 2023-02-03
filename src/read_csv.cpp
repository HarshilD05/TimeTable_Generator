#ifndef READ_CSV_H
#define READ_CSV_H

#include<vector>
#include<string>
#include<iostream>
#include<fstream>

/*  Functions   */
void reverse_string(std::string &str) {
    int len = str.size()-1;

    for (int x = 0;x < len / 2 ;x++) {
        char temp = str[x];
        str[x] = str[len - x];
        str[len - x] = temp;
    }
}

std::string get_extension (std::string file) {
    std::string f_name = "";
    
    /*  Getting Last part of path (Potentialy a file) */
    for (int i = file.size()-1;i>=0;i--) {
        if (file[i] == '/' || file[i] == '\\') break;
        f_name += file[i];
    }

    /*  Getting the .ext part of file   */
    std::string ext = "";
    for (char c : f_name) {
        if (c == '.') break;
        ext += c;
    }
    reverse_string(ext);

    return ext;
}

std::vector<std::vector<std::string>> csv_table (std::string file) {
    /*  To be returned  */
    std::vector<std::vector<std::string>> table;

    /*  Vaaalid only for a csv file */
    if ( get_extension(file) == "csv" || get_extension(file) == "CSV" ) {
        /*  Converting string to File   */
        std::ifstream f(file);

        while(!f.eof() ) {
            /*  Getting input of line of the file   */
            std::string line;
            getline(f,line);

            /*  Vector to store data of row */
            std::vector<std::string> row;
            std::string data = "";
            
            int i = 0;

            while (i < line.size()-1) {
                if (line[i] == ',') {
                    row.push_back(data);
                    data = "";
                    i++;
                }
                data += line[i++];
            }
            
            table.push_back(row);
        }

    }
    else {
        std::cout<<"\nNot a csv file!"<<std::endl<<std::endl;
    }    

    return table;
}

#endif

/*  Testing */
/*
int main() {
    std::vector<std::vector<std::string>> tab = csv_table("../input/CSE_B.csv");

    for (auto r : tab) {
        for (auto x : r) {
            std::cout<< x <<"\t|\t";
        }
        std::cout<<std::endl;
    }
    

    return 0;
}

// */