#ifndef PROCESSING_H
#define PROCESSING_H

#include <SDL3/SDL.h>

void compute_histogram(SDL_Surface *img, int histogram[256]);
float compute_mean(int histogram[256], int total_pixels);
float compute_stddev(int histogram[256], int total_pixels, float mean);
SDL_Surface* create_histogram_image(int histogram[256]);
const char* classify_brightness(float mean);
const char* classify_contrast(float stddev);

#endif