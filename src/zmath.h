#pragma once

#ifndef ZMATH_DEF
#define ZMATH_DEF

#include <stdbool.h>
#include <stdio.h>

/*! 
    @brief Flag that if activated will crush the program if an assertion fails.
    @if 0 Then the program wont crash on assert failures.
    @elseif 1 Then the program will crash if an assertion fails.
*/
#define EXIT_ON_ASSERT_FAILURE 1

/*!
    @brief Flag that if activated will print debug information.
    @if 0 Then when a function is called it wont print debug information.
    @elseif 1 Then when a function is called it may print debug information.
*/
#define VISUALIZE_DEBUG 0

/*!
    @brief Flag that if activated will print each step done in a function.
    @if 0 Then when a function is called it wont print each step done in a function.
    @elseif 1 Then when a function is called it may print each step done in a function.
*/
#define VISUALIZE_STEPS 0

/*!
    @attention CHANGE THIS ONLY IF THE ZSTRING.H IN PRESENT IN THE SAME FOLDER OF THIS FILE.

    @brief Flag that if activated will print each number in its rational representation.
    @if 0 Then the program will print every value as a float.
    @elseif 1 Then the program will print every value in its rational representation.
*/
#define VISUALIZE_RATIONAL 0

#define MZ_EQUAL_ERROR      "Dimension mismatch."
#define MZ_ALLOC_ERROR      "Allocation failure."
#define MZ_PROD_ERROR       "Matrix 1 columns not equal to Matrix 2 rows."
#define MZ_DIRECTION_ERROR  "Invalid direction."
#define MZ_SQUARE_ERROR     "Matrix is not square."
#define MZ_NULL_VECTOR       "(null vector)"
#define MZ_NULL_MATRIX       "(null matrix)"

/*!
    @brief Finds the maximum of two values
    @param n the first value
    @param m the second value
    @return the larger element
*/
#define MZ_MAX(n, m) ({\
    __auto_type _a = (n);\
    __auto_type _b = (m);\
    _a > _b ? _a : _b;\
})

/*!
    @brief Finds the minimum of two values
    @param n the first value
    @param m the second value
    @return the smaller element
*/
#define MZ_MIN(n, m) ({\
    __auto_type _a = (n);\
    __auto_type _b = (m);\
    _a < _b ? _a : _b;\
})

/*!
    @brief Alloc macro.
    @param count The size of the chunk to allocate.
    @param type The type of the chunk.
*/
#define MZ_ALLOC(count, type) \
    (type*)calloc((count), sizeof(type))\

/*!
    @brief Swap two values.
    @param n The first value to swap.
    @param m The second value to swap.
*/
#define MZ_SWAP(n, m) ({\
    typeof(n) _tmp = (n);\
    (n) = (m);\
    (m) = _tmp;\
})

/*!
    @brief Checks if the condition is true and printf an error message and exit the program if it is false.
    @param condition The condition to check.
    @param message The message to send if the condition is false.
*/
void _MZ_assert(bool condition, const char* message, const char* filepath, size_t line);

/*!
    @brief Gives a random float random in a certain range.
    @param min The minimum value.
    @param max The maximum value.
    @return a random float value.
*/
float MZ_rand_float( float min, float max );

/*!
    @brief Gives a random int random in a certain range.
    @param min The minimum value.
    @param max The maximum value.
    @return a random int value.
*/
int MZ_rand_int( int min, int max );
   
/*!
    @brief Swap two int numbers.
    @param a the pointer to the first number.
    @param b the pointer to the second number.
*/
void MZ_swap_int(int* a, int* b);

/*!
    @brief Swap two float numbers.
    @param a the pointer to the first number.
    @param b the pointer to the second number.
*/
void MZ_swap_float(float* a, float* b);

/*!
    @brief Prints a single float value.
    @param label The label of the print
    @param value The value to print
*/
void MZ_print_value(FILE* fp, const char* label, const char* name_of_value, float value );

/*!
    @brief Sets a random starting point for producing a series of pseudo-random integers every time the function is called.
    @param seed The seed of the random number generator.
*/
void _MZ_SRAND(unsigned int _Seed);

/*!
    @brief Checks if the array contains a value.
    @param arr The pointer to the array.
    @param n The number of elements in the array 
    @param target The target element.
    @return if the element exists in the array
*/
bool MZ_is_in_array(unsigned int *arr, int n, float target);

/*!
    @brief Checks if the condition is true and printf an error message and exit the program if it is false.
    @param condition The condition to check.
    @param message The message to send if the condition is false.
*/
#define MZ_assert(condition, message) _MZ_assert(condition, message, __FILE__, __LINE__)

/*!
    @brief Sets a random starting point for producing a series of pseudo-random integers every time the function is called.
*/
#define MZ_SRAND() _MZ_SRAND((unsigned)time(NULL) )

#endif // ZMATH_DEF

#ifndef ZVEC_DEF
#define ZVEC_DEF

/*! 

    @brief Struct that holds the dimensions of the vector and its components
    @param dim The dimension of the vector
    @param elements The elements of the vector

*/
typedef struct MZ_Vec{
    size_t dim;
    float *elements;
}MZ_Vec;

extern MZ_Vec NULL_VECTOR;

/*!
    @brief Prints the dimensions of the vector and its components.
    @param fp The file to write the vector.
    @param vector The vector to print.
*/
void MZ_print_vector(FILE* fp, MZ_Vec vector);

/*!
    @brief Prints the dimensions of the vector by its label and its components.
    @param fp The file to write the vector.
    @param label The vector label.
    @param vector The vector to print.
*/
void MZ_print_vector_by_label(FILE* fp, const char* label, MZ_Vec vector);

/*!
    @brief Prints the dimensions of the vector by its index and its components.
    @param fp The file to write the vector.
    @param index The vector index.
    @param vector The vector to print.
*/
void MZ_print_vector_by_index(FILE* fp, int index, MZ_Vec vector);

/*!
    @brief Free the vector and sets its dimensions to 0.
    @param vector The vector to free.
*/
void MZ_free_vector(MZ_Vec* vector);

/*!
    @brief Copy one vector into another.
    @param source The vector to copy.
    @param dest The destination vector.
*/
void MZ_copy_vector_pointer(MZ_Vec* source, MZ_Vec* dest);

/*!
    @brief Allocate memory for the vector.
    @param dim The dimensions of the vector.
    @return The memory allocated. 
*/
MZ_Vec MZ_alloc_vector(size_t dim);

/*!
    @brief Create a new vector of dim dimensions with every component in the vector equal to 0.
    @param dim The dimensions of the vector.
    @return The new vector with every element in the vector equal to 0.
*/
MZ_Vec MZ_new_zero_vector(size_t dim);

/*!
    @brief Create a new vector of dim dimensions with every component in the vector equal to to element.
    @param dim The dimensions of the vector.
    @param element The element of which the vector will be filled.
    @return The new vector with every component in the vector equal to element.
*/
MZ_Vec MZ_new_default_vector(size_t dim, float element);

/*!
    @brief Create a new vector of dim dimensions with every component being randomly generated.
    @param dim The dimensions of the vector.
    @return The new vector with every element in the vector equal to 0.
*/
MZ_Vec MZ_new_random_float_vector(size_t dim, float min, float max);

/*!
    @brief Create a new vector of dimensions with every component being randomly generated.
    @param dim The dimensions of the vector.
    @return The new vector with every element in the vector equal to 0.
*/
MZ_Vec MZ_new_random_int_vector(size_t dim, float min, float max);

/*!
    @brief Create a new vector of dim dimensions.
    @param dim The dimensions of the vector.
    @param ... The components of the vector.
    @return The new vector of dim dimensions.
*/
MZ_Vec _MZ_new_vector(size_t dim, ...);

/*!
    @brief Copy the dimensions and the components from a vector to another one.
    @param source The vector to copy.
    @return The copy of the vector.
*/
MZ_Vec MZ_copy_vector(MZ_Vec source);

/*!
    @brief Sums the two vectors.
    @param vector1
    @param vector2
    @return The sum between vector1 and vector2.
*/
MZ_Vec MZ_add_two_vectors(MZ_Vec vector1 , MZ_Vec vector2);

/*!
    @brief Sums a vector and a scalar.
    @param vector1
    @param scalar
    @return The sum between vector1 and a scalar.
*/
MZ_Vec MZ_add_vector_with_scalar(MZ_Vec vector1 , float scalar);

/*!
    @brief Sums the two vectors.
    @param vector1
    @param vector2
    @return The sum between vector1 and vector2.
*/
MZ_Vec MZ_subtract_two_vectors(MZ_Vec vector1 , MZ_Vec vector2);

/*!
    @brief Subtract a vector and a scalar.
    @param vector1
    @param scalar
    @return The subtraction between vector1 and a scalar.
*/
MZ_Vec MZ_subtract_vector_with_scalar(MZ_Vec vector1 , float scalar);

/*!
    @brief Multiply two vectors.
    @param vector1
    @param vector2
    @return The product between vector1 and  vector2.
*/
MZ_Vec MZ_multiply_two_vectors(MZ_Vec vector1, MZ_Vec vector2);

/*!
    @brief Multiply a vector and a scalar.
    @param vector1
    @param scalar
    @return The product between vector1 and a scalar.
*/
MZ_Vec MZ_multiply_vector_by_scalar(MZ_Vec vector1, float scalar);

/*!
    @brief Divide two vectors.
    @param vector1
    @param vector2
    @return The division between vector1 and  vector2.
*/
MZ_Vec MZ_divide_two_vectors(MZ_Vec vector1, MZ_Vec vector2);

/*!
    @brief Divide a vector and a scalar.
    @param vector1
    @param scalar
    @return The division between vector1 and a scalar.
*/
MZ_Vec MZ_divide_vector_by_scalar(MZ_Vec vector1, float scalar);

/*!
    @brief Raise every component of a vector to the exponent given.
    @param vector The vector to raise.
    @param exponent The exponent of the power.
    @return The vector raised to the exponent.
*/
MZ_Vec MZ_raise_vector_to_exp(MZ_Vec vector, size_t exponent);

/*!
    @brief The cross product between two vectors.
    @param vector1
    @param vector2
    @return The cross product between two vectors.
*/
MZ_Vec MZ_cross_product(MZ_Vec vector1, MZ_Vec vector2);

/*!
    @brief This function return the normalized version of a vector given.
    @param vector The vector to normalize.
    @return The normalized vector.
*/
MZ_Vec MZ_normalized_vector(MZ_Vec vector);

/*!
    @brief This function return the normalized version of a vector given.
    @param vector The vector pointer to normalize.
*/
void MZ_normalize_vector(MZ_Vec* vector);

/*!
    @brief Checks if two vectors are equal.
    @param vector1
    @param vector2
    @return true if they are equal false if otherwise.
*/
bool MZ_are_two_vectors_equal(MZ_Vec vector1, MZ_Vec vector2);

/*!
    @brief Checks if the two vectors are orthogonal.
    @param vector1.
    @param vector2.
    @return true if they are orthogonal false if otherwise
*/
bool MZ_are_two_vectors_orthogonal(MZ_Vec vector1, MZ_Vec vector2);

/*!
    @brief Checks if the vector is normalized.
    @param vector The vector.
    @return true if the vector is normalized.
*/
bool MZ_is_vector_normalized(MZ_Vec vector);

/*!
    @brief This functions return the dot product of two vectors.
    @param vector1
    @param vector2
    @return The dot product of the two vectors.
*/
float MZ_dot_two_vectors(MZ_Vec vector1, MZ_Vec vector2);

/*!
    @brief This function return the magnitude of a vector.
    @param vector 
    @return The magnitude of the vector.
*/
float MZ_magnitude_of_vector(MZ_Vec vector);


/*!
    @brief Find the arguments given 
    @param type The type of the arguments.
    @param ... The variable arguments.
*/
#define MZ_NUM_OF_ARGS(type, ...) (sizeof((type[]){0.0f, ##__VA_ARGS__}) / sizeof(type) - 1) 

/*!
    @brief Create a new vector of dim dimensions.
    @param ... The components of the vector.
    @result The new vector of dim dimensions.
*/
#define MZ_new_vector(...) _MZ_new_vector(MZ_NUM_OF_ARGS(float, ##__VA_ARGS__), __VA_ARGS__)

/*!
    @brief Return the value of the specified vector at the specified index.
    @param vector The vector from which to retrieve the value.
    @param index The index where to retrieve the value.
    @result The value at the specified index.
*/
#define MZ_VALUE_OF_VECTOR_AT(vector, index) (vector.elements[index])

/*!
    @brief Return the value of the specified vector at the specified index.
    @param vector The vector from which to retrieve the value.
    @param index The index where to retrieve the value.
    @result The value at the specified index.
*/
#define MZ_VALUE_OF_VECTOR_POINTER_AT(vector, index) (vector->elements[index])

/*!
    @brief Return the dimensions of the specified vector.
    @param vector The vector from which we pick the dimensions.
    @result The dimensions of the vector.
*/
#define MZ_DIM_OF_VECTOR(vector) (vector.dim)

#endif // ZVEC_DEF

#ifndef MATRIX_DEF
#define MATRIX_DEF

/*!
    @brief The direction of the vec to matrix conversion
    @param HORIZONTAL = 0,
    @param VERTICAL   = 1,
    @param DIR_COUNT  = 2
*/
typedef enum Direction{
    HORIZONTAL = 0,
    VERTICAL = 1,
    DIR_COUNT,
}Direction;


/*!
    @brief The struct that holds the information about a matrix.
    @param rows The number of rows.
    @param cols The number of columns.
    @param elements The elements of the matrix.
*/
typedef struct MZ_Matrix{
    unsigned int rows;
    unsigned int cols;
    float** elements;
}MZ_Matrix;

extern MZ_Matrix NULL_MATRIX;

/*!
    @brief Prints the information about a matrix.
    @param fp The file to write the matrix.
    @param mat The matrix to print.
*/
void MZ_print_matrix(FILE *fp, MZ_Matrix mat);

/*!
    @brief Prints the information about a matrix with a label.
    @param fp The file to write the matrix.
    @param label The label of the matrix.
    @param mat The matrix to print.
*/
void MZ_print_matrix_by_label(FILE *fp, const char* label, MZ_Matrix mat);

/*!
    @brief Prints the information about a matrix with an index.
    @param fp The file to write the matrix.
    @param index The index of the matrix.
    @param mat The matrix to print.
*/
void MZ_print_matrix_by_index(FILE *fp, unsigned int index, MZ_Matrix mat);

/*!
    @brief Frees the matrix and set the rows and cols to 0.
    @param mat The matrix to free.
*/
void MZ_free_matrix(MZ_Matrix* mat);

/*!
    @brief Copy the source matrix to the destination matrix by the pointer.
    @param source The source matrix to copy.
    @param dest The destination matrix.
*/
void MZ_copy_matrix_pointer(MZ_Matrix *source, MZ_Matrix *dest);

/*!
    @brief Allocate memory chunk to the matrix through its rows and cols.
    @param rows The rows of the matrix.
    @param cols The cols of the matrix.
    @return The allocated memory chunk.
*/
MZ_Matrix MZ_alloc_matrix(unsigned int rows, unsigned int cols);

/*!
    @brief Create a matrix of rows * cols dimensions all set to 0.
    @param rows The rows of the matrix.
    @param cols The cols of the matrix.
    @return The matrix of rows * cols dimensions all set to 0.
*/
MZ_Matrix MZ_new_zero_matrix(unsigned int rows, unsigned int cols);

/*!
    @brief Create a matrix of rows * cols dimensions filled with random float values.
    @param rows The rows of the matrix.
    @param cols The cols of the matrix.
    @param min The minimum value.
    @param max The maximum value.
    @return The matrix of rows * cols dimensions filled with random float values.
*/
MZ_Matrix MZ_new_random_float_matrix(unsigned int rows, unsigned int cols, float min, float max);

/*!
    @brief Create a matrix of rows * cols dimensions filled with random int values.
    @param rows The rows of the matrix.
    @param cols The cols of the matrix.
    @param min The minimum value.
    @param max The maximum value.
    @return The matrix of rows * cols dimensions filled with random int values.
*/
MZ_Matrix MZ_new_random_int_matrix(unsigned int rows, unsigned int cols, int min, int max);

/*!
    @brief Create a matrix of rows * cols dimensions all set to a certain value.
    @param rows The rows of the matrix.
    @param cols The cols of the matrix.
    @param value The value used to fill the matrix.
    @return The matrix of rows * cols dimensions all set to a certain value.
*/
MZ_Matrix MZ_new_default_matrix(unsigned int rows, unsigned int cols, float value);

/*!
    @brief Create a matrix of rows * cols dimensions all set to 0.0f except for the main diagonal that is set to 1.0f.
    @param dim The rows of the matrix.
    @return The matrix of rows * cols dimensions all set to 0.0f except for the main diagonal that is set to 1.0f. 
*/
MZ_Matrix MZ_new_identity_matrix(unsigned int dim);

/*!
    @brief Create a matrix of rows * cols dimensions.
    @param rows The rows of the matrix.
    @param cols The cols of the matrix.
    @param numVals the number of values inside the matrix.
    @return The matrix of rows * cols dimensions with the values specified.
*/
MZ_Matrix _MZ_new_matrix(unsigned int rows, unsigned int cols, unsigned int numVals, ...);

/*!
    @brief Create a Row or a Col Matrix from a vector.
    @param source The source vector.
    @param dir Whether it will be a Row Matrix or a Col Matrix.
    @return The vector converted to a Matrix.
*/
MZ_Matrix MZ_Vector_to_matrix(MZ_Vec source, Direction dir);

/*!
    @brief Create a vector from a matrix.
    @param source The source matrix.
    @return The vector converted from the Matrix.
*/
MZ_Vec MZ_Matrix_to_vector(MZ_Matrix source);

/*!
    @brief Create a vector from a matrix's row.
    @param source The source matrix.
    @param row The row that will be converted to a vector.
    @return The vector converted from the Matrix's row.
*/
MZ_Vec MZ_get_vector_from_matrix_row(MZ_Matrix source, unsigned int row);

/*!
    @brief Create a vector from a matrix's col.
    @param source The source matrix.
    @param col The col that will be converted to a vector.
    @return The vector converted from the Matrix's col.
*/
MZ_Vec MZ_get_vector_from_matrix_col(MZ_Matrix source, unsigned int col);

/*!
    @brief Flattens the given matrix in a vertical or horizontal direction
    @param matrix The matrix to flatten
    @param dir The direction in which the matrix will be flattened.
    @return The flatten matrix.
*/
MZ_Matrix MZ_flatten_matrix(MZ_Matrix matrix, Direction dir);

/*!
    @brief Add two matrices together.
    @param matrix1.
    @param matrix2.
    @return The sum of the two matrices.
*/
MZ_Matrix MZ_add_two_matrices(MZ_Matrix matrix1, MZ_Matrix matrix2);

/*!
    @brief Add a scalar to every single element of the matrix.
    @param matrix1.
    @param scalar.
    @return The sum of every single element of the matrix to a certain scalar.
*/
MZ_Matrix MZ_add_matrix_with_scalar(MZ_Matrix matrix1, float scalar);

/*!
    @brief Subtract two matrices together.
    @param matrix1.
    @param matrix2.
    @return The subtracted of the two matrices.
*/
MZ_Matrix MZ_subtract_two_matrices(MZ_Matrix matrix1, MZ_Matrix matrix2);

/*!
    @brief Subtract a scalar to every single element of the matrix.
    @param matrix1.
    @param scalar.
    @return The subtracted of every single element of the matrix to a certain scalar.
*/
MZ_Matrix MZ_subtract_matrix_with_scalar(MZ_Matrix matrix1, float scalar);

/*!
    @brief Multiply two matrices together by the rows per cols product.
    @param matrix1.
    @param matrix2
    @return The product of two matrices together by the rows per cols product.
*/
MZ_Matrix MZ_multiply_two_matrices(MZ_Matrix matrix1, MZ_Matrix matrix2);

/*!
    @brief Multiply a scalar to every single element of the matrix.
    @param matrix1.
    @param scalar.
    @return The product of every single element of the matrix to a certain scalar.
*/
MZ_Matrix MZ_multiply_matrix_by_scalar(MZ_Matrix matrix1, float scalar);

/*!
    @brief Divide two matrices together.
    @param matrix1.
    @param matrix2.
    @return The division of the two matrices.
*/
MZ_Matrix MZ_divide_two_matrices(MZ_Matrix matrix1, MZ_Matrix matrix2);

/*!
    @brief Divide a scalar to every single element of the matrix.
    @param matrix1.
    @param scalar.
    @return The division of every single element of the matrix to a certain scalar.
*/
MZ_Matrix MZ_divide_matrix_by_scalar(MZ_Matrix matrix1, float scalar);

/*!
    @brief Multiply two matrices together.
    @param matrix1.
    @param matrix2.
    @return The product of the two matrices element by elements.
*/
MZ_Matrix MZ_hadamard_multiply_two_matrices(MZ_Matrix matrix1, MZ_Matrix matrix2);


/*!
    @brief Transpose a matrix.
    @param source The matrix to transpose.
    @return The transposed matrix.
*/
MZ_Matrix MZ_transposed_matrix(MZ_Matrix source);

/*!
    @brief Swap two rows in a matrix.
    @param source The original matrix.
    @param row1.
    @param row2.
    @return The matrix in which row1 and row2 have been swapped.
*/
bool MZ_swap_two_matrix_rows(MZ_Matrix *source, unsigned int row1, unsigned int row2);

/*!
    @brief Add two rows in a matrix.
    @param source The original matrix.
    @param row1.
    @param row2.
    @return The matrix in which row1 and row2 have been added.
*/
bool MZ_add_two_matrix_rows(MZ_Matrix *source, unsigned int row1, unsigned int row2);

/*!
    @brief Multiply two rows in a matrix.
    @param source The original matrix.
    @param row1.
    @param row2.
    @return The matrix in which row1 and row2 have been multiplied.
*/
bool MZ_multiply_two_matrix_rows(MZ_Matrix *source, unsigned int row, int scalar);

/*!
    @brief Multiply one row to a scalar and then add it to the other row.
    @param source The original matrix.
    @param row1.
    @param row2.
    @return The matrix in which row2 have been multiplied to a scalar and then add it to the row1.
*/
bool MZ_multiply_add_two_matrix_rows(MZ_Matrix *source, unsigned int row1, unsigned int row2, int scalar);

/*!
    @brief Convert a matrix to its Row Echelon Form.
    @param source The source matrix.
    @return The Row Echelon Form of the Matrix.
*/
void MZ_to_echelon_form(MZ_Matrix *source);

/*!
    @brief Convert a matrix to its Reduced Row Echelon Form.
    @param source The source matrix.
    @return The Reduced Row Echelon Form of the Matrix.
*/
void MZ_to_reduced_echelon_form(MZ_Matrix *source);

/*!
    @brief Append a vector to a matrix.
    @param source The source matrix.
    @param vector The vector to append.
    @return The matrix with the added vector.
*/
MZ_Matrix MZ_append_vector_to_matrix(MZ_Matrix source, MZ_Vec vector);

/*!
    @brief Append a matrix to a matrix.
    @param source The source matrix.
    @param matrix The matrix to append.
    @return The matrix with the added matrix.
*/
MZ_Matrix MZ_append_matrix_to_matrix(MZ_Matrix source, MZ_Matrix matrix);

/*!
    @brief Remove a row and a col from a matrix.
    @param source The source matrix.
    @param remRow The row to remove.
    @param remCol The col to remove.
    @return The sub Matrix with the row and col removed.
*/
MZ_Matrix MZ_get_sub_matrix(MZ_Matrix source, unsigned int remRow, unsigned int remCol);

/*!
    @brief Find the determinant of a matrix.
    @param source The source Matrix.
    @return The determinant of the matrix.
*/
float MZ_determinant_of_matrix_old(MZ_Matrix source);

/*!
    @brief Find the determinant of a matrix through cofactor expansion with an exclusion list.
    @param source The source Matrix.
    @return The determinant of the matrix.
*/
float MZ_determinant_of_matrix(MZ_Matrix source);

/*!
    @brief Calculate the determinant of a matrix through cofactor expansion using an exclusion list.
    @param source The source matrix.
    @param row The row to expand on.
    @param col The new column to exclude.
    @param skipCols The existing list of columns to exclude.
    @param noSkipCols The number of columns in the list to skip.
    @return The determinant.
*/
float _MZ_determinant_of_matrix(MZ_Matrix source,
                            unsigned int row,
                            unsigned int col,
                            unsigned int *skipCols,
                            unsigned int *noSkipCols);

/*!
    @brief Finds the cofactor of a matrix at the specific row and col.
    @param source The source matrix.
    @param row The row index.
    @param col The col index.
    @return The cofactor value.
*/
float MZ_cofactor_of_matrix_at_coord(MZ_Matrix source, unsigned int row, unsigned int col);

/*!
    @brief Calculates the matrix in which the elements are the cofactor of every element of the source matrix.
    @param source The source matrix.
    @return The matrix in which the elements are the cofactor of every element of the source matrix.
*/
MZ_Matrix MZ_cofactor_matrix(MZ_Matrix source);

/*!
    @brief Find the transpose of the cofactor Matrix.
    @param source The source matrix.
    @return The transpose of the cofactor Matrix.
*/
MZ_Matrix MZ_adjugate_matrix(MZ_Matrix source);

/*!
    @brief Checks if the matrix is invertible.
    @param source The source matrix.
    @return true if the matrix is invertible and false otherwise.
*/
bool MZ_is_matrix_invertible(MZ_Matrix source);

/*!
    @brief Calculates the inverse of the source matrix.
    @param source The source matrix.
    @return The inverse of the source matrix.
*/
MZ_Matrix MZ_inverse_of_matrix(MZ_Matrix source);

/*!
    @brief Calculates the inverse of the source matrix using Gaussian Elimination.
    @param source The source matrix.
    @return The inverse of the source matrix.
*/
MZ_Matrix MZ_inverse_of_matrix_by_rref(MZ_Matrix source);

#define sSTRAIGHT_LINE 196
#define STRAIGHT_LINE '_'
#define sLEFT_UP_CORNER 218
#define LEFT_UP_CORNER 'x'
#define sRIGHT_UP_CORNER 191
#define RIGHT_UP_CORNER 'x'
#define sSIDE_CHAR 179
#define SIDE_CHAR '|'
#define sLEFT_DOWN_CORNER 192
#define LEFT_DOWN_CORNER 'x'
#define sRIGHT_DOWN_CORNER 217
#define RIGHT_DOWN_CORNER 'x'

/*! 
    @param matrix The source matrix
    @param x The x coordinate
    @param y The y coordinate
    @return The value of the element at the specified coordinates in the matrix
*/
#define MZ_VALUE_OF_MAT_AT(matrix, x, y) (matrix.elements[x][y])

/*!
    @param matrix The source matrix
    @param x The x coordinate
    @param y The y coordinate
    @return the value of the element at the specified coordinates in the matrix pointer
*/
#define MZ_VALUE_OF_MAT_POINTER_AT(matrix, x, y) (matrix->elements[x][y])

/*!
    @brief Create a matrix of rows * cols dimensions.
    @param rows The rows of the matrix.
    @param cols The cols of the matrix.
    @param numVals the number of values inside the matrix.
    @return The matrix of rows * cols dimensions with the values specified.
*/
#define MZ_new_matrix(rows, cols, ...)  _MZ_new_matrix(rows, cols, rows*cols, __VA_ARGS__)

#endif // ZMATRIX_DEF

#ifdef ZMATH_IMPLEMENTATION

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <time.h>

#if defined (__unix__) || (defined (__APPLE__) && defined (__MACH__))
#include <unistd.h>
#elif _WIN32
#include <process.h>
#endif 

#if VISUALIZE_RATIONAL
#define ZSTRING_IMPLEMENTATION
#include "zstring.h"
#endif

/*
*/
void _MZ_assert(bool condition, const char* message, const char* filepath, size_t line){
    if(!condition){
        fprintf(stderr, "\n[ERROR] : %s:%zu > %s\n", filepath, line, message);
        #if EXIT_ON_ASSERT_FAILURE 
            exit(EXIT_FAILURE);
        #endif
    }
}

/*
*/
float MZ_rand_float( float min, float max ){
    float scale = rand() / (float) RAND_MAX; 
    return min + scale * ( max - min );      
}

/*!
*/
int MZ_rand_int( int min, int max ){
    return (rand() % (max - min)) + min;
}

/*
*/
void MZ_swap_int(int* a, int* b){

    int* tmp = a;
    a = b;
    b = tmp;

}

/*
*/
void MZ_swap_float(float* a, float* b){
    
    float* tmp = a;
    a = b;
    b = tmp;
}

/*
*/
void MZ_print_value(FILE* fp, const char* label, const char* name_of_value, float value ){
    fprintf(fp, "   | %s : {\n   |\t%s: %f;\n   | }\n\n", label, name_of_value, value);
}

/*
*/
bool MZ_is_in_array(unsigned int *arr, int n, float target){
    for (int i = 0; i < n; i++){
        if (arr[i] == target)
        {
            return true;
        }
    }

    return false;
}

void _MZ_SRAND(unsigned int _Seed){
    #if defined (__unix__) || (defined (__APPLE__) && defined (__MACH__))
        srand((_Seed * getpid()); 
    #elif _WIN32
        srand(_Seed * _getpid()); 
    #endif   
}

MZ_Vec NULL_VECTOR = {0, NULL};

/*
*/
void MZ_print_vector(FILE* fp, MZ_Vec vector){

    fprintf(fp ,"\n\n   | Vector of size %zu: {\n   |\t[", MZ_DIM_OF_VECTOR(vector));

    if(vector.elements == NULL){
        fprintf(fp ," %s ", MZ_NULL_VECTOR);
    }else {
        for(size_t i = 0; i < MZ_DIM_OF_VECTOR(vector); i++){
            #if !VISUALIZE_RATIONAL
            fprintf(fp ," %f", MZ_VALUE_OF_VECTOR_AT(vector, i));
            #else
            zstring value = rationalizeFloatToStr(MZ_VALUE_OF_VECTOR_AT(vector, i), 3);
            fprintf(fp, " %s", value.data);
            #endif
            fprintf(fp ,"%c", (i < MZ_DIM_OF_VECTOR(vector) - 1 ? ',' : ' '));
        }
    }
    fprintf(fp ,"]\n   |  }\n\n");
}

/*
*/
void MZ_print_vector_by_label(FILE* fp, const char* label, MZ_Vec vector){

    fprintf(fp ,"\n\n   | [%s] of size %zu: {\n   |\t[", label, MZ_DIM_OF_VECTOR(vector));

    if(vector.elements == NULL){
        fprintf(fp ," %s ", MZ_NULL_VECTOR);
    }else {
        for(size_t i = 0; i < MZ_DIM_OF_VECTOR(vector); i++){
            #if !VISUALIZE_RATIONAL 
            fprintf(fp ," %f", MZ_VALUE_OF_VECTOR_AT(vector, i));
            #else
            zstring value = rationalizeFloatToStr(MZ_VALUE_OF_VECTOR_AT(vector, i), 3);
            fprintf(fp, " %s", value.data);
            #endif
            fprintf(fp ,"%c", (i < MZ_DIM_OF_VECTOR(vector) - 1 ? ',' : ' '));
        }
    }
    fprintf(fp ,"]\n   |  }\n\n");
}

/*
*/
void MZ_print_vector_by_index(FILE* fp, int index, MZ_Vec vector){

    fprintf(fp ,"\n\n   | [VECTOR %d] of size %zu: {\n   |\t[", index, MZ_DIM_OF_VECTOR(vector));

    if(vector.elements == NULL){
        fprintf(fp ," %s ", MZ_NULL_VECTOR);
    }else {
        for(size_t i = 0; i < MZ_DIM_OF_VECTOR(vector); i++){
            #if !VISUALIZE_RATIONAL 
            fprintf(fp ," %f", MZ_VALUE_OF_VECTOR_AT(vector, i));
            #else
            zstring value = rationalizeFloatToStr(MZ_VALUE_OF_VECTOR_AT(vector, i), 3);
            fprintf(fp, " %s", value.data);
            #endif
            fprintf(fp ,"%c", (i < MZ_DIM_OF_VECTOR(vector) - 1 ? ',' : ' '));
        }
    }
    fprintf(fp ,"]\n   |  }\n\n");
}

/*
*/
void MZ_free_vector(MZ_Vec* vector){

    MZ_assert(vector != NULL, "Vector must not be NULL.");

    free(vector->elements);
    vector->elements = NULL;
    vector->dim = 0;
}

/*
*/
void MZ_copy_vector_pointer(MZ_Vec* source, MZ_Vec* dest){

    if(dest->elements == NULL){ 
        *dest= MZ_alloc_vector(source->dim); 
    }

    dest->dim = source->dim;
    dest->elements = source->elements;

}

/*
*/
MZ_Vec MZ_alloc_vector(size_t dim){
    MZ_Vec result;
    result.dim = dim;
    result.elements = MZ_ALLOC(dim, float);

    MZ_assert(result.elements != NULL, MZ_ALLOC_ERROR);

    return result;
}

/*
*/
MZ_Vec MZ_new_zero_vector(size_t dim){

    MZ_Vec result = MZ_alloc_vector(dim);

    for(size_t i = 0; i < dim; i++){
        MZ_VALUE_OF_VECTOR_AT(result, i) = 0.0f;
    }

    return result;

}

/*
*/
MZ_Vec MZ_new_default_vector(size_t dim, float element){

    MZ_Vec result = MZ_alloc_vector(dim);

    for(size_t i = 0; i < dim; i++){
        MZ_VALUE_OF_VECTOR_AT(result, i) = element;
    }

    return result;

}

/*
*/
MZ_Vec MZ_new_random_float_vector(size_t dim, float min, float max){

    MZ_Vec result = MZ_alloc_vector(dim);

    MZ_SRAND();

    for(size_t i = 0; i < dim; i++){
        MZ_VALUE_OF_VECTOR_AT(result, i) = MZ_rand_float(min, max);
    }

    return result;
}

/*
*/
MZ_Vec MZ_new_random_int_vector(size_t dim, float min, float max){

    MZ_Vec result = MZ_alloc_vector(dim);

    MZ_SRAND();
    
    for(size_t i = 0; i < dim; i++){
        MZ_VALUE_OF_VECTOR_AT(result, i) = MZ_rand_int(min, max);
    }

    return result;
}

/*
*/
MZ_Vec _MZ_new_vector(size_t dim, ...){

    MZ_Vec result = MZ_alloc_vector(dim);

    va_list elem;
    va_start(elem, dim);

    for(size_t i = 0 ; i < dim; i++){
        MZ_VALUE_OF_VECTOR_AT(result, i) = va_arg(elem, double);
    }

    va_end(elem);

    return result;

}

/*
*/
MZ_Vec MZ_copy_vector(MZ_Vec source){

    MZ_Vec result = MZ_alloc_vector(MZ_DIM_OF_VECTOR(source));

    for(size_t i = 0; i < MZ_DIM_OF_VECTOR(source); i++){
        MZ_VALUE_OF_VECTOR_AT(result , i) = MZ_VALUE_OF_VECTOR_AT(source, i);
    }

    return result;

}

/*
*/
MZ_Vec MZ_add_two_vectors(MZ_Vec vector1 , MZ_Vec vector2){

    MZ_assert(MZ_DIM_OF_VECTOR(vector1) == MZ_DIM_OF_VECTOR(vector2), MZ_EQUAL_ERROR);

    MZ_Vec result = MZ_alloc_vector(MZ_DIM_OF_VECTOR(vector1));

    for(size_t i = 0; i < MZ_DIM_OF_VECTOR(vector1); i++){
        MZ_VALUE_OF_VECTOR_AT(result , i) = MZ_VALUE_OF_VECTOR_AT(vector1, i) + MZ_VALUE_OF_VECTOR_AT(vector2, i);
    }

    return result;

}

/*
*/
MZ_Vec MZ_add_vector_with_scalar(MZ_Vec vector1 , float scalar){

    MZ_Vec result = MZ_alloc_vector(MZ_DIM_OF_VECTOR(vector1));

    for(size_t i = 0; i < MZ_DIM_OF_VECTOR(vector1); i++){
        MZ_VALUE_OF_VECTOR_AT(result , i) = MZ_VALUE_OF_VECTOR_AT(vector1, i) + scalar;
    }

    return result;
}
    
/*
*/
MZ_Vec MZ_subtract_two_vectors(MZ_Vec vector1 , MZ_Vec vector2){

    MZ_assert(MZ_DIM_OF_VECTOR(vector1) == MZ_DIM_OF_VECTOR(vector2), MZ_EQUAL_ERROR);

    MZ_Vec result = MZ_alloc_vector(MZ_DIM_OF_VECTOR(vector1));

    for(size_t i = 0; i < MZ_DIM_OF_VECTOR(vector1); i++){
        MZ_VALUE_OF_VECTOR_AT(result , i) = MZ_VALUE_OF_VECTOR_AT(vector1, i) - MZ_VALUE_OF_VECTOR_AT(vector2, i);
    }

    return result;  
}

/*
*/
MZ_Vec MZ_subtract_vector_with_scalar(MZ_Vec vector1 , float scalar){

    MZ_Vec result = MZ_alloc_vector(MZ_DIM_OF_VECTOR(vector1));

    for(size_t i = 0; i < MZ_DIM_OF_VECTOR(vector1); i++){
        MZ_VALUE_OF_VECTOR_AT(result , i) = MZ_VALUE_OF_VECTOR_AT(vector1, i) - scalar;
    }

    return result;
}

/*
*/
MZ_Vec MZ_multiply_two_vectors(MZ_Vec vector1, MZ_Vec vector2){

    MZ_assert(MZ_DIM_OF_VECTOR(vector1) == MZ_DIM_OF_VECTOR(vector2), MZ_EQUAL_ERROR);

    MZ_Vec result = MZ_alloc_vector(MZ_DIM_OF_VECTOR(vector1));

    for(size_t i = 0; i < MZ_DIM_OF_VECTOR(vector1); i++){
        MZ_VALUE_OF_VECTOR_AT(result , i) = MZ_VALUE_OF_VECTOR_AT(vector1, i) * MZ_VALUE_OF_VECTOR_AT(vector2, i);
    }

    return result;  
}

/*
*/
MZ_Vec MZ_multiply_vector_by_scalar(MZ_Vec vector1, float scalar){

    MZ_Vec result = MZ_alloc_vector(MZ_DIM_OF_VECTOR(vector1));

    for(size_t i = 0; i < MZ_DIM_OF_VECTOR(vector1); i++){
        MZ_VALUE_OF_VECTOR_AT(result , i) = MZ_VALUE_OF_VECTOR_AT(vector1, i) * scalar;
    }

    return result;
}

/*
*/
MZ_Vec MZ_divide_two_vectors(MZ_Vec vector1, MZ_Vec vector2){

    MZ_assert(MZ_DIM_OF_VECTOR(vector1) == MZ_DIM_OF_VECTOR(vector2), MZ_EQUAL_ERROR);


    MZ_Vec result = MZ_alloc_vector(MZ_DIM_OF_VECTOR(vector1));

    for(size_t i = 0; i < MZ_DIM_OF_VECTOR(vector1); i++){
        if(MZ_VALUE_OF_VECTOR_AT(vector2 , i) == 0.0f) return NULL_VECTOR;
        MZ_VALUE_OF_VECTOR_AT(result , i) = MZ_VALUE_OF_VECTOR_AT(vector1, i) / MZ_VALUE_OF_VECTOR_AT(vector2, i);
    }

    return result;  
}

/*
*/
MZ_Vec MZ_divide_vector_by_scalar(MZ_Vec vector1, float scalar){

    MZ_Vec result = MZ_alloc_vector(MZ_DIM_OF_VECTOR(vector1));

    for(size_t i = 0; i < MZ_DIM_OF_VECTOR(vector1); i++){
        MZ_VALUE_OF_VECTOR_AT(result , i) = MZ_VALUE_OF_VECTOR_AT(vector1, i) / scalar;
    }

    return result;
}

/*
*/
MZ_Vec MZ_raise_vector_to_exp(MZ_Vec vector, size_t exponent){

    MZ_Vec result = MZ_copy_vector(vector);
    
    printf("\n");
    for(size_t i = 0; i < MZ_DIM_OF_VECTOR(result); i++){
        for(size_t j = 0; j < exponent; j++){
            MZ_VALUE_OF_VECTOR_AT(result, i) *= MZ_VALUE_OF_VECTOR_AT(vector, i);

            #if VISUALIZE_STEPS
            printf("%f -> %f |", MZ_VALUE_OF_VECTOR_AT(result, i) / MZ_VALUE_OF_VECTOR_AT(vector, i), MZ_VALUE_OF_VECTOR_AT(result, i));
            #endif
        }

        #if VISUALIZE_STEPS
        printf("\n");
        #endif
    }

    return result;

}

/*
*/
MZ_Vec MZ_cross_product(MZ_Vec vector1, MZ_Vec vector2){

    if(MZ_DIM_OF_VECTOR(vector1) != 3 || MZ_DIM_OF_VECTOR(vector2) != 3){
        return NULL_VECTOR;
    }

    MZ_Vec result = MZ_alloc_vector(3);

    MZ_VALUE_OF_VECTOR_AT(result , 0 ) = (MZ_VALUE_OF_VECTOR_AT(vector1, 1) * MZ_VALUE_OF_VECTOR_AT( vector2, 2)) - (MZ_VALUE_OF_VECTOR_AT(vector1 , 2) * MZ_VALUE_OF_VECTOR_AT(vector2 , 1));
    MZ_VALUE_OF_VECTOR_AT(result , 1 ) = -1 * (MZ_VALUE_OF_VECTOR_AT(vector1, 0) * MZ_VALUE_OF_VECTOR_AT( vector2, 2)) - (MZ_VALUE_OF_VECTOR_AT(vector1 , 2) * MZ_VALUE_OF_VECTOR_AT(vector2 , 0));
    MZ_VALUE_OF_VECTOR_AT(result , 2 ) = (MZ_VALUE_OF_VECTOR_AT(vector1, 0) * MZ_VALUE_OF_VECTOR_AT( vector2, 1)) - (MZ_VALUE_OF_VECTOR_AT(vector1 , 1) * MZ_VALUE_OF_VECTOR_AT(vector2 , 0));

    return result;
}

/*
*/
MZ_Vec MZ_normalized_vector(MZ_Vec vector){

    MZ_Vec result = MZ_alloc_vector(MZ_DIM_OF_VECTOR(vector));
    float mag = MZ_magnitude_of_vector(vector);

    for(size_t i = 0 ; i < MZ_DIM_OF_VECTOR(vector); i++){
        MZ_VALUE_OF_VECTOR_AT(result, i ) = MZ_VALUE_OF_VECTOR_AT(vector, i) / mag;
    }

    return result;

}

/*
*/
void MZ_normalize_vector(MZ_Vec* vector){

    float mag = MZ_magnitude_of_vector(*vector);

    for(size_t i = 0 ; i < vector->dim; i++){
        vector->elements[i] /= mag;
    }
}

/*
*/
bool MZ_are_two_vectors_equal(MZ_Vec vector1, MZ_Vec vector2){

    if(MZ_DIM_OF_VECTOR(vector1) != MZ_DIM_OF_VECTOR(vector2)) return false;

    for(size_t i = 0; i < MZ_DIM_OF_VECTOR(vector1); i++){
        if(MZ_VALUE_OF_VECTOR_AT(vector1, i) != MZ_VALUE_OF_VECTOR_AT(vector2, i)) return false;
    }

    return true;

}

/*
*/
bool MZ_are_two_vectors_orthogonal(MZ_Vec vector1, MZ_Vec vector2){
    return MZ_dot_two_vectors(vector1, vector2) == 0; 
}

/*
*/
bool MZ_is_vector_normalized(MZ_Vec vector){

    return fabs(MZ_magnitude_of_vector(vector) - 1.0) < 0.0001;
}

/*
*/
float MZ_dot_two_vectors(MZ_Vec vector1, MZ_Vec vector2){

    MZ_assert(MZ_DIM_OF_VECTOR(vector1) == MZ_DIM_OF_VECTOR(vector2), MZ_EQUAL_ERROR);

    float result = 0.0f;

    for(size_t i = 0; i < MZ_DIM_OF_VECTOR(vector1); i++){
        result += MZ_VALUE_OF_VECTOR_AT(vector1, i) * MZ_VALUE_OF_VECTOR_AT(vector2, i);
    }

    return result;

}

/*
*/
float MZ_magnitude_of_vector(MZ_Vec vector){

    float result = 0.0f;

    for(size_t i = 0; i < MZ_DIM_OF_VECTOR(vector); i++){
        result += MZ_VALUE_OF_VECTOR_AT(vector, i) * MZ_VALUE_OF_VECTOR_AT(vector, i);
    }

    return sqrt(result);

}

MZ_Matrix NULL_MATRIX = {0, 0, NULL};

/*
*/
void MZ_print_matrix(FILE *fp, MZ_Matrix mat){
	
	#if VISUALIZE_RATIONAL
	int spaces = 12;
    #else
    int spaces = 11;
    #endif

	fprintf(fp, "\n\n   | Matrix of size %ux%u: {\n", mat.rows, mat.cols);
	
    if(mat.elements == NULL){

        int spaces = 13;

        fprintf(fp, "   |\t\t%c   ", LEFT_UP_CORNER);
        for(unsigned int i = 0; i < 2; i++){
            for(int i = 0; i < spaces; i++){
                fprintf(fp, " ");
            }	
        }
        fprintf(fp, "    %c   \n", RIGHT_UP_CORNER);
        
        for(unsigned int i = 0; i < 2; i++){
            
            fprintf(fp, "   |\t\t%c   ", SIDE_CHAR);
            
            for(unsigned int j = 0; j < 2; j++){
                fprintf(fp, "%-13s ", MZ_NULL_MATRIX);
            }		
            fprintf(fp, "  %c\n", SIDE_CHAR);
        }

        fprintf(fp, "   |\t\t%c   ", LEFT_DOWN_CORNER);
        for(unsigned int i = 0; i < 2; i++){
            for(int i = 0; i < spaces; i++){
                fprintf(fp, " ");
            }
        }
        fprintf(fp, "    %c   \n", RIGHT_DOWN_CORNER);
        fprintf(fp, "   | }\n\n");

    }else {

        fprintf(fp, "   |\t\t%c   ", LEFT_UP_CORNER);
        for(unsigned int i = 0; i < mat.cols; i++){
            for(int i = 0; i < spaces; i++){
                fprintf(fp, " ");
            }	
        }
        fprintf(fp, "%c   \n", RIGHT_UP_CORNER);
        
        for(unsigned int i = 0; i < mat.rows; i++){
            
            fprintf(fp, "   |\t\t%c   ", SIDE_CHAR);
            
            for(unsigned int j = 0; j < mat.cols; j++){
                #if !VISUALIZE_RATIONAL
                fprintf(fp, "%-11f", MZ_VALUE_OF_MAT_AT(mat, i, j));
                #else
                zstring value = rationalizeFloatToStr(MZ_VALUE_OF_MAT_AT(mat, i, j), 3);
                fprintf(fp, " %-11s", value.data);
                #endif
            }		
            fprintf(fp, "%c\n", SIDE_CHAR);
        }

        fprintf(fp, "   |\t\t%c   ", LEFT_DOWN_CORNER);
        for(unsigned int i = 0; i < mat.cols; i++){
            for(int i = 0; i < spaces; i++){
                fprintf(fp, " ");
            }
        }
        fprintf(fp, "%c   \n", RIGHT_DOWN_CORNER);
        fprintf(fp, "   | }\n\n");

    }
	
}

/*
*/
void MZ_print_matrix_by_label(FILE *fp, const char* label, MZ_Matrix mat){
	
	#if VISUALIZE_RATIONAL
	int spaces = 12;
    #else
    int spaces = 11;
    #endif

	fprintf(fp, "\n\n   | [%s] of size %ux%u: {\n", label, mat.rows, mat.cols);

    if(mat.elements == NULL){

        int spaces = 13;

        fprintf(fp, "   |\t\t%c   ", LEFT_UP_CORNER);
        for(unsigned int i = 0; i < 2; i++){
            for(int i = 0; i < spaces; i++){
                fprintf(fp, " ");
            }	
        }
        fprintf(fp, "    %c   \n", RIGHT_UP_CORNER);
        
        for(unsigned int i = 0; i < 2; i++){
            
            fprintf(fp, "   |\t\t%c   ", SIDE_CHAR);
            
            for(unsigned int j = 0; j < 2; j++){
                fprintf(fp, "%-13s ", MZ_NULL_MATRIX);
            }		
            fprintf(fp, "  %c\n", SIDE_CHAR);
        }

        fprintf(fp, "   |\t\t%c   ", LEFT_DOWN_CORNER);
        for(unsigned int i = 0; i < 2; i++){
            for(int i = 0; i < spaces; i++){
                fprintf(fp, " ");
            }
        }
        fprintf(fp, "    %c   \n", RIGHT_DOWN_CORNER);
        fprintf(fp, "   | }\n\n");

    }else {

        fprintf(fp, "   |\t\t%c   ", LEFT_UP_CORNER);
        for(unsigned int i = 0; i < mat.cols; i++){
            for(int i = 0; i < spaces; i++){
                fprintf(fp, " ");
            }	
        }
        fprintf(fp, "%c   \n", RIGHT_UP_CORNER);
	
        for(unsigned int i = 0; i < mat.rows; i++){
            
            fprintf(fp, "   |\t\t%c   ", SIDE_CHAR);
            
            for(unsigned int j = 0; j < mat.cols; j++){
                #if !VISUALIZE_RATIONAL
                fprintf(fp, "%-11f", MZ_VALUE_OF_MAT_AT(mat, i, j));
                #else
                zstring value = rationalizeFloatToStr(MZ_VALUE_OF_MAT_AT(mat, i, j), 3);
                fprintf(fp, " %-11s", value.data);
                #endif
            }		
            fprintf(fp, "%c\n", SIDE_CHAR);
        }

        fprintf(fp, "   |\t\t%c   ", LEFT_DOWN_CORNER);
        for(unsigned int i = 0; i < mat.cols; i++){
            for(int i = 0; i < spaces; i++){
                fprintf(fp, " ");
            }
        }
        fprintf(fp, "%c   \n", RIGHT_DOWN_CORNER);
        fprintf(fp, "   | }\n\n");

    }
	
}

/*
*/
void MZ_print_matrix_by_index(FILE *fp, unsigned int index, MZ_Matrix mat){
	
    #if VISUALIZE_RATIONAL
	int spaces = 12;
    #else
    int spaces = 11;
    #endif
    
    fprintf(fp, "\n\n   | [MATRIX %d] of size %ux%u: {\n", index, mat.rows, mat.cols);

    if(mat.elements == NULL){

        int spaces = 13;

        fprintf(fp, "   |\t\t%c   ", LEFT_UP_CORNER);
        for(unsigned int i = 0; i < 2; i++){
            for(int i = 0; i < spaces; i++){
                fprintf(fp, " ");
            }	
        }
        fprintf(fp, "    %c   \n", RIGHT_UP_CORNER);
        
        for(unsigned int i = 0; i < 2; i++){
            
            fprintf(fp, "   |\t\t%c   ", SIDE_CHAR);
            
            for(unsigned int j = 0; j < 2; j++){
                fprintf(fp, "%-13s ", MZ_NULL_MATRIX);
            }		
            fprintf(fp, "  %c\n", SIDE_CHAR);
        }

        fprintf(fp, "   |\t\t%c   ", LEFT_DOWN_CORNER);
        for(unsigned int i = 0; i < 2; i++){
            for(int i = 0; i < spaces; i++){
                fprintf(fp, " ");
            }
        }
        fprintf(fp, "    %c   \n", RIGHT_DOWN_CORNER);
        fprintf(fp, "   | }\n\n");

    }else {

        fprintf(fp, "   |\t\t%c   ", LEFT_UP_CORNER);
        for(unsigned int i = 0; i < mat.cols; i++){
            for(int i = 0; i < spaces; i++){
                fprintf(fp, " ");
            }	
        }
        fprintf(fp, "%c   \n", RIGHT_UP_CORNER);
	
        for(unsigned int i = 0; i < mat.rows; i++){
            
            fprintf(fp, "   |\t\t%c   ", SIDE_CHAR);
            
            for(unsigned int j = 0; j < mat.cols; j++){
                #if !VISUALIZE_RATIONAL
                fprintf(fp, "%-11f", MZ_VALUE_OF_MAT_AT(mat, i, j));
                #else
                zstring value = rationalizeFloatToStr(MZ_VALUE_OF_MAT_AT(mat, i, j), 3);
                fprintf(fp, " %-11s", value.data);
                #endif
            }		
            fprintf(fp, "%c\n", SIDE_CHAR);
        }

        fprintf(fp, "   |\t\t%c   ", LEFT_DOWN_CORNER);
        for(unsigned int i = 0; i < mat.cols; i++){
            for(int i = 0; i < spaces; i++){
                fprintf(fp, " ");
            }
        }
        fprintf(fp, "%c   \n", RIGHT_DOWN_CORNER);
        fprintf(fp, "   | }\n\n");

    }
	
}

/*
*/
void MZ_free_matrix(MZ_Matrix* mat){
    MZ_assert(mat->elements != NULL, "Matrix must not be NULL.");

    for(unsigned int i = 0; i < mat->rows; i++){
        free(mat->elements[i]);
    }

    free(mat->elements);
    mat->elements = NULL;
    mat->rows = 0;
    mat->cols = 0;
}

/*
*/
void MZ_copy_matrix_pointer(MZ_Matrix *source, MZ_Matrix *dest){

    if(dest->elements == NULL){ 
        *dest= MZ_alloc_matrix(source->rows, source->cols); 
    }

    dest->rows = source->rows;
    dest->cols = source->cols;
    dest->elements = source->elements;

}

/*
*/
MZ_Matrix MZ_alloc_matrix(unsigned int rows, unsigned int cols){

    MZ_Matrix result;
    result.rows = rows;
    result.cols = cols;

    result.elements = MZ_ALLOC(rows, float*);
    for(unsigned int i=0; i<rows; i++){
        result.elements[i] = MZ_ALLOC(cols, float);
    }

    MZ_assert(result.elements != NULL, MZ_ALLOC_ERROR);

    return result;

}

/*
*/
MZ_Matrix MZ_new_zero_matrix(unsigned int rows, unsigned int cols){

    MZ_Matrix result = MZ_alloc_matrix(rows, cols);

    for(unsigned int i = 0; i < rows; i++){
        for(unsigned int j = 0; j < cols; j++){
            MZ_VALUE_OF_MAT_AT(result, i, j) = 0.0f;
        }
    }

    return result;

}

/*
*/
MZ_Matrix MZ_new_random_float_matrix(unsigned int rows, unsigned int cols, float min, float max){

    MZ_Matrix result = MZ_alloc_matrix(rows, cols);
    
    MZ_SRAND();

    for(unsigned int i = 0; i < rows; i++){
        for(unsigned int j = 0; j < cols; j++){
            MZ_VALUE_OF_MAT_AT(result, i, j) = MZ_rand_float(min, max);
        }
    }

    return result;
   
}

/*
*/
MZ_Matrix MZ_new_random_int_matrix(unsigned int rows, unsigned int cols, int min, int max){

    MZ_Matrix result = MZ_alloc_matrix(rows, cols);

    MZ_SRAND();

    for(unsigned int i = 0; i < rows; i++){
        for(unsigned int j = 0; j < cols; j++){
            MZ_VALUE_OF_MAT_AT(result, i, j) = (float)MZ_rand_int(min, max);
        }
    }

    return result;
   
}

/*
*/
MZ_Matrix MZ_new_default_matrix(unsigned int rows, unsigned int cols, float value){

    MZ_Matrix result = MZ_alloc_matrix(rows, cols);

    for(unsigned int i = 0; i < rows; i++){
        for(unsigned int j = 0; j < cols; j++){
            MZ_VALUE_OF_MAT_AT(result, i, j) = value;
        }
    }

    return result;

}

MZ_Matrix MZ_new_identity_matrix(unsigned int MZ_DIM_OF_VECTOR){
    MZ_Matrix result = MZ_alloc_matrix(MZ_DIM_OF_VECTOR, MZ_DIM_OF_VECTOR);

    for(unsigned int i = 0; i < MZ_DIM_OF_VECTOR; i++){
        for(unsigned int j = 0; j < MZ_DIM_OF_VECTOR; j++){
            if(i == j){
                MZ_VALUE_OF_MAT_AT(result, i, j) = 1.0f;
            }else {
                MZ_VALUE_OF_MAT_AT(result, i, j) = 0.0f;
            }
        }
    }

    return result;

}

/*
*/
MZ_Matrix _MZ_new_matrix(unsigned int rows, unsigned int cols, unsigned int numVals, ...){

    MZ_Matrix result = MZ_alloc_matrix(rows, cols);

    va_list args;
    va_start(args, numVals);

    unsigned int vals = 0;

    for(unsigned int i = 0; i < result.rows; i++){
        for(unsigned int j = 0 ; j < result.cols; j++){
            if(vals++ < numVals){
                MZ_VALUE_OF_MAT_AT(result, i, j) =  va_arg(args, double);
            }else {
                MZ_VALUE_OF_MAT_AT(result, i, j) = 0.0f;
            }
        }
    }

    va_end(args);

    return result;

}

/*
*/
MZ_Matrix MZ_Vector_to_matrix(MZ_Vec source, Direction dir){

    MZ_assert(dir < DIR_COUNT, MZ_DIRECTION_ERROR);

    MZ_Matrix result;

    switch(dir){
        case HORIZONTAL: {
            result = MZ_alloc_matrix(1, MZ_DIM_OF_VECTOR(source));

            for(unsigned int i = 0; i < result.cols; i++){
                MZ_VALUE_OF_MAT_AT(result, 0, i) = source.elements[i];
            }       

        } break;
        case VERTICAL: {
            result = MZ_alloc_matrix(source.dim, 1); 

            for(unsigned int i = 0; i < result.rows; i++){
                MZ_VALUE_OF_MAT_AT(result, i, 0) = source.elements[i];
            }  

        } break;
        default: break;
    }

    return result;

}

/*
*/
MZ_Vec MZ_Matrix_to_vector(MZ_Matrix source){

    MZ_Vec result = MZ_alloc_vector(source.rows * source.cols);   

    for(unsigned int i = 0; i < source.rows; i++){
        for(unsigned int j = 0; j < source.cols; j++){
            result.elements[j + i * source.cols] = MZ_VALUE_OF_MAT_AT(source, i, j);
        }
    }

    return result;
}

/*
*/
MZ_Vec MZ_get_vector_from_matrix_row(MZ_Matrix source, unsigned int row){

    row--;

    if(row > source.rows){ return NULL_VECTOR; }

    MZ_Vec result = MZ_alloc_vector(source.cols);   

    for(unsigned int i = 0; i < source.cols; i++){
        result.elements[i] = MZ_VALUE_OF_MAT_AT(source, row, i);
    }

    return result;
}

/*
*/
MZ_Vec MZ_get_vector_from_matrix_col(MZ_Matrix source, unsigned int col){

    col--;

    if(col > source.cols){ return NULL_VECTOR; }

    MZ_Vec result = MZ_alloc_vector(source.rows);   

    for(unsigned int i = 0; i < source.cols; i++){
        result.elements[i] = MZ_VALUE_OF_MAT_AT(source, i, col);
    }

    return result;
}

/*
*/
MZ_Matrix MZ_flatten_matrix(MZ_Matrix matrix, Direction dir){
    MZ_Matrix result;

    switch(dir){
        case VERTICAL:{
            result = MZ_alloc_matrix(matrix.rows * matrix.cols, 1);
        }break;
        case HORIZONTAL:{
            result = MZ_alloc_matrix(1, matrix.rows * matrix.cols);
        }break;
    }

    for(unsigned int i = 0; i < matrix.rows; i++){
        for(unsigned int j = 0; j < matrix.cols; j++){
            switch(dir){
                case VERTICAL:{
                    MZ_VALUE_OF_MAT_AT(result, i*matrix.cols + j, 0) = MZ_VALUE_OF_MAT_AT(matrix, i, j);
                }break;
                case HORIZONTAL:{
                    MZ_VALUE_OF_MAT_AT(result, 0, i*matrix.cols + j) = MZ_VALUE_OF_MAT_AT(matrix, i, j);
                }break;
            }
        }
    }

    return result;
}

/*
*/
MZ_Matrix MZ_add_two_matrices(MZ_Matrix matrix1, MZ_Matrix matrix2){

    MZ_assert(matrix1.rows == matrix2.rows && matrix1.cols == matrix2.cols, MZ_EQUAL_ERROR);
    
    MZ_Matrix result = MZ_alloc_matrix(matrix1.rows, matrix1.cols);

    for(unsigned int i = 0; i < result.rows; i++){
        for(unsigned int j = 0; j < result.cols; j++){
            MZ_VALUE_OF_MAT_AT(result, i, j) = MZ_VALUE_OF_MAT_AT(matrix1, i, j) + MZ_VALUE_OF_MAT_AT(matrix2, i, j);
        }
    }

    return result;

}

/*
*/
MZ_Matrix MZ_add_matrix_with_scalar(MZ_Matrix matrix1, float scalar){
    
    MZ_Matrix result = MZ_alloc_matrix(matrix1.rows, matrix1.cols);

    for(unsigned int i = 0; i < result.rows; i++){
        for(unsigned int j = 0; j < result.cols; j++){
            MZ_VALUE_OF_MAT_AT(result, i, j) = MZ_VALUE_OF_MAT_AT(matrix1, i, j) + scalar;
        }
    }

    return result;

}

/*
*/
MZ_Matrix MZ_subtract_two_matrices(MZ_Matrix matrix1, MZ_Matrix matrix2){

    MZ_assert(matrix1.rows == matrix2.rows && matrix1.cols == matrix2.cols, MZ_EQUAL_ERROR);

    MZ_Matrix result = MZ_alloc_matrix(matrix1.rows, matrix1.cols);

    for(unsigned int i = 0; i < result.rows; i++){
        for(unsigned int j = 0; j < result.cols; j++){
            MZ_VALUE_OF_MAT_AT(result, i, j) = MZ_VALUE_OF_MAT_AT(matrix1, i, j) - MZ_VALUE_OF_MAT_AT(matrix2, i, j);
        }
    }

    return result;

}

/*
*/
MZ_Matrix MZ_subtract_matrix_with_scalar(MZ_Matrix matrix1, float scalar){
    
    MZ_Matrix result = MZ_alloc_matrix(matrix1.rows, matrix1.cols);

    for(unsigned int i = 0; i < result.rows; i++){
        for(unsigned int j = 0; j < result.cols; j++){
            MZ_VALUE_OF_MAT_AT(result, i, j) = MZ_VALUE_OF_MAT_AT(matrix1, i, j) - scalar;
        }
    }

    return result;

}

/*
*/
MZ_Matrix MZ_multiply_two_matrices(MZ_Matrix matrix1, MZ_Matrix matrix2){

    MZ_assert(matrix1.cols == matrix2.rows, MZ_PROD_ERROR);

    MZ_Matrix result = MZ_alloc_matrix(matrix1.rows, matrix2.cols);
    
    for(unsigned int i = 0; i < result.rows; i++){
		for(unsigned int j = 0; j < result.cols; j++){
			MZ_VALUE_OF_MAT_AT(result, i, j) = 0;
			for(unsigned int k = 0; k < matrix2.rows; k++){
				MZ_VALUE_OF_MAT_AT(result, i, j) += MZ_VALUE_OF_MAT_AT(matrix1, i, k) * MZ_VALUE_OF_MAT_AT(matrix2, k, j); 
			}
		}
	}

    return result;

}

/*
*/
MZ_Matrix MZ_multiply_matrix_by_scalar(MZ_Matrix matrix1, float scalar){
    
    MZ_Matrix result = MZ_alloc_matrix(matrix1.rows, matrix1.cols);

    for(unsigned int i = 0; i < result.rows; i++){
        for(unsigned int j = 0; j < result.cols; j++){
            MZ_VALUE_OF_MAT_AT(result, i, j) = MZ_VALUE_OF_MAT_AT(matrix1, i, j) * scalar;
        }
    }

    return result;

}

/*
*/
MZ_Matrix MZ_divide_two_matrices(MZ_Matrix matrix1, MZ_Matrix matrix2){

    MZ_assert(matrix1.rows == matrix2.rows && matrix1.cols == matrix2.cols, MZ_EQUAL_ERROR);

    MZ_Matrix result = MZ_alloc_matrix(matrix1.rows, matrix1.cols);

    for(unsigned int i = 0; i < result.rows; i++){
        for(unsigned int j = 0; j < result.cols; j++){
            if(MZ_VALUE_OF_MAT_AT(matrix2, i, j) != 0.0f){
                MZ_VALUE_OF_MAT_AT(result, i, j) = MZ_VALUE_OF_MAT_AT(matrix1, i, j) / MZ_VALUE_OF_MAT_AT(matrix2, i, j);
            }else {
                MZ_VALUE_OF_MAT_AT(result, i, j) = 0.0f;
            }
        }
    }

    return result;

}

/*
*/
MZ_Matrix MZ_divide_matrix_by_scalar(MZ_Matrix matrix1, float scalar){
    
    MZ_Matrix result = MZ_alloc_matrix(matrix1.rows, matrix1.cols);

    for(unsigned int i = 0; i < result.rows; i++){
        for(unsigned int j = 0; j < result.cols; j++){
            if(scalar != 0.0f){
                MZ_VALUE_OF_MAT_AT(result, i, j) = MZ_VALUE_OF_MAT_AT(matrix1, i, j) / scalar;
            }else {
                return NULL_MATRIX;
            }
        }
    }

    return result;

}

/*
*/
MZ_Matrix MZ_hadamard_multiply_two_matrices(MZ_Matrix matrix1, MZ_Matrix matrix2){

    MZ_assert(matrix1.rows == matrix2.rows && matrix1.cols == matrix2.cols, MZ_EQUAL_ERROR);

    MZ_Matrix result = MZ_alloc_matrix(matrix1.rows, matrix1.cols);
    
    for(unsigned int i = 0; i < result.rows; i++){
        for(unsigned int j = 0; j < result.cols; j++){
            MZ_VALUE_OF_MAT_AT(result, i, j) = MZ_VALUE_OF_MAT_AT(matrix1, i, j) * MZ_VALUE_OF_MAT_AT(matrix2, i, j);
        }
    }

    return result;
    
}

/*
*/
MZ_Matrix MZ_transposed_matrix(MZ_Matrix source){
    MZ_Matrix result = MZ_alloc_matrix(source.cols, source.rows);

    for(unsigned int i = 0; i < result.rows; i++){
        for(unsigned int j = 0; j < result.cols; j++){
            MZ_VALUE_OF_MAT_AT(result, i, j) = MZ_VALUE_OF_MAT_AT(source, j, i);
        }
    }

    return result;
}


/*
*/
bool MZ_swap_two_matrix_rows(MZ_Matrix *source, unsigned int row1, unsigned int row2){


    if(row1 >= source->rows || row2 >= source->rows || row1 == row2){
        return false;
    }

    float* tmp = source->elements[row1];
    source->elements[row1] = source->elements[row2];
    source->elements[row2] = tmp; 

    return true;
}

/*
*/
bool MZ_add_two_matrix_rows(MZ_Matrix *source, unsigned int row1, unsigned int row2){


    if(row1 >= source->rows || row2 >= source->rows || row1 == row2){
        return false;
    }

    for(unsigned int i = 0; i < source->cols; i++){
        //source->elements[row1][i] += source->elements[row2][i];
        MZ_VALUE_OF_MAT_POINTER_AT(source, row1, i) += MZ_VALUE_OF_MAT_POINTER_AT(source, row2, i);
    }

    return true;
}

/*
*/
bool MZ_multiply_two_matrix_rows(MZ_Matrix *source, unsigned int row, int scalar){


    if(row >= source->rows || scalar == 0.0f){
        return false;
    }

    for(unsigned int i = 0; i < source->cols; i++){
        MZ_VALUE_OF_MAT_POINTER_AT(source, row, i)  *= scalar;
    }

    return true;
}

/*
*/
bool MZ_multiply_add_two_matrix_rows(MZ_Matrix *source, unsigned int row1, unsigned int row2, int scalar){


    if(row1 >= source->rows || row2 >= source->rows || 
       scalar == 0.0f || row1 == row2){
        return false;
    }

    for(unsigned int i = 0; i < source->cols; i++){
        //source->elements[row1][i] += source->elements[row2][i] * scalar;
        MZ_VALUE_OF_MAT_POINTER_AT(source, row1, i) += MZ_VALUE_OF_MAT_POINTER_AT(source, row2, i) * scalar;
    }

    return true;
}

/*
*/
void MZ_to_echelon_form(MZ_Matrix *source){

    unsigned int curRow = 0;

    for(unsigned int i = 0; i < source->cols; i++){
        
        #if VISUALIZE_STEPS
        printMatrixByIndex(curRow, *source);
        #endif

        unsigned int row = curRow;

        if(row >= source->rows) break;

        for(; row < source->rows; row++){
            if(MZ_VALUE_OF_MAT_POINTER_AT(source, row, i) != 0.0f) break;
        }

        if(row == source->rows) continue;

        MZ_swap_two_matrix_rows(source, curRow, row);

        float factor = 1 / MZ_VALUE_OF_MAT_POINTER_AT(source, curRow, i);

        for(unsigned int col = i; col < source->cols; col++){
            MZ_VALUE_OF_MAT_POINTER_AT(source, curRow, col) *= factor;
        }

        for(row = curRow + 1; row < source->rows; row++){
            MZ_multiply_add_two_matrix_rows(source, row, curRow, -1 * MZ_VALUE_OF_MAT_POINTER_AT(source, curRow, i));
        }

        curRow++;

    }

}

/*
*/
void MZ_to_reduced_echelon_form(MZ_Matrix *source){

    unsigned int curRow = 0;

    for(unsigned int i = 0; i < source->cols; i++){
        
        #if VISUALIZE_STEPS
        printMatrixByIndex(curRow, *source);
        #endif

        unsigned int row = curRow;

        if(row >= source->rows) break;

        for(; row < source->rows; row++){
            if(MZ_VALUE_OF_MAT_POINTER_AT(source, row, i) != 0.0f) break;
        }

        if(row == source->rows) continue;

        MZ_swap_two_matrix_rows(source, curRow, row);

        float factor = 1 / MZ_VALUE_OF_MAT_POINTER_AT(source, curRow, i);

        for(unsigned int col = i; col < source->cols; col++){
            MZ_VALUE_OF_MAT_POINTER_AT(source, curRow, col) *= factor;
        }

        for(row = 0; row < source->rows; row++){
            if(row == curRow) continue;
            MZ_multiply_add_two_matrix_rows(source, row, curRow, -1 * MZ_VALUE_OF_MAT_POINTER_AT(source, row, i));
        }

        curRow++;

    }
}

/*
*/
MZ_Matrix MZ_append_vector_to_matrix(MZ_Matrix source, MZ_Vec vector){

    MZ_assert(source.rows == vector.dim, MZ_EQUAL_ERROR);
    
    MZ_Matrix result = MZ_alloc_matrix(source.rows, source.cols + 1);

    for(unsigned int i = 0; i < source.rows; i++){
        unsigned int j = 0;
        for(; j < source.cols; j++){
            #if VISUALIZE_DEBUG
            printf("%d\n", j);
            #endif
            MZ_VALUE_OF_MAT_AT(result, i, j) = MZ_VALUE_OF_MAT_AT(source, i, j);
        }
        MZ_VALUE_OF_MAT_AT(result, i, j) = MZ_VALUE_OF_VECTOR_AT(vector, i);
        #if VISUALIZE_DEBUG
        printf("%f at %d:%d\n", MZ_VALUE_OF_MAT_AT(result, i, j), i, j);
        #endif
    }

    return result;

}

/*
*/
MZ_Matrix MZ_append_matrix_to_matrix(MZ_Matrix source, MZ_Matrix matrix){

    MZ_assert(source.rows == matrix.rows, MZ_EQUAL_ERROR);
    
    MZ_Matrix result = MZ_alloc_matrix(source.rows, source.cols + matrix.cols);

    for(unsigned int i = 0; i < source.rows; i++){
        unsigned int j = 0;
        for(; j < source.cols; j++){
            MZ_VALUE_OF_MAT_AT(result, i, j) = MZ_VALUE_OF_MAT_AT(source, i, j);
        }
        for(unsigned int k = 0; k < matrix.cols; k++){
            MZ_VALUE_OF_MAT_AT(result, i, k + j) = MZ_VALUE_OF_MAT_AT(matrix, i, k);
        }
        
    }

    return result;

}

/*
*/
MZ_Matrix MZ_get_sub_matrix(MZ_Matrix source, unsigned int remRow, unsigned int remCol){

    remRow--;
    remCol--;

    MZ_Matrix result = MZ_alloc_matrix(source.rows - 1, source.cols - 1);

    unsigned int rowOffset = 0;
    for (unsigned int i = 0; i < result.rows; i++){
        unsigned int colOffset = 0;

        if (i == remRow){
            rowOffset++;
        }

        for (unsigned int j = 0; j < result.cols; j++){
            if (j == remCol)
            {
                colOffset++;
            }

            // assign value
            MZ_VALUE_OF_MAT_AT(result, i, j) = MZ_VALUE_OF_MAT_AT(source, i + rowOffset, j + colOffset);//source.elements[i + rowOffset][j + colOffset];
        }
    }

    return result;
}

/*
*/
float MZ_determinant_of_matrix_old(MZ_Matrix source){
    MZ_assert(source.rows == source.cols, MZ_SQUARE_ERROR);

    if(source.rows == 1){
        return MZ_VALUE_OF_MAT_AT(source, 0, 0);  
    }

    float result = 0.0f;

    for(unsigned int i = 0; i < source.cols; i++){
        result += MZ_VALUE_OF_MAT_AT(source, 0 , i) * MZ_cofactor_of_matrix_at_coord(source, 1, i + 1);
    }

    return result;

}

/*
*/
float MZ_determinant_of_matrix(MZ_Matrix source){
    if (source.rows != source.cols || source.rows == 0)
    {
        return 0.0f;
    }

    // initialize array
    unsigned int *skipCols = malloc(source.cols * sizeof(unsigned int));
    unsigned int noSkipCols = 0;

    float result = _MZ_determinant_of_matrix(source, 1, 0, skipCols, &noSkipCols);

    free(skipCols);

    return result;
}

/*
*/
float _MZ_determinant_of_matrix(MZ_Matrix source,
                            unsigned int row,
                            unsigned int col,
                            unsigned int *skipCols,
                            unsigned int *noSkipCols){

    skipCols[*noSkipCols] = col;
    (*noSkipCols)++;

    /*if (row == source.rows - 1)
    {
        printf("");
    }*/

    // base case to return single element
    if (row == source.rows)
    {
        unsigned int i = source.cols;
        // find last column not in exclusion list
        if (*noSkipCols != 0)
        {
            if (skipCols[*noSkipCols - 1] != 0)
            {
                while (MZ_is_in_array(skipCols, *noSkipCols, i))
                {
                    i--;
                }
                (*noSkipCols)--;
            }
        }
        return MZ_VALUE_OF_MAT_AT(source, row-1, i-1);//source.elements[row - 1][i - 1];
    }

    float result = 0.0f;
    char cofactorSign = 1;

    // cofactor expansion across current row
    for (unsigned int i = 1; i <= source.cols; i++)
    {
        // skip excluded cols
        if (MZ_is_in_array(skipCols, *noSkipCols, i))
        {
            continue;
        }

        float res = 0.0f;
        if (MZ_VALUE_OF_MAT_AT(source, row-1, i-1) != 0.0f)
        {
            // recursive
            res = cofactorSign *
                  MZ_VALUE_OF_MAT_AT(source, row-1, i-1) *
                  _MZ_determinant_of_matrix(source, row + 1, i, skipCols, noSkipCols);
        }

        result += res;
        cofactorSign = -cofactorSign;
    }

    // remove current column from the list
    (*noSkipCols)--;
    return result;
}

/*
*/
float MZ_cofactor_of_matrix_at_coord(MZ_Matrix source, unsigned int row, unsigned int col){

    // must be a square matrix with at least 1 row
    if (source.rows != source.cols || source.rows == 0)
    {
        return 0.0f;
    }

    // boundary condition
    if (row > source.rows || col > source.cols)
    {
        return 0.0f;
    }

    // alternate signs
    // if row + col is even, positive
    // if row + col is odd, negative
    char sign = ((row + col) & 1) == 0 ? 1 : -1;

    MZ_Matrix subbedMat = MZ_get_sub_matrix(source, row, col);

    // cofactor = sign * determinant of the matrix without row and col
    float result = sign * MZ_determinant_of_matrix(subbedMat);

    MZ_free_matrix(&subbedMat);

    return result;
}

/*
*/
MZ_Matrix MZ_cofactor_matrix(MZ_Matrix source){

    // must be a square matrix with at least 1 row
    if (source.rows != source.cols || source.rows == 0)
    {
        return NULL_MATRIX;
    }

    MZ_Matrix result = MZ_alloc_matrix(source.rows, source.cols);

    for (unsigned int i = 0; i < result.rows; i++)
    {
        for (unsigned int j = 0; j < result.cols; j++)
        {
            MZ_VALUE_OF_MAT_AT(result, i, j) = MZ_cofactor_of_matrix_at_coord(source, i + 1, j + 1);
        }
    }

    return result;
}

/*
*/
MZ_Matrix MZ_adjugate_matrix(MZ_Matrix source){

    // must be a square matrix with at least 1 row
    if (source.rows != source.cols || source.rows == 0)
    {
        return NULL_MATRIX;
    }

    MZ_Matrix result = MZ_alloc_matrix(source.rows, source.cols);

    for (unsigned int i = 0; i < result.rows; i++)
    {
        for (unsigned int j = 0; j < result.cols; j++)
        {
            MZ_VALUE_OF_MAT_AT(result, i, j) = MZ_cofactor_of_matrix_at_coord(source, j + 1, i + 1);
        }
    }

    return result;
}

/*
*/
bool MZ_is_matrix_invertible(MZ_Matrix source){

    // must be a square matrix with at least 1 row
    if (source.rows != source.cols || source.rows == 0)
    {
        return false;
    }

    return MZ_determinant_of_matrix(source) != 0.0f;
}

/*
*/
MZ_Matrix MZ_inverse_of_matrix(MZ_Matrix source){

    // must be a square matrix with at least 1 row
    if (source.rows != source.cols || source.rows == 0)
    {
        return NULL_MATRIX;
    }

    // get the adjugate
    MZ_Matrix adj = MZ_adjugate_matrix(source);

    // calculate the determinant using the adjugate
    float det = 0.0f;

    // expand across first row of the matrix
    for (unsigned int i = 0; i < source.cols; i++)
    {
        if (MZ_VALUE_OF_MAT_AT(source, 0, i) != 0.0f)
        {
            det += MZ_VALUE_OF_MAT_AT(source, 0, i) * MZ_VALUE_OF_MAT_AT(adj, i, 0); // [c][0] because the adjugate is the transpose of the cofactor matrix
        }
    }

    if (det == 0.0f)
    {
        return NULL_MATRIX;
    }

    // inverse = 1 / det * adj
    MZ_Matrix result = MZ_alloc_matrix(adj.rows, adj.cols);
    result = MZ_multiply_matrix_by_scalar(adj, 1.0f / det);

    MZ_free_matrix(&adj);

    return result;
}

/*
*/
MZ_Matrix MZ_inverse_of_matrix_by_rref(MZ_Matrix source){

    if (!MZ_is_matrix_invertible(source))
    {
        return NULL_MATRIX;
    }

    // augment the identity matrix
    MZ_Matrix idMat = MZ_new_identity_matrix(source.rows);
    MZ_Matrix opMat = MZ_append_matrix_to_matrix(source, idMat);

    // row reduce the augmented matrix
    MZ_to_reduced_echelon_form(&opMat);

    // take the right half of the matrix -> that is the inverse
    MZ_Matrix result = MZ_alloc_matrix(source.rows, source.cols);

    for (unsigned int i = 0; i < result.rows; i++)
    {
        for (unsigned int j = 0; j < result.cols; j++)
        {
            MZ_VALUE_OF_MAT_AT(result, i, j) = MZ_VALUE_OF_MAT_AT(opMat, i, result.cols + j);
        }
    }

    MZ_free_matrix(&idMat);
    MZ_free_matrix(&opMat);

    return result;
}

#endif // ZMATH_IMPLEMENTATION