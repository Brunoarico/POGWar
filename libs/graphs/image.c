/******************************************************************************
 *  Nome:   Bruno Arico         8125459
 *          Gabriel Capella     8962078
 *          Nicolas Nogueira    9277541
 *
 *  Projeto da disciplina de Laboratorio de Programacao MAC0211
 *  Batalha Espacial
 *
 *  Manipulacao de imagens
 *
 *  https://gist.github.com/niw/5963798
 *
 ******************************************************************************/

#include "image.h"

void image_delete (Image img) {
    free (img);
}

void image_zoom (Image img, double z) {
    img->zoom = z;
}

Image image_create (char *filename) {
    Image img;
    img = malloc (sizeof (struct image));
    img->zoom = 1.0;
    img->h = 0;
    img->w = 0;
    img->filename = filename;
    return img;
}

void image_load (Image img) {

    FILE *fp;
    float *data;
    int y, x;
    unsigned long location = 0;
    int width, height;
    png_byte color_type;
    png_byte bit_depth;
    png_bytep *row_pointers;
    png_structp png;
    png_infop info;

    fp = fopen(img->filename, "rb");

    png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    info = png_create_info_struct(png);
    if(!info) abort();

    if(setjmp(png_jmpbuf(png))) abort();

    png_init_io(png, fp);

    png_read_info(png, info);

    width      = png_get_image_width(png, info);
    height     = png_get_image_height(png, info);
    color_type = png_get_color_type(png, info);
    bit_depth  = png_get_bit_depth(png, info);

    /* Read any color_type into 8bit depth, RGBA format. */
    /* See http://www.libpng.org/pub/png/libpng-manual.txt */

    if(bit_depth == 16)
    png_set_strip_16(png);

    if(color_type == PNG_COLOR_TYPE_PALETTE)
    png_set_palette_to_rgb(png);

    /* PNG_COLOR_TYPE_GRAY_ALPHA is always 8 or 16bit depth. */
    if(color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
    png_set_expand_gray_1_2_4_to_8(png);

    if(png_get_valid(png, info, PNG_INFO_tRNS))
    png_set_tRNS_to_alpha(png);

    /* These color_type don't have an alpha channel then fill it with 0xff. */
    if(color_type == PNG_COLOR_TYPE_RGB ||
     color_type == PNG_COLOR_TYPE_GRAY ||
     color_type == PNG_COLOR_TYPE_PALETTE)
    png_set_filler(png, 0xFF, PNG_FILLER_AFTER);

    if(color_type == PNG_COLOR_TYPE_GRAY ||
     color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
    png_set_gray_to_rgb(png);

    png_read_update_info(png, info);

    row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * height);
    
    for(y = 0; y < height; y++) {
        row_pointers[y] = (png_byte*)malloc(png_get_rowbytes(png,info));
    }
    png_read_image(png, row_pointers);

    fclose(fp);

    img->w = width;
    img->h = height;

    data = malloc(img->w * img->h * 4 *sizeof(float));
    if (DEBUG) {
        printf("Lendo %s \t", img->filename);
        printf("W: %d\tH: %d\tD: %d\n", img->w, img->h , 4);
    }
    for(y = 0; y < height; y++) {
        png_bytep row = row_pointers[y];
        for(x = 0; x < width * 4; x++) {
            data[location++] = (float) row[x]/255.0;
        }
    }

    glGenTextures(1, &(img->texture));
    glBindTexture(GL_TEXTURE_2D, img->texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img->w, img->h, 0, GL_RGBA, GL_FLOAT, data);

    free (data);
    png_destroy_read_struct(&png, &info, NULL);
}

void image_set_texture (Image img) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D, img->texture);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}
