/*
TO DO:
	- particles issue
	- delta time issue
	- setup key class
	- remake 2d rendering system (Renderable/Sprite/Label as separate classes, not subclasses of Renderable2D)
	- font rendering
	- add to Window class check if key is pressed (do action once)
	- change ParticleGroup std::vector of variables to std::vector of pointers in GraphicsGraphicsScene3D class
	- check mipmapping
	- optimize 3d rendering with water (dont recalculate same things 3 times)
	- repair texture atlas rendering (for particles)
	- fog support in all shaders
	- add water rendering options (light reflection, scene reflection, fbos' resolutions, etc.)
	- change water reflection fbo resolution based on camera's distance from water
	- add possibility to add particle to the same particle group every frame

	+ make texture atlas support for 2D
	+ organize whole code
	+ improve model loading (check for repeating indices, then combine it into one if it's the same vertex)
	+ add rotating to 2D/3D groups (using matrices)
	+ add support for rendering closest lights when there are too many important lights
	+ 2d camera zooming in and out
	+ check if FrameBuffer class should have std::vector of texture ids

*/




/* INCLUDES */
// Normal Includes
#include <iostream>
#include <vector>

// Gumi Gota Engine Includes
#include "../../Gumi Gota/src/GumiGota.h"

// Header Includes
#include "WalkingCamera3D.h"



/* DEFINITIONS */
#define FPS_TEST false
#define FPS_TEST_LENGTH 60





#if 0
int main()
{
	using namespace gg;

	/* Window Setup */
	Window window("Gumi Gota Engine v0.0.1 - Tester", 1280, 720);
	//window.hideCursor();

	std::cout << "OpenGL version used: " << glGetString(GL_VERSION) << std::endl;




	/* TESTING STUFF */
	Sprite2D sprite(vector2(640.0f, 360.0f), vector2(200.0f, 200.0f), 0.0f);
	sprite.setColor(Color(0.6f, 1.0f, 0.1f));
	Texture texture1("Gumi Gota/Engine Tester/res/textures/logo.png");
	sprite.setTexture(&texture1);


	/* TEST 1 */
	Layer2D wr(window);

	Light2D light1(vector2(640.0f, 360.0f), Color(COLOR_WHITE), vector3(1.0f, 0.001f, 0.0001f));
	wr.addLight(&light1, true);
	Light2D light2(vector2(0.0f, 0.0f), Color(COLOR_RED), vector3(1.0f, 0.001f, 0.0001f));
	wr.addLight(&light2, true);
	Light2D light3(vector2(1280.0f, 0.0f), Color(COLOR_YELLOW), vector3(1.0f, 0.001f, 0.0001f));
	wr.addLight(&light3, true);
	Light2D light4(vector2(0.0f, 720.0f), Color(COLOR_BLUE), vector3(1.0f, 0.001f, 0.0001f));
	wr.addLight(&light4, true);
	Light2D light5(vector2(1280.0f, 720.0f), Color(COLOR_PURPLE), vector3(1.0f, 0.001f, 0.0001f));
	wr.addLight(&light5, true);
	
	/* TEST 2 */
	Sprite2D background(vector2(-2000.0f, -2000.0f), vector2(12000.0f, 9000.0f), 0.0f);
	background.setColor(Color(0.4f, 0.4f, 0.4f));
	Texture texture2("Gumi Gota/Engine Tester/res/textures/Pro Tlo.png");
	background.setTexture(&texture2);
	wr.addSprite(&background);

	Camera2D camera(vector2(640.0f, 360.0f), vector2(1280.0f, 720.0f));

	wr.addSprite(&sprite);


	const float squareSpeed = 0.3f;


	Timer fpsTimer; //used for fps calculating
	Timer secondTimer; //used for fps calculating

	/* APPLICATION LOOP */
	while (!window.closed())
	{
		/* Clearing */
		window.clear();

		/* Updating */
		wr.updateLights(camera);
		sprite.rotate(0.0004f);

		if (window.isKeyPressed(GLFW_KEY_W))
		{
			sprite.move(vector2(0.0f, squareSpeed));
			camera.move(vector2(0.0f, squareSpeed));
		}

		if (window.isKeyPressed(GLFW_KEY_S))
		{
			sprite.move(vector2(0.0f, -squareSpeed));
			camera.move(vector2(0.0f, -squareSpeed));
		}

		if (window.isKeyPressed(GLFW_KEY_A))
		{
			sprite.move(vector2(-squareSpeed, 0.0f));
			camera.move(vector2(-squareSpeed, 0.0f));
		}

		if (window.isKeyPressed(GLFW_KEY_D))
		{
			sprite.move(vector2(squareSpeed, 0.0f));
			camera.move(vector2(squareSpeed, 0.0f));
		}

		/* Rendering */
		wr.render(camera, true);

		/* Drawing */
		window.update();

		// FPS Calculations
		if (secondTimer.elapsed() >= 1.0f)
		{
			std::cout << "FPS: " << 1.0f / fpsTimer.elapsed() << std::endl; //fps calculating and printing
			secondTimer.reset();
		}

		fpsTimer.reset(); //used for fps calculating
		

	}


	return 0;
}
#endif

#if 1
int main()
{
	using namespace gg;
	using namespace rexer;

	/* Window Setup */
	Window window("Gumi Gota Engine v0.0.1 - Tester", 1920, 1080);
	window.hideCursor();

	LOG("OpenGL version: " << std::endl << glGetString(GL_VERSION) << std::endl);


	/* TEST STUFF */

	Font font("Gumi Gota/Engine Tester/res/fonts/test font.ttf", 20);



	Model model1 = loadModelFromFile("Gumi Gota/Engine Tester/res/models/monkey.obj", "Gumi Gota/Engine Tester/res/textures/wood texture.jpg");
	Renderable3D entity1(&model1, vector3(0.0f));
	Renderable3D entity2(&model1, vector3(1.5f, 2.0f, 0.0f));
	Renderable3D entity3(&model1, vector3(-1.5f, 2.0f, 0.0f));

	Model grassModel = loadModelFromFile("Gumi Gota/Engine Tester/res/models/grass.obj", "Gumi Gota/Engine Tester/res/textures/insane grass.png");
	Renderable3D grassEntity(&grassModel, vector3(-3.0f, 1.5f, 2.0f));
	grassModel.setHasFakeLighting(true);
	grassModel.setHasTransparency(true);
	grassEntity.setRotation(vector3(toRadians(-90.0f), 0.0f, 0.0f));

	Model metalModel = loadModelFromFile("Gumi Gota/Engine Tester/res/models/logo cube.obj", "Gumi Gota/Engine Tester/res/textures/MetalPlate/Metal_plate_006_COLOR.jpg");
	Renderable3D metalEntity(&metalModel, vector3(4.0, 10.0f, -1.0f));

	Model taModel = loadModelFromFile("Gumi Gota/Engine Tester/res/models/logo cube.obj", "Gumi Gota/Engine Tester/res/textures/best texture atlas ever.png");
	taModel.setTextureRows(2);
	Renderable3D taEntity(&taModel, vector3(10.0, 2.0f, 4.0f));
	taEntity.setTextureAtlasIndex(3);

	Model donutModel = loadModelFromFile("Gumi Gota/Engine Tester/res/models/Wooden Donut Model.obj", "Gumi Gota/Engine Tester/res/textures/MetalPlate/Metal_plate_006_COLOR.jpg");
	Renderable3D donutEntity(&donutModel, vector3(-5.0, 3.0f, 16.0f));

	Model groundModel = loadModelFromFile("Gumi Gota/Engine Tester/res/models/logo cube.obj", "Gumi Gota/Engine Tester/res/textures/MetalPlate/Metal_plate_006_COLOR.jpg");
	Renderable3D groundEntity(&groundModel, vector3(0.0, -34.0f, 0.0f));
	groundEntity.setScale(32.0f);

	Model simpleLampModel = loadModelFromFile("Gumi Gota/Engine Tester/res/models/simple light model.obj", "Gumi Gota/Engine Tester/res/textures/simple lamp texture.png");
	Renderable3D simpleLampEntity(&simpleLampModel, vector3(8.0, 4.0f, 8.0f));
	Light3D simpleLampLight(simpleLampEntity.getPosition(), COLOR_GREEN, vector3(1.0f, 0.01f, 0.005f));

	Model bigDonutModel = loadModelFromFile("Gumi Gota/Engine Tester/res/models/Wooden Donut Model.obj", "Gumi Gota/Engine Tester/res/textures/MetalPlate/Metal_plate_006_COLOR.jpg");
	Renderable3D bigDonutEntity(&bigDonutModel, vector3(-4.0, -5.0f, 4.0f));
	bigDonutEntity.setScale(36.0f);


	Light3D moon(vector3(-400000.0f, 250000.0f, -50000.0f), vector3(0.855f / 1.4f, 0.969f / 1.2f, 1.0f), vector3(1.0f, 0.0f, 0.0f));


	WalkingCamera3D cam(vector3(2.5f, 2.5f, 6.0f), window.getAspectRatio(), &window);
	cam.setFOV(toRadians(90.0f));
	cam.setPitch(toRadians(-4.0f));
	cam.setYaw(toRadians(30.0f));

	CubeMap skybox(
		"Gumi Gota/Engine Tester/res/textures/hw_desertnight/desert_night_up.tga",
		"Gumi Gota/Engine Tester/res/textures/hw_desertnight/desert_night_dn.tga",
		"Gumi Gota/Engine Tester/res/textures/hw_desertnight/desert_night_lf.tga",
		"Gumi Gota/Engine Tester/res/textures/hw_desertnight/desert_night_rt.tga",
		"Gumi Gota/Engine Tester/res/textures/hw_desertnight/desert_night_ft.tga",
		"Gumi Gota/Engine Tester/res/textures/hw_desertnight/desert_night_bk.tga"
	);


	Texture particleTexture1("Gumi Gota/Engine Tester/res/textures/particle texture atlas 2.png", 4, LINEAR, CLAMP_TO_EDGE);
	Texture particleTexture2("Gumi Gota/Engine Tester/res/textures/particle texture atlas.png", 8, LINEAR, CLAMP_TO_EDGE);
	Texture particleTexture3("Gumi Gota/Engine Tester/res/textures/particle1.png", LINEAR, CLAMP_TO_EDGE);
	
	DirectionParticleSystem ps1(vector3(0.0f, 2400.0f, 0.0f), &particleTexture1);
	ps1.setUsingAdditiveBlending(true);
	ps1.setGravity(480000.0f);
	ps1.setLifetime(3.0f);
	ps1.setLifetimeError(48.0f);
	ps1.setDirectionError(vector3(2400000.0f, 240.0f, 2400000.0f));

	DirectionParticleSystem ps2(vector3(0.0f, 4000.0f, 0.0f), &particleTexture2);
	ps2.setEndingTextureAtlasIndex(31);
	ps2.setGravity(480000.0f);
	ps2.setLifetime(3.0f);
	ps2.setLifetimeError(0.3f);
	ps2.setDirectionError(vector3(2400000.0f, 240.0f, 2400000.0f));

	SpreadParticleSystem ps3(&particleTexture3);
	ps3.setUsingAdditiveBlending(true);
	ps3.setScale(0.3f);
	ps3.setSpeed(60.0f);
	ps3.setSpeedError(120.0f);
	ps3.setLifetime(3.0f);


	WaterTile myWater(vector3(0.0f, 0.0f, 0.0f), 32.0f);
	myWater.setTilingFactor(2.0f);
	myWater.setWaveStrength(0.1f);

	float waterSpeed = 0.0002f;


	Renderer3D rr;
	rr.setSkyColor(Color(0.098f, 0.149f, 0.271f), window);

	rr.addRenderable(&entity1);
	rr.addRenderable(&entity2);
	rr.addRenderable(&entity3);
	rr.addRenderable(&grassEntity);
	rr.addRenderable(&metalEntity);
	rr.addRenderable(&taEntity);
	rr.addRenderable(&donutEntity);
	rr.addRenderable(&groundEntity);
	rr.addRenderable(&simpleLampEntity);
	rr.addRenderable(&bigDonutEntity);

	rr.addLight(&moon, true);
	rr.addLight(&simpleLampLight);
	rr.setSkybox(&skybox);
	rr.addWaterTile(&myWater);

	rr.reserveParticleGroups(300);


	PhysicsScene3D physicsScene;
	physicsScene.addCamera(&cam);


	Layer2D textLayer(window);
	Font testFont("Gumi Gota/Engine Tester/res/fonts/test font.ttf", 128.0f);
	Label2D testText("text", vector2(400.0f, 400.0f), vector2(500.0f, 500.0f), &testFont);
	textLayer.addLabel(&testText);






	Timer fpsTimer; //used for fps calculating
	Timer secondTimer; //used for fps calculating

	bool clickedR = false;
	bool clickedE = false;

	float totalFPS = 0.0f;
	unsigned int fpsSeconds = 0;


	Timer deltaTimeTimer;

	/* APPLICATION LOOP */
	while (!window.closed())
	{
		fpsTimer.reset(); //used for fps calculating

		/* Clearing */
		window.clear();

		/* Updating */
		float deltaTime = deltaTimeTimer.elapsed();


		physicsScene.update(deltaTime);

		///rr.updateLights(cam.getPosition());
		grassEntity.rotate(vector3(0.0f, 0.0f, 0.001f));

		// Input Handling
		{
			// Quit Control
			if (window.isKeyPressed(GLFW_KEY_ESCAPE))
			{
				window.close();
			}

			// Particle Controls
			if (window.isKeyPressed(GLFW_KEY_R))
			{
				if (!clickedR)
				{
					rr.addParticleGroup(ps2.generateParticles(donutEntity.getPosition(), 100));

					clickedR = true;
				}
			}
			else
			{
				clickedR = false;
			}

			if (window.isKeyPressed(GLFW_KEY_E))
			{
				if (!clickedE)
				{
					rr.addParticleGroup(ps1.generateParticles(donutEntity.getPosition(), 100));

					clickedE = true;
				}
			}
			else
			{
				clickedE = false;
			}

			// Water FX Controls
			if (window.isKeyPressed(GLFW_KEY_F))
			{
				waterSpeed += 0.000001f;
			}

			if (window.isKeyPressed(GLFW_KEY_G))
			{
				waterSpeed -= 0.000001f;
			}

			if (window.isButtonPressed(GLFW_MOUSE_BUTTON_1))
			{
				myWater.setWaveStrength(myWater.getWaveStrength() + 0.002f);
			}

			if (window.isButtonPressed(GLFW_MOUSE_BUTTON_2))
			{
				myWater.setWaveStrength(myWater.getWaveStrength() - 0.002f);
			}

			if (window.isButtonPressed(GLFW_MOUSE_BUTTON_4))
			{
				myWater.setTilingFactor(myWater.getTilingFactor() - 0.005f);
			}

			if (window.isButtonPressed(GLFW_MOUSE_BUTTON_5))
			{
				myWater.setTilingFactor(myWater.getTilingFactor() + 0.005f);
			}


			if (window.isKeyPressed(GLFW_KEY_T))
			{
				physicsScene.explosion(vector3(0.0f), vector3(1.0f, 0.01f, 0.001f));
			}
		}
		

		
		rr.addParticleGroup(ps3.generateParticles(metalEntity.getPosition(), 1));
		
		

		rr.update(cam, deltaTime);

		myWater.addMovementFactor(waterSpeed);

		/* Rendering */
		rr.render(cam);
		textLayer.render();

		/* Drawing */
		window.update();

		// FPS Calculations
		if (secondTimer.elapsed() >= 1.0f)
		{
			float fps = 1.0f / fpsTimer.elapsed();
			///std::cout << "[Info] FPS: " << fps << std::endl; //fps calculating and printing
			secondTimer.reset();

			if (FPS_TEST && fpsSeconds < FPS_TEST_LENGTH)
			{
				totalFPS += fps;

				fpsSeconds++;

				float averageFPS = totalFPS / fpsSeconds;
				std::cout << "[Info] FPS Test - Average FPS: " << averageFPS << std::endl;
			}
			else if (FPS_TEST && fpsSeconds == FPS_TEST_LENGTH)
			{
				float averageFPS = totalFPS / fpsSeconds;
				std::cout << "[Info] FPS Test - Final Average FPS: " << averageFPS << std::endl;
				system("pause");
			}
		}


		deltaTimeTimer.reset();

	}


	return 0;
}
#endif