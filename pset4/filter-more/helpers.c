// TODO:
#include "helpers.h"
#include "math.h"

int min(int x, int y);
float gx(int step, BYTE rgb);
float gy(int step, BYTE rgb);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop through all pixels in the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculate the average of each R,G and B value
            int r = image[i][j].rgbtRed, g = image[i][j].rgbtGreen, b = image[i][j].rgbtBlue;
            float rgbAvgs = (r + g + b) / 3.0;
            int avg = roundf(rgbAvgs);
            // Update pixel setting the RGB values to the average
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop through all pixels in the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // Swap pixels
            RGBTRIPLE tmp = image[i][j];
            image[i][j] = image[i][(width - j) - 1];
            image[i][(width - j) - 1] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop through all pixels in the image and making a copy
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }
    // Loop through each pixel in the copied image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int neighbors = 0;
            int r = 0, g = 0, b = 0;
            // Index to each adjacent pixel
            for (int row = i - 1; row <= i + 1; row++)
            {
                // Validate row
                if (row >= 0 && row < height)
                {
                    for (int px = j - 1; px <= j + 1; px++)
                    {
                        // Validate pixel
                        if (px >= 0 && px < width)
                        {
                            // Add the RGB values to the sum of each
                            r += copy[row][px].rgbtRed;
                            g += copy[row][px].rgbtGreen;
                            b += copy[row][px].rgbtBlue;
                            neighbors++;
                        }
                    }
                }
            }
            // Apply box blur to the pixel in the original image
            image[i][j].rgbtRed = min(round(r / (neighbors * 1.0)), 255);
            image[i][j].rgbtGreen = min(round(g / (neighbors * 1.0)), 255);
            image[i][j].rgbtBlue = min(round(b / (neighbors * 1.0)), 255);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop through all pixels in the image and making a copy
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }
    // Loop through each pixel in the copied image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int steps = 0;
            float gxR = 0, gxG = 0, gxB = 0;
            float gyR = 0, gyG = 0, gyB = 0;
            // Index to each adjacent pixel
            for (int row = i - 1; row <= i + 1; row++)
            {
                for (int px = j - 1; px <= j + 1; px++)
                {
                    if ((row >= 0 && row < height) && (px >= 0 && px < width))
                    {
                        // Sum gx value
                        gxR += gx(steps, copy[row][px].rgbtRed);
                        gxG += gx(steps, copy[row][px].rgbtGreen);
                        gxB += gx(steps, copy[row][px].rgbtBlue);
                        // Sum gy value
                        gyR += gy(steps, copy[row][px].rgbtRed);
                        gyG += gy(steps, copy[row][px].rgbtGreen);
                        gyB += gy(steps, copy[row][px].rgbtBlue);
                    }
                    steps++;
                }
            }
            // Square and round gx values
            gxR = gxR * gxR;
            gxG = gxG * gxG;
            gxB = gxB * gxB;
            // Square and round gy values
            gyR = gyR * gyR;
            gyG = gyG * gyG;
            gyB = gyB * gyB;
            // Apply box blur to the pixel in the original image
            image[i][j].rgbtRed = min(round(sqrt(gxR + gyR)), 255);
            image[i][j].rgbtGreen = min(round(sqrt(gxG + gyG)), 255);
            image[i][j].rgbtBlue = min(round(sqrt(gxB + gyB)), 255);
        }
    }
    return;
}

// Function that return the lowest of two values
int min(int x, int y)
{
    if (x > y)
        return y;
    return x;
}

float gx(int step, BYTE rgb)
{
    switch (step)
    {
        case 0:
        case 6:
            return rgb * -1;
        case 2:
        case 8:
            return rgb;
        case 3:
            return rgb * -2;
        case 5:
            return rgb * 2;
        // case 1, 4, 7
        default:
            return 0;
    }
}

float gy(int step, BYTE rgb)
{
    switch (step)
    {
        case 0:
        case 2:
            return rgb * -1;
        case 6:
        case 8:
            return rgb;
        case 1:
            return rgb * -2;
        case 7:
            return rgb * 2;
        // case 3, 4, 5
        default:
            return 0;
    }
}
