////////////////////////////////////////////////////////
//
// GEM - Graphics Environment for Multimedia
//
// zmoelnig@iem.kug.ac.at
//
// Implementation file
//
//    Copyright (c) 1997-1998 Mark Danks.
//    Copyright (c) Günther Geiger.
//    Copyright (c) 2001-2011 IOhannes m zmölnig. forum::für::umläute. IEM. zmoelnig@iem.at
//    For information on usage and redistribution, and for a DISCLAIMER OF ALL
//    WARRANTIES, see the file, "GEM.LICENSE.TERMS" in this distribution.
//
/////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////
//
//  pix_set
//
//  0409:forum::für::umläute:2000
//  IOhannes m zmoelnig
//  mailto:zmoelnig@iem.kug.ac.at
//
/////////////////////////////////////////////////////////

// TODO add setroioffset and setroisize methods



// this is to paint easily your own pictures by passing a package of floats that contain all necessary image data)

#include "pix_set.h"
#include "Gem/State.h"

#include <string.h>
#include <stdio.h>

CPPEXTERN_NEW_WITH_TWO_ARGS(pix_set, t_floatarg, A_DEFFLOAT, t_floatarg, A_DEFFLOAT);

/////////////////////////////////////////////////////////
// Constructor
//
/////////////////////////////////////////////////////////
pix_set :: pix_set(t_floatarg xsize, t_floatarg ysize) :
  m_mode(GL_RGBA), m_roiflag(0)
{
  if (xsize < 1) xsize = 256;
  if (ysize < 1) ysize = 256;
  m_roisize[0] = xsize;
  m_roisize[1] = ysize;
  m_roioffset[0]=0;
  m_roioffset[1]=0;
  
  SETMess(xsize, ysize);

  inlet_new(this->x_obj, &this->x_obj->ob_pd, gensym("list"), gensym("data"));
}

/////////////////////////////////////////////////////////
// Destructor
//
/////////////////////////////////////////////////////////
pix_set :: ~pix_set()
{
  cleanPixBlock();
}

/////////////////////////////////////////////////////////
// render
//
/////////////////////////////////////////////////////////
void pix_set :: render(GemState *state)
{
  state->set(GemState::_PIX,&m_pixBlock);
}

/////////////////////////////////////////////////////////
// startRendering
//
/////////////////////////////////////////////////////////
void pix_set :: startRendering()
{
    m_pixBlock.newimage = true;
}

/////////////////////////////////////////////////////////
// postrender
//
/////////////////////////////////////////////////////////
void pix_set :: postrender(GemState *state)
{
    m_pixBlock.newimage = false;
    //state->image = NULL;
}


/////////////////////////////////////////////////////////
// DATAMess
//
/////////////////////////////////////////////////////////
void pix_set :: DATAMess(t_symbol *s, int argc, t_atom *argv)
{
   int picturesize, counter, n;
   int i = 0, j;
   unsigned char *buffer;
   
   if (m_roiflag==0){ 
	  // if no ROI is set, set whole image black before setting pixels values
	  m_pixBlock.image.setBlack();
	  buffer = m_pixBlock.image.data;
	  picturesize = m_pixBlock.image.xsize * m_pixBlock.image.ysize;

   } else {
	   buffer = m_pixBlock.image.data + m_pixBlock.image.csize*(( i / m_roisize[0] + m_roioffset[1] ) * m_pixBlock.image.xsize + (i % m_roisize[0]) + m_roioffset[0]) ;
	   picturesize = m_roisize[0]*m_roisize[1];
   }

   


  switch (m_mode) {
  case GL_RGB:
    n = argc/3;
    counter=(picturesize<n)?picturesize:n;
    while (counter--) {
      buffer[chRed]   = (unsigned char)(255.*atom_getfloat(&argv[0])); // red
      buffer[chGreen] = (unsigned char)(255.*atom_getfloat(&argv[1])); // green
      buffer[chBlue]  = (unsigned char)(255.*atom_getfloat(&argv[2])); // blue
      buffer[chAlpha] = 0;					     // alpha
      argv+=3;
      if (m_roiflag!=0) {
		  i++;
		  buffer = m_pixBlock.image.data + m_pixBlock.image.csize*(( i / m_roisize[0] + m_roioffset[1] ) * m_pixBlock.image.xsize + (i % m_roisize[0]) + m_roioffset[0]) ;
	  } else {
		  buffer+=4;
	  }
    }
    break;
  case GL_LUMINANCE:
    counter=(picturesize<argc)?picturesize:argc;
    while (counter--) {
      buffer[chRed] = buffer[chGreen] = buffer[chBlue] = (unsigned char)(255.*atom_getfloat(argv));	// rgb
      buffer[chAlpha] = 0;									// alpha
      argv++;
      if (m_roiflag!=0) {
		  i++;
		  buffer = m_pixBlock.image.data + m_pixBlock.image.csize*(( i / m_roisize[0] + m_roioffset[1] ) * m_pixBlock.image.xsize + (i % m_roisize[0]) + m_roioffset[0]) ;
	  } else {
		  buffer+=4;
	  }
    }
    break;
  case GL_YCBCR_422_GEM:
    // ?
    break;
  default:
    n = argc/4;
    counter=(picturesize<n)?picturesize:n;
    while (counter--) {
      buffer[chRed]   = (unsigned char)(255.*atom_getfloat(&argv[0])); // red
      buffer[chGreen] = (unsigned char)(255.*atom_getfloat(&argv[1])); // green
      buffer[chBlue]  = (unsigned char)(255.*atom_getfloat(&argv[2])); // blue
      buffer[chAlpha] = (unsigned char)(255.*atom_getfloat(&argv[3])); // alpha
      argv+=4; 
      if (m_roiflag!=0) {
		  i++;
		  buffer = m_pixBlock.image.data + m_pixBlock.image.csize*(( i / m_roisize[0] + m_roioffset[1] ) * m_pixBlock.image.xsize + (i % m_roisize[0]) + m_roioffset[0]) ;
	  } else {
		  buffer+=4;
	  }
    }
  }
  m_pixBlock.newimage = true;
}



/////////////////////////////////////////////////////////
// RGBAMess
//
/////////////////////////////////////////////////////////
void pix_set :: RGBAMess(void)
{
	m_mode = GL_RGBA;
}
/////////////////////////////////////////////////////////
// RGBMess
//
/////////////////////////////////////////////////////////
void pix_set :: RGBMess(void)
{
	m_mode = GL_RGB;
}
/////////////////////////////////////////////////////////
// GREYMess
//
/////////////////////////////////////////////////////////
void pix_set :: GREYMess(void)
{
	m_mode = GL_LUMINANCE;
}

/////////////////////////////////////////////////////////
// SETMess
//
/////////////////////////////////////////////////////////
void pix_set :: SETMess(int xsize, int ysize)
{
	if ((xsize < 1) || (ysize < 1)) return;
	m_pixBlock.image.clear();
	m_pixBlock.image.xsize = (int)xsize;
	m_pixBlock.image.ysize = (int)ysize;
	ROISIZEMess(m_roisize[0],m_roisize[1]); // reset roisizeqq
	ROIOFFSETMess(m_roioffset[0], m_roioffset[1]); // reset roioffset
  m_pixBlock.image.setCsizeByFormat(GL_RGBA_GEM);
  m_pixBlock.image.reallocate();
  m_pixBlock.image.setBlack();
}

/////////////////////////////////////////////////////////
// ROIOFFSETMess
//
/////////////////////////////////////////////////////////
void pix_set :: ROIOFFSETMess(int xoffset, int yoffset)
{
	if ( xoffset<0 ){
		m_roioffset[0] = 0;
	} else if (xoffset+m_roisize[0] > m_pixBlock.image.xsize) {
		m_roioffset[0] = m_pixBlock.image.xsize-m_roisize[0];
	} else {
		m_roioffset[0]=xoffset;
	}
	
	if ( yoffset<0 ){
		m_roioffset[1] = 0;
	} else if (yoffset+m_roisize[1] > m_pixBlock.image.ysize) {
		m_roioffset[1] = m_pixBlock.image.ysize-m_roisize[1];
	} else {
		m_roioffset[1]=yoffset;
	}
	
	m_roiflag=((m_roioffset[0]!=0) || (m_roioffset[1]!=0)) || (m_roisize[0]<m_pixBlock.image.xsize) || (m_roisize[1]<m_pixBlock.image.ysize);
}

/////////////////////////////////////////////////////////
// ROISIZEMess
//
/////////////////////////////////////////////////////////
void pix_set :: ROISIZEMess(int xsize, int ysize)
{
	if ( xsize<0 ){
		m_roisize[0] = 0;
	} else if (xsize > m_pixBlock.image.xsize) {
		m_roisize[0] = m_pixBlock.image.xsize;
		verbose(4,"roisize shoul be > image size");
	} else {
		m_roisize[0]=xsize;
	}
	
	if ( ysize<0 ){
		m_roisize[1] = 0;
	} else if (ysize > m_pixBlock.image.ysize) {
		m_roisize[1] = m_pixBlock.image.ysize;
	} else {
		m_roisize[1]=xsize;
	}
	
	m_roisize[0] = xsize>0?xsize:1;
	m_roisize[1] = ysize>0?ysize:1;
	m_roiflag=((m_roioffset[0]!=0) || (m_roioffset[1]!=0)) || (m_roisize[0]<m_pixBlock.image.xsize) || (m_roisize[1]<m_pixBlock.image.ysize);

}

/////////////////////////////////////////////////////////
// CLEARMess
//
/////////////////////////////////////////////////////////
void pix_set :: FILLMess(t_symbol *s, int argc, t_atom *argv)
{
	int counter = m_pixBlock.image.xsize*m_pixBlock.image.ysize;
	unsigned char 	*buffer = m_pixBlock.image.data;
	unsigned char r,g,b,a;	

	switch (m_mode) {
	  case GL_RGB:
		if ( argc==1 ) {
			r=g=b=a=(unsigned char)(255.*atom_getfloat(&argv[0]));
		} else if ( argc ==3 ) {
			r=(unsigned char)(255.*atom_getfloat(&argv[0]));
			g=(unsigned char)(255.*atom_getfloat(&argv[1]));
			b=(unsigned char)(255.*atom_getfloat(&argv[2]));
			a=0;
		} else {
		  error("fill need 1 or 3 float arg in RGB mode");
		  return;
		}	  
		while (counter--) {
		  buffer[chRed]   = r; // red
		  buffer[chGreen] = g; // green
		  buffer[chBlue]  = b; // blue
		  buffer[chAlpha] = a; // alpha
		  buffer+=4;
		}
		break;
	  case GL_LUMINANCE:
	    if ( argc>0 ) {
			r=g=b=(unsigned char)(255.*atom_getfloat(&argv[0]));
			a=0;
		} else {
			error("fill need 1 float arg in GREY mode");
			return;
		}
		while (counter--) {
		  buffer[chRed] = r;
		  buffer[chGreen] = g;
		  buffer[chBlue] = b;
		  buffer[chAlpha] = a;
		  buffer+=4;
		}
		break;
	  case GL_YCBCR_422_GEM:
		// ?
		break;
	  default:
	    if ( argc==1 ) {
			r=g=b=a=(unsigned char)(255.*atom_getfloat(&argv[0]));
		} else if ( argc == 4 ) {
			r=(unsigned char)(255.*atom_getfloat(&argv[0]));
			g=(unsigned char)(255.*atom_getfloat(&argv[1]));
			b=(unsigned char)(255.*atom_getfloat(&argv[2]));
			a=(unsigned char)(255.*atom_getfloat(&argv[3]));;
		} else {
		  error("fill need 1 or 4 float arg in RGB mode");
		  return;
		}	  
		while (counter--) {
		  buffer[chRed]   = r; // red
		  buffer[chGreen] = g; // green
		  buffer[chBlue]  = b; // blue
		  buffer[chAlpha] = a; // alpha
	      buffer+=4;
		}
	}
}

/////////////////////////////////////////////////////////
// BANGMess
//
/////////////////////////////////////////////////////////
void pix_set :: BANGMess(void)
{
	m_pixBlock.newimage = true;
}

/////////////////////////////////////////////////////////
// cleanPixBlock -- free the pixel buffer memory
//
/////////////////////////////////////////////////////////
void pix_set :: cleanPixBlock()
{
  m_pixBlock.image.clear();
  m_pixBlock.image.data = NULL;
}

/////////////////////////////////////////////////////////
// static member function
//
/////////////////////////////////////////////////////////
void pix_set :: obj_setupCallback(t_class *classPtr)
{
  CPPEXTERN_MSG0(classPtr, "RGBA", RGBAMess);
  CPPEXTERN_MSG0(classPtr, "rgba", RGBAMess);
  CPPEXTERN_MSG0(classPtr, "RGB" , RGBMess);
  CPPEXTERN_MSG0(classPtr, "rgb" , RGBMess);
  //  CPPEXTERN_MSG0(classPtr, "YUV" , YUVMess);
  //  CPPEXTERN_MSG0(classPtr, "yuv" , YUVMess);

  CPPEXTERN_MSG0(classPtr, "GREY", GREYMess);
  CPPEXTERN_MSG0(classPtr, "grey", GREYMess);
  CPPEXTERN_MSG0(classPtr, "GRAY", GREYMess);
  CPPEXTERN_MSG0(classPtr, "gray", GREYMess);

  CPPEXTERN_MSG (classPtr, "data", DATAMess);
  CPPEXTERN_MSG2(classPtr, "set", SETMess, int, int);
  CPPEXTERN_MSG2(classPtr, "roioffset", ROIOFFSETMess, int, int);
  CPPEXTERN_MSG2(classPtr, "roisize", ROISIZEMess, int, int);
  CPPEXTERN_MSG(classPtr, "fill", FILLMess);
  CPPEXTERN_MSG0(classPtr, "bang", BANGMess);

}
