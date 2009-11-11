#ifndef COIN_SOFLOATELEMENT_H
#define COIN_SOFLOATELEMENT_H

/**************************************************************************\
 *
 *  This file is part of the Coin 3D visualization library.
 *  Copyright (C) 1998-2009 by Kongsberg SIM.  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  ("GPL") version 2 as published by the Free Software Foundation.
 *  See the file LICENSE.GPL at the root directory of this source
 *  distribution for additional information about the GNU GPL.
 *
 *  For using Coin with software that can not be combined with the GNU
 *  GPL, and for taking advantage of the additional benefits of our
 *  support services, please contact Kongsberg SIM about acquiring
 *  a Coin Professional Edition License.
 *
 *  See http://www.coin3d.org/ for more information.
 *
 *  Kongsberg SIM, Postboks 1283, Pirsenteret, 7462 Trondheim, NORWAY.
 *  http://www.sim.no/  sales@sim.no  coin-support@coin3d.org
 *
\**************************************************************************/

#include <Inventor/elements/SoSubElement.h>

class COIN_DLL_API SoFloatElement : public SoElement {
  typedef SoElement inherited;

  SO_ELEMENT_ABSTRACT_HEADER(SoFloatElement);
public:
  static void initClass(void);
protected:
  virtual ~SoFloatElement();

public:
  virtual void init(SoState * state);

  virtual SbBool matches(const SoElement * element) const;
  virtual SoElement * copyMatchInfo(void) const;

  virtual void print(FILE * file) const;

  static void set(const int stackIndex, SoState * const state,
                  SoNode * const node, const float value);
  static void set(const int stackIndex, SoState * const state,
                  const float value);

  static float get(const int stackIndex, SoState * const state);

  virtual void setElt(float value);

protected:
  float data;
};

#endif // !COIN_SOFLOATELEMENT_H
