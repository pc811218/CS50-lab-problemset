#include "helpers.h"
#include <math.h>

// int IIF(int a, int b) {
//     if a
// }

int thresholdColor(int value) {
    if(value > 255)
        return 255;
    else
        return value;
}

void swap(BYTE *a, BYTE *b) {
    BYTE temp = *a;
    *a = *b;
    *b = temp;
}

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int avg;
    for (int h = 0; h < height; h++) {
        for (int w = 0; w < width; w++) {
            avg = round((image[h][w].rgbtBlue + image[h][w].rgbtGreen + image[h][w].rgbtRed) / 3.0);
            image[h][w].rgbtRed = avg;
            image[h][w].rgbtGreen = avg;
            image[h][w].rgbtBlue = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int originalRed;
    int originalGreen;
    int originalBlue;

    for (int h = 0; h < height; h++) {
        for (int w = 0; w < width; w++) {
            originalRed = image[h][w].rgbtRed;
            originalGreen = image[h][w].rgbtGreen;
            originalBlue = image[h][w].rgbtBlue;

            image[h][w].rgbtRed = thresholdColor(round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue));
            image[h][w].rgbtGreen = thresholdColor(round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue));
            image[h][w].rgbtBlue = thresholdColor(round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue));

        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int w_max_idx = width - 1;
    for (int h = 0; h < height; h++) {
        for (int w = 0, mid = width/2; w < mid; w++) {
            swap(&image[h][w].rgbtRed, &image[h][w_max_idx - w].rgbtRed);
            swap(&image[h][w].rgbtGreen, &image[h][w_max_idx - w].rgbtGreen);
            swap(&image[h][w].rgbtBlue, &image[h][w_max_idx - w].rgbtBlue);
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    //copy
    for (int h = 0; h < height; h++) {
        for (int w = 0; w < width; w++) {
            copy[h][w].rgbtRed = image[h][w].rgbtRed;
            copy[h][w].rgbtGreen = image[h][w].rgbtGreen;
            copy[h][w].rgbtBlue = image[h][w].rgbtBlue;
        }
    }

    //blur
    for (int h = 0; h < height; h++) {
        for (int w = 0; w < width; w++) {

            int h_head = h-1 >= 0 ? h-1 : 0;
            int h_end = h+1 < height ? h+1 : height-1;
            int w_head = w-1 >= 0 ? w-1 : 0;
            int w_end = w+1 < width ? w+1 : width-1;

            int count = 0, R_total = 0, G_total = 0, B_total = 0;

            for(int i = h_head; i <= h_end; i++) {
                for(int j = w_head; j <= w_end; j++) {
                    R_total += copy[i][j].rgbtRed;
                    G_total += copy[i][j].rgbtGreen;
                    B_total += copy[i][j].rgbtBlue;
                    count++;
                }
            }

            image[h][w].rgbtRed =  round(R_total/(double) count);
            image[h][w].rgbtGreen = round(G_total/(double) count);
            image[h][w].rgbtBlue = round(B_total/(double) count);
        }
    }

    return;
}
