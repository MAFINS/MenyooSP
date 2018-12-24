/*
* Menyoo PC - Grand Theft Auto V single-player trainer mod
* Copyright (C) 2019  MAFINS
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*/
#include "SpoonerMarker.h"

#include "..\..\macros.h"

//#include "..\..\Menu\Menu.h"
//#include "..\..\Menu\Routine.h"

//#include "..\..\Natives\natives2.h"
#include "..\..\Util\GTAmath.h"
#include "..\..\Scripting\GTAentity.h"
#include "..\..\Natives\types.h" //RGBA
#include "..\..\Scripting\enums.h"

namespace sub::Spooner
{
	// SpoonerMarker

	SpoonerMarker::SpoonerMarker()
	{
		SpoonerMarker::iMarkerIdIter++;
		this->m_id = SpoonerMarker::iMarkerIdIter;
		//this->m_name = name;
		this->m_type = MarkerType::UpsideDownCone;
		this->m_scale = 0.9f;
		this->m_showName = false;
		this->m_rotateContinuously = true;
		this->m_allowVehicles = false;
		this->m_colour = RGBA(102, 0, 204, 190);
		this->m_selectedInSub = false;
		this->m_destinationPtr = nullptr;
	}
	SpoonerMarker::SpoonerMarker(const std::string& name, const Vector3& pos, const Vector3& rot)
	{
		SpoonerMarker::iMarkerIdIter++;
		this->m_id = SpoonerMarker::iMarkerIdIter;
		this->m_name = name;
		this->m_type = MarkerType::UpsideDownCone;
		this->m_scale = 0.9f;
		this->m_showName = false;
		this->m_rotateContinuously = true;
		this->m_allowVehicles = false;
		this->m_selectedInSub = false;
		this->m_colour = RGBA(102, 0, 204, 190);
		this->m_position = pos;
		this->m_rotation = rot;
		this->m_destinationHeading = round(rot.z);
		this->m_destinationPtr = nullptr;
	}

	bool operator == (const SpoonerMarker& left, const SpoonerMarker& right)
	{
		return
			left.m_name == right.m_name &&
			left.m_type == right.m_type &&
			left.m_scale == right.m_scale &&
			left.m_showName == right.m_showName &&
			left.m_rotateContinuously == right.m_rotateContinuously &&
			left.m_allowVehicles == right.m_allowVehicles &&
			left.m_colour == right.m_colour &&
			(left.m_attachmentArgs.attachedTo != right.m_attachmentArgs.attachedTo ?
				left.m_position == right.m_position &&
				left.m_rotation == right.m_rotation
				: true) &&
			left.m_attachmentArgs.attachedTo == right.m_attachmentArgs.attachedTo &&
			left.m_attachmentArgs.offset == right.m_attachmentArgs.offset &&
			left.m_attachmentArgs.rotation == right.m_attachmentArgs.rotation;
	}
	SpoonerMarker& SpoonerMarker::operator = (const SpoonerMarker& right)
	{
		this->m_name = right.m_name;
		this->m_type = right.m_type;
		this->m_scale = right.m_scale;
		this->m_showName = right.m_showName;
		this->m_rotateContinuously = right.m_rotateContinuously;
		this->m_allowVehicles = right.m_allowVehicles;
		this->m_selectedInSub = right.m_selectedInSub;
		this->m_colour = right.m_colour;
		this->m_position = right.m_position;
		this->m_rotation = right.m_rotation;
		this->m_destinationVal = right.m_destinationVal;
		this->m_destinationPtr = right.m_destinationPtr;
		this->m_destinationHeading = right.m_destinationHeading;
		this->m_attachmentArgs = right.m_attachmentArgs;
		return *this;
	}

	
	bool SpoonerMarker::bPlayerJustTeleportedBetweenMarkers = false;

	UINT SpoonerMarker::iMarkerIdIter = 0;

	SpoonerMarker* SelectedMarker;

}



