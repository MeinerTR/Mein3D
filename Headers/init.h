void Reshape(GLFWwindow* _Window, const int _Width, int _Height) {glViewport(0, 0, _Width, _Height);}

void HandleKeyboard() {
	if (glfwGetKey(Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(Window, true);

    float Camera__ = static_cast<float>(2.5 * DeltaTime);
    if (glfwGetKey(Window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {Camera__ += 0.3;}
    
    if (glfwGetKey(Window, GLFW_KEY_W) == GLFW_PRESS)
        _Camera += Camera__ * Camera_;
    if (glfwGetKey(Window, GLFW_KEY_S) == GLFW_PRESS)
        _Camera -= Camera__ * Camera_;
    if (glfwGetKey(Window, GLFW_KEY_A) == GLFW_PRESS)
        _Camera -= glm::normalize(glm::cross(Camera_, Cam_era)) * Camera__;
    if (glfwGetKey(Window, GLFW_KEY_D) == GLFW_PRESS)
        _Camera += glm::normalize(glm::cross(Camera_, Cam_era)) * Camera__;
}

void HandleMouseScrool(GLFWwindow* window, const double OffsetX, const double OffsetY) {
    Fov -= (float) OffsetY;
    if (Fov < 1.0f) {Fov = 1.0f;}
    if (Fov > 45.0f) {Fov = 45.0f;}
}

void HandleMouse(GLFWwindow *_Window,  double MouseX,  double MouseY) {
	float PosX = static_cast<float>(MouseX);
    float PosY = static_cast<float>(MouseY);

    if (FirstCalled) {
        LastX = PosX; LastY = PosY;
        FirstCalled = false;      }

    float OffsetX = PosX - LastX;
    float OffsetY = LastY - PosY;
    LastX = PosX; LastY = PosY;
    float Sensitivity = 0.1f; // change this value to your liking
    OffsetX *= Sensitivity;
    OffsetY *= Sensitivity;
	Yaw += OffsetX; Pitch += OffsetY;
    if (Pitch > 89.0f) {Pitch = 89.0f;}
    if (Pitch < -89.0f) {Pitch = -89.0f;} 
    glm::vec3 Front;
    Front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front.y = sin(glm::radians(Pitch));
    Front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Camera_ = glm::normalize(Front);
}

void InitMein3D() {
	// try { Width = std::stoi(INI(Merged(CWD, "/settings.ini"), "Window", 0));
	// } catch (const std::invalid_argument & e) {
	// 	std::cout << CWD << "/settings.ini -> Width -> Invalid_Argument!" << std::endl;
	// 	Width = 1280; }
	// try { Height = std::stoi(INI(Merged(CWD, "/settings.ini"), "Window", 1));
	// } catch (const std::invalid_argument & e) {
	// 	std::cout << CWD << "/settings.ini -> Height -> Invalid_Argument!" << std::endl;
	// 	Height = 768; }
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	#ifdef __APPLE__ 
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	#endif

	Window = glfwCreateWindow(Width, Height, "Mein3D", NULL, NULL);
	glfwMakeContextCurrent(Window); if (!Window) {Error("Unable to create GLFW3 window!", 0);}
	glfwSetWindowSizeLimits(Window, 640, 480, GLFW_DONT_CARE, GLFW_DONT_CARE);
}

void InitOpenGL() {
	if ((CWD = getcwd(NULL, 0)) == NULL) {Error("Failed to get current directory!", 0);}
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {Error("Unable to init GLAD!", 1);}
	glViewport(0, 0, Width, Height); glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f); glEnable(GL_DEPTH_TEST); glDepthFunc(GL_LEQUAL);
   	glShadeModel(GL_SMOOTH); glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
   	glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}
