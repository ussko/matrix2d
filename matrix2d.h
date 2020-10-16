#pragma once

#include <ostream>
#include <sstream>

template <typename T, size_t ROW, size_t COL>
class Matrix2d
{
public:
    Matrix2d()
    :   _data{new T[ROW * COL]}
    {
    }
    Matrix2d(const Matrix2d &rhs)
    :   Matrix2d()
    {
        for (size_t i = 0; i < ROW * COL; ++i)
            _data[i] = rhs._data[i];
    }
    Matrix2d(Matrix2d &&rhs) noexcept
    {
        _data = rhs._data;
        rhs._data = nullptr;
    }
    ~Matrix2d()
    {
        delete[] _data;
    }

    T& operator[](size_t n)
    {
        if (n >= ROW * COL)
            throw std::range_error(dynamic_cast<std::ostringstream &&>(std::ostringstream{} << "index " << n << " out of range").str());
        return _data[n];
    }
    T* begin()
    {
        return _data;
    }
    T* end()
    {
        if (!_data)
            return nullptr;
        return _data + (ROW * COL);
    }
    Matrix2d &operator=(const Matrix2d &rhs)
    {
        if (&rhs == this)
            return *this;
        if (_data)
            delete[] _data;
        _data = new T[ROW * COL];
        for (size_t i = 0; i < ROW * COL; ++i)
            _data[i] = rhs._data[i];
        return *this;
    }
    Matrix2d &operator=(Matrix2d &&rhs) noexcept
    {
        if (&rhs == this)
            return *this;
        if (_data)
            delete[] _data;
        _data = rhs._data;
        rhs._data = nullptr;
        return *this;
    }
    friend Matrix2d operator+(const Matrix2d &lhs, const Matrix2d &rhs)
    {
        auto result = Matrix2d{};
        for (size_t i = 0; i < ROW * COL; ++i)
            result._data[i] = lhs._data[i] + rhs._data[i];
        return result;
    }
    Matrix2d& operator+=(const Matrix2d &rhs)
    {
        for (size_t i = 0; i < ROW * COL; ++i)
            _data[i] += rhs._data[i];
        return *this;
    }
    friend std::ostream& operator<<(std::ostream& os, const Matrix2d &m)
    {
        for (size_t row = 0; row < ROW; ++row)
        {
            for (size_t col = 0; col < COL; ++col)
                os << m._data[row * COL + col] << ' ';
            os << '\n';
        }
        return os;
    }

private:
    T *_data{nullptr};
};

template <size_t ROW, size_t COL>
using Matrix2dInt = class Matrix2d<int, ROW, COL>;
