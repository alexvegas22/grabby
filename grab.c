#include "grab.h"
#include <X11/Xlib.h>
#include <stdio.h>
#include <png.h>

void getXimage() {
    Display *display = XOpenDisplay(NULL);
    if (!display) {
        fprintf(stderr, "Unable to open X display\n");
        return;
    }
    XWindowAttributes attr;
    int height;
    int width;
    int x = 0;
    int y = 0;
    Window root = RootWindow(display, DefaultScreen(display));
    XGetWindowAttributes(display, root, &attr);
    width = attr.width, height = attr.height;
    XImage *image = XGetImage(display, root, x, y, width, height, AllPlanes, ZPixmap);
    if (!image) {
        printf("XGetImage failed\n");
        XCloseDisplay(display);
        return;
    }

    // Save the image as a PNG file
    FILE *fp = fopen("screenshot.png", "wb");
    if (!fp) {
        fprintf(stderr, "Error opening output file\n");
        
        XCloseDisplay(display);
        return;
    }
    
    png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png_ptr) {
        fclose(fp);
        fprintf(stderr, "Error creating PNG write structure\n");
        XCloseDisplay(display);
        return;
    }

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        png_destroy_write_struct(&png_ptr, NULL);
        fclose(fp);
        fprintf(stderr, "Error creating PNG info structure\n");
        XCloseDisplay(display);
        return;
    }

    png_init_io(png_ptr, fp);
    png_set_IHDR(png_ptr, info_ptr, width, height, 16, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
    png_write_info(png_ptr, info_ptr);

    png_bytep row_pointers[height];
    for (int i = 0; i < height; ++i) {
        row_pointers[i] = (png_bytep)(image->data + i * image->bytes_per_line);
    }

    png_write_image(png_ptr, row_pointers);
    png_write_end(png_ptr, NULL);

    png_destroy_write_struct(&png_ptr, &info_ptr);
    fclose(fp);

    XCloseDisplay(display);

    printf("Screenshot saved as screenshot.png\n");
}
