#include <iostream>
#include <vector>

bool satisfactionProblem (std::vector<bool> & CV){
    bool all_satisfied = true;

    for (auto it = CV.begin(); it != CV.end() && all_satisfied; it++){
        if (all_satisfied && *it == false){
            all_satisfied = false;
        }
    }

    return all_satisfied;
}

int branchAndBoundMaximal(const std::vector<std::vector<int>> & C, std::vector<bool> & CV, int cummulated, int actual_comensal, const int comensal_starting)
{
    int max_actual = 0;
    int new_comensal = -1;

    if (satisfactionProblem(CV)){
        // SATISFIED: WE COMPLETE THE CIRCUIT
        max_actual = C[actual_comensal][comensal_starting];
        cummulated += max_actual;

        // mark the visited commensal and set as the next to eval
        std::cout << "FROM: " << actual_comensal << " TO: " << comensal_starting << " FOR ADYACENCY *MAX* : " << max_actual << " CUMMULATED: " << cummulated << std::endl;

        return cummulated;
    }

    // From starting point we consider all of these commensals and we only pick that one that have the maximum rating defined in 0<=X<=100
    // In the next node, we could consider these 
    for (int i = 0; i < CV.size(); i++){
        if (i != actual_comensal && CV[i]==false && C[actual_comensal][i] > max_actual){
            max_actual = C[actual_comensal][i];
            new_comensal = i;
        }
    }

    // mark the visited commensal and set as the next to eval
    cummulated += max_actual;
    std::cout << "FROM: " << actual_comensal << " TO: " << new_comensal << " FOR ADYACENCY *MAX* : " << max_actual << " CUMMULATED: " << cummulated << std::endl;
    CV[new_comensal] = true;

    return branchAndBoundMaximal(C,CV,cummulated,new_comensal,comensal_starting);
}


int main() {
    // Input Matrix
    std::vector<std::vector<int>> C = {
        {0, 50, 80, 30},
        {50, 0, 30, 60},
        {80, 30, 0, 20},
        {30, 60, 20, 0}
    };

    std::vector<bool> CV = {false,false,false,false};

    for (int i = 0; i < CV.size(); i++){
        int actual_comensal = i;
        int cummulated = 0;
        CV[actual_comensal] = {true};

        std::cout << "STARTING AT: " << i << " \n" << branchAndBoundMaximal(C, CV, cummulated, actual_comensal, actual_comensal) << std::endl;
        CV = {false,false,false,false};
    }
    
    return 0;
}
