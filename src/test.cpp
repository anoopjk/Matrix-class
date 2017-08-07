#include <iostream>
#include <ctime>
#include "Matrix.h"  

using namespace std;

int main()
{

    cout << "enter the rows and columns for the matrix" << endl;

	size_t rows, cols; 

    cout << "enter the rows: " ;
    cin >> rows ;
    cout << "enter the cols: ";
    cin >> cols;

     ofstream transpose_out, original_out;
     transpose_out.open ("../transpose_out.txt");
     original_out.open ("../orignal_out.txt");


    Matrix <double> src(rows, cols);

    cout << "before fillMatrix" << endl;
    double min_value = 0;
    double max_value = 9;
    src.fillMatrix(min_value, max_value);

    cout << "src(0,0): " << src(0,0) << endl;
    src.printToFile(original_out);

    clock_t t1 = clock();
    
    Matrix <double> dst = src.transpose();
    dst.printToFile(transpose_out);


     clock_t t2 = clock();
     double timeSec1 = (t2- t1)/ static_cast<double>(CLOCKS_PER_SEC);
     cout << "time taken: " << timeSec1 << " secs" << endl;

     ////////////////////////////////////////////////////////////////////////////////
    ofstream AB_out, ABtrans_out, A_out, B_out;
    A_out.open ("../A.txt");
    B_out.open ("../B.txt");
    AB_out.open ("../AB.txt");

    ABtrans_out.open ("ABtrans.txt");
    size_t rowsA, colsA, rowsB, colsB; 
    cout << "Matrix multiplication part" << endl;
    cout << "Matrix A, enter rowsA: " ;
    cin >>  rowsA ;
    cout << "enter colsA: " ;
    cin >> colsA;

    cout << "Matrix B, enter rowsB: " ;
    cin >>  rowsB ;
    cout << "enter colsB: " ;
    cin >> colsB;

    assert( rowsB == colsA);

    Matrix <double> A(rowsA, colsA);
    Matrix <double> B(rowsB, colsB);

    //Matrix <double> AB;

    A.fillMatrix(min_value, max_value);
    B.fillMatrix(min_value, max_value);

    A.printToFile(A_out);
    B.printToFile(B_out);


    cout << "before AB" << endl;
    clock_t t3 = clock();

    Matrix <double> AB=A*B;
    
    clock_t t4 = clock();
    double timeSec2 = (t4- t3)/ static_cast<double>(CLOCKS_PER_SEC);
    cout << "time taken for transposeBlock: " << timeSec2 << " secs" << endl;
    AB.printToFile(AB_out);
    cout << AB;

    A.set(0,0,-1);
    //cout << A;

    Matrix <double> C(2,3);
    double arr[6] = {1.0,2.0,3.0,4.0,5.0,6.0};
    C.feedArray(arr);

    cout << C;

    cout << "before main return " << endl;

    return 0;

}
