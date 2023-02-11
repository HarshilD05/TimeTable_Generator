#ifndef FILL_H
#define FILL_H

#include"teacher.cpp"

/*  Functions   */
void fill_time_table(bool &complete, std::vector<Division> &divisions,std::vector<Teacher> &teachers,std::unordered_map<std::string,int> t_map,int div,int day,int slot);

void next_fill (bool &complete, std::vector<Division> divisions,std::vector<Teacher> teachers, std::unordered_map<std::string,int> t_map,int div, int day,int slot) {
    /*  If all 6 days Filled then TT complete   */
    if (day < 6) {
        /*  If all 6 slot of day filled then reset slot to 0 and increment day  */
        if (slot < 6) {
            /*  If All Divisions have filled this slot then goto next slot  */
            if (div < divisions.size() - 1) {
                div++;
            }
            else {
                div = 0;
                slot++;
            }
        }
        else {
            slot = 0;
            day++;
        }
    }
    else complete = true;

    fill_time_table(complete,divisions,teachers,t_map,div,day,slot);
}

bool is_valid_lec(Division div,Teacher teacher,int day,int slot,std::string lec) {
    /*  Checking if Number of lectures hasnt runnout    */
    if ( div.are_lecs_over(lec) ) return false;

    /*  If Techer is Busy its invalid lec   */
    if ( !teacher.is_NULL_slot(day,slot) ) return false;

    return true;
}

void fill_time_table(bool &complete, std::vector<Division> &divisions,std::vector<Teacher> &teachers,std::unordered_map<std::string,int> t_map,int div = 0,int day=0,int slot=0) {
    /*  Fill only if Valid day and Slot */
    if (day < 6 && slot < 6) {

        /* Checking if Selected Slot is Empty   */
        if (divisions[div].is_NULL_slot(day,slot) ) {
        
            /*  Itterating through all Possible Lectures    */
            for (std::string l : divisions[div].lec_list) {

                /*  If TT filling is Complete then Return   */
                if (complete) return;

                /*  Getting Teacher Name from lec   */
                std::string t = divisions[div].sub_teacher_map[l];
                /*  Getting Teacher idx in vector   */
                int idx = t_map[t];

                /*  Checking if Valid Lecturre   */
                if (is_valid_lec(divisions[div],teachers[idx],day,slot,l) ) {
                    
                    /*  Filling Data in Division TT */
                    divisions[div].fill_slot(day,slot,l);

                    /*  Filling Slot in Teachers TT */
                    teachers[idx].fill_slot(day,slot,l);

                    next_fill(complete,divisions,teachers,t_map,div,day,slot);
                }
                
                /*  Restoring Slot to Null if Returning from a backtrack */
                if ( !complete ) {
                    divisions[div].undo_fill(day,slot);
                    teachers[idx].undo_fill(day,slot);
                }

            }
            

        }
        else next_fill(complete,divisions,teachers,t_map,div,day,slot);
    }
    else next_fill(complete,divisions,teachers,t_map,div,day,slot);

}

#endif

/*  Testing */
// /*
int main () {
    std::cout<<"Main";
    std::vector<Division> divs = division_list("../input");
    std::cout<<"\nDivision List created.";

    std::vector<std::vector<std::string>> t_list = uniq_teachers(divs);

    std::vector<Teacher> teachers;
    std::unordered_map<std::string,int> t_map;
    create_Teacher_vector(t_list,teachers,t_map);
    std::cout<<"\nTeacher Vector created!!";

    bool fin = false;
    std::cout<<"\n\nFilling Starts...";
    fill_time_table(fin,divs,teachers,t_map);

    std::cout<<"\n\nFilling Complete!!!";
    
    return 0;
}
// */
