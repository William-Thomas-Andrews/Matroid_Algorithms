template <class SET, typename ELEMENT>
class Oracle {
    public:
        Oracle() {}
        bool independent(SET S, ELEMENT e) {
            return (S.is_independent(e));
        }
};