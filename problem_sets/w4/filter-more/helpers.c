#include "helpers.h"
#include "math.h"
#include "stdio.h"
#include "stdlib.h"

int calculateFinalG(int gxb, int gyb);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int r = 0; r < height; r++)
    {
        for (int c = 0; c < width; c++)
        {
            int avg =
                round((image[r][c].rgbtBlue + image[r][c].rgbtGreen + image[r][c].rgbtRed) / 3.0);
            if (avg > 255)
                avg = 255;
            image[r][c].rgbtBlue = avg;
            image[r][c].rgbtGreen = avg;
            image[r][c].rgbtRed = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int r = 0; r < height; r++)
    {
        for (int c = 0; c < width / 2; c++)
        {
            RGBTRIPLE tmp = image[r][c];
            image[r][c] = image[r][width - 1 - c];
            image[r][width - 1 - c] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // create the image copy (because altering pixels in the original image would
    // affect the calculated values for all the following pixels)
    RGBTRIPLE(*imgCopy)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    if (imgCopy == NULL)
    {
        printf("Not enough memory to create the copy image for the bluring effect.\n");
        return;
    }

    for (int r = 0; r < height; r++)
    {
        for (int c = 0; c < width; c++)
        {
            imgCopy[r][c] = image[r][c];
        }
    }

    // blur the imgCopy
    for (int r = 0; r < height; r++)
    {
        for (int c = 0; c < width; c++)
        {
            float numPixels = 0;
            int blue = 0;
            int green = 0;
            int red = 0;

            for (int i = r - 1; i <= r + 1; i++)
            {
                for (int j = c - 1; j <= c + 1; j++)
                {
                    if (i >= 0 && i < height && j >= 0 && j < width)
                    {
                        blue += image[i][j].rgbtBlue;
                        green += image[i][j].rgbtGreen;
                        red += image[i][j].rgbtRed;
                        numPixels++;
                    }
                }
            }

            imgCopy[r][c].rgbtBlue = round(blue / numPixels);
            imgCopy[r][c].rgbtGreen = round(green / numPixels);
            imgCopy[r][c].rgbtRed = round(red / numPixels);
        }
    }

    // change the original image
    for (int r = 0; r < height; r++)
    {
        for (int c = 0; c < width; c++)
        {
            image[r][c] = imgCopy[r][c];
        }
    }
    free(imgCopy);

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE(*imgCopy)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    if (imgCopy == NULL)
    {
        printf("Not enough memory to create the copy image for the bluring effect.\n");
        return;
    }

    for (int r = 0; r < height; r++)
    {
        for (int c = 0; c < width; c++)
        {
            imgCopy[r][c] = image[r][c];
        }
    }

    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};

    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // transform the pixels
    for (int r = 0; r < height; r++)
    {
        for (int c = 0; c < width; c++)
        {
            int GxBlue = 0, GyBlue = 0;
            int GxGreen = 0, GyGreen = 0;
            int GxRed = 0, GyRed = 0;

            for (int i = -1; i <= 1; i++)
            {
                for (int j = -1; j <= 1; j++)
                {
                    // if at corners or edges, do not calculate anything for the indices outside of
                    // the border
                    if (!(((r == 0 && c == 0) && (i < 0 && j < 0)) ||
                          ((r == 0 && c == width - 1) && (i < 0 && j > 0)) ||
                          ((r == height - 1 && c == 0) && (i > 0 && j < 0)) ||
                          ((r == height - 1 && c == width - 1) && (i > 0 && j > 0)) ||
                          (r == 0 && i < 0) || (r == height - 1 && i > 0) || (c == 0 && j < 0) ||
                          (c == width - 1 && j > 0)))
                    {
                        GxBlue += image[r + i][c + j].rgbtBlue * Gx[i + 1][j + 1];
                        GyBlue += image[r + i][c + j].rgbtBlue * Gy[i + 1][j + 1];
                        GxGreen += image[r + i][c + j].rgbtGreen * Gx[i + 1][j + 1];
                        GyGreen += image[r + i][c + j].rgbtGreen * Gy[i + 1][j + 1];
                        GxRed += image[r + i][c + j].rgbtRed * Gx[i + 1][j + 1];
                        GyRed += image[r + i][c + j].rgbtRed * Gy[i + 1][j + 1];
                    }
                }
            }

            int GBlue = calculateFinalG(GxBlue, GyBlue);
            int GGreen = calculateFinalG(GxGreen, GyGreen);
            int GRed = calculateFinalG(GxRed, GyRed);

            imgCopy[r][c].rgbtBlue = GBlue;
            imgCopy[r][c].rgbtGreen = GGreen;
            imgCopy[r][c].rgbtRed = GRed;
        }
    }

    // change the original image
    for (int r = 0; r < height; r++)
    {
        for (int c = 0; c < width; c++)
        {
            image[r][c] = imgCopy[r][c];
        }
    }
    free(imgCopy);

    return;
}

int calculateFinalG(int gxb, int gyb)
{
    int g = round(sqrt(pow(gxb, 2) + pow(gyb, 2)));
    if (g > 255)
        g = 255;
    return g;
}
