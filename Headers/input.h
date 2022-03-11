float CharacterX = 0.0f, CharacterY = 0.0f, CharacterZ = 0.0f;

std::string Split(std::string String, const char *Character) {
	std::string Output = ""; char Char;
	bool Done = 0, Equal = 0; int CharPos = 0;
	for (int Idx = 0; Idx < String.length() + 1; Idx++) {
		Char = String[Idx]; if (Done) {Output += Char;} else {
			if (Equal) {CharPos++; if (Char == Character[CharPos]) {
					if (CharPos == sizeof(Character) / sizeof(char *)) {Done = 1;}} else {
						CharPos = 0; Equal = 0;}}
			else {if (Char == Character[0]) {Equal = 1;}}
		}} if (Equal) {Output += String[String.length()];} return Output; }

std::string INI(const char *Path, const int Idx_) {
	std::string Output = ""; int _Idx = 0;
	FILE *File = fopen(Path, "r");
	if (File == NULL) {
		Error("Unable to open './settings.ini' file!");
	} else { std::string Line; 
		char Char = 0; while (Char != -2) {
			Char = fgetc(File);
			if (Char == '\n' | Char == -1) { if (Char == -1) {Char = -2;}
				if (Line[0] != '[' && Line[0] != '#') {_Idx++; if (_Idx == Idx_) {
						Output += Split(Line, ": ");
						printf("Output: %s\n", Output.c_str());
				} } Line.clear();
			} else {Line += Char;}
		} } fclose(File);
	return Output;}