#include <GL/freeglut.h> // Reemplazo de GL/glut.h

void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);   // Establece el color de fondo a blanco
    glMatrixMode(GL_PROJECTION);        // Configura la matriz de proyección
    gluOrtho2D(0.0, 200.0, 0.0, 150.0); // Configura un sistema de coordenadas 2D
}

void lineSegment(void)
{
    glClear(GL_COLOR_BUFFER_BIT); // Borra la pantalla con el color de fondo
    glColor3f(1.0, 0.0, 0.0);     // Establece el color a rojo

    glBegin(GL_LINES);
    glVertex2i(180, 15); // Punto inicial de la línea
    glVertex2i(10, 145); // Punto final de la línea
    glEnd();

    glFlush(); // Fuerza la ejecución inmediata de los comandos de OpenGL
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);                         // Inicializa GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);   // Usa buffer simple y modo RGB
    glutInitWindowPosition(50, 100);               // Posición inicial de la ventana
    glutInitWindowSize(400, 300);                  // Tamaño de la ventana
    glutCreateWindow("An Example OpenGL Program"); // Crea la ventana con título

    init();                       // Llama a la función de inicialización
    glutDisplayFunc(lineSegment); // Establece la función de dibujo
    glutMainLoop();               // Inicia el bucle principal de eventos de GLUT

    return 0; // Finaliza correctamente
}
