////////////////////////////////////////////////////////
//
// GEM - Graphics Environment for Multimedia
//
// Implementation file
//
// Copyright (c) 2002-2011 IOhannes m zmölnig. forum::für::umläute. IEM. zmoelnig@iem.at
//	zmoelnig@iem.kug.ac.at
//  For information on usage and redistribution, and for a DISCLAIMER
//  *  OF ALL WARRANTIES, see the file, "GEM.LICENSE.TERMS"
//
//  this file has been generated...
////////////////////////////////////////////////////////

#include "GEMglTexEnvi.h"

CPPEXTERN_NEW_WITH_THREE_ARGS ( GEMglTexEnvi , t_floatarg, A_DEFFLOAT, t_floatarg, A_DEFFLOAT, t_floatarg, A_DEFFLOAT);

/////////////////////////////////////////////////////////
//
// GEMglViewport
//
/////////////////////////////////////////////////////////
// Constructor
//
GEMglTexEnvi :: GEMglTexEnvi	(t_floatarg arg0, t_floatarg arg1, t_floatarg arg2) :
		target(static_cast<GLenum>(arg0)),
		pname(static_cast<GLenum>(arg1)),
		param(static_cast<GLint>(arg2))
{
	m_inlet[0] = inlet_new(this->x_obj, &this->x_obj->ob_pd, &s_float, gensym("target"));
	m_inlet[1] = inlet_new(this->x_obj, &this->x_obj->ob_pd, &s_float, gensym("pname"));
	m_inlet[2] = inlet_new(this->x_obj, &this->x_obj->ob_pd, &s_float, gensym("param"));
}
/////////////////////////////////////////////////////////
// Destructor
//
GEMglTexEnvi :: ~GEMglTexEnvi () {
inlet_free(m_inlet[0]);
inlet_free(m_inlet[1]);
inlet_free(m_inlet[2]);
}

/////////////////////////////////////////////////////////
// Render
//
void GEMglTexEnvi :: render(GemState *state) {
	glTexEnvi (target, pname, param);
}

/////////////////////////////////////////////////////////
// Variables
//
void GEMglTexEnvi :: targetMess (t_float arg1) {	// FUN
	target = static_cast<GLenum>(arg1);
	setModified();
}

void GEMglTexEnvi :: pnameMess (t_float arg1) {	// FUN
	pname = static_cast<GLenum>(arg1);
	setModified();
}

void GEMglTexEnvi :: paramMess (t_float arg1) {	// FUN
	param = static_cast<GLint>(arg1);
	setModified();
}


/////////////////////////////////////////////////////////
// static member functions
//

void GEMglTexEnvi :: obj_setupCallback(t_class *classPtr) {
	 class_addmethod(classPtr, reinterpret_cast<t_method>(&GEMglTexEnvi::targetMessCallback),  	gensym("target"), A_DEFFLOAT, A_NULL);
	 class_addmethod(classPtr, reinterpret_cast<t_method>(&GEMglTexEnvi::pnameMessCallback),  	gensym("pname"), A_DEFFLOAT, A_NULL);
	 class_addmethod(classPtr, reinterpret_cast<t_method>(&GEMglTexEnvi::paramMessCallback),  	gensym("param"), A_DEFFLOAT, A_NULL);
};

void GEMglTexEnvi :: targetMessCallback (void* data, t_float arg0){
	GetMyClass(data)->targetMess ( static_cast<t_float>(arg0));
}
void GEMglTexEnvi :: pnameMessCallback (void* data, t_float arg0){
	GetMyClass(data)->pnameMess ( static_cast<t_float>(arg0));
}
void GEMglTexEnvi :: paramMessCallback (void* data, t_float arg0){
	GetMyClass(data)->paramMess ( static_cast<t_float>(arg0));
}
