// clang --target=wasm32 -nostdlib -Wl,--no-entry -Wl,--export-all howold2.c -o howold.wasm

int howOld( int currentYear, int yearBorn )
{
	int retValue = -1;

	if ( yearBorn <= currentYear )
	{
		retValue = currentYear - yearBorn;
	}

	return(retValue);
}