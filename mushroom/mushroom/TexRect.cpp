#include "TexRect.h"

TexRect::TexRect (const char* filename, int rows, int cols, float x=0, float y=0, float w=0.5, float h=0.5)
{
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);
    
    RgbImage theTexMap( filename );
    
    glGenTextures( 1, &texture_id );
    glBindTexture( GL_TEXTURE_2D, texture_id );
    
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, theTexMap.GetNumCols(), theTexMap.GetNumRows(),
                      GL_RGB, GL_UNSIGNED_BYTE, theTexMap.ImageData() );
    this->texture_id = texture_id;
    
    r = rows;
    c = cols;
    
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    
    r1 = 1;
    c1 = 1;
    
    Done = false;
}

bool TexRect::ifExplode()
{
	return Exploded;
}

bool TexRect::ifDone()
{
	return Done;
}

void TexRect::draw()
{
    glBindTexture( GL_TEXTURE_2D, texture_id );
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    
    float x1, x2, y1, y2;

    y1 = 1 - (1.0 / r) * (r1 - 1);
	y2 = 1 - (1.0 / r) * r1;
    x1 = (1.0 / c) * (c1 - 1);
    x2 = (1.0 / c) * c1;
    
    
    glBegin(GL_QUADS);
    
    glTexCoord2f(x1, y2);
    glVertex2f(x, y - h);
    
    glTexCoord2f(x1, y1);
    glVertex2f(x, y);
    
    glTexCoord2f(x2, y1);
    glVertex2f(x+w, y);
    
    glTexCoord2f(x2, y2);
    glVertex2f(x+w, y - h);
    
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
}

void TexRect::animate()
{
    if (c1 < c){
        c1++;
    }
    else {
        if (r1 < r){
            r1++;
            c1 = 1;
        }
        else{
            r1 = 1;
            c1 = 1;
        }
    }
    
    if (r1 == r && c1 == c){
        Done = true;
    }
}

void TexRect::restart(const char* filename, int r, int c)
{
    Done = false;
    Exploded = false;

    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);
    
    RgbImage theTexMap(filename);
    
    glGenTextures( 1, &texture_id );
    glBindTexture( GL_TEXTURE_2D, texture_id );
    
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, theTexMap.GetNumCols(), theTexMap.GetNumRows(),
                      GL_RGB, GL_UNSIGNED_BYTE, theTexMap.ImageData() );
    this->texture_id = texture_id;
    
    this->r = r;
    this->c = c;

    r1 = 1;
    c1 = 1;

}

void TexRect::explode(const char* filename, int r, int c)
{
    Exploded = true;

    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);
    
    RgbImage theTexMap(filename);
    
    glGenTextures( 1, &texture_id );
    glBindTexture( GL_TEXTURE_2D, texture_id );
    
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, theTexMap.GetNumCols(), theTexMap.GetNumRows(),
                      GL_RGB, GL_UNSIGNED_BYTE, theTexMap.ImageData() );
    this->texture_id = texture_id;
    
    this->r = r;
    this->c = c;

    r1 = 1;
    c1 = 1;
}

bool TexRect::contains(float x, float y)
{

    if(x >= this->x && x <= this->x + w)
        if(y <= this->y && y >= this->y - h)
            return true;

    return false;

}
