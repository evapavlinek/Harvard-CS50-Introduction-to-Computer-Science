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
            int avg = round((image[r][c].rgbtBlue + image[r][c].rgbtGreen + image[r][c].rgbtRed) / 3.0);
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

    // blur the corners
    // upper-left
    imgCopy[0][0].rgbtBlue = round((image[0][0].rgbtBlue + image[0][1].rgbtBlue + image[1][0].rgbtBlue + image[1][1].rgbtBlue) / 4.0);
    imgCopy[0][0].rgbtGreen = round((image[0][0].rgbtGreen + image[0][1].rgbtGreen + image[1][0].rgbtGreen + image[1][1].rgbtGreen) / 4.0);
    imgCopy[0][0].rgbtRed = round((image[0][0].rgbtRed + image[0][1].rgbtRed + image[1][0].rgbtRed + image[1][1].rgbtRed) / 4.0);

    // upper-right
    imgCopy[0][width - 1].rgbtBlue = round((image[0][width - 1].rgbtBlue + image[0][width - 2].rgbtBlue +
                                            image[1][width - 1].rgbtBlue + image[1][width - 2].rgbtBlue) / 4.0);
    imgCopy[0][width - 1].rgbtGreen = round((image[0][width - 1].rgbtGreen + image[0][width - 2].rgbtGreen +
                                             image[1][width - 1].rgbtGreen + image[1][width - 2].rgbtGreen) / 4.0);
    imgCopy[0][width - 1].rgbtRed = round((image[0][width - 1].rgbtRed + image[0][width - 2].rgbtRed +
                                           image[1][width - 1].rgbtRed + image[1][width - 2].rgbtRed) / 4.0);

    // lower-left
    imgCopy[height - 1][0].rgbtBlue = round((image[height - 1][0].rgbtBlue + image[height - 1][1].rgbtBlue +
                                             image[height - 2][0].rgbtBlue + image[height - 2][1].rgbtBlue) / 4.0);
    imgCopy[height - 1][0].rgbtGreen = round((image[height - 1][0].rgbtGreen + image[height - 1][1].rgbtGreen +
                                              image[height - 2][0].rgbtGreen + image[height - 2][1].rgbtGreen) / 4.0);
    imgCopy[height - 1][0].rgbtRed = round((image[height - 1][0].rgbtRed + image[height - 1][1].rgbtRed +
                                            image[height - 2][0].rgbtRed + image[height - 2][1].rgbtRed) / 4.0);

    // lower-right
    imgCopy[height - 1][width - 1].rgbtBlue = round((image[height - 1][width - 1].rgbtBlue + image[height - 1][width - 2].rgbtBlue +
                                                     image[height - 2][width - 1].rgbtBlue + image[height - 2][width - 2].rgbtBlue) / 4.0);
    imgCopy[height - 1][width - 1].rgbtGreen = round((image[height - 1][width - 1].rgbtGreen + image[height - 1][width - 2].rgbtGreen +
                                                      image[height - 2][width - 1].rgbtGreen + image[height - 2][width - 2].rgbtGreen) / 4.0);
    imgCopy[height - 1][width - 1].rgbtRed = round((image[height - 1][width - 1].rgbtRed + image[height - 1][width - 2].rgbtRed +
                                                    image[height - 2][width - 1].rgbtRed + image[height - 2][width - 2].rgbtRed) / 4.0);

    // blur the edges
    // upper and lower edges
    for (int c = 1; c < width - 2; c++)
    {
        imgCopy[0][c].rgbtBlue = round((image[0][c - 1].rgbtBlue + image[0][c].rgbtBlue + image[0][c + 1].rgbtBlue +
                                        image[1][c - 1].rgbtBlue + image[1][c].rgbtBlue + image[1][c + 1].rgbtBlue) / 6.0);
        imgCopy[0][c].rgbtGreen = round((image[0][c - 1].rgbtGreen + image[0][c].rgbtGreen + image[0][c + 1].rgbtGreen +
                                         image[1][c - 1].rgbtGreen + image[1][c].rgbtGreen + image[1][c + 1].rgbtGreen) / 6.0);
        imgCopy[0][c].rgbtRed = round((image[0][c - 1].rgbtRed + image[0][c].rgbtRed + image[0][c + 1].rgbtRed +
                                       image[1][c - 1].rgbtRed + image[1][c].rgbtRed + image[1][c + 1].rgbtRed) / 6.0);

        //printf("%i %i %i\n%i %i %i\n",
        //        image[0][c - 1].rgbtBlue, image[0][c].rgbtBlue,
        //        image[0][c + 1].rgbtBlue, image[1][c - 1].rgbtBlue,
        //        image[1][c].rgbtBlue, image[1][c + 1].rgbtBlue);
//
        //printf("The avg for %i is: %f\n", image[0][c].rgbtBlue,
        //                         round((image[0][c - 1].rgbtBlue + image[0][c].rgbtBlue + image[0][c + 1].rgbtBlue +
        //                                image[1][c - 1].rgbtBlue + image[1][c].rgbtBlue + image[1][c + 1].rgbtBlue) / 6.0));

        imgCopy[height - 1][c].rgbtBlue = round((image[height - 1][c - 1].rgbtBlue + image[height - 1][c].rgbtBlue + image[height - 1][c + 1].rgbtBlue +
                                                 image[height - 2][c - 1].rgbtBlue + image[height - 2][c].rgbtBlue + image[height - 2][c + 1].rgbtBlue) / 6.0);
        imgCopy[height - 1][c].rgbtGreen = round((image[height - 1][c - 1].rgbtGreen + image[height - 1][c].rgbtGreen + image[height - 1][c + 1].rgbtGreen +
                                                  image[height - 2][c - 1].rgbtGreen + image[height - 2][c].rgbtGreen + image[height - 2][c + 1].rgbtGreen) / 6.0);
        imgCopy[height - 1][c].rgbtRed = round((image[height - 1][c - 1].rgbtRed + image[height - 1][c].rgbtRed + image[height - 1][c + 1].rgbtRed +
                                                image[height - 2][c - 1].rgbtRed + image[height - 2][c].rgbtRed + image[height - 2][c + 1].rgbtRed) / 6.0);
    }

    // left and right edges
    for (int r = 1; r < height - 2; r++)
    {
        imgCopy[r][0].rgbtBlue = round((image[r - 1][0].rgbtBlue + image[r][0].rgbtBlue + image[r + 1][0].rgbtBlue +
                                        image[r - 1][1].rgbtBlue + image[r][1].rgbtBlue + image[r + 1][1].rgbtBlue) / 6.0);
        imgCopy[r][0].rgbtGreen = round((image[r - 1][0].rgbtGreen + image[r][0].rgbtGreen + image[r + 1][0].rgbtGreen +
                                         image[r - 1][1].rgbtGreen + image[r][1].rgbtGreen + image[r + 1][1].rgbtGreen) / 6.0);
        imgCopy[r][0].rgbtRed = round((image[r - 1][0].rgbtRed + image[r][0].rgbtRed + image[r + 1][0].rgbtRed +
                                       image[r - 1][1].rgbtRed + image[r][1].rgbtRed + image[r + 1][1].rgbtRed) / 6.0);

        imgCopy[r][width - 1].rgbtBlue = round((image[r - 1][width - 1].rgbtBlue + image[r][width - 1].rgbtBlue + image[r + 1][width - 1].rgbtBlue +
                                                image[r - 1][width - 2].rgbtBlue + image[r][width - 2].rgbtBlue + image[r + 1][width - 2].rgbtBlue) / 6.0);
        imgCopy[r][width - 1].rgbtGreen = round((image[r - 1][width - 1].rgbtGreen + image[r][width - 1].rgbtGreen + image[r + 1][width - 1].rgbtGreen +
                                                 image[r - 1][width - 2].rgbtGreen + image[r][width - 2].rgbtGreen + image[r + 1][width - 2].rgbtGreen) / 6.0);
        imgCopy[r][width - 1].rgbtRed = round((image[r - 1][width - 1].rgbtRed + image[r][width - 1].rgbtRed + image[r + 1][width - 1].rgbtRed +
                                               image[r - 1][width - 2].rgbtRed + image[r][width - 2].rgbtRed + image[r + 1][width - 2].rgbtRed) / 6.0);

    }

    // blur the rest of the imgCopy
    for (int r = 1; r < height - 1; r++)
    {
        for (int c = 1; c < width - 1; c++)
        {
            imgCopy[r][c].rgbtBlue = round((image[r - 1][c - 1].rgbtBlue + image[r - 1][c].rgbtBlue + image[r - 1][c + 1].rgbtBlue +
                                            image[r][c - 1].rgbtBlue + image[r][c].rgbtBlue + image[r][c + 1].rgbtBlue +
                                            image[r + 1][c - 1].rgbtBlue + image[r + 1][c].rgbtBlue + image[r + 1][c + 1].rgbtBlue) / 9.0);

            imgCopy[r][c].rgbtGreen = round((image[r - 1][c - 1].rgbtGreen + image[r - 1][c].rgbtGreen + image[r - 1][c + 1].rgbtGreen +
                                             image[r][c - 1].rgbtGreen + image[r][c].rgbtGreen + image[r][c + 1].rgbtGreen +
                                             image[r + 1][c - 1].rgbtGreen + image[r + 1][c].rgbtGreen + image[r + 1][c + 1].rgbtGreen) / 9.0);

            imgCopy[r][c].rgbtRed = round((image[r - 1][c - 1].rgbtRed + image[r - 1][c].rgbtRed + image[r - 1][c + 1].rgbtRed +
                                           image[r][c - 1].rgbtRed + image[r][c].rgbtRed + image[r][c + 1].rgbtRed +
                                           image[r + 1][c - 1].rgbtRed + image[r + 1][c].rgbtRed + image[r + 1][c + 1].rgbtRed) / 9.0);
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

    int Gx[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };

    int Gy[3][3] = {
        {-1, -2, -1},
        { 0,  0,  0},
        { 1,  2,  1}
    };

    // transform the corners
    // upper-left
    int GxBlue = image[0][0].rgbtBlue * Gx[1][1] + image[0][1].rgbtBlue * Gx[1][2] +
                 image[1][0].rgbtBlue * Gx[2][1] + image[1][1].rgbtBlue * Gx[2][2];
    int GyBlue = image[0][0].rgbtBlue * Gy[1][1] + image[0][1].rgbtBlue * Gy[1][2] +
                 image[1][0].rgbtBlue * Gy[2][1] + image[1][1].rgbtBlue * Gy[2][2];

    int GBlue = calculateFinalG(GxBlue, GyBlue);
    imgCopy[0][0].rgbtBlue = GBlue;

    int GxBlue = image[0][0].rgbtGreen * Gx[1][1] + image[0][1].rgbtGreen * Gx[1][2] +
                 image[1][0].rgbtGreen * Gx[2][1] + image[1][1].rgbtGreen * Gx[2][2];
    int GyGreen = image[0][0].rgbtGreen * Gy[1][1] + image[0][1].rgbtGreen * Gy[1][2] +
                  image[1][0].rgbtGreen * Gy[2][1] + image[1][1].rgbtGreen * Gy[2][2];

    int GBlue = calculateFinalG(GxBlue, GyBlue);
    imgCopy[0][0].rgbtBlue = GBlue;




    // transform the rest of the pixels
    for (int r = 1; r < height - 1; r++)
    {
        for (int c = 1; c < width - 1; c++)
        {
            GxBlue = 0;
            GyBlue = 0;
            GxGreen = 0;
            GyGreen = 0;
            GxRed = 0;
            GyRed = 0;

            for (int i = -1; i <= 1; i++)
            {
                for (int j = -1; j <= 1; j++)
                {
                    GxBlue += image[r + i][c + j].rgbtBlue * Gx[i + 1][j + 1];
                    GyBlue += image[r + i][c + j].rgbtBlue * Gy[i + 1][j + 1];
                    GxGreen += image[r + i][c + j].rgbtGreen * Gx[i + 1][j + 1];
                    GyGreen += image[r + i][c + j].rgbtGreen * Gy[i + 1][j + 1];
                    GxRed += image[r + i][c + j].rgbtRed * Gx[i + 1][j + 1];
                    GyRed += image[r + i][c + j].rgbtRed * Gy[i + 1][j + 1];
                }
            }

            GBlue = calculateFinalG(GxBlue, GyBlue);
            GGreen = calculateFinalG(GxGreen, GyGreen);
            GRed = calculateFinalG(GxRed, GyRed);

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


//RGBTRIPLE *[] copyImage(RGBTRIPLE image[][], int height, int width)
//{
//    RGBTRIPLE(*imgCopy)[width] = calloc(height, width * sizeof(RGBTRIPLE));
//    if (imgCopy == NULL)
//    {
//        printf("Not enough memory to create the copy of the original image.\n");
//        return;
//    }
//
//    for (int r = 0; r < height; r++)
//    {
//        for (int c = 0; c < width; c++)
//        {
//            imgCopy[r][c] = image[r][c];
//        }
//    }
//
//    return imgCopy;
//}

int calculateFinalG(int gxb, int gyb)
{
    int g = round(sqrt(pow(gxb, 2) + pow(gyb, 2)));
    if (g > 255)
        g = 255;
    return g;
}
