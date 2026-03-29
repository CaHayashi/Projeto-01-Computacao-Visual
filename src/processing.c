#include "processing.h"
#include <SDL3/SDL.h>
#include <math.h>

// Calcula histograma (imagem já deve estar em grayscale)
#include "processing.h"
#include <SDL3/SDL.h>
#include <math.h>

void compute_histogram(SDL_Surface *img, int histogram[256]) {
    for (int i = 0; i < 256; i++) histogram[i] = 0;

    // 🔥 LOCK
    SDL_LockSurface(img);

    Uint32 *pixels = (Uint32*)img->pixels;
    Uint8 r, g, b;

    const SDL_PixelFormatDetails *fmt = SDL_GetPixelFormatDetails(img->format);

    int total = img->w * img->h;

    for (int i = 0; i < total; i++) {
        SDL_GetRGB(pixels[i], fmt, NULL, &r, &g, &b);
        histogram[r]++;
    }

    SDL_UnlockSurface(img);
}

// Média
float compute_mean(int histogram[256], int total_pixels) {
    long sum = 0;

    for (int i = 0; i < 256; i++) {
        sum += i * histogram[i];
    }

    return (float)sum / total_pixels;
}

// Desvio padrão
float compute_stddev(int histogram[256], int total_pixels, float mean) {
    float variance = 0.0;

    for (int i = 0; i < 256; i++) {
        float diff = i - mean;
        variance += diff * diff * histogram[i];
    }

    variance /= total_pixels;

    return sqrt(variance);
}

// Classificação de brilho
const char* classify_brightness(float mean) {
    if (mean < 85) return "Escura";
    else if (mean < 170) return "Media";
    else return "Clara";
}

// Classificação de contraste
const char* classify_contrast(float stddev) {
    if (stddev < 50) return "Baixo";
    else if (stddev < 100) return "Medio";
    else return "Alto";
}

SDL_Surface* create_histogram_image(int histogram[256]) {
    int width = 256;
    int height = 200;

    SDL_Surface *img = SDL_CreateSurface(width, height, SDL_PIXELFORMAT_RGBA32);
    if (!img) return NULL;

    SDL_LockSurface(img);

    Uint8 *base = (Uint8*)img->pixels;
    int pitch = img->pitch;

    const SDL_PixelFormatDetails *fmt = SDL_GetPixelFormatDetails(img->format);

    // fundo branco
    Uint32 white = SDL_MapRGB(fmt, NULL, 255, 255, 255);
    for (int y = 0; y < height; y++) {
        Uint32 *row = (Uint32*)(base + y * pitch);
        for (int x = 0; x < width; x++) {
            row[x] = white;
        }
    }

    // encontrar max
    int max = 0;
    for (int i = 0; i < 256; i++) {
        if (histogram[i] > max) max = histogram[i];
    }

    if (max == 0) max = 1;

    // desenhar barras
    for (int x = 0; x < 256; x++) {
        int bar_height = (histogram[x] * height) / max;

        for (int y = height - 1; y >= height - bar_height; y--) {
            Uint32 *row = (Uint32*)(base + y * pitch);
            row[x] = SDL_MapRGB(fmt, NULL, 0, 0, 0);
        }
    }

    SDL_UnlockSurface(img);
    return img;
}