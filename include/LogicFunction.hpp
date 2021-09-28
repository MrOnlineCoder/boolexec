#ifndef LOGIC_FUNCTION_HPP
#define LOGIC_FUNCTION_HPP

#include <Tuple.hpp>

#include <Runtime.hpp>

#include <vector>

class LinearityChecker {
    public:
        LinearityChecker(std::size_t varsCount);

        bool isLinear();

        void iterate(
            Tuple& tuple,
            value_t functionValue
        );
    private:
        bool m_isLinear;

        std::size_t m_variablesCount;

        std::vector<value_t> m_singleCoefficientsSums;

        bool m_hold1;
        bool m_hold2;
};

class LogicFunction {
    public:
        LogicFunction(Tuple& functionDef);

        //class A0
        bool doesSaveZero();

        //class A1
        bool doesSaveOne();

        //class L
        bool isLinear();

        //class M
        bool isMonotone();

        //class S
        bool doesBelongToSClass();

        void updateLinearity(LinearityChecker& checker);
    private:
        void checkClasses();

        bool m_isLinear;
        bool m_isMonotone;
        bool m_isSClass;

        Tuple& m_tuple;
};

#endif