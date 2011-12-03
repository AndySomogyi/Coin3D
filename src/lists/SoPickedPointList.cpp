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

#include <Inventor/lists/SoPickedPointList.h>
#include <Inventor/SoPickedPoint.h>

/*!
  \class SoPickedPointList SoPickedPointList.h Inventor/lists/SoPickedPointList.h
  \brief The SoPickedPointList class is a container for pointers to SoPickedPoint objects.
  \ingroup general

  This list class will delete the picked points when
  destructed/truncated, or when a picked point in the list is replaced
  by another picked point The caller is responsible for allocating the
  picked points passed to the list, but should not deallocate them since
  this will be handled by the list.

  \sa SbPList
*/

/*!
  \fn SoPickedPointList::SoPickedPointList(void)

  Default constructor.
*/

/*!
  \fn SoPickedPointList::SoPickedPointList(const int sizehint)

  This constructor initializes the internal allocated size for the
  list to \a sizehint. Note that the list will still initially contain
  zero items.

  \sa SbList::SbList(const int sizehint)
*/

/*!
  \fn SoPickedPoint * SoPickedPointList::operator[](const int idx) const

  Returns element at \a idx.

  Will automatically expand the size of the internal array if \a idx
  is outside the current bounds of the list. The values of any
  additional pointers are then set to \c NULL.
*/


/*!
  Copy constructor. Will copy picked points, not just pointers.

  \sa SbList::SbList(const SbList<Type> & l)
*/
SoPickedPointList::SoPickedPointList(const SoPickedPointList & l)
  : SbPList(l.getLength())
  
{
  for (int i = 0; i < l.getLength(); i++) {
    this->append(l[i]->copy());
  }
}

/*!
  Overridden to delete truncated items.
*/
void 
SoPickedPointList::truncate(const int start, const int fit) 
{
  int oldlen = this->getLength();
  
  for (int i = start; i < oldlen; i++) {
    delete (*this)[i];
  }
  SbPList::truncate(start, fit);
}

/*!
  Overridden to destruct the replaced item.
*/
void 
SoPickedPointList::set(const int idx, SoPickedPoint * pp)
{
  if (idx < this->getLength()) delete (*this)[idx];
  SbPList::operator[](idx) = (void*) pp;
}
