#ifndef MIKA_VECT_H
#define MIKA_VECT_H

#include <algorithm>
#include <cmath>
#include <initializer_list>
#include <iterator>
#include <stdexcept>

#include "mika.h"

namespace mika {
    template <typename T, std::size_t N>
    class VecT {
       public:
        // Constructors
        VecT() { m_data.fill(T()); }  // ensure 0
        VecT(std::initializer_list<T> list) {
            if (list.size() != N)
                throw std::invalid_argument("Wrong number of elements");
            std::copy(list.begin(), list.end(), m_data.begin());
        }

        // Element access
        T& operator[](std::size_t index) { return m_data[index]; }
        const T& operator[](std::size_t index) const { return m_data[index]; }
        std::array<T, N> data() { return m_data; }
        std::array<T, N> data() const { return m_data; }

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

        // Dot product
        T dot(const VecT& other) const {
            T result = T();
            for (std::size_t i = 0; i < N; ++i)
                result += m_data[i] * other.m_data[i];
            return result;
        }

        // Normalized
        VecT normalized() const {
            T len = length();
            if (len == T(0)) throw std::runtime_error("Zero-Length vector");
            VecT result;
            for (std::size_t i = 0; i < N; ++i) result[i] = m_data[i] / len;
            return result;
        }

        // Angle in radians
        T angle(const VecT& other) const {
            T dot = this->dot(other);
            T lenA = this->length();
            T lenB = other.length();

            if (lenA == T(0) || lenB == T(0)) {
                throw std::runtime_error(
                    "Angle undefined for zero-length vector");
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
            return angle(other) * T(180) /
                   T(M_PI);  // Or use std::numbers::pi if C++20
        }

        // Bytes
        const char* asBytes() const {
            return reinterpret_cast<const char*>(m_data.data());
        }
        std::size_t byteSize() const { return sizeof(T) * N; }

       private:
        std::array<T, N> m_data;
        mutable std::string m_cached_str;
    };

}  // namespace mika
#endif

template <typename T, std::size_t N>
inline std::ostream& operator<<(std::ostream& os, const mika::VecT<T, N>& t) {
    os << "VecT (" << mika::array::join(t.data());
    os << "), Size: " << t.size();
    os << ", Length: " << t.length();
    os << ", Normalized (" << mika::array::join(t.normalized().data()) << ")"
       << std::endl;
    return os;
}
