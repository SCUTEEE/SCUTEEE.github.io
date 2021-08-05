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

    /* 初始化二维指针 */
    unsigned char **in_img, **out_img;

    in_img = malloc(height * sizeof(unsigned char *));
    for (int i = 0; i < height; i++)
    {
        in_img[i] = malloc(width * sizeof(unsigned char));
        if (in_img[i] == NULL)
        {
            printf("\n\tmalloc of in_img[%d] failed", i);
        } /* ends if */
    }     /* ends loop over i */

    out_img = malloc(height * sizeof(unsigned char *));
    for (int i = 0; i < height; i++)
    {
        out_img[i] = malloc(width * sizeof(unsigned char));
        if (out_img[i] == NULL)
        {
            printf("\n\tmalloc of out_img[%d] failed", i);
        } /* ends if */
    }     /* ends loop over i */

    /* 将读取的一维数据转化为二维数据 */
    resize_to_2D(img, in_img, width, height);

    /* 进行图像处理 */
    out_img = in_img;

    /* 将处理后的二维数据转化为一维数据 */
    resize_to_1D(img, out_img, width, height);

    /* 保存图像 */
    stbi_write_jpg("lean_test.jpg", width, height, 1, img, 100);

    /* 释放内存空间 */
    stbi_image_free(img);
    for (int i = 0; i < height; i++)
    {
        free(in_img[i]);
        free(out_img[i]);
    }
}