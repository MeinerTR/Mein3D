GLFWwindow* Window; int Width, Height;
float Yaw   = -90.0f;
float Pitch =  0.0f;
float LastX; float LastY;
float DeltaTime = 0.0f;
float LastFrame = 0.0f;
bool FirstCalled = true;

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

void HandleMouse(GLFWwindow* window, double MouseX, double MouseY) {
	float PosX = static_cast<float>(MouseX);
    float PosY = static_cast<float>(MouseY);
    if (FirstCalled) {
	    LastX = PosX;
	    LastY = PosY;
	    FirstCalled = false;   } 
	float OffsetX = PosX - LastX;
	float OffsetY = LastY - PosY;
	LastX = PosX; LastY = PosY;

	float Sensitivity = 0.1f;
	OffsetX *= Sensitivity;
	OffsetY *= Sensitivity;

	Yaw += OffsetX; Pitch += OffsetY;

	if (Pitch > 89.0f)
	    Pitch = 89.0f;
	if (Pitch < -89.0f)
	    Pitch = -89.0f;

	glm::vec3 Front;
	Front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	Front.y = sin(glm::radians(Pitch));
	Front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	CameraP = glm::normalize(Front);
}

void HandleKeyboard() {
    if (glfwGetKey(Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    	glfwSetWindowShouldClose(Window, true);

    float CameraS = static_cast<float>(2.5 * DeltaTime);
    if (glfwGetKey(Window, GLFW_KEY_W) == GLFW_PRESS) {
    	CameraP += CameraS * CameraP;}
    if (glfwGetKey(Window, GLFW_KEY_S) == GLFW_PRESS) {
    	CameraP -= CameraS * CameraP;}
    if (glfwGetKey(Window, GLFW_KEY_A) == GLFW_PRESS) {
    	CameraP -= glm::normalize(glm::cross(CameraF, CameraU)) * CameraS;}
    if (glfwGetKey(Window, GLFW_KEY_D) == GLFW_PRESS) {
    	CameraP += glm::normalize(glm::cross(CameraF, CameraU)) * CameraS;}
    glfwSwapBuffers(Window);
}

void InitWindow() {
	Width = std::stoi(INI("./settings.ini", 1));
	Height = std::stoi(INI("./settings.ini", 2));
  	Window = glfwCreateWindow(Width, Height, "Mein3D", NULL, NULL);
  	if (!Window){
    	glfwTerminate();
    	exit(EXIT_FAILURE);
 	} LastX = (float) Width / 2.0; LastY = (float) Height / 2.0;

    glfwMakeContextCurrent(Window);
    if (Height == 0) Height = 1;
	GLfloat Aspect = (GLfloat)Width / (GLfloat)Height;
	 
	glViewport(0, 0, Width, Height);
	 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, Aspect, 0.1f, 100.0f);

	glfwSetCursorPosCallback(Window, HandleMouse);  
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