#include "Game.h"
#include <string>
#include "Utilities.h"
#include <stdlib.h>
#include <time.h>

Game::Game() : GBuffer(5), WorkBuffer1(1), WorkBuffer2(1), ShadowMap(0), LUTBuffer(1), DeferredComposite(1), EdgeMap(1), ScreenBuffer(1), DofPass1(1), DofPass2(1) {}
Game::~Game() { delete updateTimer; }


void Game::loadAssets()
{
	//Load Shaders
	Shader.Load("./Assets/Shaders/Main.vert", "./Assets/Shaders/PassThrough.frag");
	UIShader.Load("./Assets/Shaders/Main.vert", "./Assets/Shaders/UI.frag");
	NoLightShader.Load("./Assets/Shaders/Main.vert", "./Assets/Shaders/NoLight.frag");
	LUTShader.Load("./Assets/Shaders/PassThrough.vert", "./Assets/Shaders/LUT.frag");
	BillBoard.Load("./Assets/Shaders/Particles/BillBoard.vert", "./Assets/Shaders/Particles/BillBoard.frag", "./Assets/Shaders/Particles/BillBoard.geom");

	BloomHighPass.Load("./Assets/Shaders/PassThrough.vert", "./Assets/Shaders/Bloom/BloomHighPass.frag");
	BlurHorizontal.Load("./Assets/Shaders/PassThrough.vert", "./Assets/Shaders/Bloom/BlurHorizontal.frag");
	BlurVertical.Load("./Assets/Shaders/PassThrough.vert", "./Assets/Shaders/Bloom/BlurVertical.frag");
	BloomComposite.Load("./Assets/Shaders/PassThrough.vert", "./Assets/Shaders/Bloom/BloomComposite.frag");
	DeferredLighting.Load("./Assets/Shaders/PassThrough.vert", "./Assets/Shaders/DeferredLighting.frag");
	SobelPass.Load("./Assets/Shaders/PassThrough.vert", "./Assets/Shaders/Toon/Sobel.frag");
	Screen.Load("./Assets/Shaders/PassThrough.vert", "./Assets/Shaders/Screen.frag");
	DoFHorizontal.Load("./Assets/Shaders/PassThrough.vert", "./Assets/Shaders/dofHorizontal.frag");
	DoFVertical.Load("./Assets/Shaders/PassThrough.vert", "./Assets/Shaders/dofVertical.frag");

	//Load Objects
	SmallObjects.LoadFromFile("./Assets/Models/Scene_SmallObjects.obj");
	BigObjects.LoadFromFile("./Assets/Models/Scene_BigObjects.obj");
	ExteriorObj.LoadFromFile("./Assets/Models/Exterior.obj");
	Grass.LoadFromFile("./Assets/Models/Ground.obj");
	InteriorObj.LoadFromFile("./Assets/Models/Interior.obj");

	//Load Fireball
	Fireball.LoadFromFile("./Assets/Models/Sphere.obj");
	Fireball.setCulling(false);

	//Load FirePillar
	FirePillar.LoadFromFile("./Assets/Models/Pillar.obj");
	FirePillar.setCulling(false);

	//Load FirePillar
	Portal.LoadFromFile("./Assets/Models/Portal.obj");

	//Load Skybox
	Skybox.LoadFromFile("./Assets/Models/XLSkybox.obj");

	//Load Paladin UI/HUD Icon
	UIPaladin.LoadFromFile("./Assets/Models/NoPaladinHealth.obj");
	UIPaladin.LoadFromFile("./Assets/Models/FullPaladinHealth.obj");
	//Load Demon UI/HUD Icon
	UIDemon.LoadFromFile("./Assets/Models/NoDemonHealth.obj");
	UIDemon.LoadFromFile("./Assets/Models/FullDemonHealth.obj");

	//Load Animations
	Demon.LoadFromFile("./Assets/Animations/DemonIdle_00.obj");		//0
	Demon.LoadFromFile("./Assets/Animations/DemonIdle_01.obj");		//1
	Demon.LoadFromFile("./Assets/Animations/DemonIdle_02.obj");		//2
	Demon.LoadFromFile("./Assets/Animations/DemonIdle_03.obj");		//3

	Demon.LoadFromFile("./Assets/Animations/DemonStab_00.obj");		//4
	Demon.LoadFromFile("./Assets/Animations/DemonStab_01.obj");		//5
	Demon.LoadFromFile("./Assets/Animations/DemonStab_02.obj");		//6
	Demon.LoadFromFile("./Assets/Animations/DemonStab_03.obj");		//7
	Demon.LoadFromFile("./Assets/Animations/DemonStab_04.obj");		//8
	Demon.LoadFromFile("./Assets/Animations/DemonStab_05.obj");		//9
	Demon.LoadFromFile("./Assets/Animations/DemonStab_06.obj");		//10
	Demon.LoadFromFile("./Assets/Animations/DemonStab_07.obj");		//11
	Demon.LoadFromFile("./Assets/Animations/DemonStab_08.obj");		//12
	Demon.LoadFromFile("./Assets/Animations/DemonStab_09.obj");		//13
	Demon.LoadFromFile("./Assets/Animations/DemonStab_10.obj");		//14

	Demon.LoadFromFile("./Assets/Animations/DemonStomp_00.obj");	//15
	Demon.LoadFromFile("./Assets/Animations/DemonStomp_01.obj");	//16
	Demon.LoadFromFile("./Assets/Animations/DemonStomp_02.obj");	//17
	Demon.LoadFromFile("./Assets/Animations/DemonStomp_03.obj");	//18
	Demon.LoadFromFile("./Assets/Animations/DemonStomp_04.obj");	//19

	Demon.LoadFromFile("./Assets/Animations/DemonFireball_00.obj");	//20
	Demon.LoadFromFile("./Assets/Animations/DemonFireball_01.obj");	//21
	Demon.LoadFromFile("./Assets/Animations/DemonFireball_02.obj");	//22
	Demon.LoadFromFile("./Assets/Animations/DemonFireball_03.obj");	//23

	Demon.LoadFromFile("./Assets/Animations/DemonPillar_00.obj");	//24
	Demon.LoadFromFile("./Assets/Animations/DemonPillar_01.obj");	//25
	Demon.LoadFromFile("./Assets/Animations/DemonPillar_02.obj");	//26
	Demon.LoadFromFile("./Assets/Animations/DemonPillar_03.obj");	//27
	Demon.LoadFromFile("./Assets/Animations/DemonPillar_04.obj");	//28
	Demon.LoadFromFile("./Assets/Animations/DemonPillar_05.obj");	//29

	Demon.LoadFromFile("./Assets/Animations/DemonDeath_00.obj");	//30
	Demon.LoadFromFile("./Assets/Animations/DemonDeath_01.obj");	//31
	Demon.LoadFromFile("./Assets/Animations/DemonDeath_02.obj");	//32
	Demon.LoadFromFile("./Assets/Animations/DemonDeath_03.obj");	//33

	Flame.LoadFromFile("./Assets/Animations/Fire_00.obj");	//0
	Flame.LoadFromFile("./Assets/Animations/Fire_01.obj");	//1
	Flame.LoadFromFile("./Assets/Animations/Fire_02.obj");	//2
	Flame.LoadFromFile("./Assets/Animations/Fire_03.obj");	//3
	Flame.LoadFromFile("./Assets/Animations/Fire_04.obj");	//4
	Flame.LoadFromFile("./Assets/Animations/Fire_05.obj");	//5
	Flame2 = Flame;
	Flame3 = Flame;
	Flame4 = Flame;
	Flame5 = Flame;

	Paladin.LoadFromFile("./Assets/Animations/PaladinIdle_00.obj");	//0
	Paladin.LoadFromFile("./Assets/Animations/PaladinIdle_01.obj");	//1
	Paladin.LoadFromFile("./Assets/Animations/PaladinIdle_02.obj");	//2
	Paladin.LoadFromFile("./Assets/Animations/PaladinIdle_03.obj");	//3

	Paladin.LoadFromFile("./Assets/Animations/PaladinRun_00.obj");	//4
	Paladin.LoadFromFile("./Assets/Animations/PaladinRun_01.obj");	//5
	Paladin.LoadFromFile("./Assets/Animations/PaladinRun_02.obj");	//6
	Paladin.LoadFromFile("./Assets/Animations/PaladinRun_03.obj");	//7

	Paladin.LoadFromFile("./Assets/Animations/PaladinJump.obj");	//8
	Paladin.LoadFromFile("./Assets/Animations/PaladinMid.obj");		//9
	Paladin.LoadFromFile("./Assets/Animations/PaladinFall.obj");	//10
	Paladin.LoadFromFile("./Assets/Animations/PaladinDash.obj");	//11

	Paladin.LoadFromFile("./Assets/Animations/PaladinAttack_00.obj");	//12
	Paladin.LoadFromFile("./Assets/Animations/PaladinAttack_01.obj");	//13
	Paladin.LoadFromFile("./Assets/Animations/PaladinAttack_02.obj");	//14
	Paladin.LoadFromFile("./Assets/Animations/PaladinAttack_03.obj");	//15
	Paladin.LoadFromFile("./Assets/Animations/PaladinAttack_04.obj");	//16

	Paladin.LoadFromFile("./Assets/Animations/PaladinDeath_00.obj");	//17
	Paladin.LoadFromFile("./Assets/Animations/PaladinDeath_01.obj");	//18
	Paladin.LoadFromFile("./Assets/Animations/PaladinDeath_02.obj");	//19
	Paladin.LoadFromFile("./Assets/Animations/PaladinDeath_03.obj");	//20
	Paladin.LoadFromFile("./Assets/Animations/PaladinDeath_04.obj");	//21
	Paladin.LoadFromFile("./Assets/Animations/PaladinDeath_05.obj");	//22
	Paladin.setCulling(false);

	//Load Textures
	RedTex.Load("./Assets/Textures/Red.png");
	WhiteTex.Load("./Assets/Textures/White.png");
	BlackTex.Load("./Assets/Textures/Black.png");
	PaladinTex.Load("./Assets/Textures/PaladinTexture.png");
	DemonTex.Load("./Assets/Textures/Demon.png");
	SmallObjTex.Load("./Assets/Textures/TextureSmall.png");
	BigObjTex.Load("./Assets/Textures/TextureBig.png");
	FireTex.Load("./Assets/Textures/Fire.png");
	ExteriorObjTex.Load("./Assets/Textures/Exterior.png");
	GrassTex.Load("./Assets/Textures/Ground.png");
	InteriorObjTex.Load("./Assets/Textures/Interior.png");
	PaladinEmissive.Load("./Assets/Textures/PaladinTextureEmit.png");
	DemonEmissive.Load("./Assets/Textures/DemonEmit.png");
	PillarTex.Load("./Assets/Textures/PillarTex.png");
	PillarTex.SetNearestFilter();
	FireballTex.Load("./Assets/Textures/FireballTex.png");
	FireballTex.SetNearestFilter();
	PortalTex.Load("./Assets/Textures/Portal.png");
	PortalTex.SetNearestFilter();

	//Load Skybox Texture
	SkyboxTex.Load("./Assets/Textures/XLSkybox.png");
	//Load Screen Textures
	Controls.Load("./Assets/Textures/DS_Controls.png");
	GameOver0.Load("./Assets/Textures/DS_GameOver0.png");
	GameOver1.Load("./Assets/Textures/DS_GameOver1.png");
	GameOver2.Load("./Assets/Textures/DS_GameOver2.png");
	MainMenu0.Load("./Assets/Textures/DS_MainMenu0.png");
	MainMenu1.Load("./Assets/Textures/DS_MainMenu1.png");
	MainMenu2.Load("./Assets/Textures/DS_MainMenu2.png");
	Paused0.Load("./Assets/Textures/DS_Paused0.png");
	Paused1.Load("./Assets/Textures/DS_Paused1.png");
	Paused2.Load("./Assets/Textures/DS_Paused2.png");
	Victory0.Load("./Assets/Textures/DS_Victory0.png");
	Victory1.Load("./Assets/Textures/DS_Victory1.png");
	Victory2.Load("./Assets/Textures/DS_Victory2.png");

	//Load UI/HUD Paladin Textures
	UITex.Load("./Assets/Textures/uiAtlas.png");
	UITex.SetNearestFilter();
	//LUT Textures
	LUTTex.Load3D("./Assets/LUTs/normal.CUBE");
	LUTCool.Load3D("./Assets/LUTs/cool.CUBE");
	LUTWarm.Load3D("./Assets/LUTs/warm.CUBE");
	//Toon shader Texture
	ToonTex.Load("./Assets/Textures/ToonTex.png");
	ToonTex.SetNearestFilter();

	//Particles
	StepEffect.Init("./Assets/Textures/step.png", 50, 1);
	FireEffect.Init("./Assets/Textures/fireball.png", 200, 25);
	FireEffect2.Init("./Assets/Textures/FireParticle.png", 15, 1);
	BloodEffect.Init("./Assets/Textures/Blood.png", 5, 1);
	StepEffect2.Init("./Assets/Textures/step.png", 50, 1);


	//Load Sounds
	/// Music
	BGM.Load("./Assets/Sounds/Music/DS_Demonblight_v2.ogg");
	BGM8bit.Load("./Assets/Sounds/Music/DS_Demonblight_8-bit_v2.ogg");
	MenuMusic.Load("./Assets/Sounds/Music/DS_Delphic-Hymn.ogg");
	BrownNoise.Load("./Assets/Sounds/Music/DS_Brown-Noise.ogg");
	MenuNoise.Load("./Assets/Sounds/Paladin/pld_sw1.ogg");
	Thunder.Load("./Assets/Sounds/Music/thunder.ogg");
	/// Fire
	AmbientFire.Load("./Assets/Sounds/Fire/fire_tone.ogg");
	Fire1.Load("./Assets/Sounds/Fire/fire1.ogg");
	Fire2.Load("./Assets/Sounds/Fire/fire2.ogg");
	Fire3.Load("./Assets/Sounds/Fire/fire3.ogg");
	Fire4.Load("./Assets/Sounds/Fire/fire4.ogg");
	/// Paladin
	PaladinSwing1.Load("./Assets/Sounds/Paladin/pld_sw1.ogg");
	PaladinSwing2.Load("./Assets/Sounds/Paladin/pld_sw2.ogg");
	PaladinDash1.Load("./Assets/Sounds/Paladin/pld_dash.ogg");
	PaladinVoice.Load("./Assets/Sounds/Paladin/pld_dialogue.ogg");
	PaladinJump.Load("./Assets/Sounds/Paladin/jump.ogg");
	PaladinJump1.Load("./Assets/Sounds/Paladin/pld_jump1.ogg");
	PaladinJump2.Load("./Assets/Sounds/Paladin/pld_jump2.ogg");
	PaladinJumpDouble.Load("./Assets/Sounds/Paladin/jumpDouble.ogg");
	PaladinAttack1.Load("./Assets/Sounds/Paladin/pld_attack1.ogg");
	PaladinAttack2.Load("./Assets/Sounds/Paladin/pld_attack2.ogg");
	PaladinDamage1.Load("./Assets/Sounds/Paladin/pld_dmg1.ogg");
	PaladinDamage2.Load("./Assets/Sounds/Paladin/pld_dmg2.ogg");
	PaladinDeath1.Load("./Assets/Sounds/Paladin/pld_death1.ogg");
	PaladinDeath2.Load("./Assets/Sounds/Paladin/pld_death2.ogg");
	PaladinSteps.Load("./Assets/Sounds/Paladin/footstep.ogg");
	PaladinLanding.Load("./Assets/Sounds/Paladin/landing.ogg");
	PaladinDeflect.Load("./Assets/Sounds/Paladin/deflect.ogg");
	/// Demon
	DemonSwing1.Load("./Assets/Sounds/Demon/dmn_sw1.ogg");
	DemonSwing2.Load("./Assets/Sounds/Demon/dmn_sw2.ogg");
	DemonSwing3.Load("./Assets/Sounds/Demon/dmn_sw3.ogg");
	DemonAttack1.Load("./Assets/Sounds/Demon/dmn_attack1.ogg");
	DemonAttack2.Load("./Assets/Sounds/Demon/dmn_attack2.ogg");
	DemonAttack3.Load("./Assets/Sounds/Demon/dmn_attack3.ogg");
	DemonBreath.Load("./Assets/Sounds/Demon/dmn_breath.ogg");
	DemonBurn.Load("./Assets/Sounds/Demon/dmn_burn.ogg");
	DemonCrit1.Load("./Assets/Sounds/Demon/dmn_crit1.ogg");
	DemonCrit2.Load("./Assets/Sounds/Demon/dmn_crit2.ogg");
	DemonDamage1.Load("./Assets/Sounds/Demon/dmn_damage1.ogg");
	DemonDamage2.Load("./Assets/Sounds/Demon/dmn_damage2.ogg");
	DemonDamage3.Load("./Assets/Sounds/Demon/dmn_damage3.ogg");
	DemonLaugh.Load("./Assets/Sounds/Demon/dmn_laugh.ogg");
	DemonRoar1.Load("./Assets/Sounds/Demon/dmn_roar1.ogg");
	DemonRoar2.Load("./Assets/Sounds/Demon/dmn_roar2.ogg");
	DemonRoar3.Load("./Assets/Sounds/Demon/dmn_roar3.ogg");
	DemonSnarl1.Load("./Assets/Sounds/Demon/dmn_snarl1.ogg");
	DemonSnarl2.Load("./Assets/Sounds/Demon/dmn_snarl2.ogg");
	DemonSnarl3.Load("./Assets/Sounds/Demon/dmn_snarl3.ogg");
	Dialogue.Load("./Assets/Sounds/Music/pld_dialogue.ogg");

	UIShader.addMesh(&UIPaladin);
	UIShader.addMesh(&UIDemon);

	NoLightShader.addMesh(&Skybox);
	NoLightShader.addMesh(&Flame);
	NoLightShader.addMesh(&Flame2);
	NoLightShader.addMesh(&Flame3);
	NoLightShader.addMesh(&Flame4);
	NoLightShader.addMesh(&Flame5);
	NoLightShader.addMesh(&FirePillar);
	NoLightShader.addMesh(&Fireball);
	NoLightShader.addMesh(&Portal);

	Shader.addMesh(&InteriorObj);
	Shader.addMesh(&Grass);
	Shader.addMesh(&ExteriorObj);
	Shader.addMesh(&SmallObjects);
	Shader.addMesh(&BigObjects);
	Shader.addMesh(&Demon);
	Shader.addMesh(&Paladin);

	BillBoard.addParticle(&StepEffect);
	BillBoard.addParticle(&FireEffect);
	BillBoard.addParticle(&FireEffect2);
	BillBoard.addParticle(&BloodEffect);
	BillBoard.addParticle(&StepEffect2);
}

void Game::InitializeObjects()
{
	if (bgm8bit)
	{
		BGM8bit.Stop(channel_Music);
		channel_Music = BGM8bit.Play(true);
	}
	else if (!bgm8bit)
	{
		BGM.Stop(channel_Music);
		channel_Music = BGM.Play(true);
	}

	SmallObjects.SetTextures(&SmallObjTex, &BlackTex);
	BigObjects.SetTextures(&BigObjTex, &BlackTex);
	ExteriorObj.SetTextures(&ExteriorObjTex, &BlackTex);
	Grass.SetTextures(&GrassTex, &BlackTex);
	InteriorObj.SetTextures(&InteriorObjTex, &BlackTex);
	Fireball.SetTextures(&FireballTex, &BlackTex);
	FirePillar.SetTextures(&PillarTex, &BlackTex);
	Skybox.SetTextures(&SkyboxTex, &BlackTex);
	UIPaladin.SetTextures(&UITex, &BlackTex);
	UIDemon.SetTextures(&UITex, &BlackTex);
	Demon.SetTextures(&DemonTex, &DemonEmissive);
	Flame.SetTextures(&FireTex, &BlackTex);
	Flame2.SetTextures(&FireTex, &BlackTex);
	Flame3.SetTextures(&FireTex, &BlackTex);
	Flame4.SetTextures(&FireTex, &BlackTex);
	Flame5.SetTextures(&FireTex, &BlackTex);
	Paladin.SetTextures(&PaladinTex, &PaladinEmissive);
	Portal.SetTextures(&PortalTex, &PortalTex);

	SmallObjects.SetAnimations(0, 0);
	BigObjects.SetAnimations(0, 0);
	ExteriorObj.SetAnimations(0, 0);
	Grass.SetAnimations(0, 0);
	InteriorObj.SetAnimations(0, 0);
	Fireball.SetAnimations(0, 0);
	FirePillar.SetAnimations(0, 0);
	Skybox.SetAnimations(0, 0);
	UIPaladin.SetAnimations(0, 1);
	UIDemon.SetAnimations(0, 1);
	Demon.SetAnimations(0, 1);
	Flame.SetAnimations(0, 1);
	Flame2.SetAnimations(0, 1);
	Flame3.SetAnimations(0, 1);
	Flame4.SetAnimations(0, 1);
	Flame5.SetAnimations(0, 1);
	Paladin.SetAnimations(0, 1);
	Portal.SetAnimations(0, 0);

	Demon.animIndex = 1;
	Paladin.animIndex = 1;
	Flame.animIndex = 1;
	Flame2.animIndex = 1;
	Flame3.animIndex = 1;
	Flame4.animIndex = 1;
	Flame5.animIndex = 1;

	Demon.interp = 0.0f;
	Flame.interp = 0.0f;
	Flame2.interp = 0.0f;
	Flame3.interp = 0.0f;
	Flame4.interp = 0.0f;
	Flame5.interp = 0.0f;
	Paladin.interp = 0.0f;

	jumpCount = 0;			//keeps track of jump count
	PaladinHealth = 50;	//health
	PaladinMoveX = 0.0f;	//movement on horiz axis
	PaladinMoveY = 0.0f;	//movement on verti axis

	dashTimer = 1.0f;			//dash timer
	attackTimer = 0.0f;		//attack timer, inits with no cooldown
	attackCooldown = 0.32f;	//attack cooldown value
	deathTimer = 0.0f;
	ShakeX = 0.0f;
	ShakeY = 0.0f;
	ShakeMagnitude = 0.0f;
	PillarHurtTimer = 0.5f;

	faceLeft = false, faceRight = true;	//paladin inits facing right
	prevState = false;						//prevents multiple keydown inputs in main loop
	PaladinHurt = false;
	PaladinAttack = false;
	PaladinDash = false;
	ToonShading = false;
	playDialogue = true;

	Knockback = true;

	DistPaladinDemon = 0;
	DistPaladinFireballX = 0;
	DistPaladinFireballY = 0;
	DistPaladinFirePillar = 0;
	PaladinHurtTimer = 0.0f;

	DemonHealth = 150;
	DemonAttack = 0;
	StabTimer = 0;
	StompTimer = 0;
	FireballTimer = 0;
	DemonTimer = 1.0f;
	FirePillarTimer = 0.0f;
	FirePillarCoolDown = 5.0f;
	DemonHurt = false;
	cutsceneTimer = 0.0f;

	BloodTimer = 0.0f;
	fireballrandom = 2;
	FireballDir = vec3(0.0f, 0.0f, 0.0f);

	lightningTimer = 0.0f;
	lightningTime = static_cast<float>(rand() % 10 + 7);
	Reflect = false;
	winAnim = false;
	loseAnim = false;

	key_A = false;
	key_S = false;
	key_D = false;
	key_W = false;
	key_O = false;
	key_P = false;
	key_ESC = false;
	key_SPACE = false;
	currentLUT = 0;

	//Camera transform position
	camera.setPosition(camPosXYZ);	//set camera position
	camera.setRotationX(camPitch);		//set camera pitch
	camera.setRotationY(camYaw);		//set camera yaw
	camera.setRotationZ(camRoll);		//set camera roll
	camera.perspective(60.0f, (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.01f, 1000.0f);


	//Paladin
	Paladin.setRotationY(80.0f);
	Paladin.setPosition(vec3(-7.0f, 0.0f, 0.0f));
	camera.setPosition(vec3(Paladin.getPositionX() + camera.getPositionX(), camera.getPositionY(), camera.getPositionZ()));

	//Demon
	Demon.setRotationY(-80.0f);
	Demon.setPosition(vec3(9.0f, 0.0f, 0.0f));
	DemonPos = Demon.getPositionX();

	//Small & Big Objects
	BigObjects.setScale(1.5f);
	SmallObjects.setScale(1.5f);

	//Interior and exterior
	ExteriorObj.setScale(2.5f);
	InteriorObj.setScale(1.5f);

	//Grass
	Grass.setScale(vec3(2.0f, 1.0f, 1.0f));
	Grass.setPosition(vec3(0.0f, -0.1f, -37.0f));

	//Fire
	Flame.setScale(0.1f);
	Flame.setPosition(vec3(4.56f, 0.9f, 2.55f));
	Flame2.setScale(0.1f);
	Flame2.setPosition(vec3(5.18f, 0.9f, 3.8f));
	Flame3.setScale(0.1f);
	Flame3.setPosition(vec3(6.38f, 0.9f, 3.19f));
	Flame4.setScale(0.1f);
	Flame4.setPosition(vec3(7.3f, 0.9f, 3.48f));
	Flame5.setScale(0.25f);
	Flame5.setPosition(vec3(-6.95f, 5.85f, -7.8f));

	//Projectile init
	Fireball.setPosition(vec3(-100.0f, -100.0f, 0.0f));

	//Fire Pillar Init
	FirePillar.setPosition(vec3(-100.0f, -100.0, 0.0f));

	//Skybox init
	Skybox.setScale(3.0f);
	Skybox.setPosition(vec3(15.0f, -5.0f, -100.0f));
	Skybox.setRotationY(270.0f);

	//UI/HUD init
	UIPaladin.setScale(1.7f);
	UIPaladin.setPosition(vec3(-20.0f, 21.5f, -7.0f) + camera.getPosition());

	UIDemon.setScale(1.7f);
	UIDemon.setPosition(vec3(20.0f, 21.5f, -7.0f) + camera.getPosition());


	Portal.setPosition(vec3(-100.0f, 0.01f, 0.0f));
	Portal.setScale(vec3(0.0f, 1.0f, 0.0f));

	Paladin.update();
	Demon.update();
	SmallObjects.update();
	BigObjects.update();
	Flame.update();
	Flame2.update();
	Flame3.update();
	Flame4.update();
	Flame5.update();
	ExteriorObj.update();
	Grass.update();
	InteriorObj.update();
	Skybox.update();
	Fireball.update();
	FirePillar.update();
	Portal.update();

	UIPaladin.update();
	UIDemon.update();

	FireQ.destroyQueue();
	FireQ.addQueue(1);
	FireQ.addQueue(2);
	FireQ.addQueue(3);
	FireQ.addQueue(4);
	FireQ.addQueue(5);
	FireQ.addQueue(0);

	StepEffect.LerpAlpha = vec2(1.0f, 1.0f);
	StepEffect.LerpSize = vec2(1.0f, 0.0f);
	StepEffect.RangeLifetime = vec2(0.0f, 0.7f);
	StepEffect.RangeVelocity = vec2(0.2f, 0.5f); 
	StepEffect.RangeX = vec2(-100.0f, -100.0f);
	StepEffect.RangeY = vec2(0.1f, 0.3f);
	StepEffect.RangeZ = vec2(-0.5f, 0.5f);

	StepEffect2.LerpAlpha = vec2(1.0f, 1.0f);
	StepEffect2.LerpSize = vec2(1.0f, 0.0f);
	StepEffect2.RangeLifetime = vec2(0.0f, 0.5f);
	StepEffect2.RangeVelocity = vec2(0.2f, 0.5f);
	StepEffect2.RangeX = vec2(-100.0f, -100.0f);
	StepEffect2.RangeY = vec2(0.1f, 0.3f);
	StepEffect2.RangeZ = vec2(-0.5f, 0.5f);

	FireEffect.LerpAlpha = vec2(1.0f, 1.0f);
	FireEffect.LerpSize = vec2(1.0f, 0.0f);
	FireEffect.RangeLifetime = vec2(0.0f, 1.0f);
	FireEffect.RangeVelocity = vec2(0.1f, 0.5f);
	FireEffect.RangeX = vec2(-100.0f, -100.0f);
	FireEffect.RangeY = vec2(-100.0f, -100.0f);
	FireEffect.RangeZ = vec2(Fireball.getPositionZ(), Fireball.getPositionZ());

	FireEffect2.LerpAlpha = vec2(1.0f, 1.0f);
	FireEffect2.LerpSize = vec2(2.5f, 0.0f);
	FireEffect2.RangeLifetime = vec2(0.0f, 1.5f);
	FireEffect2.RangeVelocity = vec2(0.1f, 0.5f);
	FireEffect2.RangeX = vec2(-100.0f, -100.0f);
	FireEffect2.RangeY = vec2(-100.0f, -100.0f);
	FireEffect2.RangeZ = vec2(-0.5f, 0.5f);

	BloodEffect.LerpAlpha = vec2(1.0f, 1.0f);
	BloodEffect.LerpSize = vec2(0.0, 0.5f);
	BloodEffect.RangeLifetime = vec2(0.0f, 0.5f);
	BloodEffect.RangeVelocity = vec2(1.0f, 2.0f);
	BloodEffect.RangeX = vec2(DemonPos, DemonPos);
	BloodEffect.RangeY = vec2(-100.0f, -100.0f);
	BloodEffect.RangeZ = vec2(2.0f, 2.0f);

}

void Game::initializeGame()
{
	updateTimer = new Timer();

	InitFullScreenQuad();

	glEnable(GL_DEPTH_TEST);							//Enable Z-Buffer
	glEnable(GL_BLEND);									//Blending Enabled
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	//blending stuff with alpha channel
	glEnable(GL_CULL_FACE);								//Enable Culling
	glEnable(GL_MULTISAMPLE);							//Enable MSAA (Multisample Anti-Aliasing)
	glCullFace(GL_BACK);

	loadAssets();

	GBuffer.InitDepthTexture(WINDOW_WIDTH, WINDOW_HEIGHT);
	GBuffer.InitColorTexture(0, WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGBA8, GL_NEAREST, GL_CLAMP_TO_EDGE);
	GBuffer.InitColorTexture(1, WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGB16, GL_NEAREST, GL_CLAMP_TO_EDGE);
	GBuffer.InitColorTexture(2, WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGB32F, GL_NEAREST, GL_CLAMP_TO_EDGE);
	GBuffer.InitColorTexture(3, WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGBA8, GL_NEAREST, GL_CLAMP_TO_EDGE);
	GBuffer.InitColorTexture(4, WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGBA8, GL_NEAREST, GL_CLAMP_TO_EDGE); //Emissive
	GBuffer.CheckFBO();

	DeferredComposite.InitColorTexture(0, WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGBA8, GL_NEAREST, GL_CLAMP_TO_EDGE);
	DeferredComposite.CheckFBO();

	ShadowMap.InitDepthTexture(SHADOW_RESOLUTION, SHADOW_RESOLUTION);
	ShadowMap.CheckFBO();

	WorkBuffer1.InitColorTexture(0, static_cast<int>(WINDOW_WIDTH / BLOOM_DOWNSCALE), static_cast<int>(WINDOW_HEIGHT / BLOOM_DOWNSCALE), GL_RGB8, GL_LINEAR, GL_CLAMP_TO_EDGE);
	WorkBuffer1.CheckFBO();

	WorkBuffer2.InitColorTexture(0, static_cast<int>(WINDOW_WIDTH / BLOOM_DOWNSCALE), static_cast<int>(WINDOW_HEIGHT / BLOOM_DOWNSCALE), GL_RGB8, GL_LINEAR, GL_CLAMP_TO_EDGE);
	WorkBuffer2.CheckFBO();

	LUTBuffer.InitColorTexture(0, WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGBA8, GL_NEAREST, GL_CLAMP_TO_EDGE);
	LUTBuffer.CheckFBO();

	ScreenBuffer.InitColorTexture(0, WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGBA8, GL_NEAREST, GL_CLAMP_TO_EDGE);
	ScreenBuffer.CheckFBO();

	DofPass1.InitColorTexture(0, WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGBA8, GL_NEAREST, GL_CLAMP_TO_EDGE);
	DofPass1.CheckFBO();

	DofPass2.InitColorTexture(0, WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGBA8, GL_NEAREST, GL_CLAMP_TO_EDGE);
	DofPass2.CheckFBO();

	EdgeMap.InitColorTexture(0, WINDOW_WIDTH, WINDOW_HEIGHT, GL_R8, GL_NEAREST, GL_CLAMP_TO_EDGE);
	EdgeMap.CheckFBO();

	//Shadows init
	ShadowTransform.Translate(vec3(0.0f, 0.0f, -100.0f));
	ShadowTransform.RotateX(-40.0f);
	ShadowTransform.RotateY(165.0f);
	ShadowProjection = mat4::OrthographicProjection(-35.0f, 35.0f, 35.0f, -35.0f, -200.0f, 200.0f);

	//Sounds init
	///load bgm music
	channel_Music = BGM.Play(true);
	Sound::SetPosition(channel_Music, FMOD_VECTOR{ 0.0f, 5.0f, 0.0f });
	Sound::SetVolume(channel_Music, musicVolume);
	///load menu music
	channel_MenuMusic = MenuMusic.Play(true);
	Sound::SetPosition(channel_MenuMusic, FMOD_VECTOR{ 0.0f, 5.0f, 0.0f });
	Sound::SetVolume(channel_MenuMusic, musicVolume);
	///load ambient fire sound
	channel_Ambient = AmbientFire.Play(true);
	Sound::SetPosition(channel_Ambient, FMOD_VECTOR{ 0.0f, 0.0f, 2.0f });
	///load ambient brown noise
	channel_Ambient2 = BrownNoise.Play(true);
	Sound::SetPosition(channel_Ambient2, FMOD_VECTOR{ 0.0f, 5.0f, 0.0f });
	///load the demon breathing
	channel_DemonBreath = DemonBreath.Play(true);

	Sound::PlayState(channel_Music, true);
	Sound::PlayState(channel_MenuMusic, true);
	Sound::PlayState(channel_Ambient, true);
	Sound::PlayState(channel_Ambient2, true);
	Sound::PlayState(channel_DemonBreath, true);

	InitializeObjects();
}




//Main update loop
//Note: As this function is called every frame, Keep this function as clean as possible!
void Game::update()
{
	//Update clock (to get deltaTime since the last update)
	updateTimer->tick();
	float deltaTime = updateTimer->getElapsedTimeSeconds();
	TotalGameTime += deltaTime;
	optionsTimer += deltaTime;

	if (loseAnim) //If death animation didnt play yet
	{
		Fireball.setPosition(vec3(-100.0f, -100.0f, 0.0f));
		FirePillar.setPosition(vec3(-100.0f, -100.0f, 0.0f));

		FireEffect2.RangeX = vec2(-100.0f, -100.0f);
		FireEffect2.RangeY = vec2(-100.0f, -100.0f);

		FireEffect.RangeX = vec2(-100.0f, -100.0f);
		FireEffect.RangeY = vec2(-100.0f, -100.0f);

		StepEffect.RangeX = vec2(-100.0f, -100.0f);
		StepEffect2.RangeX = vec2(-100.0f, -100.0f);
		BloodEffect.RangeY = vec2(-100.0f, -100.0f);
		
		playPaladinSteps = false;
		Paladin.setPositionY(0.0f);
		deathTimer += deltaTime;
		if (Paladin.animIndex < 17) //Set initial frame
		{
			Paladin.animIndex = 17;
			Paladin.SetNextAnimation(Paladin.animIndex);
		}
		if (Paladin.animIndex != 23) //Increment only if animation didnt end yet
			Paladin.interp += 0.1f;
		if (Paladin.interp > 1.0f) //Play next frame
		{
			Paladin.animIndex++;
			Paladin.SetNextAnimation(Paladin.animIndex);
		}
		if (Paladin.animIndex == 23 && deathTimer > 2.0f) //Stop playing after 2 seconds
		{
			deathTimer = 0.0f;
			screen = 11;
			loseAnim = false;
			optionsTimer = 0.0f;
		}
		if (Demon.animIndex > 3) //If other animation was playing, set initial frame for idle
		{
			Demon.animIndex = 0;
			Demon.SetNextAnimation(Demon.animIndex);
		}
		Demon.interp += 0.05f;
		if (Demon.interp > 1.0f) {
			Demon.animIndex++;
			if (Demon.animIndex == 4) //End of idle animation, set it back to initial frame
				Demon.animIndex = 0;
			Demon.SetNextAnimation(Demon.animIndex);
		}

		Flame.interp += 0.1f;
		Flame2.interp += 0.1f;
		Flame3.interp += 0.1f;
		Flame4.interp += 0.1f;
		Flame5.interp += 0.1f;
		if (Flame.interp > 1.0f) {
			Flame.SetNextAnimation(FireQ.Front());
			Flame2.SetNextAnimation(FireQ.Front());
			Flame3.SetNextAnimation(FireQ.Front());
			Flame4.SetNextAnimation(FireQ.Front());
			Flame5.SetNextAnimation(FireQ.Front());
			FireQ.addQueue(FireQ.Front());
			FireQ.deleteQueue();
		}
	}
	else if (winAnim) //If death animation didnt play yet
	{
		Fireball.setPosition(vec3(-100.0f, -100.0f, 0.0f));
		FirePillar.setPosition(vec3(-100.0f, -100.0f, 0.0f));

		FireEffect2.RangeX = vec2(-100.0f, -100.0f);
		FireEffect2.RangeY = vec2(-100.0f, -100.0f);

		FireEffect.RangeX = vec2(-100.0f, -100.0f);
		FireEffect.RangeY = vec2(-100.0f, -100.0f);

		StepEffect.RangeX = vec2(-100.0f, -100.0f);
		StepEffect2.RangeX = vec2(-100.0f, -100.0f);
		BloodEffect.RangeY = vec2(-100.0f, -100.0f);

		Portal.setPositionX(Demon.getPositionX() + 1.0f);
		Portal.setRotationY(Portal.getRotationY() + 3.0f);

		playPaladinSteps = false;
		deathTimer += deltaTime;

		if (Portal.getScale().x < 1.0f)
			Portal.setScale(vec3(Portal.getScale().x + 0.025f, 1.0f, Portal.getScale().z + 0.025f));
			
		if (Demon.animIndex == 34 && Portal.getScale().x > 0.0f)
			Portal.setScale(vec3(Portal.getScale().x - 0.05f, 1.0f, Portal.getScale().z - 0.05f));



		if (Demon.animIndex < 30) //Set initial frame
		{
			Demon.animIndex = 30;
			Demon.SetNextAnimation(Demon.animIndex);
		}
		if (Demon.animIndex != 34) //Increment only if animation didnt end yet
			Demon.interp += 0.05f;
		if (Demon.interp > 1.0f) //Play next frame
		{
			Demon.animIndex++;
			Demon.SetNextAnimation(Demon.animIndex);
		}
		if (Demon.animIndex == 34 && deathTimer > 3.0f) //Stop playing after 2 seconds
		{
			deathTimer = 0.0f;
			screen = 8;
			winAnim = false;
			optionsTimer = 0.0f;
		}
		Portal.update();
		if (Paladin.animIndex > 3)
		{
			Paladin.animIndex = 0;
			Paladin.SetNextAnimation(Paladin.animIndex);
		}

		Paladin.interp += 0.08f;
		if (Paladin.interp > 1.0f)
		{
			Paladin.animIndex++;
			if (Paladin.animIndex == 4)
				Paladin.animIndex = 0;
			Paladin.SetNextAnimation(Paladin.animIndex);
		}
		Flame.interp += 0.1f;
		Flame2.interp += 0.1f;
		Flame3.interp += 0.1f;
		Flame4.interp += 0.1f;
		Flame5.interp += 0.1f;
		if (Flame.interp > 1.0f) {
			Flame.SetNextAnimation(FireQ.Front());
			Flame2.SetNextAnimation(FireQ.Front());
			Flame3.SetNextAnimation(FireQ.Front());
			Flame4.SetNextAnimation(FireQ.Front());
			Flame5.SetNextAnimation(FireQ.Front());
			FireQ.addQueue(FireQ.Front());
			FireQ.deleteQueue();
		}

		//Ground Collision
		if (Paladin.getPositionY() + PaladinMoveY - gravity < 0.0f) {
			PaladinMoveY = 0.0f;		//speed set to 0
			Paladin.setPositionY(0.0f);	//Position set to 0
			if (isLandingAir)
			{
				playPaladinLanding = true;
				isLandingAir = false;
			}
		}
		else {
			if (!PaladinDash)
				PaladinMoveY -= gravity; 	//resume gravity
		}

	}
	//Move condition screens here
	else if (screen == 1 && optionsTimer > 0.3f) //MAIN MENU START
	{
		//only play the menu music
		Sound::PlayState(channel_Music, true);
		Sound::PlayState(channel_Ambient, true);
		Sound::PlayState(channel_Ambient2, true);
		Sound::PlayState(channel_DemonBreath, true);
		Sound::PlayState(channel_MenuMusic, false);
		if (key_S)
		{
			playMenuNoise = true;
			screen = 2;
			optionsTimer = 0.0f;
		}
		else if (key_O)
		{
			playMenuNoise = true;
			screen = 0;
			InitializeObjects();
		}
		else if (key_ESC)
			exit(0);
	}
	else if (screen == 2 && optionsTimer > 0.3f) //MAIN MENU CONTROLS
	{
		if (key_W)
		{
			playMenuNoise = true;
			screen = 1;
			optionsTimer = 0.0f;
		}
		else if (key_S)
		{
			playMenuNoise = true;
			screen = 3;
			optionsTimer = 0.0f;
		}
		else if (key_O)
		{
			playMenuNoise = true;
			screen = 4;
			prevScreen = 2;
			optionsTimer = 0.0f;
		}
		else if (key_ESC)
			exit(0);
	}
	else if (screen == 3 && optionsTimer > 0.3f) //MAIN MENU EXIT
	{
		if (key_W)
		{
			playMenuNoise = true;
			screen = 2;
			optionsTimer = 0.0f;
		}
		else if (key_O)
			exit(0);
		else if (key_ESC)
			exit(0);
	}
	else if (screen == 4 && optionsTimer > 0.3f) //CONTROLS
	{
		if (key_O)
		{
			playMenuNoise = true;
			screen = prevScreen;
			optionsTimer = 0.0f;
		}
		else if (key_ESC)
		{
			playMenuNoise = true;
			screen = prevScreen;
			optionsTimer = 0.0f;
		}
		else if (key_P)
		{
			playMenuNoise = true;
			screen = prevScreen;
			optionsTimer = 0.0f;
		}
	}
	else if (screen == 5 && optionsTimer > 0.3f) //PAUSED RESUME
	{
		//pause all game sounds
		Sound::PlayState(channel_Music, true);
		Sound::PlayState(channel_Ambient, true);
		Sound::PlayState(channel_Ambient2, true);
		Sound::PlayState(channel_DemonBreath, true);
		if (key_S)
		{
			playMenuNoise = true;
			screen = 6;
			optionsTimer = 0.0f;
		}
		else if (key_O)
		{
			playMenuNoise = true;
			screen = 0;
			optionsTimer = 0.0f;
		}
		else if (key_ESC)
		{
			playMenuNoise = true;
			screen = 0;
			optionsTimer = 0.0f;
		}
		else if (key_P)
		{
			playMenuNoise = true;
			screen = 0;
			optionsTimer = 0.0f;
		}
	}
	else if (screen == 6 && optionsTimer > 0.3f) //PAUSED CONTROLS
	{
		if (key_W)
		{
			playMenuNoise = true;
			screen = 5;
			optionsTimer = 0.0f;
		}
		else if (key_S)
		{
			playMenuNoise = true;
			screen = 7;
			optionsTimer = 0.0f;
		}
		else if (key_O)
		{
			playMenuNoise = true;
			screen = 4;
			prevScreen = 6;
			optionsTimer = 0.0f;
		}
		else if (key_ESC)
		{
			playMenuNoise = true;
			screen = 0;
			optionsTimer = 0.0f;
		}
		else if (key_P)
		{
			playMenuNoise = true;
			screen = 0;
			optionsTimer = 0.0f;
		}
	}
	else if (screen == 7 && optionsTimer > 0.3f) //PAUSED EXIT
	{
		if (key_W)
		{
			playMenuNoise = true;
			screen = 6;
			optionsTimer = 0.0f;
		}
		else if (key_O)
		{
			playMenuNoise = true;
			screen = 1;
			optionsTimer = 0.0f;
		}
		else if (key_ESC)
		{
			playMenuNoise = true;
			screen = 0;
			optionsTimer = 0.0f;
		}
		else if (key_P)
		{
			playMenuNoise = true;
			screen = 0;
			optionsTimer = 0.0f;
		}
	}
	else if (screen == 8 && optionsTimer > 0.3f) //VICTORY
	{
		channel_PaladinEffect->stop();
		channel_Steps->stop();
		channel_Demon->stop();
		channel_DemonVoice->stop();
		channel_DemonEffect->stop();
		channel_Fireball->stop();
		Sound::PlayState(channel_DemonBreath, true);
		if (optionsTimer > 3.0f)
			screen = 9;
	}
	else if (screen == 9 && optionsTimer > 0.3f) //VICTORY RESTART
	{
		if (key_O)
		{
			playMenuNoise = true;
			screen = 0;
			InitializeObjects();
			optionsTimer = 0.0f;
			playDialogue = false;
		}
		else if (key_S)
		{
			playMenuNoise = true;
			screen = 10;
			optionsTimer = 0.0f;
		}
		else if (key_ESC)
		{
			playMenuNoise = true;
			screen = 1;
			optionsTimer = 0.0f;
		}
		else if (key_P)
		{
			playMenuNoise = true;
			screen = 1;
			optionsTimer = 0.0f;
		}
	}
	else if (screen == 10 && optionsTimer > 0.3f) //VICTORY QUIT
	{
		if (key_O)
		{
			playMenuNoise = true;
			screen = 1;
			optionsTimer = 0.0f;
		}
		else if (key_W)
		{
			playMenuNoise = true;
			screen = 9;
			optionsTimer = 0.0f;
		}
		else if (key_ESC)
		{
			playMenuNoise = true;
			screen = 1;
			optionsTimer = 0.0f;
		}
		else if (key_P)
		{
			playMenuNoise = true;
			screen = 1;
			optionsTimer = 0.0f;
		}
	}
	else if (screen == 11 && optionsTimer > 0.3f) //GAMEOVER
	{
		channel_PaladinEffect->stop();
		channel_Steps->stop();
		channel_Demon->stop();
		channel_DemonVoice->stop();
		channel_DemonEffect->stop();
		channel_Fireball->stop();
		Sound::PlayState(channel_DemonBreath, true);
		if (optionsTimer > 3.0f)
			screen = 12;
	}
	else if (screen == 12 && optionsTimer > 0.3f) //GAMEOVER RESTART
	{
		if (key_O)
		{
			playMenuNoise = true;
			screen = 0;
			InitializeObjects();
			optionsTimer = 0.0f;
			playDialogue = false;
		}
		else if (key_S)
		{
			playMenuNoise = true;
			screen = 13;
			optionsTimer = 0.0f;
		}
		else if (key_ESC)
		{
			playMenuNoise = true;
			screen = 1;
			optionsTimer = 0.0f;
		}
		else if (key_P)
		{
			playMenuNoise = true;
			screen = 1;
			optionsTimer = 0.0f;
		}
	}
	else if (screen == 13 && optionsTimer > 0.3f) //GAMEOVER QUIT
	{
		if (key_O)
		{
			playMenuNoise = true;
			screen = 1;
			optionsTimer = 0.0f;
		}
		else if (key_W)
		{
			playMenuNoise = true;
			screen = 12;
			optionsTimer = 0.0f;
		}
		else if (key_ESC)
		{
			playMenuNoise = true;
			screen = 1;
			optionsTimer = 0.0f;
		}
		else if (key_P)
		{
			playMenuNoise = true;
			screen = 1;
			optionsTimer = 0.0f;
		}
	}
	else if (playDialogue && screen == 0)
	{
		if (cutsceneTimer == 0.0f)
			channel_PaladinEffect = Dialogue.Play(false);
		else if (cutsceneTimer > 13.0f)
			playDialogue = false;

		cutsceneTimer += deltaTime;

		UIPaladin.interp = cutsceneTimer / 13.0f;
		UIDemon.interp = cutsceneTimer / 13.0f;

		if (Paladin.animIndex > 3)
		{
			Paladin.animIndex = 0;
			Paladin.SetNextAnimation(Paladin.animIndex);
		}

		Paladin.interp += 0.08f;
		if (Paladin.interp > 1.0f)
		{
			Paladin.animIndex++;
			if (Paladin.animIndex == 4)
				Paladin.animIndex = 0;
			Paladin.SetNextAnimation(Paladin.animIndex);
		}

		if (Demon.animIndex > 3) //If other animation was playing, set initial frame for idle
		{
			Demon.animIndex = 0;
			Demon.SetNextAnimation(Demon.animIndex);
		}
		Demon.interp += 0.05f;
		if (Demon.interp > 1.0f) {
			Demon.animIndex++;
			if (Demon.animIndex == 4) //End of idle animation, set it back to initial frame
				Demon.animIndex = 0;
			Demon.SetNextAnimation(Demon.animIndex);
		}

		Flame.interp += 0.1f;
		Flame2.interp += 0.1f;
		Flame3.interp += 0.1f;
		Flame4.interp += 0.1f;
		Flame5.interp += 0.1f;
		if (Flame.interp > 1.0f) {
			Flame.SetNextAnimation(FireQ.Front());
			Flame2.SetNextAnimation(FireQ.Front());
			Flame3.SetNextAnimation(FireQ.Front());
			Flame4.SetNextAnimation(FireQ.Front());
			Flame5.SetNextAnimation(FireQ.Front());
			FireQ.addQueue(FireQ.Front());
			FireQ.deleteQueue();
		}

		if (key_O)
		{
			playDialogue = false;
			Dialogue.Stop(channel_PaladinEffect);
		}
	}

	else if (screen == 0)
	{
		if (key_ESC && optionsTimer > 0.3f)
		{
			screen = 5;
			optionsTimer = 0.0f;
		}

		lightningTimer += deltaTime;
		if (lightningTimer > lightningTime)
		{
			lightningAmount = 2.5f;
			if (lightningTimer > lightningTime + 0.25f)
				lightningAmount = 1.0f;
			if (lightningTimer > lightningTime + 0.3f)
				lightningAmount = 2.5f;

			if (lightningTimer > lightningTime + 0.45f)
			{
				playThunderNoise = true;
				lightningTimer = 0.0f;
				lightningTime = static_cast<float>(rand() % 10 + 7);
			}

		}
		else
			lightningAmount = 1.0f;

		//pause menu music and play game sounds
		Sound::PlayState(channel_Music, false);
		Sound::PlayState(channel_Ambient, false);
		Sound::PlayState(channel_Ambient2, false);
		Sound::PlayState(channel_DemonBreath, false);
		Sound::PlayState(channel_MenuMusic, true);
		//Win/Lose Condition
		//Game exits upon player death
		if (PaladinHealth <= 0.0f && Paladin.getPositionY() == 0.0f) { //Only when player hits the ground
			playPaladinDeath = true;
			loseAnim = true;
			PaladinMoveX = 0;
			PaladinMoveY = 0;
			screen = 14;
		}
		else if (DemonHealth <= 0 && Paladin.getPositionY() == 0.0f) {
			Sound::PlayState(channel_DemonBreath, false);
			winAnim = true;
			screen = 14;
		}

		DistDemonFireball = sqrt(pow(Demon.getPositionX() - Fireball.getPositionX(), 2));
		DistPaladinDemon = sqrt(pow(Paladin.getPositionX() - DemonPos, 2)); //Calculates distance
		DistPaladinDemon2 = sqrt(pow(Paladin.getPositionX() - Demon.getPositionX(), 2)); //Calculates distance
		DistPaladinFireballX = sqrt(pow(Paladin.getPositionX() - Fireball.getPositionX(), 2)); //Calculates distance
		DistPaladinFireballY = sqrt(pow(Paladin.getPositionY() - Fireball.getPositionY(), 2)); //Calculates distance
		DistPaladinFirePillar = sqrt(pow(Paladin.getPositionX() - FirePillar.getPositionX(), 2)); //Calculates distance

		StepEffect2.RangeX = vec2(Paladin.getPositionX(), Paladin.getPositionX());
		// MOVEMENT //
		if (PaladinHealth > 0.0f) //While paladin is alive
		{
			// Dash //
			if (dashTimer >= 1.0f) {
				//Ground Dash
				if (key_P == true && prevState == false) {
					PaladinMoveX = 0.0f;
					PaladinMoveY = 0.0f;
					prevState = true;
					playPaladinDash = true;
					PaladinDash = true;
					if (faceRight == true) { PaladinMoveX = 0.8f;}	//dash right
					if (faceLeft == true) { PaladinMoveX = -0.8f;}	//dash left
					dashTimer = 0.0f;
					StepEffect2.RangeY = vec2(Paladin.getPositionY() + 2.0f, Paladin.getPositionY() + 3.0f);
				}
			}
			else {		//if dash is on cooldown, cannot be used
				dashTimer += deltaTime;		//decreases cooldown by deltaTime
				if (dashTimer > 0.15f && PaladinDash)
				{
					PaladinDash = false;
					prevState = true;
					PaladinMoveX = 0.0f;
					PaladinMoveY = 0.0f;
				}
			}
			if (!PaladinDash)
			{
				StepEffect2.RangeY = vec2(-100.0f, -100.0f);
			}


			if (!PaladinDash)
			{
				// Move Left //
				if (key_A && PaladinMoveX > -0.3f) {	//Max velocity
					PaladinMoveX -= 0.028f;				//Initial velocity
					Paladin.setRotationY(260.0f);		//Rotate Paladin to face left
					faceRight = false, faceLeft = true;	//Paladin faces left
				}
				//Slow down movement upon A key release
				else if (key_A == false && PaladinMoveX < 0) {
					PaladinMoveX += 0.028f;				//Slowdown rate
					if (PaladinMoveX > 0.0f)			//Prevents movement after releasing the A key
					{
						PaladinMoveX = 0.0f;			//speed set to 0
					}
				}
				// Move Right //
				if (key_D && PaladinMoveX < 0.3f) {		//Max velocity
					PaladinMoveX += 0.028f;				//Initial velocity 
					Paladin.setRotationY(80.0f);		//Rotate Paladin to face right
					faceRight = true, faceLeft = false;	//Paladin faces right
				}
				//Slow down movement upon D key release
				else if (key_D == false && PaladinMoveX > 0) {
					PaladinMoveX -= 0.028f;				//Slowdown rate
					if (PaladinMoveX < 0.0f)			//Prevents movement after releasing the D key
					{
						PaladinMoveX = 0.0f;			//speed set to 0
					}
				}
			
				if (key_P == false) { prevState = false; }	//prevent repeated keydown input in main loop

				// Jump & Double Jump //
				if (key_SPACE && PaladinMoveY == 0.0f && jumpCount == 0.0f) {
					PaladinMoveY = 0.6f;
					jumpCount = 1;
					playPaladinJump = true;
					playPaladinJumpVoice = true;
					isLandingAir = true;
				}
				//Ground check - if space is still being held
				if (PaladinMoveY == 0.0f) {
					if (key_SPACE == false) jumpCount = 0;
					if (key_SPACE == true) jumpCount = 1;
				}
				//if space is let go in midair, counter increases
				if (jumpCount == 1 && key_SPACE == false) {
					jumpCount++;
				}
				//if counter is 2 and space is pressed, vertical impulse added (double jump)
				if (jumpCount == 2 && key_SPACE == true) {
					PaladinMoveY = 0.6f;	//double jump/vertical impulse value
					jumpCount++;			//turns jump counter to 3
					playPaladinJumpDouble = true;
					playPaladinJumpVoice = true;
					StepEffect.RangeX = vec2(Paladin.getPositionX(), Paladin.getPositionX());
				}
			}



			attackTimer += deltaTime; 	//decreases cooldown by deltaTime
			StabTimer += deltaTime;
			StompTimer += deltaTime;
			FireballTimer += deltaTime;
			FirePillarCoolDown += deltaTime;
			DemonTimer += deltaTime;
			// Attack //
			if (attackTimer > 0.65f) {		//if attack is on cooldown, cannot be used
				//Attack
				if (key_O == true && prevStateAttack == false && !PaladinDash) {
					prevStateAttack = true;
					PaladinAttack = true;
					playPaladinAttack = true;
					playPaladinSwing = true;
					attackTimer = 0;
					//...
				}
				//prevent repeated keydown input in main loop
			}
		}
		if (key_O == false) {
			prevStateAttack = false;
		}

		//Demon Attacks
		if (DemonTimer > 1.7f)
		{
			//Demon attacks if player in range
			if (DistPaladinDemon2 > 18 && StabTimer > 2.5f) //If paladin is far
			{
				DemonAttack = 1; // Stab
				playDemonAttack = true;
				playDemonSwing = true;
				StabTimer = 0;
				DemonTimer = 0;
			}
			else if (DistPaladinDemon2 <= 20 && FirePillarCoolDown > 6.0f) //If paladin is medium range
			{
				DemonAttack = 4; // Fire Pillar
				playFireball = true;
				playDemonAttack = true;
				playDemonRoar = true;
				FirePillarCoolDown = 0;
				DemonTimer = 0;
			}
			else if (FireballTimer > 3.0f)
			{
				DemonAttack = 3; // Fireball
				playFireball = true;
				playDemonAttack = true;
				playDemonSnarl = true;
				FireballTimer = 0;
				DemonTimer = 0;
			}
			else if (DistPaladinDemon2 <= 6.0f && StompTimer > 1.5f) //If paladin is close
			{
				DemonAttack = 2; // Stomp
				playDemonAttack = true;
				playDemonLaugh = true;
				StompTimer = 0;
				DemonTimer = 0;
			}
		}
	
		// ANIMATIONS //
		//Fire animation
		Flame.interp += 0.1f;
		Flame2.interp += 0.1f;
		Flame3.interp += 0.1f;
		Flame4.interp += 0.1f;
		Flame5.interp += 0.1f;
		if (Flame.interp > 1.0f) {
			Flame.SetNextAnimation(FireQ.Front());
			Flame2.SetNextAnimation(FireQ.Front());
			Flame3.SetNextAnimation(FireQ.Front());
			Flame4.SetNextAnimation(FireQ.Front());
			Flame5.SetNextAnimation(FireQ.Front());
			FireQ.addQueue(FireQ.Front());
			FireQ.deleteQueue();
		}

		//Demon attack animation
		if (DemonAttack == 0) { //Idle animation
			if (Demon.animIndex > 3) //If other animation was playing, set initial frame for idle
			{
				Demon.animIndex = 0;
				Demon.SetNextAnimation(Demon.animIndex);
			}
			Demon.interp += 0.05f;
			if (Demon.interp > 1.0f) {
				Demon.animIndex++;
				if (Demon.animIndex == 4) //End of idle animation, set it back to initial frame
					Demon.animIndex = 0;
				Demon.SetNextAnimation(Demon.animIndex);
			}
		}
		else if (DemonAttack == 1) //Stab Attack
		{
			if (Demon.animIndex < 4 || Demon.animIndex > 14) //Set initial frame
			{
				Demon.animIndex = 4;
				Demon.SetNextAnimation(Demon.animIndex);
			}
			Demon.interp += 0.1f;

			if (Demon.interp > 1.0f) {
				Demon.animIndex++;
				if (Demon.animIndex == 9 && DistPaladinDemon2 > 18 && Paladin.getPositionY() < 3.5f) //If paladin is far and close to the ground at this animation, damage it
				{
					ShakeMagnitude = 0.05f;
					PaladinHurt = true;
					Knockback = true;
				}
				if (Demon.animIndex == 15) //End of attack
				{
					DemonAttack = 0;
				}
				else
				{
					Demon.SetNextAnimation(Demon.animIndex);
				}
			}
		}
		else if (DemonAttack == 2) //Stomp attack
		{
			if (Demon.animIndex < 15 || Demon.animIndex > 19) //Set initial frame
			{
				Demon.animIndex = 15;
				Demon.SetNextAnimation(Demon.animIndex);
			}
			Demon.interp += 0.1f;
			if (Demon.interp > 1.0f) {
				Demon.animIndex++;
				if (Demon.animIndex == 19)
				{
					ShakeMagnitude = 0.5f;
					if (DistPaladinDemon2 < 6.0f && Paladin.getPositionY() < 3.5f) //If paladin is close at this animation, damage it
					{
						PaladinHurt = true;
						Knockback = true;
					}
				}
				if (Demon.animIndex == 20) //End of animation
				{
					DemonAttack = 0;
				}
				else
				{
					Demon.SetNextAnimation(Demon.animIndex);
				}
			}
		}
		else if (DemonAttack == 3) //FireBall
		{
			if (Demon.animIndex < 20 || Demon.animIndex > 23) //Set initial frame
			{
				Demon.animIndex = 20;
				Demon.SetNextAnimation(Demon.animIndex);
				Fireball.setPosition(vec3(Demon.getPositionX() - 2.0f, Demon.getPositionY() + 6.0f, Demon.getPositionZ() + 4.0f));
				Fireball.setScale(0.01f);
				FireballDir = vec3(0.0f, 0.0f, 0.0f);
			}
			Demon.interp += 0.07f;
			if (Fireball.getScale().x < 1.0)
				Fireball.setScale(Fireball.getScale().x + 0.05f);
			if (Demon.interp > 1.0f) {
				Demon.animIndex++;
				if (Demon.animIndex == 22 && Fireball.getPosition() == vec3(Demon.getPositionX() - 2.0f, Demon.getPositionY() + 6.0f, Demon.getPositionZ() + 4.0f))
				{
					if (DistPaladinDemon2 > 5.0f)
					{
						FireballDir = (vec3(Paladin.getPositionX(), Paladin.getPositionY() + 2.0f, Paladin.getPositionZ()) - Fireball.getPosition());
						FireballDir.Normalize();
						FireballDir *= 0.7f;
					}
					else
					{
						FireballDir = (vec3(Paladin.getPositionX() - 5.0f, Paladin.getPositionY() + 2.0f, Paladin.getPositionZ()) - Fireball.getPosition());
						FireballDir.Normalize();
						FireballDir *= 0.7f;
					}

				}
				if (Demon.animIndex == 24)
				{
					DemonAttack = 0;
				}
				else
				{
					Demon.SetNextAnimation(Demon.animIndex);
				}
			}
		}
		else if (DemonAttack == 4) //Fire Pillar
		{
			if (Demon.animIndex < 24 || Demon.animIndex > 29) //Set initial frame
			{
				Demon.animIndex = 24;
				Demon.SetNextAnimation(Demon.animIndex);
			}
			Demon.interp += 0.1f;
			if (Demon.interp > 1.0f) {
				Demon.animIndex++;
				if (Demon.animIndex == 28)
				{
					FirePillar.setPosition(vec3(Paladin.getPositionX(), -15.2f, 0.0f));
					FirePillarTimer = 0.0f;
					if (DistPaladinDemon2 < 5 && Paladin.getPositionY() < 3.5f) //If paladin is close at this animation, damage it
					{
						ShakeMagnitude = 0.1f;
						if(!godMode)
							PaladinHealth += 3.0f;
						PaladinHurt = true;
						Knockback = false;
					}
				}
				else if (Demon.animIndex == 30)
				{
					DemonAttack = 0;
				}
				else
				{
					Demon.SetNextAnimation(Demon.animIndex);
				}
			}
		}
		if (Demon.animIndex < 9 && Demon.animIndex > 3 && DemonPos > -5.0f)
			DemonPos -= 0.2f;
		else if (Demon.animIndex >= 9 && DemonPos < 9.0f)
			DemonPos += 0.167f;


		//Paladin animation
		if (PaladinAttack) //Attack animation
		{
			if (Paladin.animIndex < 12 || Paladin.animIndex > 16) //Set first frame
			{
				Paladin.animIndex = 12;
				Paladin.SetNextAnimation(Paladin.animIndex);
			}
			Paladin.interp += 0.34f;
			if (Paladin.interp > 1.0f)
			{
				Paladin.animIndex++;
				if (Paladin.animIndex == 16 && Paladin.getRotationY() == 80.0f && DistPaladinDemon < 5.0f) //If demon is close at this animation, damage it
				{
					ShakeMagnitude = 0.05f;
					DemonHurt = true;
				}
				if (Paladin.animIndex == 16 && Paladin.getRotationY() == 80.0f && DistPaladinFireballX < 2.5f && Fireball.getPositionY() > Paladin.getPositionY() + 0.3f && Fireball.getPositionY() < Paladin.getPositionY() + 3.5f)
				{
					ShakeMagnitude = 0.15f;
					FireballDir = (vec3(Demon.getPositionX(), Demon.getPositionY() + 7.0f, Demon.getPositionZ()) - Fireball.getPosition());
					FireballDir.Normalize();
					FireballDir *= 0.7f;
					Reflect = true;
					playPaladinDeflect = true;

				}
				if (Paladin.animIndex == 17) //End of animation
				{
					PaladinAttack = false;
				}
				else
					Paladin.SetNextAnimation(Paladin.animIndex);
			}
		}
		else if (PaladinDash) //Dash animation
		{
			if (Paladin.animIndex != 11)
			{
				Paladin.animIndex = 11;
				Paladin.SetNextAnimation(Paladin.animIndex);
			}
			Paladin.interp += 0.05f;
			if (Paladin.interp > 1.0f) {
				Paladin.interp = 1.0f;
			}
		}
		else if (PaladinMoveX == 0 && PaladinMoveY == 0) //Idle animation
		{
			if (Paladin.animIndex > 3)
			{
				Paladin.animIndex = 0;
				Paladin.SetNextAnimation(Paladin.animIndex);
			}
			Paladin.interp += 0.08f;
			if (Paladin.interp > 1.0f)
			{
				Paladin.animIndex++;
				if (Paladin.animIndex == 4)
					Paladin.animIndex = 0;
				Paladin.SetNextAnimation(Paladin.animIndex);
			}
		}
		else if (PaladinMoveX != 0 && PaladinMoveY == 0) //If Paladin is moving
		{
			if (Paladin.animIndex < 4 || Paladin.animIndex > 7)
			{
				Paladin.animIndex = 4;
				Paladin.SetNextAnimation(Paladin.animIndex);
			}
			Paladin.interp += 0.13f;
			if (Paladin.interp > 1.0f)
			{
				Paladin.animIndex++;
				if (Paladin.animIndex == 8)
					Paladin.animIndex = 4;
				Paladin.SetNextAnimation(Paladin.animIndex);
			}
		}
		else if (PaladinMoveY > 0) //If Paladin is moving up
		{
			if (Paladin.animIndex != 8 || Paladin.animIndex != 9)
			{

				Paladin.animIndex = 8;
				Paladin.SetNextAnimation(Paladin.animIndex);
			}
			else {
				Paladin.interp += 0.25f;
				if (Paladin.interp > 1.0f && Paladin.animIndex == 8)
				{
					Paladin.animIndex = 9;
					Paladin.SetNextAnimation(Paladin.animIndex);
				}
			}
		}
		else if (PaladinMoveY < 0) //If Paladin is moving down
		{
			if (Paladin.animIndex != 10)
			{
				Paladin.animIndex = 10;
				Paladin.SetNextAnimation(Paladin.animIndex);
			}
			else {
				Paladin.interp += 0.15f;
				if (Paladin.interp > 1.0f)
					Paladin.interp = 1.0f;
			}
		}

		//Fireball
		Fireball.setPosition(Fireball.getPosition() + FireballDir);
		Fireball.setRotationZ(Fireball.getRotationZ() + 10.0f);
		FireEffect.RangeX = vec2(Fireball.getPositionX() - 0.5f, Fireball.getPositionX() + 0.5f);
		FireEffect.RangeY = vec2(Fireball.getPositionY() - 0.5f, Fireball.getPositionY() + 0.5f);
		FireEffect.RangeZ = vec2(Fireball.getPositionZ(), Fireball.getPositionZ());

		if (!Reflect && FireballDir != vec3(0.0f,0.0f,0.0f) && DistPaladinFireballX < 1.5f && ((Paladin.getPositionY() >= Fireball.getPositionY() && DistPaladinFireballY < 0.5f) || (Paladin.getPositionY() < Fireball.getPositionY() && DistPaladinFireballY < 4.3f)))
		{
			ShakeMagnitude = 0.05f;
			PaladinHurt = true;
			Knockback = true;
			FireballDir = vec3(0.0f, 0.0f, 0.0f);
			Fireball.setPosition(vec3(-100.0f, -100.0f, 0.0f));
		}
		//Fireball collision with demon
		if (DistDemonFireball < 1.0f && Reflect)
		{
			DemonHurt = true;
			Fireball.setPosition(vec3(-100.0f, -100.0f, 0.0f));
		}

		//FirePillar
		FirePillarTimer += deltaTime;
		FirePillar.setRotationY(FirePillar.getRotationY() + 5.0f);
		if (FirePillarTimer > 2.0f && FirePillarTimer < 5.0f)
		{
			if(FirePillar.getPositionY() < -1.0f)
				FirePillar.setPositionY(FirePillar.getPositionY() + 1.5f);
		}
		else if (FirePillarTimer >= 4.0f)
		{
			FirePillar.setPosition(vec3(-100.0f, -100.0, 0.0f));
		}
		if (FirePillarTimer > 2.3f && DistPaladinFirePillar < 4.0f)
		{
			if (!godMode)
			{
				PillarHurtTimer += deltaTime;
				ShakeMagnitude = 0.05f;
				PaladinHealth -= 0.1f;
				if (PillarHurtTimer >= 0.5f)
				{
					playPaladinDamage = true;
					PillarHurtTimer = 0.0f;
				}
			}
			FireEffect2.RangeX = vec2(Paladin.getPositionX() - 0.5f, Paladin.getPositionX() + 0.5f);
			FireEffect2.RangeY = vec2(Paladin.getPositionY() + 1.0f, Paladin.getPositionY() + 4.0f);
		}
		else
		{
			FireEffect2.RangeX = vec2(-100.0f, -100.0f);
			FireEffect2.RangeY = vec2(-100.0f, -100.0f);
			PillarHurtTimer = 0.5f;
		}


		BloodEffect.RangeX = vec2(DemonPos, DemonPos);
		BloodTimer += deltaTime;
		//demon flashes red when damaged
		if (DemonHurt) {
			if (Reflect)
				DemonHealth -= 15.0f;
			else
				DemonHealth -= 5.0f;
			Reflect = false;
			Demon.SetTexture(&RedTex);
			DemonHurt = false;
			playDemonDamage = true;
			BloodEffect.RangeY = vec2(Paladin.getPositionY() + 1.0f, Paladin.getPositionY() + 2.0f);
			BloodTimer = 0.0f;
		}
		else {
			if (BloodTimer > 0.2f)
			{
				BloodEffect.RangeY = vec2(-100.0f, -100.0f);
			}
			Demon.SetTexture(&DemonTex);
		}
		//paladin flashes red when damaged
		if (PaladinHurt && PaladinHurtTimer > 1.0f && !godMode) {
			playPaladinDamage = true;
			Paladin.SetTexture(&RedTex);
			PaladinDash = false;
			if (Knockback)
			{
				PaladinMoveX = -0.5f;	//Horizontal knockback value
				PaladinMoveY = 0.4f;	//Vertical knockback value
			}
			PaladinHealth -= 5.0f;
			PaladinHurtTimer = 0.0f;
			PaladinHurt = false;
		}
		else {
			PaladinHurtTimer += deltaTime;
			Paladin.SetTexture(&PaladinTex);
			PaladinHurt = false;
		}

		// COLLISIONS //

		//Ground Collision
		if (Paladin.getPositionY() + PaladinMoveY - gravity < 0.0f) {
			PaladinMoveY = 0.0f;		//speed set to 0
			Paladin.setPositionY(0.0f);	//Position set to 0
			if (isLandingAir)
			{
				playPaladinLanding = true;
				isLandingAir = false;
			}
		}
		else {
			if (!PaladinDash)
				PaladinMoveY -= gravity; 	//resume gravity
		}

		//Ceiling Collision
		//...

		//Left Wall Collision
		if (Paladin.getPositionX() + PaladinMoveX < -16.0f || (Paladin.getPositionX() + PaladinMoveX < -12.0f && Paladin.getPositionY() > 5.0f)) {
			if (PaladinMoveX < 0)
				PaladinMoveX = 0.0f;	//speed set to 0
		}
		//Right Wall Collision
		else if (Paladin.getPositionX() + PaladinMoveX > 18.0f) {
			if (PaladinMoveX > 0)
				PaladinMoveX = 0.0f;	//speed set to 0
		}
		//Left "Catwalk" collision
		if (Paladin.getPositionX() < -12.0f && Paladin.getPositionY() + PaladinMoveY > 5.0f)
		{
			if (PaladinMoveY > 0.0f)
				PaladinMoveY = 0.0f;
		}
		////Collision with Demon
		////TODO: add proper bounding boxes
		if (DistPaladinDemon < 2.0f || Paladin.getPositionX() > DemonPos)
		{
			if (PaladinMoveX > 0.0f)
				PaladinMoveX = 0;
			Paladin.setPositionX(DemonPos - 2.0f);
		}



		//Set paladin position
		Paladin.setPosition(vec3(Paladin.getPositionX() + PaladinMoveX, Paladin.getPositionY() + PaladinMoveY, 0.0f));

		if (PaladinMoveX != 0 && Paladin.getPositionY() <= 0.1f)
			StepEffect.RangeX = vec2(Paladin.getPositionX(), Paladin.getPositionX());
		else
			StepEffect.RangeX = vec2(-100, -100);

		//Camera follows paladin, stops following at certain values
		if (Paladin.getPositionX() >= -6.9f && Paladin.getPositionX() <= 7.0f) {
			camera.setPositionX(Paladin.getPositionX());
		}
		camera.setPosition(vec3(camera.getPositionX() - ShakeX, 5.0f, 20.0f)); //Resets camera

		if (ShakeMagnitude > 0) //While magnitude is still above 0
		{
			ShakeX = static_cast<float>(rand() % 2 - 1);
			ShakeY = static_cast<float>(rand() % 2 - 1);
			ShakeX *= ShakeMagnitude;
			ShakeY *= ShakeMagnitude;
			camera.setPosition(vec3(ShakeX + camera.getPositionX(), ShakeY + camera.getPositionY(), 20.0f));
			ShakeMagnitude -= 0.015f;
		}
		else //Reset screen shake
		{
			ShakeX = 0.0f;
			ShakeY = 0.0f;
		}

		//Set UI position
		UIPaladin.setPositionX(camera.getPositionX() - 20.0f);
		UIDemon.setPositionX(camera.getPositionX() + 20.0f);
		UIPaladin.interp = PaladinHealth / 50;
		UIDemon.interp = DemonHealth / 150;


		
		if (playThunderNoise)
		{
			channel_Thunder = Thunder.Play(false);
			playThunderNoise = false;
		}

		// Paladin Sounds //
		if (playPaladinSwing)
		{
			randomSound = rand() % 2 + 1;
			if (randomSound == 1)
				channel_PaladinEffect = PaladinSwing1.Play(false);
			else if (randomSound == 2)
				channel_PaladinEffect = PaladinSwing2.Play(false);
			playPaladinSwing = false;
		}
		if (playPaladinDash)
		{
			channel_PaladinEffect = PaladinDash1.Play(false);
			playPaladinDash = false;
		}
		if (playPaladinJump)
		{
			channel_PaladinEffect = PaladinJump.Play(false);
			playPaladinJump = false;
		}
		if (playPaladinJumpDouble)
		{
			channel_PaladinEffect = PaladinJumpDouble.Play(false);
			playPaladinJumpDouble = false;
		}
		if (playPaladinJumpVoice)
		{
			randomSound = rand() % 2 + 1;
			if (randomSound == 1)
				channel_Paladin = PaladinJump1.Play(false);
			else if (randomSound == 2)
				channel_Paladin = PaladinJump2.Play(false);
			playPaladinJumpVoice = false;
		}
		if (playPaladinAttack)
		{
			randomSound = rand() % 2 + 1;
			if (randomSound == 1)
				channel_Paladin = PaladinAttack1.Play(false);
			else if (randomSound == 2)
				channel_Paladin = PaladinAttack2.Play(false);
			playPaladinAttack = false;
		}
		if (playPaladinDamage)
		{
			randomSound = rand() % 2 + 1;
			if (randomSound == 1)
				channel_Paladin = PaladinDamage1.Play(false);
			else if (randomSound == 2)
				channel_Paladin = PaladinDamage2.Play(false);
			playPaladinDamage = false;
		}
		if (playPaladinDeath)
		{
			randomSound = rand() % 2 + 1;
			if (randomSound == 1)
				channel_Paladin = PaladinDeath1.Play(false);
			else if (randomSound == 2)
				channel_Paladin = PaladinDeath2.Play(false);
			playPaladinDeath = false;
		}
		if (playPaladinSteps && Paladin.getPositionY() <= 0.0f)
		{
			if (!isStepPlaying)
			{
				channel_Steps = PaladinSteps.Play(true);
				isStepPlaying = true;
			}
		}
		else
		{
			channel_Steps->stop();
			isStepPlaying = false;
			playPaladinSteps = false;
		}
		if (playPaladinLanding)
		{
			channel_PaladinEffect = PaladinLanding.Play(false);
			playPaladinLanding = false;
		}
		if (playPaladinVoice)
		{
			channel_Paladin = PaladinVoice.Play(false);
			playPaladinVoice = false;
		}
		if (playPaladinDeflect)
		{
			channel_PaladinEffect = PaladinDeflect.Play(false);
			playPaladinDeflect = false;
		}

		
		// Demon Sounds //
		if (playDemonSwing)
		{
			randomSound = rand() % 3 + 1;
			if (randomSound == 1)
				channel_DemonEffect = DemonSwing1.Play(false);
			else if (randomSound == 2)
				channel_DemonEffect = DemonSwing2.Play(false);
			else if (randomSound == 3)
				channel_DemonEffect = DemonSwing3.Play(false);
			playDemonSwing = false;
		}
		if (playDemonAttack)
		{
			randomSound = rand() % 3 + 1;
			if (randomSound == 1)
				channel_Demon = DemonAttack1.Play(false);
			else if (randomSound == 2)
				channel_Demon = DemonAttack2.Play(false);
			else if (randomSound == 3)
				channel_Demon = DemonAttack3.Play(false);
			playDemonAttack = false;
		}
		if (playDemonDamage)
		{
			randomSound = rand() % 5 + 1;
			if (randomSound == 1)
				channel_Demon = DemonDamage1.Play(false);
			else if (randomSound == 2)
				channel_Demon = DemonDamage2.Play(false);
			else if (randomSound == 3)
				channel_Demon = DemonDamage3.Play(false);
			else if (randomSound == 4)
				channel_Demon = DemonCrit1.Play(false);
			else if (randomSound == 5)
				channel_Demon = DemonCrit2.Play(false);
			playDemonDamage = false;
		}
		if (playDemonLaugh)
		{
			channel_DemonVoice = DemonLaugh.Play(false);
			playDemonLaugh = false;
		}
		if (playDemonRoar)
		{
			randomSound = rand() % 3 + 1;
			if (randomSound == 1)
				channel_DemonVoice = DemonRoar1.Play(false);
			else if (randomSound == 2)
				channel_DemonVoice = DemonRoar2.Play(false);
			else if (randomSound == 3)
				channel_DemonVoice = DemonRoar3.Play(false);
			playDemonRoar = false;
		}
		if (playDemonSnarl)
		{
			randomSound = rand() % 3 + 1;
			if (randomSound == 1)
				channel_DemonVoice = DemonSnarl1.Play(false);
			else if (randomSound == 2)
				channel_DemonVoice = DemonSnarl2.Play(false);
			else if (randomSound == 3)
				channel_DemonVoice = DemonSnarl3.Play(false);
			playDemonSnarl = false;
		}
		if (playFireball)
		{
			randomSound = rand() % 4 + 1;
			if (randomSound == 1)
				channel_Fireball = Fire1.Play(false);
			else if (randomSound == 2)
				channel_Fireball = Fire2.Play(false);
			else if (randomSound == 3)
				channel_Fireball = Fire3.Play(false);
			else if (randomSound == 4)
				channel_Fireball = Fire4.Play(false);
			playFireball = false;
		}
		
		// convert paladin position to FMOD Vec3
		paladinPos.x = Paladin.getPositionX();
		paladinPos.y = Paladin.getPositionY();
		paladinPos.z = Paladin.getPositionZ();
		// convert demon position to FMOD Vec3
		demonPos.x = Demon.getPositionX();
		demonPos.y = Demon.getPositionY();
		demonPos.z = Demon.getPositionZ();
		// convert fireball position to FMOD Vec3
		firePos.x = Fireball.getPositionX();
		firePos.y = Fireball.getPositionY();
		firePos.z = Fireball.getPositionZ();
		// set channel positions
		channel_Paladin->set3DAttributes(&paladinPos, &soundVel);
		channel_PaladinEffect->set3DAttributes(&paladinPos, &soundVel);
		channel_Steps->set3DAttributes(&paladinPos, &soundVel);
		channel_Demon->set3DAttributes(&demonPos, &soundVel);
		channel_DemonVoice->set3DAttributes(&demonPos, &soundVel);
		channel_DemonEffect->set3DAttributes(&demonPos, &soundVel);
		channel_DemonBreath->set3DAttributes(&demonPos, &soundVel);
		channel_Fireball->set3DAttributes(&firePos, &soundVel);
		channel_Thunder->set3DAttributes(&thunderPos, &soundVel);

		channel_Paladin->setVolume(volume);
		channel_PaladinEffect->setVolume(volume);
		channel_Steps->setVolume(volume);
		channel_Demon->setVolume(volume);
		channel_DemonVoice->setVolume(volume);
		channel_DemonEffect->setVolume(volume);
		channel_Fireball->setVolume(volume);
		channel_DemonBreath->setVolume(volume);
	}

	if (playMenuNoise)
	{
		channel_Menu = MenuNoise.Play(false);
		playMenuNoise = false;
	}
	
	//Update Objects
	Paladin.update();
	UIPaladin.update();
	UIDemon.update();
	camera.update();
	Fireball.update();
	FirePillar.update();
	StepEffect.update(deltaTime);
	FireEffect.update(deltaTime);
	FireEffect2.update(deltaTime);
	BloodEffect.update(deltaTime);
	StepEffect2.update(deltaTime);

	//Update Sound
	camPos.x = camera.getPositionX();
	camPos.y = camera.getPositionY() + 10.0f;
	camPos.z = camera.getPositionZ();
	channel_Music->set3DAttributes(&camPos, &soundVel);
	channel_MenuMusic->set3DAttributes(&camPos, &soundVel);
	channel_Menu->set3DAttributes(&camPos, &soundVel);
	Sound::SetVolume(channel_Music, musicVolume);
	Sound::SetVolume(channel_MenuMusic, musicVolume);
	camPos.y -= 10.0f;
	Sound::engine.update(camPos);

	mat4 bias =
		mat4(0.5f, 0.0f, 0.0f, 0.5f,
			0.0f, 0.5f, 0.0f, 0.5f,
			0.0f, 0.0f, 0.5f, 0.5f,
			0.0f, 0.0f, 0.0f, 1.0f);

	ViewToShadowMap.LoadIdentity();
	ViewToShadowMap = bias * ShadowProjection * ShadowTransform.GetInverse() * camera.getView();
}

void Game::DrawFullScreenQuads()
{
	SobelPass.bind();
	SobelPass.SendUniform("uPixelSize", vec2(1.0f / WINDOW_WIDTH, 1.0f / WINDOW_HEIGHT));
	SobelPass.SendUniform("uToonShading", ToonShading);
	EdgeMap.bind();

	GBuffer.bindColor(1, 0);
	GBuffer.bindDepth(1);
	DrawFullScreenQuad();
	GBuffer.unbind(1);
	GBuffer.unbind(0);

	EdgeMap.unbind();
	SobelPass.unbind();


	//Create scene from GBuffer
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	DeferredLighting.bind();
	DeferredLighting.SendUniformMat4("ViewToShadowMap", ViewToShadowMap.data, true);
	DeferredLighting.SendUniform("LightDirection", camera.getView().GetInverse().GetRotationMat() * ShadowTransform.GetDirectionVec());
	DeferredLighting.SendUniform("LightPosition2", camera.getView().GetInverse() * vec4(-6.95f, 5.85f, -7.8f, 1.0f));
	DeferredLighting.SendUniform("LightPosition3", camera.getView().GetInverse() * vec4(5.8f, 0.9f, 3.19f, 1.0f));
	DeferredLighting.SendUniform("uToonShading", ToonShading);
	DeferredLighting.SendUniform("uLightning", lightningAmount);

	DeferredComposite.bind();

	GBuffer.bindColor(0, 0);
	ShadowMap.bindDepth(1);
	GBuffer.bindColor(1, 2);
	GBuffer.bindColor(2, 3);
	GBuffer.bindColor(3, 4);
	EdgeMap.bindColor(0, 5);
	ToonTex.bind(6);
	GBuffer.bindColor(4, 7);
	DrawFullScreenQuad();
	GBuffer.unbind(7);
	ToonTex.unbind(6);
	EdgeMap.unbind(5);
	GBuffer.unbind(4);
	GBuffer.unbind(3);
	GBuffer.unbind(2);
	ShadowMap.unbind(1);
	GBuffer.unbind(0);

	DeferredComposite.unbind();
	DeferredLighting.unbind();

	//Compute High Pass
	glViewport(0, 0, GLsizei(WINDOW_WIDTH / BLOOM_DOWNSCALE), GLsizei(WINDOW_HEIGHT / BLOOM_DOWNSCALE));

	BloomHighPass.bind();
	BloomHighPass.SendUniform("uThreshold", BLOOM_THRESHOLD);
	BloomHighPass.SendUniform("uActive", Bloom);
	WorkBuffer1.bind();

	DeferredComposite.bindColor(0, 0);
	GBuffer.bindColor(3, 1);
	DrawFullScreenQuad();
	GBuffer.unbind(1);
	DeferredComposite.unbind(0);

	WorkBuffer1.unbind();
	BloomHighPass.unbind();

	//Compute Blur
	glViewport(0, 0, GLsizei(WINDOW_WIDTH / BLOOM_DOWNSCALE), GLsizei(WINDOW_HEIGHT / BLOOM_DOWNSCALE));
	for (int i = 0; i < BLOOM_BLUR_PASSES; i++)
	{
		//Horizontal
		BlurHorizontal.bind();
		BlurHorizontal.SendUniform("uPixelSize", 1.0f / WINDOW_WIDTH);

		WorkBuffer2.bind();

		WorkBuffer1.bindColor(0, 0);
		DrawFullScreenQuad();
		WorkBuffer1.unbind(0);

		WorkBuffer2.unbind();
		BlurHorizontal.unbind();

		//Vertical
		BlurVertical.bind();
		BlurVertical.SendUniform("uPixelSize", 1.0f / WINDOW_HEIGHT);

		WorkBuffer1.bind();

		WorkBuffer2.bindColor(0, 0);
		DrawFullScreenQuad();
		WorkBuffer2.unbind(0);

		WorkBuffer1.unbind();
		BlurVertical.unbind();
	}

	//Composite to back buffer
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	DofPass1.bind();
	BloomComposite.bind();

	DeferredComposite.bindColor(0, 0);
	WorkBuffer1.bindColor(0, 1);
	DrawFullScreenQuad();
	WorkBuffer1.unbind(1);
	DeferredComposite.unbind(0);

	BloomComposite.unbind();
	DofPass1.unbind();


	//Depth of field
	float a = (camera.m_pFar + camera.m_pNear) / (camera.m_pFar - camera.m_pNear);
	float b = (-2 * (camera.m_pFar * camera.m_pNear)) / (camera.m_pFar - camera.m_pNear) / 5.0f;
	float focusDepth = (a + b) * 0.5f + 0.5f;

	//Horizontal
	DofPass2.bind();
	DoFHorizontal.bind();
	DoFHorizontal.SendUniform("uFocus", focusDepth);
	DoFHorizontal.SendUniform("uPixelSize", vec2(1.0f / WINDOW_WIDTH, 1.0f / WINDOW_HEIGHT));

	DofPass1.bindColor(0, 0);
	GBuffer.bindDepth(1);
	GBuffer.bindColor(3, 2);
	DrawFullScreenQuad();
	GBuffer.unbind(2);
	GBuffer.unbind(1);
	DofPass1.unbind(0);

	DoFHorizontal.unbind();
	DofPass2.unbind();

	//Vertical
	LUTBuffer.bind();
	DoFVertical.bind();
	DoFVertical.SendUniform("uFocus", focusDepth);
	DoFVertical.SendUniform("uPixelSize", vec2(1.0f / WINDOW_WIDTH, 1.0f / WINDOW_HEIGHT));

	DofPass2.bindColor(0, 0);
	GBuffer.bindDepth(1);
	GBuffer.bindColor(3, 2);
	DrawFullScreenQuad();
	GBuffer.unbind(2);
	GBuffer.unbind(1);
	DofPass2.unbind(0);

	DoFVertical.unbind();
	LUTBuffer.unbind();

	//LUT Shader
	LUTShader.bind();
	LUTShader.SendUniform("LUTsize", static_cast<float>(LUTTex.LUTsize));
	LUTShader.SendUniform("uAmount", 1.0f);
	ScreenBuffer.bind();

	LUTBuffer.bindColor(0, 0);
	if (currentLUT == 0)
		LUTTex.bind3D(10);
	else if (currentLUT == 1)
		LUTCool.bind3D(10);
	else if (currentLUT == 2)
		LUTWarm.bind3D(10);
	DrawFullScreenQuad();
	LUTTex.unbind3D(10);
	LUTBuffer.unbind(0);

	LUTShader.unbind();
	ScreenBuffer.unbind();

	// Screens(PAUSE,MENU,END)
	Screen.bind();
	Screen.SendUniform("uIndex", screen);
	if (screen == 0 || screen == 14)
		ScreenBuffer.bindColor(0, 0);
	else if (screen == 1)
		MainMenu0.bind(0);
	else if (screen == 2)
		MainMenu1.bind(0);
	else if (screen == 3)
		MainMenu2.bind(0);
	else if (screen == 4)
		Controls.bind(0);
	else if (screen == 5)
		Paused0.bind(0);
	else if (screen == 6)
		Paused1.bind(0);
	else if (screen == 7)
		Paused2.bind(0);
	else if (screen == 8)
		Victory0.bind(0);
	else if (screen == 9)
		Victory1.bind(0);
	else if (screen == 10)
		Victory2.bind(0);
	else if (screen == 11)
		GameOver0.bind(0);
	else if (screen == 12)
		GameOver1.bind(0);
	else if (screen == 13)
		GameOver2.bind(0);

	if (Normals)
		GBuffer.bindColor(1, 0);
	else if (Positions)
		GBuffer.bindColor(2, 0);

	DrawFullScreenQuad();
	ScreenBuffer.unbind(0);

	Screen.unbind();
}

void Game::draw()
{
	glClearColor(0.00f, 0.00f, 0.05f, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	GBuffer.clear();
	WorkBuffer1.clear();
	WorkBuffer2.clear();
	ShadowMap.clear();
	LUTBuffer.clear();
	DeferredComposite.clear();
	EdgeMap.clear();
	ScreenBuffer.clear();
	DofPass1.clear();
	DofPass2.clear();

	glActiveTexture(GL_TEXTURE0);

	//Generate Shadow Map
	glViewport(0, 0, SHADOW_RESOLUTION, SHADOW_RESOLUTION);

	ShadowMap.bind();
	Shader.bind();
	Shader.SendUniformMat4("uView", ShadowTransform.GetInverse().data, true);
	Shader.SendUniformMat4("uProj", ShadowProjection.data, true);

	Shader.drawNoTex();

	ShadowMap.unbind();
	Shader.unbind();

	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	if (screen == 0)
	{
		//UI shader
		camera.setRotationX(10.0f + camera.getRotationX());
		camera.setPosition(vec3(0.0f, -6.5f, 0.0f) + camera.getPosition());
		camera.orthographic(WINDOW_WIDTH / -40, WINDOW_WIDTH / 40, WINDOW_HEIGHT / 40, WINDOW_HEIGHT / -40, 0.01f, 1000.0f);
		UIShader.bind();
		UIShader.SendUniformMat4("uView", camera.getView().GetInverse().data, true);
		UIShader.SendUniformMat4("uProj", camera.getProjection().data, true);

		UIShader.draw();

		UIShader.unbind();
		camera.setPosition(vec3(0.0f, 6.5f, 0.0f) + camera.getPosition());
		camera.setRotationX(-10.0f + camera.getRotationX());
		camera.perspective(60.0f, (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.01f, 1000.0f);
	}

	//bind gbuffer

	GBuffer.bind();
	//Bind normal shader
	Shader.bind();
	Shader.SendUniformMat4("uView", camera.getView().GetInverse().data, true);
	Shader.SendUniformMat4("uProj", camera.getProjection().data, true);

	Shader.draw();

	Shader.unbind();

	//No light shader
	NoLightShader.bind();
	NoLightShader.SendUniformMat4("uView", camera.getView().GetInverse().data, true);
	NoLightShader.SendUniformMat4("uProj", camera.getProjection().data, true);

	NoLightShader.draw();

	NoLightShader.unbind();

	//Particles shader
	BillBoard.bind();
	BillBoard.SendUniformMat4("uView", camera.getView().GetInverse().data, true);
	BillBoard.SendUniformMat4("uProj", camera.getProjection().data, true);

	BillBoard.drawParticles();

	BillBoard.unbind();

	//unbind gbuffer
	GBuffer.unbind();

	glDisable(GL_BLEND);
	DrawFullScreenQuads();
	glEnable(GL_BLEND);

	glBindTexture(GL_TEXTURE_2D, GL_NONE);
	glBindVertexArray(GL_NONE);

	glutSwapBuffers();
}

void Game::keyboardDown(unsigned char key, int mouseX, int mouseY)
{
	if (key == 27) //ESC
	{
		key_ESC = true;
	}
	if (key == 'w' || key == 'W') //W
	{
		key_W = true;
		if (screen == 0)
			key_SPACE = true;
	}
	if (key == 'a' || key == 'A') //A
	{
		key_A = true;
		playPaladinSteps = true;
	}
	if (key == 's' || key == 'S') //S
		key_S = true;
	if (key == 'd' || key == 'D') //D
	{
		key_D = true;
		playPaladinSteps = true;
	}
	if (key == 'o' || key == 'O') //O
		key_O = true;
	if (key == 'p' || key == 'P') //P
		key_P = true;

	if (key == ' ') //SPACE
		key_SPACE = true;

	switch (key) {
	case '0':
		Shader.reload();
		UIShader.reload();
		BloomHighPass.reload();
		BlurHorizontal.reload();
		BlurVertical.reload();
		BloomComposite.reload();
		NoLightShader.reload();
		LUTShader.reload();
		DeferredLighting.reload();
		SobelPass.reload();
		Screen.reload();
		DoFHorizontal.reload();
		DoFVertical.reload();
		break;
	case 'm':
		if (!musicState)
		{
			//Sound::PlayState(channel_Music, true);
			Sound::SetVolume(channel_Music, 0.0f);
			musicState = true;
		}
		else
		{
			//Sound::PlayState(channel_Music, false);
			Sound::SetVolume(channel_Music, 0.2f);
			musicState = false;
		}
		break;
	}
}

void Game::keyboardUp(unsigned char key, int mouseX, int mouseY)
{
	if (key == 27) //ESC
	{
		key_ESC = false;
	}

	if (key == 'a' || key == 'A') //A
	{
		key_A = false;
		playPaladinSteps = false;
	}
	if (key == 'd' || key == 'D') //D
	{
		key_D = false;
		playPaladinSteps = false;
	}
	if (key == 'w' || key == 'W') //W
	{
		key_W = false;
		if (screen == 0)
			key_SPACE = false;
	}
	if (key == 's' || key == 'S') //S
		key_S = false;

	if (key == 'o' || key == 'O') //O
		key_O = false;
	if (key == 'p' || key == 'P') //P
		key_P = false;

	if (key == ' ') //SPACE
		key_SPACE = false;
}

void Game::keyboardSpecialDown(int key, int mouseX, int mouseY)
{
	switch (key)
	{
	case GLUT_KEY_F1:
		currentLUT = 0;
		break;
	case GLUT_KEY_F2:
		currentLUT = 1;
		break;
	case GLUT_KEY_F3:
		currentLUT = 2;
		break;
	case GLUT_KEY_F4:
		ToonShading = !ToonShading;
		break;
	case GLUT_KEY_F5:
		Bloom = !Bloom;
		break;
	case GLUT_KEY_F6:
		Normals = !Normals;
		break;
	case GLUT_KEY_F7:
		Positions = !Positions;
		break;
	case GLUT_KEY_F9:
		bgm8bit = !bgm8bit;
		if (bgm8bit)
		{
			musicVolume = 0.9f;
			BGM.Stop(channel_Music);
			channel_Music = BGM8bit.Play(true);
		}
		else if (!bgm8bit)
		{
			musicVolume = 0.4f;
			BGM8bit.Stop(channel_Music);
			channel_Music = BGM.Play(true);
		}
		break;
	case GLUT_KEY_F10:
		godMode = !godMode;
		break;
	case GLUT_KEY_UP:
		volume += 0.1f;
		if (volume > 1.0f)
			volume = 1.0f;
		break;
	case GLUT_KEY_DOWN:
		volume -= 0.1f;
		if (volume < 0.0f)
			volume = 0.0f;
		break;
	case GLUT_KEY_PAGE_UP:
		musicVolume += 0.1f;
		if (musicVolume > 1.0f)
			musicVolume = 1.0f;
		break;
	case GLUT_KEY_PAGE_DOWN:
		musicVolume -= 0.1f;
		if (musicVolume <= 0.0f)
			musicVolume = 0.0f;
		break;
	}
}

void Game::mouseClicked(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN) {

		switch (button) {
		case GLUT_LEFT_BUTTON:
			//...
			break;
		case GLUT_RIGHT_BUTTON:
			//...
			break;
		case GLUT_MIDDLE_BUTTON:
			//...
			break;
		}
	}
	else {
		//...
	}
}

/*
 * mouseMoved(x,y)
 * - this occurs only when the mouse is pressed down
 *   and the mouse has moved.  you are given the x,y locations
 *   in window coordinates (from the top left corner) and thus
 *   must be converted to screen coordinates using the screen to window pixels ratio
 *   and the y must be flipped to make the bottom left corner the origin.
 */
void Game::mouseMoved(int x, int y)
{
	//...
}
