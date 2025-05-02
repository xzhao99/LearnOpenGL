// be sure to include GLAD before GLFW.
// the include file for GLAD includes the required OpenGL header behand the scenes(like GL/gl.h)
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void processInput(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

// settings of window size
const int width = 1200;
const int height = 900;

// GLSL
const char* vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "void main()\n"
                                 "{\n"
                                 "  gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "}\0";
const char *fragmentShader1Source = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "  FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0);\n"
                                   "}\0";
const char* fragmentShader2Source = "#version 330 core\n"
                                    "out vec4 FragColor;\n"
                                    "void main()\n"
                                    "{\n"
                                    "  FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0);\n"
                                    "}\0";


int main() {
    
    // init glfw
    glfwInit();

    // configure GLFW using glfwWindowHint. make sure OpenGL ver >= 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#if __APPLE__      // on MacOSX
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    
    GLFWwindow* window = glfwCreateWindow(width, height, "LearnOpenGL", NULL, NULL);
    if (!window) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    // tell GLFW to make the context of our window the main context on the current thread
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


    // glad: load all OpenGL function pointers
    // init GLAD before we call any OpenGL function    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    // build and compile the shader program
    // -------------------------------------
    // vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // (shader, # of strings passing as source code, source code to be loaded to the shader, length)
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    const int buf_size = 512;
    GLint success;
    GLchar infoLog[buf_size];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, buf_size, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // fragment shader 1: Orange
    // -------------------------
    GLuint fragmentShaderOrange = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderOrange, 1, &fragmentShader1Source, NULL);
    glCompileShader(fragmentShaderOrange);
    // check for shader compile errors
    glGetShaderiv(fragmentShaderOrange, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShaderOrange, buf_size, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // link shaders 1
    GLuint shaderProgramOrange = glCreateProgram();
    glAttachShader(shaderProgramOrange, vertexShader);
    glAttachShader(shaderProgramOrange, fragmentShaderOrange);
    glLinkProgram(shaderProgramOrange);

    // check for linking errors of shader 1
    glGetProgramiv(shaderProgramOrange, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgramOrange, buf_size, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    // fragment shader 2: Yellow (no check error and infoLog)
    // -------------------------
    GLuint fragmentShaderYellow = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderYellow, 1, &fragmentShader2Source, NULL);
    glCompileShader(fragmentShaderYellow);
    // link shaders 2
    GLuint shaderProgramYellow = glCreateProgram();
    glAttachShader(shaderProgramYellow, vertexShader);
    glAttachShader(shaderProgramYellow, fragmentShaderYellow);
    glLinkProgram(shaderProgramYellow);

    // delete shaders after linking
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShaderOrange);
    glDeleteShader(fragmentShaderYellow);

    // set up vertex data(and buffers) and configure vertex attributes
    // 4 vertices + 2 triangles
    // ---------------------------------------------------------------
    float vertices4[] = {
        0.5f,  0.5f,  0.0f, // top right
        0.5f,  -0.5f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, // bottom left
        -0.5f, 0.5f,  0.0f  // top left 
    }; 
    unsigned int indices4[] = {  // note that we start from 0!
        0, 1, 3, // first Triangle
        1, 2, 3  // second Triangle
    };

    // a total of 6 vertices representing 2 triangles;
    float vertices6[] = {
        // first triangle
        -0.9f, -0.5f, 0.0f, // left
        -0.0f, -0.5f, 0.0f, // right
        -0.45f, 0.5f, 0.0f, // top
                            // second triangle
        0.0f, -0.5f, 0.0f,  // left
        0.9f, -0.5f, 0.0f,  // right
        0.45f, 0.7f, 0.0f   // top
    }; 


    // Vertex Buffer Object and Vertex Array Object, Element Buffer Object.
    // a VAO that stores our vertex attribute configuration and which VBO to use.
    GLuint VBO[2], VAO[2], EBO;
    glGenVertexArrays(2, VAO);
    glGenBuffers(2, VBO);
    glGenBuffers(1, &EBO);
    //std::cout << "===>Test: VAO = " << VAO << ", VBO = " << VBO << ", EBO = " << EBO << std::endl;
    // output: ===>Test: VAO = 1, VBO = 1, EBO = 2

    // bind the 1st group of triangles
    // --------------------------------
    glBindVertexArray(VAO[0]);
    // bind Vertex Buffer data
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices4), vertices4, GL_STATIC_DRAW);
    // bind Element Buffer data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices4), indices4, GL_STATIC_DRAW);

    const GLint index = 0, ver_size = 3;
    GLboolean normalized = GL_FALSE;
    glVertexAttribPointer(index, ver_size, GL_FLOAT, normalized, 3 * sizeof(float), (GLvoid*)0);
    glEnableVertexAttribArray(index);


    // bind the 2nd group of triangles
    // --------------------------------
    glBindVertexArray(VAO[1]);
    // bind Vertex Buffer data
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices6), vertices6, GL_STATIC_DRAW);
    //  bind Element Buffer data
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices4), indices4, GL_STATIC_DRAW);

    // the same
    glVertexAttribPointer(index, ver_size, GL_FLOAT, normalized, 3 * sizeof(float), (GLvoid*)0);
    glEnableVertexAttribArray(index);


    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex
    // attribute's bound vertex buffer object so afterwards we can safely unbind
    //glBindBuffer(GL_ARRAY_BUFFER, 0);

    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS
    // stored in the VAO; keep the EBO bound.
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but
    // this rarely happens. Modifying other VAOs requires a call to glBindVertexArray anyways so we
    // generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    //glBindVertexArray(0);


    // this call to draw in wireframe polygons
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


    // tell OpenGL the size of the rendering window
    glViewport(0, 0, width, height);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window)) {

        // input
        processInput(window);

        // render : rgb + alpha(opacity)
        glClearColor(0.2f, 0.6f, 0.3f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw 1st group of triangles: draw elemets(using shader 1)
        glUseProgram(shaderProgramOrange);
        glBindVertexArray(VAO[0]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
        // draw 2nd group of triangles: draw vertices array(using shader 2)
        glUseProgram(shaderProgramYellow);
        glBindVertexArray(VAO[1]);
        glDrawArrays(GL_TRIANGLES, 0, 6); // first, count(for vertices6)
        //glBindVertexArray(0);   // no need to unbind it every time


        // glfw: swap buffers and poll IO events(keys pressed/released, mouse move etc.)
        // -----------------------------------------------------------------------------
        // swap the color buffer that is used to render
        glfwSwapBuffers(window);
        // check if any events are triggered, updates the window state,
        // and call corresponding functions.
        glfwPollEvents();
    }

#if 1    // optional: deallocate all resources
    glDeleteVertexArrays(2, VAO);
    glDeleteBuffers(2, VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgramOrange);
    glDeleteProgram(shaderProgramYellow);
#endif

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react
// accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}