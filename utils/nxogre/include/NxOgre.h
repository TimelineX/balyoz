/** File: NxOgre.h
    Created on: 24-Aug-09
    Author: Robin Southern "betajaen"
    SVN: $Id$
    This is an automatically created file.

    (c) Copyright, 2008-2009 by Robin Southern, http://www.nxogre.org

    This file is part of NxOgre.

    NxOgre is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    NxOgre is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with NxOgre.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef NXOGRE_H
#define NXOGRE_H

#include <bml/bml.h>
#include "NxOgreAccumulativeSceneTimer.h"
#include "NxOgreActiveParticle.h"
#include "NxOgreActor.h"
#include "NxOgreActorMachinePart.h"
#include "NxOgreArchive.h"
#include "NxOgreArchiveResourceIdentifier.h"
#include "NxOgreArray.h"
#include "NxOgreBox.h"
#include "NxOgreBuffer.h"
#include "NxOgreCallback.h"
#include "NxOgreCapsule.h"
#include "NxOgreCircularBuffer.h"
#include "NxOgreClasses.h"
#include "NxOgreCloth.h"
#include "NxOgreClothDescription.h"
#include "NxOgreCommon.h"
#include "NxOgreCompartment.h"
#include "NxOgreCompartmentDescription.h"
#include "NxOgreCompiler.h"
#include "NxOgreContactPair.h"
#include "NxOgreConvex.h"
#include "NxOgreD6Joint.h"
#include "NxOgreD6JointDescription.h"
#include "NxOgreEntityReport.h"
#include "NxOgreErrorStream.h"
#include "NxOgreFixedJoint.h"
#include "NxOgreFixedSceneTimer.h"
#include "NxOgreFluid.h"
#include "NxOgreFluidDescription.h"
#include "NxOgreFunctions.h"
#include "NxOgreHeightField.h"
#include "NxOgreHeightFieldGeometry.h"
#include "NxOgreHeightFieldGeometryBlueprint.h"
#include "NxOgreHeightFieldManager.h"
#include "NxOgreHeightFieldSample.h"
#include "NxOgreIntVectors.h"
#include "NxOgreJoint.h"
#include "NxOgreJointDescription.h"
#include "NxOgreJointDriveDescription.h"
#include "NxOgreJointFunctions.h"
#include "NxOgreJointLimitDescription.h"
#include "NxOgreJointLimitSoftDescription.h"
#include "NxOgreKinematicActor.h"
#include "NxOgreKinematicController.h"
#include "NxOgreKinematicFunctions.h"
#include "NxOgreMachine.h"
#include "NxOgreMachinePart.h"
#include "NxOgreManualHeightField.h"
#include "NxOgreManualMesh.h"
#include "NxOgreMaterial.h"
#include "NxOgreMaterialDescription.h"
#include "NxOgreMaterialPrototype.h"
#include "NxOgreMath.h"
#include "NxOgreMatrix.h"
#include "NxOgreMemory.h"
#include "NxOgreMemoryArchive.h"
#include "NxOgreMemoryDebugger.h"
#include "NxOgreMemoryResource.h"
#include "NxOgreMemoryResourceProtocol.h"
#include "NxOgreMesh.h"
#include "NxOgreMeshFunctions.h"
#include "NxOgreMeshManager.h"
#include "NxOgreMeshStats.h"
#include "NxOgreMotorDescription.h"
#include "NxOgreMSWindowsFileArchive.h"
#include "NxOgreMSWindowsFileResource.h"
#include "NxOgreMSWindowsFileResourceProtocol.h"
#include "NxOgreNodeRenderable.h"
#include "NxOgreNXSFunctions.h"
#include "NxOgreParticleData.h"
#include "NxOgrePhysXCallback.h"
#include "NxOgrePhysXMeshData.h"
#include "NxOgrePhysXOutputStream.h"
#include "NxOgrePhysXPointer.h"
#include "NxOgrePhysXPrototypes.h"
#include "NxOgrePhysXRaycastReport.h"
#include "NxOgrePhysXStream.h"
#include "NxOgrePhysXUserAllocator.h"
#include "NxOgrePhysXUserEntityReport.h"
#include "NxOgrePlaneGeometry.h"
#include "NxOgrePointerClass.h"
#include "NxOgrePointRenderable.h"
#include "NxOgrePrototypeFunctions.h"
#include "NxOgreRay.h"
#include "NxOgreRaycastHit.h"
#include "NxOgreReason.h"
#include "NxOgreRemoteDebugger.h"
#include "NxOgreRemoteDebuggerListener.h"
#include "NxOgreRenderable.h"
#include "NxOgreResource.h"
#include "NxOgreResourceProtocol.h"
#include "NxOgreResourceSystem.h"
#include "NxOgreRestingParticle.h"
#include "NxOgreRevoluteJoint.h"
#include "NxOgreRevoluteJointDescription.h"
#include "NxOgreRigidBody.h"
#include "NxOgreRigidBodyDescription.h"
#include "NxOgreRigidBodyDynamicFunctions.h"
#include "NxOgreRigidBodyFunctions.h"
#include "NxOgreRigidBodyPrototype.h"
#include "NxOgreScene.h"
#include "NxOgreSceneDescription.h"
#include "NxOgreSceneGeometry.h"
#include "NxOgreScenePrototype.h"
#include "NxOgreSceneRenderable.h"
#include "NxOgreSceneRenderer.h"
#include "NxOgreSceneTimer.h"
#include "NxOgreShape.h"
#include "NxOgreShapeBlueprint.h"
#include "NxOgreSharedBuffer.h"
#include "NxOgreSharedPointer.h"
#include "NxOgreSharedStringStream.h"
#include "NxOgreSimple.h"
#include "NxOgreSingleton.h"
#include "NxOgreSoftBody.h"
#include "NxOgreSoftBodyDescription.h"
#include "NxOgreSoftBodyMesh.h"
#include "NxOgreSphere.h"
#include "NxOgreSphericalJoint.h"
#include "NxOgreSphericalJointDescription.h"
#include "NxOgreSpringDescription.h"
#include "NxOgreStable.h"
#include "NxOgreString.h"
#include "NxOgreTimeController.h"
#include "NxOgreTimeListener.h"
#include "NxOgreTimeStep.h"
#include "NxOgreTireFunction.h"
#include "NxOgreTriangle.h"
#include "NxOgreTriangleGeometry.h"
#include "NxOgreTuple.h"
#include "NxOgreUniformResourceIdentifier.h"
#include "NxOgreUtil.h"
#include "NxOgreVec.h"
#include "NxOgreVertex.h"
#include "NxOgreVisualDebugger.h"
#include "NxOgreVisualDebuggerMeshData.h"
#include "NxOgreVolume.h"
#include "NxOgreWheel.h"
#include "NxOgreWheelBlueprint.h"
#include "NxOgreWheelMachinePart.h"
#include "NxOgreWorld.h"
#include "NxOgreWorldDescription.h"
#include "NxOgreWorldPrototype.h"
#include "NxOgreXFunctions.h"
#include "NxOgreConfiguration.h"
#include "NxOgrePhysXProtoypesTest.h"
#include "NxOgreProtoypesTest.h"

#endif
