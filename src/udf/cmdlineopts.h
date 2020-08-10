#ifndef _CMDLINEOPTS_H_
#define _CMDLINEOPTS_H_
// $Id: cmdlineopts.h,v 1.5 2003/05/30 07:56:56 takimoto Exp $
/*========================================================================

	class CmdLineOpts - analyze command line options

	Public methods:

		CmdLineOpts(int argc, const char* const argv[],
						char* optstr);	// constructor

		bool isOn(char optchar);		// is this option set?
		string arg(char optchar);		// argument of this option

		int nextArgPosition();			// start position of ordinary args

		bool good();					// are there any error?
		operator bool();				// ditto
		string message();				// error messages

		string cmdName();				// basename(argv[0])

	Example:
		// Constructor does everything.
		// Meaning of optstr is the same as getopt(3C).

		CmdLineOpts	opts(argc,argv,"ab:");

		if( ! opts.good() ) {		// or if( ! opts )
			cerr << opts.message();
			exit(99);
		}

		// Which options are specified?

		bool aflag = opts.isOn('a');
		bool bflag = opts.isOn('b');
		if( bflag ) {
			string barg = opts.arg('b');
		}

		// Now take care of ordinary arguments.
		// argv[ nextArgPosition() ] is the first non-option arg.

		for(int i=opts.nextArgPosition(); i<argc; ++i) {
			// process argv[i]
		}

	In the above example, the following options are accepted:

		command -a 					# aflag=true
		command -b bar				# bflag=true, barg="bar"
		command -bbar				# bflag=true, barg="bar"
		command -b bar -a file1		# file1 is an ordinary arg.
		command -a -- -x -b			# -- delimits the end of option. bflag=false
		command file1 -a			# -a is not considerd as an option
		command -b bar -b boo		# repetition is not an error. barg="boo"

	The followings are error:

		command -x					# x is not specified in optstr
		command -b					# -b requires arg.
		command -					# a single - is not allowed.
									# command -- - is OK.
		command --a
		command -afoo				# -a can't take arg.

	NOTE:
		Trying to get infomation of nonexistent option or arg is OK.

		bool zflag = opts.isOn('z');	// zflag=false
		string aarg = opts.arg('a');	// aarg=""

	History:
		ver.1.0	'99/08/28	J.Takimoto
		ver.1.1	2000/03/28	J.Takimoto
		ver.1.2	2001/09/26	J.Takimoto

=========================================================================*/
#if defined(__GNUC__) && __GNUC__ == 2 && __GNUC_MINOR__ < 96
#define USE_STRSTREAM
#endif

#ifdef USE_STRSTREAM
#include <strstream>
#else
#include <sstream>
#endif

#include <string>
#include <map>
using namespace std;

class CmdLineOpts {
public:
	//--- constructor
	CmdLineOpts(int argc, const char* const argv[], const char* optstr);

	//--- get info
	bool isOn(char optchar) const;
	string arg(char optchar) const;

	//--- start position (in argv[]) of non-option arg.
	int nextArgPosition() const { return argpos; }

	//--- error status
	bool good() const { return !errflag; }
	operator bool() const { return !errflag; }	// convert to bool
	string message() { return errstr.str(); }

	//--- basename of argv[0]
	string cmdName() { return cmdname; }

private:
	bool parse(int argc, const char* const argv[]);
	void errmsg(const char* msg1, const char* msg2);

	class OptEntry {
	public:
		OptEntry(bool hasarg=false) : isOn(false), hasArg(hasarg) {}
		bool	isOn;
		bool	hasArg;
		string	arg;
	};
	typedef map<char,OptEntry> OptMap;
		
	OptMap options;
	string cmdname;
	bool errflag;
#ifdef USE_STRSTREAM
	ostrstream errstr;
#else
	ostringstream errstr;
#endif
	int argpos;
};

#endif // _CMDLINEOPTS_H_
