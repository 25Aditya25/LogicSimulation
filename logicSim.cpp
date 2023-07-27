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
    list<gate> ipList;
    list<gate> opList;
    logicValue value;
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

void createNetlist(list<gate> gateList){
    //This will make all the connections

}

void levalize(){

}

void evaluate(){

}

int main(){
    
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
    

    return 0;   
}



