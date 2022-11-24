#include "tspsolve.h"
#include<cstdlib>
#include<string>

using namespace std;

enum CompMode {MST, FASTTSP, OPTTSP};
void printHelp();

int main(int argc, char* argv[]){
    //get input
    string optStr;
    string argStr;

    bool seenM = false;

    CompMode compMode;

    for(int i=1; i < argc; i++){
        optStr = string(argv[i]);
        if(optStr=="-h" || optStr=="--help"){
            printHelp();
            exit(0);
        }
        else if(optStr=="-m" || optStr=="--mode"){
            if(seenM){
                cerr<<"Redundant input"<<endl;
                exit(1);
            }
            if(i == argc - 1){
                cerr<<"No argument specified for "<<optStr<<" option."<<endl;
                exit(1);
            }

            argStr = string(argv[++i]);
            
            if(argStr == "MST")
                compMode = MST;
            else if(argStr == "OPTTSP") 
                compMode = OPTTSP; 
            else if(argStr == "FASTTSP") 
                compMode = FASTTSP; 
            else{
                cerr<<"Argument invalid"<<endl;
                exit(1);
            }

            seenM = true;
        }
        else{
            cerr<<"Invalid option specified"<<endl;
            exit(1);
        }
    }

    int mapSize, numCakes, a, b;
    coord inputCoord;
    TSPsolver tspsolver;

    cin >> mapSize >> numCakes;

    for(int i =0; i < numCakes; i++){
        cin >> a >> b;
        inputCoord.first = a;
        inputCoord.second = b;
        tspsolver.addNode(inputCoord);
    }

    //
    //calculate path
    if(compMode==MST){
        tspsolver.makeMST();
        return 0;
    }
    else if(compMode==OPTTSP){
        tspsolver.solveTSP_opt();
    }
    else{
        tspsolver.solveTSP_fast();
    }

    tspsolver.print(cout);

    return 0;
}

void printHelp(){
    cout<<"SYNTAX: \n";
    cout<<"\t-h or --help for this help\n";
    cout<<"\t-m [MODE] or --mode [MODE] to set mode (required!)\n";
    cout<<"\t\t[MODE] should be replaced by either MST, FASTTSP, or OPTTSP.\n\n";
    cout << "Input through standard input, output through standard output."<<endl;
}
