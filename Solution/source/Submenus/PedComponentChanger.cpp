/*
* Menyoo PC - Grand Theft Auto V single-player trainer mod
* Copyright (C) 2019  MAFINS
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*/
#include "PedComponentChanger.h"

#include "..\macros.h"

#include "..\Menu\Menu.h"
#include "..\Menu\Routine.h"

#include "..\Natives\natives2.h"
#include "..\Scripting\GTAped.h"
#include "..\Scripting\GTAentity.h"
#include "..\Scripting\Model.h"
#include "..\Scripting\Camera.h"
#include "..\Scripting\GameplayCamera.h"
#include "..\Scripting\World.h"
#include "..\Scripting\Game.h"
#include "..\Util\ExePath.h"
#include "..\Util\FileLogger.h"
#include "..\Util\StringManip.h"

#include "..\Menu\FolderPreviewBmps.h"
#include "..\Submenus\PedModelChanger.h"
#include "..\Submenus\Spooner\SpoonerEntity.h"
#include "..\Submenus\Spooner\Databases.h"
#include "..\Submenus\Spooner\EntityManagement.h"
#include "..\Submenus\Spooner\FileManagement.h"

#include <Shlwapi.h>
#pragma comment(lib, "Shlwapi.lib")
#include <string>
#include <vector>
#include <map>
//#include <utility>
#include <array>
#include <pugixml\src\pugixml.hpp>
#include <dirent\include\dirent.h>

namespace sub
{
	// Component changer

	Camera g_cam_componentChanger;

	void AddpedcomponentOption_(const std::string& text, int index)
	{
		bool pressed = false;
		AddOption(text, pressed, nullFunc, SUB::COMPONENTS2, true, true); if (pressed)
		{
			Static_12 = index;
		}
	}
	void AddpedpropOption_(const std::string& text, int index)
	{
		bool pressed = false;
		AddOption(text, pressed, nullFunc, SUB::COMPONENTSPROPS2); if (pressed)
		{
			Static_12 = index;
		}
	}

	void ComponentChanger_()
	{
		dict2.clear();
		dict3.clear();

		bool ComponentChanger_random = 0, comp_front_view = 0, ComponentChanger_default = 0,
			ComponentChanger_online_police_m = 0, ComponentChanger_online_robber_m = 0,
			ComponentChanger_online_garbage_m = 0, ComponentChanger_online_police_f = 0,
			ComponentChanger_offline_police_michael = 0, ComponentChanger_offline_firefighter_michael = 0;

		GTAped thisPed = Static_241;
		const Model& thisPedModel = thisPed.Model();

		if (g_cam_componentChanger.Exists())
		{
			g_cam_componentChanger.AttachTo(thisPed, Vector3(0.0f, 2.6f + thisPed.Dim1().y, 0.5f));
			g_cam_componentChanger.PointAt(thisPed);
		}

		AddTitle("Wardrobe");

		AddLocal("Front View", g_cam_componentChanger.Exists(), comp_front_view, comp_front_view);
		AddOption("Outfits", null, nullFunc, SUB::COMPONENTS_OUTFITS);
		AddOption("Decal Overlays", null, PedDecals_catind::ComponentChanger_OpenSub_Decals, -1, true);
		AddOption("Damage Overlays", null, nullFunc, SUB::PEDDAMAGET_CATEGORYLIST);
		AddOption("Head Features", null, nullFunc, SUB::PED_HEADFEATURES_MAIN);
		AddOption("Accessories", null, nullFunc, SUB::COMPONENTSPROPS);

		AddBreak("---Components---");
		AddpedcomponentOption_("Head", PV_COMP_HEAD);
		AddpedcomponentOption_("Beard/Mask", PV_COMP_BERD); // Beard // FACE_BRD
		AddpedcomponentOption_("Hair", PV_COMP_HAIR); // Hair // FACE_HAIR
		AddpedcomponentOption_("Torso", PV_COMP_UPPR);
		AddpedcomponentOption_("Legs", PV_COMP_LOWR);
		AddpedcomponentOption_("Hands/Back", PV_COMP_HAND);
		AddpedcomponentOption_("Shoes", PV_COMP_FEET); // Shoes // CSHOP_ITEM39
		AddpedcomponentOption_("Teeth/Scarf/Necklace/Bracelets", PV_COMP_TEEF);
		AddpedcomponentOption_("Accessory/Tops", PV_COMP_ACCS); // Accessory // PIM_TACCE
		AddpedcomponentOption_("Task/Armour", PV_COMP_TASK);
		AddpedcomponentOption_("Emblem", PV_COMP_DECL);
		AddpedcomponentOption_("Tops2 (Outer)", PV_COMP_JBIB);

		AddOption("Random Components", ComponentChanger_random);
		AddOption("Default Components", ComponentChanger_default);

		switch (thisPedModel.hash)
		{
		case PedHash::FreemodeMale01:
		case PedHash::FreemodeFemale01:
		case PedHash::Michael:
			AddBreak("---Premade Outfits---"); break;
		}
		if (thisPedModel.hash == PedHash::FreemodeMale01)
			AddOption("Police (Freemode Male)", ComponentChanger_online_police_m);
		if (thisPedModel.hash == PedHash::FreemodeFemale01)
			AddOption("Police (Freemode Female)", ComponentChanger_online_police_f);
		if (thisPedModel.hash == PedHash::FreemodeMale01)
			AddOption("Robber (Freemode Male)", ComponentChanger_online_robber_m);
		if (thisPedModel.hash == PedHash::FreemodeMale01)
			AddOption("Garbage Man (Freemode Male)", ComponentChanger_online_garbage_m);
		if (thisPedModel.hash == PedHash::Michael)
			AddOption("Police (Michael)", ComponentChanger_offline_police_michael);
		if (thisPedModel.hash == PedHash::Michael)
			AddOption("Firefighter (Michael)", ComponentChanger_offline_firefighter_michael);


		if (ComponentChanger_random) {
			thisPed.RequestControlOnce();
			SET_PED_RANDOM_COMPONENT_VARIATION(thisPed.GetHandle(), 0);
			return;
		}

		if (ComponentChanger_default) {
			thisPed.RequestControlOnce();
			SET_PED_DEFAULT_COMPONENT_VARIATION(thisPed.GetHandle());
			return;
		}

		if (ComponentChanger_online_police_m) {
			SET_PED_PROP_INDEX(Static_241, 0, 47, 0, NETWORK_IS_GAME_IN_PROGRESS(), 0);
			SET_PED_PROP_INDEX(Static_241, 1, 10, 0, NETWORK_IS_GAME_IN_PROGRESS(), 0);
			SET_PED_PROP_INDEX(Static_241, 2, 3, 0, NETWORK_IS_GAME_IN_PROGRESS(), 0);
			SET_PED_COMPONENT_VARIATION(Static_241, 0, 0, 0, 0);
			SET_PED_COMPONENT_VARIATION(Static_241, 1, 0, 0, 0);
			SET_PED_COMPONENT_VARIATION(Static_241, 3, 0, 0, 0);
			SET_PED_COMPONENT_VARIATION(Static_241, 4, 35, 0, 0);
			SET_PED_COMPONENT_VARIATION(Static_241, 5, 0, 0, 0);
			SET_PED_COMPONENT_VARIATION(Static_241, 6, 25, 0, 0);
			SET_PED_COMPONENT_VARIATION(Static_241, 7, 0, 0, 0);
			SET_PED_COMPONENT_VARIATION(Static_241, 8, 58, 0, 0);
			SET_PED_COMPONENT_VARIATION(Static_241, 9, 0, 0, 0);
			SET_PED_COMPONENT_VARIATION(Static_241, 10, 0, 0, 0);
			SET_PED_COMPONENT_VARIATION(Static_241, 11, 55, 0, 0);
			return;
		}

		if (ComponentChanger_online_police_f) {
			SET_PED_PROP_INDEX(Static_241, 0, 45, 0, NETWORK_IS_GAME_IN_PROGRESS(), 0);
			SET_PED_COMPONENT_VARIATION(Static_241, 3, 100, 0, 0);
			SET_PED_COMPONENT_VARIATION(Static_241, 4, 34, 0, 0);
			SET_PED_COMPONENT_VARIATION(Static_241, 11, 48, 0, 0);
			return;
		}

		if (ComponentChanger_offline_police_michael) {
			SET_PED_PROP_INDEX(Static_241, 0, 10, 0, NETWORK_IS_GAME_IN_PROGRESS(), 0);
			SET_PED_COMPONENT_VARIATION(Static_241, 3, 6, 0, 0);
			SET_PED_COMPONENT_VARIATION(Static_241, 4, 6, 0, 0);
			SET_PED_COMPONENT_VARIATION(Static_241, 6, 6, 0, 0);
			SET_PED_COMPONENT_VARIATION(Static_241, 8, 8, 0, 0);
			SET_PED_COMPONENT_VARIATION(Static_241, 11, 0, 0, 0);
			return;
		}

		if (ComponentChanger_offline_firefighter_michael) {
			SET_PED_PROP_INDEX(Static_241, 0, 0, 0, NETWORK_IS_GAME_IN_PROGRESS(), 0);
			SET_PED_COMPONENT_VARIATION(Static_241, 3, 1, 0, 0);
			SET_PED_COMPONENT_VARIATION(Static_241, 4, 1, 0, 0);
			SET_PED_COMPONENT_VARIATION(Static_241, 5, 1, 0, 0);
			SET_PED_COMPONENT_VARIATION(Static_241, 6, 1, 0, 0);
			SET_PED_COMPONENT_VARIATION(Static_241, 8, 1, 0, 0);
			return;
		}

		if (ComponentChanger_online_robber_m) {
			SET_PED_PROP_INDEX(Static_241, 0, 48, 1, NETWORK_IS_GAME_IN_PROGRESS(), 0);
			SET_PED_COMPONENT_VARIATION(Static_241, 3, 29, 1, 0);
			SET_PED_COMPONENT_VARIATION(Static_241, 4, 34, 0, 0);
			SET_PED_COMPONENT_VARIATION(Static_241, 5, 45, 0, 0);
			SET_PED_COMPONENT_VARIATION(Static_241, 6, 24, 0, 0);
			SET_PED_COMPONENT_VARIATION(Static_241, 7, 40, 0, 0);
			SET_PED_COMPONENT_VARIATION(Static_241, 8, 25, 1, 0);
			SET_PED_COMPONENT_VARIATION(Static_241, 11, 0, 16, 0);
			return;
		}

		if (ComponentChanger_online_garbage_m) {
			SET_PED_PROP_INDEX(Static_241, 1, 4, 0, NETWORK_IS_GAME_IN_PROGRESS(), 0);
			SET_PED_COMPONENT_VARIATION(Static_241, 0, 0, 0, 0);
			SET_PED_COMPONENT_VARIATION(Static_241, 1, 0, 0, 0);
			SET_PED_COMPONENT_VARIATION(Static_241, 3, 64, 0, 0);
			SET_PED_COMPONENT_VARIATION(Static_241, 4, 36, 0, 0);
			SET_PED_COMPONENT_VARIATION(Static_241, 5, 0, 0, 0);
			SET_PED_COMPONENT_VARIATION(Static_241, 6, 23, 0, 0);
			SET_PED_COMPONENT_VARIATION(Static_241, 7, 0, 0, 0);
			SET_PED_COMPONENT_VARIATION(Static_241, 8, 59, 0, 0);
			SET_PED_COMPONENT_VARIATION(Static_241, 9, 0, 0, 0);
			SET_PED_COMPONENT_VARIATION(Static_241, 10, 0, 0, 0);
			SET_PED_COMPONENT_VARIATION(Static_241, 11, 57, 0, 0);
			return;
		}

		if (comp_front_view) {
			if (g_cam_componentChanger.Exists())
			{
				g_cam_componentChanger.SetActive(false);
				g_cam_componentChanger.Destroy();
				World::RenderingCamera_set(0);
			}
			else
			{
				Camera gmCam = CREATE_CAM("DEFAULT_SCRIPTED_CAMERA", 1);
				g_cam_componentChanger = CREATE_CAM("DEFAULT_SCRIPTED_CAMERA", 1);

				g_cam_componentChanger.FieldOfView_set(40.0f);
				g_cam_componentChanger.AttachTo(thisPed, Vector3(0.0f, 1.5f + thisPed.Dim1().y, 0.5f));
				g_cam_componentChanger.PointAt(thisPed);

				gmCam.Position_set(World::RenderingCamera_get().Handle() == 0 ? GameplayCamera::Position_get() : World::RenderingCamera_get().Position_get());
				gmCam.Rotation_set(World::RenderingCamera_get().Handle() == 0 ? GameplayCamera::Rotation_get() : World::RenderingCamera_get().Rotation_get());

				gmCam.InterpTo(g_cam_componentChanger, 1000, true, true);
				while (gmCam.IsInterpolating())
					WAIT(0);
				gmCam.Destroy();
				World::RenderingCamera_set(g_cam_componentChanger);
			}
			return;
		}


	}
	void ComponentChanger2_()
	{
		bool compon_plus = 0,
			compon_minus = 0;

		int compon_drawable_current = GET_PED_DRAWABLE_VARIATION(Static_241, Static_12),
			compon_texture_current = GET_PED_TEXTURE_VARIATION(Static_241, Static_12),
			compon_palette_current = GET_PED_PALETTE_VARIATION(Static_241, Static_12);

		int compon_drawable_old = compon_drawable_current,
			compon_texture_old = compon_texture_current,
			compon_palette_old = compon_palette_current;

		AddTitle("Set Variation");

		AddNumber("Type", compon_drawable_current, 0, null, compon_plus, compon_minus);
		AddNumber("Texture", compon_texture_current, 0, null, compon_plus, compon_minus);
		//AddNumber("Palette", compon_palette_current, 0, null, compon_plus, compon_minus);

		switch (*Menu::currentopATM)
		{
		case 1:
			if (compon_plus)
			{
				if (compon_drawable_current < GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(Static_241, Static_12) - 1)
				{
					compon_drawable_current++;
					compon_texture_current = 0;
				}
				else
				{
					compon_drawable_current = 0;
					compon_texture_current = 0;
				}
			}
			else if (compon_minus)
			{
				if (compon_drawable_current > -1)
				{
					compon_drawable_current--;
					compon_texture_current = 0;
				}
				else
				{
					compon_drawable_current = GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(Static_241, Static_12) - 1;
					compon_texture_current = 0;
				}
			}
			break;
		case 2:
			if (compon_plus)
			{
				if (compon_texture_current < GET_NUMBER_OF_PED_TEXTURE_VARIATIONS(Static_241, Static_12, compon_drawable_current))
				{
					compon_texture_current++;
				}
				else compon_texture_current = 0;
			}
			else if (compon_minus)
			{
				if (compon_texture_current > 0)
				{
					compon_texture_current--;
				}
				else compon_texture_current = GET_NUMBER_OF_PED_TEXTURE_VARIATIONS(Static_241, Static_12, compon_drawable_current) - 1;
			}
			break;
		case 3:
			if (compon_plus) {
				if (compon_palette_current < 10)
				{
					compon_palette_current++;
				}
				else compon_palette_current = 0;
			}
			else if (compon_minus)
				if (compon_palette_current > 0)
				{
					compon_palette_current--;
				}
				else compon_palette_current = 10;
				break;

		}

        if (compon_drawable_old != compon_drawable_current
            || compon_texture_old != compon_texture_current
            || compon_palette_old != compon_palette_current)
        {
        	//if (IS_PED_COMPONENT_VARIATION_VALID(Static_241, Static_12, compon_drawable_current, compon_texture_current))
        	SET_PED_COMPONENT_VARIATION(Static_241, Static_12, compon_drawable_current, compon_texture_current, compon_palette_current);
            while (!HasPedSpecificDrawable(compon_drawable_current))
            {
                if (compon_plus)
                {
                    if (compon_drawable_current < GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(Static_241, Static_12) - 1)
                    {
                        compon_drawable_current++;
                        compon_texture_current = 0;
                    }
                    else
                    {
                        compon_drawable_current = 0;
                        compon_texture_current = 0;
                    }
                }
                else if (compon_minus)
                {
                    if (compon_drawable_current > -1)
                    {
                        compon_drawable_current--;
                        compon_texture_current = 0;
                        //Game::Print::PrintBottomLeft(oss_ << "compon_drawable_current prev " << compon_drawable_current << ".");
                    }
                    else
                    {
                        compon_drawable_current = GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(Static_241, Static_12) - 1;
                        compon_texture_current = 0;
                    }
                }
                SET_PED_COMPONENT_VARIATION(Static_241, Static_12, compon_drawable_current, compon_texture_current, compon_palette_current);
            }
        }
    }

    bool HasPedSpecificDrawable(int compon_drawable_new)
    {
        bool compon_drawable_correct = false;
        int compon_drawable_current = GET_PED_DRAWABLE_VARIATION(Static_241, Static_12);
        if (compon_drawable_new == compon_drawable_current)
        {
            compon_drawable_correct = true;
        }
        return compon_drawable_correct;
    }
    void ComponentChangerProps_()
	{
		GTAped thisPed = Static_241;

		if (g_cam_componentChanger.Exists())
		{
			g_cam_componentChanger.AttachTo(thisPed, Bone::Head, Vector3(0.0f, 0.6f, 0.0f));
			g_cam_componentChanger.PointAt(thisPed, Bone::Head);
		}

		bool ComponentChanger_randomProps = 0, ComponentChanger_clearAllProps = 0;

		AddTitle("Accessories");

		AddpedpropOption_("Hats", 0);
		AddpedpropOption_("Glasses", 1);
		AddpedpropOption_("Ear Pieces", 2);
		AddpedpropOption_("Watches", 6);
		AddpedpropOption_("Bangles", 7);

		AddBreak("---Unknown---");
		AddpedpropOption_("Unknown 3", 3);
		AddpedpropOption_("Unknown 4", 4);
		AddpedpropOption_("Unknown 5", 5);
		AddpedpropOption_("Unknown 8", 8);
		AddpedpropOption_("Unknown 9", 9);

		AddBreak("---Utilities---");
		AddOption("Random Accessories", ComponentChanger_randomProps);
		AddTickol("Clear Accessories", true, ComponentChanger_clearAllProps, ComponentChanger_clearAllProps, TICKOL::CROSS);

		if (ComponentChanger_randomProps) {
			thisPed.RequestControlOnce();
			SET_PED_RANDOM_PROPS(thisPed.Handle());
			return;
		}

		if (ComponentChanger_clearAllProps) {
			thisPed.RequestControlOnce();
			CLEAR_ALL_PED_PROPS(thisPed.Handle(), 0);
			return;
		}

	}
	void ComponentChangerProps2_()
	{
		GTAentity ped = Static_241;
		auto& propId = Static_12;

		bool compon_plus = 0,
			compon_minus = 0;

		int	prop_type_current = GET_PED_PROP_INDEX(Static_241, Static_12, 0),
			prop_texture_current = GET_PED_PROP_TEXTURE_INDEX(Static_241, Static_12);
		int prop_type_old = prop_type_current,
			prop_texture_old = prop_texture_current;

		AddTitle("Set Variation");

		AddNumber("Type", prop_type_current, 0, null, compon_plus, compon_minus);
		AddNumber("Texture", prop_texture_current, 0, null, compon_plus, compon_minus);


		switch (Menu::currentop)
		{
		case 1:
			if (compon_plus)
			{
				if (prop_type_current < GET_NUMBER_OF_PED_PROP_DRAWABLE_VARIATIONS(Static_241, Static_12) - 1)
				{
					prop_type_current++;
					prop_texture_current = 0;
				}
				else
				{
					prop_type_current = -1;
					prop_texture_current = 0;
				}
			}
			else if (compon_minus)
			{
				if (prop_type_current > -1)
				{
					prop_type_current--;
					prop_texture_current = 0;
				}
				else
				{
					prop_type_current = GET_NUMBER_OF_PED_PROP_DRAWABLE_VARIATIONS(Static_241, Static_12) - 1;
					prop_texture_current = 0;
				}
			}
			break;
		case 2:
			if (compon_plus)
			{
				if (prop_texture_current < GET_NUMBER_OF_PED_PROP_TEXTURE_VARIATIONS(Static_241, Static_12, prop_type_current) - 1)
				{
					prop_texture_current++;
				}
				else prop_texture_current = 0;
			}
			else if (compon_minus)
			{
				if (prop_texture_current > 0)
				{
					prop_texture_current--;
				}
				else prop_texture_current = GET_NUMBER_OF_PED_PROP_TEXTURE_VARIATIONS(Static_241, Static_12, prop_type_current) - 1;
			}
			break;
		}

		if (ped.Exists() && (prop_type_current != prop_type_old || prop_texture_current != prop_texture_old))
		{
			if (prop_type_current == -1)
				CLEAR_PED_PROP(ped.Handle(), propId, 0);
			else
			{
				SET_PED_PROP_INDEX(ped.Handle(), propId, prop_type_current, prop_texture_current, NETWORK_IS_GAME_IN_PROGRESS(), 0);
				while (!HasPedSpecificPropType(prop_type_current))
				{
					if (compon_plus)
					{
						if (prop_type_current < GET_NUMBER_OF_PED_PROP_DRAWABLE_VARIATIONS(Static_241, Static_12) - 1)
						{
							prop_type_current++;
							prop_texture_current = 0;
						}
						else
						{
							prop_type_current = -1;
							prop_texture_current = 0;
						}
					}
					else if (compon_minus)
					{
						if (prop_type_current > -1)
						{
							prop_type_current--;
							prop_texture_current = 0;
						}
						else
						{
							prop_type_current = GET_NUMBER_OF_PED_PROP_DRAWABLE_VARIATIONS(Static_241, Static_12) - 1;
							prop_texture_current = 0;
						}
					}
				SET_PED_PROP_INDEX(ped.Handle(), propId, prop_type_current, prop_texture_current, NETWORK_IS_GAME_IN_PROGRESS(), 0);
				}
			}
		}
	}
	bool HasPedSpecificPropType(int prop_type_new)
	{
		bool prop_type_correct = false;
		int prop_type_current = GET_PED_PROP_INDEX(Static_241, Static_12, 0);
		if (prop_type_new == prop_type_current)
		{
			prop_type_correct = true;
		}
		return prop_type_correct;
	}

	// Decals - tattoos & badges

	namespace PedDecals_catind
	{
		std::map<Ped, std::vector<PedDecalValue>> vPedsAndDecals;

		bool NamedPedDecal::IsOnPed(GTAentity ped) const
		{
			auto it = vPedsAndDecals.find(ped.Handle());
			if (it == vPedsAndDecals.end())
				return false;
			else
			{
				auto& decals = it->second;
				for (auto& decal : decals)
				{
					if (decal.collection == this->collection && decal.value == this->value)
						return true;
				}
			}
			return false;
		}
		void NamedPedDecal::Apply(GTAentity ped) const
		{
			if (ped.Exists())
			{
				ped.RequestControl(200);
				PED::ADD_PED_DECORATION_FROM_HASHES(ped.Handle(), this->collection, this->value);
				vPedsAndDecals[ped.Handle()].push_back({ this->collection, this->value });
			}
			else
			{
				vPedsAndDecals.erase(ped.Handle());
			}
		}
		void NamedPedDecal::Remove(GTAentity ped) const
		{
			if (ped.Exists())
			{
				auto& decals = vPedsAndDecals[ped.Handle()];
				for (auto it = decals.begin(); it != decals.end();)
				{
					if (it->collection == this->collection && it->value == this->value)
						it = decals.erase(it);
					else ++it;
				}
				ped.RequestControl(200);
				CLEAR_PED_DECORATIONS(ped.Handle());
				for (auto& decal : decals)
				{
					ADD_PED_DECORATION_FROM_HASHES(ped.Handle(), decal.collection, decal.value);
				}
			}
			else
			{
				vPedsAndDecals.erase(ped.Handle());
			}
		}

		std::map<Hash, std::map<std::string, std::map<std::string, std::vector<NamedPedDecal>>>> vAllDecals; // PedHash[Type][Zone]
		void PopulateDecalsDict()
		{
			vAllDecals.clear();
			pugi::xml_document doc;
			if (doc.load_file((const char*)(GetPathffA(Pathff::Main, true) + "PedDecalOverlays.xml").c_str()).status != pugi::status_ok)
			{
				addlog(ige::LogType::LOG_ERROR,  "Unable to open PedDecalOverlays.xml", __FILENAME__);
				return;
			}

			auto nodeRoot = doc.document_element();
			for (auto nodePed = nodeRoot.child("Ped"); nodePed; nodePed = nodePed.next_sibling("Ped"))
			{
				auto& dictType = vAllDecals[nodePed.attribute("hash").as_uint()];
				for (auto nodeType = nodePed.first_child(); nodeType; nodeType = nodeType.next_sibling())
				{
					auto& dictZone = dictType[nodeType.name()];
					for (auto nodeZone = nodeType.first_child(); nodeZone; nodeZone = nodeZone.next_sibling())
					{
						auto& listDecals = dictZone[nodeZone.name()];
						for (auto nodeDecal = nodeZone.child("OVERLAY"); nodeDecal; nodeDecal = nodeDecal.next_sibling("OVERLAY"))
						{
							NamedPedDecal decal;
							decal.collection = GET_HASH_KEY(nodeDecal.attribute("collection").as_string());
							decal.value = GET_HASH_KEY(nodeDecal.attribute("name").as_string());
							decal.caption = nodeDecal.attribute("caption").as_string();
							listDecals.push_back(decal);
						}
					}
				}
			}
		}

		std::pair<std::string, std::map<std::string, std::vector<NamedPedDecal>>>* _selectedType;
		std::pair<std::string, std::vector<NamedPedDecal>>* _selectedZone;

		void Sub_Decals_Types()
		{
			GTAped ped = Static_241;
			const auto& pedModel = ped.Model();

			const auto& vPed = vAllDecals.find(pedModel.hash);
			if (vPed == vAllDecals.end())
			{
				Menu::SetSub_previous();
				return;
			}

			AddTitle("Decal Overlays");

			for (auto& type : vPed->second)
			{
				bool bTypePressed = false;
				AddOption(type.first, bTypePressed, nullFunc, SUB::PEDDECALS_ZONES); if (bTypePressed)
				{
					_selectedType = (std::pair<std::string, std::map<std::string, std::vector<NamedPedDecal>>>*)&type;
				}
			}

			bool bClearAllPressed = false;
			AddTickol("CLEAR ALL", true, bClearAllPressed, bClearAllPressed, TICKOL::CROSS); if (bClearAllPressed)
			{
				ped.RequestControl(600);
				CLEAR_PED_DECORATIONS(ped.Handle());
				vPedsAndDecals.erase(ped.Handle());
			}

		}
		void Sub_Decals_Zones()
		{
			AddTitle(_selectedType->first);

			for (auto& zone : _selectedType->second)
			{
				bool bZonePressed = false;
				AddOption(zone.first, bZonePressed, nullFunc, SUB::PEDDECALS_INZONE); if (bZonePressed)
				{
					_selectedZone = (std::pair<std::string, std::vector<NamedPedDecal>>*)&zone;
				}
			}
		}
		void Sub_Decals_InZone()
		{
			GTAentity ped = Static_241;

			AddTitle(_selectedZone->first);

			for (const auto& decal : _selectedZone->second)
			{
				bool bDecalPressedApply = false, bDecalPressedRemove = false;
				AddTickol(decal.caption, decal.IsOnPed(ped), bDecalPressedApply, bDecalPressedRemove, TICKOL::TATTOOTHING);
				if (bDecalPressedApply)
				{
					decal.Apply(ped);
				}
				else if (bDecalPressedRemove)
				{
					decal.Remove(ped);
				}
			}

		}
		void ComponentChanger_OpenSub_Decals()
		{
			GTAentity ped = Static_241;
			bool allowed = vAllDecals.find(ped.Model().hash) != vAllDecals.end();

			if (vAllDecals.find(ped.Model().hash) != vAllDecals.end())
				Menu::SetSub_delayed = SUB::PEDDECALS_TYPES;
			else
				Game::Print::PrintBottomCentre("~r~Error:~s~ No decal overlays available for this ped model.");
		}

	}

	// Damage/blood textures

	namespace PedDamageTextures_catind
	{
		auto& _selectedPedHandle = Static_241;
		int _boneToUse = 0;

		std::map<Ped, std::vector<std::string>> vPedsAndDamagePacks;

		void ClearAllBloodDamage(GTAped ped)
		{
			ped.ClearBloodDamage();
		}
		void ClearAllVisibleDamage(GTAped ped)
		{
			ped.ResetVisibleDamage();
			const auto& it = vPedsAndDamagePacks.find(ped.Handle());
			if (it != vPedsAndDamagePacks.end())
				vPedsAndDamagePacks.erase(it);
		}
		void ClearAll241BloodDamage()
		{
			ClearAllBloodDamage(_selectedPedHandle);
		}
		void ClearAll241VisibleDamage()
		{
			ClearAllVisibleDamage(_selectedPedHandle);
		}

#pragma region blood data
		using PedBloodDecals::vBloodDecals;
#pragma endregion
#pragma region damage decal data
		using PedDamageDecals::vDamageDecals;
#pragma endregion
#pragma region damage packs
		using PedDamagePacks::vDamagePacks;
#pragma endregion

		// Use Banner idk k
		void Sub_CategoryList()
		{
			AddTitle("Damage Overlays");

			//AddOption("Select Bone", null, nullFunc, SUB::PEDDAMAGET_BONESELECTION);
			//AddOption("Blood Decals", null, nullFunc, SUB::PEDDAMAGET_BLOOD);
			//AddOption("Damage Decals", null, nullFunc, SUB::PEDDAMAGET_DAMAGEDECALS);
			AddOption("Damage Packs", null, nullFunc, SUB::PEDDAMAGET_DAMAGEPACKS);

			AddBreak("---Wash Up---");
			AddTickol("Clear Blood Damage", true, ClearAll241BloodDamage, ClearAll241BloodDamage, TICKOL::CROSS);
			AddTickol("Clear All Visible Damage", true, ClearAll241VisibleDamage, ClearAll241VisibleDamage, TICKOL::CROSS);
		}
		void Sub_BoneSelection()
		{
			AddTitle("Select Bone");

			bool bPressed = false;
			for (const auto& bn : Bone::vBoneNames)
			{
				bPressed = false;
				AddTickol(bn.name, _boneToUse == bn.boneid, bPressed, bPressed, TICKOL::SKULL_DM, TICKOL::NONE, true); if (bPressed) // Gxt test
				{
					_boneToUse = bn.boneid;
				}
			}

		}
		void Sub_Blood()
		{
			GTAped thisPed = _selectedPedHandle;
			auto& thisBone = _boneToUse;

			AddTitle("Blood Decals");

			bool bPressed = false;
			for (const auto& bdn : vBloodDecals)
			{
				bPressed = false;
				AddOption(bdn, bPressed); if (bPressed)
				{
					thisPed.ApplyBlood(bdn, thisBone, Vector3());
				}
			}
		}
		void Sub_DamageDecals()
		{
			GTAped thisPed = _selectedPedHandle;
			auto& thisBone = _boneToUse;

			AddTitle("Damage Decals");

			bool bPressed = false;
			for (const auto& ddn : vDamageDecals)
			{
				bPressed = false;
				AddOption(ddn, bPressed); if (bPressed)
				{
					thisPed.ApplyDamageDecal(ddn, thisBone, Vector3(), 1.0f, 1.0f, 1, true);
				}
			}
		}
		void Sub_DamagePacks()
		{
			GTAped thisPed = _selectedPedHandle;

			auto& dmgPacksApplied = vPedsAndDamagePacks[thisPed.Handle()];

			AddTitle("Damage Packs");

			for (const auto& dpn : vDamagePacks)
			{
				bool bPressedApply = false, bPressedRemove = false;
				AddTickol(dpn, std::find(dmgPacksApplied.begin(), dmgPacksApplied.end(), dpn) != dmgPacksApplied.end(), bPressedApply, bPressedRemove, TICKOL::MAKEUPTHING);
				if (bPressedApply)
				{
					thisPed.ApplyDamagePack(dpn, 1.0f, 1.0f);
					dmgPacksApplied.push_back(dpn);
				}
				if (bPressedRemove)
				{
					thisPed.ResetVisibleDamage();
					for (auto dpntrit = dmgPacksApplied.begin(); dpntrit != dmgPacksApplied.end();)
					{
						if (dpntrit->compare(dpn) == 0)
						{
							dpntrit = dmgPacksApplied.erase(dpntrit);
							continue;
						}
						thisPed.ApplyDamagePack(*dpntrit, 1.0f, 1.0f);
						++dpntrit;
					}
				}
			}
		}
	}

	// Head features (freemode m/f)

	namespace PedHeadFeatures_catind
	{

		std::map<Ped, sPedHeadFeatures> vPedHeads;
		std::map<Ped, sPedHeadFeatures>::mapped_type* _pedHead;

#pragma region arrays
		const std::vector<std::pair<std::string, std::vector<std::string>>> vCaptions_headOverlays
		{
			{ /*"Skin Rash"*/"FACE_F_SUND",{ "Uneven", "Sandpaper", "Patchy", "Rough", "Leathery", "Textured", "Coarse", "Rugged", "Creased", "Cracked", "Gritty" } },
			{ /*"Beard"*/"FACE_F_BEARD",{ "HAIR_BEARD1", "HAIR_BEARD2", "HAIR_BEARD3", "HAIR_BEARD4", "HAIR_BEARD5", "HAIR_BEARD6", "HAIR_BEARD7", "HAIR_BEARD8", "HAIR_BEARD9", "HAIR_BEARD10", "HAIR_BEARD11", "HAIR_BEARD12", "HAIR_BEARD13", "HAIR_BEARD14", "HAIR_BEARD15", "HAIR_BEARD16", "HAIR_BEARD17", "HAIR_BEARD18", "HAIR_BEARD19" } }, // Beard HAIR_OPTION_0
			{ /*"Eyebrows"*/"FACE_F_EYEBR",{ "CC_EYEBRW_0", "CC_EYEBRW_1", "CC_EYEBRW_2", "CC_EYEBRW_3", "CC_EYEBRW_4", "CC_EYEBRW_5", "CC_EYEBRW_6", "CC_EYEBRW_7", "CC_EYEBRW_8", "CC_EYEBRW_9", "CC_EYEBRW_10", "CC_EYEBRW_11", "CC_EYEBRW_12", "CC_EYEBRW_13", "CC_EYEBRW_14", "CC_EYEBRW_15", "CC_EYEBRW_16", "CC_EYEBRW_17", "CC_EYEBRW_18", "CC_EYEBRW_19", "CC_EYEBRW_20", "CC_EYEBRW_21", "CC_EYEBRW_22", "CC_EYEBRW_23", "CC_EYEBRW_24", "CC_EYEBRW_25", "CC_EYEBRW_26", "CC_EYEBRW_27", "CC_EYEBRW_28", "CC_EYEBRW_29", "CC_EYEBRW_30", "CC_EYEBRW_31", "CC_EYEBRW_32", "CC_EYEBRW_33" } },
			{ /*"Wrinkles"*/"FACE_F_SKINA",{ "Crow's Feet", "First Signs", "Middle Aged", "Worry Lines", "Depression", "Distinguished", "Aged", "Weathered", "Wrinkled", "Sagging", "Tough Life", "Vintage", "Retired", "Junkie", "Geriatric" } },
			{ /*"Makeup & Face Paint"*/"HAIR_OPTION_2",{ "CC_MKUP_0", "CC_MKUP_1", "CC_MKUP_2", "CC_MKUP_3", "CC_MKUP_4", "CC_MKUP_5", "CC_MKUP_6", "CC_MKUP_7", "CC_MKUP_8", "CC_MKUP_9", "CC_MKUP_10", "CC_MKUP_11", "CC_MKUP_12", "CC_MKUP_13", "CC_MKUP_14", "CC_MKUP_15", "CC_MKUP_16", "CC_MKUP_17", "CC_MKUP_18", "CC_MKUP_19", "CC_MKUP_20", "CC_MKUP_21", "CC_MKUP_22", "CC_MKUP_23", "CC_MKUP_24", "CC_MKUP_25", "CC_MKUP_26", "CC_MKUP_27", "CC_MKUP_28", "CC_MKUP_29", "CC_MKUP_30", "CC_MKUP_31", "CC_MKUP_32", "CC_MKUP_33", "CC_MKUP_34", "CC_MKUP_35", "CC_MKUP_36", "CC_MKUP_37", "CC_MKUP_38", "CC_MKUP_39", "CC_MKUP_40", "CC_MKUP_41" } }, // Makeup & face paint HAIR_OPTION_2
			{ /*"Blush"*/"FACE_F_BLUSH",{ "CC_BLUSH_0", "CC_BLUSH_1", "CC_BLUSH_2", "CC_BLUSH_3", "CC_BLUSH_4", "CC_BLUSH_5", "CC_BLUSH_6" } },
			{ /*"Pigment 1 - Complexion"*/"FACE_F_SKC",{ "Rosy Cheeks", "Stubble Rash", "Hot Flush", "Sunburn", "Bruised", "Alchoholic", "Patchy", "Totem", "Blood Vessels", "Damaged", "Pale", "Ghostly" } },
			{ /*"Pigment 2 - Blemishes"*/"FACE_F_SKINB",{ "Measles", "Pimples", "Spots", "Break Out", "Blackheads", "Build Up", "Pustules", "Zits", "Full Acne", "Acne", "Cheek Rash", "Face Rash", "Picker", "Puberty", "Eyesore", "Chin Rash", "Two Face", "T Zone", "Greasy", "Marked", "Acne Scarring", "Full Acne Scarring", "Cold Sores", "Impetigo" } },
			{ /*"Lipstick"*/"FACE_F_LIPST",{ "CC_LIPSTICK_0", "CC_LIPSTICK_1", "CC_LIPSTICK_2", "CC_LIPSTICK_3", "CC_LIPSTICK_4", "CC_LIPSTICK_5", "CC_LIPSTICK_6", "CC_LIPSTICK_7", "CC_LIPSTICK_8", "CC_LIPSTICK_9" } },
			{ /*"Spots"*/"FACE_F_MOLE",{ "Cherub", "All Over", "Irregular", "Dot Dash", "Over the Bridge", "Baby Doll", "Pixie", "Sun Kissed", "Beauty Marks", "Line Up", "Modelesque", "Occasional", "Speckled", "Rain Drops", "Double Dip", "One Sided", "Pairs", "Growth" } },
			{ "Chest Hair",{ "CC_BODY_1_0", "CC_BODY_1_1", "CC_BODY_1_2", "CC_BODY_1_3", "CC_BODY_1_4", "CC_BODY_1_5", "CC_BODY_1_6", "CC_BODY_1_7", "CC_BODY_1_8", "CC_BODY_1_9", "CC_BODY_1_10", "CC_BODY_1_11", "CC_BODY_1_12", "CC_BODY_1_13", "CC_BODY_1_14", "CC_BODY_1_15", "CC_BODY_1_16", "CC_BODY_1_17" } },
			{ "Chest Blemishes",{} },
			{ "Chest Blemishes 2",{} },
		};
		const std::vector<std::string> vCaptions_facialFeatures
		{
			{ "Nose Width" },
			{ "Nose Bottom Height" },
			{ "Nose Tip Length" },
			{ "Nose Bridge Depth" },
			{ "Nose Tip Height" },
			{ "Nose Broken" },
			{ "Brow Height" },
			{ "Brow Depth" },
			{ "Cheekbone Height" },
			{ "Cheekbone Width" },
			{ "Cheek Depth" },
			{ "Eye Size" },
			{ "Lip Thickness" },
			{ "Jaw Width" },
			{ "Jaw Shape" },
			{ "Chin Height" },
			{ "Chin Depth" },
			{ "Chin Width" },
			{ "Chin Indent" },
			{ "Neck Width" }
		};
#pragma endregion

		UINT8 max_shapeAndSkinIDs = 46;
		UINT8 GetPedHeadOverlayColourType(const PedHeadOverlay& overlayIndex)
		{
			switch (overlayIndex)
			{
			case PedHeadOverlay::Eyebrows:
			case PedHeadOverlay::Beard:
			case PedHeadOverlay::ChestHair:
			case PedHeadOverlay::Makeup:
				return 1; break;
			case PedHeadOverlay::Blush:
			case PedHeadOverlay::Lipstick:
				return 2; break;
			}
			return 0;
		}
		bool DoesPedModelSupportHeadFeatures(const GTAmodel::Model& pedModel)
		{
			switch (pedModel.hash)
			{
			case PedHash::FreemodeMale01:
			case PedHash::FreemodeFemale01:
				return true; break;
			}
			return false;
		}
		void UpdatePedHeadBlendData(GTAped& ped, const PedHeadBlendData& blendData, bool bUnused)
		{
			ped.HeadBlendData_set(blendData);
			//else UPDATE_PED_HEAD_BLEND_DATA(ped.Handle(), blendData.shapeMix, blendData.skinMix, blendData.thirdMix);
		}

		void Sub_Main()
		{
			GTAped ped = Static_241;
			Model pedModel = ped.Model();

			if (g_cam_componentChanger.Exists())
			{
				g_cam_componentChanger.AttachTo(ped, Bone::Head, Vector3(0.0f, 0.645f, 0.0f));
				g_cam_componentChanger.PointAt(ped, Bone::Head);
			}

			if (!ped.Exists() || !DoesPedModelSupportHeadFeatures(pedModel.hash))
			{
				auto pit = vPedHeads.find(ped.Handle());
				if (pit != vPedHeads.end())
					vPedHeads.erase(pit);
				Menu::SetSub_previous();
				Game::Print::PrintBottomLeft("~r~Error:~s~ Either the ped died or it isn't an MP freemode model.");
				return;
			}

			_pedHead = &vPedHeads[ped.Handle()];

			auto headBlend = ped.HeadBlendData_get();
			if (headBlend.shapeFirstID < 0 || headBlend.shapeFirstID > max_shapeAndSkinIDs || headBlend.shapeSecondID < 0 || headBlend.shapeSecondID > max_shapeAndSkinIDs
				|| headBlend.shapeThirdID < 0 || headBlend.shapeThirdID > max_shapeAndSkinIDs || headBlend.skinFirstID < 0 || headBlend.skinFirstID > max_shapeAndSkinIDs
				|| headBlend.skinSecondID < 0 || headBlend.skinSecondID > max_shapeAndSkinIDs || headBlend.skinThirdID < 0 || headBlend.skinThirdID > max_shapeAndSkinIDs
				)
			{
				headBlend.shapeFirstID = 0;
				headBlend.shapeSecondID = 0;
				headBlend.shapeThirdID = 0;
				headBlend.skinFirstID = 1;
				headBlend.skinSecondID = 1;
				headBlend.skinThirdID = 1;
				headBlend.shapeMix = 0.0f;
				headBlend.skinMix = 0.0f;
				headBlend.thirdMix = 0.0f;
				headBlend.isParent = false;
				ped.HeadBlendData_set(headBlend);
			}

			int max_hairColours = GET_NUM_PED_HAIR_TINTS() - 1;
			int max_eyeColours = 32;

			bool hairColour_plus = 0, hairColour_minus = 0;
			bool hairColourStreaks_plus = 0, hairColourStreaks_minus = 0;
			bool eyeColour_plus = 0, eyeColour_minus = 0;
			//bool bRubItAllOff = false;

			AddTitle("Head Features");

			AddOption("Overlays", null, nullFunc, SUB::PED_HEADFEATURES_HEADOVERLAYS);
			AddOption("Facial Features", null, nullFunc, SUB::PED_HEADFEATURES_FACEFEATURES);
			AddOption("Shape & Skin Tone", null, nullFunc, SUB::PED_HEADFEATURES_SKINTONE);

			AddBreak("---Hair---");
			AddNumber("Hair Colour", _pedHead->hairColour, 0, null, hairColour_plus, hairColour_minus); // 0f to GET_NUM_PED_HAIR_TINTS
			AddNumber("Hair Streaks Colour", _pedHead->hairColourStreaks, 0, null, hairColourStreaks_plus, hairColourStreaks_minus); // 0f to GET_NUM_PED_HAIR_TINTS

			AddBreak("---Eyes---");
			AddNumber(Game::GetGXTEntry("FACE_APP_EYE", "Eye Colour"), _pedHead->eyeColour, 0, null, eyeColour_plus, eyeColour_minus); // 1f to 32f

																																	   //AddBreak("---Removal---");
																																	   //AddTickol("Rub It All Off", true, bRubItAllOff, bRubItAllOff, TICKOL::CROSS); if (bRubItAllOff) RubOffPedHeadElements(ped);

			if (hairColour_plus)
			{
				if (_pedHead->hairColour < max_hairColours) _pedHead->hairColour++;
				SET_PED_HAIR_TINT(ped.Handle(), _pedHead->hairColour, _pedHead->hairColourStreaks);
			}
			if (hairColour_minus)
			{
				if (_pedHead->hairColour > 0) _pedHead->hairColour--;
				SET_PED_HAIR_TINT(ped.Handle(), _pedHead->hairColour, _pedHead->hairColourStreaks);
			}
			if (hairColourStreaks_plus)
			{
				if (_pedHead->hairColourStreaks < max_hairColours) _pedHead->hairColourStreaks++;
				SET_PED_HAIR_TINT(ped.Handle(), _pedHead->hairColour, _pedHead->hairColourStreaks);
			}
			if (hairColourStreaks_minus)
			{
				if (_pedHead->hairColourStreaks > 0) _pedHead->hairColourStreaks--;
				SET_PED_HAIR_TINT(ped.Handle(), _pedHead->hairColour, _pedHead->hairColourStreaks);
			}

			if (eyeColour_plus)
			{
				if (_pedHead->eyeColour < max_eyeColours) _pedHead->eyeColour++;
				SET_HEAD_BLEND_EYE_COLOR(ped.Handle(), SYSTEM::ROUND((float)_pedHead->eyeColour)); // What even
			}
			if (eyeColour_minus)
			{
				if (_pedHead->eyeColour > 0) _pedHead->eyeColour--;
				SET_HEAD_BLEND_EYE_COLOR(ped.Handle(), SYSTEM::ROUND((float)_pedHead->eyeColour));
			}

		}
		void Sub_HeadOverlays()
		{
			auto& overlayIndex = Static_12;
			AddTitle("Overlays");

			for (UINT i = 0; i < vCaptions_headOverlays.size(); i++)
			{
				bool bOverlayNamePressed = false;
				AddOption(vCaptions_headOverlays[i].first, bOverlayNamePressed, nullFunc, -1, true, true); if (bOverlayNamePressed)
				{
					overlayIndex = i;
					Menu::SetSub_delayed = SUB::PED_HEADFEATURES_HEADOVERLAYS_INITEM;
				}
			}
		}
		void Sub_HeadOverlays_InItem()
		{
			auto& overlayIndex = Static_12;
			GTAped ped = Static_241;

			auto colourType = GetPedHeadOverlayColourType((PedHeadOverlay)overlayIndex);
			bool bColoursAvailable = (colourType != 0);

			auto& currentOverlayData = _pedHead->overlayData[overlayIndex];
			int currentOverlayValue = GET_PED_HEAD_OVERLAY(ped.Handle(), overlayIndex);
			int max_overlays = GET_PED_HEAD_OVERLAY_NUM(overlayIndex) - 1;
			int max_colours = 64;

			bool overlay_plus = 0, overlay_minus = 0;
			bool opacity_plus = 0, opacity_minus = 0;

			AddTitle(vCaptions_headOverlays[overlayIndex].first);

			// VARIATION
			AddTexter("Variation", currentOverlayValue, vCaptions_headOverlays[overlayIndex].second, null, overlay_plus, overlay_minus);
			if (overlay_plus)
			{
				if (currentOverlayValue < max_overlays)
				{
					currentOverlayValue++;
					SET_PED_HEAD_OVERLAY(ped.Handle(), overlayIndex, currentOverlayValue, currentOverlayData.opacity);
					SET_PED_HEAD_OVERLAY_TINT(ped.Handle(), overlayIndex, 0, currentOverlayData.colour=0, currentOverlayData.colourSecondary=0);
				}
				else
				{
					currentOverlayValue = currentOverlayValue == 255 ? 0 : 255;
					SET_PED_HEAD_OVERLAY(ped.Handle(), overlayIndex, currentOverlayValue, currentOverlayData.opacity);
					SET_PED_HEAD_OVERLAY_TINT(ped.Handle(), overlayIndex, 0, currentOverlayData.colour=0, currentOverlayData.colourSecondary=0);
				}
			}
			if (overlay_minus)
			{
				if (currentOverlayValue > 0)
				{
					currentOverlayValue = currentOverlayValue > max_overlays ? max_overlays : currentOverlayValue - 1;
					SET_PED_HEAD_OVERLAY(ped.Handle(), overlayIndex, currentOverlayValue, currentOverlayData.opacity);
					SET_PED_HEAD_OVERLAY_TINT(ped.Handle(), overlayIndex, 0, currentOverlayData.colour=0, currentOverlayData.colourSecondary=0);
				}
				else
				{
					currentOverlayValue = 255;
					SET_PED_HEAD_OVERLAY(ped.Handle(), overlayIndex, currentOverlayValue, currentOverlayData.opacity);
					SET_PED_HEAD_OVERLAY_TINT(ped.Handle(), overlayIndex, 0, currentOverlayData.colour=0, currentOverlayData.colourSecondary=0);
				}
			}

			// OPACITY
			AddNumber(Game::GetGXTEntry("FACE_OPAC", "Opacity"), currentOverlayData.opacity, 3, null, opacity_plus, opacity_minus);
			if (opacity_plus)
			{
				if (currentOverlayData.opacity < 1.0f)
				{
					currentOverlayData.opacity += 0.01f;
					SET_PED_HEAD_OVERLAY(ped.Handle(), overlayIndex, currentOverlayValue, currentOverlayData.opacity);
				}
			}
			if (opacity_minus)
			{
				if (currentOverlayData.opacity > 0.0f)
				{
					currentOverlayData.opacity -= 0.01f;
					SET_PED_HEAD_OVERLAY(ped.Handle(), overlayIndex, currentOverlayValue, currentOverlayData.opacity);
				}
			}

			if (bColoursAvailable)
			{
				bool colour_plus = 0, colour_minus = 0;
				bool colourSecondary_plus = 0, colourSecondary_minus = 0;

				// PRIMARY COLOUR
				AddNumber(Game::GetGXTEntry("CMOD_COL0_0", "Primary Colour"), currentOverlayData.colour, 0, null, colour_plus, colour_minus);
				if (colour_plus)
				{
					if (currentOverlayData.colour < max_colours)
					{
						currentOverlayData.colour++;
						SET_PED_HEAD_OVERLAY_TINT(ped.Handle(), overlayIndex, colourType, currentOverlayData.colour, currentOverlayData.colourSecondary);
					}
				}
				if (colour_minus)
				{
					if (currentOverlayData.colour > 0)
					{
						currentOverlayData.colour--;
						SET_PED_HEAD_OVERLAY_TINT(ped.Handle(), overlayIndex, colourType, currentOverlayData.colour, currentOverlayData.colourSecondary);
					}
				}

				// SECONDARY COLOUR
				AddNumber(Game::GetGXTEntry("CMOD_COL0_1", "Secondary Colour"), currentOverlayData.colourSecondary, 0, null, colourSecondary_plus, colourSecondary_minus);
				if (colourSecondary_plus)
				{
					if (currentOverlayData.colourSecondary < max_colours)
					{
						currentOverlayData.colourSecondary++;
						SET_PED_HEAD_OVERLAY_TINT(ped.Handle(), overlayIndex, colourType, currentOverlayData.colour, currentOverlayData.colourSecondary);
					}
				}
				if (colourSecondary_minus)
				{
					if (currentOverlayData.colourSecondary > 0)
					{
						currentOverlayData.colourSecondary--;
						SET_PED_HEAD_OVERLAY_TINT(ped.Handle(), overlayIndex, colourType, currentOverlayData.colour, currentOverlayData.colourSecondary);
					}
				}

			}
		}
		void Sub_FaceFeatures()
		{
			GTAped ped = Static_241;

			AddTitle("Facial Features");

			for (int i = 0; i < vCaptions_facialFeatures.size(); i++)
			{
				auto& featureValue = _pedHead->facialFeatureData[i]; // Use data from memory or native func if possible later

				bool feature_plus = false, feature_minus = false;
				AddNumber(vCaptions_facialFeatures[i], featureValue, 2, null, feature_plus, feature_minus);
				if (feature_plus)
				{
					if (featureValue < 1.0f)
						featureValue += 0.05f;
					SET_PED_MICRO_MORPH(ped.Handle(), i, featureValue);
				}
				if (feature_minus)
				{
					if (featureValue > -1.0f)
						featureValue -= 0.05f;
					SET_PED_MICRO_MORPH(ped.Handle(), i, featureValue);
				}

			}

		}
		void Sub_SkinTone() // HEAD_BLEND
		{
			GTAped ped = Static_241;
			//auto& blendData = _pedHead->blendData;
			PedHeadBlendData blendData;
			GET_PED_HEAD_BLEND_DATA(ped.Handle(), (Any*)&blendData);
			std::vector<std::string> vIdNames;//{ "Male Non-DLC", "Female Non-DLC", "Male DLC", "Female DLC" };
			auto max_ids = max_shapeAndSkinIDs;
			//for (UINT8 i = 0; i < max_ids - 4; i++) vIdNames.push_back(std::to_string(i));
			float max_mix = 1.0f;
			float min_mix = -1.0f;
			float mix_amountToChange = 0.01f;

			AddTitle("Shape & Skin Tone");

			// Shape IDs
			bool shapeFirstID_plus = false, shapeFirstID_minus = false;
			AddTexter("Shape Inherited From Father", blendData.shapeFirstID, vIdNames, null, shapeFirstID_plus, shapeFirstID_minus);
			if (shapeFirstID_plus) { if (blendData.shapeFirstID < max_ids) { blendData.shapeFirstID++; UpdatePedHeadBlendData(ped, blendData, true); } }
			if (shapeFirstID_minus) { if (blendData.shapeFirstID > 0) { blendData.shapeFirstID--; UpdatePedHeadBlendData(ped, blendData, true); } }

			bool shapeSecondID_plus = false, shapeSecondID_minus = false;
			AddTexter("Shape Inherited From Mother", blendData.shapeSecondID, vIdNames, null, shapeSecondID_plus, shapeSecondID_minus);
			if (shapeSecondID_plus) { if (blendData.shapeSecondID < max_ids) { blendData.shapeSecondID++; UpdatePedHeadBlendData(ped, blendData, true); } }
			if (shapeSecondID_minus) { if (blendData.shapeSecondID > 0) { blendData.shapeSecondID--; UpdatePedHeadBlendData(ped, blendData, true); } }

			//bool shapeThirdID_plus = false, shapeThirdID_minus = false;
			//AddTexter("Shape Override", blendData.shapeThirdID, vIdNames, null, shapeThirdID_plus, shapeThirdID_minus);
			//if (shapeThirdID_plus){ if (blendData.shapeThirdID < max_ids){ blendData.shapeThirdID++; UpdatePedHeadBlendData(ped, blendData, true); } }
			//if (shapeThirdID_minus){ if (blendData.shapeThirdID > 0){ blendData.shapeThirdID--; UpdatePedHeadBlendData(ped, blendData, true); } }

			// Skin IDs
			bool skinFirstID_plus = false, skinFirstID_minus = false;
			AddTexter("Tone Inherited From Father", blendData.skinFirstID, vIdNames, null, skinFirstID_plus, skinFirstID_minus);
			if (skinFirstID_plus) { if (blendData.skinFirstID < max_ids) { blendData.skinFirstID++; UpdatePedHeadBlendData(ped, blendData, true); } }
			if (skinFirstID_minus) { if (blendData.skinFirstID > 0) { blendData.skinFirstID--; UpdatePedHeadBlendData(ped, blendData, true); } }

			bool skinSecondID_plus = false, skinSecondID_minus = false;
			AddTexter("Tone Inherited From Mother", blendData.skinSecondID, vIdNames, null, skinSecondID_plus, skinSecondID_minus);
			if (skinSecondID_plus) { if (blendData.skinSecondID < max_ids) { blendData.skinSecondID++; UpdatePedHeadBlendData(ped, blendData, true); } }
			if (skinSecondID_minus) { if (blendData.skinSecondID > 0) { blendData.skinSecondID--; UpdatePedHeadBlendData(ped, blendData, true); } }


			//bool skinThirdID_plus = 0, skinThirdID_minus = 0;
			//AddTexter("Tone Override", blendData.skinThirdID, vIdNames, null, skinThirdID_plus, skinThirdID_minus);
			//if (skinThirdID_plus){ if (blendData.skinThirdID < max_ids) { blendData.skinThirdID++; UpdatePedHeadBlendData(ped, blendData, true); } }
			//if (skinThirdID_minus){ if (blendData.skinThirdID > 0){ blendData.skinThirdID--; UpdatePedHeadBlendData(ped, blendData, true); } }

			// Mixes
			AddBreak("---Adjustment---");
			bool shapeMix_plus = false, shapeMix_minus = false;
			AddNumber("Shape", blendData.shapeMix, 2, null, shapeMix_plus, shapeMix_minus);
			if (shapeMix_plus) { if (blendData.shapeMix < max_mix) { blendData.shapeMix += mix_amountToChange; UpdatePedHeadBlendData(ped, blendData, false); } }
			if (shapeMix_minus) { if (blendData.shapeMix > min_mix) { blendData.shapeMix -= mix_amountToChange; UpdatePedHeadBlendData(ped, blendData, false); } }

			bool skinMix_plus = false, skinMix_minus = false;
			AddNumber("Tone", blendData.skinMix, 2, null, skinMix_plus, skinMix_minus);
			if (skinMix_plus) { if (blendData.skinMix < max_mix) { blendData.skinMix += mix_amountToChange; UpdatePedHeadBlendData(ped, blendData, false); } }
			if (skinMix_minus) { if (blendData.skinMix > min_mix) { blendData.skinMix -= mix_amountToChange; UpdatePedHeadBlendData(ped, blendData, false); } }

			//bool thirdMix_plus = false, thirdMix_minus = false;
			//AddNumber("Override", blendData.thirdMix, 2, null, thirdMix_plus, thirdMix_minus);
			//if (thirdMix_plus){ if (blendData.thirdMix < max_mix){ blendData.thirdMix += mix_amountToChange; UpdatePedHeadBlendData(ped, blendData, false); } }
			//if (thirdMix_minus){ if (blendData.thirdMix > min_mix){ blendData.thirdMix -= mix_amountToChange; UpdatePedHeadBlendData(ped, blendData, false); } }
		}

	}

	// Outfits (saver)

	namespace ComponentChanger_Outfit_catind
	{
		UINT8 _persistentAttachmentsTexterIndex = 0;

		bool Create(GTAentity ped, std::string filePath)
		{
			sub::Spooner::SpoonerEntity eped;
			eped.Handle = ped;
			eped.Type = EntityType::PED;
			eped.Dynamic = true;

			bool bClearDecalOverlays = true;
			bool bAddAttachmentsToSpoonerDb = false;
			bool bStartTaskSeqsOnLoad = true;

			pugi::xml_document oldXml;
			if (oldXml.load_file((const char*)filePath.c_str()).status == pugi::status_ok)
			{
				auto nodeOldRoot = oldXml.child("OutfitPedData");
				bClearDecalOverlays = nodeOldRoot.child("ClearDecalOverlays").text().as_bool(bClearDecalOverlays);
				bAddAttachmentsToSpoonerDb = nodeOldRoot.child("SpoonerAttachments").attribute("SetAttachmentsPersistentAndAddToSpoonerDatabase").as_bool(bAddAttachmentsToSpoonerDb);
				bStartTaskSeqsOnLoad = nodeOldRoot.child("SpoonerAttachments").attribute("StartTaskSequencesOnLoad").as_bool(bStartTaskSeqsOnLoad);
			}

			pugi::xml_document doc;

			auto nodeDecleration = doc.append_child(pugi::node_declaration);
			nodeDecleration.append_attribute("version") = "1.0";
			nodeDecleration.append_attribute("encoding") = "ISO-8859-1";

			auto nodeEntity = doc.append_child("OutfitPedData"); // Root
			nodeEntity.append_child("ClearDecalOverlays").text() = bClearDecalOverlays;
			sub::Spooner::FileManagement::AddEntityToXmlNode(eped, nodeEntity);

			// Attachments
			auto nodeAttachments = nodeEntity.append_child("SpoonerAttachments");
			nodeAttachments.append_attribute("SetAttachmentsPersistentAndAddToSpoonerDatabase") = bAddAttachmentsToSpoonerDb;
			nodeAttachments.append_attribute("StartTaskSequencesOnLoad") = bStartTaskSeqsOnLoad;
			for (auto& e : sub::Spooner::Databases::EntityDb)
			{
				if (e.AttachmentArgs.isAttached)
				{
					GTAentity att;
					if (sub::Spooner::EntityManagement::GetEntityThisEntityIsAttachedTo(e.Handle, att))
					{
						if (att.Handle() == ped.Handle())
						{
							auto nodeAttachment = nodeAttachments.append_child("Attachment");
							sub::Spooner::FileManagement::AddEntityToXmlNode(e, nodeAttachment);
						}
					}
				}
			}

			return doc.save_file((const char*)filePath.c_str());
		}

		bool Apply(GTAped ep, const std::string& filePath, bool applyModelAndHead, bool applyProps, bool applyComps, bool applyDecals, bool applyDamageTextures, bool applyAttachedEntities)
		{
			pugi::xml_document doc;
			if (doc.load_file((const char*)filePath.c_str()).status != pugi::status_ok)
				return false;

			bool bNetworkIsGameInProgress = NETWORK::NETWORK_IS_GAME_IN_PROGRESS() != 0;
			auto nodeEntity = doc.child("OutfitPedData"); // Root
			ep.RequestControl(400);

			//===========================================================================

			Model eModel = nodeEntity.child("ModelHash").text().as_uint();
			auto nodePedStuff = nodeEntity.child("PedProperties");

			if (applyModelAndHead)
			{
				if (ep.Handle() == PLAYER_PED_ID())
				{
					bool bWas241 = (Static_241 == ep.Handle());
					ChangeModel_(eModel);
					ep = PLAYER_PED_ID();
					if (bWas241) Static_241 = ep.Handle();
				}

				if (nodePedStuff.child("HasShortHeight").text().as_bool()) SET_PED_CONFIG_FLAG(ep.Handle(), 223, 1);

				auto nodePedHeadFeatures = nodePedStuff.child("HeadFeatures");
				if (sub::PedHeadFeatures_catind::DoesPedModelSupportHeadFeatures(eModel) && nodePedHeadFeatures)
				{
					auto nodePedHeadBlend = nodePedHeadFeatures.child("ShapeAndSkinTone");
					PED::SET_PED_HEAD_BLEND_DATA(ep.Handle(), 0, 0, 0, 1, 1, 1, 0.0f, 0.0f, 0.0f, false);
					PedHeadBlendData headBlend;
					headBlend.shapeFirstID = nodePedHeadBlend.child("ShapeFatherId").text().as_int();
					headBlend.shapeSecondID = nodePedHeadBlend.child("ShapeMotherId").text().as_int();
					headBlend.shapeThirdID = nodePedHeadBlend.child("ShapeOverrideId").text().as_int();
					headBlend.skinFirstID = nodePedHeadBlend.child("ToneFatherId").text().as_int();
					headBlend.skinSecondID = nodePedHeadBlend.child("ToneMotherId").text().as_int();
					headBlend.skinThirdID = nodePedHeadBlend.child("ToneOverrideId").text().as_int();
					headBlend.shapeMix = nodePedHeadBlend.child("ShapeVal").text().as_float();
					headBlend.skinMix = nodePedHeadBlend.child("ToneVal").text().as_float();
					headBlend.thirdMix = nodePedHeadBlend.child("OverrideVal").text().as_float();
					headBlend.isParent = nodePedHeadBlend.child("IsP").text().as_int();
					ep.HeadBlendData_set(headBlend);

					if (nodePedHeadFeatures.attribute("WasInArray").as_bool())
					{
						sub::PedHeadFeatures_catind::sPedHeadFeatures pedHead;
						pedHead.hairColour = nodePedHeadFeatures.child("HairColour").text().as_int();
						pedHead.hairColourStreaks = nodePedHeadFeatures.child("HairColourStreaks").text().as_int();
						pedHead.eyeColour = nodePedHeadFeatures.child("EyeColour").text().as_int();

						SET_PED_HAIR_TINT(ep.Handle(), pedHead.hairColour, pedHead.hairColourStreaks);
						SET_HEAD_BLEND_EYE_COLOR(ep.Handle(), SYSTEM::ROUND((float)pedHead.eyeColour)); // Sjaak says so

						auto nodePedFacialFeatures = nodePedHeadFeatures.child("FacialFeatures");
						int ii = 0;
						for (auto nodePedFacialFeature = nodePedFacialFeatures.first_child(); nodePedFacialFeature; nodePedFacialFeature = nodePedFacialFeature.next_sibling())
						{
							ii = stoi(std::string(nodePedFacialFeature.name()).substr(1));
							pedHead.facialFeatureData[ii] = nodePedFacialFeature.text().as_float();
							SET_PED_MICRO_MORPH(ep.Handle(), ii, pedHead.facialFeatureData[ii]);
						}

						auto nodePedHeadOverlays = nodePedHeadFeatures.child("Overlays");
						ii = 0;
						for (auto nodePedHeadOverlay = nodePedHeadOverlays.first_child(); nodePedHeadOverlay; nodePedHeadOverlay = nodePedHeadOverlay.next_sibling())
						{
							ii = stoi(std::string(nodePedHeadOverlay.name()).substr(1));
							auto overlayData_index = nodePedHeadOverlay.attribute("index").as_int();
							pedHead.overlayData[ii].colour = nodePedHeadOverlay.attribute("colour").as_int();
							pedHead.overlayData[ii].colourSecondary = nodePedHeadOverlay.attribute("colourSecondary").as_int();
							pedHead.overlayData[ii].opacity = nodePedHeadOverlay.attribute("opacity").as_float();
							SET_PED_HEAD_OVERLAY(ep.Handle(), ii, overlayData_index, pedHead.overlayData[ii].opacity);
							SET_PED_HEAD_OVERLAY_TINT(ep.Handle(), ii, sub::PedHeadFeatures_catind::GetPedHeadOverlayColourType((PedHeadOverlay)ii), pedHead.overlayData[ii].colour, pedHead.overlayData[ii].colourSecondary);
						}
						sub::PedHeadFeatures_catind::vPedHeads[ep.Handle()] = pedHead;
					}
				}

				auto nodeFacialMood = nodePedStuff.child("FacialMood");
				if (nodeFacialMood)
				{
					set_ped_facial_mood(ep, nodeFacialMood.text().as_string());
				}

				int opacityLevel = nodeEntity.child("OpacityLevel").text().as_int(255);
				if (opacityLevel < 255) ep.Alpha_set(opacityLevel);
				ep.SetVisible(nodeEntity.child("IsVisible").text().as_bool());
			}

			if (nodeEntity.child("ClearDecalOverlays").text().as_bool(true)) CLEAR_PED_DECORATIONS(ep.Handle());
			auto& decalsApplied = sub::PedDecals_catind::vPedsAndDecals[ep.Handle()];
			decalsApplied.clear();
			if (applyDecals)
			{
				auto nodePedTattooLogoDecals = nodePedStuff.child("TattooLogoDecals");
				if (nodePedTattooLogoDecals)
				{
					for (auto nodeDecal = nodePedTattooLogoDecals.first_child(); nodeDecal; nodeDecal = nodeDecal.next_sibling())
					{
						sub::PedDecals_catind::PedDecalValue decal(
							nodeDecal.attribute("collection").as_uint(),
							nodeDecal.attribute("value").as_uint()
						);
						decalsApplied.push_back(decal);
						ADD_PED_DECORATION_FROM_HASHES(ep.Handle(), decal.collection, decal.value);
					}
				}
			}

			if (applyComps)
			{
				auto nodePedComps = nodePedStuff.child("PedComps");
				for (auto nodePedCompsObject = nodePedComps.first_child(); nodePedCompsObject; nodePedCompsObject = nodePedCompsObject.next_sibling())
				{
					int pedCompId = stoi(std::string(nodePedCompsObject.name()).substr(1));
					std::string pedCompIdValueStr = nodePedCompsObject.text().as_string();
					int pedCompIdValueDrawable = stoi(pedCompIdValueStr.substr(0, pedCompIdValueStr.find(",")));
					int pedCompIdValueTexture = stoi(pedCompIdValueStr.substr(pedCompIdValueStr.find(",") + 1));

					SET_PED_COMPONENT_VARIATION(ep.Handle(), pedCompId, pedCompIdValueDrawable, pedCompIdValueTexture, 0);
				}
			}
			if (applyProps)
			{
				CLEAR_ALL_PED_PROPS(ep.Handle(), 0);
				auto nodePedProps = nodePedStuff.child("PedProps");
				for (auto nodePedPropsObject = nodePedProps.first_child(); nodePedPropsObject; nodePedPropsObject = nodePedPropsObject.next_sibling())
				{
					int pedPropId = stoi(std::string(nodePedPropsObject.name()).substr(1));
					std::string pedPropIdValueStr = nodePedPropsObject.text().as_string();

					SET_PED_PROP_INDEX(ep.Handle(), pedPropId, stoi(pedPropIdValueStr.substr(0, pedPropIdValueStr.find(","))), stoi(pedPropIdValueStr.substr(pedPropIdValueStr.find(",") + 1)), bNetworkIsGameInProgress, 0);
				}
			}

			sub::PedDamageTextures_catind::ClearAllBloodDamage(ep);
			sub::PedDamageTextures_catind::ClearAllVisibleDamage(ep);
			if (applyDamageTextures)
			{
				auto nodePedDamagePacks = nodePedStuff.child("DamagePacks");
				if (nodePedDamagePacks)
				{
					auto& dmgPacksApplied = sub::PedDamageTextures_catind::vPedsAndDamagePacks[ep.Handle()];
					dmgPacksApplied.clear();
					for (auto nodePedDamagePack = nodePedDamagePacks.first_child(); nodePedDamagePack; nodePedDamagePack = nodePedDamagePack.next_sibling())
					{
						const std::string dpnta = nodePedDamagePack.text().as_string();
						ep.ApplyDamagePack(dpnta, 1.0f, 1.0f);
						dmgPacksApplied.push_back(dpnta);
					}
				}
			}

			if (applyAttachedEntities)
			{
				std::unordered_set<Hash> vModelHashes;
				std::vector<sub::Spooner::SpoonerEntityWithInitHandle> vSpawnedAttachments;
				auto nodeAttachments = nodeEntity.child("SpoonerAttachments");
				bool bAddAttachmentsToSpoonerDb = nodeAttachments.attribute("SetAttachmentsPersistentAndAddToSpoonerDatabase").as_bool(false);
				bool bStartTaskSeqsOnLoad = nodeAttachments.attribute("StartTaskSequencesOnLoad").as_bool(true);
				switch (_persistentAttachmentsTexterIndex)
				{
				case 0: break; // FileDecides
				case 1: bAddAttachmentsToSpoonerDb = false; break; // ForceOff
				case 2: bAddAttachmentsToSpoonerDb = true; break; // ForceOn
				}
				for (auto nodeAttachment = nodeAttachments.first_child(); nodeAttachment; nodeAttachment = nodeAttachment.next_sibling())
				{
					auto e = sub::Spooner::FileManagement::SpawnEntityFromXmlNode(nodeAttachment, vModelHashes);
					sub::Spooner::EntityManagement::AttachEntity(e.e, ep, e.e.AttachmentArgs.boneIndex, e.e.AttachmentArgs.offset, e.e.AttachmentArgs.rotation);
					vSpawnedAttachments.push_back(e);
					if (bAddAttachmentsToSpoonerDb)
					{
						if (!e.e.TaskSequence.empty())
						{
							auto& vTskPtrs = e.e.TaskSequence.AllTasks();
							for (auto& u : vSpawnedAttachments)
							{
								for (auto& tskPtr : vTskPtrs)
								{
									tskPtr->LoadTargetingDressing(u.initHandle, u.e.Handle.Handle());
								}
							}
							if (bStartTaskSeqsOnLoad) e.e.TaskSequence.Start();
						}
						sub::Spooner::Databases::EntityDb.push_back(e.e);
					}
					else
					{
						e.e.Handle.NoLongerNeeded();
					}
				}
				for (auto& amh : vModelHashes)
					Model(amh).Unload();
			}

			//===========================================================================

			return true;
		}

	}

	void ComponentChanger_Outfits()
	{
		using ComponentChanger_Outfit_catind::_persistentAttachmentsTexterIndex;
		std::string& _name = dict;
		std::string& _searchStr = dict2;
		std::string& _dir = dict3;

		bool save2 = false, bCreateFolderPressed = false;
		std::vector<std::string> vfilnames;

		AddTitle("Outfits");

		bool persistentAttachments_plus = 0, persistentAttachments_minus = 0;
		AddTexter("AddAttachmentsToSpoonerDB", _persistentAttachmentsTexterIndex, std::vector<std::string>{ "FileDecides", "ForceOff", "ForceOn" }, null, persistentAttachments_plus, persistentAttachments_minus);
		if (persistentAttachments_plus) { if (_persistentAttachmentsTexterIndex < 2) _persistentAttachmentsTexterIndex++; }
		if (persistentAttachments_minus) { if (_persistentAttachmentsTexterIndex > 0) _persistentAttachmentsTexterIndex--; }

		AddOption("Save Outfit To File", save2);

		AddOption("Create New Folder", bCreateFolderPressed);

		//get_all_filenames_with_extension(GetPathffA(Pathff::Outfit, false), ".xml", vfilnames, false);
		if (_dir.empty()) _dir = GetPathffA(Pathff::Outfit, false);
		DIR* dir_point = opendir(_dir.c_str());
		dirent* entry = readdir(dir_point);
		while (entry)
		{
			vfilnames.push_back(entry->d_name);
			entry = readdir(dir_point);
		}
		closedir(dir_point);

		AddBreak("---Found Files---");

		bool bFolderBackPressed = false;
		AddOption("..", bFolderBackPressed); if (bFolderBackPressed)
		{
			_dir = _dir.substr(0, _dir.rfind("\\"));
			Menu::currentop = 5;
		}

		if (!vfilnames.empty())
		{
			bool bSearchPressed = false;
			AddOption(_searchStr.empty() ? "SEARCH" : _searchStr, bSearchPressed, nullFunc, -1, true); if (bSearchPressed)
			{
				_searchStr = Game::InputBox(_searchStr, 126U, "SEARCH", boost::to_lower_copy(_searchStr));
				boost::to_upper(_searchStr);
				//OnscreenKeyboard::State::Set(OnscreenKeyboard::Purpose::SearchToUpper, _searchStr, 126U, std::string(), _searchStr);
				//OnscreenKeyboard::State::arg1._ptr = reinterpret_cast<void*>(&_searchStr);
			}

			for (auto& filname : vfilnames)
			{
				if (filname.front() == '.' || filname.front() == ',') continue;
				if (!_searchStr.empty()) { if (boost::to_upper_copy(filname).find(_searchStr) == std::string::npos) continue; }

				bool isFolder = PathIsDirectoryA((_dir + "\\" + filname).c_str()) != 0;
				bool isXml = filname.length() > 4 && filname.rfind(".xml") == filname.length() - 4;
				TICKOL icon = TICKOL::NONE;
				if (isFolder) icon = TICKOL::ARROWRIGHT;
				else if (isXml) icon = TICKOL::TICK2;
				bool bFilePressed = false;

				if (isFolder)
				{
					AddTickol(filname + " >>>", true, bFilePressed, bFilePressed, icon, TICKOL::NONE); if (bFilePressed)
					{
						_dir = _dir + "\\" + filname;
						Menu::currentop = 5;
					}

					if (Menu::printingop == *Menu::currentopATM && !bFilePressed)
					{
						if (FolderPreviewBmps_catind::bFolderBmpsEnabled)
							FolderPreviewBmps_catind::DrawBmp(_dir + "\\" + filname);
					}
				}
				else if (isXml)
				{
					AddTickol(filname, true, bFilePressed, bFilePressed, icon, TICKOL::NONE); if (bFilePressed)
					{
						_name = filname.substr(0, filname.rfind('.'));
						Menu::SetSub_delayed = SUB::COMPONENTS_OUTFITS2;
						return;
					}
				}
			}
		}

		if (save2)
		{
			std::string inputStr = Game::InputBox("", 28U, "FMMC_KEY_TIP9");
			if (inputStr.length() > 0)
			{
				ComponentChanger_Outfit_catind::Create(Static_241, _dir + "\\" + inputStr + ".xml");
				Game::Print::PrintBottomLeft("File ~b~created~s~.");
			}
			else Game::Print::PrintError_InvalidInput();
			return;
			//OnscreenKeyboard::State::Set(OnscreenKeyboard::Purpose::SavepIndexOutfitToFile, std::string(), 28U, "FMMC_KEY_TIP9");
			//OnscreenKeyboard::State::arg1._ptr = reinterpret_cast<void*>(&_dir);
		}

		if (bCreateFolderPressed)
		{
			std::string inputStr = Game::InputBox("", 28U, "Enter folder name:");
			if (inputStr.length() > 0)
			{
				if (CreateDirectoryA((_dir + "\\" + inputStr).c_str(), NULL) ||
					GetLastError() == ERROR_ALREADY_EXISTS)
				{
					_dir = _dir + "\\" + inputStr;
					Menu::currentop = 5;
					Game::Print::PrintBottomLeft("Folder ~b~created~s~.");
				}
				else
				{
					Game::Print::PrintBottomCentre("~r~Failed~s~ to create folder.");
					addlog(ige::LogType::LOG_ERROR, "Attempt to create folder " + inputStr + " failed", __FILENAME__);
				}
			}
			else Game::Print::PrintError_InvalidInput();
			return;
			// No OnscreenKeyboard!
		}

		//if (Menu::currentop > Menu::printingop) Menu::Up();
		//else if (Menu::currentop <= 0) Menu::Down();
	}
	void ComponentChanger_Outfits2()
	{
		std::string& _name = dict;
		std::string& _dir = dict3;
		std::string filePath = _dir + "\\" + _name + ".xml";

		bool outfits2_apply = 0, outfits2_applyAllFeatures = 0, outfits2_applyModel = 0,
			outfits2_overwrite = 0, outfits2_rename = 0, outfits2_delete = 0;

		AddTitle(_name);
		AddOption("Apply", outfits2_apply);
		AddOption("Apply Clothing & Attachments", outfits2_applyAllFeatures);
		AddOption((std::string)"Apply " + (Static_241 == PLAYER_PED_ID() ? "Ped Model" : "Head Features"), outfits2_applyModel);
		AddOption("Rename File", outfits2_rename);
		AddOption("Overwrite File", outfits2_overwrite);
		AddOption("Delete File", outfits2_delete);

		if (outfits2_apply)
		{
			outfits2_applyModel = true;
			outfits2_applyAllFeatures = true;
		}
		if (outfits2_applyModel)
		{
			bool s1isme = Static_241 == PLAYER_PED_ID();
			ComponentChanger_Outfit_catind::Apply(Static_241, filePath, true, false, false, false, false, false);
			if (s1isme) Static_241 = PLAYER_PED_ID();
		}
		if (outfits2_applyAllFeatures)
		{
			ComponentChanger_Outfit_catind::Apply(Static_241, filePath, false, true, true, true, true, true);
		}

		if (outfits2_overwrite)
		{
			if (ComponentChanger_Outfit_catind::Create(Static_241, filePath))
				Game::Print::PrintBottomLeft("File ~b~overwritten~s~.");
			else
			{
				Game::Print::PrintBottomCentre("~r~Error:~s~ Unable to overwrite file.");
				addlog(ige::LogType::LOG_ERROR, "Attempt to overwrite file " + filePath + " failed", __FILENAME__);
			}
		}

		if (outfits2_rename)
		{
			std::string newName = Game::InputBox("", 28U, "FMMC_KEY_TIP9", _name);
			if (newName.length() > 0)
			{
				if (rename(filePath.c_str(), (_dir + "\\" + newName + ".xml").c_str()) == 0)
				{
					_name = newName;
					Game::Print::PrintBottomLeft("File ~b~renamed~s~.");
				}
				else Game::Print::PrintBottomCentre("~r~Error:~s~ Unable to rename file.");
				addlog(ige::LogType::LOG_ERROR, "Attempt to rename file " + _name + " to " + newName + "failed", __FILENAME__);
			}
			else Game::Print::PrintError_InvalidInput();
			//OnscreenKeyboard::State::Set(OnscreenKeyboard::Purpose::RenameOutfitFile, std::string(), 28U, "FMMC_KEY_TIP9", _name);
			//OnscreenKeyboard::State::arg1._ptr = reinterpret_cast<void*>(&_name);
			//OnscreenKeyboard::State::arg2._ptr = reinterpret_cast<void*>(&_dir);
		}

		if (outfits2_delete)
		{
			if (remove(filePath.c_str()) == 0)
				Game::Print::PrintBottomLeft("File ~b~deleted~s~.");
			else
			{
				Game::Print::PrintBottomCentre("~r~Error:~s~ Unable to delete file.");
				addlog(ige::LogType::LOG_ERROR, "Attempt to delete file " + filePath + " failed", __FILENAME__);
			}
			Menu::SetSub_previous();
			Menu::Up();
			return;
		}

		//=============================================================================
		pugi::xml_document doc;
		if (doc.load_file((const char*)filePath.c_str()).status == pugi::status_ok)
		{
			AddBreak("---Attributes---");
			auto nodeEntity = doc.child("OutfitPedData"); // Root
			auto nodePedStuff = nodeEntity.child("PedProperties");

			auto nodeClearDecalOverlays = nodeEntity.child("ClearDecalOverlays");
			bool bToggleClearDecalOverlaysPressed = false;
			AddTickol("Clear Previous Decals", nodeClearDecalOverlays.text().as_bool(true), bToggleClearDecalOverlaysPressed, bToggleClearDecalOverlaysPressed, TICKOL::BOXTICK, TICKOL::BOXBLANK); if (bToggleClearDecalOverlaysPressed)
			{
				if (!nodeClearDecalOverlays) nodeClearDecalOverlays = nodeEntity.append_child("ClearDecalOverlays");
				nodeClearDecalOverlays.text() = !nodeClearDecalOverlays.text().as_bool(true);
				doc.save_file((const char*)filePath.c_str());
			}

			auto nodeShortHeighted = nodePedStuff.child("HasShortHeight");
			if (nodeShortHeighted)
			{
				bool bToggleShortHeightedPressed = false;
				AddTickol("Short Height", nodeShortHeighted.text().as_bool(), bToggleShortHeightedPressed, bToggleShortHeightedPressed, TICKOL::BOXTICK, TICKOL::BOXBLANK); if (bToggleShortHeightedPressed)
				{
					nodeShortHeighted.text() = !nodeShortHeighted.text().as_bool();
					doc.save_file((const char*)filePath.c_str());
				}
			}

			auto nodeAddAttachmentsToSpoonerDb = nodeEntity.child("SpoonerAttachments").attribute("SetAttachmentsPersistentAndAddToSpoonerDatabase");
			bool bAddAttachemntsToSpoonerDb = nodeAddAttachmentsToSpoonerDb.as_bool();
			if (nodeAddAttachmentsToSpoonerDb)
			{
				bool bToggleAddAttachmentsToSpoonerDbPressed = false;
				AddTickol("Persistent Attachments (AddToSpoonerDb)", bAddAttachemntsToSpoonerDb, bToggleAddAttachmentsToSpoonerDbPressed, bToggleAddAttachmentsToSpoonerDbPressed, TICKOL::BOXTICK, TICKOL::BOXBLANK); if (bToggleAddAttachmentsToSpoonerDbPressed)
				{
					nodeAddAttachmentsToSpoonerDb = !nodeAddAttachmentsToSpoonerDb.as_bool();
					bAddAttachemntsToSpoonerDb = !bAddAttachemntsToSpoonerDb;
					doc.save_file((const char*)filePath.c_str());
				}
			}

			if (bAddAttachemntsToSpoonerDb)
			{
				auto nodeStartTaskSeqOnLoad = nodeEntity.child("SpoonerAttachments").attribute("StartTaskSequencesOnLoad");
				if (nodeStartTaskSeqOnLoad)
				{
					bool bToggleStartTaskSeqOnLoadPressed = false;
					AddTickol("Start Task Sequences Immediately", nodeStartTaskSeqOnLoad.as_bool(), bToggleStartTaskSeqOnLoadPressed, bToggleStartTaskSeqOnLoadPressed, TICKOL::BOXTICK, TICKOL::BOXBLANK); if (bToggleStartTaskSeqOnLoadPressed)
					{
						nodeStartTaskSeqOnLoad = !nodeStartTaskSeqOnLoad.as_bool();
						doc.save_file((const char*)filePath.c_str());
					}
				}
			}

		}
	}

}


