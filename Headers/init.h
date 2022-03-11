GLFWwindow* Window;
int Width, Height;
int AngleEX = 0, AngleEY = 0, AngleEZ = 3,
	AngleUX = 0, AngleUY = 1, AngleUZ = 0;

void Reshape(GLFWwindow* window, int width, int height)
{
	if (height == 0) height = 1;
	GLfloat Aspect = (GLfloat)width / (GLfloat)height;
	 
	glViewport(0, 0, width, height);
	 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, Aspect, 0.1f, 100.0f);
	glfwSetWindowSizeLimits(window, 640, 480, 
				GLFW_DONT_CARE, GLFW_DONT_CARE);
}

void HandleKeyboard()
{
    if (glfwGetKey(Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    	glfwSetWindowShouldClose(Window, true);
    if (glfwGetKey(Window, GLFW_KEY_W) == GLFW_PRESS)
    	CharacterZ += 0.1f;
    if (glfwGetKey(Window, GLFW_KEY_A) == GLFW_PRESS)
    	CharacterX += 0.1f;
    if (glfwGetKey(Window, GLFW_KEY_S) == GLFW_PRESS)
    	CharacterZ -= 0.1f;
    if (glfwGetKey(Window, GLFW_KEY_D) == GLFW_PRESS)
    	CharacterX -= 0.1f;
    glfwSwapBuffers(Window);
}

void InitWindow() {
	Width = std::stoi(INI("./settings.ini", 1));
	Height = std::stoi(INI("./settings.ini", 2));
  	Window = glfwCreateWindow(Width, Height, "Mein3D", NULL, NULL);
  	if (!Window)
  	{
    	glfwTerminate();
    	exit(EXIT_FAILURE);
 	}
    glfwMakeContextCurrent(Window);
    if (Height == 0) Height = 1;
	GLfloat Aspect = (GLfloat)Width / (GLfloat)Height;
	 
	glViewport(0, 0, Width, Height);
	 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, Aspect, 0.1f, 100.0f);
	glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void InitOpenGL() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);
   	glEnable(GL_DEPTH_TEST);
   	glDepthFunc(GL_LEQUAL);
   	glShadeModel(GL_SMOOTH);
   	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}