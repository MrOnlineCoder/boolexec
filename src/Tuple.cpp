#include <Tuple.hpp>

#include <iostream>

Tuple::Tuple(std::size_t size, std::size_t base) {
    m_size = size;
    m_base = base;

    m_data = new int[m_size];

    for (std::size_t sz = 0; sz < size; sz++) {
        m_data[sz] = 0;
    }
}

int Tuple::getDigitAt(std::size_t index) {
    return m_data[index];
}

void Tuple::increment() {
    m_data[m_size - 1]++;

    std::size_t lp = m_size - 1;

    while (m_data[lp] >= m_base) {
        m_data[lp] = 0;
        m_data[lp - 1]++;
        lp--;
    }
}

bool Tuple::isFinal() {
    for (std::size_t i = 0; i < m_size; i++) {
        if (m_data[i] != m_base - 1) return false;
    }

    return true;
}

Tuple::~Tuple() {
    delete m_data;
}

void Tuple::dump() {
    for (int i = 0; i < m_size; i++) {
        std::cout << m_data[i] << " ";
    }
}

void Tuple::setDigitAt(std::size_t index, int value) {
    m_data[index] = value;
}

int* Tuple::getDataPtr() {
    return m_data;
}

std::size_t Tuple::getSize() {
    return m_size;
}