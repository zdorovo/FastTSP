#include "tspsolve.h"
#include<string>

string itos(int i){ // i >= 0 
    if(i==0)
        return "0";

    string s;

    while(i != 0){
        s.push_back( (char) ((i % 10) + 48) );
        i = i/10;
    }

    int size = s.size();

    string toret(size, '0');
    for(int j = 0; j != size; j++){
        toret[j] = s[size - j - 1];
    }

    return toret;
}

int TSPsolver::makeMST(){
    vector<int> n(numNodes);

    for (int i=0; i < numNodes; i++)
        n[i] = i;

    return MST_help(true, n, 0);
}

int TSPsolver::MST_help(const bool& toPrint, vector<int>& node_l,
        const int& root){
    if(root == node_l.size())
        return 0;

    if(distVect.empty())
        distVect.assign(numNodes, -1); 
    if(parentVect.empty())
        parentVect.assign(numNodes, -1);

    int weightToRet = 0;
    int toAdd; //index of next node to add to MST
    int rent; //may make things slow...
    int newDist;

    for(int i = root+1; i < node_l.size(); i++){
        distVect[node_l[i]] = ptDist(node_l[i], node_l[root]);
        parentVect[node_l[i]] = node_l[root];
        toAdd = i;
    }

    string output;

    for(int new_lb = root+1; new_lb < node_l.size(); new_lb++){
        for(int i= new_lb; i < node_l.size(); i++){
            //find node with least distance
            if(distVect[node_l[toAdd]] > distVect[node_l[i]]){
                toAdd = i;
            }
        }

        //add that node: add nearest node and node to string,
        swapVals(node_l, new_lb, toAdd);

        weightToRet += distVect[node_l[new_lb]];
        rent = parentVect[node_l[new_lb]]; 

        if(toPrint){
            (rent < node_l[new_lb] ?
                    output += itos(rent) + " " + itos(node_l[new_lb]):
                    output += itos(node_l[new_lb]) + " " + itos(rent));
            output.push_back('\n');
        }

        //change distances
        
        for(int i = new_lb + 1; i < node_l.size(); i++){
                toAdd = i; //need to do this for the for loop above
                newDist = ptDist(node_l[i], node_l[new_lb]);
                if(newDist < distVect[node_l[i]]){
                    distVect[node_l[i]]= newDist;
                    parentVect[node_l[i]] = node_l[new_lb];
                }
        }
    }

    if(toPrint)
        cout << weightToRet << '\n' << output;
    
    return weightToRet;
}

