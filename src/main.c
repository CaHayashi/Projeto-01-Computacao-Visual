#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <stdio.h>
#include "image.h"
#include "processing.h"

int main(int argc, char *argv[]) {

    if (argc < 2) {
        printf("Uso: %s <imagem>\n", argv[0]);
        return 1;
    }

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Surface *img = load_image(argv[1]);
    if (!img) return 1;

    SDL_Surface *gray;

    if (is_grayscale(img)) {
        printf("Imagem já é grayscale\n");
        gray = img;
    } else {
        printf("Convertendo para grayscale...\n");
        gray = convert_to_grayscale(img);
        SDL_DestroySurface(img);
        img = NULL;
    }

    save_image(gray, "output/gray.png");
    printf("Imagem salva em output/gray.png\n");

    int histogram[256];
    int total_pixels = gray->w * gray->h;

    compute_histogram(gray, histogram);

    float mean = compute_mean(histogram, total_pixels);
    float stddev = compute_stddev(histogram, total_pixels, mean);

    printf("Media: %.2f (%s)\n", mean, classify_brightness(mean));
    printf("Desvio padrao: %.2f (%s)\n", stddev, classify_contrast(stddev));

    // ===== HISTOGRAMA =====
    SDL_Surface *hist_img = create_histogram_image(histogram);

    if (hist_img) {
        save_image(hist_img, "output/histogram.png");
        printf("Histograma salvo em output/histogram.png\n");
    }

    // ===== JANELA PRINCIPAL =====
    SDL_Window *main_window = SDL_CreateWindow(
        "Imagem",
        gray->w,
        gray->h,
        SDL_WINDOW_RESIZABLE
    );

    SDL_Renderer *main_renderer = SDL_CreateRenderer(main_window, NULL);

    // 🔥 Corrige problema de cor
    SDL_Surface *main_formatted = SDL_ConvertSurface(gray, SDL_PIXELFORMAT_RGBA32);
    SDL_Texture *main_texture = SDL_CreateTextureFromSurface(main_renderer, main_formatted);
    SDL_DestroySurface(main_formatted);

    // ===== JANELA SECUNDÁRIA =====
    int sec_width = 400;
    int sec_height = 300;

    SDL_Window *sec_window = SDL_CreateWindow(
        "Histograma",
        sec_width,
        sec_height,
        SDL_WINDOW_RESIZABLE
    );

    SDL_Renderer *sec_renderer = SDL_CreateRenderer(sec_window, NULL);

    SDL_Texture *hist_texture = NULL;

    if (hist_img) {
        // 🔥 Corrige problema de cor no histograma
        SDL_Surface *hist_formatted = SDL_ConvertSurface(hist_img, SDL_PIXELFORMAT_RGBA32);
        hist_texture = SDL_CreateTextureFromSurface(sec_renderer, hist_formatted);
        SDL_DestroySurface(hist_formatted);
    }

    int running = 1;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = 0;
            }
        }

        // ===== Render janela principal =====
        SDL_SetRenderDrawColor(main_renderer, 0, 0, 0, 255);
        SDL_RenderClear(main_renderer);
        SDL_RenderTexture(main_renderer, main_texture, NULL, NULL);
        SDL_RenderPresent(main_renderer);

        // ===== Render janela secundária =====
        SDL_SetRenderDrawColor(sec_renderer, 30, 30, 30, 255);
        SDL_RenderClear(sec_renderer);

        if (hist_texture) {
            SDL_RenderTexture(sec_renderer, hist_texture, NULL, NULL);
        }

        SDL_RenderPresent(sec_renderer);
    }

    // ===== LIMPEZA =====
    SDL_DestroyTexture(main_texture);
    if (hist_texture) SDL_DestroyTexture(hist_texture);

    SDL_DestroyRenderer(main_renderer);
    SDL_DestroyWindow(main_window);

    SDL_DestroyRenderer(sec_renderer);
    SDL_DestroyWindow(sec_window);

    SDL_DestroySurface(gray);
    if (img) SDL_DestroySurface(img);
    if (hist_img) SDL_DestroySurface(hist_img);

    SDL_Quit();

    return 0;
}