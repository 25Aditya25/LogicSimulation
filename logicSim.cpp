#include<bits/stdc++.h>
using namespace std;


/*
Logic Simulation:
1. Compiled Code Simulation
    We use 3 value simulation 0,1,x
    Evaluate a gate when all inputs are available irrespective of change in input value
    Here we may end up doing same evaluation multiple number of times

    To do this we need to Levelize the circuit i.e. give level to gate and evaluate level by level
    and simulate level by level
    Level of any gate = 1+max(level of input)
    Level of primary input = 0

2. Event driven simulation
    Here we do evaluation only when input of a gate changes.
    Here also we need to Levelize the circuit i.e. give level to gate and evaluate level by level
    and simulate level by level
    Level of any gate = 1+max(level of input)
    Level of primary input = 0


We represent circuit as Directed Acyclic Graph.
Every gate is a node.
interconnect is an edge.

Every node must have
1. node number
2. type of gate to evaluate
3. controlling value(eg and gate ip=0 op=0)
4. Inversion parity (if gate is inverting gate or on inverting gate) Not that imp for simulation
5. Number of inputs
6. Number of Outputs
7. From which nodes it is getting input (input list)
8. Output List
9. Value (0,1 or x)
10. Level

Steps:
1. Levelize
2. Sort the gates level by level 
3. Evaluate the gates



evaluate a gate when all inputs are available



*/

enum gateType {Input,And, Or, Not, Nand, Nor, Xor, Xnor};
enum logicValue {HIGH, LOW, UNKNOWN};

class gate {
public:
    int nodeNumber;
    gateType gt; //Type of gate according to the gateType enum above
    logicValue controllingValue;
    bool inversionParity; //High means inversion is present at output
    int numInputs,numOutputs;
    list<gate*> ipList;
    list<gate*> opList;
    logicValue value;
    vector<logicValue> inputValues;
    int level;

    gate(
        int nodeNumber,
        gateType gt,
        logicValue controllingValue,
        bool inversionParity,
        int numInputs,
        int numOutputs,
        // list<gate> ipList,
        // list<gate> opList,
        logicValue value,
        int level
    ){
        this->nodeNumber=nodeNumber;
        this->gt=gt;
        this->controllingValue=controllingValue;
        this->inversionParity=inversionParity;
        this->numInputs=numInputs;
        this->numOutputs=numOutputs;
        // this->ipList=ipList;
        // this->opList=opList;
        this->value=value;
        this->level=level;
    }

};

void createNetlist(list<gate> gateList, vector<vector<int>> adj){
    //This will make all the connections
    /*
    Things to fill here:
        ipList
        opList
        
    */
    int i=0;
    for(auto it:gateList){
        //opList & ipList
        //Find the pointers to gate nodes with the nodeNumbers specified in adj matrix


        for(int j=0 ; j<adj[i].size() ; j++){ //Traverse through the row of the adjacency matrix
            for(auto it1:gateList){
                if(it1.nodeNumber==adj[i][j]){ //Found the gateNode with the nodeNumber 
                    it.opList.push_back(&it1);
                    it1.ipList.push_back(&it); //Takes care of ipList
                }
                else continue;
            }

        }

       
    }


}

int levalize(list<gate> gateList){
    //Go over each node in the gateList and iterate over its ipList to find the maximum level value and the level of the current node.
    int totalLevels=0;
    for(auto it:gateList){
        int maxLevel=0;
        for(auto it1:it.ipList){
            if((*it1).level>maxLevel){
                maxLevel=(*it1).level;
            }
            //Read the inputs also
            it.inputValues.push_back(it1->value);
        }
        it.level=1+maxLevel;
        if(maxLevel>totalLevels)totalLevels=maxLevel;
    }

    return totalLevels;

}

void evaluate(list<gate> gateList,int totalLevels){
    //Returns the final output value
    int eValue=UNKNOWN;
    int countHIGH=0;
    bool foundUnknown=false;
    for(int i=1;i<totalLevels;i++){
        for(auto it:gateList){
            if(it.level==i){ //If you found a node in the level to be computed 
                switch(it.gt){
                    case And:
                            eValue=HIGH;
                            for(auto it1:it.inputValues){
                                if(it1==UNKNOWN){
                                    it.value=UNKNOWN;
                                    break;
                                }
                                else if(it1==LOW){
                                    it.value=LOW;
                                }
                            }
                            break;
                    case Or:
                            eValue=LOW;
                            for(auto it1:it.inputValues){
                                if(it1==UNKNOWN){
                                    it.value=UNKNOWN;
                                    break;
                                }
                                else if(it1==HIGH){
                                    it.value=HIGH;
                                }
                            }
                            break;
                    case Not:
                            eValue=LOW;
                            if(it.inputValues[0]==UNKNOWN) it.value=UNKNOWN;
                            else if(it.inputValues[0]==LOW) it.value=HIGH;
                            else it.value=LOW;
                            break;
                    case Nand:
                            eValue=LOW;
                            for(auto it1:it.inputValues){
                                if(it1==UNKNOWN){
                                    it.value=UNKNOWN;
                                    break;
                                }
                                else if(it1==LOW){
                                    it.value=HIGH;
                                }
                            }
                            break;
                    case Nor:
                            eValue=HIGH;
                            for(auto it1:it.inputValues){
                                if(it1==UNKNOWN){
                                    it.value=UNKNOWN;
                                    break;
                                }
                                else if(it1==HIGH){
                                    it.value=LOW;
                                }
                            }
                            break;
                    case Xor:
                            eValue=HIGH;
                            foundUnknown=false;
                            countHIGH=0;
                            for(auto it1:it.inputValues){
                                if(it1==UNKNOWN){
                                    it.value=UNKNOWN;
                                    foundUnknown=true;
                                    break;
                                }
                                if(it1==HIGH){
                                    countHIGH++;
                                }                                
                            }
                            if(!foundUnknown){
                                if(countHIGH%2==0)it.value=LOW;
                                else it.value=HIGH;
                            }
                            break;
                    case Xnor:
                            eValue=HIGH;
                            foundUnknown=false;
                            countHIGH=0;
                            for(auto it1:it.inputValues){
                                if(it1==UNKNOWN){
                                    it.value=UNKNOWN;
                                    foundUnknown=true;
                                    break;
                                }
                                if(it1==HIGH){
                                    countHIGH++;
                                }                                
                            }
                            if(!foundUnknown){
                                if(countHIGH%2==0)it.value=HIGH;
                                else it.value=LOW;
                            }
                            break;
                }
            }
        }
    }
}



int main(){
    int totalLevels;
    //Lets hardcode a and gate followed by a not gate
    //All we need to start simulation is the primary input list
    //We will store the primary inputs in form of gates only
    

    //Primary Inputs
    gate ip1(0,Input,HIGH,false,0,1,HIGH,0);
    gate ip2(1,Input,HIGH,false,0,1,HIGH,0);

    //Gate declaration
    gate a1(2,And,LOW,false,2,1,UNKNOWN,-1);
    gate n1(3,Not,LOW,false,1,1,UNKNOWN,-1);
 
    
    //List of all the gates
    list<gate> gateList={ip1,ip2,a1,n1};
    

    int n,m;
    //n=num of nodes
    //m=num of edges

    //Here number of nodes is 4(2 inputs + 2 gates) and number of edges is 3
    n=4;
    m=3;

    vector<vector<int>> adj;

    adj.push_back({2});
    adj.push_back({2});
    adj.push_back({3});
    adj.push_back({-1});

    createNetlist(gateList, adj);
    totalLevels=levalize(gateList);
    evaluate(gateList,totalLevels);
    
    
    cout<<ip1.value<<endl;

    return 0;   
}



