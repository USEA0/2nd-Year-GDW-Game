#pragma once

#include <windows.h>

#include "Mesh.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "FrameBuffer.h"
#include "CollisionBox.h"
#include "ParticleEffect.h"

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/freeglut.h>

#include "Timer.h"
#include "Camera.h"
#include "Transform.h"
#include "FmodWrapper.h"
#include "Queue.h"

//Laptop Native Resolution: 1920x1080
#define WINDOW_WIDTH			1920
#define WINDOW_HEIGHT			1080
//#define WINDOW_WIDTH			1600
//#define WINDOW_HEIGHT			900
#define FRAMES_PER_SECOND		60
#define BLOOM_THRESHOLD			0.55f
#define BLOOM_DOWNSCALE			4.0f
#define BLOOM_BLUR_PASSES		4
#define SHADOW_RESOLUTION		8192


class Game
{
public:
	Game();
	~Game();

	void initializeGame();
	void update();
	void draw();
	void loadAssets();
	void DrawFullScreenQuads();
	void InitializeObjects();

	// input callback functions //
	void keyboardDown(unsigned char key, int mouseX, int mouseY);
	void keyboardUp(unsigned char key, int mouseX, int mouseY);
	void keyboardSpecialDown(int key, int mouseX, int mouseY);
	void mouseClicked(int button, int state, int x, int y);
	void mouseMoved(int x, int y);

	// Data Members //
	Timer *updateTimer = nullptr;
	float TotalGameTime = 0.0f;

	// Meshes //
	Mesh
		Paladin,
		Demon,
		SmallObjects,
		BigObjects,
		Flame,
		Flame2,
		Flame3,
		Flame4,
		Flame5,
		FirePillar,
		Grass,
		InteriorObj,
		ExteriorObj,
		UIPaladin,
		UIDemon,
		Skybox,
		Fireball,
		Portal;

	// Textures //
	Texture
		RedTex,
		BlackTex,
		WhiteTex,
		PaladinTex,
		DemonTex,
		SmallObjTex,
		BigObjTex,
		FireTex,
		GrassTex,
		InteriorObjTex,
		ExteriorObjTex,
		UITex,
		SkyboxTex,
		LUTTex,
		LUTCool,
		LUTWarm,
		ToonTex,
		PaladinEmissive,
		DemonEmissive,
		PillarTex,
		FireballTex,
		PortalTex;

	Texture
		Controls,
		GameOver0,
		GameOver1,
		GameOver2,
		MainMenu0,
		MainMenu1,
		MainMenu2,
		Paused0,
		Paused1,
		Paused2,
		Victory0,
		Victory1,
		Victory2;

	// Particles //
	ParticleEffect
		StepEffect,
		FireEffect,
		FireEffect2,
		BloodEffect,
		StepEffect2;
	

	// Shaders //
	ShaderProgram
		Shader,
		UIShader,
		BloomHighPass,
		BlurHorizontal,
		BlurVertical,
		BloomComposite,
		NoLightShader,
		LUTShader,
		DeferredLighting,
		BillBoard,
		SobelPass,
		Screen,
		DoFHorizontal,
		DoFVertical;

	// FrameBufffers //
	FrameBuffer
		GBuffer,
		WorkBuffer1,
		WorkBuffer2,
		ShadowMap,
		LUTBuffer,
		DeferredComposite,
		EdgeMap,
		ScreenBuffer,
		DofPass1,
		DofPass2;

	mat4
		ShadowTransform,
		ShadowProjection,
		ViewToShadowMap;

	// Sounds //
	/// Music
	Sound BGM, MenuMusic, BGM8bit;
	Sound BrownNoise;
	Sound MenuNoise;
	Sound Thunder;
	Sound Dialogue;
	/// Fire
	Sound AmbientFire;
	Sound Fire1, Fire2, Fire3, Fire4; //random
	/// Paladin
	Sound PaladinSwing1, PaladinSwing2; //random effect
	Sound PaladinDash1; //effect
	Sound PaladinVoice; //voice
	Sound PaladinJump, PaladinJumpDouble; //effect
	Sound PaladinJump1, PaladinJump2; //voice
	Sound PaladinAttack1, PaladinAttack2; //voice
	Sound PaladinDamage1, PaladinDamage2; //voice
	Sound PaladinDeath1, PaladinDeath2; //voice
	Sound PaladinSteps, PaladinLanding;
	Sound PaladinDeflect;
	/// Demon
	Sound DemonSwing1, DemonSwing2, DemonSwing3; //random effect
	Sound DemonAttack1, DemonAttack2, DemonAttack3; //random voice
	Sound DemonBreath; //voice
	Sound DemonBurn; //voice
	Sound DemonCrit1, DemonCrit2; //random voice
	Sound DemonDamage1, DemonDamage2, DemonDamage3; //random voice
	Sound DemonLaugh; //voice
	Sound DemonRoar1, DemonRoar2, DemonRoar3; //random voice
	Sound DemonSnarl1, DemonSnarl2, DemonSnarl3; //random voice

	// Sound Channels //
	FMOD::Channel* channel_Music; // Music
	FMOD::Channel* channel_Ambient; // Ambient
	FMOD::Channel* channel_Ambient2;
	FMOD::Channel* channel_Thunder;
	FMOD::Channel* channel_Menu;
	FMOD::Channel* channel_MenuMusic;

	FMOD::Channel* channel_Paladin;
	FMOD::Channel* channel_PaladinEffect;
	FMOD::Channel* channel_Steps;
	FMOD::Channel* channel_Demon;
	FMOD::Channel* channel_DemonVoice;
	FMOD::Channel* channel_DemonBreath;
	FMOD::Channel* channel_DemonEffect;
	FMOD::Channel* channel_Fireball;

	// Sound Booleans //
	bool playFire = false; //efect
	bool isFirePlayed = false;
	bool playMenuNoise = false; //other
	bool playThunderNoise = false;
	bool isStepPlaying = false;
	bool playDialogue = false;
	bool bgm8bit = false;

	bool playPaladinSwing = false; //effect
	bool playPaladinDash = false; //effect
	bool playPaladinJump = false; //effect
	bool playPaladinJumpDouble = false; //effect
	bool playPaladinJumpVoice = false;
	bool playPaladinAttack = false; //voice
	bool playPaladinDamage = false; //voice
	bool playPaladinDeath = false; //voice
	bool playPaladinSteps = false; //effect
	bool playPaladinLanding = false;
	bool isLandingAir = false;
	bool playPaladinVoice = false;
	bool playPaladinDeflect = false;

	bool playDemonSwing = false; //effect
	bool playDemonAttack = false; //voice
	bool playDemonBreath = false; //voice
	bool playDemonDamage = false; //voice
	bool playDemonLaugh = false; //voice
	bool playDemonRoar = false; //voice
	bool playDemonSnarl = false; //voice 
	bool playFireball = false; //voice 

	// FMOD variables //
	int randomSound;
	bool musicState = false;
	float volume = 1.0f;
	float musicVolume = 0.4f;
	FMOD_VECTOR soundVel = { 0.0f, 0.0f, 0.0f };
	FMOD_VECTOR posTemp = { 0.0f, 0.0f, 2.0f };
	FMOD_VECTOR thunderPos = { 0.0f, 0.0f, 0.0f };
	FMOD_VECTOR camPos;
	FMOD_VECTOR paladinPos;
	FMOD_VECTOR demonPos;
	FMOD_VECTOR firePos;



	// Attribute Values //

	// World / General
	float gravity = 0.04f;

	//Queue for Fire animation
	Queue FireQ;

	// Paladin
	int jumpCount = 0;			//keeps track of jump count
	float PaladinHealth = 50;	//health
	float PaladinMoveX = 0.0f;	//movement on horiz axis
	float PaladinMoveY = 0.0f;	//movement on verti axis

	float dashTimer = 1.0f;			//dash timer
	float attackTimer = 0.0f;		//attack timer, inits with no cooldown
	float attackCooldown = 0.32f;	//attack cooldown value
	float deathTimer = 0.0f;
	float ShakeX = 0.0f;
	float ShakeY = 0.0f;
	float ShakeMagnitude = 0.0f;
	float cutsceneTimer = 0.0f;

	bool faceLeft = false, faceRight = true;	//paladin inits facing right
	bool prevState = false;						//prevents multiple keydown inputs in main loop
	bool PaladinHurt = false;
	bool PaladinAttack = false;
	bool PaladinDash = false;
	bool ToonShading = false;
	bool godMode = false;
	bool Knockback = true;
	bool Reflect = false;

	float DistDemonFireball = 0.0f;
	float DistPaladinDemon = 0;
	float DistPaladinDemon2 = 0;
	float DistPaladinFireballX = 0;
	float DistPaladinFireballY = 0;
	float DistPaladinFirePillar = 0;
	float PaladinHurtTimer = 0.0f;
	float PillarHurtTimer = 0.5f;

	//Lightning
	float lightningAmount = 1.0f;
	float lightningTimer = 0.0f;
	float lightningTime = 0.0f;

	// Demon
	float DemonHealth = 150;
	int DemonAttack = 0;
	float StabTimer = 0;
	float StompTimer = 0;
	float DemonTimer = 0;
	bool DemonHurt = false;
	float DemonPos = 9.0f;

	float BloodTimer = 0.0f;
	// Projectiles
	float FireballTimer = 0;
	float FirePillarCoolDown = 0;
	int fireballrandom = 2;
	vec3 FireballDir = vec3(0.0f, 0.0f, 0.0f);

	float FirePillarTimer = 0.0f;

	//Screen State
	float prevScreen = 0;
	float screen = 1;
	float optionsTimer;

	// States
	bool winAnim = false;
	bool loseAnim = false;

	// Keys //
	bool key_A = false;
	bool key_S = false;
	bool key_D = false;
	bool key_W = false;
	bool key_O = false;
	bool key_P = false;
	bool key_ESC = false;
	bool key_SPACE = false;
	bool prevStateAttack = false;


	bool Bloom = true;
	bool Normals = false;
	bool Positions = false;

	// LUT Toggles //
	float currentLUT = 0;

private:
	unsigned int VBO1 = GL_NONE;
	unsigned int VBO2 = GL_NONE;
	unsigned int VAO = GL_NONE;

	unsigned int program = GL_NONE;
	unsigned int vertShader = GL_NONE;
	unsigned int fragShader = GL_NONE;

	// Camera Values //
	Camera camera;
	vec3 camPosXYZ = vec3(0.0f, 5.0f, 20.0f);	//camera XYZ position vector
	float camPitch = 3.0f;						//X axis rotation angle
	float camYaw = 0.0f;						//Y axis rotation angle
	float camRoll = 0.0f;						//Z axis rotation angle
};