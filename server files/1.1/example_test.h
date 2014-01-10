#ifndef MATRIX_TEST_H_INCLUDED
#define MATRIX_TEST_H_INCLUDED

#include "Matrix.h"
#include "../cxxtest/cxxtest/TestSuite.h"
#include <fstream>
#include <sstream>
#include <iostream>

class MatrixTestSuite : public CxxTest::TestSuite
{

    Matrix a_matrix_3by2() {    // [ 1 3 5 ]
        Matrix m;               // [ 0 2 0 ]
        std::stringstream s("  [ 1 3 5 ; 0 2 0 ]");
        s >> m;
        return m;
    }

    void init_matrix( Matrix& m, const char* file )
    {
        std::stringstream stream( file );   
        stream >> m;
    }

public:
    void testIndexOperator ( )
    {
        Matrix m( 2, 2 );
        TS_ASSERT( m[ 0 ][ 1 ] == 0 );
        TS_ASSERT( m[0][0] == 0);
        TS_ASSERT( m.cols() == 2 && m.rows() == 2);

        m = a_matrix_3by2();
        TS_ASSERT( m[ 0 ][ 0 ] == 1 );

        init_matrix(m, "  [ 1 3 5 ; 0 2 1 ]");
        TS_ASSERT( m[ 0 ][ 0 ] == 1 );

        std::stringstream ss;
        ss << m;
        ss >> m;
        TS_ASSERT( m[ 0 ][ 0 ] == 1 );
        
        TS_ASSERT( m[1][1] == 2 );
        TS_ASSERT( m[1][2] == 1 );
        int val = m[1][1];
        m[1][2] = val;
        TS_ASSERT( m[1][2] == 2 );
        
        Matrix a = Matrix(5);
        TS_ASSERT( a.cols() == 5);
        TS_ASSERT( a.rows() == 5);
        for(int row = 0; row < a.rows(); row++){
            for(int col = 0; col < a.cols(); col++){
                if(row == col){
                    TS_ASSERT(a[row][col] == 1);
                }else{
                    TS_ASSERT(a[row][col] == 0);
                }
            }
        }
        Matrix b;
        TS_ASSERT(b.rows() == 0 && b.cols() == 0);
        
        Matrix c = a_matrix_3by2();
        
        Matrix::matrix_row & mr = c[0];
        mr[1] =55;
        
        TS_ASSERT(mr[0] == 1 && mr[1] == 55 && mr[2] == 5);
        TS_ASSERT(c[0][0] == mr[0] && c[0][1] == mr[1] && c[0][2] == mr[2]);
        
        const Matrix d = a_matrix_3by2();
        const Matrix::matrix_row & mr2 = d[0];
        TS_ASSERT(mr2[0] == 1 && mr2[1] == 3 && mr2[2] == 5);
        try {
            int i = mr[3];
            throw std::runtime_error( "The returned row has the wrong size." );
        } catch (const std::out_of_range& oor) {
            //All good!
        }
        try {
            int i = mr2[3];
            throw std::runtime_error( "The returned row has the wrong size." );
        } catch (const std::out_of_range& oor) {
            //All good!
        }
        
        
        
        //Aritmethic
        Matrix m1 = a_matrix_3by2();
        Matrix m2;
        init_matrix(m2, "  [ 0 5 2 ; 1 6 9 ]");
        TS_ASSERT(m2.rows() == 2);
        TS_ASSERT(m2.cols() == 3);
        
        Matrix m3 = m1 + m2;

        Matrix m4 = m1 - m2;
        int scalar = 6;
        Matrix m5 = m1 * 6;
        Matrix m14;
        try {
            m14 = 6 * m1;
            //All good!
        } catch (const std::out_of_range& oor) {
            throw std::runtime_error( "Something wrong with * operator with int to the left." );
        }
        
        TS_ASSERT (m14.rows() == m1.rows() && m14.cols() == m1.cols());
        Matrix m8 = -m1;
        Matrix m11 = m1 * 0;
        Matrix m12 = Matrix(m3);
        Matrix m13 = Matrix(10);
        m13 = m3;
        TS_ASSERT(m13.cols() == m3.cols() && m13.rows() == m3.rows());
        
        
        for(int row = 0; row < m3.rows(); row++){
            for(int col = 0; col < m3.cols(); col++){
                TS_ASSERT ( m3[row][col] == m1[row][col] + m2[row][col]);
                TS_ASSERT ( m4[row][col] == m1[row][col] - m2[row][col]);
                TS_ASSERT ( m5[row][col] == m1[row][col] * 6);
                TS_ASSERT ( m14[row][col] == 6 * m1[row][col]);
                TS_ASSERT ( m8[row][col] == m1[row][col] * -1);
                TS_ASSERT ( m11[row][col] == 0);
                TS_ASSERT ( m12[row][col] == m3[row][col]);
                TS_ASSERT ( m13[row][col] == m3[row][col]);
            }
        }
       
        
        Matrix m6;
        init_matrix(m6, "  [ 2 0 ; 5 4 ; 7 9 ]");
        Matrix m7 = m2 * m6;
        for(int row = 0; row < m7.rows(); row++){
            for(int col = 0; col < m7.cols(); col++){
                int sum = 0;
                for(int i = 0; i < m2.cols(); i++){
                    sum += (m2[row][i] * m6[i][col]);
                }
                TS_ASSERT ( m7[row][col] == sum );
            }
        }
        
        Matrix m9 = m2;
        Matrix m10 = m2.transpose();
        for(int row = 0; row < m9.rows(); row++){
            for(int col = 0; col < m9.cols(); col++){
                TS_ASSERT( m9[row][col] == m10[col][row]);
            }
        }
        

        
        
        
        
        
        
        // Illegal operations
        Matrix mf;
        Matrix me = a_matrix_3by2();
        Matrix me2 = a_matrix_3by2().transpose();
        try {
            mf = me * me;
            throw std::runtime_error( "We can multiply matrices that should not be allowed." );
        } catch (const std::out_of_range& oor) {
            //All good!
        }
        
        try{
            mf = me + me2;
            throw std::runtime_error( "We can do addition on different sized matrices." );
        } catch (const std::out_of_range& oor) {
            //All good!
        }
        
        try{
            mf = me - me2;
            throw std::runtime_error( "We can do subtraction on different sized matrices." );
        } catch (const std::out_of_range& oor) {
            //All good!
        }
        
        try{
            int i = me[2][0];
            throw std::runtime_error( "We can access elements out of range." );
        } catch (const std::out_of_range& oor) {
            //All good!
        }
        
        try{
            int i = me[0][3];
            throw std::runtime_error( "We can access elements out of range." );
        } catch (const std::out_of_range& oor) {
            //All good!
        }
        
        
    }
};

#endif

