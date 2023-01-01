/*
* Menyoo PC - Grand Theft Auto V single-player trainer mod
* Copyright (C) 2019  MAFINS
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*/
#include "AnimalRiding.h"

#include "..\macros.h"

#include "..\Menu\Menu.h"
#include "..\Menu\Routine.h"

#include "..\Natives\natives2.h"
#include "..\Scripting\enums.h"
#include "..\Util\ExePath.h"
#include "..\Util\GTAmath.h"
#include "..\Scripting\Model.h"
#include "..\Misc\GenericLoopedMode.h"
#include "..\Scripting\GTAentity.h"
#include "..\Scripting\GTAped.h"
#include "..\Scripting\WeaponIndivs.h"
#include "..\Scripting\World.h"
#include "..\Scripting\Game.h"
#include "..\Scripting\CustomHelpText.h"
#include "..\Scripting\ModelNames.h"

#include <string>
#include <vector>
#include <pugixml\src\pugixml.hpp>

namespace sub
{
	namespace AnimalRiding_catind
	{
		struct AnimalAndSeat { Model model; int attachBone; Vector3 position; Vector3 rotation; };
		std::vector<AnimalAndSeat> vAnimals
		{
			{ PedHash::Deer, 24816, Vector3(-0.3f, 0.0f, 0.3f), Vector3(180.0f, 0.0f, 90.0f) },
			{ PedHash::Cow, 24816, Vector3(-0.3f, 0.0f, 0.1f), Vector3(180.0f, 0.0f, 90.0f) },
			{ PedHash::MountainLion, 24816, Vector3(-0.3f, 0.0f, 0.24f), Vector3(180.0f, 0.0f, 90.0f) }

		};

		void PopulateAnimals()
		{
			pugi::xml_document doc;
			if (doc.load_file((const wchar_t*)(GetPathffW(Pathff::Main, true) + (L"AnimalRidingData.xml")).c_str()).status == pugi::status_ok)
			{
				vAnimals.clear();
				auto& nodeRoot = doc.document_element();//doc.child("AnimalRidingData");
				auto& nodePeds = nodeRoot.child("Peds");
				for (auto& nodePed = nodePeds.first_child(); nodePed; nodePed = nodePed.next_sibling())
				{
					AnimalAndSeat a;
					a.model = GET_HASH_KEY(nodePed.attribute("modelName").as_string());
					a.attachBone = nodePed.child("Bone").text().as_int();
					auto& nodePos = nodePed.child("Position");
					a.position = Vector3(nodePos.attribute("X").as_float(), nodePos.attribute("Y").as_float(), nodePos.attribute("Z").as_float());
					auto& nodeRot = nodePed.child("Rotation");
					a.rotation = Vector3(nodeRot.attribute("X").as_float(), nodeRot.attribute("Y").as_float(), nodeRot.attribute("Z").as_float());
					vAnimals.push_back(a);
				}
			}
		}

		class AnimalRidingMode final : public GenericLoopedMode
		{
		private:
			GTAped myHumanPed;
			GTAentity myAnimalPed;
			std::vector<s_Weapon_Components_Tint> myHumanWeaponBackup;
		public:
			void TurnOn() override
			{
				GenericLoopedMode::TurnOn();

				myHumanPed = 0;
				myAnimalPed = 0;
				this->PrintInstructions();
			}
			void TurnOff() override
			{
				GenericLoopedMode::TurnOff();

				this->UnMount();
			}

			void Tick() override
			{
				if (this->bEnabled)
				{
					this->DoAnimalRidingTick();
				}
			}
			inline void DoAnimalRidingTick()
			{
				GTAped myPed = PLAYER_PED_ID();
				auto& myPos = myPed.Position_get();

				if ((myPed.Handle() != myAnimalPed.Handle()))
				{
					//std::vector<Entity> closestPeds;
					//GTAmemory::GetPedHandles(closestPeds, myPos, 1.0f);

					for (auto& ped : _nearbyPeds)
					{
						for (auto& a : AnimalRiding_catind::vAnimals)
						{
							if (a.model.hash == GET_ENTITY_MODEL(ped) && !IS_ENTITY_DEAD(ped, false))
							{
								if (myPos.DistanceTo(GET_ENTITY_COORDS(ped, 1)) < 1.6f)
								{
									this->PrintHelpMessage();
									if (this->IsMountKeyPressed())
									{
										this->Mount(ped, a);
										break;
									}
								}
							}
						}
					}
				}
				else
				{
					if (this->IsMountKeyPressed())
					{
						this->UnMount();
					}
					else
					{
						DISABLE_CONTROL_ACTION(0, INPUT_COVER, true);

						REMOVE_ALL_PED_WEAPONS(myHumanPed.Handle(), true);
						myHumanPed.Health_set(myHumanPed.MaxHealth_get());
						set_ped_invincible_on(myHumanPed.Handle());

						REMOVE_ALL_PED_WEAPONS(myAnimalPed.Handle(), true);
						myAnimalPed.Health_set(myAnimalPed.MaxHealth_get());
						set_ped_invincible_on(myAnimalPed.Handle());
					}
				}
			}

			void Mount(GTAped ped, const AnimalRiding_catind::AnimalAndSeat& a)
			{
				//ped.MissionEntity_set(true);
				ped.RelationshipGroup_set("PLAYER");

				myHumanPed = PLAYER_PED_ID();
				myHumanPed.StoreWeaponsInArray(myHumanWeaponBackup);

				myHumanPed.Position_set(ped.Position_get());
				ped.FreezePosition(true);
				myHumanPed.FreezePosition(true);

				myHumanPed.AttachTo(ped, ped.GetBoneIndex(a.attachBone), false, a.position, a.rotation);

				switch (a.model.hash)
				{
				default: //myHumanPed.Task().PlayAnimation("amb@code_human_in_car_idles@generic@ds@idle_a", "idle_a", 2.0, -2.0, -1, 33, 0, false); break;
				case PedHash::MountainLion: myHumanPed.Task().PlayAnimation("rcmjosh2", "josh_sitting_loop", 4.0f, -4.0f, -1, 1, 0, false); break;
				}

				ped.FreezePosition(false);
				myHumanPed.FreezePosition(false);

				WAIT(50);
				CHANGE_PLAYER_PED(PLAYER_ID(), ped.Handle(), true, true); // true,false?
				WAIT(50);
				myAnimalPed = PLAYER_PED_ID();

			}

			void UnMount()
			{
				if (myAnimalPed.Exists())
				{
					set_ped_invincible_off(myAnimalPed.Handle());
				}

				if (myAnimalPed.Handle() != 0)
				{
					if (myHumanPed.Exists())
					{
						CHANGE_PLAYER_PED(PLAYER_ID(), myHumanPed.Handle(), true, true);
						WAIT(50);
						myHumanPed = PLAYER_PED_ID();
						myHumanPed.Detach();
						set_ped_invincible_off(myHumanPed.Handle());
						myHumanPed.GiveWeaponsFromArray(myHumanWeaponBackup);
					}
					else
					{
						myHumanPed = PLAYER_PED_ID();
						auto& newPed = World::CreatePed(PedHash::Michael, myHumanPed.Position_get(), myHumanPed.Heading_get(), false);
						WAIT(50);
						CHANGE_PLAYER_PED(PLAYER_ID(), newPed.Handle(), true, true);
						WAIT(50);
						myHumanPed = PLAYER_PED_ID();
						myHumanPed.GiveWeaponsFromArray(myHumanWeaponBackup);
					}
				}
				myHumanPed = 0;
				myAnimalPed = 0;
			}

			inline bool IsMountKeyPressed()
			{
				return IS_DISABLED_CONTROL_JUST_PRESSED(2, INPUT_VEH_EXIT) != 0;
			}

			inline void PrintHelpMessage()
			{
				Game::CustomHelpText::ShowTimedText("Press ~INPUT_VEH_EXIT~ to mount onto this animal.", 100);
			}
			void PrintInstructions()
			{
				Game::Print::PrintBottomLeft("Approach a supported animal and hop on it like it's a car!");
			}

		};

		AnimalRidingMode g_animalRidingMode;

		void ToggleOnOff()
		{
			g_animalRidingMode.Toggle();
		}
		void Tick()
		{
			g_animalRidingMode.Tick();
		}
		bool& Enabled()
		{
			return g_animalRidingMode.Enabled();
		}

		void SpawnAnimalRide(const Model& model)
		{
			GTAped myPed = PLAYER_PED_ID();
			auto& myPos = myPed.Position_get();
			auto myHeading = myPed.Heading_get();
			auto& myRot = myPed.Rotation_get();
			auto& myDir = Vector3::RotationToDirection(myRot);

			auto& animalRide = World::CreatePed(model, myPos + myDir * 3.0f, myHeading, false); // An animal created with ped type 26 (human) gg

			animalRide.RelationshipGroup_set("PLAYER");

			TaskSequence seq;
			seq.AddTask().GuardCurrentPosition();
			seq.Close();
			animalRide.Task().PerformSequence(seq);
			seq.Clear();
			model.Unload();
		}

		void Sub_AnimalRiding()
		{
			AddTitle("Animal Riding");

			AddLocal("Toggle", AnimalRiding_catind::g_animalRidingMode.Enabled(), AnimalRiding_catind::ToggleOnOff, AnimalRiding_catind::ToggleOnOff);

			AddBreak("---Spawn A Ride---");
			for (auto& a : vAnimals)
			{
				bool bSpawnRidePressed = false;
				AddOption(get_ped_model_label(a.model, true), bSpawnRidePressed); if (bSpawnRidePressed)
				{
					AnimalRiding_catind::SpawnAnimalRide(a.model);
				}
			}

			AddBreak("---Animal Data---");
			AddOption("Reload Data From File", null, PopulateAnimals);
		}

	}

}


