#include "main.h"
//-----------------------------------------------------------------------------
void MyGlDraw(void)
{
//*************************************************************************
// Chame aqui as funções do mygl.h
//*************************************************************************
    ponto p0(400,400,12,45,255,255);
    ponto p1(255,255,255,65,47,255);
    DrawLine(p0,p1);

    ponto p2(0,200,36,129,255,255);
    ponto p3(350,50,255,32,255,255);
    DrawTriangle(p1,p2,p3);
        //DrawLine(200,200,c1,350,50,c2);



    ponto p4(200,200,127,0,255,255);
    ponto p5(350,199,255,74,64,255);
    PutPixel(p4);
    PutPixel(p5);
    //DrawLine(200,200,c1,350,199,c2);

    ponto p6(200,200,0,38,255,255);
    ponto p7(201,50,255,10,25,255);
    DrawLine(p6,p7);
    //DrawLine(200,200,c1,201,50,c2);
    /*
    ponto p8(200,200,0,36,255,255);
    ponto p9(50,50,255,33,45,255);
    DrawLine(p8,p9);
    //DrawLine(200,200,c1,50,50,c2);

    ponto p00(200,200,0,65,255,255);
    ponto p01(50,199,255,136,15,255);
    DrawLine(p00,p01);
    //DrawLine(200,200,c1,50,199,c2);

    ponto p02(200,200,0,250,255,255);
    ponto p03(199,50,255,23,47,255);
    DrawLine(p02,p03);
    //DrawLine(200,200,c1,199,50,c2);

    ponto p04(200,200,0,75,255,255);
    ponto p05(50,350,255,25,168,255);
    DrawLine(p04,p05);
    //DrawLine(200,200,c1,50,350,c2);

    ponto p06(200,200,0,45,255,255);
    ponto p07(50,201,255,69,41,255);
    DrawLine(p06,p07);
    //DrawLine(200,200,c1,50,201,c2);

    ponto p08(200,200,0,78,255,255);
    ponto p09(199,350,255,33,10,255);
    DrawLine(p08,p09);
    //DrawLine(200,200,c1,199,350,c2);

    /*ponto p000(200,200,0,95,255,255);
    ponto p001(350,350,255,0,0,255);
    DrawLine(p000,p001);
    //DrawLine(200,200,c1,350,350,c2);

    ponto p002(200,200,0,69,255,255);
    ponto p003(350,201,255,0,0,255);
    DrawLine(p002,p003);
    //DrawLine(200,200,c1,350,201,c2);

    ponto p004(200,200,0,80,255,255);
    ponto p005(201,350,255,0,0,255);
    DrawLine(p004,p005);
    //DrawLine(200,200,c1,201,350,c2);

    ponto p006(200,200,0,63,255,255);
    ponto p007(0,460,255,0,75,255);
    DrawLine(p006,p007);
    //DrawLine(0,0,c1,0,460,c2);


    ponto p008(200,200,0,13,255,255);
    ponto p009(255,255,255,0,69,255);
    DrawLine(p008,p009);
    //DrawLine(0,460,c1,255,255,c2

    */
};


//-----------------------------------------------------------------------------
//AQUI É O MAIN
int main(int argc, char **argv)
{
	//Inicializações.
	InitOpenGL(&argc, argv);
	InitCallBacks();
	InitDataStructures();


	// Ajusta a função que chama as funções do mygl.h
	DrawFunc = MyGlDraw;

	// Framebuffer scan loop.
	glutMainLoop();

	return 0;
}
