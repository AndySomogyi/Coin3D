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
  \class SoGLViewportRegionElement Inventor/elements/SoGLViewportRegionElement.h
  \brief The SoGLViewportRegionElement class is yet to be documented.
  \ingroup elements

  FIXME: write doc.
*/

#include <Inventor/elements/SoGLViewportRegionElement.h>


#include <cassert>
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif // HAVE_CONFIG_H

#include <Inventor/system/gl.h>

#if COIN_DEBUG
#include <Inventor/errors/SoDebugError.h>
#endif // COIN_DEBUG

SO_ELEMENT_SOURCE(SoGLViewportRegionElement);

/*!
  This static method initializes static data for the
  SoGLViewportRegionElement class.
*/

void
SoGLViewportRegionElement::initClass(void)
{
  SO_ELEMENT_INIT_CLASS(SoGLViewportRegionElement, inherited);
}

/*!
  The destructor.
*/

SoGLViewportRegionElement::~SoGLViewportRegionElement()
{
}

//! FIXME: write doc.

void
SoGLViewportRegionElement::init(SoState * state)
{
  inherited::init(state);
  this->initialized = FALSE;
}

//! FIXME: write doc.

void
SoGLViewportRegionElement::push(SoState * state)
{
  inherited::push(state);
  SoGLViewportRegionElement * prev = (SoGLViewportRegionElement*)
    this->getNextInStack();
  this->viewportRegion = prev->viewportRegion;
  this->initialized = TRUE;
}

//! FIXME: write doc.

void
SoGLViewportRegionElement::pop(SoState * state,
                               const SoElement * prevTopElement)
{
  SoGLViewportRegionElement * prev =
    (SoGLViewportRegionElement *)prevTopElement;
  if (!(this->viewportRegion == prev->viewportRegion))
    this->updategl();
  prev->capture(state);
}

//! FIXME: write doc.

void
SoGLViewportRegionElement::setElt(const SbViewportRegion & viewportRegionarg)
{
  this->viewportRegion = viewportRegionarg;
  this->initialized = TRUE;
  this->updategl();
}

//! FIXME: write doc.

void
SoGLViewportRegionElement::updategl() const
{
  if (this->initialized) {
    SbVec2s origin = this->viewportRegion.getViewportOriginPixels();
    SbVec2s size = this->viewportRegion.getViewportSizePixels();
    glViewport(origin[0], origin[1], size[0], size[1]);

#if COIN_DEBUG && 0 // debug
    SoDebugError::postInfo("SoGLViewportRegionElement::updategl",
                           "glViewport: %d %d %d %d",
                           origin[0], origin[1], size[0], size[1]);
#endif // debug
  }
}
