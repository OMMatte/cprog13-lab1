#include "Matrix.h"
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>

std::istream & operator>> (std::istream & in, Matrix & matrix) {
    //Read the stream buffer into a stringstream which can construct the string.
    //This to read the whole chunk of the stream into the input string in once.
    std::stringstream sstr;
    sstr << in.rdbuf();
    std::string input = sstr.str();
    
    //Erase all the newline characters, if any.
    input.erase(std::remove(input.begin(), input.end(), '\n'), input.end());
    
    matrix = Matrix();
    
    Matrix::matrix_row row;
    std::size_t prev;
    std::size_t next = prev = input.find("[") + 1;
    while((next = input.find(" ", next + 1)) != std::string::npos) {
        std::string unit = input.substr(prev + 1, next - prev - 1);
        prev = next;
        
        if(unit == ";") {
            matrix.addRow(row);
            row.clear();
        } else {
            row.push_back(std::stoi(unit));
        }
    }
    
    if(row.size() != 0) {
        matrix.addRow(row);
    }
    
    return in;
}

std::ostream & operator<< (std::ostream & out, Matrix & matrix) {

    for(unsigned int row = 0; row < matrix.rows(); row++) {
        out << (row == 0 ? "[ " : "; ");
        
        for(unsigned int col = 0; col < matrix.cols(); col++) {
            out << std::to_string(matrix[row][col]) << " ";
        }
        
        if(row == matrix.rows()-1) {
            out << "]";
        } else {
            out << std::endl;
        }
    }
    
    return out;
}

Matrix operator* (int value, const Matrix & matrix) {
    return matrix * value;
}

Matrix::Matrix() : Matrix(0, 0) {}

Matrix::Matrix(std::size_t size) : Matrix(size, size) {
    for(index i = 0; i < size; i++) {
        mData[i][i] = 1;
    }
}

Matrix::Matrix(std::size_t rows, std::size_t cols) : mData(Vector<matrix_row>(rows, matrix_row(cols))), mRows(rows), mCols(cols) {}

Matrix::Matrix(const Matrix & matrix) : mData(matrix.mData), mRows(matrix.mRows), mCols(matrix.mCols) {}

Matrix::Matrix(Matrix && matrix) : mData(std::move(matrix.mData)), mRows(matrix.mRows), mCols(matrix.mCols) {}

Matrix::~Matrix() {}

Matrix & Matrix::operator=(const Matrix & matrix) {
    //TODO: Is this okay way of copying the data?
    mData = matrix.mData;
    mRows = matrix.mRows;
    mCols = matrix.mCols;
    
    return *this;
}

Matrix & Matrix::operator=(Matrix && matrix) {
    mData = std::move(matrix.mData);
    mRows = matrix.mRows;
    mCols = matrix.mCols;
    
    return *this;
}

void Matrix::assureRows(const Matrix & matrix) const {
    if(rows() != matrix.rows()) {
        throw std::invalid_argument("Matrix got wrong dimension");
    }
}

void Matrix::assureCols(const Matrix & matrix) const {
    if(cols() != matrix.cols()) {
        throw std::invalid_argument("Matrix got wrong dimension");
    }
}

void Matrix::assureSize(const Matrix & matrix) const {
    assureRows(matrix);
    assureCols(matrix);
}

Matrix Matrix::everyOperation(const std::function<int (int)> & operation) const {
    return everyOperation([operation] (index, index, int cell) { return operation(cell); });
}

Matrix Matrix::everyOperation(const std::function<int(index, index, int)> & operation) const {
    Matrix result(mRows, mCols);
    
    for(int row = 0; row < mRows; row++) {
        for(int col = 0; col < mCols; col++) {
            result[row][col] = operation(row, col, mData[row][col]);
        }
    }
    
    return result;
}

Matrix Matrix::pairWiseOperation(const Matrix & matrix, const std::function<int(int, int)> & operation) const {
    assureSize(matrix);
    
    return everyOperation([matrix, operation] (index row, index col, int self) { return operation(self, matrix[row][col]); });
}

Matrix Matrix::operator+ (const Matrix & matrix) const {
    return pairWiseOperation(matrix, [](int self, int other) { return self + other; });
}

Matrix Matrix::operator- (const Matrix & matrix) const {
    return pairWiseOperation(matrix, [] (int self, int other) { return self - other; });
}

Matrix Matrix::operator- () const {
    return everyOperation([] (int cell) { return -cell; });
}

Matrix Matrix::operator* (int value) const {
    return everyOperation([value] (int cell) { return value * cell; });
}

Matrix Matrix::operator* (const Matrix & matrix) const {
    if(cols() != matrix.rows()) {
        throw std::invalid_argument("Matrix got wrong dimension");
    }
    
    const std::size_t LENGTH = matrix.rows();
    
    Matrix result(rows(), matrix.cols());

    auto multiplyRowCol = [this, & LENGTH, & matrix] (index row, index col) {
        int result = 0;
        
        for(index i = 0; i < LENGTH; i++) {
            result += mData[row][i] * matrix[i][col];
        }
        
        return result;
    };
    
    for(index row = 0; row < rows(); row++) {
        for(index col = 0; col < matrix.cols(); col++) {
            result[row][col] = multiplyRowCol(row, col);
        }
    }
    
    return result;
}

Matrix & Matrix::transpose() {
    auto newData = Vector<matrix_row>(cols(), matrix_row(rows()));
    
    const std::size_t ROWS = rows();
    const std::size_t COLS = cols();
    
    for(index row = 0; row < ROWS; row++) {
        for(index col = 0; col < COLS; col++) {
            newData[col][row] = mData[row][col];
        }
    }
    
    //TODO: Is this right?
    mData = newData;
    mRows = COLS;
    mCols = ROWS;
    
    return *this;
}

Matrix::matrix_row & Matrix::operator[] (index i) {
    if(i >= rows()) {
        throw std::out_of_range("Index out of bounds");
    }
    
    return mData[i];
}

const Matrix::matrix_row & Matrix::operator[] (index i) const {
    if(i >= rows()) {
        throw std::out_of_range("Index out of bounds");
    }
    
    return mData[i];
}

std::size_t Matrix::rows() const {
    return mRows;
}

std::size_t Matrix::cols() const {
    return mCols;
}

void Matrix::addRow(Matrix::matrix_row row) {
    if(row.size() != cols() && cols() != 0) {
        throw std::invalid_argument("Added row must fit in the matrix");
    }
    
    mData.push_back(row);
    mRows++;
    
    if(mCols == 0) {
        mCols = row.size();
    }
}