////////////////////////////////////////////////////////
//
// GEM - Graphics Environment for Multimedia
//
// zmoelnig@iem.kug.ac.at
//
//    Copyright (c) 1997-2000 Mark Danks.
//    Copyright (c) Günther Geiger.
//    Copyright (c) 2001-2003 IOhannes m zmoelnig. forum::für::umläute. IEM
//    For information on usage and redistribution, and for a DISCLAIMER OF ALL
//    WARRANTIES, see the file, "GEM.LICENSE.TERMS" in this distribution.
//
/////////////////////////////////////////////////////////

#include "partlib_base.h"

#include <string.h>
#include "Gem/State.h"

#include "papi.h"

/////////////////////////////////////////////////////////
//
// partlib_base
//
/////////////////////////////////////////////////////////
// Constructor
//
/////////////////////////////////////////////////////////
partlib_base :: partlib_base() : m_tickTime(0)
{
}

/////////////////////////////////////////////////////////
// Destructor
//
/////////////////////////////////////////////////////////
partlib_base :: ~partlib_base()
{ 
}

/////////////////////////////////////////////////////////
// render
//
/////////////////////////////////////////////////////////
void partlib_base :: render(GemState *state)
{
  m_tickTime=50.;

  if(state)
    state->get(GemState::_TIMING_TICK, m_tickTime);

  renderParticles(state);
}

