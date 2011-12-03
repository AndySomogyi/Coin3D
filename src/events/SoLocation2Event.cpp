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
  \class SoLocation2Event SoLocation2Event.h Inventor/events/SoLocation2Event.h
  \brief The SoLocation2Event class contains information about 2D movement
  events.
  \ingroup events

  Location2 events are generated by devices capable of 2D, e.g. pointer
  devices -- typically computer mice. Instances of this class contains
  information about the position of the pointer on the render area.

  SoLocation2Event does not contain any new information versus its
  superclass, its sole purpose is to make it possible to specify the
  type of the event for event object receivers in the scene graph.

  \sa SoEvent, SoMotion3Event
  \sa SoEventCallback, SoHandleEventAction */

#include <Inventor/events/SoLocation2Event.h>
#include <Inventor/SbName.h>
#include <cassert>


SO_EVENT_SOURCE(SoLocation2Event);

/*!
  Initialize the type information data.
 */
void
SoLocation2Event::initClass(void)
{
  SO_EVENT_INIT_CLASS(SoLocation2Event, SoEvent);
}

/*!
  Constructor.
*/
SoLocation2Event::SoLocation2Event(void)
{
}

/*!
  Destructor.
 */
SoLocation2Event::~SoLocation2Event()
{
}
