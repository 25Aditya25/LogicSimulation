Logic Simulation:
Logic Simulation can be of two types:
1. Compiled Code Simulation:
    Here we use 3 value simulation 0,1,x
    Evaluate a gate when all inputs are available irrespective of change in input value
    Here we may end up doing same evaluation multiple number of times

    To do this we need to Levelize the circuit i.e. give level to gate and evaluate level by level
    and simulate level by level
    Level of any gate = 1+max(level of input)
    Level of primary input = 0

2. Event driven simulation:
    Here we do evaluation only when input of a gate changes.
    Here also we need to Levelize the circuit i.e. give level to gate and evaluate level by level
    and simulate level by level
    Level of any gate = 1+max(level of input)
    Level of primary input = 0
    But here we evaluate only those gates whose input values have changed.


We can represent circuit as Directed Acyclic Graph.
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
0. Make a Directed Acyclic Graph of the nodes(gates) 
1. Levelize
2. Evaluate the gates level by level



evaluate a gate when all inputs are available
