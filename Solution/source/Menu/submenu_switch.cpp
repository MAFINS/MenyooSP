/*
* Menyoo PC - Grand Theft Auto V single-player trainer mod
* Copyright (C) 2019  MAFINS
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*/
#include "submenu_switch.h"

#include "..\macros.h"

#include "Menu.h"
//#include "submenu_enum.h"

#include "..\Submenus\MainMenu.h"
#include "..\Submenus\Settings.h"
#include "..\Submenus\MiscOptions.h"
#include "..\Submenus\WeaponOptions.h"
#include "..\Submenus\Players.h"
#include "..\Submenus\PlayerOptions.h"
#include "..\Submenus\WeatherOptions.h"
#include "..\Submenus\TimeOptions.h"

#include "..\Submenus\PtfxSubs.h"
#include "..\Submenus\PedAnimation.h"
#include "..\Submenus\PedModelChanger.h"
#include "..\Submenus\PedComponentChanger.h"
#include "..\Submenus\PedSpeech.h"
#include "..\Submenus\BreatheStuff.h"
#include "..\Submenus\GhostRiderMode.h"

#include "..\Submenus\VehicleOptions.h"
#include "..\Submenus\VehicleSpawner.h"
#include "..\Submenus\FunnyVehicles.h"
#include "..\Submenus\VehicleModShop.h"

#include "..\Submenus\Teleport\Teleport_Submenus.h"
#include "..\Submenus\Teleport\OfficeGarages.h"
#include "..\Submenus\Teleport\IeVehicleWarehouses.h"
#include "..\Submenus\Teleport\BikerInteriors.h"
#include "..\Submenus\Teleport\GunRunningInteriors.h"
#include "..\Submenus\Teleport\Hangars.h"
#include "..\Submenus\Teleport\Facilities.h"
#include "..\Submenus\Teleport\Nightclubs.h"
#include "..\Submenus\Teleport\ArenaWar.h"
#include "..\Submenus\Teleport\Yachts.h"

#include "..\Submenus\MiscMapMods.h"
#include "..\Submenus\CutscenePlayer.h"
#include "..\Submenus\AnimalRiding.h"
#include "..\Submenus\StatManager.h"

#include "..\Submenus\Spooner\Submenus.h"
#include "..\Submenus\Spooner\Submenus_TaskSequence.h"


void Menu::submenu_switch()
{
	switch (currentsub)
	{
	case SUB::MAINMENU:					sub::MainMenu(); break;
	case SUB::SETTINGS:					sub::Settings(); break;
	case SUB::SETTINGS_MENUPOS:			sub::SettingsMenuPos_(); break;
	case SUB::SETTINGS_THEMES:			sub::SettingsThemes_catind::Sub_Main(); break;
	case SUB::SETTINGS_COLOURS:			sub::SettingsColours(); break;
	case SUB::SETTINGS_COLOURS2:		sub::SettingsColours2(); break;
	case SUB::SETTINGS_FONTS:			sub::SettingsFonts(); break;
	case SUB::SETTINGS_FONTS2:			sub::SettingsFonts2(); break;
	case SUB::SETTINGS_LANGUAGE:		sub::SettingsLanguage(); break;
	case SUB::TIMECYCLES:				sub::Timecycles_(); break;

	case SUB::OBJECTSPAWNER_OBJS:		sub::ObjectSpawner_objs(); break;

	case SUB::PLAYERSSUB:				sub::PlayersSub_(); break;
	case SUB::PLAYERSSUBAMENU:			sub::PlayersSubAMenu_(); break;
	case SUB::CLONECOMPANIONSUB:		sub::CloneCompanionSub(); break;
	case SUB::PEDEXPLOSIONSUB:			sub::PedExplosionSub(); break;
	case SUB::ATTACHFUNNYOBJECTSUB:		sub::AttachFunnyObjectSub(); break;
	case SUB::PTFXSUB:					sub::Ptfx_catind::PTFXSub(); break;
	case SUB::CLEARAREA:				sub::ClearAreaSub(); break;
	case SUB::PLAYEROPS:				sub::PlayerOps_(); break;
	case SUB::ANIMATIONSUB:				sub::AnimationSub_(); break;
	case SUB::ANIMATIONSUB_SETTINGS:	sub::AnimationSub_Settings(); break;
	case SUB::ANIMATIONSUB_FAVOURITES:	sub::AnimationSub_Favourites(); break;
	case SUB::ANIMATIONSUB_CUSTOM:		sub::AnimationSub_Custom(); break;
	case SUB::ANIMATIONSUB_DEER:		sub::AnimationSub_Deer(); break;
	case SUB::ANIMATIONSUB_SHARK:		sub::AnimationSub_Shark(); break;
	case SUB::ANIMATIONSUB_MISSRAPPEL:	sub::AnimationSub_MissRappel(); break;
	case SUB::ANIMATIONSUB_GESTSIT:		sub::AnimationSub_GestSit(); break;
	case SUB::ANIMATIONSUB_SWAT:		sub::AnimationSub_Swat(); break;
	case SUB::ANIMATIONSUB_GUARDREAC:	sub::AnimationSub_GuardReac(); break;
	case SUB::ANIMATIONSUB_RANDARREST:	sub::AnimationSub_RandArrest(); break;
	case SUB::ANIMATIONSUB_ALLPEDANIMS:			sub::AnimationSub_catind::Sub_AllPedAnims(); break;
	case SUB::ANIMATIONSUB_ALLPEDANIMS_INDICT:	sub::AnimationSub_catind::Sub_AllPedAnims_InDict(); break;
	case SUB::ANIMATIONSUB_TASKSCENARIOS:			sub::AnimationSub_TaskScenarios::AnimationSub_TaskScenarios(); break;
	case SUB::ANIMATIONSUB_TASKSCENARIOS2:			sub::AnimationSub_TaskScenarios::AnimationSub_TaskScenarios2(); break;
	case SUB::FACIALMOOD:				sub::FacialAnims_catind::Sub_FacialMood(); break;
	case SUB::MOVEMENTGROUP:			sub::MovementGroup_(); break;
	case SUB::MODELCHANGER:							sub::ModelChanger_(); break;
	case SUB::MODELCHANGER_FAVOURITES:				sub::PedFavourites_catind::Sub_PedFavourites(); break;
	case SUB::MODELCHANGER_PLAYER:					sub::ModelChanger_Player(); break;
	case SUB::MODELCHANGER_ANIMAL:					sub::ModelChanger_Animal(); break;
	case SUB::MODELCHANGER_AMBFEMALES:				sub::ModelChanger_AmbientFemale(); break;
	case SUB::MODELCHANGER_AMBMALES:				sub::ModelChanger_AmbientMale(); break;
	case SUB::MODELCHANGER_CS:						sub::ModelChanger_Cutscene(); break;
	case SUB::MODELCHANGER_GANGFEMALES:				sub::ModelChanger_GangFemale(); break;
	case SUB::MODELCHANGER_GANGMALES:				sub::ModelChanger_GangMale(); break;
	case SUB::MODELCHANGER_STORY:					sub::ModelChanger_Story(); break;
	case SUB::MODELCHANGER_MP:						sub::ModelChanger_Multiplayer(); break;
	case SUB::MODELCHANGER_SCENARIOFEMALES:			sub::ModelChanger_ScenarioFemale(); break;
	case SUB::MODELCHANGER_SCENARIOMALES:			sub::ModelChanger_ScenarioMale(); break;
	case SUB::MODELCHANGER_ST_SCENARIOFEMALES:		sub::ModelChanger_Story_ScenarioFemale(); break;
	case SUB::MODELCHANGER_ST_SCENARIOMALES:		sub::ModelChanger_Story_ScenarioMale(); break;
	case SUB::MODELCHANGER_OTHERS:					sub::ModelChanger_Others(); break;
	case SUB::COMPONENTS:				sub::ComponentChanger_(); break;
	case SUB::COMPONENTS2:				sub::ComponentChanger2_(); break;
	case SUB::COMPONENTSPROPS:			sub::ComponentChangerProps_(); break;
	case SUB::COMPONENTSPROPS2:			sub::ComponentChangerProps2_(); break;
	case SUB::COMPONENTS_OUTFITS:		sub::ComponentChanger_Outfits(); break;
	case SUB::COMPONENTS_OUTFITS2:		sub::ComponentChanger_Outfits2(); break;
	case SUB::PEDDECALS_TYPES:			sub::PedDecals_catind::Sub_Decals_Types(); break;
	case SUB::PEDDECALS_ZONES:			sub::PedDecals_catind::Sub_Decals_Zones(); break;
	case SUB::PEDDECALS_INZONE:			sub::PedDecals_catind::Sub_Decals_InZone(); break;
	case SUB::VEHICLEOPS:				sub::VehicleOps(); break;
	case SUB::PVOPS:					sub::PVOpsSub_(); break;
	case SUB::VEHICLEWEAPONS:			sub::VehicleWeapons_(); break;
	case SUB::VEHICLEMULTIPLIERS:		sub::VehicleMultipliers_(); break;
	case SUB::VEHICLESPEEDOS:			sub::Speedo_catind::Sub_Main(); break;
	case SUB::VEHICLESPEEDOS_LIGHT:		sub::Speedo_catind::Sub_Themes_Light(); break;
	case SUB::VEHICLESPEEDOS_DARK:		sub::Speedo_catind::Sub_Themes_Dark(); break;
	case SUB::MULTIPLATNEONS:			sub::VehicleMultiPlatNeons_Sub(); break;
	case SUB::VEHICLESLAM:				sub::VehicleSlam_catind::Sub_VehicleSlam(); break;
	case SUB::SPAWNVEHICLE:						sub::SpawnVehicle_(); break;
	case SUB::SPAWNVEHICLE_OPTIONS:				sub::SpawnVehicle_Options(); break;
	case SUB::SPAWNVEHICLE_ALLCATS:				sub::SpawnVehicle_AllCatsSub(); break;
	case SUB::SPAWNVEHICLE_FAVOURITES:			sub::SpawnVehicle_Favourites(); break;
	case SUB::FUNNYVEHICLES:					sub::FunnyVehicles_catind::Sub_FunnyVehicles(); break;
	case SUB::MODSHOP:					sub::ModShop_(); break;
	case SUB::MS_BENNYS:				sub::Bennys_catind::Sub_BennysMain(); break;
	case SUB::MS_EMBLEM:				sub::MSEmblem_(); break;
	case SUB::MSWHEELS:					sub::MSWheels_(); break;
	case SUB::MSWHEELS2:				sub::MSWheels2_(); break;
	case SUB::MSWHEELS3:				sub::MSWheels3_(); break;
	case SUB::MS_TYRESBURST:			sub::MSTyresBurst_(); break;
	case SUB::MSPAINTS:					sub::MSPaints_(); break;
	case SUB::MSPAINTS2:				sub::MSPaints2_(); break; // will do prim/sec/prespawn
	case SUB::MSPAINTS2_CHROME:			sub::MSPaints_catind::Sub_Chrome(); break;
	case SUB::MSPAINTS2_MATTE:			sub::MSPaints_catind::Sub_Matte(); break;
	case SUB::MSPAINTS2_METAL:			sub::MSPaints_catind::Sub_Metal(); break;
	case SUB::MSPAINTS2_CHAMELEON:		sub::MSPaints_catind::Sub_Chameleon(); break;
	case SUB::MSPAINTS2_PEARL:			sub::MSPaints_catind::Sub_Pearl(); break;
	case SUB::MSPAINTS2_METALLIC:		sub::MSPaints_catind::Sub_Metallic(); break;
	case SUB::MSPAINTS2_NORMAL:			sub::MSPaints_catind::Sub_Normal(); break;
	case SUB::MSPAINTS2_UTIL:			sub::MSPaints_catind::Sub_Util(); break;
	case SUB::MSPAINTS2_WORN:			sub::MSPaints_catind::Sub_Worn(); break;
	case SUB::MSPAINTS2_SHARED:			sub::MSPaints_catind::Sub_Shared(); break; // will do wheels, interior and Dashboard
	case SUB::MSPAINTS_RGB:				sub::MSPaints_RGB(); break;
	case SUB::MSCATALL:					sub::MSCatall_(); break;
	case SUB::MSWINDOWS:				sub::MSWindows_catind::MSWindows_(); break;
	case SUB::MSENGINESOUND:			sub::MSEngineSound_(); break;
	case SUB::MSLIGHTS:					sub::MSLights_(); break;
	case SUB::MSDOORS:					sub::MSDoors_(); break;
	case SUB::MSNEONS:					sub::MSNeons_(); break;
	case SUB::MSEXTRA:					sub::MSExtra_(); break;
	case SUB::TELEPORTOPS:					sub::TeleportLocations_catind::Submenus::Sub_TeleportMain(); break;
	case SUB::TELEPORTOPS_CUSTOMCOORDS:		sub::TeleportLocations_catind::Submenus::Sub_CustomCoords(); break;
	case SUB::TELEPORTOPS_SELECTEDCATEGORY:	sub::TeleportLocations_catind::Submenus::Sub_SelectedCategory(); break;
	case SUB::TELEPORTOPS_BLIPLIST:			sub::TeleportLocations_catind::Submenus::Sub_BlipList(); break;
	case SUB::TELEPORTOPS_SAVEDLOCATIONS:	sub::TeleportLocations_catind::Submenus::Sub_SavedLocations(); break;
	case SUB::TELEPORTOPS_OFFICEGARAGES:			sub::TeleportLocations_catind::OfficeGarages::Sub_OfficeGarages(); break;
	case SUB::TELEPORTOPS_OFFICEGARAGES_INLOC:		sub::TeleportLocations_catind::OfficeGarages::Sub_OfficeGarages_InLoc(); break;
	case SUB::TELEPORTOPS_IEVEHICLEWAREHOUSES:		sub::TeleportLocations_catind::IeVehicleWarehouses::Sub_IeVehicleWarehouses(); break;
	case SUB::TELEPORTOPS_IEVEHICLEWAREHOUSES_INLOC:sub::TeleportLocations_catind::IeVehicleWarehouses::Sub_IeVehicleWarehouses_InLoc(); break;
	case SUB::TELEPORTOPS_BIKERCLUBHOUSES:			sub::TeleportLocations_catind::BikerInteriors::Clubhouses::Sub_Clubhouses(); break;
	case SUB::TELEPORTOPS_BIKERCLUBHOUSES_INLOC:	sub::TeleportLocations_catind::BikerInteriors::Clubhouses::Sub_Clubhouses_InLoc(); break;
	case SUB::TELEPORTOPS_BUSINESSES:				sub::TeleportLocations_catind::BikerInteriors::Businesses::Sub_Businesses(); break;
	case SUB::TELEPORTOPS_BUSINESSES_INLOC:			sub::TeleportLocations_catind::BikerInteriors::Businesses::Sub_Businesses_InLoc(); break;
	case SUB::TELEPORTOPS_BUNKERS:					sub::TeleportLocations_catind::GunRunningInteriors::Bunkers::Sub_Bunkers(); break;
	case SUB::TELEPORTOPS_BUNKERS_INLOC:			sub::TeleportLocations_catind::GunRunningInteriors::Bunkers::Sub_Bunkers_InLoc(); break;
	case SUB::TELEPORTOPS_MOC:						sub::TeleportLocations_catind::GunRunningInteriors::Moc::Sub_Moc(); break;
	case SUB::TELEPORTOPS_MOC_INLOC:				sub::TeleportLocations_catind::GunRunningInteriors::Moc::Sub_Moc_InLoc(); break;
	case SUB::TELEPORTOPS_HANGARS:					sub::TeleportLocations_catind::Hangars::Sub_Hangars(); break;
	case SUB::TELEPORTOPS_HANGARS_INLOC:			sub::TeleportLocations_catind::Hangars::Sub_Hangars_InLoc(); break;
	case SUB::TELEPORTOPS_HANGARS_INOPTION:			sub::TeleportLocations_catind::Hangars::Sub_Hangars_InOption(); break;
	case SUB::TELEPORTOPS_FACILITIES:				sub::TeleportLocations_catind::Facilities::Sub_Facilities(); break;
	case SUB::TELEPORTOPS_FACILITIES_INLOC:			sub::TeleportLocations_catind::Facilities::Sub_Facilities_InLoc(); break;
	case SUB::TELEPORTOPS_FACILITIES_INOPTION:		sub::TeleportLocations_catind::Facilities::Sub_Facilities_InOption(); break;
	case SUB::TELEPORTOPS_NIGHTCLUBS:				sub::TeleportLocations_catind::Nightclubs::Sub_Nightclubs(); break;
	case SUB::TELEPORTOPS_ARENAWAR:					sub::TeleportLocations_catind::ArenaWar::Sub_ArenaWar(); break;
	case SUB::TELEPORTOPS_YACHTS:					sub::TeleportLocations_catind::Yachts::Sub_Yachts(); break;
	case SUB::TELEPORTOPS_YACHTS_INGRP:				sub::TeleportLocations_catind::Yachts::Sub_Yachts_InGrp(); break;
	case SUB::WEAPONOPS:				sub::Weaponops(); break;
	case SUB::WEAPONOPS_WEAPONFAVOURITES:	sub::WeaponFavourites_catind::Sub_WeaponFavourites(); break;
	case SUB::WEAPONOPS_INDIVS_CATEGORIES:	sub::WeaponIndivs_catind::Sub_CategoriesList(); break;
	case SUB::WEAPONOPS_INDIVS_CATEGORY:	sub::WeaponIndivs_catind::Sub_InCategory(); break;
	case SUB::WEAPONOPS_INDIVS_ITEM:		sub::WeaponIndivs_catind::Sub_InItem(); break;
	case SUB::WEAPONOPS_INDIVS_ITEM_MODS:	sub::WeaponIndivs_catind::Sub_InItem_Mods(); break;
	case SUB::WEAPONOPS_LOADOUTS:			sub::WeaponsLoadouts_catind::Sub_Loadouts(); break;
	case SUB::WEAPONOPS_LOADOUTS_INITEM:	sub::WeaponsLoadouts_catind::Sub_Loadouts_InItem(); break;
	case SUB::WEAPONOPS_PARACHUTE:			sub::WeaponIndivs_catind::Sub_Parachute(); break;
	case SUB::WEAPONOPS_LASERSIGHT:		sub::LaserSight_catind::Sub_LaserSight(); break;
	case SUB::FORGEGUN:					sub::ForgeGun_(); break;
	case SUB::GRAVITYGUN:				sub::GravityGun_catind::Sub_GravityGun(); break;
	case SUB::KABOOMGUN:				sub::KaboomGun_(); break;
	case SUB::TRIGGERFXGUN:				sub::TriggerFxGun_catind::Sub_GunMain(); break;
	case SUB::BULLETGUN:				sub::BulletGun_(); break;
	case SUB::PEDGUN:					sub::PedGun_(); break;
	case SUB::PEDGUN_ALLPEDS:			sub::PedGun_AllPeds(); break;
	case SUB::OBJECTGUN:				sub::ObjectGun_(); break;
	case SUB::LIST_VEHICLECATS:			sub::List_VehicleCats_Sub(); break;
	case SUB::WEATHEROPS:				sub::WeatherOps_(); break;
	case SUB::CLOUDOPS:					sub::WeatherClouds_catind::sub_CloudOps(); break;
	case SUB::WATERHACK:				sub::WaterHack_catind::Sub_WaterHack(); break;
	case SUB::TIMEOPS:					sub::TimeOps_(); break;
	case SUB::MISCOPS:					sub::MiscOps(); break;
	case SUB::MAPMODS:					sub::MapMods_catind::MapMods_(); break;
	case SUB::MAPMODS2:					sub::MapMods_catind::MapMods2_(); break;
	case SUB::VOICECHANGER:				sub::Speech_catind::Sub_VoiceChanger(); break;
	case SUB::SPEECHPLAYER:				sub::Speech_catind::Sub_AmbientSpeechPlayer(); break;
	case SUB::SPEECHPLAYER_INVOICE:		sub::Speech_catind::Sub_AmbientSpeechPlayer_InVoice(); break;
	case SUB::BREATHESTUFF:				sub::BreatheStuff_catind::BreatheStuffSub_(); break;
	case SUB::VEHICLE_SAVER:			sub::VehicleSaver_catind::Sub_VehSaver(); break;
	case SUB::VEHICLE_SAVER_INITEM:		sub::VehicleSaver_catind::Sub_VehSaver_InItem(); break;
	case SUB::RADIOSUB:					sub::RadioSub_(); break;
	case SUB::AUTODRIVESUB:				sub::VehicleAutoDrive_catind::Sub_AutoDrive(); break;
	case SUB::CUTSCENEPLAYER:			sub::CutscenePlayer_catind::Sub_CutsceneList(); break;
	case SUB::PEDFLAGMANAGER_NAMEDLIST:	sub::PedConfigFlagManager_catind::Sub_FlagList(); break;
	case SUB::PEDFLAGMANAGER_CUSTOM:	sub::PedConfigFlagManager_catind::Sub_CustomFlagSetter(); break;
	case SUB::GHOSTRIDERMODE:			sub::GhostRiderMode_catind::Sub_GhostRiderMode(); break;
	case SUB::PEDDAMAGET_CATEGORYLIST:	sub::PedDamageTextures_catind::Sub_CategoryList(); break;
	case SUB::PEDDAMAGET_BONESELECTION:	sub::PedDamageTextures_catind::Sub_BoneSelection(); break;
	case SUB::PEDDAMAGET_BLOOD:			sub::PedDamageTextures_catind::Sub_Blood(); break;
	case SUB::PEDDAMAGET_DAMAGEDECALS:	sub::PedDamageTextures_catind::Sub_DamageDecals(); break;
	case SUB::PEDDAMAGET_DAMAGEPACKS:	sub::PedDamageTextures_catind::Sub_DamagePacks(); break;
	case SUB::PED_HEADFEATURES_MAIN:				sub::PedHeadFeatures_catind::Sub_Main(); break;
	case SUB::PED_HEADFEATURES_HEADOVERLAYS:		sub::PedHeadFeatures_catind::Sub_HeadOverlays(); break;
	case SUB::PED_HEADFEATURES_HEADOVERLAYS_INITEM:	sub::PedHeadFeatures_catind::Sub_HeadOverlays_InItem(); break;
	case SUB::PED_HEADFEATURES_FACEFEATURES:		sub::PedHeadFeatures_catind::Sub_FaceFeatures(); break;
	case SUB::PED_HEADFEATURES_SKINTONE:			sub::PedHeadFeatures_catind::Sub_SkinTone(); break;
	case SUB::ENTITYALPHALEVEL:			sub::EntityAlphaLevelSub_(); break;
	case SUB::ANIMALRIDING:				sub::AnimalRiding_catind::Sub_AnimalRiding(); break;
	case SUB::TVCHANNELSTUFF_TV:		sub::TVChannelStuff_catind::Sub_TV(); break;

	case SUB::SPOONER_MAIN:							sub::Spooner::Submenus::Sub_SpoonerMain(); break;
	case SUB::SPOONER_SPAWN_CATEGORIES:				sub::Spooner::Submenus::Sub_SpawnCategories(); break;
	case SUB::SPOONER_SPAWN_PROP:					sub::Spooner::Submenus::Sub_SpawnProp(); break;
	case SUB::SPOONER_SPAWN_PROP_FAVOURITES:		sub::Spooner::Submenus::Sub_SpawnProp_Favourites(); break;
	case SUB::SPOONER_SPAWN_PED:					sub::Spooner::Submenus::Sub_SpawnPed(); break;
	case SUB::SPOONER_SPAWN_VEHICLE:				sub::Spooner::Submenus::Sub_SpawnVehicle(); break;
	case SUB::SPOONER_MANAGEMARKERS:							sub::Spooner::Submenus::Sub_ManageMarkers(); break;
	case SUB::SPOONER_MANAGEMARKERS_REMOVAL:					sub::Spooner::Submenus::Sub_ManageMarkers_Removal(); break;
	case SUB::SPOONER_MANAGEMARKERS_INMARKER:					sub::Spooner::Submenus::Sub_ManageMarkers_InMarker(); break;
	case SUB::SPOONER_MANAGEMARKERS_INMARKER_DEST2MARKER:		sub::Spooner::Submenus::Sub_ManageMarkers_InMarker_Dest2Marker(); break;
	case SUB::SPOONER_MANAGEMARKERS_INMARKER_ATTACH:			sub::Spooner::Submenus::Sub_ManageMarkers_InMarker_Attach(); break;
	case SUB::SPOONER_MANAGEDB:						sub::Spooner::Submenus::Sub_ManageEntities(); break;
	case SUB::SPOONER_MANAGEDB_REMOVAL:				sub::Spooner::Submenus::Sub_ManageEntities_Removal(); break;
		//case SUB::SPOONER_MANAGEDB_REMOVAL_FROMDB:		sub::Spooner::Submenus::Sub_ManageEntities_Removal_FromDb(); break;
	case SUB::SPOONER_SAVEFILES:					sub::Spooner::Submenus::Sub_SaveFiles(); break;
	case SUB::SPOONER_SAVEFILES_LOAD:				sub::Spooner::Submenus::Sub_SaveFiles_Load(); break;
	case SUB::SPOONER_SAVEFILES_LOAD_LEGACYSP00N:	sub::Spooner::Submenus::Sub_SaveFiles_Load_LegacySP00N(); break;
	case SUB::SPOONER_VECTOR3_MANUALPLACEMENT:		sub::Spooner::Submenus::Sub_Vector3_ManualPlacement(); break;
	case SUB::SPOONER_QUICKMANUALPLACEMENT:			sub::Spooner::Submenus::Sub_QuickManualPlacement(); break;
	case SUB::SPOONER_GROUPSPOON:					sub::Spooner::Submenus::Sub_GroupSpoon(); break;
	case SUB::SPOONER_GROUPSPOON_SELECTENTITIES:	sub::Spooner::Submenus::Sub_GroupSpoon_SelectEntities(); break;
	case SUB::SPOONER_GROUPSPOON_ATTACHTO:			sub::Spooner::Submenus::Sub_GroupSpoon_AttachTo(); break;
	case SUB::SPOONER_SETTINGS:						sub::Spooner::Submenus::Sub_Settings(); break;
	case SUB::SPOONER_SELECTEDENTITYOPS:			sub::Spooner::Submenus::Sub_SelectedEntityOps(); break;
	case SUB::SPOONER_PEDOPS:						sub::Spooner::Submenus::Sub_PedOps(); break;
	case SUB::SPOONER_PEDOPS_WEAPON:				sub::Spooner::Submenus::Sub_PedOps_Weapon(); break;
	case SUB::SPOONER_PEDOPS_WEAPON_INCATEGORY:		sub::Spooner::Submenus::Sub_PedOps_Weapon_InCategory(); break;
	case SUB::SPOONER_TASKSEQUENCE_TASKLIST:								sub::Spooner::Submenus::Sub_TaskSequence_TaskList(); break;
	case SUB::SPOONER_TASKSEQUENCE_ADDTASK:									sub::Spooner::Submenus::Sub_TaskSequence_AddTask(); break;
	case SUB::SPOONER_TASKSEQUENCE_INTASK:									sub::Spooner::Submenus::Sub_TaskSequence_InTask(); break;
	case SUB::SPOONER_TASKSEQUENCE_TASKSUB_SCENARIOACTION_LIST:				sub::Spooner::Submenus::Sub_TaskSequence::ScenarioAction_list(); break;
	case SUB::SPOONER_TASKSEQUENCE_TASKSUB_PLAYANIMATION_SETTINGS:			sub::Spooner::Submenus::Sub_TaskSequence::PlayAnimation_settings(); break;
	case SUB::SPOONER_TASKSEQUENCE_TASKSUB_PLAYANIMATION_ALLPEDANIMS:		sub::Spooner::Submenus::Sub_TaskSequence::PlayAnimation_allPedAnims(); break;
	case SUB::SPOONER_TASKSEQUENCE_TASKSUB_PLAYANIMATION_ALLPEDANIMS_INDICT:sub::Spooner::Submenus::Sub_TaskSequence::PlayAnimation_allPedAnims_inDict(); break;
	case SUB::SPOONER_TASKSEQUENCE_TASKSUB_PLAYSPEECHWITHVOICE_INVOICE:		sub::Spooner::Submenus::Sub_TaskSequence::PlaySpeechWithVoice_inVoice(); break;
	case SUB::SPOONER_ATTACHMENTOPS:				sub::Spooner::Submenus::Sub_AttachmentOps(); break;
	case SUB::SPOONER_ATTACHMENTOPS_ATTACHTO:		sub::Spooner::Submenus::Sub_AttachmentOps_AttachTo(); break;
	case SUB::SPOONER_ATTACHMENTOPS_SELECTBONE:		sub::Spooner::Submenus::Sub_AttachmentOps_SelectBone(); break;
	case SUB::SPOONER_MANUALPLACEMENT:				sub::Spooner::Submenus::Sub_ManualPlacement(); break;

	case SUB::CLOCK:					sub::Clock_catind::Sub_Clock(); break;

	case SUB::HUDOPTIONS:				sub::HudOptions_catind::Sub_HudOptions(); break;
	case SUB::GAMECAMOPTIONS:			sub::GameCamOptions_catind::Sub_GameCamOptions(); break;

	case SUB::SPSTATMANAGER:						sub::SpStatManager_catind::Sub_SpStatManager(); break;
	case SUB::SPSTATMANAGER_INCHAR:					sub::SpStatManager_catind::Sub_InChar(); break;
	case SUB::SPSTATMANAGER_INCHAR_INLIST:			sub::SpStatManager_catind::Sub_InChar_InList(); break;
	}
}


