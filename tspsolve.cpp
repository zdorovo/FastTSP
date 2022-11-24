#include "tspsolve.h"

int iAbs(int a){
    if(a>=0)
        return a;
    return -a;
}

int norm(const coord& a, const coord& b){
    return iAbs(a.first - b.first) + iAbs(a.second - b.second);
}

void TSPsolver::addNode(const coord& c){
    PtsToVisit.push_back(c);
    numNodes++;
    return;
}

void TSPsolver::print(ostream& out){
    if(numNodes == 0)
        return;
        
    out << solWeight << '\n';
    vector<int>::iterator it = tspSolution.begin();
    for(int i=0; i < numNodes-1; i++){
        out << *it << ' '; 
        it++;
    }
    
    out << *it << endl; //do I want this endl?????????????????????????????????
    return;
}

void swapVals(vector<int>& v, const int& i, const int& j){
    int temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}
