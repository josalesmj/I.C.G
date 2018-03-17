#ifndef _MYGL_H_
#define _MYGL_H_

#include "definitions.h"
#include <math.h>

//*****************************************************************************
// Defina aqui as suas funções gráficas
//*****************************************************************************
class ponto {
public:
  int r,g,b,a;
  int x;
  int y;
  ponto(){}
  ponto(int x,int y,int r,int g,int b,int a) {
  this->x=x;
  this->y=y;
  this->r = r;
  this->g = g;
  this->b = b;
  this->a = a;
  }
};

ponto calcCor(int x, int y, ponto p1, ponto p2) {
    ponto c;
    float distP = sqrt(pow(x-p2.x,2) + pow(y-p2.y,2));
    float distT = sqrt(pow(p1.x-p2.x,2) + pow(p1.y-p2.y,2));
    float p = (distP/distT);
    c.x = x;
    c.y = y;
    c.r = p*p1.r + (1.0 - p)*p2.r;
    c.g = p*p1.g + (1.0 - p)*p2.g;
    c.b = p*p1.b + (1.0 - p)*p2.b;
    c.a = p*p1.a + (1.0 - p)*p2.a;
    return c;
}

void PutPixel(ponto p) {
    FBptr[(4*p.x + 4*IMAGE_WIDTH*p.y) + 0] = p.r;
    FBptr[(4*p.x + 4*IMAGE_WIDTH*p.y) + 1] = p.g;
    FBptr[(4*p.x + 4*IMAGE_WIDTH*p.y) + 2] = p.b;
    FBptr[(4*p.x + 4*IMAGE_WIDTH*p.y) + 3] = p.a;
  }

void DrawLine(ponto p1,ponto p2) {
    int x0=p1.x;
    int y0=p1.y;
    int x = x0;//recebe o x do ponto inicial
    int y = y0;//recebe o y do ponto inicial
    int x1 = p2.x;//recebe o x do ponto final
    int y1 = p2.y;//recebe o y do ponto final

//1 quadrante
    if(x1>=x0 && y1<=y0) {
      if(x0!=x1 && y0!=y1) {
        int dx = x1 - x0;
        int dy = y1 - y0;//sempre será negativo ou zero
        PutPixel(calcCor(x,y,p1,p2));
        if(dx>=(-1*dy)) {
          int p = - 2*dy-dx;
          while(x<x1) {
            if(p < 0) {
              x++;
              p = p - 2*dy;
            }
            else {
              x++;
              y--;
              p = (p - 2*dy) - (2*dx);
            }
            PutPixel(calcCor(x,y,p1,p2));
          }
        }
        else {
          int p = -1*dy + 2*dx;
          while(y>y1) {
            if(p > 0) {
              y--;
              p = p - 2*dx;
            }
            else {
              x++;
              y--;
              p = (p - 2*dy) - (2*dx);
            }
            PutPixel(calcCor(x,y,p1,p2));
          }
        }
      }
      else if(x0==x1) {
        while(y>=y1) {
          PutPixel(calcCor(x,y,p1,p2));
          y--;
        }
      }
      else if(y0==y1) {
        while(x<=x1) {
          PutPixel(calcCor(x,y,p1,p2));
          x++;
        }
      }
    }
// 2 quadrante
    if(x1<=x0 && y1<=y0) {
      if(x0!=x1 && y0!=y1) {
        int dx = x1 - x0;//negativo
        int dy = y1 - y0;//nevativo
        PutPixel(calcCor(x,y,p1,p2));
        if((-1*dx)>=(-1*dy)) {
          int p = -2*dy+dx;
          while(x>x1) {
            if(p < 0) {
              x--;
              p = p - 2*dy;
            }
            else {
              x--;
              y--;
              p = (p - 2*dy) + (2*dx);
            }
            PutPixel(calcCor(x,y,p1,p2));
          }
        }
        else {
          int p = (-1*dy)+2*dx;
          while(y>y1) {
            if(p > 0) {
              y--;
              p = p + 2*dx;
            }
            else {
              x--;
              y--;
              p = (p - 2*dy) + (2*dx);
            }
            PutPixel(calcCor(x,y,p1,p2));
          }
        }
      }
      else if(x0==x1){
        while(y>=y1) {
          PutPixel(calcCor(x,y,p1,p2));
          y--;
        }
      }
      else if(y0==y1) {
        while(x>=x1) {
          PutPixel(calcCor(x,y,p1,p2));
          x--;
        }
      }
    }
//3 quadrante
    if(x1<=x && y1>=y) {
      if(x!=x1 && y!=y1) {
        int dx = x1 - x;//sempre será negativo ou zero
        int dy = y1 - y;
        PutPixel(calcCor(x,y,p1,p2));
        if((-1*dx)>=dy) {
          int p = 2*dy+dx;
          while(x>x1) {
            if (p < 0) {
              x--;
              p = p + 2*dy;
            }
            else {
              x--;
              y++;
              p = (p + 2*dy) + (2*dx);
            }
            PutPixel(calcCor(x,y,p1,p2));
          }
        }
        else {
          int p = dy + 2*dx;
          while(y<y1) {
            if (p > 0) {
              y++;
              p = p + 2*dx;
            }
            else {
              x--;
              y++;
              p = (p + 2*dy) + (2*dx);
            }
            PutPixel(calcCor(x,y,p1,p2));
          }
        }
      }
      else if(x0==x1) {
        while(y<=y1) {
          PutPixel(calcCor(x,y,p1,p2));
          y++;
        }
      }
      else if(y0==y1) {
        while(x>=x1) {
          PutPixel(calcCor(x,y,p1,p2));
          x--;
        }
      }
    }
// 4 quadrante
    if(x0!=x1 && y0!=y1) {
      int dx = x1 - x;
      int dy = y1 - y;
      PutPixel(calcCor(x,y,p1,p2));
      if(dx>=dy) {
        int p = 2*dy-dx;
        while(x<x1) {
          if (p < 0) {
            x++;
            p = p + 2*dy;
          }
          else {
            x++;
            y++;
            p = (p + 2*dy) - (2*dx);
          }
          PutPixel(calcCor(x,y,p1,p2));
        }
      }
      else {
        int p = dy-2*dx;
        while(y<y1) {
          if (p > 0) {
            y++;
            p = p - 2*dx;
          }
          else {
            x++;
            y++;
            p = (p + 2*dy) - (2*dx);
          }
          PutPixel(calcCor(x,y,p1,p2));
        }
      }
    }
    else if(x0==x1) {
      while(y<=y1) {
        PutPixel(calcCor(x,y,p1,p2));
        y++;
      }
    }
    else if(y0==y1) {
      while(x<=x1) {
        PutPixel(calcCor(x,y,p1,p2));
        x++;
      }
    }
  }


void DrawTriangle(ponto p1, ponto p2, ponto p3) {
    DrawLine(p1,p2);
    DrawLine(p1,p3);
    DrawLine(p2,p3);
}

#endif // _MYGL_H_
