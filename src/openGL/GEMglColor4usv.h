 /* ------------------------------------------------------------------
  * GEM - Graphics Environment for Multimedia
  *
  *  Copyright (c) 2002 IOhannes m zmoelnig. forum::für::umläute. IEM
  *	zmoelnig@iem.kug.ac.at
  *  For information on usage and redistribution, and for a DISCLAIMER
  *  OF ALL WARRANTIES, see the file, "GEM.LICENSE.TERMS"
  *
  *  this file has been generated...
  * ------------------------------------------------------------------
  */

#ifndef INCLUDE_GEM_GLCOLOR4USV_H_
#define INCLUDE_GEM_GLCOLOR4USV_H_

#include "Base/GemGLBase.h"

/*
 CLASS
	GEMglColor4usv
 KEYWORDS
	openGL	0
 DESCRIPTION
	wrapper for the openGL-function
	"glColor4usv( GLushort* v)"
 */

class GEM_EXTERN GEMglColor4usv : public GemGLBase
{
	CPPEXTERN_HEADER(GEMglColor4usv, GemGLBase);

	public:
	  // Constructor
	  GEMglColor4usv (t_float, t_float, t_float, t_float);	// CON
	protected:
	  // Destructor
	  virtual ~GEMglColor4usv ();
	  // Do the rendering
	  virtual void	render (GemState *state);

	// variable
	GLushort	v[4];		// VAR
	virtual void	vMess(t_float, t_float, t_float, t_float);	// FUN

	private:

	// we need one inlet
	  t_inlet *m_inlet;

	// static member functions
         static void    vMessCallback (void*, t_floatarg, t_floatarg, t_floatarg, t_floatarg);
};
#endif // for header file
