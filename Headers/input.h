#if defined(_MSC_VER)
    #include <direct.h>
    #define getcwd _getcwd
#elif defined(__GNUC__)
    #include <unistd.h>
#endif

int Width, Height; char *CWD;
glm::vec3 _Camera = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 Camera_ = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 Cam_era = glm::vec3(0.0f, 1.0f, 0.0f);
bool FirstCalled = true;
float Yaw = -90.0f;
float Pitch = 0.0f;
float LastX, LastY;
float Fov =  45.0f;
float DeltaTime = 0.0f;
float LastFrame = 0.0f;

std::string Merged(const char *A, const char *B) {
	std::string Output = ""; Output += A; Output += B; return Output; }

std::string Split(std::string String, const char *MagicWord, const int WhichOne) {
	std::string Output = ""; char Char; bool Getting = 0, Checking = 0; int Pops = 0;
	for (int Idx = 0; Idx < String.length() + 1; Idx++) {
		Char = String[Idx]; if (Getting) {Pops++; if (Pops == 1) {
		if (Char != ' ') {Output += Char;}} else {Output += Char;}
	} else {if (Checking) {Pops++; if (Char == MagicWord[Pops]) {
		if (Pops == sizeof(MagicWord) / sizeof(char *)) {
			Getting = 1; Pops = 0;}} else {Checking = 0; Pops = 0;}} else {
			if (Char == MagicWord[0]) {Checking = 1;}
	}}
} return Output;}

std::string INI(std::string Path, const char *Class, const int WhichOne) {
	std::string Output = "", Word = ""; int CurrentOne = -1;
	FILE *File = fopen(Path.c_str(), "r");
	if (File == NULL) {Error("Unable to open './settings.ini'!", 0);} 
	else {char Char; while (Char != EOF) {Char = fgetc(File);
		if (Char == '\n' | Char == EOF) {if (Word[0] != ' ' && Word[0] != '[') {
			CurrentOne++;} if (WhichOne == CurrentOne) {
				Output += Split(Word, ": ", 1); break;} 
			Word = ""; } else {Word += Char;}}} fclose(File); return Output;}