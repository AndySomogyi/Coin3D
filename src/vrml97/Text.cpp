/**************************************************************************\
 *
 *  This file is part of the Coin 3D visualization library.
 *  Copyright (C) 1998-2003 by Systems in Motion.  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  ("GPL") version 2 as published by the Free Software Foundation.
 *  See the file LICENSE.GPL at the root directory of this source
 *  distribution for additional information about the GNU GPL.
 *
 *  For using Coin with software that can not be combined with the GNU
 *  GPL, and for taking advantage of the additional benefits of our
 *  support services, please contact Systems in Motion about acquiring
 *  a Coin Professional Edition License.
 *
 *  See <URL:http://www.coin3d.org> for  more information.
 *
 *  Systems in Motion, Teknobyen, Abels Gate 5, 7030 Trondheim, NORWAY.
 *  <URL:http://www.sim.no>.
 *
\**************************************************************************/

/*!
  \class SoVRMLText SoVRMLText.h Inventor/VRMLnodes/SoVRMLText.h
  \brief The SoVRMLText class is used to represent text in a scene.
  \ingroup VRMLnodes

  \WEB3DCOPYRIGHT

  Important note: currently, the implementation of this node is not
  complete, and some of the features mentioned in the documentation
  below may not be working yet.

  \WEB3DCOPYRIGHT
  
  \verbatim
  Text { 
    exposedField  MFString string    []
    exposedField  SFNode   fontStyle NULL
    exposedField  MFFloat  length    []      # [0,)
    exposedField  SFFloat  maxExtent 0.0     # [0,)
  }
  \endverbatim

  The Text node specifies a two-sided, flat text string object
  positioned in the Z=0 plane of the local coordinate system based on
  values defined in the fontStyle field (see SoVRMLFontStyle).
  Text nodes may contain multiple text strings specified using the
  UTF-8 encoding as specified by ISO 10646-1:1993 (see
  <http://www.web3d.org/technicalinfo/specifications/vrml97/part1/references.html#[UTF8]>).
  The text strings are stored in the order in which the text mode
  characters are to be produced as defined by the parameters in the
  FontStyle node.

  The text strings are contained in the string field. The fontStyle
  field contains one FontStyle node that specifies the font size, font
  family and style, direction of the text strings, and any specific
  language rendering techniques used for the text.

  The maxExtent field limits and compresses all of the text strings if
  the length of the maximum string is longer than the maximum extent,
  as measured in the local coordinate system. If the text string with
  the maximum length is shorter than the maxExtent, then there is no
  compressing. The maximum extent is measured horizontally for
  horizontal text (FontStyle node: horizontal=TRUE) and vertically for
  vertical text (FontStyle node: horizontal=FALSE). The maxExtent
  field shall be greater than or equal to zero.

  The length field contains an MFFloat value that specifies the length
  of each text string in the local coordinate system. If the string is
  too short, it is stretched (either by scaling the text or by adding
  space between the characters). If the string is too long, it is
  compressed (either by scaling the text or by subtracting space
  between the characters). If a length value is missing (for example,
  if there are four strings but only three length values), the missing
  values are considered to be 0. The length field shall be greater
  than or equal to zero.

  Specifying a value of 0 for both the maxExtent and length fields
  indicates that the string may be any length.

  \sa SoVRMLFontStyle
*/

/*!
  \var SoMFString SoVRMLText::string
  The strings. Empty by default.
*/

/*!
  \var SoMFFloat SoVRMLText::length
  Length of each string in the local coordinate system.
*/

/*!
  \var SoSFNode SoVRMLText::fontStyle
  Can contain an SoVRMLFontStyle node.
*/

/*!
  \var SoSFFloat SoVRMLText::maxExtent
  Maximum object space extent of longest string.
*/

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif // HAVE_CONFIG_H

#include <float.h> // FLT_MIN
#include <stddef.h>

#include <Inventor/VRMLnodes/SoVRMLText.h>
#include <Inventor/VRMLnodes/SoVRMLMacros.h>
#include <Inventor/VRMLnodes/SoVRMLFontStyle.h>

#include <Inventor/elements/SoFontNameElement.h>
#include <Inventor/elements/SoFontSizeElement.h>

#include <Inventor/SoPrimitiveVertex.h>
#include <Inventor/nodes/SoSubNodeP.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/actions/SoGetPrimitiveCountAction.h>
#include <Inventor/bundles/SoMaterialBundle.h>
#include <Inventor/details/SoTextDetail.h>
#include <Inventor/elements/SoGLTexture3EnabledElement.h>
#include <Inventor/elements/SoGLTextureEnabledElement.h>
#include <Inventor/errors/SoDebugError.h>
#include <Inventor/lists/SbList.h>
#include <Inventor/misc/SoGlyph.h>
#include <Inventor/system/gl.h>
#include <Inventor/sensors/SoFieldSensor.h>
#include <Inventor/nodes/SoAsciiText.h>


#include "../fonts/glyph3d.h"

static void fontstylechangeCB(void * data, SoSensor * sensor);

class SoVRMLTextP {
public:
  SoVRMLTextP(SoVRMLText * master) : master(master) { }
  SoVRMLText * master;

  float getWidth(const int idx, const float fontsize);
  SbList <float> glyphwidths;
  SbBool needsetup;
  cc_font_specification * fontspec;

  void setUpGlyphs(SoState * state, SoVRMLText * textnode);

  SoFieldSensor * fontstylesensor;

  int justificationmajor;
  int justificationminor;
  SbBool lefttorighttext;
  SbBool toptobottomtext;
  SbBool horizontaltext;
  float textspacing;
  float textsize;
  float maxglyphheight;
  float maxglyphwidth;
  SbBox3f maxglyphbbox;
  int fontfamily;
  int fontstyle;
};


#define PRIVATE(obj) (obj->pimpl)

SO_NODE_SOURCE(SoVRMLText);

// Doc in parent
void
SoVRMLText::initClass(void)
{
  SO_NODE_INTERNAL_INIT_CLASS(SoVRMLText, SO_VRML97_NODE_TYPE);
}

/*!
  Constructor.
*/
SoVRMLText::SoVRMLText(void)
{
  PRIVATE(this) = new SoVRMLTextP(this);
  PRIVATE(this)->needsetup = TRUE;

  SO_VRMLNODE_INTERNAL_CONSTRUCTOR(SoVRMLText);

  SO_VRMLNODE_ADD_EMPTY_EXPOSED_MFIELD(string);

  SO_VRMLNODE_ADD_EXPOSED_FIELD(fontStyle, (NULL));
  SO_VRMLNODE_ADD_EXPOSED_FIELD(maxExtent, (0.0f));
  SO_VRMLNODE_ADD_EMPTY_EXPOSED_MFIELD(length);

  // Default text setup
  PRIVATE(this)->textsize = 1.0f;
  PRIVATE(this)->textspacing = 1.0f;
  PRIVATE(this)->maxglyphheight = 1.0f;
  PRIVATE(this)->maxglyphwidth = 1.0f;
  PRIVATE(this)->lefttorighttext = TRUE;
  PRIVATE(this)->toptobottomtext = TRUE;
  PRIVATE(this)->horizontaltext = TRUE;
  PRIVATE(this)->justificationmajor = SoAsciiText::LEFT;
  PRIVATE(this)->justificationminor = SoAsciiText::LEFT;
  
  PRIVATE(this)->fontstylesensor = new SoFieldSensor(fontstylechangeCB, PRIVATE(this));
  PRIVATE(this)->fontstylesensor->attach(&fontStyle);
  PRIVATE(this)->fontstylesensor->setPriority(0);
  
  PRIVATE(this)->fontspec = NULL;

}

float
SoVRMLTextP::getWidth(const int idx, const float fontsize)
{
  float w = this->glyphwidths[idx];
  float maxe = this->master->maxExtent.getValue();
  if (maxe > 0.0f && w > maxe) w = maxe;
  return w;
}


/*!
  Destructor.
*/
SoVRMLText::~SoVRMLText()
{

  if (PRIVATE(this)->fontspec != NULL) {
    cc_fontspec_clean(PRIVATE(this)->fontspec);
  }

  delete PRIVATE(this)->fontstylesensor;
  delete PRIVATE(this);
}

// Doc in parent
void
SoVRMLText::GLRender(SoGLRenderAction * action)
{

  if (!this->shouldGLRender(action)) return;

  SoState * state = action->getState();
  PRIVATE(this)->setUpGlyphs(state, this);

  SoMaterialBundle mb(action);
  mb.sendFirst();

  SbBool do2Dtextures = FALSE;
  SbBool do3Dtextures = FALSE;
  if (SoGLTextureEnabledElement::get(state)) do2Dtextures = TRUE;
  else if (SoGLTexture3EnabledElement::get(state)) do3Dtextures = TRUE;

  // FIXME: implement proper support for 3D-texturing, and get rid of
  // this. 20020120 mortene.
  if (do3Dtextures) {
    static SbBool first = TRUE;
    if (first) {
      first = FALSE;
      SoDebugError::postWarning("SoVRMLText::GLRender",
                                "3D-textures not properly supported for this node type yet.");
    }
  }

  int i;
  const int n = this->string.getNum();

  glBegin(GL_TRIANGLES);
  glNormal3f(0.0f, 0.0f, 1.0f);

  int glyphidx = 0;
  const float spacing = PRIVATE(this)->textspacing * PRIVATE(this)->textsize;
  int maxstringchars = 0;
  float ypos = 0.0f;

  for (i = 0; i < n; ++i) 
    maxstringchars = SbMax(maxstringchars, this->string[i].getLength());
  
  for (i = 0; i < n; i++) {

    float xpos = 0.0f;
    const char * str = this->string[i].getString();
  
    float stretchlength = 0.0f;
    if (i < this->length.getNum()) 
      stretchlength = this->length[i];
    float stretchfactor = (stretchlength * PRIVATE(this)->textsize) / strlen(str);
    
    float compressfactor = 1;
    if (this->maxExtent.getValue() > 0) {
      if (PRIVATE(this)->glyphwidths[i] > this->maxExtent.getValue()) {
        assert(PRIVATE(this)->glyphwidths[i] != 0 && "String length == 0! Cannot divide");
        compressfactor = (this->maxExtent.getValue() * PRIVATE(this)->textsize) / PRIVATE(this)->glyphwidths[i];
      }
    }
    
    
    if (PRIVATE(this)->horizontaltext) { // -- Horizontal text ----------------------
      
      switch (PRIVATE(this)->justificationmajor) {
      case SoAsciiText::LEFT:
        xpos = 0.0f;
        break;
      case SoAsciiText::CENTER:
        if (PRIVATE(this)->lefttorighttext)
          xpos = - PRIVATE(this)->glyphwidths[i] * PRIVATE(this)->textsize * 0.5f;
        else
          xpos = PRIVATE(this)->glyphwidths[i] * PRIVATE(this)->textsize * 0.5f;
        break;
      case SoAsciiText::RIGHT:
        if (PRIVATE(this)->lefttorighttext)
          xpos = -PRIVATE(this)->glyphwidths[i] * PRIVATE(this)->textsize;
        else
          xpos = PRIVATE(this)->glyphwidths[i] * PRIVATE(this)->textsize;
        break;
      default:
        break;
      }

      switch (PRIVATE(this)->justificationminor) {
      case SoAsciiText::LEFT:
        break;
      case SoAsciiText::CENTER:
        ypos = (i * spacing) + ((n-1) * spacing) * 0.5f;
        break;
      case SoAsciiText::RIGHT:
        ypos = (i * spacing) + ((n-1) * spacing);
        break;        
      default:
        break;
      }
    
    }
    else { // -- Vertical text -----------------------------------------

      if (PRIVATE(this)->lefttorighttext)
        xpos = i * spacing;
      else
        xpos = -i * spacing;
        
      switch (PRIVATE(this)->justificationmajor) {
      case SoAsciiText::LEFT:        
        ypos = -PRIVATE(this)->maxglyphheight;
        break;
      case SoAsciiText::RIGHT:
        if (PRIVATE(this)->toptobottomtext)
          ypos = this->string[i].getLength() * spacing;
        else
          ypos = -this->string[i].getLength() * spacing;
        break;
      case SoAsciiText::CENTER:
        if (PRIVATE(this)->toptobottomtext)
          ypos = this->string[i].getLength() * PRIVATE(this)->textsize * 0.5f;
        else
          ypos = -this->string[i].getLength() * PRIVATE(this)->textsize * 0.5f;
        break;
      default:
        break;
      }

      switch (PRIVATE(this)->justificationminor) {
      case SoAsciiText::LEFT:
        break;
      case SoAsciiText::CENTER:
        xpos -= ((n-1) * spacing) * PRIVATE(this)->textsize * 0.5f;
        break;
      case SoAsciiText::RIGHT:
        xpos -= ((n-1) * spacing) * PRIVATE(this)->textsize;
        break;        
      default:
        break;
      }

    }
     

    const cc_glyph3d * lastglyph = NULL;

    while (*str++) {

      cc_glyph3d * glyph = cc_glyph3d_getglyph(*(str-1), PRIVATE(this)->fontspec);

      float width = cc_glyph3d_getwidth(glyph);
      if (width == 0) 
        width = PRIVATE(this)->textsize / 3; // SPACE width is set to fontsize/3

      // Kerning adjustments
      if (lastglyph != NULL) {
        float kerningx = 0.0f;
        float kerningy = 0.0f;
        // FIXME: Must implement proper kerning support here. (20030910 handegar)
        //cc_glyph3d_getkerning(lastglyph, PRIVATE(this)->glyphs[glyphidx-1][0], &kerningx, &kerningy)/PRIVATE(this)->textsize; 
        xpos += kerningx;
      }

      lastglyph = glyph;

      const SbVec2f * coords = (SbVec2f *) cc_glyph3d_getcoords(glyph);
      const int * ptr = cc_glyph3d_getfaceindices(glyph);

      if (PRIVATE(this)->horizontaltext) {
        if (!PRIVATE(this)->lefttorighttext) {// Right to left text.
          xpos -= (width + stretchfactor) * compressfactor * PRIVATE(this)->textsize;

          if (lastglyph != NULL) {
            float kerningx = 0.0f;
            float kerningy = 0.0f;
            // FIXME: Must implement proper kerning support here. (20030910 handegar)
            //cc_glyph3d_getkerning(lastglyph, PRIVATE(this)->glyphs[glyphidx-1][0], &kerningx, &kerningy)/PRIVATE(this)->textsize;
            xpos += kerningx;
          }
        }
      }             

      while (*ptr >= 0) {
        SbVec2f v0, v1, v2;
        v0 = coords[*ptr++];
        v1 = coords[*ptr++];
        v2 = coords[*ptr++];

        if (do2Dtextures) {
          glTexCoord2f(v0[0], v0[1]);
        }
        glVertex3f((v0[0]*PRIVATE(this)->textsize) + xpos, (v0[1]*PRIVATE(this)->textsize) + ypos, 0.0f);
        if (do2Dtextures) {
          glTexCoord2f(v1[0], v1[1]);
        }
        glVertex3f(v1[0] * PRIVATE(this)->textsize + xpos, v1[1] * PRIVATE(this)->textsize + ypos, 0.0f);
        if (do2Dtextures) {
          glTexCoord2f(v2[0], v2[1]);
        }
        glVertex3f(v2[0] * PRIVATE(this)->textsize + xpos, v2[1] * PRIVATE(this)->textsize + ypos, 0.0f);
      }
      
      if (!PRIVATE(this)->horizontaltext) {
        
        if (PRIVATE(this)->toptobottomtext)
          ypos -= PRIVATE(this)->textsize;
        else 
          ypos += PRIVATE(this)->textsize;
        
      } else if (PRIVATE(this)->lefttorighttext) {
        xpos += (width + stretchfactor) * compressfactor * PRIVATE(this)->textsize;
      }
    }

    if (PRIVATE(this)->horizontaltext) {
      if (PRIVATE(this)->toptobottomtext)
        ypos -= spacing * PRIVATE(this)->maxglyphheight;
      else
        ypos += spacing * PRIVATE(this)->maxglyphheight;
    }
   
  }
  glEnd();
}


// Doc in parent
void
SoVRMLText::getPrimitiveCount(SoGetPrimitiveCountAction * action)
{
  PRIVATE(this)->setUpGlyphs(action->getState(), this);

  if (action->is3DTextCountedAsTriangles()) {        
    int lines = this->string.getNum();
    int numtris = 0;      
    for (int i = 0;i < lines; ++i) {
      int n = this->string[i].getLength();
      const char * str = this->string[i].getString();
      for (int j = 0; j < n; j++) {
        cc_glyph3d * glyph = cc_glyph3d_getglyph(*str++, PRIVATE(this)->fontspec);
        int cnt = 0;
        const int * ptr = cc_glyph3d_getfaceindices(glyph);
        while (*ptr++ >= 0) cnt++;
        numtris += cnt / 3;
      }
    }
    action->addNumTriangles(numtris);
  }
  else {
    action->addNumText(this->string.getNum());
  }

}


// Doc in parent
void
SoVRMLText::notify(SoNotList * list)
{
  SoField * f = list->getLastField();
  if (f == &this->string) PRIVATE(this)->needsetup = TRUE;
  inherited::notify(list);
}

// Doc in parent
SoChildList *
SoVRMLText::getChildren(void) const
{
  return NULL;
}


// Doc in parent
void
SoVRMLText::computeBBox(SoAction * action,
                        SbBox3f & box,
                        SbVec3f & center)
{
  PRIVATE(this)->setUpGlyphs(action->getState(), this);

  int i;
  const int n = this->string.getNum();
  const float linespacing = PRIVATE(this)->textspacing * PRIVATE(this)->maxglyphheight;

  float maxw = FLT_MIN;
  int maxstringchars = 0;
  for (i = 0; i < n; i++) {
    maxw = SbMax(maxw, PRIVATE(this)->glyphwidths[i]); 
    maxstringchars = SbMax(maxstringchars, this->string[i].getLength());
  }

  float maxglyphsize = PRIVATE(this)->maxglyphheight;  
  float maxlength = 0.0f;

  for (i = 0; i < this->length.getNum();++i) 
    maxlength = SbMax(maxlength, this->length[i]);
  float stretchfactor = (maxlength * PRIVATE(this)->textsize);

  float maxy, miny;
  float minx, maxx;
  
  if (PRIVATE(this)->horizontaltext) {  // -- Horizontal text -----------------
    
    if (PRIVATE(this)->toptobottomtext) {
      miny = -PRIVATE(this)->textsize * PRIVATE(this)->textspacing * (n-1);
      maxy = PRIVATE(this)->textsize;
    } 
    else {
      miny = 0.0f;
      maxy = PRIVATE(this)->textsize * PRIVATE(this)->textspacing * (n-1);
    }
    
    minx = 0.0f;  
    maxx = (maxw + stretchfactor) * PRIVATE(this)->textsize;
 
    switch (PRIVATE(this)->justificationmajor) {
    case SoAsciiText::LEFT:
      if (!PRIVATE(this)->lefttorighttext) {
        maxx -= (maxw + stretchfactor) * PRIVATE(this)->textsize;
        minx -= (maxw + stretchfactor) * PRIVATE(this)->textsize;
      }
      break;
    case SoAsciiText::RIGHT:
      if (PRIVATE(this)->lefttorighttext) {
        maxx = 0.0f;
        minx = -maxw * PRIVATE(this)->textsize; 
      }
      else {
        minx = 0.0f;
        maxx = maxw * PRIVATE(this)->textsize;      
      }
      break;
    case SoAsciiText::CENTER:
      maxx -= maxw * PRIVATE(this)->textsize * 0.5f;
      minx -= maxw * PRIVATE(this)->textsize * 0.5f;
      break;
    default:
      assert(0 && "Unknown justification");
      minx = maxx = 0.0f;
      break;
    }
    
    switch (PRIVATE(this)->justificationminor) {
    case SoAsciiText::LEFT:
      break;
    case SoAsciiText::RIGHT:
      miny += ((n-1) * PRIVATE(this)->textsize);
      maxy += ((n-1) * PRIVATE(this)->textsize);
      break;
    case SoAsciiText::CENTER:
      miny += ((n-1) * PRIVATE(this)->textsize) * 0.5f;
      maxy += ((n-1) * PRIVATE(this)->textsize) * 0.5f;
      break;
    default:
      break;
    }

  }
  else { // -- Vertical text ----------------------------------------


    if (PRIVATE(this)->lefttorighttext) {
      minx = 0.0f;
      maxx = ((n-1) * linespacing) + PRIVATE(this)->textsize;
    }
    else {
      // FIXME: This is probably not the right way of doing this. The
      // box tends to be abit larger on the right side than
      // needed. (14Aug2003 handegar)
      maxx = ((n-1) * linespacing * 0.5f) - PRIVATE(this)->textsize;
      minx = -(n+2) * linespacing * 0.5f;
    }
    

    // FIXME: The 'stretchfactor' addon for vertical text not tested
    // yet... Might be wrong but it works for horizontal
    // text. (27Aug2003 handegar)
    if (PRIVATE(this)->toptobottomtext) {
      maxy = 0.0f;
      miny = -maxstringchars*PRIVATE(this)->textsize - stretchfactor;
    }
    else {
      miny = 0.0f;
      maxy = maxstringchars + stretchfactor;
    }

    switch (PRIVATE(this)->justificationmajor) {
    case SoAsciiText::LEFT:
      break;
    case SoAsciiText::RIGHT:
      maxy += maxstringchars;
      miny += maxstringchars;
      break;
    case SoAsciiText::CENTER:
      maxy += maxstringchars * 0.5f;
      miny += maxstringchars * 0.5f;
      break;
    default:
      assert(0 && "unknown justification");
      minx = maxx = 0.0f;
      break;
    }

    switch (PRIVATE(this)->justificationminor) {
    case SoAsciiText::LEFT:
      break;
    case SoAsciiText::CENTER:      
      maxx -= ((n-1) * PRIVATE(this)->maxglyphheight) * 0.5f;
      minx -= ((n-1) * PRIVATE(this)->maxglyphheight) * 0.5f;
      break;
    case SoAsciiText::RIGHT:
      maxx -= ((n-1) * PRIVATE(this)->maxglyphheight);
      minx -= ((n-1) * PRIVATE(this)->maxglyphheight);
      break;        
    default:
      break;
    }    
 
  }
  
  box.setBounds(SbVec3f(minx, miny, 0.0f), SbVec3f(maxx, maxy, 0.0f));

  // Expanding bbox so that glyphs like 'j's and 'q's are completely inside.
  if (PRIVATE(this)->toptobottomtext) 
    box.extendBy(SbVec3f(0,PRIVATE(this)->maxglyphbbox.getMin()[1] - (n-1)*PRIVATE(this)->textsize*PRIVATE(this)->textspacing, 0));

  // FIXME: Here one must handle special cases for bottom-to-top text
  // and its minor-alignment modes (center/end) for glyphs like 'q'
  // and 'j' (20030916 handegar)

  center = box.getCenter();
}

// Doc in parent
void
SoVRMLText::generatePrimitives(SoAction * action)
{

  PRIVATE(this)->setUpGlyphs(action->getState(), this);

  int i, n = this->string.getNum();
  const float spacing = PRIVATE(this)->textspacing * PRIVATE(this)->textsize;

  SoPrimitiveVertex vertex;
  SoTextDetail detail;
  detail.setPart(0);
  vertex.setDetail(&detail);
  vertex.setMaterialIndex(0);

  this->beginShape(action, SoShape::TRIANGLES, NULL);
  vertex.setNormal(SbVec3f(0.0f, 0.0f, 1.0f));

  float ypos = 0.0f;
  int glyphidx = 0;
  int maxstringchars = 0;
  for (i = 0; i < n; ++i) 
    maxstringchars = SbMax(maxstringchars, this->string[i].getLength());


  for (i = 0; i < n; i++) {
    detail.setStringIndex(i);
    float xpos = 0.0f;
    const char * str = this->string[i].getString();
    
    float stretchlength = 0.0f;
    if (i < this->length.getNum()) 
      stretchlength = this->length[i];
    float stretchfactor = (stretchlength * PRIVATE(this)->textsize) / strlen(str);
    
    float compressfactor = 1;
    if (this->maxExtent.getValue() > 0) {
      if (PRIVATE(this)->glyphwidths[i] > this->maxExtent.getValue()) {
        assert(PRIVATE(this)->glyphwidths[i] != 0 && "String length == 0! Cannot divide");
        compressfactor = (this->maxExtent.getValue() * PRIVATE(this)->textsize) / PRIVATE(this)->glyphwidths[i];
      }
    }
    
    
    if (PRIVATE(this)->horizontaltext) { // -- Horizontal text ----------------------
      
      switch (PRIVATE(this)->justificationmajor) {
      case SoAsciiText::LEFT:
        xpos = 0.0f;
        break;
      case SoAsciiText::CENTER:
        if (PRIVATE(this)->lefttorighttext)
          xpos = - PRIVATE(this)->glyphwidths[i] * PRIVATE(this)->textsize * 0.5f;
        else
          xpos = PRIVATE(this)->glyphwidths[i] * PRIVATE(this)->textsize * 0.5f;
        break;
      case SoAsciiText::RIGHT:
        if (PRIVATE(this)->lefttorighttext) 
          xpos = -PRIVATE(this)->glyphwidths[i] * PRIVATE(this)->textsize;
        else
          xpos = PRIVATE(this)->glyphwidths[i] * PRIVATE(this)->textsize;
        break;
      default:
        break;
      }

      switch (PRIVATE(this)->justificationminor) {
      case SoAsciiText::LEFT:
        break;
      case SoAsciiText::CENTER:
        ypos = (i * spacing) + ((n-1) * spacing) * 0.5f;
        break;
      case SoAsciiText::RIGHT:
        ypos = (i * spacing) + ((n-1) * spacing);
        break;        
      default:
        break;
      }
    
    }
    else { // -- Vertical text -----------------------------------------

      if (PRIVATE(this)->lefttorighttext)
        xpos = i * spacing;
      else
        xpos = -i * spacing;
        
      switch (PRIVATE(this)->justificationmajor) {
      case SoAsciiText::LEFT:        
        ypos = -PRIVATE(this)->maxglyphheight;
        break;
      case SoAsciiText::RIGHT:
        if (PRIVATE(this)->toptobottomtext)
          ypos = this->string[i].getLength() * spacing;
        else
          ypos = -this->string[i].getLength() * spacing;
        break;
      case SoAsciiText::CENTER:
        if (PRIVATE(this)->toptobottomtext)
          ypos = this->string[i].getLength() * PRIVATE(this)->textsize * 0.5f;
        else
          ypos = -this->string[i].getLength() * PRIVATE(this)->textsize * 0.5f;
        break;
      default:
        break;
      }

      switch (PRIVATE(this)->justificationminor) {
      case SoAsciiText::LEFT:
        break;
      case SoAsciiText::CENTER:
        xpos -= ((n-1) * spacing) * PRIVATE(this)->textsize * 0.5f;
        break;
      case SoAsciiText::RIGHT:
        xpos -= ((n-1) * spacing) * PRIVATE(this)->textsize;
        break;        
      default:
        break;
      }

    }
    
    int charidx = 0;
    
    while (*str++) {
      detail.setCharacterIndex(charidx++);

      cc_glyph3d * glyph = cc_glyph3d_getglyph(*(str-1), PRIVATE(this)->fontspec);
      const SbVec2f * coords = (SbVec2f *) cc_glyph3d_getcoords(glyph);
      const int * ptr = cc_glyph3d_getfaceindices(glyph);

      float width = cc_glyph3d_getwidth(glyph);
      if (width == 0) 
        width = PRIVATE(this)->textsize / 3; // SPACE width is set to fontsize/3

      if (PRIVATE(this)->horizontaltext) {
        if (!PRIVATE(this)->lefttorighttext)
          xpos -= (width + stretchfactor) * PRIVATE(this)->textsize * compressfactor;
      }             

      while (*ptr >= 0) {
        SbVec2f v0, v1, v2;
        v0 = coords[*ptr++];
        v1 = coords[*ptr++];
        v2 = coords[*ptr++];
        vertex.setTextureCoords(SbVec2f(v0[0], v0[1]));
        vertex.setPoint(SbVec3f(v0[0] * PRIVATE(this)->textsize + xpos, v0[1] * PRIVATE(this)->textsize + ypos, 0.0f));
        this->shapeVertex(&vertex);
        vertex.setTextureCoords(SbVec2f(v1[0], v1[1]));
        vertex.setPoint(SbVec3f(v1[0] * PRIVATE(this)->textsize + xpos, v1[1] * PRIVATE(this)->textsize + ypos, 0.0f));
        this->shapeVertex(&vertex);
        vertex.setTextureCoords(SbVec2f(v2[0], v2[1]));
        vertex.setPoint(SbVec3f(v2[0] * PRIVATE(this)->textsize + xpos, v2[1] * PRIVATE(this)->textsize + ypos, 0.0f));
        this->shapeVertex(&vertex);
      }


      if (!PRIVATE(this)->horizontaltext) {       
        if (PRIVATE(this)->toptobottomtext)
          ypos -= PRIVATE(this)->textsize;
        else 
          ypos += PRIVATE(this)->textsize;       
      } else if (PRIVATE(this)->lefttorighttext)
        xpos += (width + stretchfactor) * PRIVATE(this)->textsize * compressfactor; 
    }

    if (PRIVATE(this)->horizontaltext) {
      if (PRIVATE(this)->toptobottomtext)
        ypos -= spacing * PRIVATE(this)->maxglyphheight;
      else
        ypos += spacing * PRIVATE(this)->maxglyphheight;
    }

  }

  this->endShape();
}

#undef PRIVATE


// recalculate glyphs
void
SoVRMLTextP::setUpGlyphs(SoState * state, SoVRMLText * textnode)
{
  // Note that this code is duplicated in SoText3::setUpGlyphs(), so
  // migrate bugfixes and other improvements.

  if (!this->needsetup) return;
  this->needsetup = FALSE;

  if (this->fontspec != NULL) {
    cc_fontspec_clean(this->fontspec);
    delete this->fontspec;
  }

  // Build up font-spesification struct
  this->fontspec = new cc_font_specification;

  SbString fontstr;
  switch (this->fontfamily) {
  case SoVRMLFontStyle::PLAIN: fontstr = "Times New Roman"; break;
  case SoVRMLFontStyle::SANS: fontstr = "Arial"; break;
  case SoVRMLFontStyle::TYPEWRITER: fontstr = "Courier New"; break;
  default: /* FIXME: warn on faulty input data. 20030921 mortene. */ fontstr = "defaultFont"; break;
  }

  switch (this->fontstyle) {
  case SoVRMLFontStyle::BOLD: fontstr += ":Bold"; break;
  case SoVRMLFontStyle::ITALIC: fontstr += ":Italic"; break;
  case  SoVRMLFontStyle::BOLDITALIC: fontstr += ":Bold Italic"; break;
  default: /* FIXME: check for and warn on faulty input data. 20030921 mortene. */ break;
  }

  cc_fontspec_construct(this->fontspec,
                        fontstr.getString(),
                        this->textsize,
                        this->master->getComplexityValue(state->getAction()));



  this->glyphwidths.truncate(0);

  for (int i = 0; i < textnode->string.getNum(); i++) {
    const SbString & s = textnode->string[i];
    int strlen = s.getLength();
    // Note that the "unsigned char" cast is needed to avoid 8-bit
    // chars using the highest bit (i.e. characters above the ASCII
    // set up to 127) be expanded to huge int numbers that turn
    // negative when casted to integer size.
    const unsigned char * ptr = (const unsigned char *)s.getString();
    float stringwidth = 0.0f;
    float glyphwidth = 0.0f;
    const float * maxbbox;
    this->maxglyphbbox.makeEmpty();

    for (int j = 0; j < strlen; j++) {
   
      cc_glyph3d * glyph = cc_glyph3d_getglyph(ptr[j], this->fontspec);
      assert(glyph);

      maxbbox = cc_glyph3d_getboundingbox(glyph); // Get max height
      this->maxglyphbbox.extendBy(SbVec3f(0, maxbbox[0], 0));
      this->maxglyphbbox.extendBy(SbVec3f(0, maxbbox[1], 0));

      glyphwidth = cc_glyph3d_getwidth(glyph);
      if (glyphwidth == 0)
        glyphwidth = this->textsize/3; // SPACE width is always == 0.

      stringwidth += glyphwidth;
            
    }
    this->glyphwidths.append(stringwidth);
  }

}

void 
fontstylechangeCB(void * data, SoSensor * sensor)
{

  SoVRMLTextP * pimpl = (SoVRMLTextP *) data;

  SoVRMLFontStyle * fs = (SoVRMLFontStyle*) pimpl->master->fontStyle.getValue();
  if (!fs) {
    pimpl->textsize = 1.0f;
    pimpl->textspacing = 1.0f;
    pimpl->lefttorighttext = TRUE;
    pimpl->toptobottomtext = TRUE;
    pimpl->horizontaltext = TRUE;
    pimpl->justificationmajor = SoAsciiText::LEFT;
    pimpl->justificationminor = SoAsciiText::LEFT;
    pimpl->fontfamily = SoVRMLFontStyle::SERIF;
    pimpl->fontstyle = SoVRMLFontStyle::PLAIN;
    return;
  }

  // Major mode
  if (!strcmp(fs->justify[0].getString(),"BEGIN") || 
      !strcmp(fs->justify[0].getString(),"FIRST") ||
      (fs->justify[0].getLength() == 0)) {
    pimpl->justificationmajor = SoAsciiText::LEFT;  
  } 
  else if (!strcmp(fs->justify[0].getString(),"MIDDLE")) {
    pimpl->justificationmajor = SoAsciiText::CENTER;
  } 
  else if (!strcmp(fs->justify[0].getString(),"END")) {
    pimpl->justificationmajor = SoAsciiText::RIGHT;
  }
    
  // Minor mode
  if (fs->justify.getNum() > 1) {
    if (!strcmp(fs->justify[1].getString(),"BEGIN") || 
        !strcmp(fs->justify[1].getString(),"FIRST") ||
        (fs->justify[1].getLength() == 0))
      pimpl->justificationminor = SoAsciiText::LEFT;  
    else if (!strcmp(fs->justify[1].getString(),"MIDDLE")) 
      pimpl->justificationminor = SoAsciiText::CENTER;
    else if (!strcmp(fs->justify[1].getString(),"END")) 
      pimpl->justificationminor = SoAsciiText::RIGHT;
  }
  
  pimpl->lefttorighttext = fs->leftToRight.getValue();
  pimpl->toptobottomtext = fs->topToBottom.getValue();
  pimpl->horizontaltext = fs->horizontal.getValue();
  pimpl->textsize = fs->size.getValue();
  pimpl->textspacing = fs->spacing.getValue();

  pimpl->fontfamily = SoVRMLFontStyle::SERIF;
  pimpl->fontstyle = SoVRMLFontStyle::PLAIN;

  const char * family = fs->family[0].getString();
  if (strlen(family) != 0) {
    if (!strcmp(family, "SERIF"))
      pimpl->fontfamily = SoVRMLFontStyle::SERIF;
    else if (!strcmp(family, "SANS"))
      pimpl->fontfamily = SoVRMLFontStyle::SANS;
    else if (!strcmp(family, "TYPEWRITER"))
      pimpl->fontfamily = SoVRMLFontStyle::TYPEWRITER;
  }
      
  const char * style = fs->style[0].getString();
  if (strlen(style) != 0) {
    if (!strcmp(style, "PLAIN"))
      pimpl->fontstyle = SoVRMLFontStyle::PLAIN;
    else if (!strcmp(style, "BOLD"))
      pimpl->fontstyle = SoVRMLFontStyle::BOLD;
    else if (!strcmp(style, "ITALIC"))
      pimpl->fontstyle = SoVRMLFontStyle::ITALIC;
    else if (!strcmp(style, "BOLDITALIC"))
      pimpl->fontstyle = SoVRMLFontStyle::BOLDITALIC;
  }

  pimpl->needsetup = TRUE;

}
