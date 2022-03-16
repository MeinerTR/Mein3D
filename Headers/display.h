void HandleDisplay() {
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
   glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix

   glLoadIdentity();
   glTranslatef(_Camera.x, _Camera.y, _Camera.z);

	glfwSwapBuffers(Window); 
}