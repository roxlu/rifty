/*

  RoomDrawer
  --------------------
  Uses the `Room` model to draw something to screen :) 

 */

#ifndef ROOM_DRAWER_H
#define ROOM_DRAWER_H

#include <GLFW/glfw3.h>
#include "Vertices.h"
#include "Types.h"
#include <room/RGBShift.h>

class Room;

static const char* ROOM_VS = ""
  "#version 150\n"
  "uniform mat4 u_pm;"
  "uniform mat4 u_vm;"
  "uniform mat4 u_mm;"
  "uniform mat3 u_nm;"
  "in vec4 a_pos;"
  "in vec3 a_norm;"
  "out vec3 v_norm;"
  "void main() {"
  "  gl_Position = u_pm * u_vm * u_mm * a_pos;"
  "  v_norm = u_nm * mat3(u_mm) * a_norm;"
  "}"
  "";

static const char* ROOM_FS = ""
  "#version 150\n"
  "out vec4 fragcolor;"
  "in vec3 v_norm;"
  "void main() {"
  "  fragcolor = vec4(0.0, 0.0, 0.6, 1.0);"
#if 1
  "  vec3 norm = v_norm * 0.5 + 0.5;"
  "  fragcolor.rgb = norm; " 
#endif
#if 1
  "  float v = (norm.r + norm.g + norm.b) * 1.0/3.0;"
  "  fragcolor.rgb = vec3(v);"
  //  "  fragcolor.rgb = vec3(v, 0.0, 0.0); " 

#endif
  "  fragcolor.a = 1.0;"
  "}"
  "";

static const char* ROOM_LINE_FS = ""
  "#version 150\n"
  "out vec4 fragcolor;"
  "void main() { "
  "  fragcolor = vec4(0.2);"
  "}"
  "";

class RoomDrawer {
 public:
  RoomDrawer(Room& room);
  ~RoomDrawer();
  bool setup();
  void update();
  void draw(float* pm, float* vm, float* nm, float* mm); /* pm = projection matrix, vm = view matrix, mm = model matrix, nm = normal matrix */
 private:
  bool createShader();
 private:
  Room& room;
  GLuint vbo;
  GLuint vao;
  GLuint prog;
  GLuint vert;
  GLuint frag;
  GLuint frag_line;
  GLuint prog_line;
  GLint u_pm; /* projection matrix */
  GLint u_vm; /* view matrix */
  GLint u_mm; /* model matrix */
  GLint u_nm; /* normal matrix */
  RGBShift rgb_shift;
};

#endif
