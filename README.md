# Relatório do Trabalho 1
### Introdução à Computação Gráfica 19/03/2018
   - Guilherme Vale Sarmento - 20160163479
   - Jó Sales de Medeiros Júnior - 20160132104
   - Samuel Gomes Bezerra Araújo - 20160163773

## Introdução

- O objetivo deste trabalho era a criação de funções que desenhem pixels na tela utilizando algoritmos de rasterização, estas funções sendo PutPixel, cujo objetivo é rasterizar um pixel, Drawline, cujo objetivo é rasterizar uma linha de pixels, e DrawTriangle, cujo objetivo é desenhar um triângulo. Nas funções PutPixel e DrawTriangle tem que haver uma interpolação linear de cores entre os pixels de cada ponta.
    Como os sistemas operacionais protegem a memória do acesso direto, foi dado um framework que simulasse tal acesso à memória de vídeo.

## Desenvolvimento

- Primeiro de tudo, foi criada uma classe Ponto, que contém as coordenadas X e Y do pixel na tela, e os seus valores RGBA, de modo que facilitasse a passagem de parâmetros para as funções, pois tira a necessidade de passar cada parâmetro individualmente.

```c++
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

```

- A função PutPixel foi feita tratando o array FBptr como uma simulação da memória gráfica, cada pixel ocupando 4 posições, cada posição contendo os valores de R, G, B e o Alfa, respectivamente. O trecho “4*p.x” serve para achar a posição equivalente a coordenada x do pixel na linha, enquanto o resto do trecho entre parênteses serve para achar a posição equivalente a coordenada y do pixel. Foi utilizada a classe ponto para passar os parâmetros mais facilmente para a função.

```c++
void PutPixel(ponto p) {
    FBptr[(4*p.x + 4*IMAGE_WIDTH*p.y) + 0] = p.r;
    FBptr[(4*p.x + 4*IMAGE_WIDTH*p.y) + 1] = p.g;
    FBptr[(4*p.x + 4*IMAGE_WIDTH*p.y) + 2] = p.b;
    FBptr[(4*p.x + 4*IMAGE_WIDTH*p.y) + 3] = p.a;
  }
```

- A função DrawLine utiliza como base o material dado em aula, utilizando o algoritmo de Bresenham. A função foi feita de maneira que os pontos recebidos eram analizados, e dependendo do quadrante que pertenciam, o algoritmo se alterava para aquele quadrante em sí, podendo assim desenhar uma reta de qualquer ponto para qualquer ponto, independente de direção.

```c++
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
```
![alt text](https://github.com/kaminarirn/I.C.G/blob/master/Prints/ExemploDrawLine.png)

- A função CalcCor é uma função auxiliar que foi criada no intuito de fazer a interpolação de cores na função DrawLine, ela usa uma equação que se comporta como uma média ponderada, para calcular a cor de acordo com a distância, fazendo uma cor ficar mais fraca a medida que se distancia do ponto inicial enquanto a outra fica mais forte a medida que se aproxima do ponto final.

```c++
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
```

- A função DrawTriangle utiliza a função DrawLine para desenhar linhas ligando 3 pontos dados, formando um triângulo.

```c++
void DrawTriangle(ponto p1, ponto p2, ponto p3) {
    DrawLine(p1,p2);
    DrawLine(p1,p3);
    DrawLine(p2,p3);
}
```
![alt text](https://github.com/kaminarirn/I.C.G/blob/master/Prints/ExemploDrawTriangle.png)

## Resultados e Desafios

- O algoritmo de Bresenham teve que ser adaptado, pois originalmente ele não funciona se os valores do ponto final forem menores que os valores do ponto inicial, para superar isso, o algoritmo se adapta, para dependendo de cada quadrante o ponto se encontrar, ele poder funcionar.
- É um algoritmo facilmente implementável, por usar apenas variáveis do tipo inteiro, dispensa uso de bibliotecas adicionais, ajudando no desempenho do programa, porém, houve a utilização da biblioteca math.h, para implementação da interpolação linear.

## Referências Bibliográficas

- http://www.univasf.edu.br/~jorge.cavalcanti/comput_graf04_prim_graficas2.pdf
- Material do professor sobre o algoritmo de Bresenham
