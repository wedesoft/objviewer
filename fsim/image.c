#include <gc.h>
#include <magick/MagickCore.h>
#include "image.h"


image_t *read_image(const char *file_name)
{
  image_t *retval = NULL;
  ExceptionInfo *exception_info = AcquireExceptionInfo();
  ImageInfo *image_info = CloneImageInfo((ImageInfo *)NULL);
  CopyMagickString(image_info->filename, file_name, MaxTextExtent);
  Image *images = ReadImage(image_info, exception_info);
  if (exception_info->severity < ErrorException) {
    CatchException(exception_info);
    Image *image = RemoveFirstImageFromList(&images);
    Image *flipped = FlipImage(image, exception_info);
    CatchException(exception_info);
    DestroyImage(image);
    retval = GC_MALLOC(sizeof(image_t));
    retval->width = flipped->columns;
    retval->height = flipped->rows;
    retval->data = GC_MALLOC_ATOMIC(flipped->rows * flipped->columns * 3);
    ExportImagePixels(flipped, 0, 0, flipped->columns, flipped->rows, "BGR", CharPixel, retval->data, exception_info);
    if (exception_info->severity < ErrorException)
      CatchException(exception_info);
    DestroyImage(flipped);
  };
  if (exception_info->severity >= ErrorException) {
    retval = NULL;
    fprintf(stderr, "%s\n", exception_info->reason);
    CatchException(exception_info);
  };
  DestroyImageInfo(image_info);
  DestroyExceptionInfo(exception_info);
  return retval;
}
