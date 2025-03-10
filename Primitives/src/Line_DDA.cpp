#include <GL/freeglut.h> // Librería para manejar gráficos con OpenGL
#include <cmath>         // Librería para operaciones matemáticas como fabs()
#include <cstdlib>       // Librería estándar para funciones auxiliares

// Función inline para redondear valores flotantes a enteros
inline int roundFloat(float a)
{
    return static_cast<int>(a + 0.5);
}

// Función para dibujar un píxel en la pantalla
void setPixel(int x, int y)
{
    glBegin(GL_POINTS); // Iniciar el modo de dibujo de puntos
    glVertex2i(x, y);   // Definir la posición del punto en coordenadas enteras
    glEnd();            // Finalizar la operación de dibujo
    glFlush();          // Asegurar que el punto se dibuje inmediatamente
}

// Algoritmo DDA (Digital Differential Analyzer) para dibujar una línea entre (x0, y0) y (xEnd, yEnd)
void lineDDA(int x0, int y0, int xEnd, int yEnd)
{
    // Calcular la diferencia entre los puntos
    const int dx = xEnd - x0;
    const int dy = yEnd - y0;

    // Determinar el número de pasos basado en la mayor distancia (horizontal o vertical)
    const int steps = (std::abs(dx) > std::abs(dy)) ? std::abs(dx) : std::abs(dy);

    // Calcular los incrementos en x e y para cada paso
    const float xIncrement = static_cast<float>(dx) / steps;
    const float yIncrement = static_cast<float>(dy) / steps;

    // Variables de posición inicial
    float x = x0, y = y0;

    // Dibujar el primer punto
    setPixel(roundFloat(x), roundFloat(y));

    // Iterar para calcular y dibujar cada punto de la línea
    for (int k = 0; k < steps; k++)
    {
        x += xIncrement;
        y += yIncrement;
        setPixel(roundFloat(x), roundFloat(y)); // Dibujar el siguiente punto
    }
}

// Función de renderizado: se ejecuta cuando OpenGL necesita redibujar la ventana
void display()
{
    glClear(GL_COLOR_BUFFER_BIT); // Limpiar el búfer de color (pantalla)
    glColor3f(1.0, 0.0, 0.0);     // Definir color blanco para la línea

    // Dibujar una línea desde (50, 50) hasta (400, 300) usando el algoritmo DDA
    lineDDA(50, 50, 400, 300);

    glFlush(); // Forzar el renderizado inmediato
}
// Configuración inicial de la ventana y el sistema de coordenadas
void init()
{
    glClearColor(1.0, 1.0, 1.0, 1.0); // Definir el color de fondo (negro)
    glMatrixMode(GL_PROJECTION);      // Seleccionar la matriz de proyección
    glLoadIdentity();                 // Restablecer la matriz de proyección
    gluOrtho2D(0, 500, 0, 500);       // Definir el sistema de coordenadas (0 a 500 en x e y)
}

// Función principal del programa
int main(int argc, char **argv)
{
    glutInit(&argc, argv);                       // Inicializar GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Definir el modo de visualización (buffer único, RGB)
    glutInitWindowSize(500, 500);                // Tamaño de la ventana (500x500 píxeles)
    glutInitWindowPosition(100, 100);            // Posición inicial de la ventana en la pantalla
    glutCreateWindow("Linea DDA con FreeGLUT");  // Crear la ventana con un título

    init();                   // Llamar a la función de inicialización
    glutDisplayFunc(display); // Definir la función de renderizado
    glutMainLoop();           // Iniciar el bucle de eventos de GLUT

    return 0; // Terminar el programa correctamente
}