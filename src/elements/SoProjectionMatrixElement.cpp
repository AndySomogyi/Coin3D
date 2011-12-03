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
  \class SoProjectionMatrix Inventor/elements/SoProjectionMatrixElement.h
  \brief The SoProjectionMatrixElement class is yet to be documented.
  \ingroup elements

  FIXME: write doc.
*/

#include <Inventor/elements/SoProjectionMatrixElement.h>

#include "SbBasicP.h"

#include <cassert>

SO_ELEMENT_SOURCE(SoProjectionMatrixElement);

/*!
  This static method initializes static data for the SoProjectionMatrixElement
  class.
*/

void
SoProjectionMatrixElement::initClass(void)
{
  SO_ELEMENT_INIT_CLASS(SoProjectionMatrixElement, inherited);
}

/*!
  The destructor.
*/

SoProjectionMatrixElement::~SoProjectionMatrixElement(void)
{
}

//! FIXME: write doc.

void
SoProjectionMatrixElement::set(SoState * const state,
                               SoNode * const node,
                               const SbMatrix & projectionMatrix)
{
  SoProjectionMatrixElement * element = coin_safe_cast<SoProjectionMatrixElement *>
    (
     SoReplacedElement::getElement(state, classStackIndex, node)
     );

  if (element) {
    element->setElt(projectionMatrix);
  }
}

//! FIXME: write doc.

const SbMatrix &
SoProjectionMatrixElement::get(SoState * const state)
{
  const SoProjectionMatrixElement * element =
    coin_assert_cast<const SoProjectionMatrixElement *>
    (
     SoElement::getConstElement(state, classStackIndex)
     );
  return element->projectionMatrix;
}

//! FIXME: write doc.

void
SoProjectionMatrixElement::setElt(SbMatrix const & matrix)
{
  this->projectionMatrix = matrix;
}

//! FIXME: write doc.

void
SoProjectionMatrixElement::init(SoState * state)
{
  inherited::init(state);
  this->projectionMatrix.makeIdentity();
}
