// #include "Graph.hpp"
// #include "Matrix.hpp"
#include <queue>
// #include <vector> // ?? not needed i think

template <typename ELEMENT_TYPE>
class Compare {
    public:
        bool operator()(ELEMENT_TYPE a, ELEMENT_TYPE b) {
            if (a.get_weight() > b.get_weight()) {
                return true;
            }
            return false;
        }
};

template <class SET_TYPE, typename ELEMENT_TYPE>
class Set {
    private:
        std::priority_queue<ELEMENT_TYPE, std::vector<ELEMENT_TYPE>, Compare<ELEMENT_TYPE>> pq;
        SET_TYPE result_set; // empty set that will be filled for the result
    public:
        Set() {}
        Set(SET_TYPE input_set) {
            for (auto element : input_set.get_elements()) {
                pq.push(element);
            }
        }

        // Checks if the set of data is empty
        bool not_empty() {
            if (!pq.empty()) {
                return true;
            }
            return false;
        }

        // Returns the top (maximal/minimal) element
        auto top() {
            return pq.top();
        }

        // Pops the top (maximal/minimal) element
        void pop() {
            pq.pop();
        }

        // Adds an element to the set
        void add(ELEMENT_TYPE element) {
            pq.push(element);
        }

        SET_TYPE set() {
            while(!pq.empty()) {
                result_set.add(pq.top());
                pq.pop();
            }
            return result_set;
        }
};