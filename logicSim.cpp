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
enum logicValue {LOW, HIGH, UNKNOWN};

class gate {
public:
    int nodeNumber;
    gateType gt; //Type of gate according to the gateType enum above
    logicValue controllingValue;
    bool inversionParity; //High means inversion is present at output
    int numInputs,numOutputs;
    vector<gate*> ipList;
    vector<gate*> opList;
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

    void changeLevel(int newLevel){
        this->level=newLevel;
    }

};



int levalize(list<gate>& gateList){
    //Go over each node in the gateList and iterate over its ipList to find the maximum level value and the level of the current node.
    int totalLevels=0;
    for(list<gate>::iterator it=gateList.begin(); it!=gateList.end(); it++){
        int maxLevel=-1;
        bool notInputLayer=false;
        for(auto it1=it->ipList.begin(); it1!=it->ipList.end(); it1++){
            if((*&(*it1))->level>maxLevel){
                maxLevel=(*&(*it1))->level;
                notInputLayer=true;
            }           
        }
        // cout<<"maxLevel="<<maxLevel<<endl;
        if(notInputLayer) (*it).changeLevel(1+maxLevel);
        // cout<<"nodeNumber= "<<it->nodeNumber<<" Changed Level to "<<(1+maxLevel)<<endl;
        // (*it).level=1+maxLevel;
        //if(notInputLayer)cout<<"level of node"<<it->nodeNumber<<"="<<it->level<<endl;
        //if(notInputLayer)cout<<(*it).level<<endl;

        // cout<<"maxlevel= "<<maxLevel<<" TotalLevel= "<<totalLevels<<endl;
        if(maxLevel>=totalLevels){
            totalLevels=1+maxLevel;
            // cout<<"Changed totalLevel to: "<<totalLevels<<endl;
        }

        
        
    }
    // cout<<"Total Levels:"<<totalLevels<<endl;
    return totalLevels;

}

void evaluate(list<gate>& gateList,int totalLevels){
    //Returns the final output value
    logicValue eValue=UNKNOWN;
    int countHIGH=0;
    bool foundUnknown=false;
    for(int i=1;i<=totalLevels;i++){
        //cout<<i<<endl;
        for(auto it=gateList.begin(); it!=gateList.end(); it++){
            if(it->level==i){ //If you found a node in the level to be computed 

                //Get input values form preceding level
                for(auto it1=it->ipList.begin(); it1!=it->ipList.end(); it1++){
                     //Read the inputs also
                    it->inputValues.push_back((*it1)->value); //This Should not be here
                    //cout<<"Pushed value:"<<(*it1)->value<<" as input to node"<<it->nodeNumber<<endl;
                }

                switch(it->gt){
                    case And:                            
                            eValue=HIGH;
                            foundUnknown=false;
                            for(auto it1=it->inputValues.begin(); it1!=it->inputValues.end(); it1++){
                                if(*it1==UNKNOWN){      
                                    // cout<<"foundUnknown"<<endl;                             
                                    it->value=UNKNOWN;
                                    foundUnknown=true;
                                    break;
                                }
                                else if(*it1==LOW){                                    
                                    eValue=LOW;
                                }
                            }
                            // cout<<"Here"<<endl;
                            if(!foundUnknown)it->value=eValue;                        
                            break;
                    case Or:
                            eValue=LOW;
                            foundUnknown=false;
                            for(auto it1=it->inputValues.begin(); it1!=it->inputValues.end(); it1++){
                                if(*it1==UNKNOWN){
                                    it->value=UNKNOWN;
                                    foundUnknown=true;
                                    break;
                                }
                                else if(*it1==HIGH){
                                    eValue=HIGH;
                                }
                            }
                            if(!foundUnknown)it->value=eValue;
                            break;
                    case Not:
                            eValue=LOW;
                            if(*(it->inputValues.begin())==UNKNOWN) eValue=UNKNOWN;
                            else if(*(it->inputValues.begin())==LOW) eValue=HIGH;
                            else eValue=LOW;
                            it->value=eValue;
                            break;
                    case Nand:
                            eValue=LOW;
                            foundUnknown=false;
                            for(auto it1=it->inputValues.begin(); it1!=it->inputValues.end(); it1++){
                                if(*it1==UNKNOWN){
                                    it->value=UNKNOWN;
                                    foundUnknown=true;
                                    break;
                                }
                                else if(*it1==LOW){
                                    eValue=HIGH;
                                }
                            }
                            if(!foundUnknown)it->value=eValue;
                            break;
                    case Nor:
                            eValue=HIGH;
                            foundUnknown=false;
                            for(auto it1=it->inputValues.begin(); it1!=it->inputValues.end(); it1++){
                                if(*it1==UNKNOWN){
                                    it->value=UNKNOWN;
                                    foundUnknown=true;
                                    break;
                                }
                                else if(*it1==HIGH){
                                    eValue=LOW;
                                }
                            }
                            if(!foundUnknown)it->value=eValue;
                            break;
                    case Xor:
                            eValue=HIGH;
                            foundUnknown=false;
                            countHIGH=0;
                            for(auto it1=it->inputValues.begin(); it1!=it->inputValues.end(); it1++){
                                if(*it1==UNKNOWN){
                                    it->value=UNKNOWN;
                                    foundUnknown=true;
                                    break;
                                }
                                if(*it1==HIGH){
                                    countHIGH++;
                                }                                
                            }
                            if(!foundUnknown){
                                if(countHIGH%2==0)eValue=LOW;
                                else eValue=HIGH;
                            }
                            it->value=eValue;
                            break;
                    case Xnor:
                            eValue=HIGH;
                            foundUnknown=false;
                            countHIGH=0;
                            for(auto it1=it->inputValues.begin(); it1!=it->inputValues.end(); it1++){
                                if(*it1==UNKNOWN){
                                    it->value=UNKNOWN;
                                    foundUnknown=true;
                                    break;
                                }
                                if(*it1==HIGH){
                                    countHIGH++;
                                }                                
                            }
                            if(!foundUnknown){
                                if(countHIGH%2==0)eValue=HIGH;
                                else eValue=LOW;
                            }
                            it->value=eValue;
                            break;
                }
            }
        }
    }
}

void createNetlist(list<gate>& gateList, vector<vector<int>> adj){
    //This will make all the connections
    /*
    Things to fill here:
        ipList, opList
    */
    int i=0;
    for(auto it=gateList.begin(); it!=gateList.end(); it++){
        //opList & ipList
        //Find the pointers to gate nodes with the nodeNumbers specified in adj matrix
        // auto it = v.begin() ; it < v.end(); it++
        for(int j=0 ; j<adj[i].size() ; j++){ //Traverse through the row of the adjacency matrix
            for(auto it1=gateList.begin(); it1!=gateList.end(); it1++){
                if(it1->nodeNumber==adj[i][j]){ //Found the gateNode with the nodeNumber 
                    // cout<<"This Happened"<<endl;
                    // cout<<it1->nodeNumber<<" "<<it->nodeNumber<<endl;
                    it->opList.push_back(&*it1);
                    // it->opList->push_back(&it1);                    
                    it1->ipList.push_back(&*it); //Takes care of ipList
                    //cout<<it.opList.front()->nodeNumber<<" "<<it1.ipList.front()->nodeNumber<<endl;
                }
                // else continue;
            }
        }       
        i=i+1;
    }
    // cout<<gateList.back().level<<endl;
}

int main(){
    int totalLevels=0;
    //Lets hardcode a and gate followed by a not gate
    //All we need to start simulation is the primary input list
    //We will store the primary inputs in form of gates only
    
    /*
    gate Constructor:

        int nodeNumber,
        gateType gt,
        logicValue controllingValue,
        bool inversionParity,
        int numInputs,
        int numOutputs,
        logicValue value,
        int level
    */

    //Primary Inputs
    gate ip1(0,Input,HIGH,false,0,1,LOW,0);
    gate ip2(1,Input,HIGH,false,0,1,LOW,0);

    //Gate declaration for and gate followed by not gate
    // gate a1(2,And,LOW,false,2,1,UNKNOWN,1);
    // gate n1(3,Not,LOW,false,1,1,UNKNOWN,2);
    
    //Gate Declaration for implementation of xor gate using 4 nand gates
    gate na1(2,Nand,LOW,false,2,1,UNKNOWN,1);
    gate na2(3,Nand,LOW,false,1,1,UNKNOWN,2);
    gate na3(4,Nand,LOW,false,1,1,UNKNOWN,2);
    gate na4(5,Nand,LOW,false,1,1,UNKNOWN,2);

    //List of all the gates
    list<gate> gateList={ip1,ip2,na1,na2,na3,na4};
    

    int n,m;
    //n=num of nodes
    //m=num of edges

    //Here number of nodes is 4(2 inputs + 2 gates) and number of edges is 3
    n=4;
    m=3;

    vector<vector<int>> adj;

    //Adjacency matrix for implementation of xor gate using 4 nand gates
    adj.push_back({2,3}); //input1
    adj.push_back({2,4}); //input2
    adj.push_back({3,4}); //nand1
    adj.push_back({5});//nand2
    adj.push_back({5}); //nand3
    adj.push_back({-1});//nand4
    
    createNetlist(gateList, adj);
    
    
    totalLevels=levalize(gateList); //We get the input values of the gates and the levels
    evaluate(gateList,totalLevels);
    
    auto it=gateList.begin();
    for(int i=0;i<gateList.size();i++){        
        cout<<"Output value of node "<<it->nodeNumber<<" is "<<it->value<<" and level is "<<it->level<<endl;
        it++;
    }
  
    // cout<<totalLevels<<endl;

    
    

    return 0;   
}



