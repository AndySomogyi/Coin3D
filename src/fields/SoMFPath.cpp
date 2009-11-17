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

// Important note: this sourcefile was mostly generated by the
// Coin/scripts/templant script from the code in MFNodeEnginePath.tpl,
// only the notify() method is specific for SoMFPath.cpp.

//$ BEGIN TEMPLATE MFNodeEnginePath(PATH, Path, path)

/*!
  \class SoMFPath SoMFPath.h Inventor/fields/SoMFPath.h
  \brief The SoMFPath class is a container for paths.
  \ingroup fields

  This field container stores an array of pointers to paths. It takes
  care of the necessary functionality for handling copy, import and
  export operations.

  Note that path pointers stored in field instances of this type may
  be \c NULL pointers.

  \sa SoPath, SoSFPath

*/

// Type-specific define to be able to do #ifdef tests on type.  (Note:
// used to check the header file wrapper define, but that doesn't work
// with --enable-compact build.)
#define COIN_INTERNAL_SOMFPATH

#include <Inventor/fields/SoMFPath.h>

#include "coindefs.h"
#include "SbBasicP.h"

#include <Inventor/fields/SoSFPath.h>
#include <Inventor/SoOutput.h>
#include <Inventor/actions/SoWriteAction.h>
#include <Inventor/SoPath.h>
#include <Inventor/engines/SoEngine.h>
#include <Inventor/nodes/SoNode.h>
#if COIN_DEBUG
#include <Inventor/errors/SoDebugError.h>
#endif // COIN_DEBUG

#include "fields/SoSubFieldP.h"

// These are the macros from SO_MFIELD_SOURCE_MALLOC we're
// using. What's missing is the SO_MFIELD_VALUE_SOURCE macro, which we
// need to implement "by hand" so reference counting and auditing
// comes out correctly.
SO_MFIELD_REQUIRED_SOURCE(SoMFPath);
SO_MFIELD_CONSTRUCTOR_SOURCE(SoMFPath);
SO_MFIELD_MALLOC_SOURCE(SoMFPath, SoPath *);
// Note that we're using the MALLOC versions (which just does
// bit-copying) of the macros, and not the the ALLOC versions (which
// allocates with "new", so constructors are run). The reason for this
// is that it's node/engine/path *pointers* that are simply bit-wise
// copied.


// Override from parent class.
void
SoMFPath::initClass(void)
{
  SO_MFIELD_INTERNAL_INIT_CLASS(SoMFPath);
}


// No need to document readValue() and writeValue() here, as the
// necessary information is provided by the documentation of the
// parent classes.
#ifndef DOXYGEN_SKIP_THIS

//// From the SO_MFIELD_VALUE_SOURCE macro, start. ///////////////////////////

// We can't use the macro invocation, as we need to take care of doing
// ref() and unref() on the paths in the array.

int
SoMFPath::fieldSizeof(void) const
{
  return sizeof(SoPath *);
}

void *
SoMFPath::valuesPtr(void)
{
  return this->values;
}

void
SoMFPath::setValuesPtr(void * ptr)
{
  // We don't get any ref()'ing done here, or any notification
  // mechanisms set up -- so this function should _only_ be used for
  // initial setup of array memory.  In Coin, it's only used from
  // SoMField::allocValues().
  this->values = static_cast<SoPath **>(ptr);
}

int
SoMFPath::find(SoPath * value, SbBool addifnotfound)
{
  for (int i=0; i < this->num; i++) if ((*this)[i] == value) return i;

  if (addifnotfound) this->set1Value(this->num, value);
  return -1;
}

void
SoMFPath::setValues(const int start, const int numarg, const SoPath ** newvals)
{
  // Disable temporarily, so we under any circumstances will not send
  // more than one notification about the changes.
  SbBool notificstate = this->enableNotify(FALSE);
  // Important note: the notification state is reset at the end, so
  // this function should *not* have multiple return-points.

  // ref() new paths before unref()-ing old ones, in case there are
  // common paths (we don't want any premature destruction to happen).
  { for (int i=0; i < numarg; i++) if (newvals[i]) newvals[i]->ref(); }

  // We favor simplicity of code over performance here.
  { for (int i=0; i < numarg; i++)
    this->set1Value(start+i, const_cast<SoPath *>(newvals[i])); }

  // unref() to match the initial ref().
  { for (int i=0; i < numarg; i++) if (newvals[i]) newvals[i]->unref(); }

  // Finally, send notification.
  (void)this->enableNotify(notificstate);
  if (notificstate) this->valueChanged();
}

void
SoMFPath::set1Value(const int idx, SoPath * newval)
{
  // Disable temporarily, so we under no circumstances will send more
  // than one notification about the change.
  SbBool notificstate = this->enableNotify(FALSE);
  // Important note: the notification state is reset at the end, so
  // this function should *not* have multiple return-points.

  // Don't use getNum(), getValues() or operator[] to find old values,
  // since this might trigger a recursive evaluation call if the field
  // is connected.

  // Expand array if necessary.
  if (idx >= this->num) {
#ifdef COIN_INTERNAL_SOMFPATH
    for (int i = this->num; i <= idx; i++) this->pathheads.append(NULL);
#endif // COIN_INTERNAL_SOMFPATH
    this->setNum(idx + 1);
  }

  SoPath * oldptr = this->values[idx];
  if (oldptr != newval) {
    if (oldptr) {
#ifdef COIN_INTERNAL_SOMFPATH
      SoNode * h = oldptr->getHead();
      // The path should be audited by us at all times. So don't use
      // SoMFPath to wrap SoTempPath or SoLightPath, for instance.
      assert(h==this->pathheads[idx] &&
             "Path head changed without notification!");
      if (h) {
        h->removeAuditor(this, SoNotRec::FIELD);
        h->unref();
      }
#endif // COIN_INTERNAL_SOMFPATH
      oldptr->removeAuditor(this, SoNotRec::FIELD);
      oldptr->unref();
    }

    if (newval) {
      newval->addAuditor(this, SoNotRec::FIELD);
      newval->ref();
#ifdef COIN_INTERNAL_SOMFPATH
      SoNode * h = newval->getHead();
      if (h) {
        h->addAuditor(this, SoNotRec::FIELD);
        h->ref();
      }
#endif // COIN_INTERNAL_SOMFPATH
    }

    this->values[idx] = newval;
#ifdef COIN_INTERNAL_SOMFPATH
    this->pathheads[idx] = newval ? newval->getHead() : NULL;
#endif // COIN_INTERNAL_SOMFPATH
  }

  // Finally, send notification.
  (void)this->enableNotify(notificstate);
  if (notificstate) this->valueChanged();
}

void
SoMFPath::setValue(SoPath * value)
{
  this->deleteAllValues();
  this->set1Value(0, value);
}

SbBool
SoMFPath::operator==(const SoMFPath & field) const
{
  if (this == &field) return TRUE;
  if (this->getNum() != field.getNum()) return FALSE;

  const SoPath ** const lhs = this->getValues(0);
  const SoPath ** const rhs = field.getValues(0);
  for (int i = 0; i < this->num; i++) if (lhs[i] != rhs[i]) return FALSE;
  return TRUE;
}

/*!
  \copydoc SoMFFloat::deleteAllValues()
*/
void
SoMFPath::deleteAllValues(void)
{
  // Don't use getNum(), but use this->num directly, since getNum()
  // might trigger a recursive evaluation call if the field
  // is connected.

  if (this->num) this->deleteValues(0);
}

// Overridden to handle unref() and removeAuditor().
void
SoMFPath::deleteValues(int start, int numarg)
{
  // Note: this function overrides the one in SoMField, so if you do
  // any changes here, take a look at that method aswell.

  if (numarg == -1) numarg = this->num - start;
  for (int i=start; i < start+numarg; i++) {
    SoPath * n = this->values[i];
    if (n) {
      n->removeAuditor(this, SoNotRec::FIELD);
      n->unref();
    }
#ifdef COIN_INTERNAL_SOMFPATH
    SoNode * h = this->pathheads[start];
    this->pathheads.remove(start);
    if (h) {
      h->removeAuditor(this, SoNotRec::FIELD);
      h->unref();
    }
#endif // COIN_INTERNAL_SOMFPATH
  }

  inherited::deleteValues(start, numarg);
}

// Overridden to insert NULL pointers in new array slots.
void
SoMFPath::insertSpace(int start, int numarg)
{
  // Disable temporarily so we don't send notification prematurely
  // from inherited::insertSpace().
  SbBool notificstate = this->enableNotify(FALSE);
  // Important note: the notification state is reset at the end, so
  // this function should *not* have multiple return-points.

  inherited::insertSpace(start, numarg);
  for (int i=start; i < start+numarg; i++) {
#ifdef COIN_INTERNAL_SOMFPATH
    this->pathheads.insert(NULL, start);
#endif // COIN_INTERNAL_SOMFPATH
    this->values[i] = NULL;
  }

  // Initialization done, now send notification.
  (void)this->enableNotify(notificstate);
  if (notificstate) this->valueChanged();
}

/*!
  \copydoc SoMFFloat::copyValue()
*/
void
SoMFPath::copyValue(int to, int from)
{
  this->values[to] = this->values[from];
}

//// From the SO_MFIELD_VALUE_SOURCE macro, end. /////////////////////////////


// Import a single path.
SbBool
SoMFPath::read1Value(SoInput * in, int index)
{
  SoSFPath sfpath;
  SbBool result = sfpath.readValue(in);
  if (result) this->set1Value(index, sfpath.getValue());
  return result;
}

// Export a single path.
void
SoMFPath::write1Value(SoOutput * out, int idx) const
{
  // NB: This code is common for SoMFNode, SoMFPath and SoMFEngine.
  // That's why we check for the base type before writing.

  SoBase * base = this->values[idx];
  if (base) {
    if (base->isOfType(SoNode::getClassTypeId())) {
      coin_assert_cast<SoNode *>(base)->writeInstance(out);
    }
    else if (base->isOfType(SoPath::getClassTypeId())) {
      SoWriteAction wa(out);
      wa.continueToApply(coin_assert_cast<SoPath *>(base));
    }
    else if (base->isOfType(SoEngine::getClassTypeId())) {
      coin_assert_cast<SoEngine *>(base)->writeInstance(out);
    }
  }
  else {
    out->write("NULL");
  }
}

#endif // DOXYGEN_SKIP_THIS


// Overridden from parent to propagate write reference counting to
// path.
void
SoMFPath::countWriteRefs(SoOutput * out) const
{
  inherited::countWriteRefs(out);

  for (int i = 0; i < this->getNum(); i++) {
    SoBase * base = this->values[i];
    if (base) {
      // NB: This code is common for SoMFNode, SoMFPath and SoMFEngine.
      // That's why we check the base type before writing/counting

      if (base->isOfType(SoNode::getClassTypeId())) {
        coin_assert_cast<SoNode *>(base)->writeInstance(out);
      }
      else if (base->isOfType(SoEngine::getClassTypeId())) {
        coin_assert_cast<SoEngine *>(base)->addWriteReference(out);
      }
      else if (base->isOfType(SoPath::getClassTypeId())) {
        SoWriteAction wa(out);
        wa.continueToApply(coin_assert_cast<SoPath *>(base));
      }
    }
  }
}

// Override from parent to update our path pointer
// references. This is necessary so we do the Right Thing with regard
// to the copyconnections flag.
//
// Note that we have to unplug auditing and the reference counter
// addition we made during the copy process.
//
// For reference for future debugging sessions, copying of this field
// goes like this:
//
//    - copyFrom() is called (typically from SoFieldData::overlay())
//    - copyFrom() calls operator=()
//    - operator=() calls setValues()
//    - we have a local copy (ie not from SoSubField.h) of setValues()
//      that sets up auditing and references the array items
//
// <mortene@sim.no>
void
SoMFPath::fixCopy(SbBool COIN_UNUSED_ARG(copyconnections))
{
  // Disable temporarily, so we under no circumstances will send more
  // than one notification about the changes.
  SbBool notificstate = this->enableNotify(FALSE);
  // Important note: the notification state is reset at the end, so
  // this function should *not* have multiple return-points.

  for (int i=0; i < this->getNum(); i++) {
    SoPath * n = (*this)[i];
    if (n) {
#if COIN_DEBUG
      n->assertAlive();
#endif // COIN_DEBUG
      // The set1Value() call below will automatically de-audit and
      // un-ref the old pointer value node reference we have in the
      // array, *before* re-inserting a copy.

#if defined(COIN_INTERNAL_SOMFNODE) || defined(COIN_INTERNAL_SOMFENGINE)
      SoFieldContainer * fc = SoFieldContainer::findCopy(n, copyconnections);
#if COIN_DEBUG
      fc->assertAlive();
#endif // COIN_DEBUG
      this->set1Value(i, (SoPath *)fc);
#endif // COIN_INTERNAL_SOMFNODE || COIN_INTERNAL_SOMFENGINE

#ifdef COIN_INTERNAL_SOMFPATH
      this->set1Value(i, n->copy());
#endif // COIN_INTERNAL_SOMFPATH
    }
  }

  // Finally, send notification.
  (void)this->enableNotify(notificstate);
  if (notificstate) this->valueChanged();
}

// Override from SoField to check path pointer.
SbBool
SoMFPath::referencesCopy(void) const
{
  if (inherited::referencesCopy()) return TRUE;

  for (int i=0; i < this->getNum(); i++) {
    SoPath * item = (*this)[i];
    if (item) {
#if defined(COIN_INTERNAL_SOMFNODE) || defined(COIN_INTERNAL_SOMFENGINE)
      if (SoFieldContainer::checkCopy((SoFieldContainer *)item)) return TRUE;
#endif // COIN_INTERNAL_SOMFNODE || COIN_INTERNAL_SOMFENGINE
#ifdef COIN_INTERNAL_SOMFPATH
      if (item->getHead() && SoFieldContainer::checkCopy(item->getHead())) return TRUE;
#endif // COIN_INTERNAL_SOMFPATH
    }
  }

  return FALSE;
}

// Kill the type-specific define.
#undef COIN_INTERNAL_SOMFPATH
//$ END TEMPLATE MFNodeEnginePath


// Overridden from superclass to handle changes in paths.
void
SoMFPath::notify(SoNotList * l)
{
  // Detect if any of our paths have gotten a new head :^), and if so
  // do the necessary audit setup magic.
  for (int i=0; i < this->getNum(); i++) {
    SoPath * p = (*this)[i];
    SoNode * oldhead = this->pathheads[i];
    if (p && p->getHead() != oldhead) {
      if (oldhead) {
        oldhead->removeAuditor(this, SoNotRec::FIELD);
        oldhead->unref();
      }
      SoNode * newhead = this->pathheads[i] = p->getHead();
      if (newhead) {
        newhead->addAuditor(this, SoNotRec::FIELD);
        newhead->ref();
      }
    }
  }

  inherited::notify(l);
}

#ifdef COIN_TEST_SUITE

BOOST_AUTO_TEST_CASE(initialized)
{
  SoMFPath field;
  BOOST_CHECK_MESSAGE(field.getTypeId() != SoType::badType(),
                      "missing class initialization");
  BOOST_CHECK_EQUAL(field.getNum(), 0);
}

#endif // COIN_TEST_SUITE
