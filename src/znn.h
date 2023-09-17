#pragma once

#ifndef ZNN_H_
#define ZNN_H_

#include <direct.h>

#define ZMATH_IMPLEMENTATION
#include "zmath.h"

#define ZIMG_IMPLEMENTATION
#include "zimg.h"

typedef struct nn{
    int input;
    int hidden;
    int output;
    double learning_rate;
    MZ_Matrix hidden_weights;
    MZ_Matrix output_weights;
}ZN_NN;

MZ_Matrix MZ_new_random_uniform_float_matrix(unsigned int rows, unsigned int cols, float n);
//MZ_Matrix MZ_flatten_matrix(MZ_Matrix matrix, Direction dir);
MZ_Matrix MZ_apply_function_to_matrix(MZ_Matrix source,double (*func)(double));
MZ_Matrix MZ_softmax(MZ_Matrix matrix);
void MZ_matrix_save(MZ_Matrix matrix, char* filename);
MZ_Matrix MZ_matrix_load(char* filename);
int MZ_matrix_argmax(MZ_Matrix matrix);
double zn_uniform_distribution(double low, double high);
double zn_sigmoid_func(double x);
ZN_NN* zn_nn_new(int input, int hidden, int output, double learning_rate);
void zn_nn_train(ZN_NN* nn, MZ_Matrix input_data, MZ_Matrix output_data);
void zn_nn_train_batch_imgs(ZN_NN* nn, ZI_Img** imgs, int batch_size);
MZ_Matrix zn_nn_predict_img(ZN_NN* nn, ZI_Img* img);
double zn_nn_predict_imgs(ZN_NN* nn, ZI_Img** imgs, int n);
MZ_Matrix zn_nn_predict(ZN_NN* nn, MZ_Matrix input_data);
void zn_nn_save(ZN_NN* nn, const char* filename);
ZN_NN* zn_nn_load(const char* filename);
void zn_nn_print(ZN_NN* nn);
void zn_nn_free(ZN_NN* nn);

#endif // ZNN_H_

#ifdef ZNN_IMPLEMENTATION

MZ_Matrix MZ_new_random_uniform_float_matrix(unsigned int rows, unsigned int cols, float n){

    MZ_Matrix result = MZ_alloc_matrix(rows, cols);
    
    MZ_SRAND();

    float min = -1 / sqrt(n);
    float max =  1 / sqrt(n);

    for(unsigned int i = 0; i < rows; i++){
        for(unsigned int j = 0; j < cols; j++){
            MZ_VALUE_OF_MAT_AT(result, i, j) = zn_uniform_distribution(min, max);
        }
    }

    return result;
   
}

/*MZ_Matrix MZ_flatten_matrix(MZ_Matrix matrix, Direction dir){
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
}*/

MZ_Matrix MZ_apply_function_to_matrix(MZ_Matrix source,double (*func)(double)){

    MZ_Matrix result;

    MZ_copy_matrix_pointer(&source, &result);

    for(unsigned int i = 0; i < result.rows; i++){
        for(unsigned int j = 0; j < result.cols; j++){
                MZ_VALUE_OF_MAT_AT(result, i, j) = (*func)(MZ_VALUE_OF_MAT_AT(result, i, j));
        }
    }

    return result;
}

MZ_Matrix MZ_sigmoidPrime(MZ_Matrix matrix) {

    MZ_Matrix ones = MZ_new_default_matrix(matrix.rows, matrix.cols, 1.0f);
    MZ_Matrix minus = MZ_subtract_two_matrices(ones, matrix);
    MZ_Matrix mult = MZ_hadamard_multiply_two_matrices(matrix, minus);
    return mult;

}

MZ_Matrix MZ_softmax(MZ_Matrix matrix) {

    double total = 0;

    for(unsigned int i = 0; i < matrix.rows; i++) {
        for(unsigned int j = 0; j < matrix.cols; j++){
            total += exp(MZ_VALUE_OF_MAT_AT(matrix, i, j));
        }
    }

    MZ_Matrix result = MZ_alloc_matrix(matrix.rows, matrix.cols);

    for(unsigned int i = 0; i < result.rows; i++) {
        for(unsigned int j = 0; j < result.cols; j++){
            MZ_VALUE_OF_MAT_AT(result, i, j) = exp(MZ_VALUE_OF_MAT_AT(matrix, i, j)) / total;
        }
    }

    return result;
}

void MZ_matrix_save(MZ_Matrix matrix, char* filename){
	FILE* fp = fopen(filename, "w");

    if(fp==NULL) {
        fprintf(stderr,"[ERROR] Could not open file '%s'\n", filename);
        exit(EXIT_FAILURE);
    }

	fprintf(fp, "%d\n", matrix.rows);
	fprintf(fp, "%d\n", matrix.cols);
	for (int i = 0; i < matrix.rows; i++) {
		for (int j = 0; j < matrix.cols; j++) {
			fprintf(fp, "%.6f\n", MZ_VALUE_OF_MAT_AT(matrix, i, j));
		}
	}
	printf("Successfully saved matrix to %s\n", filename);
	fclose(fp);
}

MZ_Matrix MZ_matrix_load(char* filename) {
	FILE* fp = fopen(filename, "r");

    if(fp==NULL) {
        fprintf(stderr,"[ERROR] Could not open file '%s'\n", filename);
        exit(EXIT_FAILURE);
    }

	char elements[MAXCHAR]; 
	fgets(elements, MAXCHAR, fp);
	int rows = atoi(elements);
	fgets(elements, MAXCHAR, fp);
	int cols = atoi(elements);
	MZ_Matrix matrix = MZ_alloc_matrix(rows, cols);
	for (int i = 0; i < matrix.rows; i++) {
		for (int j = 0; j < matrix.cols; j++) {
			fgets(elements, MAXCHAR, fp);
			MZ_VALUE_OF_MAT_AT(matrix, i, j) = strtod(elements, NULL);
		}
	}
	printf("Sucessfully loaded matrix from %s\n", filename);
	fclose(fp);
	return matrix;
}

int MZ_matrix_argmax(MZ_Matrix matrix) {
	double max_score = 0;
	int max_idx = 0;
	for (int i = 0; i < matrix.rows; i++) {
		if (MZ_VALUE_OF_MAT_AT(matrix, i, 0) > max_score) {
			max_score = MZ_VALUE_OF_MAT_AT(matrix, i, 0);
			max_idx = i;
		}
	}
	return max_idx;
}


double zn_uniform_distribution(double low, double high) {
	double difference = high - low; 
	int scale = 10000;
	int scaled_difference = (int)(difference * scale);
	return low + (1.0 * (rand() % scaled_difference) / scale);
}

double zn_sigmoid_func(double x){
    return 1.0 / (1 + exp(-1 * x));
}


ZN_NN* zn_nn_new(int input, int hidden, int output, double learning_rate){

    ZN_NN* nn = (ZN_NN*)malloc(sizeof(ZN_NN));
    nn->input = input;
    nn->hidden = hidden;
    nn->output = output;
    nn->learning_rate = learning_rate;

    MZ_Matrix hidden_layer = MZ_alloc_matrix(hidden, input);
    MZ_Matrix output_layer = MZ_alloc_matrix(output, hidden);

    hidden_layer = MZ_new_random_uniform_float_matrix(hidden, input, hidden);
    output_layer = MZ_new_random_uniform_float_matrix(output, hidden, output);

    nn->hidden_weights = hidden_layer;
    nn->output_weights = output_layer;

    return nn;
}


void zn_nn_train(ZN_NN* nn, MZ_Matrix input_data, MZ_Matrix output_data){

    // Forward propagation

    MZ_Matrix hidden_inputs = MZ_multiply_two_matrices(nn->hidden_weights, input_data);
    MZ_Matrix hidden_outputs = MZ_apply_function_to_matrix(hidden_inputs, zn_sigmoid_func);
    MZ_Matrix final_inputs = MZ_multiply_two_matrices(nn->output_weights, hidden_outputs);
    MZ_Matrix final_outputs = MZ_apply_function_to_matrix(final_inputs, zn_sigmoid_func);

    // Errors

    MZ_Matrix output_errors = MZ_subtract_two_matrices(output_data, final_outputs);
    MZ_Matrix transposed_mat = MZ_transposed_matrix(nn->output_weights);
    MZ_Matrix hidden_errors = MZ_multiply_two_matrices(transposed_mat, output_errors);
    MZ_free_matrix(&transposed_mat);

    // Back Propagation 

    MZ_Matrix sigmoid_primed_mat = MZ_sigmoidPrime(final_outputs);
    MZ_Matrix multiplied_mat = MZ_hadamard_multiply_two_matrices(output_errors, sigmoid_primed_mat);
              transposed_mat = MZ_transposed_matrix(hidden_outputs);
    MZ_Matrix dot_mat = MZ_multiply_two_matrices(multiplied_mat, transposed_mat);
    MZ_Matrix scaled_mat = MZ_multiply_matrix_by_scalar(dot_mat, nn->learning_rate);
    MZ_Matrix added_mat = MZ_add_two_matrices(nn->output_weights, scaled_mat);

    MZ_free_matrix(&nn->output_weights);
    nn->output_weights = added_mat;

    MZ_free_matrix(&sigmoid_primed_mat);
	MZ_free_matrix(&multiplied_mat);
	MZ_free_matrix(&transposed_mat);
	MZ_free_matrix(&dot_mat);
	MZ_free_matrix(&scaled_mat);

    sigmoid_primed_mat = MZ_sigmoidPrime(hidden_outputs);
    multiplied_mat = MZ_hadamard_multiply_two_matrices(hidden_errors, sigmoid_primed_mat);
    transposed_mat = MZ_transposed_matrix(input_data);
    dot_mat = MZ_multiply_two_matrices(multiplied_mat, transposed_mat);
    scaled_mat = MZ_multiply_matrix_by_scalar(dot_mat, nn->learning_rate);
    added_mat = MZ_add_two_matrices(nn->hidden_weights, scaled_mat);

    nn->hidden_weights = added_mat;

    MZ_free_matrix(&sigmoid_primed_mat);
	MZ_free_matrix(&multiplied_mat);
	MZ_free_matrix(&transposed_mat);
	MZ_free_matrix(&dot_mat);
	MZ_free_matrix(&scaled_mat);
    
}

void zn_nn_train_batch_imgs(ZN_NN* nn, ZI_Img** imgs, int batch_size){

    for (int i = 0; i < batch_size; i++) {
		if (i % 100 == 0) printf("Img No. %d\n", i);
		ZI_Img* cur_img = imgs[i];
        MZ_Matrix img_data = MZ_flatten_matrix(cur_img->img_data, VERTICAL);
		MZ_Matrix output = MZ_alloc_matrix(10, 1);
        MZ_VALUE_OF_MAT_AT(output, cur_img->label, 0) = 1;
		zn_nn_train(nn, img_data, output);
	}
}

MZ_Matrix zn_nn_predict_img(ZN_NN* nn, ZI_Img* img){
    MZ_Matrix img_data = MZ_flatten_matrix(img->img_data, VERTICAL);
    MZ_Matrix result = zn_nn_predict(nn, img_data);
    return result;
}

double zn_nn_predict_imgs(ZN_NN* nn, ZI_Img** imgs, int n){
    int n_correct = 0;
    for(unsigned int i = 0; i < n; i++){
        MZ_Matrix prediction = zn_nn_predict_img(nn, imgs[i]);
        if(MZ_matrix_argmax(prediction) == imgs[i]->label){
            n_correct++;
        }
    }
    return 1.0f * n_correct / n;
}

MZ_Matrix zn_nn_predict(ZN_NN* nn, MZ_Matrix input_data){

    MZ_Matrix hidden_inputs = MZ_multiply_two_matrices(nn->hidden_weights, input_data);
    MZ_Matrix hidden_outputs = MZ_apply_function_to_matrix(hidden_inputs, zn_sigmoid_func);
    MZ_Matrix final_inputs = MZ_multiply_two_matrices(nn->output_weights, hidden_outputs);
    MZ_Matrix final_outputs = MZ_apply_function_to_matrix(final_inputs, zn_sigmoid_func);
    MZ_Matrix result = MZ_softmax(final_outputs);

    return result;
}

void zn_nn_save(ZN_NN* nn, const char* filename){
	_mkdir(filename);
	// Write the descriptor file
	_chdir(filename);
	FILE* NN_Inputs = fopen("NN_Inputs_Data", "w");
	fprintf(NN_Inputs, "%d\n", nn->input);
	fprintf(NN_Inputs, "%d\n", nn->hidden);
	fprintf(NN_Inputs, "%d\n", nn->output);
	fclose(NN_Inputs);
	MZ_matrix_save(nn->hidden_weights, "NN_Hidden_Layer");
	MZ_matrix_save(nn->output_weights, "NN_Output_Layer");
	printf("Successfully written to '%s'\n", filename);
	_chdir("-"); // Go back to the orignal directory
}

ZN_NN* zn_nn_load(const char* filename){
	ZN_NN* nn = malloc(sizeof(ZN_NN));
	char entry[MAXCHAR];
	_chdir(filename);

	FILE* NN_Inputs = fopen("NN_Inputs_Data", "r");

    if(NN_Inputs==NULL) {
        fprintf(stderr,"[ERROR] Could not open file 'NN_Inputs'\n");
        exit(EXIT_FAILURE);
    }

	fgets(entry, MAXCHAR, NN_Inputs);
	nn->input = atoi(entry);
	fgets(entry, MAXCHAR, NN_Inputs);
	nn->hidden = atoi(entry);
	fgets(entry, MAXCHAR, NN_Inputs);
	nn->output = atoi(entry);
	fclose(NN_Inputs);
	nn->hidden_weights = MZ_matrix_load("NN_Hidden_Layer");
	nn->output_weights = MZ_matrix_load("NN_Output_Layer");
	printf("Successfully loaded network from '%s'\n", filename);
	_chdir("-"); // Go back to the original directory
	return nn;
}

void zn_nn_print(ZN_NN* nn){
    printf("# of Inputs: %d\n", nn->input);
	printf("# of Hidden: %d\n", nn->hidden);
	printf("# of Output: %d\n", nn->output);
	printf("Hidden Weights: \n");
	MZ_print_matrix(stdout, nn->hidden_weights);
	printf("Output Weights: \n");
	MZ_print_matrix(stdout, nn->output_weights);
}

void zn_nn_free(ZN_NN* nn) {
	MZ_free_matrix(&nn->hidden_weights);
    MZ_free_matrix(&nn->output_weights);
	free(nn);
	nn = NULL;
}

#endif // ZNN_IMPLEMENTATION