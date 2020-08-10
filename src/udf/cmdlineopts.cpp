// $Id: cmdlineopts.cpp,v 1.2 2003/05/23 16:28:38 takimoto Exp $
//===== cmdlineopts.cpp =====
//
//	ver.1.2		J.Takimoto
//

#ifdef __DECCXX
#define __USE_STD_IOSTREAM
#endif
#include "cmdlineopts.h"

//----- Constructor -----

CmdLineOpts::CmdLineOpts(int argc, const char* const argv[],
							const char* optstr)
{
	while(*optstr) {
		char optchar = *optstr++;
		if( *optstr == ':' ) {
			options[optchar] = OptEntry( true );
			optstr++;
		}
		else {
			options[optchar] = OptEntry( false );
		}
	}
	errflag = ! parse(argc, argv);
}

//----- Parse command line arguments -----

bool
CmdLineOpts::parse(int argc, const char* const argv[])
{
	//--- get command name from argv[0] ---

	cmdname = argv[0];
#ifdef _WIN32
	const char separator = '\\';
#else
	const char separator = '/';
#endif
	string::size_type pos = cmdname.rfind(separator);
	if( pos != string::npos ) {
		cmdname.erase(0,pos+1);
	}

	//--- process options ---

	for( argpos=1; argpos < argc; ++argpos ) {
		if(argv[argpos][0] != '-') {		// ordinary argument
			break;							// end of option
		}
		else {
			if( argv[argpos][1] == 0 ) {	// '-' only
				errmsg("bad option",argv[argpos]);
				return false;
			}
			if( argv[argpos][1] == '-' ) {	// "--"
				if( argv[argpos][2] ) {		// more chars after "--"
					errmsg("bad option",argv[argpos]);
					return false;
				}
				else {						// "--" alone
					++argpos;				// skip "--"
					break;					// end of option
				}
			}

			//--- valid option ? ---
			OptMap::iterator iter = options.find(argv[argpos][1]);
			if( iter == options.end() ) {	// not found
				errmsg("unknown option",argv[argpos]);
				return false;
			}

			(iter->second).isOn = true;

			//--- option arg ---
			if( (iter->second).hasArg ) {
				if( argv[argpos][2] ) {		// '-carg'
					(iter->second).arg = argv[argpos]+2;
				}
				else {						// '-c arg'
					if( argpos == argc-1 || argv[argpos+1][0] == '-') {
						errmsg("argument missing for option",argv[argpos]);
						return false;
					}
					(iter->second).arg = argv[++argpos];
				}
			}
			else {
				if( argv[argpos][2] ) {
					errmsg("extra argument for option",argv[argpos]);
					return false;
				}
			}
		} // end if
	} // end for

	return true;
}

//----- is this option on? ----

bool
CmdLineOpts::isOn(char c) const
{
	OptMap::const_iterator iter = options.find(c);
	if( iter == options.end() ) {
		return false;
	}
	else {
		return iter->second.isOn;
	}
}

//----- argument of this option -----

string
CmdLineOpts::arg(char c) const
{
	OptMap::const_iterator iter = options.find(c);
	if( iter == options.end() ) {
		return string("");;
	}
	else {
		return iter->second.arg;
	}
}

//----- save error message into errstr -----

void
CmdLineOpts::errmsg(const char* msg1, const char* msg2)
{
	errstr << cmdname << ": " << msg1 << ": " << msg2 << endl;
}
