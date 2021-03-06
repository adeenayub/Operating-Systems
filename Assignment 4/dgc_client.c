/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "dgc.h"


void
digitscompute_prog_1(char *host)
{
	CLIENT *clnt;
	int  *result_1;
	char * printsum_1_arg;

#ifndef	DEBUG
	clnt = clnt_create (host, DIGITSCOMPUTE_PROG, DIGITSCOMPUTE_VERS, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

	result_1 = printsum_1(&printsum_1_arg, clnt);
	if (result_1 == (int *) NULL) {
		clnt_perror (clnt, "call failed");
	}
#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}


int
main (int argc, char *argv[])
{
	char *host;

	if (argc < 2) {
		printf ("usage: %s server_host\n", argv[0]);
		exit (1);
	}
	host = argv[1];
	digitscompute_prog_1 (host);
exit (0);
}
