#ifndef MS_ILCDTYPEBASE_H__
#define MS_ILCDTYPEBASE_H__

class String;

namespace ms
{

	template<typename TLCD>
	class lcdtype_base
	{
	public:
		lcdtype_base( int rows, int cols )
		: 	_rows( rows),
			_cols( _cols )
		{
		}

		virtual TLCD & getLcd() = 0;

		virtual bool initialize() = 0;

    	virtual bool uninitialize() { return true; }

    	virtual bool activate() { return true; }

    	virtual bool deactivate() { return true; }

		virtual String name() const = 0;

		int rows() const { return _rows; }

		int cols() const { return _cols; }

		void setCursor( int col, int line)
		{
			this->getLcd().setCursor( col, line );
		}

		void print( const String & s ) 
		{
		  this->getLcd().print( s );	
		}

		void clear()
		{
			this->getLcd().clear();
		}
	private:
		int _rows;
		int _cols;

	};


	template<typename LCDTYPE>
	class lcdtype : public lcdtype_base< LCDTYPE >
	{
	};

}

#endif


