#include <cstdio>
#include <cstdlib>
#define STL_USING_STRING
#include "stl.h"


bool findFile(char* root, char* filename)
{
	FILE* fp;
	char buf[1024];
	char temp[1024];
	bool foundFile = false;
	
	// Dir parameters:
	//	/B no heading information or summary
	//	/A:-h-d no hidden files or directories will be displayed
	//  /A:-hd  no hidden files will be displayed.  Display directories.
	string dirCommand1 = "dir /B /A:-h-d ";
	string dirCommand2 = "dir /B /A:-hd ";

	dirCommand1 += root;
	dirCommand2 += root;
	
	// Check non directory files to see if they match
	fp = _popen(dirCommand1.c_str(), "r");

	if(fp) {

		while(fscanf(fp, "%s", buf) != EOF) {
			// Have we found a match?
			if(!strcmp(buf, filename)) {
				// Yes, we have.
				sprintf(root, "%s\\%s", root, filename);
				return true;
			}
		}
	}
	_pclose(fp);

	fp = _popen(dirCommand2.c_str(), "r");

	if(fp) {
		memset(buf, 0, sizeof(buf));
		
		// Check each directory recursively to see if the file
		// resides in one of the subdirectories
		while(fscanf(fp, "%s", buf) != EOF) {
			strcpy(temp, root);
			sprintf(root, "%s\\%s", root, buf);
			foundFile = findFile(root, filename);
			if(foundFile) {
				return true;
			}

			foundFile = false;
			strcpy(root, temp);
		}
	}
	_pclose(fp);
	
	return false;
}