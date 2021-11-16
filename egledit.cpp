#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "config.h"

static const char* common_shader_header = common_shader_header_gles3;
static const char* vertex_shader_body = vertex_shader_body_gles3;
static const char* fragment_shader_header = fragment_shader_header_gles3;
static const char* fragment_shader_footer = fragment_shader_footer_gles3;


static GLFWwindow *window;


static GLuint shader_program;
static GLint attrib_position;
static GLint sampler_channel[4];
static GLint uniform_cres;
static GLint uniform_ctime;
static GLint uniform_date;
static GLint uniform_gtime;
static GLint uniform_time;
static GLint uniform_mouse;
static GLint uniform_res;
static GLint uniform_srate;
static GLfloat viewportSizeX = 0.0;
static GLfloat viewportSizeY = 0.0;
static GLfloat mouseX = 0.0;
static GLfloat mouseY = 0.0;
static GLfloat mouseLPressed = 0.0;
static GLfloat mouseRPressed = 0.0;
static int mouseUpdating = 0;
static int maximized = 0;

static void select_gles3() {
    common_shader_header = common_shader_header_gles3;
    vertex_shader_body = vertex_shader_body_gles3;
    fragment_shader_header = fragment_shader_header_gles3;
    fragment_shader_footer = fragment_shader_footer_gles3;
}

static GLuint compile_shader(GLenum type, GLsizei nsources, const char **sources){
    GLuint shader;
    GLint success, len;
    GLsizei i, srclens[nsources];
    char *log;
    for (i = 0; i < nsources; ++i)
        srclens[i] = (GLsizei)strlen(sources[i]);
    shader = glCreateShader(type);
    glShaderSource(shader, nsources, sources, srclens);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
          printf("Error compiling shader.\n");
    }
    return shader;
}


static void startup(int width, int height, int window_x, int window_y, bool fullscreen)
{
    GLuint vtx, frag;
    const char *sources[4];
    char* log;
    GLint success, len;
  
    if (!glfwInit())
        printf("Unable to initialize GLFW.\n");
   
  
    GLFWmonitor *monitor = NULL;
    if (fullscreen) {
     }

  
    if (!(window = glfwCreateWindow(width, height, "esshader", monitor, NULL))) {
        glfwTerminate();
        printf("Unable to create GLFW window.\n");
    }
  
    if (window_x >= 0 && window_y >= 0) {
        glfwSetWindowPos(window, window_x, window_y);
    }
  
  
    glfwMakeContextCurrent(window);
  
  
    sources[0] = common_shader_header;
    sources[1] = vertex_shader_body;
    vtx = compile_shader(GL_VERTEX_SHADER, 2, sources);
    sources[0] = common_shader_header;
    sources[1] = fragment_shader_header;
    sources[2] = default_fragment_shader;
    sources[3] = fragment_shader_footer;
    frag = compile_shader(GL_FRAGMENT_SHADER, 4, sources);
    shader_program = glCreateProgram();
    glAttachShader(shader_program, vtx);
    glAttachShader(shader_program, frag);
    glLinkProgram(shader_program);
    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    glDeleteShader(vtx);
    glDeleteShader(frag);
    glReleaseShaderCompiler();
    glUseProgram(shader_program);
    glValidateProgram(shader_program);
    attrib_position = glGetAttribLocation(shader_program, "iPosition");
    sampler_channel[0] = glGetUniformLocation(shader_program, "iChannel0");
    sampler_channel[1] = glGetUniformLocation(shader_program, "iChannel1");
    sampler_channel[2] = glGetUniformLocation(shader_program, "iChannel2");
    sampler_channel[3] = glGetUniformLocation(shader_program, "iChannel3");
    uniform_cres = glGetUniformLocation(shader_program, "iChannelResolution");
    uniform_ctime = glGetUniformLocation(shader_program, "iChannelTime");
    uniform_date = glGetUniformLocation(shader_program, "iDate");
    uniform_gtime = glGetUniformLocation(shader_program, "iGlobalTime");
    uniform_time = glGetUniformLocation(shader_program, "iTime");
    uniform_mouse = glGetUniformLocation(shader_program, "iMouse");
    uniform_res = glGetUniformLocation(shader_program, "iResolution");
    uniform_srate = glGetUniformLocation(shader_program, "iSampleRate");
}

static void render(float abstime){
    static const GLfloat vertices[] = {
        -1.0f, -1.0f,
        1.0f, -1.0f,
        -1.0f, 1.0f,
        1.0f, 1.0f,
    };

    if(uniform_gtime >= 0)
        glUniform1f(uniform_gtime, abstime);
    if(uniform_time >= 0)
        glUniform1f(uniform_time, abstime);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glEnableVertexAttribArray(attrib_position);
    glVertexAttribPointer(attrib_position, 2, GL_FLOAT, GL_FALSE, 0, vertices);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

static char* read_file_into_str(const char *filename) {
    long length = 0;
    char *result = NULL;
    FILE *file = fopen(filename, "r");
    if(file) {
        int status = fseek(file, 0, SEEK_END);
        if(status != 0) {
            fclose(file);
            return NULL;
        }
        length = ftell(file);
        status = fseek(file, 0, SEEK_SET);
        if(status != 0) {
            fclose(file);
            return NULL;
        }
        result = malloc((length+1) * sizeof(char));
        if(result) {
            size_t actual_length = fread(result, sizeof(char), length , file);
            result[actual_length++] = '\0';
        } 
        fclose(file);
        return result;
    }
    return NULL;
}

int main(int argc, char **argv){
    bool fullscreen = false;
    int window_width = 640;
    int window_height = 360;
    int window_x = -1;
    int window_y = -1;
    int temp_val = 0;
    const char* texture_files[4];
    for (int i=0; i<4; ++i) {
        texture_files[i] = NULL;
    }
    char *program_source = NULL;
    int selected_option = -1;
    int selected_index = 0;
    program_source = read_file_into_str(optarg);
    default_fragment_shader = program_source;
    select_gles3();
    startup(window_width, window_height, window_x, window_y, fullscreen);
  
    glfwSetTime(0.0);
    
    while (!glfwWindowShouldClose(window)) {
        render((float)glfwGetTime());
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    return 0;
}
