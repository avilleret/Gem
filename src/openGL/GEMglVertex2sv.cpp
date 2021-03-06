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

#include "GEMglVertex2sv.h"

CPPEXTERN_NEW_WITH_TWO_ARGS ( GEMglVertex2sv , t_floatarg, A_DEFFLOAT, t_floatarg, A_DEFFLOAT);

/////////////////////////////////////////////////////////
//
// GEMglVertex2sv
//
/////////////////////////////////////////////////////////
// Constructor
//
GEMglVertex2sv :: GEMglVertex2sv	(t_floatarg arg0, t_floatarg arg1) {
vMess(arg0, arg1);
	m_inlet = inlet_new(this->x_obj, &this->x_obj->ob_pd, &s_float, gensym("v"));
}
/////////////////////////////////////////////////////////
// Destructor
//
GEMglVertex2sv :: ~GEMglVertex2sv () {
	inlet_free(m_inlet);
}

/////////////////////////////////////////////////////////
// Render
//
void GEMglVertex2sv :: render(GemState *state) {
	glVertex2sv (v);
}

/////////////////////////////////////////////////////////
// variable
//
void GEMglVertex2sv :: vMess (t_float arg0, t_float arg1) {	// FUN
	v[0]=static_cast<GLshort>(arg0);
	v[1]=static_cast<GLshort>(arg1);
	setModified();
}

/////////////////////////////////////////////////////////
// static member functions
//

void GEMglVertex2sv :: obj_setupCallback(t_class *classPtr) {
	 class_addmethod(classPtr, reinterpret_cast<t_method>(&GEMglVertex2sv::vMessCallback),  	gensym("v"), A_DEFFLOAT, A_DEFFLOAT, A_NULL);
}

void GEMglVertex2sv :: vMessCallback (void* data, t_float arg0, t_float arg1) {
	GetMyClass(data)->vMess ( arg0, arg1);
}
