#include "helpers.h"
#include <math.h>

#define red rgbtRed
#define blue rgbtBlue
#define green rgbtGreen

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Assigns new greyscale value to the values in the image array
    int avg;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            avg = round((image[i][j].rgbtRed + image[i][j].rgbtBlue + image[i][j].rgbtGreen) / 3.0);
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // RGBTRIPLE temp;
    int temp[3];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[0] = round(0.393 * image[i][j].red + 0.769 * image[i][j].green + 0.189 * image[i][j].blue);
            temp[1] = round(0.349 * image[i][j].red + 0.686 * image[i][j].green + 0.168 * image[i][j].blue);
            temp[2] = round(0.272 * image[i][j].red + 0.534 * image[i][j].green + 0.131 * image[i][j].blue);

            for (int k = 0; k < 3; k++)
            {
                if (temp[k] > 255)
                {
                    temp[k] = 255;
                }
            }

            image[i][j].red = temp[0];
            image[i][j].green = temp[1];
            image[i][j].blue = temp[2];
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;
    // Reflects the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int sum[4] = {0, 0, 0, 0};
    RGBTRIPLE img[height][width];
    // Copies the contents of image to img array
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            img[i][j] = image[i][j];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            for (int k = i - 1; k < i + 2; k++)
            {
                for (int l = j - 1; l < j + 2; l++)
                {
                    if (((k >= 0) && (l >= 0)) && ((k < height) && (l < width)))
                    {
                        sum[0] += (int)img[k][l].rgbtRed;
                        sum[1] += (int)img[k][l].rgbtGreen;
                        sum[2] += (int)img[k][l].rgbtBlue;
                        sum[3]++;
                    }
                }
            }

            image[i][j].rgbtRed = round(sum[0] / (float)sum[3]);
            image[i][j].rgbtGreen = round(sum[1] / (float)sum[3]);
            image[i][j].rgbtBlue = round(sum[2] / (float)sum[3]);

            for (int k = 0; k < 4; k++)
            {
                sum[k] = 0;
            }
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE img[height][width];
    int sum[4] = {0, 0, 0, 0};

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            img[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            for (int k = i - 1; k < i + 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    if (((k >= 0) && (l >= 0)) && ((k < height) && (l < width)))
                    {
                        sum[0] += img[k][j + l].rgbtRed * l;
                        sum[1] += img[k][j + l].rgbtGreen * l;
                        sum[2] += img[k][j + l].rgbtBlue * l;
                        sum[3]++;
                    }
                }
            }

            for (int k = 0; k < 4; k++)
            {
                sum[k] = 0;
            }
        }
    }

    return;
}
