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
        TS_ASSERT( m[ 0 ][ 1 ] == 0 )

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
        int e = m[1][1];
        m[1][2] = e;
        TS_ASSERT( m[1][2] == 2 );
        
        
        
        //Aritmethic
        Matrix m1 = a_matrix_3by2();
        Matrix m2;
        init_matrix(m2, "  [ 0 5 2 ; 1 6 9 ]");
        
        Matrix m3 = m1 + m2;

        Matrix m4 = m1 - m2;
        int scalar = 6;
        Matrix m5 = m1 * 6;
        
        for(int row = 0; row < m3.rows(); row++){
            for(int col = 0; col < m3.cols(); col++){
                TS_ASSERT ( m3[row][col] == m1[row][col] + m2[row][col]);
                TS_ASSERT ( m4[row][col] == m1[row][col] - m2[row][col]);
                TS_ASSERT ( m5[row][col] == m1[row][col] * 6);
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
                std::cout << sum << std::endl;
                std::cout << m7[row][col] << std::endl;
                TS_ASSERT ( m7[row][col] == sum );
            }
        }
        
        
        
        // Illegal operations
//        Matrix mf;
//        mf = m1 * m2;
//        init_matrix(m1, " [ 1 3 ; 0 2 ]");
//        mf = m1 + m2; // Illegal, wrong size!
        
    }
};

#endif

