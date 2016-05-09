/* Baseado em 
http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-11-2d-text/
https://github.com/olikraus/u8glib/wiki/fontsize
*/
void initText2D (char * texturePath) {
    Font font;
    FILE *infofile;
    char * img;
    int id, i;

    infofile = fopen(texturePath, "rb");
    fscanf(infofile, "%s", img);
    font = malloc (sizeof (struct font));
    font->img = image_create (img);
    image_load (font->img);

    for (i = 0; i < 256; ++i) {
        font->x[i] = 0;
        font->y[i] = 0;
        font->height[i] = 0;
        font->width[i] = 0;
    }
    while (fscanf(infofile, "char id=%d", &id) == 1) {
        fscanf(infofile, " x=%d y=%d", &font->x[id], &font->y[id]);
        fscanf(infofile, " width=%d", &font->width[id]);
        fscanf(infofile, " height=%d", &font->height[id]);
        fscanf(infofile, " xoffset=%*d yoffset=%*d xadvance=%*d");
    }
}

void printText2D (char * text, double x, double y, double h) {

}

void printletter (Font f, char l, double x, double y, double h) {
    if (f->height[(int)l] != 0 && f->width[(int)l] != 0) {
        glPushMatrix();
        glTranslatef (x, y, 0.0);
        glRotatef(angle, 0, 0, 1);
        glEnable(GL_TEXTURE_2D);
        image_set_texture (f->img);
        glBegin(GL_POLYGON);
        glTexCoord2f(0.0, 1.0); glVertex2f(-zoom*img_radio, -zoom);
        glTexCoord2f(1.0, 1.0); glVertex2f(zoom*img_radio, -zoom);
        glTexCoord2f(1.0, 0.0); glVertex2f(zoom*img_radio, zoom);
        glTexCoord2f(0.0, 0.0); glVertex2f(-zoom*img_radio, zoom);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    
        glFlush();
        glPopMatrix();

    }

}
