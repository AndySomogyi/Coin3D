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

#include <Inventor/nodes/SoTexture.h>

/*!
  SoTexture SoTexture.h Inventor/nodes/SoTexture.h
  \brief Common base class for texture nodes.

  \ingroup nodes
  \COIN_CLASS_EXTENSION
  \since Coin 3.0
*/

SO_NODE_ABSTRACT_SOURCE(SoTexture);

void
SoTexture::initClass(void)
{
  SO_NODE_INIT_ABSTRACT_CLASS(SoTexture, SoNode, Node);
}

void
SoTexture::cleanupClass(void)
{
}

SoTexture::SoTexture(void)
{
  SO_NODE_CONSTRUCTOR(SoTexture);
}

SoTexture::~SoTexture(void)
{
}

void
SoTexture::doAction(SoAction * action)
{
  inherited::doAction(action);
}

void
SoTexture::GLRender(SoGLRenderAction * action)
{
  inherited::GLRender(action);
}

void
SoTexture::callback(SoCallbackAction * action)
{
  inherited::callback(action);
}
