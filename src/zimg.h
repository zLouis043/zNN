#pragma once 

#ifndef ZIMG_H_
#define ZIMG_H_

#include <string.h>
#include <stdlib.h>

#define ZMATH_IMPLEMENTATION
#include "zmath.h"

typedef struct{
    MZ_Matrix img_data;
    int label;
}ZI_Img;

ZI_Img** zi_csv_to_imgs(const char* filename, int number_of_images);
void zi_img_print(ZI_Img* img);
void zi_img_free(ZI_Img* img);
void zi_imgs_free(ZI_Img** imgs, int n);

#define MAXCHAR 10000

#endif // ZIMG_H_

#ifdef ZIMG_IMPLEMENTATION

ZI_Img** zi_csv_to_imgs(const char* filename, int number_of_images){
    FILE *fp;

    fopen_s(&fp, filename, "r");

    if(fp == NULL){
        fprintf(stderr, "[ERROR]: Failed to open image file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    ZI_Img** imgs = (ZI_Img**)malloc(number_of_images * sizeof(ZI_Img*));

    char row[MAXCHAR];

    fgets(row, MAXCHAR, fp);

    int i = 0;

    while(feof(fp) != 1 && i < number_of_images){
        imgs[i] = (ZI_Img*)malloc(sizeof(ZI_Img));

        int j = 0;
        fgets(row, MAXCHAR, fp);
        char* token = strtok(row, ",");
        imgs[i]->img_data = MZ_alloc_matrix(28, 28);
        
        while(token != NULL){
            if(j == 0){
                imgs[i]->label = atoi(token);
            }else {
                imgs[i]->img_data.elements[(j-1) / 28][(j-1) % 28] = atoi(token) / 256.0f;
            }
            token = strtok(NULL, ",");
            j++;
        }
        i++;
    }
    fclose(fp);
    return imgs;
}

void zi_img_print(ZI_Img* img){
    MZ_print_matrix(stdout, img->img_data);
    printf("Img Label: %d\n", img->label);
}

void zi_img_free(ZI_Img* img){
	MZ_free_matrix(&img->img_data);
	free(img);
	img = NULL;
}

void zi_imgs_free(ZI_Img** imgs, int n){
	for (int i = 0; i < n; i++) {
		zi_img_free(imgs[i]);
	}
	free(imgs);
	imgs = NULL;
}

#endif // ZIMG_IMPLEMENTATION