#ifndef __TSP_SOLVE__
#define __TSP_SOLVE__

#include<utility>
#include<vector>
#include<deque>
#include<iostream>
#include<climits>

using namespace std;    

typedef pair<int, int> coord;

int norm(const coord&, const coord&);
void swapVals(vector<int>& v, const int& i, const int& j);

class TSPsolver{
    vector<coord> PtsToVisit;
    vector<int> tspSolution;
    int numNodes;
    int solWeight;
    int optThresh;

    vector<int> distVect;
    vector<int> parentVect;
    
    bool promising(vector<int>&, const int&, const int&);
    //bool promising(int, const deque<int>&);
    int MST_help(const bool&, vector<int>&, const int&);
    void solveTSP_opt_help(vector<int>&, const int&, const int&);
    void solveTSP_fast_help(const int&);

    int ptDist(const int& i, const int& j){
        return norm(PtsToVisit[i], PtsToVisit[j]);
    }

    //vector<vector<int> > ordAdjList;
    //void make_ordAdjList();
    //int sumDists(const vector<int>& v, const int& lb);

  public:
    void addNode(const coord&);
    void solveTSP_opt();
    void solveTSP_fast();
    int makeMST();
    void print(ostream& out);
    TSPsolver(): numNodes(0), solWeight(INT_MAX), optThresh(6){}
};

#endif
