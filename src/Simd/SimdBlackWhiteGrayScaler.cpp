#include "Simd/SimdMemory.h"
#include "Simd/SimdStore.h"
#include "Simd/SimdSet.h"

typedef unsigned char luminance;
typedef luminance pixel1[1];
typedef struct {
   unsigned int width;
   unsigned int height;
   luminance *buf;
} grayimage_t;
typedef grayimage_t *grayimage;
 
grayimage alloc_grayimg(unsigned int, unsigned int);
grayimage tograyscale(image);
image tocolor(grayimage);

grayimage alloc_grayimg(unsigned int width, unsigned int height)
{
     grayimage img;
     img = malloc(sizeof(grayimage_t));
     img->buf = malloc(width*height*sizeof(pixel1));
     img->width = width;
     img->height = height;
     return img;
}

grayimage tograyscale(image img)
{
   unsigned int x, y;
   grayimage timg;
   double rc, gc, bc, l;
   unsigned int ofs;
 
   timg = alloc_grayimg(img->width, img->height);
 
   for(x=0; x < img->width; x++)
   {
      for(y=0; y < img->height; y++)
      {
        ofs = (y * img->width) + x;
        rc = (double) img->buf[ofs][0];
        gc = (double) img->buf[ofs][1];
        bc = (double) img->buf[ofs][2];
        l = 0.2126*rc + 0.7152*gc + 0.0722*bc;
        timg->buf[ofs][0] = (luminance) (l+0.5);
      }
   }
   return timg;
}

image tocolor(grayimage img)
{
   unsigned int x, y;
   image timg;
   luminance l;
   unsigned int ofs;
 
   timg = alloc_img(img->width, img->height);
 
   for(x=0; x < img->width; x++)
   {
      for(y=0; y < img->height; y++)
      {
        ofs = (y * img->width) + x;
        l = img->buf[ofs][0];
        timg->buf[ofs][0] = l;
        timg->buf[ofs][1] = l;
        timg->buf[ofs][2] = l;
      }
   }
   return timg;
}