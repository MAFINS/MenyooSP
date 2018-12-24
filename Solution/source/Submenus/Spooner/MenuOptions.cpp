/*
* Menyoo PC - Grand Theft Auto V single-player trainer mod
* Copyright (C) 2019  MAFINS
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*/
#include "MenuOptions.h"

#include "..\..\macros.h"

#include "..\..\Menu\Menu.h"
//#include "..\..\Menu\Routine.h"

#include "..\..\Natives\natives2.h"
#include "..\..\Scripting\GTAentity.h"
#include "..\..\Scripting\GTAped.h"

#include "SpoonerMode.h"
#include "EntityManagement.h"
#include "RelationshipManagement.h"
#include "SpoonerEntity.h"

namespace sub::Spooner
{
	namespace MenuOptions
	{
		void AddOption_AddProp(const std::string& text, const GTAmodel::Model& model)
		{
			bool pressed = false;
			AddOption(text, pressed);

			if (*Menu::currentopATM == Menu::printingop)
			{
				SpoonerMode::ModelPreviewInfo.entityType = EntityType::PROP;
				SpoonerMode::ModelPreviewInfo.model = model;
			}

			if (pressed)
			{
				EntityManagement::AddProp(model, text);
			}
		}
		void AddOption_AddPed(const std::string& text, const GTAmodel::Model& model)
		{
			bool pressed = false;
			AddOption(text, pressed);

			if (*Menu::currentopATM == Menu::printingop)
			{
				SpoonerMode::ModelPreviewInfo.entityType = EntityType::PED;
				SpoonerMode::ModelPreviewInfo.model = model;
			}

			if (pressed)
			{
				EntityManagement::AddPed(model, text);
			}
		}
		void AddOption_AddVehicle(const std::string& text, const GTAmodel::Model& model)
		{
			bool pressed = false;
			AddOption(text, pressed);

			if (*Menu::currentopATM == Menu::printingop)
			{
				SpoonerMode::ModelPreviewInfo.entityType = EntityType::VEHICLE;
				SpoonerMode::ModelPreviewInfo.model = model;
			}

			if (pressed)
			{
				EntityManagement::AddVehicle(model, text);
			}
		}

		void AddOption_RelationshipTextScroller()
		{
			std::vector<std::string> relationshipstringvec{ "NONE" };
			for (UINT8 i = 0; i < RelationshipManagement::vRGs.size(); i++)
			{
				if (GTAped(SelectedEntity.Handle).RelationshipGroup_get() == GET_HASH_KEY(RelationshipManagement::vRGs[i]))
					relationshipstringvec[0] = RelationshipManagement::vRGs[i];
			}

			bool relationshipstring_plus = false, relationshipstring_minus = false;
			AddTexter("Relationship", 0, relationshipstringvec, null, relationshipstring_plus, relationshipstring_minus);
			if (relationshipstring_plus)
			{
				Hash currHash;
				if (RelationshipManagement::GetPedRelationshipGroup(SelectedEntity.Handle, currHash))
				{
					for (INT8 i = 0; i < RelationshipManagement::vRGs.size(); i++)
					{
						if (GTAped(SelectedEntity.Handle).RelationshipGroup_get() == GET_HASH_KEY(RelationshipManagement::vRGs[i]))
						{
							i++;
							if (i >= RelationshipManagement::vRGs.size())
								break;
							RelationshipManagement::SetPedRelationshipGroup(SelectedEntity.Handle, GET_HASH_KEY(RelationshipManagement::vRGs[i]));
							break;
						}
					}
				}
				else
				{
					RelationshipManagement::SetPedRelationshipGroup(SelectedEntity.Handle, GET_HASH_KEY(RelationshipManagement::vRGs[0]));
				}
			}
			if (relationshipstring_minus)
			{
				for (INT8 i = 0; i < RelationshipManagement::vRGs.size(); i++)
				{
					if (GTAped(SelectedEntity.Handle).RelationshipGroup_get() == GET_HASH_KEY(RelationshipManagement::vRGs[i]))
					{
						i--;
						if (i < 0)
							break;
						RelationshipManagement::SetPedRelationshipGroup(SelectedEntity.Handle, GET_HASH_KEY(RelationshipManagement::vRGs[i]));
						break;
					}
				}
			}
		}

	}

}



