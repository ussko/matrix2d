#pragma once

#include <ostream>
#include <sstream>

template <typename T>
class Matrix2d
{
public:
    Matrix2d(const size_t col_size, const size_t row_size)
    :   _row_size{row_size},
        _col_size{col_size},
        _data{new T[_row_size * _col_size]}
    {
        for (size_t i = 0; i < _row_size * _col_size; ++i)
            _data[i] = T{};
    }
    Matrix2d(const Matrix2d &rhs)
    :   Matrix2d(rhs._col_size, rhs._row_size)
    {
        for (size_t i = 0; i < _row_size * _col_size; ++i)
            _data[i] = rhs._data[i];
    }
    Matrix2d(Matrix2d &&rhs) noexcept
    :   _row_size{rhs._row_size},
        _col_size{rhs._col_size},
        _data{rhs._data}
    {
        rhs._data = nullptr;
        rhs._row_size = 0;
        rhs._col_size = 0;
    }
    ~Matrix2d()
    {
        delete[] _data;
    }

    // helper class for operator[]
    class Row
    {
    public:
        Row(const size_t size, T * const data)
        :   _size{size},
            _data{data}
        {}
        T& operator[](const size_t col)
        {
            if (col >= _size)
                throw std::range_error(dynamic_cast<std::ostringstream &&>
                                       (std::ostringstream{} << "col index " << col
                                        << " out of range").str());
            return _data[col];
        }

    private:
        size_t _size{0};
        T *_data{nullptr};
    };

    // to get an element use matrix[row][col]
    Row operator[](size_t row) const
    {
        if (row >= _col_size)
            throw std::range_error(dynamic_cast<std::ostringstream &&>
                                   (std::ostringstream{} << "row index " << row
                                                         << " out of range").str());
        return Row{_row_size, _data + row * _row_size};
    }
    T& at(size_t row, size_t col)
    {
        return (*this)[row][col];
    }

    // range-for
    T* begin()
    {
        return _data;
    }
    T* end()
    {
        if (!_data)
            return nullptr;
        return _data + (_row_size * _col_size);
    }

    // assignment
    Matrix2d &operator=(const Matrix2d &rhs)
    {
        if (&rhs == this)
            return *this;
        if (_data)
            delete[] _data;

        _row_size = rhs._row_size;
        _col_size = rhs._col_size;
        _data = new T[_row_size * _col_size];

        for (size_t i = 0; i < _row_size * _col_size; ++i)
            _data[i] = rhs._data[i];
        return *this;
    }
    Matrix2d &operator=(Matrix2d &&rhs) noexcept
    {
        if (&rhs == this)
            return *this;
        if (_data)
            delete[] _data;

        _row_size = rhs._row_size;
        _col_size = rhs._col_size;
        _data = rhs._data;

        rhs._row_size = 0;
        rhs._col_size = 0;
        rhs._data = nullptr;

        return *this;
    }

    // addition
    friend Matrix2d operator+(const Matrix2d &lhs, const Matrix2d &rhs)
    {
        auto result = Matrix2d{std::max(lhs._col_size, rhs._col_size),
                               std::max(lhs._row_size, rhs._row_size)};
        for (size_t row = 0; row < lhs._col_size; ++row)
            for (size_t col = 0; col < lhs._row_size; ++col)
                result[row][col] += lhs[row][col];
        for (size_t row = 0; row < rhs._col_size; ++row)
            for (size_t col = 0; col < rhs._row_size; ++col)
                result[row][col] += rhs[row][col];
        return result;
    }
    Matrix2d& operator+=(const Matrix2d &rhs)
    {
        auto col_size_new = std::max(_col_size, rhs._col_size);
        auto row_size_new = std::max(_row_size, rhs._row_size);
        auto data_new = new T[row_size_new * col_size_new];

        for (size_t i = 0; i < row_size_new * col_size_new; ++i)
            data_new[i] = T{};

        for (size_t row = 0; row < _col_size; ++row)
            for (size_t col = 0; col < _row_size; ++col)
                data_new[row * row_size_new + col] = _data[row * _row_size + col];

        for (size_t row = 0; row < rhs._col_size; ++row)
            for (size_t col = 0; col < rhs._row_size; ++col)
                data_new[row * row_size_new + col] += rhs._data[row * rhs._row_size + col];

        delete [] _data;
        _data = data_new;
        _row_size = row_size_new;
        _col_size = col_size_new;

        return *this;
    }

    // concatenation
    friend Matrix2d operator|(const Matrix2d &lhs, const Matrix2d &rhs)
    {
        auto result = Matrix2d{std::max(lhs._col_size, rhs._col_size),
                               lhs._row_size + rhs._row_size};
        for (size_t row = 0; row < lhs._col_size; ++row)
            for (size_t col = 0; col < lhs._row_size; ++col)
                result[row][col] = lhs[row][col];
        for (size_t row = 0; row < rhs._col_size; ++row)
            for (size_t col = 0; col < rhs._row_size; ++col)
                result[row][lhs._row_size + col] = rhs[row][col];
        return result;
    }
    Matrix2d& operator|=(const Matrix2d &rhs)
    {
        auto col_size_new = std::max(_col_size, rhs._col_size);
        auto row_size_new = _row_size + rhs._row_size;
        auto data_new = new T[row_size_new * col_size_new];

        for (size_t i = 0; i < row_size_new * col_size_new; ++i)
            data_new[i] = T{};

        for (size_t row = 0; row < _col_size; ++row)
            for (size_t col = 0; col < _row_size; ++col)
                data_new[row * row_size_new + col] = _data[row * _row_size + col];

        for (size_t row = 0; row < rhs._col_size; ++row)
            for (size_t col = 0; col < rhs._row_size; ++col)
                data_new[row * row_size_new + _row_size + col] = rhs._data[row * rhs._row_size + col];

        delete [] _data;
        _data = data_new;
        _row_size = row_size_new;
        _col_size = col_size_new;

        return *this;
    }

    // print
    friend std::ostream& operator<<(std::ostream& os, const Matrix2d &m)
    {
        for (size_t row = 0; row < m._col_size; ++row)
        {
            for (size_t col = 0; col < m._row_size; ++col)
                os << m[row][col] << ' ';
            os << '\n';
        }
        return os;
    }

private:
    size_t _row_size{0};
    size_t _col_size{0};
    T *_data{nullptr};
};
