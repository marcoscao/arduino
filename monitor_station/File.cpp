#include "File.h"
#include "Log.h"
#include "MicroSD.h"

namespace ms
{
		File::File( MicroSD * msd )
			: 	_file(),
				_msd(msd)
		{
		}

		File::~File()
		{
		}

    void File::setMicroSD( MicroSD * p )
    {
      _msd = p;
    }
    
		bool File::create( String fname)
		{
		  	_file = _msd->openFile( fname, FILE_WRITE );
		  	if( not _file )
		  	{
			 	LOG( "File", "error creating file", true, fname );
			 	return false;
		  	}

			LOG( "File","created file", true, fname );
			return true;
		}

	 	bool File::open( String fname )
		{
			if( _file )
			{
				LOG("File", "file already opened. fname: ", true, fname );
				return _false;
			}

		 	_file = _msd->openFile(fname);
		  if (not _file)
		  {
			 LOG( "File", "couldn't open file: ", true, fname );
			return false;
		  }

		  LOG( "File", "opend successfully file: ", true, fname );
			 return true;
		}

		bool File::isFileOpen()
		{
			return _file;
		}

		void File::closeFile()
		{
		  if( not _file )
		  {
			  LOG( "File", "file not currently opened for close" );
			  return;
		  }
			
		  _file.close();
			 LOG( "File","closed");
		}

		bool File::write(String s)
		{
		  if( not _file )
		  {
			 LOG( "File", "file not yet opened for writing" );
			 return false;
		  }

			LOG( "File", "writing: ",true, s );
		  	_file.println( s );
			return true;
		}

		String File::readLine()
		{
			if(not _file )
			{
				LOG("File", "file not yet opened for reading" );
				return String();
			}

		  String r_str;
		 
		  char ch;
		  while (_file.available())
		  {
			 ch = file.read();
			 if (ch == '\n')
			 {
				return r_str;
			 }
			 
			r_str += ch;
		  }

		  LOG("File", "read line: ", true, r_str );
		  return r_str;
		}

}


