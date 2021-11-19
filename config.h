/* See LICENSE file for copyright and license details. */

/*
 * Configuration attributes for EGL context. See eglChooseConfig.
*/
#include <getopt.h>
static const char options_string[] = "?fw:h:s:l0:1:2:3:x:y:k:";
static struct option long_options[] = {
    {"source", required_argument, 0, 's'},
    {"texture0", required_argument, 0, '0'},
    {"texture1", required_argument, 0, '1'},
    {"texture2", required_argument, 0, '2'},
    {"texture3", required_argument, 0, '3'},
    {0, 0, 0, 0}
};
// OpenGL ES 3.0 / GLSL 300 es
static const char common_shader_header_gles3[] =
    "#version 300 es \n"
    "precision highp float; \n";
static const char vertex_shader_body_gles3[] =
    "layout(location = 0) in vec4 iPosition;"
    "void main() {"
    "gl_Position=iPosition;"
    "} \n";
static const char fragment_shader_header_gles3[] =
    "uniform vec3 iResolution;"
    "uniform float iGlobalTime;" // legacy
    "uniform float iTime;"
    "uniform float iChannelTime[4];"
    "uniform vec4 iMouse;"
    "uniform vec4 iDate;"
    "uniform vec3 iChannelResolution[4];"
    "uniform sampler2D iChannel0;"
    "uniform sampler2D iChannel1;"
    "uniform sampler2D iChannel2;"
    "uniform sampler2D iChannel3;"
    "out vec4 fragColor; \n";
static const char fragment_shader_footer_gles3[] =
    "\n void main(){mainImage(fragColor, gl_FragCoord.xy);} \n";
/*
 * Standard ShaderToy Shader
 * https://www.shadertoy.com/new#
*/
static char *default_fragment_shader[] =
    "\n void mainImage( out vec4 fragColor, in vec2 fragCoord )"
    "{"
    "vec2 uv = fragCoord/iResolution.xy;"
    "vec3 col = 0.5 + 0.5*cos(iTime+uv.xyx+vec3(0,2,4));"
    "fragColor = vec4(col,1.0);"
    "} \n";
