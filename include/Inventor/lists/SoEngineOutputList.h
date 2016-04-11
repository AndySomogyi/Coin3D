#ifndef COIN_SOENGINEOUTPUTLIST_H
#define COIN_SOENGINEOUTPUTLIST_H

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

#include <Inventor/lists/SbPList.h>

class SoEngineOutput;

class COIN_DLL_API SoEngineOutputList : public SbPList {
public:
  SoEngineOutputList(void) : SbPList() { }
  SoEngineOutputList(const int sizehint) : SbPList(sizehint) { }
  SoEngineOutputList(const SoEngineOutputList & l) : SbPList(l) { }

  void append(SoEngineOutput * output) {
    SbPList::append(static_cast<void *>(output));
  }
  void insert(SoEngineOutput * output, const int insertbefore) {
    SbPList::insert(static_cast<void *>(output), insertbefore);
  }
  SoEngineOutput * operator [](const int idx) const {
    return static_cast<SoEngineOutput *>(SbPList::operator[](idx));
  }
  void set(const int idx, SoEngineOutput * item) {
    SbPList::operator[](idx) = static_cast<void *>(item);
  }
};

#endif // !COIN_SOENGINEOUTPUTLIST_H
