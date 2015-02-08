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
  \class SoConeDetail SoConeDetail.h Inventor/details/SoConeDetail.h
  \brief The SoConeDetail class contains information about the parts of a SoCone shape.
  \ingroup details

  Instances of this class are used for storing information about hit
  points on cone geometry after pick operations, and for storing
  information returned to tessellation callbacks.

  \sa SoCone, SoRayPickAction, SoCallbackAction
*/

/*!
  \var int SoConeDetail::part
  \COININTERNAL
*/

#include <Inventor/details/SoConeDetail.h>
#include <Inventor/SbName.h>

SO_DETAIL_SOURCE(SoConeDetail);

/*!
  Constructor.
  */
SoConeDetail::SoConeDetail(void)
  : part(0)
{
}

/*!
  Destructor.
 */
SoConeDetail::~SoConeDetail()
{
}

// doc in super
void
SoConeDetail::initClass(void)
{
  SO_DETAIL_INIT_CLASS(SoConeDetail, SoDetail);
}

// doc in super
SoDetail *
SoConeDetail::copy(void) const
{
  SoConeDetail * copy = new SoConeDetail;
  copy->part = this->part;
  return copy;
}

/*!
  Set the part of a cone which was selected. A cone has two
  different conceptual parts; SoCone::SIDES or SoCone::BOTTOM.
 */
void
SoConeDetail::setPart(const int partarg)
{
  this->part = partarg;
}

/*!
  Returns selected cone part, either SoCone::SIDES or SoCone::BOTTOM.
 */
int
SoConeDetail::getPart(void) const
{
  return this->part;
}
