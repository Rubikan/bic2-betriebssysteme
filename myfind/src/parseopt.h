#ifndef PARSEOPT_H
#define PARSEOPT_H

typedef struct Options {
	// String-Variable die das Start-Directory speichert
	char* start_dir;
	// Integer-Variablen die speichern ob eine Aktion übergeben wurde
	int print;
	int ls;
	int nouser;
	int user;
	int name;
	int type;
	int path;
	// String-Variablen die Aktionsargumente speichern
	char* suser;
	char* sname;
	char* stype;
	char* spath;
} Options;

void parseopts(int argc, char* argv[], Options* options);

#endif
