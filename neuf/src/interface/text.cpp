#include "unites/unites.h"
#include "interface/interface.h"
#include "interface/text.h"
#include <iostream>
using namespace std;

Text font(const char* fontPath, float size, SDL_Color color, const char* content) {
    font = TTF_OpenFont(fontPath, size); // Initialise la font à la taille choisie
    text =  TTF_RenderText_Blended(font, content, color); // Initialise le texte
}

void displayText(float posX, float posY) {
    glPushMatrix();
       glEnable( GL_BLEND );
            glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

            glGenTextures(1,&texture);
            glBindTexture(GL_TEXTURE_2D,texture);

            gluBuild2DMipmaps(GL_TEXTURE_2D,4,text->w,text->h,GL_RGBA,GL_UNSIGNED_BYTE,text->pixels);

            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

            GLboolean textureIsEnabled = glIsEnabled(GL_TEXTURE_2D);

            glEnable(GL_TEXTURE_2D);
            glColor3ub(255,255,255);
            glBegin(GL_QUADS);
                glTexCoord2f(0,0);
                glVertex2f(posX,posY);
                glTexCoord2f(0,1);
                glVertex2f(posX,posY + text->h);
                glTexCoord2f(1,1);
                glVertex2f(posX + text->w,posY + text->h);
                glTexCoord2f(1,0);
                glVertex2f(posX + text->w,posY);
            glEnd();
        if(!textureIsEnabled) {
            glDisable(GL_TEXTURE_2D);
        }
    glPopMatrix();
}

void deleteText() {
    TTF_CloseFont(font);
    glDeleteTextures(1, &texture);
    SDL_FreeSurface(text);
}
