#pragma once

#include <vector>
#include <tuple>
// #include <algorithm>

#include "Compare.hpp"


struct PartitionPair {
    PartitionPair();
    PartitionPair(int element, int partition);
    std::tuple<int, int> pair;
    bool operator<(PartitionPair& pair_2);
    bool operator>(PartitionPair& pair_2);
    bool operator==(PartitionPair& pair_2);
    int get_element();
    int get_partition();
};


class PartitionMatroid {
    private:
        std::vector<PartitionPair> set;
    public:
        PartitionMatroid();
        PartitionMatroid(std::vector<PartitionPair>& input);

        // Matroid functions begin --------------------------------------------------------------------------------------------------
        void min_sort();
        void max_sort();
        bool not_empty();
        PartitionPair top();
        bool is_independent(PartitionPair& e);
        void add_element(PartitionPair e);
        void pop();
        // Matroid functions end ---------------------------------------------------------------------------------------------------------
        
        std::string get_string();
        std::vector<PartitionPair> get_data();

        friend std::ostream& operator<<(std::ostream& os, PartitionMatroid& p);
};

std::ostream& operator<<(std::ostream& os, PartitionMatroid& p);

// Create a PartitionPair
PartitionPair make_pair(int elem, int part);