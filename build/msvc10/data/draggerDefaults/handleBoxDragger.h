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

#ifndef COIN_INTERNAL
#error this is a private header file
#endif /* !COIN_INTERNAL */

#ifndef SO_HANDLEBOXDRAGGER_IV_H
#define SO_HANDLEBOXDRAGGER_IV_H

static const char HANDLEBOXDRAGGER_draggergeometry[] =
  "#Inventor V2.1 ascii\n"
  "\n"
  "\n"
  "\n"
  "DEF HANDLEBOX_INACTIVE_MATERIAL Material { diffuseColor 0.5 0.5 0.5  emissiveColor 0.5 0.5 0.5 }\n"
  "DEF HANDLEBOX_ACTIVE_MATERIAL Material { diffuseColor 0.5 0.5 0  emissiveColor 0.5 0.5 0 }\n"
  "DEF HANDLEBOX_FEEDBACK_MATERIAL Material { diffuseColor 0.5 0 0.5  emissiveColor 0.5 0 0.5 }\n"
  "\n"
  "\n"
  "\n"
  "\n"
  "\n"
  "\n"
  "\n"
  "\n"
  "\n"
  "\n"
  "\n"
  "\n"
  "DEF HANDLEBOX_TRANSLATOR_COORDS Coordinate3 {\n"
  "   point [\n"
  "    1 1 1, 1 1 -1, -1 1 -1, -1 1 1,\n"
  "    1 -1 1, 1 -1 -1, -1 -1 -1, -1 -1 1,\n"
  "   ]\n"
  "}\n"
  "\n"
  "DEF HANDLEBOX_TRANSLATOR_INACTIVE_APPEARANCE Group {\n"
  "   USE HANDLEBOX_INACTIVE_MATERIAL\n"
  "   USE HANDLEBOX_TRANSLATOR_COORDS\n"
  "   DrawStyle { style LINES }\n"
  "}\n"
  "DEF HANDLEBOX_TRANSLATOR_ACTIVE_APPEARANCE Group {\n"
  "   USE HANDLEBOX_ACTIVE_MATERIAL\n"
  "   USE HANDLEBOX_TRANSLATOR_COORDS\n"
  "   DrawStyle { style LINES }\n"
  "}\n"
  "\n"
  "DEF handleBoxTranslator1 Separator {\n"
  "   USE HANDLEBOX_TRANSLATOR_INACTIVE_APPEARANCE\n"
  "   DEF HANDLEBOX_TRANSLATOR_TOPFACE IndexedFaceSet { coordIndex [ 0, 1, 2, 3, -1 ] }\n"
  "}\n"
  "DEF handleBoxTranslator1Active Separator {\n"
  "   USE HANDLEBOX_TRANSLATOR_ACTIVE_APPEARANCE\n"
  "   USE HANDLEBOX_TRANSLATOR_TOPFACE\n"
  "}\n"
  "\n"
  "DEF handleBoxTranslator2 Separator {\n"
  "   USE HANDLEBOX_TRANSLATOR_INACTIVE_APPEARANCE\n"
  "   DEF HANDLEBOX_TRANSLATOR_BOTTOMFACE IndexedFaceSet { coordIndex [ 4, 7, 6, 5, -1 ] }\n"
  "}\n"
  "DEF handleBoxTranslator2Active Separator {\n"
  "   USE HANDLEBOX_TRANSLATOR_ACTIVE_APPEARANCE\n"
  "   USE HANDLEBOX_TRANSLATOR_BOTTOMFACE\n"
  "}\n"
  "\n"
  "DEF handleBoxTranslator3 Separator {\n"
  "   USE HANDLEBOX_TRANSLATOR_INACTIVE_APPEARANCE\n"
  "   DEF HANDLEBOX_TRANSLATOR_LEFTFACE IndexedFaceSet { coordIndex [ 3, 2, 6, 7, -1 ] }\n"
  "}\n"
  "DEF handleBoxTranslator3Active Separator {\n"
  "   USE HANDLEBOX_TRANSLATOR_ACTIVE_APPEARANCE\n"
  "   USE HANDLEBOX_TRANSLATOR_LEFTFACE\n"
  "}\n"
  "\n"
  "DEF handleBoxTranslator4 Separator {\n"
  "   USE HANDLEBOX_TRANSLATOR_INACTIVE_APPEARANCE\n"
  "   DEF HANDLEBOX_TRANSLATOR_RIGHTFACE IndexedFaceSet { coordIndex [ 0, 4, 5, 1, -1 ] }\n"
  "}\n"
  "DEF handleBoxTranslator4Active Separator {\n"
  "   USE HANDLEBOX_TRANSLATOR_ACTIVE_APPEARANCE\n"
  "   USE HANDLEBOX_TRANSLATOR_RIGHTFACE\n"
  "}\n"
  "\n"
  "DEF handleBoxTranslator5 Separator {\n"
  "   USE HANDLEBOX_TRANSLATOR_INACTIVE_APPEARANCE\n"
  "   DEF HANDLEBOX_TRANSLATOR_FRONTFACE IndexedFaceSet { coordIndex [ 0, 3, 7, 4, -1 ] }\n"
  "}\n"
  "DEF handleBoxTranslator5Active Separator {\n"
  "   USE HANDLEBOX_TRANSLATOR_ACTIVE_APPEARANCE\n"
  "   USE HANDLEBOX_TRANSLATOR_FRONTFACE\n"
  "}\n"
  "\n"
  "DEF handleBoxTranslator6 Separator {\n"
  "   USE HANDLEBOX_TRANSLATOR_INACTIVE_APPEARANCE\n"
  "   DEF HANDLEBOX_TRANSLATOR_BACKFACE IndexedFaceSet { coordIndex [ 1, 5, 6, 2, -1 ] }\n"
  "}\n"
  "DEF handleBoxTranslator6Active Separator {\n"
  "   USE HANDLEBOX_TRANSLATOR_ACTIVE_APPEARANCE\n"
  "   USE HANDLEBOX_TRANSLATOR_BACKFACE\n"
  "}\n"
  "\n"
  "\n"
  "\n"
  "\n"
  "\n"
  "\n"
  "DEF HANDLEBOX_DIRECTIONMARKER Group {\n"
  "   USE HANDLEBOX_FEEDBACK_MATERIAL\n"
  "   Coordinate3 { point [ 0 0 0, 0 0.5 0 ] }\n"
  "   IndexedLineSet { coordIndex [ 0, 1, -1 ] }\n"
  "   Translation { translation 0 0.5 0 }\n"
  "   Cone { bottomRadius 0.04  height 0.08 }\n"
  "}\n"
  "\n"
  "DEF handleBoxArrow1 Separator {\n"
  "   USE HANDLEBOX_DIRECTIONMARKER\n"
  "}\n"
  "DEF handleBoxArrow2 Separator {\n"
  "   RotationXYZ { axis Z angle 3.14 }\n"
  "   USE HANDLEBOX_DIRECTIONMARKER\n"
  "}\n"
  "DEF handleBoxArrow3 Separator {\n"
  "   RotationXYZ { axis Z angle 1.57 }\n"
  "   USE HANDLEBOX_DIRECTIONMARKER\n"
  "}\n"
  "DEF handleBoxArrow4 Separator {\n"
  "   RotationXYZ { axis Z angle -1.57 }\n"
  "   USE HANDLEBOX_DIRECTIONMARKER\n"
  "}\n"
  "DEF handleBoxArrow5 Separator {\n"
  "   RotationXYZ { axis X angle 1.57 }\n"
  "   USE HANDLEBOX_DIRECTIONMARKER\n"
  "}\n"
  "DEF handleBoxArrow6 Separator {\n"
  "   RotationXYZ { axis X angle -1.57 }\n"
  "   USE HANDLEBOX_DIRECTIONMARKER\n"
  "}\n"
  "\n"
  "\n"
  "\n"
  "\n"
  "\n"
  "\n"
  "DEF HANDLEBOX_SOLIDMARKER Cube { width 0.1  height 0.1  depth 0.1 }\n"
  "\n"
  "\n"
  "DEF HANDLEBOX_CORNER_URF Group {\n"
  "   Translation { translation 1 1 1 }\n"
  "   USE HANDLEBOX_SOLIDMARKER\n"
  "}\n"
  "DEF handleBoxUniform1 Separator {\n"
  "   USE HANDLEBOX_INACTIVE_MATERIAL\n"
  "   USE HANDLEBOX_CORNER_URF\n"
  "}\n"
  "DEF handleBoxUniform1Active Separator {\n"
  "   USE HANDLEBOX_ACTIVE_MATERIAL\n"
  "   USE HANDLEBOX_CORNER_URF\n"
  "}\n"
  "\n"
  "\n"
  "DEF HANDLEBOX_CORNER_URB Group {\n"
  "   Translation { translation 1 1 -1 }\n"
  "   USE HANDLEBOX_SOLIDMARKER\n"
  "}\n"
  "DEF handleBoxUniform2 Separator {\n"
  "   USE HANDLEBOX_INACTIVE_MATERIAL\n"
  "   USE HANDLEBOX_CORNER_URB\n"
  "}\n"
  "DEF handleBoxUniform2Active Separator {\n"
  "   USE HANDLEBOX_ACTIVE_MATERIAL\n"
  "   USE HANDLEBOX_CORNER_URB\n"
  "}\n"
  "\n"
  "\n"
  "DEF HANDLEBOX_CORNER_DRF Group {\n"
  "   Translation { translation 1 -1 1 }\n"
  "   USE HANDLEBOX_SOLIDMARKER\n"
  "}\n"
  "DEF handleBoxUniform3 Separator {\n"
  "   USE HANDLEBOX_INACTIVE_MATERIAL\n"
  "   USE HANDLEBOX_CORNER_DRF\n"
  "}\n"
  "DEF handleBoxUniform3Active Separator {\n"
  "   USE HANDLEBOX_ACTIVE_MATERIAL\n"
  "   USE HANDLEBOX_CORNER_DRF\n"
  "}\n"
  "\n"
  "\n"
  "DEF HANDLEBOX_CORNER_DRB Group {\n"
  "   Translation { translation 1 -1 -1 }\n"
  "   USE HANDLEBOX_SOLIDMARKER\n"
  "}\n"
  "DEF handleBoxUniform4 Separator {\n"
  "   USE HANDLEBOX_INACTIVE_MATERIAL\n"
  "   USE HANDLEBOX_CORNER_DRB\n"
  "}\n"
  "DEF handleBoxUniform4Active Separator {\n"
  "   USE HANDLEBOX_ACTIVE_MATERIAL\n"
  "   USE HANDLEBOX_CORNER_DRB\n"
  "}\n"
  "\n"
  "\n"
  "DEF HANDLEBOX_CORNER_ULF Group {\n"
  "   Translation { translation -1 1 1 }\n"
  "   USE HANDLEBOX_SOLIDMARKER\n"
  "}\n"
  "DEF handleBoxUniform5 Separator {\n"
  "   USE HANDLEBOX_INACTIVE_MATERIAL\n"
  "   USE HANDLEBOX_CORNER_ULF\n"
  "}\n"
  "DEF handleBoxUniform5Active Separator {\n"
  "   USE HANDLEBOX_ACTIVE_MATERIAL\n"
  "   USE HANDLEBOX_CORNER_ULF\n"
  "}\n"
  "\n"
  "\n"
  "DEF HANDLEBOX_CORNER_ULB Group {\n"
  "   Translation { translation -1 1 -1 }\n"
  "   USE HANDLEBOX_SOLIDMARKER\n"
  "}\n"
  "DEF handleBoxUniform6 Separator {\n"
  "   USE HANDLEBOX_INACTIVE_MATERIAL\n"
  "   USE HANDLEBOX_CORNER_ULB\n"
  "}\n"
  "DEF handleBoxUniform6Active Separator {\n"
  "   USE HANDLEBOX_ACTIVE_MATERIAL\n"
  "   USE HANDLEBOX_CORNER_ULB\n"
  "}\n"
  "\n"
  "\n"
  "DEF HANDLEBOX_CORNER_DLF Group {\n"
  "   Translation { translation -1 -1 1 }\n"
  "   USE HANDLEBOX_SOLIDMARKER\n"
  "}\n"
  "DEF handleBoxUniform7 Separator {\n"
  "   USE HANDLEBOX_INACTIVE_MATERIAL\n"
  "   USE HANDLEBOX_CORNER_DLF\n"
  "}\n"
  "DEF handleBoxUniform7Active Separator {\n"
  "   USE HANDLEBOX_ACTIVE_MATERIAL\n"
  "   USE HANDLEBOX_CORNER_DLF\n"
  "}\n"
  "\n"
  "\n"
  "DEF HANDLEBOX_CORNER_DLB Group {\n"
  "   Translation { translation -1 -1 -1 }\n"
  "   USE HANDLEBOX_SOLIDMARKER\n"
  "}\n"
  "DEF handleBoxUniform8 Separator {\n"
  "   USE HANDLEBOX_INACTIVE_MATERIAL\n"
  "   USE HANDLEBOX_CORNER_DLB\n"
  "}\n"
  "DEF handleBoxUniform8Active Separator {\n"
  "   USE HANDLEBOX_ACTIVE_MATERIAL\n"
  "   USE HANDLEBOX_CORNER_DLB\n"
  "}\n"
  "\n"
  "\n"
  "\n"
  "\n"
  "\n"
  "\n"
  "\n"
  "\n"
  "\n"
  "\n"
  "DEF HANDLEBOX_EXTRUSION_COORDS Coordinate3 {\n"
  "   point [\n"
  "    0 0 0,\n"
  "    1.3 0 0, -1.3 0 0,\n"
  "    0 1.3 0, 0 -1.3 0,\n"
  "    0 0 1.3, 0 0 -1.3\n"
  "   ]\n"
  "}\n"
  "\n"
  "DEF HANDLEBOX_EXTRUSION_MARKER_UP Group {\n"
  "   USE HANDLEBOX_EXTRUSION_COORDS\n"
  "   IndexedLineSet { coordIndex [ 0, 3, -1 ] }\n"
  "   Translation { translation 0 1.3 0 }\n"
  "   USE HANDLEBOX_SOLIDMARKER\n"
  "}\n"
  "DEF handleBoxExtruder1 Separator {\n"
  "   USE HANDLEBOX_INACTIVE_MATERIAL\n"
  "   USE HANDLEBOX_EXTRUSION_MARKER_UP\n"
  "}\n"
  "DEF handleBoxExtruder1Active Separator {\n"
  "   USE HANDLEBOX_ACTIVE_MATERIAL\n"
  "   USE HANDLEBOX_EXTRUSION_MARKER_UP\n"
  "}\n"
  "\n"
  "DEF HANDLEBOX_EXTRUSION_MARKER_DOWN Group {\n"
  "   USE HANDLEBOX_EXTRUSION_COORDS\n"
  "   IndexedLineSet { coordIndex [ 0, 4, -1 ] }\n"
  "   Translation { translation 0 -1.3 0 }\n"
  "   USE HANDLEBOX_SOLIDMARKER\n"
  "}\n"
  "DEF handleBoxExtruder2 Separator {\n"
  "   USE HANDLEBOX_INACTIVE_MATERIAL\n"
  "   USE HANDLEBOX_EXTRUSION_MARKER_DOWN\n"
  "}\n"
  "DEF handleBoxExtruder2Active Separator {\n"
  "   USE HANDLEBOX_ACTIVE_MATERIAL\n"
  "   USE HANDLEBOX_EXTRUSION_MARKER_DOWN\n"
  "}\n"
  "\n"
  "DEF HANDLEBOX_EXTRUSION_MARKER_LEFT Group {\n"
  "   USE HANDLEBOX_EXTRUSION_COORDS\n"
  "   IndexedLineSet { coordIndex [ 0, 2, -1 ] }\n"
  "   Translation { translation -1.3 0 0 }\n"
  "   USE HANDLEBOX_SOLIDMARKER\n"
  "}\n"
  "DEF handleBoxExtruder3 Separator {\n"
  "   USE HANDLEBOX_INACTIVE_MATERIAL\n"
  "   USE HANDLEBOX_EXTRUSION_MARKER_LEFT\n"
  "}\n"
  "DEF handleBoxExtruder3Active Separator {\n"
  "   USE HANDLEBOX_ACTIVE_MATERIAL\n"
  "   USE HANDLEBOX_EXTRUSION_MARKER_LEFT\n"
  "}\n"
  "\n"
  "DEF HANDLEBOX_EXTRUSION_MARKER_RIGHT Group {\n"
  "   USE HANDLEBOX_EXTRUSION_COORDS\n"
  "   IndexedLineSet { coordIndex [ 0, 1, -1 ] }\n"
  "   Translation { translation 1.3 0 0 }\n"
  "   USE HANDLEBOX_SOLIDMARKER\n"
  "}\n"
  "DEF handleBoxExtruder4 Separator {\n"
  "   USE HANDLEBOX_INACTIVE_MATERIAL\n"
  "   USE HANDLEBOX_EXTRUSION_MARKER_RIGHT\n"
  "}\n"
  "DEF handleBoxExtruder4Active Separator {\n"
  "   USE HANDLEBOX_ACTIVE_MATERIAL\n"
  "   USE HANDLEBOX_EXTRUSION_MARKER_RIGHT\n"
  "}\n"
  "\n"
  "DEF HANDLEBOX_EXTRUSION_MARKER_FRONT Group {\n"
  "   USE HANDLEBOX_EXTRUSION_COORDS\n"
  "   IndexedLineSet { coordIndex [ 0, 5, -1 ] }\n"
  "   Translation { translation 0 0 1.3 }\n"
  "   USE HANDLEBOX_SOLIDMARKER\n"
  "}\n"
  "DEF handleBoxExtruder5 Separator {\n"
  "   USE HANDLEBOX_INACTIVE_MATERIAL\n"
  "   USE HANDLEBOX_EXTRUSION_MARKER_FRONT\n"
  "}\n"
  "DEF handleBoxExtruder5Active Separator {\n"
  "   USE HANDLEBOX_ACTIVE_MATERIAL\n"
  "   USE HANDLEBOX_EXTRUSION_MARKER_FRONT\n"
  "}\n"
  "\n"
  "DEF HANDLEBOX_EXTRUSION_MARKER_BACK Group {\n"
  "   USE HANDLEBOX_EXTRUSION_COORDS\n"
  "   IndexedLineSet { coordIndex [ 0, 6, -1 ] }\n"
  "   Translation { translation 0 0 -1.3 }\n"
  "   USE HANDLEBOX_SOLIDMARKER\n"
  "}\n"
  "DEF handleBoxExtruder6 Separator {\n"
  "   USE HANDLEBOX_INACTIVE_MATERIAL\n"
  "   USE HANDLEBOX_EXTRUSION_MARKER_BACK\n"
  "}\n"
  "DEF handleBoxExtruder6Active Separator {\n"
  "   USE HANDLEBOX_ACTIVE_MATERIAL\n"
  "   USE HANDLEBOX_EXTRUSION_MARKER_BACK\n"
  "}\n";

#endif /* ! SO_HANDLEBOXDRAGGER_IV_H */
