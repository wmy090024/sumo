/****************************************************************************/
// Eclipse SUMO, Simulation of Urban MObility; see https://eclipse.org/sumo
// Copyright (C) 2001-2020 German Aerospace Center (DLR) and others.
// This program and the accompanying materials are made available under the
// terms of the Eclipse Public License 2.0 which is available at
// https://www.eclipse.org/legal/epl-2.0/
// This Source Code may also be made available under the following Secondary
// Licenses when the conditions for such availability set forth in the Eclipse
// Public License 2.0 are satisfied: GNU General Public License, version 2
// or later which is available at
// https://www.gnu.org/licenses/old-licenses/gpl-2.0-standalone.html
// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
/****************************************************************************/
/// @file    GNEMove.cpp
/// @author  Pablo Alvarez Lopez
/// @date    Mar 2020
///
// Class used for move shape elements
/****************************************************************************/
#include <netedit/elements/network/GNEEdge.h>
#include <netedit/changes/GNEChange_Attribute.h>
#include <netedit/GNEUndoList.h>

#include "GNEMoveElement.h"


void 
GNEMoveElement::moveElement(GNEMoveOperation* moveOperation, const Position &offset) {
    // calculate new shape
    PositionVector newShape = moveOperation->geometryToMove.getShape();
    for (const auto &index : moveOperation->geometryPointsToMove) {
        newShape[index].add(offset);
    }
    // move shape element
    moveOperation->moveElement->setMoveShape(newShape);
}


void 
GNEMoveElement::commitMove(GNEMoveOperation* moveOperation, const Position &offset, GNEUndoList* undoList) {
    // first restore original geometry geometry
    moveOperation->moveElement->setMoveShape(moveOperation->originalGeometry.getShape());
    // calculate new shape
    PositionVector newShape = moveOperation->geometryToMove.getShape();
    for (const auto &index : moveOperation->geometryPointsToMove) {
        newShape[index].add(offset);
    }
    // commit move shape
    moveOperation->moveElement->commitMoveShape(newShape, undoList);
}

/****************************************************************************/
