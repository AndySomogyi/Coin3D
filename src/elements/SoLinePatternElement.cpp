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
  \class SoLinePatternElement Inventor/elements/SoLinePatternElement.h
  \brief The SoLinePatternElement class is yet to be documented.
  \ingroup elements

  FIXME: write doc.
*/

#include <Inventor/elements/SoLinePatternElement.h>


#include <cassert>

SO_ELEMENT_SOURCE(SoLinePatternElement);

/*!
  This static method initializes static data for the
  SoLinePatternElement class.
*/

void
SoLinePatternElement::initClass(void)
{
  SO_ELEMENT_INIT_CLASS(SoLinePatternElement, inherited);
}

/*!
  The destructor.
*/

SoLinePatternElement::~SoLinePatternElement(void)
{
}

//! FIXME: write doc.

void
SoLinePatternElement::set(SoState * const state,
                          SoNode * const node,
                          const int32_t pattern,
                          const int32_t factor)
{
  // pattern and scale factor are stored as single value (pattern: 0 - 15, factor: 16-23)
  SoInt32Element::set(classStackIndex, state, node, (pattern & 0xffff) | ((factor & 0xff) << 16));
}

//! FIXME: write doc.

void
SoLinePatternElement::init(SoState * state)
{
  inherited::init(state);

  this->data = SoLinePatternElement::getDefault();
}

//! FIXME: write doc.

//$ EXPORT INLINE
void
SoLinePatternElement::set(SoState * const state, const int32_t pattern,
                          const int32_t factor)
{
  set(state, NULL, pattern, factor);
}

//! FIXME: write doc.

//$ EXPORT INLINE
int32_t
SoLinePatternElement::get(SoState * const state)
{
  return SoInt32Element::get(classStackIndex, state) & 0xffff;
}

//! FIXME: write doc.

//$ EXPORT INLINE
int32_t
SoLinePatternElement::getDefault()
{
  return CONTINUOUS;
}

//! FIXME: write doc.

//$ EXPORT INLINE
int32_t
SoLinePatternElement::getScaleFactor(SoState * const state)
{
  return SoInt32Element::get(classStackIndex, state) >> 16;
}

//! FIXME: write doc.

//$ EXPORT INLINE
int32_t
SoLinePatternElement::getDefaultScaleFactor()
{
  return 1;
}
