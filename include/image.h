#ifndef IMAGE_H
#define IMAGE_H

#include <SDL3/SDL.h>

// Classe image.h, responsável pela declaraçõ das funções implementadas na image.c

// Funcão responsável por CARREGAR a imagem
SDL_Surface* load_image(const char *path);
// Função responsável por VALIDAR se a imagem já se encontra em GRAYSCALE
int is_grayscale(SDL_Surface *img);
// Função responsável por CONVERTER a imagem GRAYSCALE
SDL_Surface* convert_to_grayscale(SDL_Surface *src);
// Função responsável por SALVAR a imagem convertida
int save_image(SDL_Surface *img, const char *path);

#endif