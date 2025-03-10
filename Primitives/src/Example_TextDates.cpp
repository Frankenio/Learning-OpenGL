#include <GL/freeglut.h> // Librería para gráficos con OpenGL
#include <iostream>      // Para entrada y salida de datos
#include <string>        // Manejo de cadenas para simular cajas de texto

// Variables para almacenar los puntos iniciales y finales
int x0 = 50, yStart = 50, xEnd = 400, yEnd = 300;
bool drawing = false; // Bandera para saber si se debe dibujar la línea

// Variables para simular la entrada de texto
std::string inputText = "";
int inputIndex = 0;
bool inputActive = false;

// Función para dibujar un píxel en la pantalla
void setPixel(int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}
inline int round(float a)
{
    return static_cast<int>(a + 0.5);
}

// Algoritmo DDA para dibujar una línea
void lineDDA(int x0, int yStart, int xEnd, int yEnd)
{
    glColor3f(1.0, 0.0, 0.0); // Color rojo para la línea
    int dx = xEnd - x0, dy = yEnd - yStart;
    int steps = (abs(dx) > abs(dy)) ? abs(dx) : abs(dy);
    float xIncrement = (float)dx / steps;
    float yIncrement = (float)dy / steps;
    float x = x0, y = yStart;

    for (int k = 0; k < steps; k++)
    {
        x += xIncrement;
        y += yIncrement;
        setPixel(round(x), round(y));
    }
}

// Función para mostrar texto en la pantalla
void renderText(float x, float y, std::string text)
{
    glRasterPos2f(x, y);
    for (char c : text)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
}

// Función que maneja la visualización en la ventana
void display()
{
    glClear(GL_COLOR_BUFFER_BIT); // Limpiar pantalla
    glColor3f(0.0, 0.0, 0.0);     // Color negro para el texto

    // Dibujar las etiquetas de los campos de entrada
    renderText(50, 470, "X0:");
    renderText(150, 470, "Y0:");
    renderText(250, 470, "XEnd:");
    renderText(350, 470, "YEnd:");

    // Mostrar valores actuales de entrada
    renderText(80, 470, std::to_string(x0));
    renderText(180, 470, std::to_string(yStart));
    renderText(300, 470, std::to_string(xEnd));
    renderText(400, 470, std::to_string(yEnd));

    // Dibujar botón
    glColor3f(0.0, 0.0, 1.0); // Azul para el botón
    glBegin(GL_QUADS);
    glVertex2f(200, 30);
    glVertex2f(300, 30);
    glVertex2f(300, 70);
    glVertex2f(200, 70);
    glEnd();

    glColor3f(1.0, 1.0, 1.0); // Texto blanco dentro del botón
    renderText(220, 50, "Dibujar");

    // Dibujar la línea si se activó
    if (drawing)
    {
        lineDDA(x0, yStart, xEnd, yEnd);
    }

    glFlush();
}

// Función para manejar clics del mouse
void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        // Convertir coordenadas de pantalla a coordenadas OpenGL
        y = 500 - y; // OpenGL tiene origen en la esquina inferior izquierda

        // Verificar si el clic está en el botón
        if (x >= 200 && x <= 300 && y >= 30 && y <= 70)
        {
            drawing = true;
            glutPostRedisplay(); // Volver a dibujar la ventana
        }
    }
}

// Función para manejar la entrada del teclado
void keyboard(unsigned char key, int x, int y)
{
    if (key == 13)
    { // Enter para cambiar al siguiente campo
        inputIndex++;
        if (inputIndex > 3)
            inputIndex = 0;
    }
    else if (isdigit(key))
    { // Solo aceptar números
        inputText += key;
    }
    else if (key == 8 && !inputText.empty())
    { // Borrar con Backspace
        inputText.pop_back();
    }

    if (key == 13 && !inputText.empty())
    {
        int value = std::stoi(inputText);
        if (inputIndex == 0)
            x0 = value;
        else if (inputIndex == 1)
            yStart = value;
        else if (inputIndex == 2)
            xEnd = value;
        else if (inputIndex == 3)
            yEnd = value;

        inputText = ""; // Limpiar el buffer de entrada
    }

    glutPostRedisplay();
}

// Configuración inicial de la ventana
void init()
{
    glClearColor(1.0, 1.0, 1.0, 1.0); // Fondo blanco
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);
}

// Función principal
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Dibujar Linea con Entrada de Datos");

    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
