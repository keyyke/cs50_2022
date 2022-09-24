#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int blue;
    int green;
    int red;
    int gray;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            blue = image[i][j].rgbtBlue;
            green = image[i][j].rgbtGreen;
            red = image[i][j].rgbtRed;

            // Calculate avg
            gray = (int) round((blue + green + red) / 3.0);

            // Set Gray
            image[i][j].rgbtBlue = gray;
            image[i][j].rgbtGreen = gray;
            image[i][j].rgbtRed = gray;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int tmpBlue;
    int tmpGreen;
    int tmpRed;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            tmpBlue = image[i][j].rgbtBlue;
            tmpGreen = image[i][j].rgbtGreen;
            tmpRed = image[i][j].rgbtRed;

            // Change left
            image[i][j].rgbtBlue = image[i][width - 1 - j].rgbtBlue;
            image[i][j].rgbtGreen = image[i][width - 1 - j].rgbtGreen;
            image[i][j].rgbtRed = image[i][width - 1 - j].rgbtRed;

            // Change right
            image[i][width - 1 - j].rgbtBlue = tmpBlue;
            image[i][width - 1 - j].rgbtGreen = tmpGreen;
            image[i][width - 1 - j].rgbtRed = tmpRed;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int avgBlue;
    int avgGreen;
    int avgRed;

    //create a temporary image to be blurred
    RGBTRIPLE tmp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            tmp[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Upper Left Corner
            if (i == 0 && j == 0)
            {
                avgBlue = (int) round((tmp[i][j].rgbtBlue + tmp[i][j + 1].rgbtBlue + tmp[i + 1][j].rgbtBlue + tmp[i + 1][j + 1].rgbtBlue) / 4.0);
                avgGreen = (int) round((tmp[i][j].rgbtGreen + tmp[i][j + 1].rgbtGreen + tmp[i + 1][j].rgbtGreen + tmp[i + 1][j + 1].rgbtGreen) /
                                       4.0);
                avgRed = (int) round((tmp[i][j].rgbtRed + tmp[i][j + 1].rgbtRed + tmp[i + 1][j].rgbtRed + tmp[i + 1][j + 1].rgbtRed) / 4.0);
            }
            // Upper Right Corner
            else if (i == 0 && j == width - 1)
            {
                avgBlue = (int) round((tmp[i][j].rgbtBlue + tmp[i][j - 1].rgbtBlue + tmp[i + 1][j].rgbtBlue + tmp[i + 1][j - 1].rgbtBlue) / 4.0);
                avgGreen = (int) round((tmp[i][j].rgbtGreen + tmp[i][j - 1].rgbtGreen + tmp[i + 1][j].rgbtGreen + tmp[i + 1][j - 1].rgbtGreen) /
                                       4.0);
                avgRed = (int) round((tmp[i][j].rgbtRed + tmp[i][j - 1].rgbtRed + tmp[i + 1][j].rgbtRed + tmp[i + 1][j - 1].rgbtRed) / 4.0);
            }
            // Lower Left Corner
            else if (i == height - 1 && j == 0)
            {
                avgBlue = (int) round((tmp[i][j].rgbtBlue + tmp[i][j + 1].rgbtBlue + tmp[i - 1][j].rgbtBlue + tmp[i - 1][j + 1].rgbtBlue) / 4.0);
                avgGreen = (int) round((tmp[i][j].rgbtGreen + tmp[i][j + 1].rgbtGreen + tmp[i - 1][j].rgbtGreen + tmp[i - 1][j + 1].rgbtGreen) /
                                       4.0);
                avgRed = (int) round((tmp[i][j].rgbtRed + tmp[i][j + 1].rgbtRed + tmp[i - 1][j].rgbtRed + tmp[i - 1][j + 1].rgbtRed) / 4.0);
            }
            // Lower Right Corner
            else if (i == height - 1 && j == width - 1)
            {
                avgBlue = (int) round((tmp[i][j].rgbtBlue + tmp[i][j - 1].rgbtBlue + tmp[i - 1][j].rgbtBlue + tmp[i - 1][j - 1].rgbtBlue) / 4.0);
                avgGreen = (int) round((tmp[i][j].rgbtGreen + tmp[i][j - 1].rgbtGreen + tmp[i - 1][j].rgbtGreen + tmp[i - 1][j - 1].rgbtGreen) /
                                       4.0);
                avgRed = (int) round((tmp[i][j].rgbtRed + tmp[i][j - 1].rgbtRed + tmp[i - 1][j].rgbtRed + tmp[i - 1][j - 1].rgbtRed) / 4.0);
            }
            // Upper Edge
            else if (i == 0)
            {
                avgBlue = (int) round((tmp[i][j].rgbtBlue + tmp[i][j + 1].rgbtBlue + tmp[i + 1][j + 1].rgbtBlue + tmp[i + 1][j].rgbtBlue + tmp[i +
                                       1][j - 1].rgbtBlue + tmp[i][j - 1].rgbtBlue) / 6.0);
                avgGreen = (int) round((tmp[i][j].rgbtGreen + tmp[i][j + 1].rgbtGreen + tmp[i + 1][j + 1].rgbtGreen + tmp[i + 1][j].rgbtGreen
                                        + tmp[i + 1][j - 1].rgbtGreen + tmp[i][j - 1].rgbtGreen) / 6.0);
                avgRed = (int) round((tmp[i][j].rgbtRed + tmp[i][j + 1].rgbtRed + tmp[i + 1][j + 1].rgbtRed + tmp[i + 1][j].rgbtRed + tmp[i + 1][j -
                                      1].rgbtRed + tmp[i][j - 1].rgbtRed) / 6.0);
            }
            // Lower Edge
            else if (i == height - 1)
            {
                avgBlue = (int) round((tmp[i][j].rgbtBlue + tmp[i][j - 1].rgbtBlue + tmp[i - 1][j - 1].rgbtBlue + tmp[i - 1][j].rgbtBlue + tmp[i -
                                       1][j + 1].rgbtBlue + tmp[i][j + 1].rgbtBlue) / 6.0);
                avgGreen = (int) round((tmp[i][j].rgbtGreen + tmp[i][j - 1].rgbtGreen + tmp[i - 1][j - 1].rgbtGreen + tmp[i - 1][j].rgbtGreen +
                                        tmp[i - 1][j + 1].rgbtGreen + tmp[i][j + 1].rgbtGreen) / 6.0);
                avgRed = (int) round((tmp[i][j].rgbtRed + tmp[i][j - 1].rgbtRed + tmp[i - 1][j - 1].rgbtRed + tmp[i - 1][j].rgbtRed + tmp[i - 1][j +
                                      1].rgbtRed + tmp[i][j + 1].rgbtRed) / 6.0);
            }
            // Left Edge
            else if (j == 0)
            {
                avgBlue = (int) round((tmp[i][j].rgbtBlue + tmp[i - 1][j].rgbtBlue + tmp[i - 1][j + 1].rgbtBlue + tmp[i][j + 1].rgbtBlue + tmp[i +
                                       1][j + 1].rgbtBlue + tmp[i + 1][j].rgbtBlue) / 6.0);
                avgGreen = (int) round((tmp[i][j].rgbtGreen + tmp[i - 1][j].rgbtGreen + tmp[i - 1][j + 1].rgbtGreen + tmp[i][j + 1].rgbtGreen +
                                        tmp[i + 1][j + 1].rgbtGreen + tmp[i + 1][j].rgbtGreen) / 6.0);
                avgRed = (int) round((tmp[i][j].rgbtRed + tmp[i - 1][j].rgbtRed + tmp[i - 1][j + 1].rgbtRed + tmp[i][j + 1].rgbtRed + tmp[i + 1][j +
                                      1].rgbtRed + tmp[i + 1][j].rgbtRed) / 6.0);
            }
            // Right Edge
            else if (j == width - 1)
            {
                avgBlue = (int) round((tmp[i][j].rgbtBlue + tmp[i + 1][j].rgbtBlue + tmp[i + 1][j - 1].rgbtBlue + tmp[i][j - 1].rgbtBlue + tmp[i -
                                       1][j - 1].rgbtBlue + tmp[i - 1][j].rgbtBlue) / 6.0);
                avgGreen = (int) round((tmp[i][j].rgbtGreen + tmp[i + 1][j].rgbtGreen + tmp[i + 1][j - 1].rgbtGreen + tmp[i][j - 1].rgbtGreen +
                                        tmp[i - 1][j - 1].rgbtGreen + tmp[i - 1][j].rgbtGreen) / 6.0);
                avgRed = (int) round((tmp[i][j].rgbtRed + tmp[i + 1][j].rgbtRed + tmp[i + 1][j - 1].rgbtRed + tmp[i][j - 1].rgbtRed + tmp[i - 1][j -
                                      1].rgbtRed + tmp[i - 1][j].rgbtRed) / 6.0);
            }
            else
            {
                avgBlue = (int) round((tmp[i][j].rgbtBlue + tmp[i + 1][j].rgbtBlue + tmp[i + 1][j - 1].rgbtBlue + tmp[i][j - 1].rgbtBlue + tmp[i -
                                       1][j - 1].rgbtBlue + tmp[i - 1][j].rgbtBlue + tmp[i - 1][j + 1].rgbtBlue + tmp[i][j + 1].rgbtBlue + tmp[i + 1][j + 1].rgbtBlue) /
                                      9.0);
                avgGreen = (int) round((tmp[i][j].rgbtGreen + tmp[i + 1][j].rgbtGreen + tmp[i + 1][j - 1].rgbtGreen + tmp[i][j - 1].rgbtGreen +
                                        tmp[i - 1][j - 1].rgbtGreen + tmp[i - 1][j].rgbtGreen + tmp[i - 1][j + 1].rgbtGreen + tmp[i][j + 1].rgbtGreen + tmp[i + 1][j +
                                                1].rgbtGreen) / 9.0);
                avgRed = (int) round((tmp[i][j].rgbtRed + tmp[i + 1][j].rgbtRed + tmp[i + 1][j - 1].rgbtRed + tmp[i][j - 1].rgbtRed + tmp[i - 1][j -
                                      1].rgbtRed + tmp[i - 1][j].rgbtRed + tmp[i - 1][j + 1].rgbtRed + tmp[i][j + 1].rgbtRed + tmp[i + 1][j + 1].rgbtRed) / 9.0);
            }

            // Set colour
            image[i][j].rgbtBlue = avgBlue;
            image[i][j].rgbtGreen = avgGreen;
            image[i][j].rgbtRed = avgRed;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    double avgBlueGx;
    double avgGreenGx;
    double avgRedGx;
    double avgBlueGy;
    double avgGreenGy;
    double avgRedGy;
    int Red;
    int Green;
    int Blue;

    //create a temporary image to be blurred
    RGBTRIPLE tmp[height + 2][width + 2];
    RGBTRIPLE black;
    black.rgbtBlue = 0;
    black.rgbtGreen = 0;
    black.rgbtRed = 0;
    for (int i = 0; i < height + 2; i++)
    {
        for (int j = 0; j < width + 2; j++)
        {
            if (i == 0 || i == height + 1 || j == 0 || j == width + 1)
            {
                tmp[i][j] = black;
            }
            else
            {
                tmp[i][j] = image[i - 1][j - 1];
            }
        }
    }

    for (int i = 1; i < height + 1; i++)
    {
        for (int j = 1; j < width + 1; j++)
        {
            // Calculate Gx
            avgBlueGx = ((-1) * tmp[i + 1][j - 1].rgbtBlue + (-2) * tmp[i][j - 1].rgbtBlue + (-1) * tmp[i - 1][j - 1].rgbtBlue + tmp[i - 1][j +
                         1].rgbtBlue + 2 * tmp[i][j + 1].rgbtBlue + tmp[i + 1][j + 1].rgbtBlue);
            avgGreenGx = ((-1) * tmp[i + 1][j - 1].rgbtGreen + (-2) * tmp[i][j - 1].rgbtGreen + (-1) * tmp[i - 1][j - 1].rgbtGreen + tmp[i -
                          1][j + 1].rgbtGreen + 2 * tmp[i][j + 1].rgbtGreen + tmp[i + 1][j + 1].rgbtGreen);
            avgRedGx = ((-1) * tmp[i + 1][j - 1].rgbtRed + (-2) * tmp[i][j - 1].rgbtRed + (-1) * tmp[i - 1][j - 1].rgbtRed + tmp[i - 1][j +
                        1].rgbtRed + 2 * tmp[i][j + 1].rgbtRed + tmp[i + 1][j + 1].rgbtRed);

            // Calculate Gy
            avgBlueGy = (2 * tmp[i + 1][j].rgbtBlue + tmp[i + 1][j - 1].rgbtBlue + (-1) * tmp[i - 1][j - 1].rgbtBlue +
                         (-2) * tmp[i - 1][j].rgbtBlue + (-1) * tmp[i - 1][j + 1].rgbtBlue + tmp[i + 1][j + 1].rgbtBlue);
            avgGreenGy = (2 * tmp[i + 1][j].rgbtGreen + tmp[i + 1][j - 1].rgbtGreen + (-1) * tmp[i - 1][j - 1].rgbtGreen +
                          (-2) * tmp[i - 1][j].rgbtGreen + (-1) * tmp[i - 1][j + 1].rgbtGreen + tmp[i + 1][j + 1].rgbtGreen);
            avgRedGy = (2 * tmp[i + 1][j].rgbtRed + tmp[i + 1][j - 1].rgbtRed + (-1) * tmp[i - 1][j - 1].rgbtRed +
                        (-2) * tmp[i - 1][j].rgbtRed + (-1) * tmp[i - 1][j + 1].rgbtRed + tmp[i + 1][j + 1].rgbtRed);

            // Calculate R G B
            Blue = (int) round(sqrt((avgBlueGx * avgBlueGx) + (avgBlueGy * avgBlueGy)));
            Green = (int) round(sqrt((avgGreenGx * avgGreenGx) + (avgGreenGy * avgGreenGy)));
            Red = (int) round(sqrt((avgRedGx * avgRedGx) + (avgRedGy * avgRedGy)));

            // number must not be greater than 255
            if (Blue > 255)
            {
                Blue = 255;
            }
            if (Green > 255)
            {
                Green = 255;
            }
            if (Red > 255)
            {
                Red = 255;
            }

            // Set colour
            image[i - 1][j - 1].rgbtBlue = Blue;
            image[i - 1][j - 1].rgbtGreen = Green;
            image[i - 1][j - 1].rgbtRed = Red;
        }
    }
    return;
}
