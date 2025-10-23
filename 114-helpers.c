#include "helpers.h"
#include <math.h>
#include <stdbool.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
    {
        for(int k = 0; k < width; k++)
        {
            int index = round((image[i][k].rgbtGreen + image[i][k].rgbtBlue + image[i][k].rgbtRed)/3.0);
            image[i][k].rgbtGreen = index;
            image[i][k].rgbtBlue = index;
            image[i][k].rgbtRed = index;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
     for(int i = 0; i < height; i++)
    {
        for(int k = 0; k < width; k++)
        {
            int red = image[i][k].rgbtRed;
            int blue = image[i][k].rgbtBlue;
            int green = image[i][k].rgbtGreen;

            //calculate red
            if(.393 * red + .769 * green + .189 * blue > 255)
            {
                image[i][k].rgbtRed = 255;
            }
            else
            {
                image[i][k].rgbtRed = round(.393 * red + .769 * green + .189 * blue);
            }

            //calculate green
            if(.349 * red + .686 * green + .168 * blue > 255)
            {
                image[i][k].rgbtGreen = 255;
            }
            else
            {
                image[i][k].rgbtGreen = round(.349 * red + .686 * green + .168 * blue );
            }

            //calculate blue
            if(.272 * red + .534 * green + .131 * blue > 255)
            {
                image[i][k].rgbtBlue = 255;
            }
            else
            {
                image[i][k].rgbtBlue = round(.272 * red + .534 * green + .131 * blue);
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
    {
        for(int k = 0; k < width/2; k++)
        {
            int blue = image[i][k].rgbtBlue;
            int green = image[i][k].rgbtGreen;
            int red = image[i][k].rgbtRed;
            image[i][k].rgbtBlue = image[i][width - k-1].rgbtBlue;
            image[i][k].rgbtGreen = image[i][width - k-1].rgbtGreen;
            image[i][k].rgbtRed = image[i][width - k-1].rgbtRed;
            image[i][width - k-1].rgbtBlue = blue;
            image[i][width - k-1].rgbtGreen = green;
            image[i][width - k-1].rgbtRed = red;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE imagecopy[height][width];

    int blue;
    int red;
    int green;
    float sum;
    bool right;
    bool left;
    bool up;
    bool down;

      for(int i = 0; i < height; i++)
    {
        for(int k = 0; k < width; k++)
        {
            imagecopy[i][k] = image[i][k];
        }
    }

    for(int i = 0; i < height; i++)
    {
        for(int k = 0; k < width; k++)
        {
            right = false;
            left = false;
            up = false;
            down = false;
            blue = 0;
            green =0;
            red = 0;
            sum = 0;

            //the middle pixel
            green += imagecopy[i][k].rgbtGreen;
            red += imagecopy[i][k].rgbtRed;
            blue += imagecopy[i][k].rgbtBlue;
            sum++;

            //up, down, left, right
            if(0 < k)
            {
                left = true;
                green += imagecopy[i][k-1].rgbtGreen;
                red += imagecopy[i][k-1].rgbtRed;
                blue += imagecopy[i][k-1].rgbtBlue;
                sum++;
            }
            if(k < width-1)
            {
                right = true;
                green += imagecopy[i][k+1].rgbtGreen;
                red += imagecopy[i][k+1].rgbtRed;
                blue += imagecopy[i][k+1].rgbtBlue;
                sum++;
            }
            if(0 < i)
            {
                up = true;
                green += imagecopy[i-1][k].rgbtGreen;
                red += imagecopy[i-1][k].rgbtRed;
                blue += imagecopy[i-1][k].rgbtBlue;
                sum++;
            }
            if(i < height-1)
            {
                down = true;
                green += imagecopy[i+1][k].rgbtGreen;
                red += imagecopy[i+1][k].rgbtRed;
                blue += imagecopy[i+1][k].rgbtBlue;
                sum++;
            }

            //corners
            if(up && left)
            {
                green += imagecopy[i-1][k-1].rgbtGreen;
                red += imagecopy[i-1][k-1].rgbtRed;
                blue += imagecopy[i-1][k-1].rgbtBlue;
                sum++;
            }
            if(up && right)
            {
                green += imagecopy[i-1][k+1].rgbtGreen;
                red += imagecopy[i-1][k+1].rgbtRed;
                blue += imagecopy[i-1][k+1].rgbtBlue;
                sum++;
            }
            if(down && left)
            {
                green += imagecopy[i+1][k-1].rgbtGreen;
                red += imagecopy[i+1][k-1].rgbtRed;
                blue += imagecopy[i+1][k-1].rgbtBlue;
                sum++;
            }
            if(down && right)
            {
                green += imagecopy[i+1][k+1].rgbtGreen;
                red += imagecopy[i+1][k+1].rgbtRed;
                blue += imagecopy[i+1][k+1].rgbtBlue;
                sum++;
            }

            //change the rgb values
            image[i][k].rgbtBlue = round(blue/sum);
            image[i][k].rgbtGreen = round(green/sum);
            image[i][k].rgbtRed = round(red/sum);
        }
    }
    return;
}
