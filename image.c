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
    retval = GC_MALLOC(sizeof(image_t));
    retval->width = image->columns;
    retval->height = image->rows;
    retval->data = GC_MALLOC_ATOMIC(image->rows * image->columns * 3);
    ExportImagePixels(image, 0, 0, image->columns, image->rows, "BGR", CharPixel, retval->data, exception_info);
    if (exception_info->severity < ErrorException)
      CatchException(exception_info);
    DestroyImage(image);
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
