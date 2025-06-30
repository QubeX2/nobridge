#ifndef MIKA_VECT_H
#define MIKA_VECT_H

#include <algorithm>
#include <cmath>
#include <initializer_list>
#include <iomanip>
#include <numeric>
#include <stdexcept>
#include <string>
#include <unordered_map>

#include "mika.h"

namespace mika {
    template <typename T, std::size_t N>
    class VecT {
       public:
        // Constructors
        VecT() { m_data.fill(T()); }  // ensure 0
        VecT(std::initializer_list<T> list) {
            if (list.size() != N) throw std::invalid_argument("Wrong number of elements");
            std::copy(list.begin(), list.end(), m_data.begin());
        }

        // Element access
        T& at(size_t index) {
            if (index >= N) {
                throw std::out_of_range("VecT::at: index is out of range");
            }
            return m_data[index];
        }

        const T& at(size_t index) const {
            if (index >= N) {
                throw std::out_of_range("VecT::at: index is out of range (const)");
            }
            return m_data[index];
        }

        T& operator[](std::size_t index) { return m_data[index]; }
        const T& operator[](std::size_t index) const { return m_data[index]; }
        std::array<T, N> data() { return m_data; }
        std::array<T, N> data() const { return m_data; }

        std::unordered_map<std::size_t, std::string> legend() { return m_legend; }
        std::unordered_map<std::size_t, std::string> legend() const { return m_legend; }
        void setLegend(std::unordered_map<std::size_t, std::string> legend) { m_legend = legend; }

        // Iterators
        auto begin() { return m_data.begin(); }
        auto end() { return m_data.end(); }
        auto begin() const { return m_data.begin(); }
        auto end() const { return m_data.end(); }

        // Length (Euclidean norm)
        T length() const {
            T sum = T();
            for (const T& v : m_data) sum += v * v;
            return std::sqrt(sum);
        }
        std::size_t size() const { return N; }

        // Distance to another vector

        // Dot product
        T dot(const VecT& other) const {
            return T(std::inner_product(m_data.begin(), m_data.end(), other.begin(), T{}));
        }

        double distance(const VecT& other) {
            // Ensure vectors have the same dimension
            if (this->size() != other.size()) {
                throw std::invalid_argument(
                    "Vectors must have the same dimension to calculate distance.");
            }

            double sum_of_squares = 0.0;
            for (size_t i = 0; i < this->size(); ++i) {
                double diff = this->at(i) - other.at(i);
                sum_of_squares += diff * diff;
            }

            return std::sqrt(sum_of_squares);
        }

        // Normalized
        VecT normalized() const {
            T len = length();
            if (len == T(0)) throw std::runtime_error("Zero-Length vector");
            VecT result;
            for (std::size_t i = 0; i < N; ++i) result[i] = m_data[i] / len;
            return result;
        }

        T angle(const VecT& other) const {
            T dot = this->dot(other);
            T lenA = this->length();
            T lenB = other.length();

            if (lenA == T(0) || lenB == T(0)) {
                throw std::runtime_error("Angle undefined for zero-length vector");
            }

            T cos = dot / (lenA * lenB);

            // Clamp to [-1, 1] to avoid NaNs from floating point error
            if (cos < T(-1))
                cos = T(-1);
            else if (cos > T(1))
                cos = T(1);

            return std::acos(cos);
        }

        // Angle in Degrees
        T angleDeg(const VecT& other) const {
            return angle(other) * T(180) / T(M_PI);  // Or use std::numbers::pi if C++20
        }

        // Bytes
        const char* asBytes() const { return reinterpret_cast<const char*>(m_data.data()); }

        char* asBytes() { return reinterpret_cast<char*>(m_data.data()); }
        std::size_t byteSize() const { return sizeof(T) * N; }

       private:
        std::array<T, N> m_data;
        mutable std::string m_cached_str;
        std::unordered_map<std::size_t, std::string> m_legend;
    };

    template <typename T, std::size_t N>
    inline std::ostream& operator<<(std::ostream& os, const mika::VecT<T, N>& t) {
        os << std::fixed << std::setprecision(2);
        os << "VecT (";
        mika::array::join(os, t.data(), ", ", t.legend());
        os << "), \033[31mSize:\033[0m " << t.size();
        os << ", \033[31mLength:\033[0m " << t.length();
        os << "\n";
        return os;
    }

}  // namespace mika
#endif
