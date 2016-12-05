////////////////////////////////////////////////////////
//
// GEM - Graphics Environment for Multimedia
//
// zmoelnig@iem.kug.ac.at
//
// Implementation file
//
//    Copyright (c) 1997-1999 Mark Danks.
//    Copyright (c) Günther Geiger.
//    Copyright (c) 2001-2011 IOhannes m zmölnig. forum::für::umläute. IEM. zmoelnig@iem.at
//    For information on usage and redistribution, and for a DISCLAIMER OF ALL
//    WARRANTIES, see the file, "GEM.LICENSE.TERMS" in this distribution.
//
/////////////////////////////////////////////////////////

#include "alpha.h"

CPPEXTERN_NEW_WITH_ONE_ARG(alpha, t_floatarg, A_DEFFLOAT);

/////////////////////////////////////////////////////////
//
// alpha
//
/////////////////////////////////////////////////////////
// Constructor
//
/////////////////////////////////////////////////////////
alpha :: alpha(t_floatarg fun)
       : m_alphaState(1),
	 m_alphaTest(1),
	 m_depthtest(1),
   m_src_function(GL_SRC_ALPHA)
{
  funMess(static_cast<int>(fun));
  m_inlet =  inlet_new(this->x_obj, &this->x_obj->ob_pd, &s_float, gensym("function"));

  glBlendFunciFn = (glBlendFunciProc)glXGetProcAddress((const GLubyte*)"glBlendFunci");
  if (!glBlendFunci) {
    ::error("You need at least OpenGL 4.0 to use separable blending function.");
  }

  for (int i = 0; i<4; i++){
    m_src_fun_separate[i] = GL_SRC_ALPHA;
    m_dst_fun_separate[i] = GL_ONE_MINUS_SRC_ALPHA;
  }
}

/////////////////////////////////////////////////////////
// Destructor
//
/////////////////////////////////////////////////////////
alpha :: ~alpha()
{
  inlet_free(m_inlet);
}

/////////////////////////////////////////////////////////
// render
//
/////////////////////////////////////////////////////////
void alpha :: render(GemState *)
{
  if (m_alphaState)    {
    glEnable(GL_BLEND);
    glBlendFunc(m_src_function, m_function);
    glBlendFunci(0, m_src_function, m_function);
    if (!m_depthtest)
      glDepthMask(GL_FALSE);  // turn off depth test for transparent objects

    if (m_alphaTest)		{
      glEnable(GL_ALPHA_TEST);
      glAlphaFunc(GL_GREATER, 0.f);
    }
  }
}

/////////////////////////////////////////////////////////
// postrender
//
/////////////////////////////////////////////////////////
void alpha :: postrender(GemState *)
{
  if (m_alphaState)
    {
      glDisable(GL_BLEND);
      if (!m_depthtest)
	glDepthMask(GL_TRUE);

      if (m_alphaTest)
	glDisable(GL_ALPHA_TEST);
    }

}
/////////////////////////////////////////////////////////
// alphaMess
//
/////////////////////////////////////////////////////////
void alpha :: alphaMess(int alphaState)
{
    m_alphaState = alphaState;
    setModified();
}
/////////////////////////////////////////////////////////
// funMess
//
/////////////////////////////////////////////////////////
void alpha :: funMess(int fun)
{
  m_function = int2GLenum(fun);
  setModified();
}

GLenum alpha :: int2GLenum(int i){
  GLenum function;
  switch(i){
  case 1:
    function=GL_ONE;
    break;
  case 2:
    function=GL_ZERO;
    break;
  case 3:
    function=GL_SRC_COLOR;
    break;
  case 4:
    function=GL_ONE_MINUS_SRC_COLOR;
    break;
  case 5:
    function=GL_DST_COLOR;
    break;
  case 6:
    function=GL_ONE_MINUS_DST_COLOR;
    break;
  case 7:
    function=GL_SRC_ALPHA;
    break;
  case 8:
    function=GL_ONE_MINUS_SRC_ALPHA;
    break;
  case 9:
    function=GL_DST_ALPHA;
    break;
  case 10:
    function=GL_ONE_MINUS_DST_ALPHA;
    break;
  case 11:
    function=GL_CONSTANT_COLOR;
    break;
  case 12:
    function=GL_ONE_MINUS_CONSTANT_COLOR;
    break;
  case 13:
    function=GL_CONSTANT_ALPHA;
    break;
  case 14:
    function=GL_ONE_MINUS_CONSTANT_ALPHA;
    break;
  case 15:
    function=GL_SRC_ALPHA_SATURATE;
    break;
  case 16:
    function=GL_SRC1_COLOR;
    break;
  case 17:
    function=GL_ONE_MINUS_SRC1_COLOR;
    break;
  case 18:
    function=GL_SRC1_ALPHA;
    break;
  case 19:
    function=GL_ONE_MINUS_SRC1_ALPHA;
    break;
   default:
     function=GL_ONE_MINUS_SRC_ALPHA;
  }
  return function;
}
/////////////////////////////////////////////////////////
// testMess
//
/////////////////////////////////////////////////////////
void alpha :: testMess(int alphaTest)
{
    m_alphaTest = alphaTest;
    setModified();
}
/////////////////////////////////////////////////////////
// depthtestMess
//
/////////////////////////////////////////////////////////
void alpha :: depthtestMess(int i)
{
    m_depthtest = i;
    setModified();
}

/////////////////////////////////////////////////////////
// static member function
//
/////////////////////////////////////////////////////////
void alpha :: obj_setupCallback(t_class *classPtr)
{
  CPPEXTERN_MSG1(classPtr, "float"   , alphaMess    , int);
  CPPEXTERN_MSG1(classPtr, "test"    , testMess     , int);
  CPPEXTERN_MSG1(classPtr, "function", funMess      , int);
  CPPEXTERN_MSG1(classPtr, "auto"    , depthtestMess, int);
}
