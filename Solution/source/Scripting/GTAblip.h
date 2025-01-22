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
#pragma once

//#include <better-enums-master\enum.h>

#include <map>
#include <string>

typedef unsigned short UINT16;
typedef unsigned char uint8_t;
class Vector3;

namespace BlipType {
	enum BlipType
	{
		Waypoint = 4,
	};
}

namespace BlipIcon {
	enum BlipIcon : int
	{
		//kagikn
		///<summary>The default English text for this value is "Destination".</summary>
		Standard = 1,
		///<summary>The default English text for this value is "Destination".</summary>
		BigBlip = 2,
		///<summary>The default English text for this value is "Police".</summary>
		PoliceOfficer = 3,
		///<summary>When this value is set, the blip will flash. The default English text for this value is "Objective".</summary>
		PoliceArea = 4,
		///<summary>The sprite shape is square and the default English text for this value is "Objective".</summary>
		Square = 5,
		Player = 6,
		North = 7,
		Waypoint = 8,
		BigCircle = 9,
		BigCircleOutline = 10,
		ArrowUpOutlined = 11,
		ArrowDownOutlined = 12,
		ArrowUp = 13,
		ArrowDown = 14,
		PoliceHelicopterAnimated = 15,
		///<summary>The default English text for this value is "Police Plane".</summary>
		Jet = 16,
		Number1 = 17,
		Number2 = 18,
		Number3 = 19,
		Number4 = 20,
		Number5 = 21,
		Number6 = 22,
		Number7 = 23,
		Number8 = 24,
		Number9 = 25,
		Number10 = 26,
		GTAOCrew = 27,
		GTAOFriendly = 28,
		///<summary>The default English text for this value is "Cable Car".</summary>
		Lift = 36,
		RaceFinish = 38,
		Safehouse = 40,
		///<summary>The default English text for this value is "Police".</summary>
		PoliceOfficer2 = 41,
		///<summary>The default English text for this value is "Police Chase".</summary>
		PoliceCarDot = 42,
		PoliceHelicopter = 43,
		///<summary>The default English text for this value is "Snitch".</summary>
		ChatBubble = 47,
		///<summary>The default English text for this value is "Criminal Carsteal".</summary>
		Garage2 = 50,
		///<summary>The default English text for this value is "Criminal Drugs".</summary>
		Drugs = 51,
		///<summary>The default English text for this value is "Criminal Holdups".</summary>
		Store = 52,
		PoliceCar = 56,
		CriminalWanted = 57,
		PolicePlayer = 58,
		HeistStore = 59,
		PoliceStation = 60,
		Hospital = 61,
		Helicopter = 64,
		StrangersAndFreaks = 66,
		ArmoredTruck = 67,
		TowTruck = 68,
		Barber = 71,
		LosSantosCustoms = 72,
		///<summary>The default English text for this value is "Clothes Store".</summary>
		Clothes = 73,
		TattooParlor = 75,
		Simeon = 76,
		Lester = 77,
		Michael = 78,
		Trevor = 79,
		TheJewelStoreJob = 80,
		Rampage = 84,
		VinewoodTours = 85,
		Lamar = 86,
		Franklin = 88,
		Chinese = 89,
		Airport = 90,
		Bar = 93,
		BaseJump = 94,
		BiolabHeist = 96,
		CarWash = 100,
		ComedyClub = 102,
		///<summary>The default English text for this value is "Darts".</summary>
		Dart = 103,
		ThePortOfLSHeist = 104,
		TheBureauRaid = 105,
		FIB = 106,
		TheBigScore = 107,
		///<summary>The default English text for this value is "Devin".</summary>
		DollarSign = 108,
		Golf = 109,
		AmmuNation = 110,
		Exile = 112,
		TheSharmootaJob = 113,
		ThePaletoScore = 118,
		ShootingRange = 119,
		Solomon = 120,
		StripClub = 121,
		Tennis = 122,
		Exile2 = 123,
		Michael2 = 124,
		Triathlon = 126,
		///<summary>The default English text for this value is "Off Road Racing".</summary>
		OffRoadRaceFinish = 127,
		GangPolice = 128,
		GangMexicans = 129,
		GangBikers = 130,
		Snitch2 = 133,
		///<summary>The default English text for this value is "Criminal Cuff Keys".</summary>
		Key = 134,
		MovieTheater = 135,
		///<summary>The default English text for this value is "Music Venue".</summary>
		Music = 136,
		PoliceStation2 = 137,
		///<summary>The default English text for this value is "Stash".</summary>
		Marijuana = 140,
		Hunting = 141,
		Objective2 = 143,
		ArmsTraffickingGround = 147,
		Nigel = 149,
		AssaultRifle = 150,
		Bat = 151,
		Crowbar = 849,
		StunGun = 891,
		AlienWeapon = 725,
		Grenade = 152,
		Health = 153,
		Knife = 154,
		Molotov = 155,
		Pistol = 156,
		RPG = 157,
		Shotgun = 158,
		SMG = 159,
		Sniper = 160,
		SonicWave = 161,
		PointOfInterest = 162,
		GTAOPassive = 163,
		GTAOUsingMenu = 164,
		///<summary>The default English text for this value is "Gang Police Partner".</summary>
		Link = 171,
		Minigun = 173,
		GrenadeLauncher = 174,
		Armor = 175,
		///<summary>The default English text for this value is "Property Takeover".</summary>
		Castle = 176,
		CriminalSnitchMexican = 177,
		CriminalSnitchLost = 178,
		PropertyBikers = 181,
		PropertyPolice = 182,
		PropertyVagos = 183,
		Camera = 184,
		PlayerPositon = 185,
		BikerHandcuffKeys = 186,
		VagosHandcuffKeys = 187,
		///<summary>The default English text for this value is "Biker Handcuffs Closed".</summary>
		Handcuffs = 188,
		VagosHandcuffsClosed = 189,
		Yoga = 197,
		Cab = 198,
		Number11 = 199,
		Number12 = 200,
		Number13 = 201,
		Number14 = 202,
		Number15 = 203,
		Number16 = 204,
		Shrink = 205,
		Epsilon = 206,
		DevinDollarSign2 = 207,
		Trevor2 = 208,
		Trevor3 = 209,
		Franklin2 = 210,
		Franklin3 = 211,
		FranklinC = 214,
		///<summary>The default English text for this value is "Gang Vehicle".</summary>
		PersonalVehicleCar = 225,
		///<summary>The default English text for this value is "Gang Vehicle Bikers".</summary>
		PersonalVehicleBike = 226,
		GangVehiclePolice = 227,
		GangPoliceHighlight = 233,
		Custody = 237,
		CustodyVagos = 238,
		ArmsTraffickingAir = 251,
		PlayerstateArrested = 252,
		PlayerstateCustody = 253,
		PlayerstateKeyholder = 255,
		PlayerstatePartner = 256,
		Fairground = 266,
		PropertyManagement = 267,
		GangHighlight = 268,
		Altruist = 269,
		Enemy = 270,
		OnMission = 271,
		CashPickup = 272,
		Chop = 273,
		Dead = 274,
		CashPickupLost = 276,
		CashPickupVagos = 277,
		CashPickupPolice = 278,
		///<summary>The default English text for this value is "Drop Off Hooker".</summary>
		Hooker = 279,
		Friend = 280,
		CustodyDropoff = 285,
		OnMissionPolice = 286,
		OnMissionLost = 287,
		OnMissionVagos = 288,
		CriminalCarstealPolice = 289,
		CriminalCarstealLost = 290,
		CriminalCarstealVagos = 291,
		SimeonFamily = 293,
		BountyHit = 303,
		///<summary>The default English text for this value is "UGC Mission".</summary>
		GTAOMission = 304,
		///<summary>The default English text for this value is "Horde".</summary>
		GTAOSurvival = 305,
		CrateDrop = 306,
		PlaneDrop = 307,
		Sub = 308,
		Race = 309,
		Deathmatch = 310,
		ArmWrestling = 311,
		AmmuNationShootingRange = 313,
		RaceAir = 314,
		///<summary>The default English text for this value is "Street Race".</summary>
		RaceCar = 315,
		///<summary>The default English text for this value is "Sea Race".</summary>
		RaceSea = 316,
		TowTruck2 = 317,
		GarbageTruck = 318,
		GetawayCar = 326,
		GangBike = 348,
		///<summary>The default English text for this value is "Property For Sale".</summary>
		SafehouseForSale = 350,
		///<summary>The default English text for this value is "Gang Attack Package".</summary>
		Package = 351,
		MartinMadrazo = 352,
		EnemyHelicopter = 353,
		Boost = 354,
		Devin = 355,
		Marina = 356,
		Garage = 357,
		GolfFlag = 358,
		Hangar = 359,
		Helipad = 360,
		JerryCan = 361,
		///<summary>The default English text for this value is "Masks Store".</summary>
		Masks = 362,
		HeistSetup = 363,
		Incapacitated = 364,
		///<summary>The default English text for this value is "Spawn Point Pickup".</summary>
		PickupSpawn = 365,
		BoilerSuit = 366,
		Completed = 367,
		///<summary>The default English text for this value is "Missiles".</summary>
		Rockets = 368,
		GarageForSale = 369,
		HelipadForSale = 370,
		///<summary>The default English text for this value is "Dock For Sale".</summary>
		MarinaForSale = 371,
		HangarForSale = 372,
		Business = 374,
		BusinessForSale = 375,
		///<summary>The default English text for this value is "Bike Race".</summary>
		RaceBike = 376,
		Parachute = 377,
		TeamDeathmatch = 378,
		///<summary>The default English text for this value is "Foot Race".</summary>
		RaceFoot = 379,
		VehicleDeathmatch = 380,
		Barry = 381,
		Dom = 382,
		MaryAnn = 383,
		Cletus = 384,
		Josh = 385,
		Minute = 386,
		Omega = 387,
		Tonya = 388,
		Paparazzo = 389,
		///<summary>The default English text for this value is "Aim".</summary>
		Crosshair = 390,
		Creator = 398,
		CreatorDirection = 399,
		Abigail = 400,
		Blimp = 401,
		Repair = 402,
		///<summary>The default English text for this value is "Raging".</summary>
		Testosterone = 403,
		Dinghy = 404,
		Fanatic = 405,
		///<summary>This blip sprite is invisible and the default English text for this value is "Invisible".</summary>
		Invisible = 406,
		Information = 407,
		CaptureBriefcase = 408,
		LastTeamStanding = 409,
		Boat = 410,
		CaptureHouse = 411,
		GTAOCrew2 = 412,
		JerryCan2 = 415,
		RP = 416,
		GTAOPlayerSafehouse = 417,
		///<summary>In GTA Online, when some player is a bounty and is in a safehouse, a blip with this sprite will be attached.</summary>
		GTAOPlayerSafehouseDead = 418,
		CaptureAmericanFlag = 419,
		CaptureFlag = 420,
		Tank = 421,
		HelicopterAnimated = 422,
		///<summary>The sprite is the same as <see cref="BlipIcon::Jet"></see> has, but the default English text for this value is "Jet".</summary>
		Plane = 423,
		///<summary>This enum is wrongly named. The sprite doesn't have outline, but you can change the color.</summary>
		PlayerNoColor = 425,
		///<summary>The default English text for this value is "Insurgent".</summary>
		GunCar = 426,
		Speedboat = 427,
		Heist = 428,
		Stopwatch = 430,
		DollarSignCircled = 431,
		Crosshair2 = 432,
		DollarSignSquared = 434,
		StuntRace = 435,
		HotProperty,
		KillListCompetitive,
		KingOfTheCastle,
		///<summary>The default English text for this value is "Player King".</summary>
		King,
		DeadDrop,
		PennedIn,
		Beast,
		CrossTheLinePointer,
		CrossTheLine,
		LamarD,
		Bennys,
		LamarDNumber1,
		LamarDNumber2,
		LamarDNumber3,
		LamarDNumber4,
		LamarDNumber5,
		LamarDNumber6,
		LamarDNumber7,
		LamarDNumber8,
		Yacht,
		FindersKeepers,
		Briefcase2,
		ExecutiveSearch,
		Wifi,
		TurretedLimo,
		AssetRecovery,
		YachtLocation,
		Beasted,
		///<summary>The default English text for this value is "Zoned".</summary>
		Loading,
		Random,
		SlowTime,
		///<summary>The default English text for this value is "Flipped".</summary>
		Flip,
		ThermalVision,
		Doped,
		Railgun,
		Seashark,
		Blind,
		Warehouse,
		WarehouseForSale,
		Office,
		OfficeForSale,
		Truck,
		SpecialCargo,
		Trailer,
		VIP,
		Cargobob,
		AreaCutline,
		Jammed,
		Ghost,
		Detonator,
		Bomb,
		///<summary>The sprite image is a shield, but the default English text for this value is "Beast".</summary>
		Shield,
		Stunt,
		Heart,
		StuntPremium,
		Adversary,
		BikerClubhouse,
		CagedIn,
		TurfWar,
		Joust,
		///<summary>The default English text for this value is "Weed Production".</summary>
		Weed,
		///<summary>The default English text for this value is "Weed Production".</summary>
		Cocaine,
		///<summary>The default English text for this value is "Weed Production".</summary>
		IdentityCard,
		///<summary>The default English text for this value is "Weed Production".</summary>
		Meth,
		///<summary>The default English text for this value is "Weed Production".</summary>
		DollarBill,
		///<summary>The default English text for this value is "Package", whose label text hash is used in Biker Business missions in GTA Online.</summary>
		Package2,
		Capture1,
		Capture2,
		Capture3,
		Capture4,
		Capture5,
		Capture6,
		Capture7,
		Capture8,
		Capture9,
		Capture10,
		QuadBike,
		Bus,
		///<summary>The default English text for this value is "Drugs Package".</summary>
		DrugPackage,
		Hop,
		Adversary4,
		Adversary8,
		Adversary10,
		Adversary12,
		Adversary16,
		Laptop,
		///<summary>The default English text for this value is "Deadline".</summary>
		Motorcycle,
		SportsCar,
		VehicleWarehouse,
		///<summary>The default English text for this value is "Registration Papers".</summary>
		Document,
		PoliceStationInverted,
		Junkyard,
		PhantomWedge,
		ArmoredBoxville,
		Ruiner2000,
		RampBuggy,
		Wastelander,
		RocketVoltic,
		TechnicalAqua,
		TargetA,
		TargetB,
		TargetC,
		TargetD,
		TargetE,
		TargetF,
		TargetG,
		TargetH,
		Juggernaut,
		Repair2,
		///<summary>The default English text for this value is "Special Vehicle Race Series".</summary>
		SteeringWheel,
		///<summary>The default English text for this value is "Challenge Series".</summary>
		Cup,
		RocketBoost,
		///<summary>The default English text for this value is "Homing Rocket".</summary>
		Rocket,
		MachineGun,
		Parachute2,
		FiveSeconds,
		TenSeconds,
		FifteenSeconds,
		TwentySeconds,
		ThirtySeconds,
		WeaponSupplies,
		Bunker,
		APC,
		Oppressor,
		HalfTrack,
		DuneFAV,
		WeaponizedTampa,
		///<summary>The default English text for this value is "Anti-Aircraft Trailer".</summary>
		WeaponizedTrailer,
		MobileOperationsCenter,
		AdversaryBunker,
		BunkerVehicleWorkshop,
		WeaponWorkshop,
		Cargo,
		GTAOHangar,
		TransformCheckpoint,
		TransformRace,
		AlphaZ1,
		Bombushka,
		Havok,
		HowardNX25,
		Hunter,
		Ultralight,
		Mogul,
		V65Molotok,
		P45Nokota,
		Pyro,
		Rogue,
		Starling,
		Seabreeze,
		Tula,
		Equipment,
		Treasure,
		OrbitalCannon,
		Avenger,
		Facility,
		HeistDoomsday,
		SAMTurret,
		Firewall,
		Node,
		Stromberg,
		Deluxo,
		Thruster,
		Khanjali,
		RCV,
		Volatol,
		Barrage,
		Akula,
		Chernobog,
		CCTV,
		StarterPackIdentifier,
		TurretStation,
		RotatingMirror,
		StaticMirror,
		Proxy,
		TargetAssault,
		SanAndreasSuperSportCircuit,
		SeaSparrow,
		Caracara,
		NightclubProperty,
		CargoBusinessBattle,
		NightclubTruck,
		Jewel,
		Gold,
		Keypad,
		HackTarget,
		HealthHeart,
		BlastIncrease,
		BlastDecrease,
		BombIncrease,
		BombDecrease,
		Rival,
		Drone,
		CashRegister,
		CCTV2,
		TargetBusinessBattle,
		FestivalBus,
		Terrorbyte,
		Menacer,
		Scramjet,
		PounderCustom,
		MuleCustom,
		SpeedoCustom,
		Blimp2,
		OppressorMkII,
		B11StrikeForce,
		ArenaSeries,
		ArenaPremium,
		ArenaWorkshop,
		RaceArenaWar,
		ArenaTurret,
		RCVehicle,
		RCWorkshop,
		FirePit,
		Flipper,
		SeaMine,
		TurnTable,
		Pit,
		Mines,
		BarrelBomb,
		RisingWall,
		Bollards,
		SideBollard,
		Bruiser,
		Brutus,
		Cerberus,
		Deathbike,
		Dominator,
		Impaler,
		Imperator,
		Issi,
		Sasquatch,
		Scarab,
		Slamvam,
		ZR380,
		ComicStore = 671,
		CopCar = 672,
		KingofTheHill = 674,
		Rucksack = 676,
		ShippingContainer = 677,
		Casino = 679,
		CasinoTable = 680,
		CasinoWheel = 681,
		CasinoChips = 683,
		CasinoHorse = 684,
		Limo = 724,
		OpenWheelCar = 726,
		Rappel = 727,
		ScubaGear = 729,
		SnowTruck = 734,
		Buggy1 = 735,
		Buggy2 = 736,
		Zhaba = 737,
		Arcade = 740,
		RCTank = 742,
		Stairs = 743,
		Camera2 = 744,
		Winky = 745,
		MiniSub = 746,
		KartRetro = 747,
		KartModern = 748,
		MilitaryQuad = 749,
		MilitaryTruck = 750,
		ShipWheel = 751,
		UFO = 752,
		SeaSparrow2 = 753,
		Dinghy2 = 754,
		PatrolBoat = 755,
		Toreador = 756,
		Squadee = 757,
		Alkonost = 758,
		AnnihilatorStealth = 759,
		Kostatka = 760,
		BoltCutter = 761,
		RappelGear = 762,
		KeyCard = 763,
		Password = 764,
		IslandHeist = 765,
		IslandParty = 766,
		RadarTower = 767,
		UnderwaterGrate = 768,
		PowerSwitch = 769,
		CompoundGate = 770,
		RappelPoint = 771,
		SubControls = 773,
		SubPeriscope = 774,
		SubMissiles = 775,
		Painting = 776,
		AutoShop = 779,
		Anchor = 780,
		PrizeBox = 781,
		ChopShopHeist = 784,
		Securoserv = 788,
		MovieCollection = 790,
		Chalkboard = 793,
		Train = 795,
		Slamvan2 = 799,
		Crusader = 800,
		ConstructionOutfit = 801,
		VanKeys = 811,
		SUVService = 812,
		SecurityContract = 813,
		SafeVault = 814,
		Payphone = 817,
		Patriot3 = 818,
		RecordStudio = 819,
		Jubilee = 820,
		Granger2 = 821,
		Dynamite = 822,
		Deity = 823,
		Champion = 824,
		Buffalo4 = 825,
		Agency = 826,
		BikerBar = 827,
		FlamingSkull = 833,
		CayoPerico = 836,
		ClubhouseContract = 837,
		Acid = 839,
		AcidLab = 840,
		MysteryPackage = 842,
		GunVan = 844,
		Tractor = 846,
		JuggaloWarehouse = 847,
		Duffelbag = 850,
		OilTanker = 851,
		Burrito = 853,
		Bicycle = 859,
		Raiju = 861,
		WeaponizedConada = 862,
		Streamer216 = 865,
		SignalJammer = 866,
		SalvageYard = 867,
		SalvageYardHeist = 868,
		SalvageYardPlans = 879,
		WeaponCrate = 880,
		Snowball = 881,
		Tombstone = 885,
		BottomDollarBounty = 886,
		BottomDollarBountyTarget = 887,
		FilmingSchedule = 888,
		Pizza = 889,
		AircraftCarrier = 890,
		//StunGun = 891,
		BottomDollarBailEnforcement = 893,
		ZombieDisease = 895,
		ZombieProximity = 896,
		ZombieFire = 897,
		PossessedAnimal = 898,
		MobilePhone = 899,
	};

	extern const std::map<int, std::string> vNames;
}

namespace BlipColour {
	//BETTER_ENUM(BlipColour, int,
	enum BlipColour : int
	{
		//kagikn
		///<summary>The default RGB value of this color is the same as HUD_COLOUR_PURE_WHITE, whose default RGB value is #FFFFFF.</summary>
		White,
		Red,
		Green,
		Blue,
		Yellow = 66,
		///<summary>The default RGB value of this color is the same as HUD_COLOUR_WHITE, whose default RGB value is #F0F0F0.</summary>
		WhiteNotPure = 4,
		///<summary>This color is always the same as <see cref="BlipColor::Yellow"></see>, the only difference is color index.</summary>
		Yellow2 = 5,
		NetPlayer1,
		NetPlayer2,
		NetPlayer3,
		NetPlayer4,
		NetPlayer5,
		NetPlayer6,
		NetPlayer7,
		NetPlayer8,
		NetPlayer9,
		NetPlayer10,
		NetPlayer11,
		NetPlayer12,
		NetPlayer13,
		NetPlayer14,
		NetPlayer15,
		NetPlayer16,
		NetPlayer17,
		NetPlayer18,
		NetPlayer19,
		NetPlayer20,
		NetPlayer21,
		NetPlayer22,
		NetPlayer23,
		NetPlayer24,
		NetPlayer25,
		NetPlayer26,
		NetPlayer27,
		NetPlayer28,
		NetPlayer29,
		NetPlayer30,
		NetPlayer31,
		NetPlayer32,
		Freemode,
		InactiveMission,
		GreyDark,
		RedLight,
		///<summary>This color is usually #65B4D4 sky blue, which is similar to <see cref="System::Drawing::Color::SkyBlue"></see>.</summary>
		Michael,
		///<summary>This color is usually #ABEDAB light green, which is very similar to <see cref="System::Drawing::Color::LightGreen"></see>.</summary>
		Franklin,
		///<summary>This color is usually #ABEDAB orange, which is very similar to <see cref="System::Drawing::Color::SandyBrown"></see>.</summary>
		Trevor,
		GolfPlayer1,
		GolfPlayer2,
		GolfPlayer3,
		GolfPlayer4,
		///<summary>This color is always the same as <see cref="BlipColor::Red"></see>, the only difference is color index.</summary>
		Red2,
		Purple,
		Orange,
		GreenDark,
		BlueLight,
		BlueDark,
		Grey,
		YellowDark,
		///<summary>This color is always the same as <see cref="BlipColor::Blue"></see>, the only difference is color index.</summary>
		Blue2,
		PurpleDark,
		///<summary>This color is always the same as <see cref="BlipColor::Red"></see>, the only difference is color index.</summary>
		Red3,
		///<summary>This color is always the same as <see cref="BlipColor::Yellow"></see>, the only difference is color index.</summary>
		Yellow3,
		Pink,
		GreyLight,
		Gang,
		Gang2,
		Gang3,
		///<summary>This color is always the same as <see cref="BlipColor::Blue"></see>, the only difference is color index.</summary>
		Blue3 = 67,
		///<summary>This color is always the same as <see cref="BlipColor::Blue"></see>, the only difference is color index.</summary>
		Blue4,
		///<summary>This color is always the same as <see cref="BlipColor::Green"></see>, the only difference is color index.</summary>
		Green2,
		///<summary>This color is always the same as <see cref="BlipColor::Yellow"></see>, the only difference is color index.</summary>
		Yellow4,
		///<summary>This color is always the same as <see cref="BlipColor::Yellow"></see>, the only difference is color index.</summary>
		Yellow5,
		///<summary>This color is always the same as <see cref="BlipColor::White"></see>, the only difference is color index.</summary>
		White2,
		///<summary>This color is always the same as <see cref="BlipColor::Yellow"></see>, the only difference is color index.</summary>
		Yellow6,
		///<summary>This color is always the same as <see cref="BlipColor::Blue"></see>, the only difference is color index.</summary>
		Blue5,
		///<summary>This color is always the same as <see cref="BlipColor::Red"></see>, the only difference is color index.</summary>
		Red4,
		RedDark,
		///<summary>This color is always the same as <see cref="BlipColor::Blue"></see>, the only difference is color index.</summary>
		Blue6,
		///<summary>This color is always the same as <see cref="BlipColor::BlueDark"></see>, the only difference is color index.</summary>
		BlueDark2,
		///<summary>This color is always the same as <see cref="BlipColor::RedDark"></see>, the only difference is color index.</summary>
		RedDark2,
		MenuYellow,
		SimpleBlipDefault,
		Waypoint,
		///<summary>This color is always the same as <see cref="BlipColor::Blue"></see>, the only difference is color index.</summary>
		Blue7
	};
	
	extern const std::map<int, std::string> vNames;
}

class GTAblip final
{
public:
	friend bool operator == (const GTAblip& left, const GTAblip& right);
	friend bool operator != (const GTAblip& left, const GTAblip& right);
	GTAblip& operator = (const GTAblip& right);

	GTAblip();
	GTAblip(int handle);

	int& Handle();

	uint8_t Alpha() const;
	void SetAlpha(uint8_t value);

	int Colour() const;
	void SetColour(int value);

	bool IsFlashing() const;
	void SetFlashing(bool value);

	void SetFriendly(bool value);

	bool IsOnMinimap() const;

	bool IsShortRange() const;
	void SetShortRange(bool value);

	Vector3 Position_get() const;
	void Position_set(const Vector3& value);

	void Rotation_set(float value);

	void SetScale(float value);

	void ShowRoute(bool value);

	int Icon() const;
	void SetIcon(int value);

	std::string IconName() const;

	void SetBlipName(const std::string& value);

	int Type() const;

	void HideNumber();
	void ShowNumber(int number);

	bool Exists() const;
	void Remove();

private:
	int mHandle;
};





