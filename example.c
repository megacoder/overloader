/*
 * vim: sw=8 ts=8
 */

#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int
main(
	int		argc,
	char * *	argv
)
{
	FILE *		fyle;

	puts( "About to call fopen(3)" );
	fyle = fopen( "/no/such/file", "r" );
	if( fyle )	{
		perror( "WTF?" );
		exit( 1 );
	}
	puts( "Correctly did not access missing file." );
	fyle = fopen( "/dev/null", "r" );
	if( !fyle )	{
		perror( "fopen(3)" );
		exit( 1 );
	}
	puts( "Correctly opened file '/dev/null'." );
	fclose( fyle );
	return( 0 );
}
