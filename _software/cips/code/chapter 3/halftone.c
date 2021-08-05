#include <stdio.h>
#include <stdlib.h>

#define STB_IMAGE_IMPLEMENTATION
#include "../resource/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../resource/stb_image_write.h"

void halftoning(unsigned char **in_image,
                unsigned char **out_image,
                unsigned char threshold,
                unsigned char one,
                unsigned char zero,
                int rows, int cols)
{
   float **eg, **ep;
   float c[2][3]={
      {0.0, 0.2, 0.0},
      {0.6, 0.1, 0.1}
   };
   float sum_p,t;
   int i, j, m, n, xx, yy;

   /***********************************************
      *
      *   Calculate the total propogated error
      *   at location(m,n) due to prior
      *   assignment.
      *
      *   Go through the input image.  If the output
      *   should be one then display that pixel as such.
      *   If the output should be zero then display it
      *   that way.
      *
      *   Also set the pixels in the input image array
      *   to 1's and 0's in case the print option
      *   was chosen.
      *
      ************************************************/

   eg = malloc(rows * sizeof(float *));
   for (i = 0; i < rows; i++)
   {
      eg[i] = malloc(cols * sizeof(float));
      if (eg[i] == NULL)
      {
         printf("\n\tmalloc of eg[%d] failed", i);
      } /* ends if */
   }    /* ends loop over i */

   ep = malloc(rows * sizeof(float *));
   for (i = 0; i < rows; i++)
   {
      ep[i] = malloc(cols * sizeof(float));
      if (ep[i] == NULL)
      {
         printf("\n\tmalloc of ep[%d] failed", i);
      } /* ends if */
   }    /* ends loop over i */

   for (i = 0; i < rows; i++)
   {
      for (j = 0; j < cols; j++)
      {
         eg[i][j] = 0.0;
         ep[i][j] = 0.0;
      }
   }

   /**********************************************
       *
       *   29 February 1988 - Fix to remove a solid 
       *   line at the bottom of each region. Loop 
       *   over ROWS-1 and then draw an extra line.
       *
       **********************************************/

   for (m = 0; m < rows; m++)
   {
      for (n = 0; n < cols; n++)
      {

         sum_p = 0.0;
         for (i = 0; i < 2; i++)
         {
            for (j = 0; j < 3; j++)
            {

               xx = m - i;
               yy = n - j;
               if (xx < 0)
                  xx = 0;
               if (xx >= rows)
                  xx = rows - 1;
               if (yy < 0)
                  yy = 0;
               if (yy >= cols)
                  yy = cols - 1;

               sum_p = sum_p + c[i][j] * eg[xx][yy];
            } /* ends loop over j */
         }    /* ends loop over i */

         ep[m][n] = sum_p;
         t = in_image[m][n] + ep[m][n];

         /**********************************
               *
               *    Here set the point [m][n]=one
               *
               ***********************************/

         if (t > threshold)
         {
            eg[m][n] = t - threshold * 2;
            out_image[m][n] = one;
         } /* ends if t > threshold  */

         /**********************************
               *
               *    Here set the point [m][n]=zero
               *
               ***********************************/

         else
         { /* t <= threshold */
            eg[m][n] = t;
            out_image[m][n] = zero;
         } /* ends else t <= threshold  */

      } /* ends loop over n columns */
   }    /* ends loop over m rows */

   for (i = 0; i < rows; i++)
   {
      free(eg[i]);
      free(ep[i]);
   }

} /*  ends halftoning  */


void resize_to_2D(unsigned char *img1D, unsigned char **img2D, int width, int height) {
   for(int i=0;i<height;i++)
   {
      for(int j=0;j<width;j++)
      {
         img2D[i][j]=img1D[i*width+j];
      }
   }
}

void resize_to_1D(unsigned char *img1D, unsigned char **img2D, int width, int height) {
   for(int i=0;i<height;i++)
   {
      for(int j=0;j<width;j++)
      {
         img1D[i*width+j]=img2D[i][j];
      }
   }
}


int main(void) {
   int width, height, channels;
   unsigned char *img = stbi_load("../resource/lena.jpg", &width, &height, &channels, 1);
   if (img == NULL) {
      printf("Error in loading the image\n");
      exit(1);
   }
   printf("Loaded image with a width of %dpx, a height of %dpx and %d channels\n", width, height, channels);

   unsigned char **in_img, **out_img;

   in_img = malloc(height * sizeof(unsigned char *));
   for (int i = 0; i < height; i++)
   {
      in_img[i] = malloc(width * sizeof(unsigned char));
      if (in_img[i] == NULL)
      {
         printf("\n\tmalloc of in_img[%d] failed", i);
      } /* ends if */
   }    /* ends loop over i */

   out_img = malloc(height * sizeof(unsigned char *));
   for (int i = 0; i < height; i++)
   {
      out_img[i] = malloc(width * sizeof(unsigned char));
      if (out_img[i] == NULL)
      {
         printf("\n\tmalloc of out_img[%d] failed", i);
      } /* ends if */
   }    /* ends loop over i */


   resize_to_2D(img, in_img, width, height);
   
   halftoning(in_img, out_img, 127, 255, 0, height, width);

   resize_to_1D(img, out_img, width, height);
   
   stbi_write_jpg("lena_halftone.jpg", width, height, 1, img, 100);
   stbi_image_free(img);

   for (int i = 0; i < height; i++)
   {
      free(in_img[i]);
      free(out_img[i]);
   }
}