#ifndef MS_FILE_H__
#define MS_FILE_H__

//#include <File.h>
#include <SD.h>

class String;

namespace ms
{
	class MicroSD;

	class File
	{
	public:
		File( MicroSD * msd );

		~File();

    void setMicroSD( MicroSD * p );
    
		bool create( String fname);

	 	bool open( String fname );

		bool isFileOpen();

		void closeFile();

		bool write(String s);

		String readLine();

	private:
		::File _file;
		MicroSD * _msd;
	};

}

#endif

