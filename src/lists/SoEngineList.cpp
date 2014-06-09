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
  \class SoEngineList SoEngineList.h Inventor/lists/SoEngineList.h
  \brief The SoEngineList class is a container for SoEngine objects.
  \ingroup engines

  As this class inherits SoBaseList, referencing and dereferencing
  will default be done on the objects at append(), remove(), insert()
  etc.
*/

#include <Inventor/lists/SoEngineList.h>


/*!
  Default constructor.
*/
SoEngineList::SoEngineList(void)
{
}

/*!
  Constructor with a hint about the number of elements the list will
  hold.

  \sa SoBaseList::SoBaseList(const int)
*/
SoEngineList::SoEngineList(const int size)
  : SoBaseList(size)
{
}

/*!
  Copy constructor.

  \sa SoBaseList::SoBaseList(const SoBaseList &)
*/
SoEngineList::SoEngineList(const SoEngineList & el)
  : SoBaseList(el)
{
}

/*!
  Destructor.

  \sa SoBaseList::~SoBaseList()
*/
SoEngineList::~SoEngineList()
{
}

/*!
  Append \a ptr to the list.

  \sa SoBaseList::append()
*/
void
SoEngineList::append(SoEngine * const ptr)
{
  SoBaseList::append((SoBase *)ptr);
}

/*!
  Return engine pointer at index \a i.

  \sa SoBaseList::operator[]()
*/
SoEngine *
SoEngineList::operator[](const int i) const
{
  return (SoEngine *)SoBaseList::operator[](i);
}

/*!
  Copy contents of list \a el to this list.

  \sa SoBaseList::operator=()
*/
SoEngineList &
SoEngineList::operator=(const SoEngineList & el)
{
  this->copy(el);
  return *this;
}
