#pragma once

#include "VectorSpace.hpp"
#include "BipartiteGraph.hpp"
#include "PartitionMatroid.hpp"
#include "Oracle.hpp"


// -------------------------------------------------------------------------------------------------- //
// "Matroids take 'It’s useful to have multiple perspectives on this thing' to a ridiculous extent."  //
// -------------------------------------------------------------------------------------------------- //


// The SET being the type of input set, like Graph, or a Matrix
// The ELEMENT being the corresponding element for each set, like Edge for graphs, and Vector for matrices
template <class SET, typename ELEMENT>
class Matroid {
    private:
        SET ground_set;
        SET solution_set;
        Oracle<SET, ELEMENT> oracle;
    public:
        Matroid();
        Matroid(SET& input_set);
        Matroid(SET& input_set, SET& other_set);

        // Minimum Greedy Algorithm
        SET min_optimize_matroid();

        // Maximum Greedy Algorithm
        SET max_optimize_matroid();
};