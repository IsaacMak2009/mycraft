#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <unistd.h>

#include "includes/shader.h"
#include "includes/camera.h"
#include "includes/texture.h"
#include "includes/blocks.h"

typedef glm::vec<3, int> vec3_int;

mycraft::camera::Camera camera(glm::vec3(0.0f, 1.0f, 0.0f));
GLfloat deltaTime = 0.025f;
GLfloat lastTime = 0;
GLuint nbFrames = 0;
GLfloat lastX, lastY;

glm::vec3 debug_block = glm::vec3(0.0f, 0.0f, 0.0f);

void keyboard_callback(GLFWwindow *window, GLint key, GLint scancode, GLint action, GLint mode);
void mouse_callback(GLFWwindow *window, GLdouble xpos, GLdouble ypos); // move
void mouse_button_callback(GLFWwindow *window, GLint button, GLint action, GLint mods); // click
void do_movement(void);
void showFPS(GLFWwindow *pWindow);
glm::float32 dotline(glm::vec3 p, glm::vec3 a, glm::vec3 b);

bool firstMouse = true;
bool keypressed[1024];

std::vector<vec3_int> blocks;

using std::cout;
using std::endl;

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow *window = glfwCreateWindow(1024, 768, "mycraft", NULL, NULL);
    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, keyboard_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glewExperimental = GL_TRUE;
    glewInit();

    glEnable(GL_DEPTH_TEST);

    mycraft::Shader shaderProg("shaders/vs/block.vsh", "shaders/fs/block.fsh");

    GLfloat vertices[180];
    mycraft::blocks::generate_cube(vertices, mycraft::blocks::GRASS);
    cout << vertices[4] << endl;
    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // TexCoord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0); // Unbind VAO

    GLfloat stone_vertices[180];
    mycraft::blocks::generate_cube(stone_vertices, mycraft::blocks::COBBLESTONE);
    GLuint VBO2, VAO2;
    glGenVertexArrays(1, &VAO2);
    glGenBuffers(1, &VBO2);

    glBindVertexArray(VAO2);

    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(stone_vertices), stone_vertices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // TexCoord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0); // Unbind VAO


    mycraft::Texture texture("D:\\mycraft\\resources\\images\\block.png", GL_REPEAT, GL_NEAREST);
    glm::mat4 projection(1.0f);
    glm::mat4 view(1.0f);
    projection = glm::perspective(glm::radians(45.0f), 1024.0f / 768.0f, 0.1f, 100.0f);

    for (int i=0; i<10; i++) {
        for (int j=0; j<10; j++) {
            blocks.push_back(vec3_int(i-5, i+j, j-5));
        }
    }

    while (!glfwWindowShouldClose(window)) {

        int width, height;
        glfwGetWindowSize(window, &width, &height);
        glViewport(0, 0, width, height);

        glClearColor(0.57f, 0.73f, 0.85f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shaderProg.useProgram();

        glActiveTexture(GL_TEXTURE0);
        texture.bindTexture();
        glUniform1i(glGetUniformLocation(shaderProg.program, "texture"), 0);

        view = camera.GetViewMatrix();

        // send matrices to shader
        glUniformMatrix4fv(glGetUniformLocation(shaderProg.program, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(shaderProg.program, "proj"), 1, GL_FALSE, glm::value_ptr(projection));

        // bind VAO
        glBindVertexArray(VAO2);
        {
            glm::mat4 model(1.0f);
            model = glm::translate(model, debug_block);
            glUniformMatrix4fv(glGetUniformLocation(shaderProg.program, "model"), 1, GL_FALSE, glm::value_ptr(model));
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        glBindVertexArray(VAO);
        for (vec3_int v : blocks) {
            glm::mat4 model(1.0f);
            model = glm::translate(model, glm::vec3(v));
            glUniformMatrix4fv(glGetUniformLocation(shaderProg.program, "model"), 1, GL_FALSE, glm::value_ptr(model));
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        glBindVertexArray(0);

        glBindVertexArray(0);
        
        showFPS(window);

        do_movement();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void keyboard_callback(GLFWwindow *window, GLint key, GLint scancode, GLint action, GLint mode) {
    if (action == GLFW_PRESS) {
        keypressed[key] = GL_TRUE;
    } else if (action == GLFW_RELEASE) {
        keypressed[key] = GL_FALSE;
    }

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

void do_movement() {
    
    // move camera
    if (keypressed[GLFW_KEY_W]) { camera.ProcessKeyboard(mycraft::camera::FORWARD, deltaTime); }
    if (keypressed[GLFW_KEY_S]) { camera.ProcessKeyboard(mycraft::camera::BACKWARD, deltaTime); }
    if (keypressed[GLFW_KEY_A]) { camera.ProcessKeyboard(mycraft::camera::LEFT, deltaTime); }
    if (keypressed[GLFW_KEY_D]) { camera.ProcessKeyboard(mycraft::camera::RIGHT, deltaTime); }
    if (keypressed[GLFW_KEY_SPACE]) { camera.ProcessKeyboard(mycraft::camera::UP, deltaTime); }
    if (keypressed[GLFW_KEY_LEFT_CONTROL]) { camera.ProcessKeyboard(mycraft::camera::DOWN, deltaTime); }
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    GLfloat xoffset = xpos - lastX;
    GLfloat yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;
    camera.ProcessMouseMovement(xoffset, yoffset);
    glm::float32 min_D = FLT_MAX;
    int min_index = 0;
    for (int i=0; i<blocks.size(); i++) {
        float D = (dotline(blocks[i], camera.getPosition(), camera.Front) + 0.1) * glm::distance(glm::vec3(blocks[0]), camera.getPosition());
        if (D < min_D) {
            min_D = D;
            min_index = i;
        }
    }
    // get which face the block is pointing
    debug_block = blocks[min_index];
    //cout << debug_block.x << " " << debug_block.y << " " << debug_block.z << endl;
}

glm::float32 dotline(glm::vec3 p, glm::vec3 a, glm::vec3 b) {
    // dot: p
    // line: a+kb
    glm::float32 s = glm::length(glm::cross(b, p-a));
    return s / glm::length(b);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        // create a new block with pointing
        // find the nearest block
        glm::float32 min_D = FLT_MAX;
        int min_index = 0;
        for (int i=1; i<blocks.size(); i++) {
            float D = (dotline(blocks[i], camera.getPosition(), camera.Front) + 0.1) * glm::distance(glm::vec3(blocks[0]), camera.getPosition());
            if (D < min_D) {
                min_D = D;
                min_index = i;
            }
        }
        // check is it pointing a block
        if (glm::distance(glm::vec3(blocks[min_index]), camera.getPosition()) >= 6.0f) return;
        // get which face the block is pointing
        glm::vec3 block = blocks[min_index];
        // get faces middle point
        glm::vec3 faces[] = {
            camera.getPosition().x > block.x ? glm::vec3(block.x + 0.5f, block.y, block.z) : glm::vec3(block.x - 0.5f, block.y, block.z),
            camera.getPosition().y > block.y ? glm::vec3(block.x, block.y + 0.5f, block.z) : glm::vec3(block.x, block.y - 0.5f, block.z),
            camera.getPosition().z > block.z ? glm::vec3(block.x, block.y, block.z + 0.5f) : glm::vec3(block.x, block.y, block.z - 0.5f),
        };
        min_D = glm::distance(camera.getPosition() + camera.Front, faces[0]);
        min_index = 0;
        for (int i=1; i<3; i++) {
            float D = dotline(faces[i], camera.getPosition(), camera.Front) + glm::distance(camera.getPosition() + camera.Front, faces[i]);
            if (D < min_D) {
                min_D = D;
                min_index = i;
            }
        }
        // create new block
        cout << min_index << " " << block.x << " " << block.y << " " << block.z << endl;
        vec3_int new_block = faces[min_index] + faces[min_index] - glm::vec3(block);
        cout << new_block.x << " " << new_block.y << " " << new_block.z << endl;
        blocks.push_back(new_block);
        // cp.x + k*cf.x = X
        // k = (X - cp.x) / cf.x
    }
}

void showFPS(GLFWwindow *pWindow) {
    // Measure speed
     GLfloat currentTime = glfwGetTime();
     GLfloat delta = currentTime - lastTime;
     nbFrames++;
     usleep(10000);
     if ( delta >= 1.0 ){ // If last cout was more than 1 sec ago;
        std::stringstream ss;
        int x = camera.getPosition().x;
        int y = camera.getPosition().y;
        int z = camera.getPosition().z;
        ss << "Mycraft - minecarft remake | FPS: " << nbFrames / delta << " | Pos: (" << x << ", " << y << ", " << z << ")";
        glfwSetWindowTitle(pWindow, ss.str().c_str());
        nbFrames = 0;
        lastTime = currentTime;
     }
}