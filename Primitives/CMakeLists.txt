cmake_minimum_required(VERSION 3.10)

# Nombre del proyecto
project(Primitives)

# Buscar OpenGL y GLUT/FreeGLUT
find_package(OpenGL REQUIRED) 
find_package(GLUT REQUIRED)


# set(SRC_DIR src)
# add_executable(Window ${SRC_DIR}/Window.cpp)

# Especificar el directorio de salida de los ejecutables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Buscar todos los archivos en src/
file(GLOB MAIN_SOURCES "src/*.cpp")

# Iterar sobre cada archivo encontrado y generar un ejecutable
foreach(SOURCE_FILE ${MAIN_SOURCES})
    # Obtener solo el nombre del archivo sin la ruta
    get_filename_component(EXEC_NAME ${SOURCE_FILE} NAME_WE)

    # Crear el ejecutable con el mismo nombre que el archivo
    add_executable(${EXEC_NAME} ${SOURCE_FILE})

    # Enlazar OpenGL, GLUT y GLU
    target_link_libraries(${EXEC_NAME} OpenGL::GL GLUT::GLUT glu32)

    # Asegurar que el ejecutable se guarde en bin/
    set_target_properties(${EXEC_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
endforeach()



# target_link_libraries(Window OpenGL::GL GLUT::GLUT glu32)

# set_target_properties(Window PROPERTIES
#    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
# )