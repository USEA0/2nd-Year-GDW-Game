#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <iostream>
#include "Game.h"

const int FRAME_DELAY_SPRITE = 1000 / FRAMES_PER_SECOND;

Game *theGame;


/* function DisplayCallbackFunction(void)
 * Description:
 *  - this is the openGL display routine
 *  - this draws the sprites appropriately
 */
void DisplayCallbackFunction(void) {
	theGame->draw();
}

/* function void KeyboardCallbackFunction(unsigned char, int, int)
 * Description:
 *   - this handles keyboard input when a button is pressed
 */
void KeyboardCallbackFunction(unsigned char key, int x, int y) {
	theGame->keyboardDown(key, x, y);
}
/* function void KeyboardUpCallbackFunction(unsigned char, int, int)
 * Description:
 *   - this handles keyboard input when a button is lifted
 */
void SpecialCallbackFunction(int key, int x, int y)
{
	theGame->keyboardSpecialDown(key, x, y);
}

void KeyboardUpCallbackFunction(unsigned char key, int x, int y) {
	theGame->keyboardUp(key, x, y);
}

/* function TimerCallbackFunction(int value)
 * Description: 
 *  - this is called many times per second
 *  - this enables you to animate things
 *  - no drawing, just changing the state
 *  - changes the frame number and calls for a redisplay
 *  - FRAME_DELAY_SPRITE is the number of milliseconds to wait before calling the timer again
 */
void TimerCallbackFunction(int value) {
	theGame->update();
	glutPostRedisplay();
	glutTimerFunc(FRAME_DELAY_SPRITE, TimerCallbackFunction, 0);
}

void MouseClickCallbackFunction(int button, int state, int x, int y) {
	theGame->mouseClicked(button,state, x, y);
	glutPostRedisplay();
}

/* function MouseMotionCallbackFunction()
 * Description:
 *   - this is called when the mouse is clicked and moves
 */
void MouseMotionCallbackFunction(int x, int y) {
	theGame->mouseMoved(x, y);
	glutPostRedisplay();
}

void CALLBACK OpenGLDebugCallback(
	GLenum source, GLenum type, GLuint id, GLenum severity,
	GLsizei length, const GLchar *msg, const void *data)
{
	std::cout << "CALLBACK\n";
	char buffer[9] = { '\0' };
	sprintf(buffer, "%.8x", id);

	std::string message("OpenGL(0x");
	message += buffer;
	message += "): ";

	switch (type) {
	case GL_DEBUG_TYPE_ERROR:
		message += "Error";
		break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
			 message += "Deprecated behavior";
			 break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
			 message += "Undefined behavior";
			 break;
	case GL_DEBUG_TYPE_PORTABILITY:
			 message += "Portability issue";
			 break;
	case GL_DEBUG_TYPE_MARKER:
			 message += "Stream annotation";
			 break;
	case GL_DEBUG_TYPE_OTHER_ARB:
	default:
		message += "Other";
	}

	message += "\nSource: ";
	switch (source) {
	case GL_DEBUG_SOURCE_API:
		message += "API";
		break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
		message += "Window system";
		break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER:
		message += "Shader compiler";
		break;
	case GL_DEBUG_SOURCE_THIRD_PARTY:
		message += "Third party";
		break;
	case GL_DEBUG_SOURCE_APPLICATION:
		message += "Application";
		break;
	case GL_DEBUG_SOURCE_OTHER:
	default:
		message += "Other";
	}

		message += "\nSeverity: ";
		switch (severity) {
		case GL_DEBUG_SEVERITY_HIGH:
			message += "High";
			break;
		case GL_DEBUG_SEVERITY_MEDIUM:
			message += "Medium";
			break;
		case GL_DEBUG_SEVERITY_LOW:
			message += "Low";
			break;
		case GL_DEBUG_SEVERITY_NOTIFICATION:
			message += "Notification";
			break;
		default:
			message += "Unknown";
		}

	message += "\n";
	message += msg;
	message += "\n";

	if (type == GL_DEBUG_TYPE_ERROR)
		std::cout << "ERROR: " << message << std::endl;
	else
		std::cout << message << std::endl;
}


void InitOpenGLDebugCallback()
{
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE | GLUT_DEBUG);
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(OpenGLDebugCallback, NULL);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);
}


int main(int argc, char **argv)
{
	/* initialize the window and OpenGL properly */
	glutInit(&argc, argv);
	glutInitContextVersion(4, 2);
	glutInitContextFlags(GLUT_CORE_PROFILE);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutCreateWindow("Demon Slayer");

	glewExperimental = true;

	if (glewInit() != GLEW_OK) {
		std::cout << "GLEW could not be initialized.\n";
		system("pause");
		return 0;
	}

	//glewInit();
	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

	// set up our function callbacks //
	glutDisplayFunc(DisplayCallbackFunction);
	glutKeyboardFunc(KeyboardCallbackFunction);
	glutKeyboardUpFunc(KeyboardUpCallbackFunction);
	glutSpecialFunc(SpecialCallbackFunction);
	glutMouseFunc(MouseClickCallbackFunction);
	glutMotionFunc(MouseMotionCallbackFunction);
	glutTimerFunc(1, TimerCallbackFunction, 0);

	// set fullscreen //
	glutFullScreen();


#ifdef _DEBUG
	InitOpenGLDebugCallback();
#endif

	// init game //
	theGame = new Game();
	theGame->initializeGame();

	// start game //
	glutMainLoop();
	return 0;
}