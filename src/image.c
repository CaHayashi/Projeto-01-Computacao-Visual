#include "image.h"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <stdio.h>

// Classe image.c, responsável por:
// 1 - Realizar o carregamento e validações da extensão e caminho da imagem, convertendo - a para RGBA32;
// 2 - Validar se a imagem já se encontra em GRAYSCALE;
// 3 - Caso não se encontra em GRAYSCALE, realizar a conversão;
// 4 - Salvar imagem convertida.

// Função implementada para o CARREGAMENTO / LOAD das imagens (passadas como parametro via linha de comando) e sua conversão para RGBA32
SDL_Surface* load_image(const char *path) {

    // Criação de variável *img para armazenar a imagem carregada
    SDL_Surface *img = IMG_Load(path);

    // Validação do carregamento da imagem (se o formato é o correto e se o caminho da imagem existe)
    if (!img) {
        printf("Erro ao carregar imagem: %s\n", SDL_GetError());
        return NULL;
    }

    // Convertendo imagem para melhores tratativas, conversão para RGBA32
    SDL_Surface *formatted = SDL_ConvertSurface(img, SDL_PIXELFORMAT_RGBA32);
    // Libera a imagem original da memória
    SDL_DestroySurface(img);

    // Valida se a imagem foi convertida com sucesso
    if (!formatted) {
        printf("Erro ao converter formato: %s\n", SDL_GetError());
        return NULL;
    }

    // Retorno da imagem carregada e convertida
    return formatted;
}

// Função implementada para VALIDAR se uma imagem já se encontra em GRAYSCALE (escala cinza)
int is_grayscale(SDL_Surface *img) {
    // Variáveis auxiliares
    Uint8 r, g, b;
    SDL_LockSurface(img);

    // Variável que armazena os pixels da imagem processada, [lista de pixels, linha x coluna]
    Uint32 *pixels = (Uint32*)img->pixels;
    const SDL_PixelFormatDetails *fmt = SDL_GetPixelFormatDetails(img->format);

    // Percorre pixel por pixel, para validar a regra R=G=B
    for (int i = 0; i < img->w * img->h; i++) {
        SDL_GetRGB(pixels[i], fmt, NULL, &r, &g, &b);

        // Se qualquer pixel NÃO tiver R=G=B, não é grayscale
        if (r != g || g != b) {
            SDL_UnlockSurface(img);
            return 0; // Retorna 0, caso a imagem não esteja em grayscale
        }
    }

    SDL_UnlockSurface(img);
    // Retorna 1, caso a imagem já se encontra na escala cinza
    return 1;
}

// Função implementada para CONVERTER uma imagem para GRAYSCALE (escala cinza)
SDL_Surface* convert_to_grayscale(SDL_Surface *src) {
    // Variável *gray responsável por ser uma cópia da imagem processada, realiza a conversão para RGBA32, novamente, por segurança
    SDL_Surface *gray = SDL_ConvertSurface(src, SDL_PIXELFORMAT_RGBA32);

    // Validação da conversão para RGBA32
    if (!gray) {
        printf("Erro ao converter imagem: %s\n", SDL_GetError());
        return NULL;
    }

    SDL_LockSurface(gray);
    // Criação das variáveis auxiliares e da lista de pixels a ser percorrida
    Uint8 r, g, b;
    Uint32 *pixels = (Uint32*)gray->pixels;
    const SDL_PixelFormatDetails *fmt = SDL_GetPixelFormatDetails(gray->format);
    int total = gray->w * gray->h;

    // Percorrendo pixel por pixel da imagem
    for (int i = 0; i < total; i++) {
        // Extrai o RGB do pixel *atual
        SDL_GetRGB(pixels[i], fmt, NULL, &r, &g, &b);
        // Realiza a conversão para um pixel de tom cinza, seguindo a fórmula passada pelo professor
        Uint8 y = (Uint8)(0.2125 * r + 0.7154 * g + 0.0721 * b);
        // Substitui o pixel atual pelo pixo de tom cinza
        pixels[i] = SDL_MapRGB(fmt, NULL, y, y, y);
    }

    SDL_UnlockSurface(gray);
    // Retorna a imagem convertida para grayscale
    return gray;
}

// Funcão responsável por salvar a imagem convertida
int save_image(SDL_Surface *img, const char *path) {
    // Valida se a imagem foi salva com sucesso, caso não seja, informe o erro ao usuário
    if (IMG_SavePNG(img, path) != 0) {
        // Armazena o erro e imprime para o usuário
        const char *err = SDL_GetError();
        if (err && *err) {
            printf("Erro ao salvar imagem: %s\n", err);
        } else {
            // printf("") auxiliar que não interfere em nada, utilizado apenas por conta do else
            printf("");
        }
        return 0; // Retorna 0, em caso de erro no salvamento
    }
    // Retorna 1, em caso de sucesso 
    return 1; 
}