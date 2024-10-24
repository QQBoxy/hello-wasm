// emcc howold.c -o howold.wasm -s STANDALONE_WASM -s --no-entry
#include <emscripten.h>

EMSCRIPTEN_KEEPALIVE
int howOld( int currentYear, int yearBorn )
{
	int retValue = -1;

	if ( yearBorn <= currentYear )
	{
		retValue = currentYear - yearBorn;
	}

	return(retValue);
}