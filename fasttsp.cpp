#include "tspsolve.h"
#include "timer.h"

int vectDistSum(const vector<int>&);

void TSPsolver::solveTSP_fast(){
    solveTSP_fast_help(20);
}

void TSPsolver::solveTSP_fast_help(const int& timeLim){
    if(numNodes <= optThresh)
        solveTSP_opt();

    Timer watch;

    vector<int> pathVect(numNodes);
    for(int i=0; i < numNodes; i++)
        pathVect[i] = i;

    int closest;
    int minDist;
    int newDist;

    solWeight = 0;

    for(int nodes_left_lb=1; nodes_left_lb < numNodes; nodes_left_lb++){
        minDist = ptDist(pathVect[nodes_left_lb-1], pathVect[nodes_left_lb]);
        closest = nodes_left_lb;

        for(int i = nodes_left_lb + 1; i != pathVect.size(); i++){
            newDist = ptDist(pathVect[nodes_left_lb-1], pathVect[i]);
            if(newDist < minDist){
                closest = i;
                minDist = newDist;
            }
        }

        swapVals(pathVect, closest, nodes_left_lb);
        solWeight += minDist;
    }

    solWeight += ptDist(pathVect[pathVect.size()-1], 0);
    tspSolution = pathVect;

 
    // new shit from now on
    if(watch.split() >= timeLim)
        return;

    vector<int> provis = pathVect;
    int provisWgt = solWeight;
    int pMinDist;
    int pLength;
    int probNode_i;
    int close_i;

    int a,b;

    while(watch.split() < timeLim){
        pMinDist = INT_MAX;
        for(int i=1; i < numNodes; i++){
            pLength = provisWgt - ptDist(provis[i-1], provis[i]);
            pLength -= ptDist(provis[i], provis[(i+1) % numNodes]);
            if(pLength < pMinDist){
                pMinDist = pLength;
                probNode_i = i;
            }
        }

        a = ptDist(provis[probNode_i], provis[0]);
        b = 0;

        for(int j=0; j < numNodes; j++){
            newDist = ptDist(provis[probNode_i], provis[j]);
            if(j != probNode_i && newDist < a ){
                a = newDist;
                b = j;
            }
        }

        close_i = b;

        //new greedy alg
        provisWgt = 0;

        if(probNode_i < close_i)
            return;

        for(int i=0; i < numNodes; i++){
         //   if(i == probNode_i) // can move this out
         //       return;
            if(i == close_i){
                //repeat greedy
                for(int k = probNode_i; k-1 > close_i; k--){
                    swapVals(provis, k, k-1);
                    if(watch.split() >= timeLim)
                        return;
                }

                /*
                swapVals(provis, ++i, probNode_i);
                provisWgt += ptDist(provis[i-1], provis[i]);
                for(; i < numNodes; i++){
                    minDist = ptDist(provis[i-1], provis[i]);
                    closest = i;

                    for(int k = i+ 1; k != provis.size(); k++){
                        newDist = ptDist(pathVect[k-1], pathVect[k]);
                        if(newDist < minDist){
                            closest = k;
                            minDist = newDist;
                        }
                    }

                    swapVals(provis, closest, i);
                    provisWgt += minDist;
                }
                */

            }
            provisWgt += ptDist(provis[i], provis[(i+1) % numNodes]);
        }

        if(provisWgt <= solWeight){
            solWeight = provisWgt;
            tspSolution = provis;
        }
        else
            return;

    }


    return;
}

/*
            for(int j=0; j < numNodes; j++){
                if(j + 1 == i){
                    if(i == numNodes - 1)
                        pLength += ptDist(provis[j], provis[0]);
                    else
                        pLength += ptDist(provis[j], provis[j+2]);
                    j++;
                }
                else if(j+1 == numNodes)
                    pLength += ptDist(provis[j], provis[0]);
                else
                    pLength += ptDist(provis[j], provis[j+1]);
            }
            */

