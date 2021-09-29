#include <LogicFunction.hpp>

#include <cmath>
#include <iostream>

LogicFunction::LogicFunction(Tuple& functionDef) : m_tuple(functionDef) {
    checkClasses();
}

void LogicFunction::updateLinearity(LinearityChecker& checker) {
    m_isLinear = checker.isLinear();
}

//class A0
bool LogicFunction::doesSaveZero() {
    return m_tuple.getDigitAt(0) == 0;
}

//class A1
bool LogicFunction::doesSaveOne() {
    return m_tuple.getDigitAt(m_tuple.getSize() - 1) == 1;
}

//class L
bool LogicFunction::isLinear() {
    return m_isLinear;
}

//class M
bool LogicFunction::isMonotone() {
    return m_isMonotone;
}

//class S
bool LogicFunction::doesBelongToSClass() {
    return m_isSClass;
}

void LogicFunction::checkClasses() {
    //S
    m_isSClass = true;
    for (std::size_t i = 0; i < m_tuple.getSize() / 2; i++) {
        if (m_tuple.getDigitAt(i) == m_tuple.getDigitAt(
                                         m_tuple.getSize() - i - 1)) {
            m_isSClass = false;
            break;
        }
    }

    //L
    m_isLinear = false;

    //M
    m_isMonotone = false;
}

LinearityChecker::LinearityChecker(std::size_t varsCount) {
    m_isLinear = true;

    m_variablesCount = varsCount;
    m_singleCoefficientsSums.reserve(m_variablesCount);

    for (std::size_t i = 0; i < varsCount;i++) m_singleCoefficientsSums.push_back(
        0
    );
}

bool LinearityChecker::isLinear() {
    return m_isLinear;
}

void LinearityChecker::iterate(
    Tuple& tuple,
    value_t functionValue) {

    value_t tupleSum = 0;
    std::size_t variablesUsed = 0;
    std::size_t lastTruthyIndex = -1;
    
    for (std::size_t i = 0; i < tuple.getSize(); i++) {
        auto dValue = tuple.getDigitAt(i);
        tupleSum ^= dValue;
        if (dValue) {
            variablesUsed++;
            lastTruthyIndex = i;
        }
    }

    if (variablesUsed == 0) return;

    if (variablesUsed > 1) {
        m_isLinear = tupleSum == 0;
    }
}
