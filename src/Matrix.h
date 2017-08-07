#include <iostream>
#include <random>
#include <fstream>
#include <cmath>
#include <assert.h>  

using namespace std;

/**
*\mainpage Description
*Templatized Matrix class provides cache friendly 1d aray implementation of Matrix Multiplication and Matrix Transpose.
*the helper functions include printing the matrix to a file, outputting to terminal, reading from console terminal,
*populating a Matrix using random numbers, using an array to fill the Matrix etc.,
*/

template <class T>
class Matrix
{
///Matrix class contains 3 public members, 1.rows, 2.cols and 3. *Mat  

public:
    ///1. rows (rows of the Matrix)
    size_t rows;
    ///2. cols (columns of the Matrix)
    size_t cols;
    ///3. *Mat (pointer to the 1d array, storing the matrix elements)
    T *Mat;

    ///constructor which initializes the rows and cols to 0
    /**USAGE:
    *@code
    Matrix <double> M; 
    *@endcode
    *creates Matrix of type double with 0 rows and 0 columns
    **/
    Matrix()
    {
        this->rows = 0;
        this->cols = 0;
        //this->double *src = new double[];

    }

    ///constructor which takes two arguments of type size_t to set the rows and cols of the Matrix
    /**USAGE:
    *@code
    Matrix <double> M(2,3);
    *@endcode
    *creates Matrix of type double with 2 rows and 3 columns
    **/
    Matrix(size_t rows, size_t cols)
    {
        assert(rows>= 0 && cols >= 0); ///< rows and cols should be positive numbers

         this->rows = rows;
         this->cols = cols;
         ///allocate the array size for the respective datatype provided by the user 
         this->Mat = new T[rows*cols];

         ///initialize all the values to zeros
        for(size_t i = 0; i < cols*rows; ++i)
        {
            this->Mat[i] = static_cast<T>(0);

        }

    }
     ///destructor for deleting Matrix
    ~Matrix()
     {
           delete [] Mat;

     }
     ///getter function which returns value at the position of 'i'th row and 'j'th column of the Matrix
     /**USAGE:
    *
    *@code 
    double M23 = M(2,3);
    *@endcode
    *double variable M23 gets assigned the value of M(2,3)
    **/
     T operator()( size_t i, size_t j ) const
     {
        ///checks for the validity of i and j values
        if (i >= rows || j >= cols || i <0 || j <0) {
            cerr << "Index out of bounds" << endl;
            exit ;
        }
         return Mat[ i * cols + j ];
     }

     ///setter function to modify the value at the position of 'i'th row and 'j'th column of the Matrix
      /**USAGE:
    *@code
    M.set(2,3,9.5);
    *@endcode
    *the value at M(2,3) gets changed to 9.5
    **/
    void  set(size_t i, size_t j, T val) 
     {
        ///checks for the validity of i and j values
        if (i >= rows || j >= cols || i <0 || j <0 || std::isnan(val)) {
            cerr << "Index out of bounds" << endl;
            exit ;
        }
          Mat[ i*cols + j ] = val;
     }

    /// getter function which returns value at the position of 'i'th row and 'j'th column of the Matrix
     T& operator()( size_t i, size_t j ) 
     {
        ///checks for the validity of i and j values
        if (i >= rows || j >= cols || i <0 || j <0) {
            cerr << "Index out of bounds" << endl;
            exit ;
        }
         return Mat[ i * cols + j ];
     }
    



    ///populates a matrix using random numbers between the bounds provided by the user
      /**USAGE:
    *@code
    M.fillMatrix(0.3, 9.1);
    *@endcode
    *populates M with values between 0.3 and 9.1
    **/
    void fillMatrix(const T lower_bound, const T upper_bound)
    {
        ///checks if the bounds are nan values
        if (std::isnan(lower_bound ) || std::isnan(upper_bound))
        {
            cerr << "enter valid bounds" << endl;
            exit;
        }
           
        uniform_real_distribution<T> unif(lower_bound, upper_bound);

        random_device rand_dev;          // Use random_device to get a random seed.

        mt19937 rand_engine(rand_dev()); // mt19937 is a good pseudo-random number 
                                              // generator.

        for(size_t i = 0; i < cols*rows; ++i)
        {
            this->Mat[i] = unif(rand_engine);
           //cout << A[i] << " , " << endl;

        }

    }

    /// populates a Matrix using the provided array elements in row major order
      /**USAGE:
    *@code 
    int arr[6] = {1,2,3,4,5,6};
    M.feedArray(arr);
    *@endcode
    *populates M with the values of arr (which is of the same datatype as M)
    **/
    void feedArray(T *arr)
    {

        for(size_t i=0; i< this->rows; ++i)
        {
            for(size_t j=0; j< this->cols; ++j)
            {

               this->Mat[i*(this->cols) + j] = arr[i*this->cols + j]   ;
               
            }

        }

    }

    /// prints the Matrix to the output file ofstream object given by the user
      /**USAGE:
    *@code
    ofstream output_file("output.txt");
    M.printToFile(output_file);
    *@endcode
    *prints the Matrix to a ofstream file object
    **/
    void printToFile(ofstream &out) const
    {
        for(size_t i=0; i< this->rows; ++i)
        {
            for(size_t j=0; j< this->cols; ++j)
            {
               out << this->Mat[i*cols + j] << " , "; 
            }
            out << endl;

        }


    }

    ///Transposes Matrix without tiling
      /**USAGE:
    *@code
    Matrix<double> Mtrans = M.transpose();
    *@endcode
    *using the regular transpose
    *@code
    Matrix<double> Mtrans = M.transposeBlock();
    *@endcode 
    *using the block transpose
    *@note 
    * The Mtrans matrix initialization should be done as shown above
    **/
    Matrix transpose() const{

        Matrix dst(this->cols, this->rows);

        for(size_t i=0; i< this->rows; ++i)
        {
            for(size_t j=0; j< this->cols; ++j)
            {
                dst[j*this->rows + i] = this->Mat[i*this->cols + j];
            }
        }

        return dst;
    }
    /// Uses tiling/blocking to transpose a Matrix
      /**USAGE:
    *@code
    Matrix<double> Mtrans = M.transposeBlock();
    *@endcode 
    *using the block transpose
    *@note 
    * The Mtrans matrix initialization should be done as shown above
    **/
    Matrix transposeBlock() const {

            Matrix dst(this->cols, this->rows);
            size_t blocksize = 32; /// block size 32 has been used
            for (size_t i = 0; i < this->rows; i += blocksize) {
            for (size_t j = 0; j < this->cols; j += blocksize) {
                // transpose the block beginning at [i,j]
                for (size_t k = i; k < i+ blocksize && k < this->rows; ++k) {
                    for (size_t l = j; l < j + blocksize && l < this->cols; ++l) {
                        dst.Mat[k + l*this->rows] = this->Mat[l + k*this->cols];
                    }
                }
            }
        }

        return dst;
    }

    ///Uses overloaded operator* to perform Matrix Multiplication
     /**USAGE:
    *@code
    Matrix<double> AB = A*B;
    *@endcode 
    *@note 
    * The AB matrix initialization should be done as shown above
    **/
    Matrix operator *(const Matrix &B) const
    {
        assert(B.rows == this->cols);

        Matrix B_trans = B.transposeBlock(); ///< using Block Matrix Transpose for faster computation

        Matrix AB(this->rows, B.cols);

        for (size_t i = 0; i < this->rows ; ++i) {
 
            for(size_t j = 0; j < B.cols; ++j) {

                double sum = 0.0;
                for(size_t k = 0; k < this->cols ; ++k) {
                    sum += this->Mat[i*this->cols + k]*B_trans.Mat[j*B.rows + k];

                    AB.Mat[i*B.cols + j]  = sum;  
                    
                } 
            }
        }
        return AB;

    }

    ///Uses overloaded operator= to perform Matrix Assignment
    /**USAGE:
    *@code
    Matrix<double> A = B;
    *@endcode 
    *@note 
    * The AB matrix initialization should be done as shown above
    **/
    Matrix operator =(const Matrix &B) 
    {

        Matrix dst(B.rows, B.cols);
        for (size_t i = 0; i < B.rows ; ++i) {
 
            for(size_t j = 0; j < B.cols; ++j) {

                    dst.Mat[i*B.cols + j]  = B.Mat[i*B.cols, j];  
                     
            }
        }
        return dst;

    }

private:
    /// getter function which returns value at the index positon in 1d array sequence of the Matrix 
    T& operator[]( int index) const
    {
        ///checks for the validity of index
        if (index >= rows*cols || index < 0) {
            cerr << "Index out of bounds" << endl;
            exit ;
        }
        return this->Mat[index] ;
    }





};
    ///Outputs matrix to console
     /**USAGE:
    *@code
    cout << M << endl;
    *@endcode 
    **/
    template <class T>
    ostream& operator<<(ostream& os, const Matrix<T> & m)
    {
        for(size_t i=0; i< m.rows; ++i)
        {
            for(size_t j=0; j< m.cols; ++j)
            {

               os << m.Mat[i*m.cols + j]  << ", "; 
            }
            cout << endl;

        }

        return os;
    }
    ///reads matrix from console
     /**USAGE:
    *@code
    cin << M ;
    *@endcode 
    **/
    template < class T>
    istream& operator>>(istream& is, Matrix<T> & m)
    {
        for(size_t i=0; i< m.rows; ++i)
        {
            for(size_t j=0; j< m.cols; ++j)
            {

               is >> m.Mat[i*m.cols + j] ;
               
            }

        }

        return is;
    }


