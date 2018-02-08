#include "Perishable.h"

using namespace std;
namespace sict
{

	Perishable::Perishable() : NonPerishable('P')
	{
		Date();
	}


	Perishable::~Perishable()
	{
	}

	std::fstream & Perishable::store(std::fstream & file, bool newLine) const
	{
		NonPerishable::store(file, false);
		file << ',' << date;
		if (newLine)
			file << '\n';
		return file;
	}

	std::fstream & Perishable::load(std::fstream & file)
	{
		NonPerishable::load(file);
		//file >> date;
		//file.get();
		if (file.is_open())
		{
			int year_;
			int month_;
			int day_;
			file.ignore();
			file >> year_;
			file.ignore();
			file >> month_;
			file.ignore();
			file >> day_;
			this->date = Date(year_, month_, day_);
		}
		return file;
	}

	std::ostream & Perishable::write(std::ostream & os, bool linear) const
	{
		if (isEmpty())
			return os;
		NonPerishable::write(os, linear);
		if (!isClear())
			return os;
		if (linear)
			os << date;
		else
			os << endl << "Expiry date: " << date;
		return os;
	}

	std::istream & Perishable::read(std::istream & is)
	{
		NonPerishable::read(is);
		if (isClear())
		{
			cout << "Expiry date (YYYY/MM/DD): ";
			Date temp;
			is >> temp;
			if (temp.bad())
			{
				switch (temp.errCode())
				{
				case 1: message("Invalid Price Entry");
					break;
				case 2: message("Invalid Year in Date Entry");
					break;
				case 3: message("Invalid Month in Date Entry");
					break;
				case 4: message("Invalid Day in Date Entry");
				}
				is.setstate(std::ios::failbit);
			}
			if (!is.fail())
				date = temp;
		}
		return is;
	}

	const Date & Perishable::expiry() const
	{
		return date;
	}

	Product * CreatePerishable()
	{
		Product *p = nullptr;
		p = new Perishable;
		return p;
	}

}