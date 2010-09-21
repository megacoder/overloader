/*
 * vim: sw=8 ts=8
 */

#if	0
#define	__USE_GNU
#define	__GNU_SOURCE
#define	_USE_GNU
#endif	/* NOPE */

#define	USE_PROFILING	1		/* True if sprof(1) breaks	*/

#define	_GNU_SOURCE

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <fuse.h>

typedef	union	{
	void *	v;
	FILE *	(*f)( char const *, char const * );
} Foolie_t;

FILE *
fopen(
	char const *	fn,
	char const *	mode
)
{
	static Foolie_t	foo;
	FILE *		fyle;

	if( ! foo.f )	{
		foo.v = dlsym( RTLD_NEXT, "fopen" );
		if( ! foo.v )	{
			puts( "not found!" );
			exit( 1 );
		}
		printf( "Real routine is at %p.\n", foo.v );
	}
#if	USE_PROFILING
	fyle = DL_CALL_FCT( foo.f, ( fn, mode ) );
#else	/* USE_PROFILING */
	fyle = foo.f( fn, mode );
#endif	/* USE_PROFILING */
	printf( 
		"Your fopen( '%s' ) %s.\n",
		fn,
		fyle ? "succeeded" : "FAILED"
	);
	return( fyle );
}
