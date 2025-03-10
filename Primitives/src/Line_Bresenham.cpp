#include <GL/freeglut.h>
#include <cmath>
#include <cstdlib>

// Función para dibujar un píxel en la pantalla
void setPixel(int x, int y)
{
    glBegin(GL_POINTS); // Iniciar el modo de dibujo de puntos
    glVertex2i(x, y);   // Definir la posición del punto en coordenadas enteras
    glEnd();            // Finalizar la operación de dibujo
    glFlush();          // Asegurar que el punto se dibuje inmediatamente
}

// Algoritmo DDA (Digital Differential Analyzer) para dibujar una línea entre (x0, y0) y (xEnd, yEnd)

// Función de renderizado: se ejecuta cuando OpenGL necesita redibujar la ventana
void display()
{
    glClear(GL_COLOR_BUFFER_BIT); // Limpiar el búfer de color (pantalla)
    glColor3f(1.0, 0.0, 0.0);     // Definir color rojo para la línea

    // Dibujar un cuadrado usando lineas y usando el algoritmo Bresenham
    // lineBresenham(50, 50, 400, 300);

    glFlush(); // Forzar el renderizado inmediato
}

// Configuración inicial de la ventana y el sistema de coordenadas
void init()
{
    glClearColor(1.0, 1.0, 1.0, 1.0); // Definir el color de fondo (blanco)
    glMatrixMode(GL_PROJECTION);      // Seleccionar la matriz de proyección
    glLoadIdentity();                 // Restablecer la matriz de proyección
    gluOrtho2D(0, 500, 0, 500);       // Definir el sistema de coordenadas (0 a 500 en x e y)
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);                            // Inicializar GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);      // Definir el modo de visualización (buffer único, RGB)
    glutInitWindowSize(500, 500);                     // Tamaño de la ventana (500x500 píxeles)
    glutInitWindowPosition(100, 100);                 // Posición inicial de la ventana en la pantalla
    glutCreateWindow("Linea Bresenham con FreeGLUT"); // Crear la ventana con un título

    init();                   // Llamar a la función de inicialización
    glutDisplayFunc(display); // Definir la función de renderizado
    glutMainLoop();           // Iniciar el bucle de eventos de GLUT

    return 0; // Terminar el programa correctamente
}