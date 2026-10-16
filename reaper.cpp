#include <sys/types.h>
#include <sys/prctl.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#if !defined( PR_SET_CHILD_SUBREAPER )
#define PR_SET_CHILD_SUBREAPER 36
#endif

int main( int argc, char **argv )
{
	int sub_command_argc = 0;

	for ( int i = 0; i < argc; i++ )
	{
		if ( strcmp( "--", argv[ i ] ) == 0 && i + 1 < argc )
		{
			sub_command_argc = i + 1;
			break;
		}
	}

	if ( sub_command_argc == 0 )
	{
		fprintf( stderr, "reaper: no sub-command!\n" );
		exit( 1 );
	}

	// (Don't Lose) The Children
	if ( prctl( PR_SET_CHILD_SUBREAPER, 1, 0, 0, 0 ) == -1 )
	{
		fprintf( stderr, "reaper: prctl() failed: %s\n", strerror( errno ) );
		exit( 1 );
	}

	pid_t pid = fork();

	if ( pid == -1 )
	{
		fprintf( stderr, "reaper: fork() failed: %s\n", strerror( errno ) );
		exit( 1 );
	}

	// Are we in the child?
	if ( pid == 0 )
	{
		execvp( argv[ sub_command_argc ], &argv[ sub_command_argc ] );
		// If we get here, then execvp() must have failed
		fprintf( stderr, "reaper: execvp(%s) failed: %s\n", argv[ sub_command_argc ], strerror( errno ) );
		// Avoid atexit handlers because we're in a child process now
		_exit( 1 );
	}

	pid_t wait_ret;
	int child_status;
	bool child_failed = false;
	while( true )
	{
		wait_ret = wait( &child_status );

		if ( child_status != 0 )
		{
			child_failed = true;
		}

		if ( wait_ret == -1 && errno == ECHILD )
		{
			// No more children.
			break;
		}
	}

	if ( child_failed )
	{
		exit ( 1 );
	} else {
		exit ( 0 );
	}
}
