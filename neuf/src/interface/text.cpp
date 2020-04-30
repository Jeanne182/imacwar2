#include "unites/unites.h"

#include "interface/interface.h"
#include "interface/text.h"



//

#include <iostream>
using namespace std;

void font(Text* montexte,const char* fontPath, float size, SDL_Color color, const char* content) {
    TTF_Font *font = TTF_OpenFont("./../fonts/SummitAttack.ttf", size); // Initialise la font à la taille choisie
    //SDL_Surface *text =
    montexte->font = font;
    montexte->text = TTF_RenderText_Blended(font, content, color); // Initialise le texte;
    //cout <<"montexte->text->w :  "<<montexte->text->w<<endl; //c'est censé cout des 0

}
void displayText(float posX, float posY, Text* montexte) {
    glPushMatrix();
       glEnable( GL_BLEND );
            glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

            glGenTextures(1,&montexte->texture);
            glBindTexture(GL_TEXTURE_2D,montexte->texture);
            cout <<"montexte->text->pixels "<<montexte->text->pixels<<endl;
            /*gluBuild2DMipmaps(GL_TEXTURE_2D,4,montexte->text->w,montexte->text->h,GL_RGBA,GL_UNSIGNED_BYTE,montexte->text->pixels);

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
                glVertex2f(posX,posY + montexte->text->h);
                glTexCoord2f(1,1);
                glVertex2f(posX + montexte->text->w,posY + montexte->text->h);
                glTexCoord2f(1,0);
                glVertex2f(posX + montexte->text->w,posY);
            glEnd();
        if(!textureIsEnabled) {
            glDisable(GL_TEXTURE_2D);
        }
    glPopMatrix();*/
}

void deleteText(Text* text) {
    TTF_CloseFont(text->font);
    glDeleteTextures(1, &text->texture);
    SDL_FreeSurface(text->text);
}
