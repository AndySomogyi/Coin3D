#ifndef COIN_SOBBOXMODELMATRIXELEMENT_H
#define COIN_SOBBOXMODELMATRIXELEMENT_H

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

#include <Inventor/elements/SoModelMatrixElement.h>

class SoLocalBBoxMatrixElement;

class COIN_DLL_API SoBBoxModelMatrixElement : public SoModelMatrixElement {
  typedef SoModelMatrixElement inherited;

  SO_ELEMENT_HEADER(SoBBoxModelMatrixElement);
public:
  static void initClass(void);
protected:
  virtual ~SoBBoxModelMatrixElement();

public:
  virtual void init(SoState * state);

  virtual void push(SoState * state);

  static  void reset(SoState * const state, SoNode * const node);
  static  void pushMatrix(SoState * const state, SbMatrix & matrix,
                          SbMatrix & localmatrix);
  static  void popMatrix(SoState * const state, const SbMatrix & matrix,
                         const SbMatrix & localmatrix);

protected:
  virtual void makeEltIdentity(void);
  virtual void setElt(const SbMatrix & matrix);
  virtual void multElt(const SbMatrix & matrix);
  virtual void translateEltBy(const SbVec3f & translation);
  virtual void rotateEltBy(const SbRotation & translation);
  virtual void scaleEltBy(const SbVec3f & scaleFactor);

// the following two functions should not be called - only for debug usage
  virtual SbMatrix pushMatrixElt();
  virtual void popMatrixElt(const SbMatrix & matrix);

private:
  SoLocalBBoxMatrixElement *getLocal();

  SoState *state;
};

#endif // !COIN_SOBBOXMODELMATRIXELEMENT_H
