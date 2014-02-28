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

/*!
  \class SoVertexAttributeBundle include/Inventor/SoVertexAttributeBundle.h
  \brief The SoVertexAttributeBundle class simplifies vertex attribute handling.
  \ingroup bundles

*/

#include <Inventor/bundles/SoVertexAttributeBundle.h>
#include <Inventor/actions/SoAction.h>
#include <cassert>
#include "SbBasicP.h"

/*!
  Constructor.
*/
SoVertexAttributeBundle::SoVertexAttributeBundle(SoAction * action, SbBool forrendering)
  : SoBundle(action)
{
  this->elem = SoVertexAttributeElement::getInstance(this->state);
  this->glelem = NULL;
  if (forrendering) {
    this->glelem = static_cast<const SoGLVertexAttributeElement *> (this->elem);
  }
}

/*!
  Destructor.
*/
SoVertexAttributeBundle::~SoVertexAttributeBundle()
{
}

SbBool 
SoVertexAttributeBundle::doAttributes(void) const
{
  return (this->elem->getNumAttributes() > 0);
}

/*!
  Send the index'th attribute to OpenGL.
*/
void 
SoVertexAttributeBundle::send(int index) const
{
  assert(this->glelem);
  this->glelem->send(index);
}
