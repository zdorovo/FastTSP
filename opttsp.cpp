#include "tspsolve.h"

void TSPsolver::solveTSP_opt(){
    vector<int> v(numNodes);
    for(int i=0; i<numNodes; i++)
        v[i] = i;
    if(numNodes > optThresh){
        solveTSP_fast_help(numNodes/optThresh);
    }
    solveTSP_opt_help(v, 0, 1);
}

void TSPsolver::solveTSP_opt_help(vector<int>& pathVect,
        const int& curWeight, const int& nodes_left_lb){
    //Nodes left = [nodes_left_lb, pathVect.end() )
    
    if(!promising(pathVect, curWeight, nodes_left_lb))
        return;

    if(nodes_left_lb == pathVect.size()){
        solWeight = curWeight;
        solWeight += norm(PtsToVisit[pathVect[nodes_left_lb-1]],
                          PtsToVisit[0]);
        tspSolution = pathVect;
        //cout << solWeight << endl;
    }
    else
        for(int i = nodes_left_lb; i < pathVect.size(); i++){
            swapVals(pathVect, nodes_left_lb, i);

            solveTSP_opt_help(pathVect,
                    curWeight + 
                    ptDist(pathVect[nodes_left_lb-1], pathVect[nodes_left_lb]),
                    nodes_left_lb + 1);

//            swapVals(pathVect, nodes_left_lb, i); //don't really need
        }
       
    return;
}

bool TSPsolver::promising(vector<int>& v, const int& w, const int& lb){
    if(w > solWeight)
        return false;
    if(lb == v.size())
        return (w + ptDist(v[lb-1], 0) < solWeight); //lb == v.size()
    //loose bounds
    if(lb < v.size()/6)
        return true;
    return (w + MST_help(false, v, lb-1) < solWeight);
}
