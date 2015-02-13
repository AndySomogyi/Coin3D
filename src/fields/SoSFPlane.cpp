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
  \class SoSFPlane SoSFPlane.h Inventor/fields/SoSFPlane.h
  \brief The SoSFPlane class is a container for an SbPlane value.
  \ingroup fields

  This field is used where nodes, engines or other field containers
  needs to store a single definition of a 3D plane.

  Fields of this type stores their value to file as a normalvector
  plus an offset from origo: "v0 v1 v2 offset".

  \sa SoMFPlane
*/

// *************************************************************************

#include <Inventor/fields/SoSFPlane.h>

#include <Inventor/SoInput.h>
#include <Inventor/SoOutput.h>
#include <Inventor/errors/SoDebugError.h>
#include <Inventor/errors/SoReadError.h>

#include "fields/SoSubFieldP.h"
#include "fields/shared.h"

// *************************************************************************

SO_SFIELD_SOURCE(SoSFPlane, SbPlane, const SbPlane &);

// *************************************************************************

// Override from parent class.
void
SoSFPlane::initClass(void)
{
  SO_SFIELD_INTERNAL_INIT_CLASS(SoSFPlane);
}

// No need to document readValue() and writeValue() here, as the
// necessary information is provided by the documentation of the
// parent classes.
#ifndef DOXYGEN_SKIP_THIS

SbBool
SoSFPlane::readValue(SoInput * in)
{
  SbPlane p;
  if (!sosfplane_read_value(in, p)) return FALSE;
  this->value = p;
  return TRUE;
}

void
SoSFPlane::writeValue(SoOutput * out) const
{
  sosfplane_write_value(out, this->getValue());
}

#endif // DOXYGEN_SKIP_THIS

// *************************************************************************

#ifdef COIN_TEST_SUITE

BOOST_AUTO_TEST_CASE(initialized)
{
  SoSFPlane field;
  BOOST_CHECK_MESSAGE(SoSFPlane::getClassTypeId() != SoType::badType(),
                      "SoSFPlane class not initialized");
  BOOST_CHECK_MESSAGE(field.getTypeId() != SoType::badType(),
                      "missing class initialization");
}

#endif // COIN_TEST_SUITE
