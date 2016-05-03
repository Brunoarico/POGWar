#include "image.h"

void image_delete (Image img) {
    free (img);
}

Image image_read (char *filename) {

    FILE *fd;
    Image img;
    float *data;

    int depth, i;
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;
    JSAMPROW row_pointer[1];
    unsigned long location = 0;

    fd = fopen(filename, "rb");
    img = malloc (sizeof (struct image));

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);
    jpeg_stdio_src(&cinfo, fd);
    jpeg_read_header(&cinfo, 0);
    cinfo.scale_num = 1;
    cinfo.scale_denom = 1;
    jpeg_start_decompress(&cinfo);
    img->w = cinfo.output_width;
    img->h = cinfo.output_height;
    depth = cinfo.num_components; 
    data = malloc(img->w * img->h * depth *sizeof(float));
    row_pointer[0] = malloc(img->w * depth *sizeof(JSAMPLE));
    /* read one scan line at a time */
    printf("Lendo %s \tW: %d\tH: %d\tD: %d\n", filename, img->w, img->h , depth);
    while( cinfo.output_scanline < cinfo.output_height ) {
        jpeg_read_scanlines( &cinfo, row_pointer, 1 );
        for(i = 0; i < (img->w * depth); i++) {
            data[location++] = (float) row_pointer[0][i]/255.0;
        }
    }
    free(row_pointer[0]);
    fclose(fd);
    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);


    glGenTextures(1, &(img->texture));
    glBindTexture(GL_TEXTURE_2D, img->texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img->w, img->h, 0, GL_RGB, GL_FLOAT, data);

    free (data);
    return img;
}
