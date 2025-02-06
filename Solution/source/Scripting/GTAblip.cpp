/*
* Copyright (C) 2015 crosire
*
* This software is  provided 'as-is', without any express  or implied  warranty. In no event will the
* authors be held liable for any damages arising from the use of this software.
* Permission  is granted  to anyone  to use  this software  for  any  purpose,  including  commercial
* applications, and to alter it and redistribute it freely, subject to the following restrictions:
*
*   1. The origin of this software must not be misrepresented; you must not claim that you  wrote the
*      original  software. If you use this  software  in a product, an  acknowledgment in the product
*      documentation would be appreciated but is not required.
*   2. Altered source versions must  be plainly  marked as such, and  must not be  misrepresented  as
*      being the original software.
*   3. This notice may not be removed or altered from any source distribution.
*/
/*
* ALTERED SOURCE
* Menyoo PC - Grand Theft Auto V single-player trainer mod
* Copyright (C) 2019  MAFINS
*/
#include "GTAblip.h"

#include "..\macros.h"

#include "..\Util\GTAmath.h"
#include "..\Natives\natives2.h"

#include <string>
#include <map>

namespace BlipIcon {
	const std::map<int, std::string> vNames
	{
		{ BlipIcon::Standard, "Standard" },
		{ BlipIcon::BigBlip, "BigBlip" },
		{ BlipIcon::PoliceOfficer, "PoliceOfficer" },
		{ BlipIcon::PoliceArea, "PoliceArea" },
		{ BlipIcon::Square, "Square" },
		{ BlipIcon::Player, "Player" },
		{ BlipIcon::North, "North" },
		{ BlipIcon::Waypoint, "Waypoint" },
		{ BlipIcon::BigCircle, "BigCircle" },
		{ BlipIcon::BigCircleOutline, "BigCircleOutline" },
		{ BlipIcon::ArrowUpOutlined, "ArrowUpOutlined" },
		{ BlipIcon::ArrowDownOutlined, "ArrowDownOutlined" },
		{ BlipIcon::ArrowUp, "ArrowUp" },
		{ BlipIcon::ArrowDown, "ArrowDown" },
		{ BlipIcon::PoliceHelicopterAnimated, "PoliceHelicopterAnimated" },
		{ BlipIcon::Jet, "Jet" },
		{ BlipIcon::Number1, "Number1" },
		{ BlipIcon::Number2, "Number2" },
		{ BlipIcon::Number3, "Number3" },
		{ BlipIcon::Number4, "Number4" },
		{ BlipIcon::Number5, "Number5" },
		{ BlipIcon::Number6, "Number6" },
		{ BlipIcon::Number7, "Number7" },
		{ BlipIcon::Number8, "Number8" },
		{ BlipIcon::Number9, "Number9" },
		{ BlipIcon::Number10, "Number10" },
		{ BlipIcon::GTAOCrew, "GTAOCrew" },
		{ BlipIcon::GTAOFriendly, "GTAOFriendly" },
		{ BlipIcon::Lift, "Lift" },
		{ BlipIcon::RaceFinish, "RaceFinish" },
		{ BlipIcon::Safehouse, "Safehouse" },
		{ BlipIcon::PoliceOfficer2, "PoliceOfficer2" },
		{ BlipIcon::PoliceCarDot, "PoliceCarDot" },
		{ BlipIcon::PoliceHelicopter, "PoliceHelicopter" },
		{ BlipIcon::ChatBubble, "ChatBubble" },
		{ BlipIcon::Garage2, "Garage2" },
		{ BlipIcon::Drugs, "Drugs" },
		{ BlipIcon::Store, "Store" },
		{ BlipIcon::PoliceCar, "PoliceCar" },
		{ BlipIcon::CriminalWanted, "CriminalWanted" },
		{ BlipIcon::PolicePlayer, "PolicePlayer" },
		{ BlipIcon::HeistStore, "HeistStore" },
		{ BlipIcon::PoliceStation, "PoliceStation" },
		{ BlipIcon::Hospital, "Hospital" },
		{ BlipIcon::Helicopter, "Helicopter" },
		{ BlipIcon::StrangersAndFreaks, "StrangersAndFreaks" },
		{ BlipIcon::ArmoredTruck, "ArmoredTruck" },
		{ BlipIcon::TowTruck, "TowTruck" },
		{ BlipIcon::Barber, "Barber" },
		{ BlipIcon::LosSantosCustoms, "LosSantosCustoms" },
		{ BlipIcon::Clothes, "Clothes" },
		{ BlipIcon::TattooParlor, "TattooParlor" },
		{ BlipIcon::Simeon, "Simeon" },
		{ BlipIcon::Lester, "Lester" },
		{ BlipIcon::Michael, "Michael" },
		{ BlipIcon::Trevor, "Trevor" },
		{ BlipIcon::TheJewelStoreJob, "TheJewelStoreJob" },
		{ BlipIcon::Rampage, "Rampage" },
		{ BlipIcon::VinewoodTours, "VinewoodTours" },
		{ BlipIcon::Lamar, "Lamar" },
		{ BlipIcon::Franklin, "Franklin" },
		{ BlipIcon::Chinese, "Chinese" },
		{ BlipIcon::Airport, "Airport" },
		{ BlipIcon::Bar, "Bar" },
		{ BlipIcon::BaseJump, "BaseJump" },
		{ BlipIcon::BiolabHeist, "BiolabHeist" },
		{ BlipIcon::CarWash, "CarWash" },
		{ BlipIcon::ComedyClub, "ComedyClub" },
		{ BlipIcon::Dart, "Dart" },
		{ BlipIcon::ThePortOfLSHeist, "ThePortOfLSHeist" },
		{ BlipIcon::TheBureauRaid, "TheBureauRaid" },
		{ BlipIcon::FIB, "FIB" },
		{ BlipIcon::TheBigScore, "TheBigScore" },
		{ BlipIcon::DollarSign, "DollarSign" },
		{ BlipIcon::Golf, "Golf" },
		{ BlipIcon::AmmuNation, "AmmuNation" },
		{ BlipIcon::Exile, "Exile" },
		{ BlipIcon::TheSharmootaJob, "TheSharmootaJob" },
		{ BlipIcon::ThePaletoScore, "ThePaletoScore" },
		{ BlipIcon::ShootingRange, "ShootingRange" },
		{ BlipIcon::Solomon, "Solomon" },
		{ BlipIcon::StripClub, "StripClub" },
		{ BlipIcon::Tennis, "Tennis" },
		{ BlipIcon::Exile2, "Exile2" },
		{ BlipIcon::Michael2, "Michael2" },
		{ BlipIcon::Triathlon, "Triathlon" },
		{ BlipIcon::OffRoadRaceFinish, "OffRoadRaceFinish" },
		{ BlipIcon::GangPolice, "GangPolice" },
		{ BlipIcon::GangMexicans, "GangMexicans" },
		{ BlipIcon::GangBikers, "GangBikers" },
		{ BlipIcon::Snitch2, "Snitch2" },
		{ BlipIcon::Key, "Key" },
		{ BlipIcon::MovieTheater, "MovieTheater" },
		{ BlipIcon::Music, "Music" },
		{ BlipIcon::PoliceStation2, "PoliceStation2" },
		{ BlipIcon::Marijuana, "Marijuana" },
		{ BlipIcon::Hunting, "Hunting" },
		{ BlipIcon::Objective2, "Objective2" },
		{ BlipIcon::ArmsTraffickingGround, "ArmsTraffickingGround" },
		{ BlipIcon::Nigel, "Nigel" },
		{ BlipIcon::AssaultRifle, "AssaultRifle" },
		{ BlipIcon::Bat, "Bat" },
		{ BlipIcon::Crowbar, "Crowbar" },
		{ BlipIcon::StunGun, "StunGun" },
		{ BlipIcon::AlienWeapon, "AlienWeapon" },
		{ BlipIcon::Grenade, "Grenade" },
		{ BlipIcon::Health, "Health" },
		{ BlipIcon::Knife, "Knife" },
		{ BlipIcon::Molotov, "Molotov" },
		{ BlipIcon::Pistol, "Pistol" },
		{ BlipIcon::RPG, "RPG" },
		{ BlipIcon::Shotgun, "Shotgun" },
		{ BlipIcon::SMG, "SMG" },
		{ BlipIcon::Sniper, "Sniper" },
		{ BlipIcon::SonicWave, "SonicWave" },
		{ BlipIcon::PointOfInterest, "PointOfInterest" },
		{ BlipIcon::GTAOPassive, "GTAOPassive" },
		{ BlipIcon::GTAOUsingMenu, "GTAOUsingMenu" },
		{ BlipIcon::Link, "Link" },
		{ BlipIcon::Minigun, "Minigun" },
		{ BlipIcon::GrenadeLauncher, "GrenadeLauncher" },
		{ BlipIcon::Armor, "Armor" },
		{ BlipIcon::Castle, "Castle" },
		{ BlipIcon::CriminalSnitchMexican, "CriminalSnitchMexican" },
		{ BlipIcon::CriminalSnitchLost, "CriminalSnitchLost" },
		{ BlipIcon::PropertyBikers, "PropertyBikers" },
		{ BlipIcon::PropertyPolice, "PropertyPolice" },
		{ BlipIcon::PropertyVagos, "PropertyVagos" },
		{ BlipIcon::Camera, "Camera" },
		{ BlipIcon::PlayerPositon, "PlayerPositon" },
		{ BlipIcon::BikerHandcuffKeys, "BikerHandcuffKeys" },
		{ BlipIcon::VagosHandcuffKeys, "VagosHandcuffKeys" },
		{ BlipIcon::Handcuffs, "Handcuffs" },
		{ BlipIcon::VagosHandcuffsClosed, "VagosHandcuffsClosed" },
		{ BlipIcon::Yoga, "Yoga" },
		{ BlipIcon::Cab, "Cab" },
		{ BlipIcon::Number11, "Number11" },
		{ BlipIcon::Number12, "Number12" },
		{ BlipIcon::Number13, "Number13" },
		{ BlipIcon::Number14, "Number14" },
		{ BlipIcon::Number15, "Number15" },
		{ BlipIcon::Number16, "Number16" },
		{ BlipIcon::Shrink, "Shrink" },
		{ BlipIcon::Epsilon, "Epsilon" },
		{ BlipIcon::DevinDollarSign2, "DevinDollarSign2" },
		{ BlipIcon::Trevor2, "Trevor2" },
		{ BlipIcon::Trevor3, "Trevor3" },
		{ BlipIcon::Franklin2, "Franklin2" },
		{ BlipIcon::Franklin3, "Franklin3" },
		{ BlipIcon::FranklinC, "FranklinC" },
		{ BlipIcon::PersonalVehicleCar, "PersonalVehicleCar" },
		{ BlipIcon::PersonalVehicleBike, "PersonalVehicleBike" },
		{ BlipIcon::GangVehiclePolice, "GangVehiclePolice" },
		{ BlipIcon::GangPoliceHighlight, "GangPoliceHighlight" },
		{ BlipIcon::Custody, "Custody" },
		{ BlipIcon::CustodyVagos, "CustodyVagos" },
		{ BlipIcon::ArmsTraffickingAir, "ArmsTraffickingAir" },
		{ BlipIcon::PlayerstateArrested, "PlayerstateArrested" },
		{ BlipIcon::PlayerstateCustody, "PlayerstateCustody" },
		{ BlipIcon::PlayerstateKeyholder, "PlayerstateKeyholder" },
		{ BlipIcon::PlayerstatePartner, "PlayerstatePartner" },
		{ BlipIcon::Fairground, "Fairground" },
		{ BlipIcon::PropertyManagement, "PropertyManagement" },
		{ BlipIcon::GangHighlight, "GangHighlight" },
		{ BlipIcon::Altruist, "Altruist" },
		{ BlipIcon::Enemy, "Enemy" },
		{ BlipIcon::OnMission, "OnMission" },
		{ BlipIcon::CashPickup, "CashPickup" },
		{ BlipIcon::Chop, "Chop" },
		{ BlipIcon::Dead, "Dead" },
		{ BlipIcon::CashPickupLost, "CashPickupLost" },
		{ BlipIcon::CashPickupVagos, "CashPickupVagos" },
		{ BlipIcon::CashPickupPolice, "CashPickupPolice" },
		{ BlipIcon::Hooker, "Hooker" },
		{ BlipIcon::Friend, "Friend" },
		{ BlipIcon::CustodyDropoff, "CustodyDropoff" },
		{ BlipIcon::OnMissionPolice, "OnMissionPolice" },
		{ BlipIcon::OnMissionLost, "OnMissionLost" },
		{ BlipIcon::OnMissionVagos, "OnMissionVagos" },
		{ BlipIcon::CriminalCarstealPolice, "CriminalCarstealPolice" },
		{ BlipIcon::CriminalCarstealLost, "CriminalCarstealLost" },
		{ BlipIcon::CriminalCarstealVagos, "CriminalCarstealVagos" },
		{ BlipIcon::SimeonFamily, "SimeonFamily" },
		{ BlipIcon::BountyHit, "BountyHit" },
		{ BlipIcon::GTAOMission, "GTAOMission" },
		{ BlipIcon::GTAOSurvival, "GTAOSurvival" },
		{ BlipIcon::CrateDrop, "CrateDrop" },
		{ BlipIcon::PlaneDrop, "PlaneDrop" },
		{ BlipIcon::Sub, "Sub" },
		{ BlipIcon::Race, "Race" },
		{ BlipIcon::Deathmatch, "Deathmatch" },
		{ BlipIcon::ArmWrestling, "ArmWrestling" },
		{ BlipIcon::AmmuNationShootingRange, "AmmuNationShootingRange" },
		{ BlipIcon::RaceAir, "RaceAir" },
		{ BlipIcon::RaceCar, "RaceCar" },
		{ BlipIcon::RaceSea, "RaceSea" },
		{ BlipIcon::TowTruck2, "TowTruck2" },
		{ BlipIcon::GarbageTruck, "GarbageTruck" },
		{ BlipIcon::GetawayCar, "GetawayCar" },
		{ BlipIcon::GangBike, "GangBike" },
		{ BlipIcon::SafehouseForSale, "SafehouseForSale" },
		{ BlipIcon::Package, "Package" },
		{ BlipIcon::MartinMadrazo, "MartinMadrazo" },
		{ BlipIcon::EnemyHelicopter, "EnemyHelicopter" },
		{ BlipIcon::Boost, "Boost" },
		{ BlipIcon::Devin, "Devin" },
		{ BlipIcon::Marina, "Marina" },
		{ BlipIcon::Garage, "Garage" },
		{ BlipIcon::GolfFlag, "GolfFlag" },
		{ BlipIcon::Hangar, "Hangar" },
		{ BlipIcon::Helipad, "Helipad" },
		{ BlipIcon::JerryCan, "JerryCan" },
		{ BlipIcon::Masks, "Masks" },
		{ BlipIcon::HeistSetup, "HeistSetup" },
		{ BlipIcon::Incapacitated, "Incapacitated" },
		{ BlipIcon::PickupSpawn, "PickupSpawn" },
		{ BlipIcon::BoilerSuit, "BoilerSuit" },
		{ BlipIcon::Completed, "Completed" },
		{ BlipIcon::Rockets, "Rockets" },
		{ BlipIcon::GarageForSale, "GarageForSale" },
		{ BlipIcon::HelipadForSale, "HelipadForSale" },
		{ BlipIcon::MarinaForSale, "MarinaForSale" },
		{ BlipIcon::HangarForSale, "HangarForSale" },
		{ BlipIcon::Business, "Business" },
		{ BlipIcon::BusinessForSale, "BusinessForSale" },
		{ BlipIcon::RaceBike, "RaceBike" },
		{ BlipIcon::Parachute, "Parachute" },
		{ BlipIcon::TeamDeathmatch, "TeamDeathmatch" },
		{ BlipIcon::RaceFoot, "RaceFoot" },
		{ BlipIcon::VehicleDeathmatch, "VehicleDeathmatch" },
		{ BlipIcon::Barry, "Barry" },
		{ BlipIcon::Dom, "Dom" },
		{ BlipIcon::MaryAnn, "MaryAnn" },
		{ BlipIcon::Cletus, "Cletus" },
		{ BlipIcon::Josh, "Josh" },
		{ BlipIcon::Minute, "Minute" },
		{ BlipIcon::Omega, "Omega" },
		{ BlipIcon::Tonya, "Tonya" },
		{ BlipIcon::Paparazzo, "Paparazzo" },
		{ BlipIcon::Crosshair, "Crosshair" },
		{ BlipIcon::Creator, "Creator" },
		{ BlipIcon::CreatorDirection, "CreatorDirection" },
		{ BlipIcon::Abigail, "Abigail" },
		{ BlipIcon::Blimp, "Blimp" },
		{ BlipIcon::Repair, "Repair" },
		{ BlipIcon::Testosterone, "Testosterone" },
		{ BlipIcon::Dinghy, "Dinghy" },
		{ BlipIcon::Fanatic, "Fanatic" },
		{ BlipIcon::Invisible, "Invisible" },
		{ BlipIcon::Information, "Information" },
		{ BlipIcon::CaptureBriefcase, "CaptureBriefcase" },
		{ BlipIcon::LastTeamStanding, "LastTeamStanding" },
		{ BlipIcon::Boat, "Boat" },
		{ BlipIcon::CaptureHouse, "CaptureHouse" },
		{ BlipIcon::GTAOCrew2, "GTAOCrew2" },
		{ BlipIcon::JerryCan2, "JerryCan2" },
		{ BlipIcon::RP, "RP" },
		{ BlipIcon::GTAOPlayerSafehouse, "GTAOPlayerSafehouse" },
		{ BlipIcon::GTAOPlayerSafehouseDead, "GTAOPlayerSafehouseDead" },
		{ BlipIcon::CaptureAmericanFlag, "CaptureAmericanFlag" },
		{ BlipIcon::CaptureFlag, "CaptureFlag" },
		{ BlipIcon::Tank, "Tank" },
		{ BlipIcon::HelicopterAnimated, "HelicopterAnimated" },
		{ BlipIcon::Plane, "Plane" },
		{ BlipIcon::PlayerNoColor, "PlayerNoColor" },
		{ BlipIcon::GunCar, "GunCar" },
		{ BlipIcon::Speedboat, "Speedboat" },
		{ BlipIcon::Heist, "Heist" },
		{ BlipIcon::Stopwatch, "Stopwatch" },
		{ BlipIcon::DollarSignCircled, "DollarSignCircled" },
		{ BlipIcon::Crosshair2, "Crosshair2" },
		{ BlipIcon::DollarSignSquared, "DollarSignSquared" },
		{ BlipIcon::StuntRace, "StuntRace" },
		{ BlipIcon::HotProperty, "HotProperty" },
		{ BlipIcon::KillListCompetitive, "KillListCompetitive" },
		{ BlipIcon::KingOfTheCastle, "KingOfTheCastle" },
		{ BlipIcon::King, "King" },
		{ BlipIcon::DeadDrop, "DeadDrop" },
		{ BlipIcon::PennedIn, "PennedIn" },
		{ BlipIcon::Beast, "Beast" },
		{ BlipIcon::CrossTheLinePointer, "CrossTheLinePointer" },
		{ BlipIcon::CrossTheLine, "CrossTheLine" },
		{ BlipIcon::LamarD, "LamarD" },
		{ BlipIcon::Bennys, "Bennys" },
		{ BlipIcon::LamarDNumber1, "LamarDNumber1" },
		{ BlipIcon::LamarDNumber2, "LamarDNumber2" },
		{ BlipIcon::LamarDNumber3, "LamarDNumber3" },
		{ BlipIcon::LamarDNumber4, "LamarDNumber4" },
		{ BlipIcon::LamarDNumber5, "LamarDNumber5" },
		{ BlipIcon::LamarDNumber6, "LamarDNumber6" },
		{ BlipIcon::LamarDNumber7, "LamarDNumber7" },
		{ BlipIcon::LamarDNumber8, "LamarDNumber8" },
		{ BlipIcon::Yacht, "Yacht" },
		{ BlipIcon::FindersKeepers, "FindersKeepers" },
		{ BlipIcon::Briefcase2, "Briefcase2" },
		{ BlipIcon::ExecutiveSearch, "ExecutiveSearch" },
		{ BlipIcon::Wifi, "Wifi" },
		{ BlipIcon::TurretedLimo, "TurretedLimo" },
		{ BlipIcon::AssetRecovery, "AssetRecovery" },
		{ BlipIcon::YachtLocation, "YachtLocation" },
		{ BlipIcon::Beasted, "Beasted" },
		{ BlipIcon::Loading, "Loading" },
		{ BlipIcon::Random, "Random" },
		{ BlipIcon::SlowTime, "SlowTime" },
		{ BlipIcon::Flip, "Flip" },
		{ BlipIcon::ThermalVision, "ThermalVision" },
		{ BlipIcon::Doped, "Doped" },
		{ BlipIcon::Railgun, "Railgun" },
		{ BlipIcon::Seashark, "Seashark" },
		{ BlipIcon::Blind, "Blind" },
		{ BlipIcon::Warehouse, "Warehouse" },
		{ BlipIcon::WarehouseForSale, "WarehouseForSale" },
		{ BlipIcon::Office, "Office" },
		{ BlipIcon::OfficeForSale, "OfficeForSale" },
		{ BlipIcon::Truck, "Truck" },
		{ BlipIcon::SpecialCargo, "SpecialCargo" },
		{ BlipIcon::Trailer, "Trailer" },
		{ BlipIcon::VIP, "VIP" },
		{ BlipIcon::Cargobob, "Cargobob" },
		{ BlipIcon::AreaCutline, "AreaCutline" },
		{ BlipIcon::Jammed, "Jammed" },
		{ BlipIcon::Ghost, "Ghost" },
		{ BlipIcon::Detonator, "Detonator" },
		{ BlipIcon::Bomb, "Bomb" },
		{ BlipIcon::Shield, "Shield" },
		{ BlipIcon::Stunt, "Stunt" },
		{ BlipIcon::Heart, "Heart" },
		{ BlipIcon::StuntPremium, "StuntPremium" },
		{ BlipIcon::Adversary, "Adversary" },
		{ BlipIcon::BikerClubhouse, "BikerClubhouse" },
		{ BlipIcon::CagedIn, "CagedIn" },
		{ BlipIcon::TurfWar, "TurfWar" },
		{ BlipIcon::Joust, "Joust" },
		{ BlipIcon::Weed, "Weed" },
		{ BlipIcon::Cocaine, "Cocaine" },
		{ BlipIcon::IdentityCard, "IdentityCard" },
		{ BlipIcon::Meth, "Meth" },
		{ BlipIcon::DollarBill, "DollarBill" },
		{ BlipIcon::Package2, "Package2" },
		{ BlipIcon::Capture1, "Capture1" },
		{ BlipIcon::Capture2, "Capture2" },
		{ BlipIcon::Capture3, "Capture3" },
		{ BlipIcon::Capture4, "Capture4" },
		{ BlipIcon::Capture5, "Capture5" },
		{ BlipIcon::Capture6, "Capture6" },
		{ BlipIcon::Capture7, "Capture7" },
		{ BlipIcon::Capture8, "Capture8" },
		{ BlipIcon::Capture9, "Capture9" },
		{ BlipIcon::Capture10, "Capture10" },
		{ BlipIcon::QuadBike, "QuadBike" },
		{ BlipIcon::Bus, "Bus" },
		{ BlipIcon::DrugPackage, "DrugPackage" },
		{ BlipIcon::Hop, "Hop" },
		{ BlipIcon::Adversary4, "Adversary4" },
		{ BlipIcon::Adversary8, "Adversary8" },
		{ BlipIcon::Adversary10, "Adversary10" },
		{ BlipIcon::Adversary12, "Adversary12" },
		{ BlipIcon::Adversary16, "Adversary16" },
		{ BlipIcon::Laptop, "Laptop" },
		{ BlipIcon::Motorcycle, "Motorcycle" },
		{ BlipIcon::SportsCar, "SportsCar" },
		{ BlipIcon::VehicleWarehouse, "VehicleWarehouse" },
		{ BlipIcon::Document, "Document" },
		{ BlipIcon::PoliceStationInverted, "PoliceStationInverted" },
		{ BlipIcon::Junkyard, "Junkyard" },
		{ BlipIcon::PhantomWedge, "PhantomWedge" },
		{ BlipIcon::ArmoredBoxville, "ArmoredBoxville" },
		{ BlipIcon::Ruiner2000, "Ruiner2000" },
		{ BlipIcon::RampBuggy, "RampBuggy" },
		{ BlipIcon::Wastelander, "Wastelander" },
		{ BlipIcon::RocketVoltic, "RocketVoltic" },
		{ BlipIcon::TechnicalAqua, "TechnicalAqua" },
		{ BlipIcon::TargetA, "TargetA" },
		{ BlipIcon::TargetB, "TargetB" },
		{ BlipIcon::TargetC, "TargetC" },
		{ BlipIcon::TargetD, "TargetD" },
		{ BlipIcon::TargetE, "TargetE" },
		{ BlipIcon::TargetF, "TargetF" },
		{ BlipIcon::TargetG, "TargetG" },
		{ BlipIcon::TargetH, "TargetH" },
		{ BlipIcon::Juggernaut, "Juggernaut" },
		{ BlipIcon::Repair2, "Repair2" },
		{ BlipIcon::SteeringWheel, "SteeringWheel" },
		{ BlipIcon::Cup, "Cup" },
		{ BlipIcon::RocketBoost, "RocketBoost" },
		{ BlipIcon::Rocket, "Rocket" },
		{ BlipIcon::MachineGun, "MachineGun" },
		{ BlipIcon::Parachute2, "Parachute2" },
		{ BlipIcon::FiveSeconds, "FiveSeconds" },
		{ BlipIcon::TenSeconds, "TenSeconds" },
		{ BlipIcon::FifteenSeconds, "FifteenSeconds" },
		{ BlipIcon::TwentySeconds, "TwentySeconds" },
		{ BlipIcon::ThirtySeconds, "ThirtySeconds" },
		{ BlipIcon::WeaponSupplies, "WeaponSupplies" },
		{ BlipIcon::Bunker, "Bunker" },
		{ BlipIcon::APC, "APC" },
		{ BlipIcon::Oppressor, "Oppressor" },
		{ BlipIcon::HalfTrack, "HalfTrack" },
		{ BlipIcon::DuneFAV, "DuneFAV" },
		{ BlipIcon::WeaponizedTampa, "WeaponizedTampa" },
		{ BlipIcon::WeaponizedTrailer, "WeaponizedTrailer" },
		{ BlipIcon::MobileOperationsCenter, "MobileOperationsCenter" },
		{ BlipIcon::AdversaryBunker, "AdversaryBunker" },
		{ BlipIcon::BunkerVehicleWorkshop, "BunkerVehicleWorkshop" },
		{ BlipIcon::WeaponWorkshop, "WeaponWorkshop" },
		{ BlipIcon::Cargo, "Cargo" },
		{ BlipIcon::GTAOHangar, "GTAOHangar" },
		{ BlipIcon::TransformCheckpoint, "TransformCheckpoint" },
		{ BlipIcon::TransformRace, "TransformRace" },
		{ BlipIcon::AlphaZ1, "AlphaZ1" },
		{ BlipIcon::Bombushka, "Bombushka" },
		{ BlipIcon::Havok, "Havok" },
		{ BlipIcon::HowardNX25, "HowardNX25" },
		{ BlipIcon::Hunter, "Hunter" },
		{ BlipIcon::Ultralight, "Ultralight" },
		{ BlipIcon::Mogul, "Mogul" },
		{ BlipIcon::V65Molotok, "V65Molotok" },
		{ BlipIcon::P45Nokota, "P45Nokota" },
		{ BlipIcon::Pyro, "Pyro" },
		{ BlipIcon::Rogue, "Rogue" },
		{ BlipIcon::Starling, "Starling" },
		{ BlipIcon::Seabreeze, "Seabreeze" },
		{ BlipIcon::Tula, "Tula" },
		{ BlipIcon::Equipment, "Equipment" },
		{ BlipIcon::Treasure, "Treasure" },
		{ BlipIcon::OrbitalCannon, "OrbitalCannon" },
		{ BlipIcon::Avenger, "Avenger" },
		{ BlipIcon::Facility, "Facility" },
		{ BlipIcon::HeistDoomsday, "HeistDoomsday" },
		{ BlipIcon::SAMTurret, "SAMTurret" },
		{ BlipIcon::Firewall, "Firewall" },
		{ BlipIcon::Node, "Node" },
		{ BlipIcon::Stromberg, "Stromberg" },
		{ BlipIcon::Deluxo, "Deluxo" },
		{ BlipIcon::Thruster, "Thruster" },
		{ BlipIcon::Khanjali, "Khanjali" },
		{ BlipIcon::RCV, "RCV" },
		{ BlipIcon::Volatol, "Volatol" },
		{ BlipIcon::Barrage, "Barrage" },
		{ BlipIcon::Akula, "Akula" },
		{ BlipIcon::Chernobog, "Chernobog" },
		{ BlipIcon::CCTV, "CCTV" },
		{ BlipIcon::StarterPackIdentifier, "StarterPackIdentifier" },
		{ BlipIcon::TurretStation, "TurretStation" },
		{ BlipIcon::RotatingMirror, "RotatingMirror" },
		{ BlipIcon::StaticMirror, "StaticMirror" },
		{ BlipIcon::Proxy, "Proxy" },
		{ BlipIcon::TargetAssault, "TargetAssault" },
		{ BlipIcon::SanAndreasSuperSportCircuit, "SanAndreasSuperSportCircuit" },
		{ BlipIcon::SeaSparrow, "SeaSparrow" },
		{ BlipIcon::Caracara, "Caracara" },
		{ BlipIcon::NightclubProperty, "NightclubProperty" },
		{ BlipIcon::CargoBusinessBattle, "CargoBusinessBattle" },
		{ BlipIcon::NightclubTruck, "NightclubTruck" },
		{ BlipIcon::Jewel, "Jewel" },
		{ BlipIcon::Gold, "Gold" },
		{ BlipIcon::Keypad, "Keypad" },
		{ BlipIcon::HackTarget, "HackTarget" },
		{ BlipIcon::HealthHeart, "HealthHeart" },
		{ BlipIcon::BlastIncrease, "BlastIncrease" },
		{ BlipIcon::BlastDecrease, "BlastDecrease" },
		{ BlipIcon::BombIncrease, "BombIncrease" },
		{ BlipIcon::BombDecrease, "BombDecrease" },
		{ BlipIcon::Rival, "Rival" },
		{ BlipIcon::Drone, "Drone" },
		{ BlipIcon::CashRegister, "CashRegister" },
		{ BlipIcon::CCTV2, "CCTV2" },
		{ BlipIcon::TargetBusinessBattle, "TargetBusinessBattle" },
		{ BlipIcon::FestivalBus, "FestivalBus" },
		{ BlipIcon::Terrorbyte, "Terrorbyte" },
		{ BlipIcon::Menacer, "Menacer" },
		{ BlipIcon::Scramjet, "Scramjet" },
		{ BlipIcon::PounderCustom, "PounderCustom" },
		{ BlipIcon::MuleCustom, "MuleCustom" },
		{ BlipIcon::SpeedoCustom, "SpeedoCustom" },
		{ BlipIcon::Blimp2, "Blimp2" },
		{ BlipIcon::OppressorMkII, "OppressorMkII" },
		{ BlipIcon::B11StrikeForce, "B11StrikeForce" },
		{ BlipIcon::ArenaSeries, "ArenaSeries" },
		{ BlipIcon::ArenaPremium, "ArenaPremium" },
		{ BlipIcon::ArenaWorkshop, "ArenaWorkshop" },
		{ BlipIcon::RaceArenaWar, "RaceArenaWar" },
		{ BlipIcon::ArenaTurret, "ArenaTurret" },
		{ BlipIcon::RCVehicle, "RCVehicle" },
		{ BlipIcon::RCWorkshop, "RCWorkshop" },
		{ BlipIcon::FirePit, "FirePit" },
		{ BlipIcon::Flipper, "Flipper" },
		{ BlipIcon::SeaMine, "SeaMine" },
		{ BlipIcon::TurnTable, "TurnTable" },
		{ BlipIcon::Pit, "Pit" },
		{ BlipIcon::Mines, "Mines" },
		{ BlipIcon::BarrelBomb, "BarrelBomb" },
		{ BlipIcon::RisingWall, "RisingWall" },
		{ BlipIcon::Bollards, "Bollards" },
		{ BlipIcon::SideBollard, "SideBollard" },
		{ BlipIcon::Bruiser, "Bruiser" },
		{ BlipIcon::Brutus, "Brutus" },
		{ BlipIcon::Cerberus, "Cerberus" },
		{ BlipIcon::Deathbike, "Deathbike" },
		{ BlipIcon::Dominator, "Dominator" },
		{ BlipIcon::Impaler, "Impaler" },
		{ BlipIcon::Imperator, "Imperator" },
		{ BlipIcon::Issi, "Issi" },
		{ BlipIcon::Sasquatch, "Sasquatch" },
		{ BlipIcon::Scarab, "Scarab" },
		{ BlipIcon::Slamvam, "Slamvam" },
		{ BlipIcon::ZR380, "ZR380" },
		{ BlipIcon::ComicStore, "ComicStore" },
		{ BlipIcon::CopCar, "CopCar" },
		{ BlipIcon::KingofTheHill, "KingofTheHill" },
		{ BlipIcon::Rucksack, "Rucksack" },
		{ BlipIcon::ShippingContainer, "ShippingContainer" },
		{ BlipIcon::Casino, "Casino" },
		{ BlipIcon::CasinoTable, "CasinoTable" },
		{ BlipIcon::CasinoWheel, "CasinoWheel" },
		{ BlipIcon::CasinoChips, "CasinoChips" },
		{ BlipIcon::CasinoHorse, "CasinoHorse" },
		{ BlipIcon::Limo, "Limo" },
		{ BlipIcon::OpenWheelCar, "OpenWheelCar" },
		{ BlipIcon::Rappel, "Rappel" },
		{ BlipIcon::ScubaGear, "ScubaGear" },
		{ BlipIcon::SnowTruck, "Everon" },
		{ BlipIcon::Buggy1, "Outlaw" },
		{ BlipIcon::Buggy2, "Vagrant" },
		{ BlipIcon::Zhaba, "Zhaba" },
		{ BlipIcon::Arcade, "Arcade" },
		{ BlipIcon::RCTank, "RCTank" },
		{ BlipIcon::Stairs, "Stairs" },
		{ BlipIcon::Camera2, "Camera2" },
		{ BlipIcon::Winky, "Winky" },
		{ BlipIcon::MiniSub, "Avisa" },
		{ BlipIcon::KartRetro, "KartRetro" },
		{ BlipIcon::KartModern, "KartModern" },
		{ BlipIcon::MilitaryQuad, "MilitaryQuad" },
		{ BlipIcon::MilitaryTruck, "MilitaryTruck" },
		{ BlipIcon::ShipWheel, "ShipWheel" },
		{ BlipIcon::UFO, "UFO" },
		{ BlipIcon::SeaSparrow2, "Sparrow" },
		{ BlipIcon::Dinghy2, "Weaponized Dinghy" },
		{ BlipIcon::PatrolBoat, "Patrol Boat" },
		{ BlipIcon::Toreador, "Toreador" },
		{ BlipIcon::Squadee, "Squadee" },
		{ BlipIcon::Alkonost, "Alkonost" },
		{ BlipIcon::AnnihilatorStealth, "Annihilator Stealth" },
		{ BlipIcon::Kostatka, "Kosatka" },
		{ BlipIcon::BoltCutter, "Bolt Cutter" },
		{ BlipIcon::RappelGear, "Rappel Gear" },
		{ BlipIcon::KeyCard, "KeyCard" },
		{ BlipIcon::Password, "Password" },
		{ BlipIcon::IslandHeist, "Island Heist" },
		{ BlipIcon::IslandParty, "Island Party" },
		{ BlipIcon::RadarTower, "Radar Tower" },
		{ BlipIcon::UnderwaterGrate, "Underwater Grate" },
		{ BlipIcon::PowerSwitch, "Power Switch" },
		{ BlipIcon::CompoundGate, "Compound Gate" },
		{ BlipIcon::RappelPoint, "Rappel Point" },
		{ BlipIcon::SubControls, "Sub Controls" },
		{ BlipIcon::SubPeriscope, "Sub Periscope" },
		{ BlipIcon::SubMissiles, "Sub Missiles" },
		{ BlipIcon::Painting, "Painting" },
		{ BlipIcon::AutoShop, "Auto Shop" },
		{ BlipIcon::Anchor, "Anchor" },
		{ BlipIcon::PrizeBox, "Prize Box" },
		{ BlipIcon::ChopShopHeist, "Chop Shop Heist" },
		{ BlipIcon::Securoserv, "SecuroServ" },
		{ BlipIcon::MovieCollection, "Movie Collection" },
		{ BlipIcon::Chalkboard, "Chalkboard" },
		{ BlipIcon::Train, "Train" },
		{ BlipIcon::Slamvan2, "Lost MC Slamvan" },
		{ BlipIcon::Crusader, "Crusader" },
		{ BlipIcon::ConstructionOutfit, "Construction Outfit" },
		{ BlipIcon::VanKeys, "VanKeys" },
		{ BlipIcon::SUVService, "SUVService" },
		{ BlipIcon::SecurityContract, "Security Contract" },
		{ BlipIcon::SafeVault, "SafeVault" },
		{ BlipIcon::Payphone, "Payphone" },
		{ BlipIcon::Patriot3, "PatriotMilSpec" },
		{ BlipIcon::RecordStudio, "RecordStudio" },
		{ BlipIcon::Jubilee, "Jubilee" },
		{ BlipIcon::Granger2, "Granger 3600XL" },
		{ BlipIcon::Dynamite, "Dynamite" },
		{ BlipIcon::Deity, "Deity" },
		{ BlipIcon::Champion, "Champion" },
		{ BlipIcon::Buffalo4, "BuffaloSTX" },
		{ BlipIcon::Agency, "Agency" },
		{ BlipIcon::BikerBar, "Biker Bar" },
		{ BlipIcon::FlamingSkull, "Flaming Skull" },
		{ BlipIcon::CayoPerico, "Cayo Perico" },
		{ BlipIcon::ClubhouseContract, "Clubhouse Contract" },
		{ BlipIcon::Acid, "Acid" },
		{ BlipIcon::AcidLab, "Acid Lab" },
		{ BlipIcon::MysteryPackage, "Mystery Package" },
		{ BlipIcon::GunVan, "Gun Van" },
		{ BlipIcon::WalkieTalkie, "Walkie Talkie" },
		{ BlipIcon::Tractor, "Tractor" },
		{ BlipIcon::JuggaloWarehouse, "Juggalo Warehouse" },
		{ BlipIcon::Duffelbag, "Duffelbag" },
		{ BlipIcon::OilTanker, "OilTanker" },
		{ BlipIcon::Burrito, "Burrito" },
		{ BlipIcon::Bicycle, "Bicycle" },
		{ BlipIcon::Raiju, "Raiju" },
		{ BlipIcon::WeaponizedConada, "Weaponized Conada" },
		{ BlipIcon::Streamer216, "Streamer216" },
		{ BlipIcon::SignalJammer, "Signal Jammer" },
		{ BlipIcon::SalvageYard, "SalvageYard" },
		{ BlipIcon::SalvageYardHeist, "SalvageYardHeist" },
		{ BlipIcon::SalvageYardPlans, "SalvageYardPlans" },
		{ BlipIcon::WeaponCrate, "Weapon Crate" },
		{ BlipIcon::Snowball, "Snowball" },
		{ BlipIcon::Tombstone, "Tombstone" },
		{ BlipIcon::BottomDollarBounty, "Bottom Dollar Bounty" },
		{ BlipIcon::BottomDollarBountyTarget, "Bottomy Dollar Bounty Target" },
		{ BlipIcon::FilmingSchedule, "Filming Schedule" },
		{ BlipIcon::Pizza, "Pizza" },
		{ BlipIcon::AircraftCarrier, "Aircraft Carrier" },
		{ BlipIcon::BottomDollarBailEnforcement, "Bottom Dollar Bail Enforcement" },
		{ BlipIcon::ZombieDisease, "Zombie Disease" },
		{ BlipIcon::ZombieProximity, "Zombie Proximity" },
		{ BlipIcon::ZombieFire, "Zombie Fire" },
		{ BlipIcon::PossessedAnimal, "Possessed Animal" },
		{ BlipIcon::MobilePhone, "Mobile Phone" },
		{ BlipIcon::DarnellBrosGarmentFactory, "Darnell Bros Garment Factory" },
		{ BlipIcon::DarnellBrosGarmentFactoryForSale, "Darnell Bros Garment Factory For Sale" },
		{ BlipIcon::FieldHanger, "Field Hanger" },
		{ BlipIcon::FieldHangerForSale, "Field Hanger For Sale" },
		{ BlipIcon::DH7IronMule, "DH-7 Iron Mule" },
		{ BlipIcon::Cargoship, "Cargoship" },
		{ BlipIcon::Torpedo, "Torpedo" },
		{ BlipIcon::Propellor, "Propellor" },
		{ BlipIcon::SharkTiger, "Shark" },
		{ BlipIcon::FastTravel, "Fast Travel" },
		{ BlipIcon::Duster300H, "Duster 300-H" },
		{ BlipIcon::Titan250D, "Titan 250 D" },
		{ BlipIcon::Collectible, "Collectible" }
	};
}

namespace BlipColour {
	const std::map<int, std::string> vNames
	{
		{ BlipColour::White, "White" },
		{ BlipColour::Red, "Red" },
		{ BlipColour::Green, "Green" },
		{ BlipColour::Blue, "Blue" },
		{ BlipColour::Yellow, "Yellow" },
		{ BlipColour::WhiteNotPure, "WhiteNotPure" },
		{ BlipColour::Yellow2, "Yellow2" },
		{ BlipColour::NetPlayer1, "NetPlayer1" },
		{ BlipColour::NetPlayer2, "NetPlayer2" },
		{ BlipColour::NetPlayer3, "NetPlayer3" },
		{ BlipColour::NetPlayer4, "NetPlayer4" },
		{ BlipColour::NetPlayer5, "NetPlayer5" },
		{ BlipColour::NetPlayer6, "NetPlayer6" },
		{ BlipColour::NetPlayer7, "NetPlayer7" },
		{ BlipColour::NetPlayer8, "NetPlayer8" },
		{ BlipColour::NetPlayer9, "NetPlayer9" },
		{ BlipColour::NetPlayer10, "NetPlayer10" },
		{ BlipColour::NetPlayer11, "NetPlayer11" },
		{ BlipColour::NetPlayer12, "NetPlayer12" },
		{ BlipColour::NetPlayer13, "NetPlayer13" },
		{ BlipColour::NetPlayer14, "NetPlayer14" },
		{ BlipColour::NetPlayer15, "NetPlayer15" },
		{ BlipColour::NetPlayer16, "NetPlayer16" },
		{ BlipColour::NetPlayer17, "NetPlayer17" },
		{ BlipColour::NetPlayer18, "NetPlayer18" },
		{ BlipColour::NetPlayer19, "NetPlayer19" },
		{ BlipColour::NetPlayer20, "NetPlayer20" },
		{ BlipColour::NetPlayer21, "NetPlayer21" },
		{ BlipColour::NetPlayer22, "NetPlayer22" },
		{ BlipColour::NetPlayer23, "NetPlayer23" },
		{ BlipColour::NetPlayer24, "NetPlayer24" },
		{ BlipColour::NetPlayer25, "NetPlayer25" },
		{ BlipColour::NetPlayer26, "NetPlayer26" },
		{ BlipColour::NetPlayer27, "NetPlayer27" },
		{ BlipColour::NetPlayer28, "NetPlayer28" },
		{ BlipColour::NetPlayer29, "NetPlayer29" },
		{ BlipColour::NetPlayer30, "NetPlayer30" },
		{ BlipColour::NetPlayer31, "NetPlayer31" },
		{ BlipColour::NetPlayer32, "NetPlayer32" },
		{ BlipColour::Freemode, "Freemode" },
		{ BlipColour::InactiveMission, "InactiveMission" },
		{ BlipColour::GreyDark, "GreyDark" },
		{ BlipColour::RedLight, "RedLight" },
		{ BlipColour::Michael, "Michael" },
		{ BlipColour::Franklin, "Franklin" },
		{ BlipColour::Trevor, "Trevor" },
		{ BlipColour::GolfPlayer1, "GolfPlayer1" },
		{ BlipColour::GolfPlayer2, "GolfPlayer2" },
		{ BlipColour::GolfPlayer3, "GolfPlayer3" },
		{ BlipColour::GolfPlayer4, "GolfPlayer4" },
		{ BlipColour::Red2, "Red2" },
		{ BlipColour::Purple, "Purple" },
		{ BlipColour::Orange, "Orange" },
		{ BlipColour::GreenDark, "GreenDark" },
		{ BlipColour::BlueLight, "BlueLight" },
		{ BlipColour::BlueDark, "BlueDark" },
		{ BlipColour::Grey, "Grey" },
		{ BlipColour::YellowDark, "YellowDark" },
		{ BlipColour::Blue2, "Blue2" },
		{ BlipColour::PurpleDark, "PurpleDark" },
		{ BlipColour::Red3, "Red3" },
		{ BlipColour::Yellow3, "Yellow3" },
		{ BlipColour::Pink, "Pink" },
		{ BlipColour::GreyLight, "GreyLight" },
		{ BlipColour::Gang, "Gang" },
		{ BlipColour::Gang2, "Gang2" },
		{ BlipColour::Gang3, "Gang3" },
		{ BlipColour::Blue3, "Blue3" },
		{ BlipColour::Blue4, "Blue4" },
		{ BlipColour::Green2, "Green2" },
		{ BlipColour::Yellow4, "Yellow4" },
		{ BlipColour::Yellow5, "Yellow5" },
		{ BlipColour::White2, "White2" },
		{ BlipColour::Yellow6, "Yellow6" },
		{ BlipColour::Blue5, "Blue5" },
		{ BlipColour::Red4, "Red4" },
		{ BlipColour::RedDark, "RedDark" },
		{ BlipColour::Blue6, "Blue6" },
		{ BlipColour::BlueDark2, "BlueDark2" },
		{ BlipColour::RedDark2, "RedDark2" },
		{ BlipColour::MenuYellow, "MenuYellow" },
		{ BlipColour::SimpleBlipDefault, "SimpleBlipDefault" },
		{ BlipColour::Waypoint, "Waypoint" },
		{ BlipColour::Blue7, "Blue7" }
	};
}


bool operator == (const GTAblip& left, const GTAblip& right)
{
	return (left.mHandle == right.mHandle);
}
bool operator != (const GTAblip& left, const GTAblip& right)
{
	return (left.mHandle != right.mHandle);
}
GTAblip& GTAblip::operator = (const GTAblip& right)
{
	this->mHandle = right.mHandle;
	return *this;
}

GTAblip::GTAblip() : mHandle(0)
{
}
GTAblip::GTAblip(int handle) : mHandle(handle)
{
}

int& GTAblip::Handle()
{
	return this->mHandle;
}

uint8_t GTAblip::Alpha() const
{
	return (uint8_t)GET_BLIP_ALPHA(this->mHandle);
}
void GTAblip::SetAlpha(uint8_t value)
{
	SET_BLIP_ALPHA(this->mHandle, value);
}

int GTAblip::Colour() const
{
	return GET_BLIP_COLOUR(this->mHandle);
}
void GTAblip::SetColour(int value)
{
	SET_BLIP_COLOUR(this->mHandle, value);
}

bool GTAblip::IsFlashing() const
{
	return IS_BLIP_FLASHING(this->mHandle) != 0;
}
void GTAblip::SetFlashing(bool value)
{
	SET_BLIP_FLASHES(this->mHandle, value);
}

void GTAblip::SetFriendly(bool value)
{
	SET_BLIP_AS_FRIENDLY(this->mHandle, value);
}

bool GTAblip::IsOnMinimap() const
{
	return IS_BLIP_ON_MINIMAP(this->mHandle) != 0;
}

bool GTAblip::IsShortRange() const
{
	return IS_BLIP_SHORT_RANGE(this->mHandle) != 0;
}
void GTAblip::SetShortRange(bool value)
{
	SET_BLIP_AS_SHORT_RANGE(this->mHandle, value);
}

Vector3 GTAblip::Position_get() const
{
	//return infoid ? GET_BLIP_INFO_ID_COORD(this->mHandle) : GET_BLIP_COORDS(this->mHandle);
	return GET_BLIP_COORDS(this->mHandle);
}
void GTAblip::Position_set(const Vector3& value)
{
	SET_BLIP_COORDS(this->mHandle, value.x, value.y, value.z);
}

void GTAblip::Rotation_set(float valueInDegrees)
{
	SET_BLIP_ROTATION(this->mHandle, valueInDegrees);
}

void GTAblip::SetScale(float value)
{
	SET_BLIP_SCALE(this->mHandle, value);
}

void GTAblip::ShowRoute(bool value)
{
	SET_BLIP_ROUTE(this->mHandle, value);
}

int GTAblip::Icon() const
{
	return GET_BLIP_SPRITE(this->mHandle);
}
void GTAblip::SetIcon(int value)
{
	SET_BLIP_SPRITE(this->mHandle, value);
}

std::string GTAblip::IconName() const
{
	/*auto icon = this->Icon();
	for (auto& i : BlipIcon::vNames)
	{
		if (i.iconId == icon) return i.name;
	}*/
	const auto& it = BlipIcon::vNames.find(this->Icon());
	if (it != BlipIcon::vNames.end())
	{
		return it->second;
	}
	return "Unknown";
}

void GTAblip::SetBlipName(const std::string& value)
{
	BEGIN_TEXT_COMMAND_SET_BLIP_NAME("STRING");
	ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(value.c_str());
	END_TEXT_COMMAND_SET_BLIP_NAME(this->mHandle);
}

int GTAblip::Type() const
{
	return GET_BLIP_INFO_ID_TYPE(this->mHandle);
}

void GTAblip::HideNumber()
{
	HIDE_NUMBER_ON_BLIP(this->mHandle);
}
void GTAblip::ShowNumber(int number)
{
	SHOW_NUMBER_ON_BLIP(this->mHandle, number);
}

bool GTAblip::Exists() const
{
	return DOES_BLIP_EXIST(this->mHandle) != 0;
}
void GTAblip::Remove()
{
	if (DOES_BLIP_EXIST(this->mHandle))
	{
		auto& id = this->mHandle;
		REMOVE_BLIP(&id);
		this->mHandle = id;
	}
}
