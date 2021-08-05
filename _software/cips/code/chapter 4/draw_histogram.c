#include <stdio.h>
#include <stdlib.h>

#define STB_IMAGE_IMPLEMENTATION
#include "../resource/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../resource/stb_image_write.h"

/* 将一维数据转化为二维数据 */
void resize_to_2D(unsigned char *img1D, unsigned char **img2D, int width, int height)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            img2D[i][j] = img1D[i * width + j];
        }
    }
}

/* 将二维数据转化为一维数据 */
void resize_to_1D(unsigned char *img1D, unsigned char **img2D, int width, int height)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            img1D[i * width + j] = img2D[i][j];
        }
    }
}


void vline(unsigned char **image, int x, int ymin, int ymax, unsigned char color)
{
   int i, j;
   for(i=ymin; i<ymax; i++)
      image[i][x] = color;

}  /* ends vline */

void hline(unsigned char **image, int y, int xmin, int xmax, unsigned char color)
{
   int i, j;
   for(i=xmin; i<xmax; i++)
      image[y][i] = color;

}  /* ends hline */

void calculate_histogram(unsigned char **image, unsigned long *histogram, int width, int height)
{
   int i,j;
   unsigned char k;
   for(i=0; i<height; i++){
      for(j=0; j<width; j++){
         k = image[i][j];
         histogram[k] = histogram[k] + 1;
      }
   }
}  /* ends calculate_histogram */

void draw_histogram(unsigned char **image, unsigned long *histogram, int width, int height, int maxval)
{
    int max=0;

    for(int i=0; i<maxval; i++)
        if(histogram[i] > max)
            max = histogram[i];

    float y_scale = (height-1)*1.0/max;
    float x_scale = (width-1)*1.0/maxval;

    for(int i=0; i<maxval+1; i++)
    {
        int amount = histogram[i]*y_scale;
        if(amount>0)
        {
            vline(image, i*x_scale, height-amount-1, height-1, 128);
        }
    }

    hline(image, height-1, 0, width-1, 128);
}

unsigned char ** allocate_image_array(int width, int height)
{
    unsigned char **img;
    img = malloc(height * sizeof(unsigned char *));
    for (int i = 0; i < height; i++)
    {
        img[i] = malloc(width * sizeof(unsigned char));
        if (img[i] == NULL)
        {
            printf("\n\tmalloc of img[%d] in allocate_image_array failed", i);
        } /* ends if */
    }     /* ends loop over i */
    return img;
}

void free_image_array(unsigned char **img, int height)
{
    for (int i = 0; i < height; i++)
    {
        free(img[i]);
    }
}


unsigned char ** vconcat(unsigned char **img1, unsigned char **img2, int width, int height1, int height2)
{
    unsigned char **img3;
    int height3 = height1 + height2;
    img3 = allocate_image_array(width, height3);

    int i,j;
    for(i=0;i<height1;++i)
    {
        for(j=0;j<width;++j)
        {
            img3[i][j] = img1[i][j];
        }
    }
    for(i=0;i<height2;++i)
    {
        for(j=0;j<width;++j)
        {
            img3[height1+i][j] = img2[i][j];
        }
    }

    return img3;
}



/* 主函数 */
int main(void)
{
    /* 读取图像 */
    int width, height, channels;
    unsigned char *img = stbi_load("../resource/lena.jpg", &width, &height, &channels, 1);
    if (img == NULL)
    {
        printf("Error in loading the image\n");
        exit(1);
    }
    printf("Loaded image with a width of %dpx, a height of %dpx and %d channels\n", width, height, channels);


    unsigned char **in_img, **out_img;
    in_img = allocate_image_array(width, height);
    resize_to_2D(img, in_img, width, height);

    unsigned long histogram[256]={0};
    calculate_histogram(in_img, histogram, width, height);


    int height2=100;
    out_img = allocate_image_array(width, height2);

    draw_histogram(out_img, histogram, width, height2, 255);

    unsigned char **img_array = vconcat(in_img, out_img, width, height, height2);

    unsigned char *img2 = malloc(width*(height+height2)*sizeof(unsigned char));
    resize_to_1D(img2, img_array, width, (height+height2));

    /* 保存图像 */
    stbi_write_jpg("lena_histogram.jpg", width, (height+height2), 1, img2, 100);

    /* 释放内存空间 */
    stbi_image_free(img);
    stbi_image_free(img2);
    free_image_array(in_img, height);
    free_image_array(out_img, height2);
}