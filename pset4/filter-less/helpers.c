#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate through each pixel in the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculate average RGB value
            BYTE avg =
                round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);

            // Assign the average to the pixel's RGB colors
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
    // Iterate through each pixel in the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Store the original pixel values
            BYTE currentRed = image[i][j].rgbtRed;
            BYTE currentGreen = image[i][j].rgbtGreen;
            BYTE currentBlue = image[i][j].rgbtBlue;

            // Calculate sepia tone RGB values
            int sepiaRed = round(.393 * currentRed + .769 * currentGreen + .189 * currentBlue);
            int sepiaGreen = round(.349 * currentRed + .686 * currentGreen + .168 * currentBlue);
            int sepiaBlue = round(.272 * currentRed + .534 * currentGreen + .131 * currentBlue);

            // Ensure sepia colors are within the valid range
            image[i][j].rgbtRed = sepiaRed > 255 ? 255 : sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen > 255 ? 255 : sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue > 255 ? 255 : sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate through each row in the image
    for (int i = 0; i < height; i++)
    {
        // Reflect each pixel in the row
        for (int j = 0; j < width / 2; j++)
        {
            // Swap the current pixel with the corresponding pixel from the end of the row
            RGBTRIPLE tmp_pixel = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = tmp_pixel;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Make a copy of original image
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // Iterate through each pixel in the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int total_color_sum[3] = {0, 0, 0}; // Array to store the neighboring pixel's RGB to
            int valid_pixels = 0;               // Counter for valid neighboring pixels

            // Iterate through the 3x3 grid of neighboring pixels
            for (int ni = i - 1; ni <= i + 1; ni++)
            {
                if (ni >= 0 && ni < height) // Check row bounds
                {
                    for (int nj = j - 1; nj <= j + 1; nj++)
                    {
                        if (nj >= 0 && nj < width) // Check column bounds
                        {
                            // Accumulate neighboring pixel colors
                            total_color_sum[0] += copy[ni][nj].rgbtRed;
                            total_color_sum[1] += copy[ni][nj].rgbtGreen;
                            total_color_sum[2] += copy[ni][nj].rgbtBlue;
                            valid_pixels++;
                        }
                    }
                }
            }
            // Calculate average RGB values and assign them to the current pixel
            image[i][j].rgbtRed = round(total_color_sum[0] / (double) valid_pixels);
            image[i][j].rgbtGreen = round(total_color_sum[1] / (double) valid_pixels);
            image[i][j].rgbtBlue = round(total_color_sum[2] / (double) valid_pixels);
        }
    }

    return;
}
