GLFWwindow* Window; int Width, Height;
float yaw   = -90.0f;
float pitch =  0.0f;
float lastX =  1280.0f / 2.0;
float lastY =  768.0f / 2.0;
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
	float xpos = static_cast<float>(MouseX);
    float ypos = static_cast<float>(MouseY);
    if (FirstCalled) {
	    lastX = xpos;
	    lastY = ypos;
	    FirstCalled = false;
	} 
	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.1f; // change this value to your liking
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	// make sure that when pitch is out of bounds, screen doesn't get flipped
	if (pitch > 89.0f)
	    pitch = 89.0f;
	if (pitch < -89.0f)
	    pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	CameraP = glm::normalize(front);
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