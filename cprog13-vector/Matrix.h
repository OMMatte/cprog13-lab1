#ifndef MATRIX_H
#define MATRIX_H

#include "kth_cprog_vektor.cpp"
#include <iostream>
#include <stdexcept>

class Matrix {
public:
    typedef unsigned int index;
    
    class matrix_row : private Vector< int > {
    public:
        matrix_row( std::size_t s = 0) : Vector< int >( s ) {}
        using Vector<int>::operator [];
    private:
        friend std::istream & operator>>( std::istream &, Matrix & );
    };
    
    Matrix();
    Matrix(std::size_t, std::size_t);
    Matrix(const Matrix &);
    Matrix(Matrix &&);
    Matrix(int size);
    ~Matrix();
    
    Matrix & operator= (const Matrix &);
    Matrix operator+ (const Matrix &) const throw(std::invalid_argument);
    Matrix operator* (const Matrix &) const throw(std::invalid_argument);
    Matrix operator* (int) const;
    Matrix operator- (const Matrix &) const throw(std::invalid_argument);
    Matrix operator- () const;
    
    Matrix & transpose();
    
    matrix_row & operator[] (index i) throw(std::invalid_argument);
    const matrix_row & operator[] (index i) const throw(std::invalid_argument);
    
    std::size_t rows() const;
    std::size_t cols() const;
    
private:
    Vector< matrix_row >        mData;
    std::size_t                 mRows;
    std::size_t                 mCols;
    
    friend std::istream & operator>> (std::istream &, Matrix &);
    
    void assureRows(const Matrix &) const throw(std::invalid_argument);
    void assureCols(const Matrix &) const throw(std::invalid_argument);
    void assureSize(const Matrix &) const throw(std::invalid_argument);
    Matrix pairWiseOperation(const Matrix &, const std::function<int(int, int)> &) const throw(std::invalid_argument);
    Matrix everyOperation(const std::function<int(int)> &) const;
    Matrix everyOperation(const std::function<int(index, index, int)> &) const;
};

std::istream & operator>> (std::istream &, Matrix & );
std::ostream & operator<< (std::ostream &, Matrix & );
Matrix operator* (int, const Matrix &);

#endif
