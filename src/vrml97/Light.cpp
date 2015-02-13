/**************************************************************************\
 * Copyright (c) Kongsberg Oil & Gas Technologies AS
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 * 
 * Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 * 
 * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 * 
 * Neither the name of the copyright holder nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
\**************************************************************************/

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif // HAVE_CONFIG_H

#ifdef HAVE_VRML97

/*!
  \class SoVRMLLight SoVRMLLight.h Inventor/VRMLnodes/SoVRMLLight.h
  \brief The SoVRMLLight class is a superclass for VRML light nodes.
*/

/*!
  \var SoSFBool SoVRMLLight::on
  Enable/disable light. Default value is TRUE.
*/

/*!
  \var SoSFFloat SoVRMLLight::intensity
  The light intensity. A value from 0 to 1. Default value is 1.
*/

/*!
  \var SoSFColor SoVRMLLight::color
  The light color. Default value is (1, 1, 1).
*/

/*!
  \var SoSFFloat SoVRMLLight::ambientIntensity
  The light ambient intensity. A value from 0 to 1. Default value is 0.
*/

#include <Inventor/VRMLnodes/SoVRMLLight.h>
#include "coindefs.h"

#include <Inventor/VRMLnodes/SoVRMLMacros.h>

#include "nodes/SoSubNodeP.h"

SO_NODE_ABSTRACT_SOURCE(SoVRMLLight);

// Doc in parent
void
SoVRMLLight::initClass(void)
{
  SO_NODE_INTERNAL_INIT_ABSTRACT_CLASS(SoVRMLLight, SO_VRML97_NODE_TYPE);
}

/*!
  Constructor.
*/
SoVRMLLight::SoVRMLLight(void)
{
  SO_VRMLNODE_INTERNAL_CONSTRUCTOR(SoVRMLLight);

  SO_VRMLNODE_ADD_FIELD(on, (TRUE));
  SO_VRMLNODE_ADD_FIELD(intensity, (1.0f));
  SO_VRMLNODE_ADD_FIELD(color, (1.0f, 1.0f, 1.0f));
  SO_VRMLNODE_ADD_FIELD(ambientIntensity, (0.0f));
}

/*!
  Destructor.
*/
SoVRMLLight::~SoVRMLLight()
{
}

// Doc in parent
void
SoVRMLLight::GLRender(SoGLRenderAction * COIN_UNUSED_ARG(action))
{
}

#endif // HAVE_VRML97
