#include "parseopt.h"

/**
 * \brief Parses the argv[] into a linked list of options.
 *
 * \param argc The number of arguments
 * \param argv The arguments itselves (including the program name in argv[0])
 * \param first Pointer to an option (the first option in the list)
 *
 * \return void
 */
 
void parseopts(int argc, char* argv[], OptionsPart* first) {
	int i = (strncmp(".", argv[1], 1) == 0 || strncmp("/", argv[1], 1) == 0) ? 2 : 1;
	Option* current = NULL;
	OptionsPart* currentOP=first;
	int isPrint=1;
	
	inizializeOptionsPart(&currentOP);
	current=currentOP->first;
	

	for (; i < argc; i++) {
		if (strcmp("-user", argv[i]) == 0) {
			if(current==NULL){				
				current = create_option("-user", argv[++i]);
			}else{
				current->next=create_option("-user", argv[++i]);
				current = current->next;
			}			
			if(currentOP->first==NULL){
				currentOP->first=current;
			}
		}
		else if (strcmp("-name", argv[i]) == 0) {
			if(current==NULL){				
				current = create_option("-name", argv[++i]);
			}else{
				current->next = create_option("-name", argv[++i]);
				current = current->next;
			}			
			if(currentOP->first==NULL){
				currentOP->first=current;
			}
		}
		else if (strcmp("-type", argv[i]) == 0) {
			if(current==NULL){				
				current = create_option("-type", argv[++i]);
			}else{
				current->next = create_option("-type", argv[++i]);
				current = current->next;
			}			
			if(currentOP->first==NULL){
				currentOP->first=current;
			}
		}
		else if (strcmp("-path", argv[i]) == 0) {
			if(current==NULL){		
				current = create_option("-path", argv[++i]);
			}else{		
				current->next = create_option("-path", argv[++i]);
				current = current->next;
			}			
			if(currentOP->first==NULL){
				currentOP->first=current;
			}
		}
		else if (strcmp("-print", argv[i]) == 0) {
			if(current==NULL){		
				current = create_option("-print", NULL);
			}else{		
				current->next = create_option("-print", NULL);
				current = current->next;
			}			
			if(currentOP->first==NULL){
				currentOP->first=current;
			}
			current=NULL;
			isPrint=0;
			currentOP->next= create_OptionsPart();
			currentOP=currentOP->next
			inizializeOptionsPart(currentOP);
		}
		else if (strcmp("-ls", argv[i]) == 0) {
			if(current==NULL){		
				current = create_option("-ls", NULL);
			}else{		
				current->next = create_option("-ls", NULL);
				current = current->next;
			}			
			if(currentOP->first==NULL){
				currentOP->first=current;
			}
			current = NULL;
			isPrint=0;
			currentOP->next= create_OptionsPart();
			currentOP=currentOP->next
			inizializeOptionsPart(currentOP);
		}
		else if (strcmp("-nouser", argv[i]) == 0) {
			if(current==NULL){		
				current=create_option("-nouser", NULL);
			}else{		
				current->next = create_option("-nouser", NULL);
				current = current->next;
			}			
			if(currentOP->first==NULL){
				currentOP->first=current;
			}
		}
		else {
			printf("%s ist keine gueltige Aktion!", argv[i]);
		}
	}
}

void inizializeOptionsPart(OptionsPart* current){
	current = (OptionsPart *) malloc(sizeof(OptionsPart));
	current->first=NULL;
	current->next=NULL;
}

OptionsPart* create_OptionsPart() {
	OptionsPart* option;

	current = (OptionsPart *) malloc(sizeof(OptionsPart));
	current->first=create_option;
	current->next=NULL;

	return option;
}

Option* create_option(char* optionname, char* argument) {
	Option* option;

	option = (Option *) malloc(sizeof(Option));
	option->name = optionname;
	option->argument = argument;
	option->next = NULL;

	return option;
}
