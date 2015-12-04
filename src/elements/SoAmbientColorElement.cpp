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
  \class SoAmbientColorElement Inventor/elements/SoAmbientColorElement.h
  \brief The SoAmbientColorElement class is yet to be documented.
  \ingroup elements
*/


#include <Inventor/elements/SoAmbientColorElement.h>
#include <Inventor/elements/SoLazyElement.h>
#include <Inventor/errors/SoDebugError.h>
#include <Inventor/SbColor.h>
#include <cassert>
#include <cstdlib>

#include "coindefs.h"
#include "SbBasicP.h"

SO_ELEMENT_SOURCE(SoAmbientColorElement);

/*!
  This static method initializes static data for the
  SoAmbientColorElement class.
*/

void
SoAmbientColorElement::initClass(void)
{
  SO_ELEMENT_INIT_CLASS(SoAmbientColorElement, inherited);
}

//! FIXME: write doc.

void
SoAmbientColorElement::init(SoState * stateptr)
{
  inherited::init(stateptr);
  this->state = stateptr;
}

/*!
  The destructor.
*/

SoAmbientColorElement::~SoAmbientColorElement()
{
}

//! FIXME: write doc.

void
SoAmbientColorElement::set(SoState * const state, SoNode * const COIN_UNUSED_ARG(node),
                           const int32_t numcolors,
                           const SbColor * const colors)
{
  SoLazyElement::setAmbient(state, colors);
#if COIN_DEBUG
  if (numcolors > 1) {
    SoDebugError::postWarning("SoAmbientColorElement::set",
                              "Multiple ambient colors not supported. "
                              "All color except the first will be ignored.");
  }
#endif // COIN_DEBIG
}

//! FIXME: write doc.

int32_t
SoAmbientColorElement::getNum(void) const
{
  return 1;
}

//! FIXME: write doc.

const SbColor &
SoAmbientColorElement::get(const int index) const
{
  assert(index == 0);
  return SoLazyElement::getAmbient(this->state);
}

/*!
  Return a pointer to the color array. This method is not part of the OIV API.
*/
const SbColor *
SoAmbientColorElement::getArrayPtr(void) const
{
  return &SoLazyElement::getAmbient(this->state);
}

//! FIXME: write doc.
const SoAmbientColorElement *
SoAmbientColorElement::getInstance(SoState *state)
{
  return coin_assert_cast<const SoAmbientColorElement *>(
    state->getElementNoPush(classStackIndex)
    );
}
