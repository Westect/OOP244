#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include "NonPerishable.h"

using namespace std;
namespace sict {
	void NonPerishable::name(const char * nName)
	{
		if (nName == nullptr)
		{
			delete[] prod_name;
			prod_name = nullptr;
			return;
		}
		else if (prod_name != nullptr)
		{
			delete[] prod_name;
		}
		int leng = strlen(nName);
		prod_name = new char [leng + 1];
		snprintf(prod_name, leng + 1, "%s", nName);
	}

	const char * NonPerishable::name() const
	{
		if (prod_name == nullptr)
		{
			return nullptr;
		}
		else
		{
			return prod_name;
		}
	}

	double NonPerishable::cost() const
	{
		if (taxable)
		{
			return price * (1 + tax_rate);
		}
		else
		{
			return price;
		}
	}

	void NonPerishable::message(const char * msg)
	{
		errmsg.message(msg);
	}

	bool NonPerishable::isClear() const
	{
		if (errmsg.isClear())
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	NonPerishable::NonPerishable(char type)
	{
		prod_type = type;
		sku[0] = '\0';
		prod_name = nullptr;
		unit[0] = '\0';
		qty = 0;
		qtyNeed = 0;
		price = 0;
		taxable = false;
		errmsg.ErrorMessage::clear();
	}

	NonPerishable::NonPerishable(const char* nSku, const char* nName, const char* nUnit, const int nQty, const bool nTaxable, const double nPrice, const int nQtyNeed)
	{
		snprintf(sku, max_sku_length, "%s", nSku);
		prod_name = nullptr;
		name(nName);
		snprintf(unit, max_unit_length, "%s", nUnit);
		qty = nQty;
		taxable = nTaxable;
		price = nPrice;
		this->qtyNeed = nQtyNeed;
		errmsg.ErrorMessage::clear();
	}

	NonPerishable::NonPerishable(const NonPerishable & rhs)  //crash here
	{
		//prod_type = rhs.prod_type;
		//snprintf(sku, max_sku_length, "%s", rhs.sku);
		//name(rhs.prod_name);
		//snprintf(unit, max_unit_length, "%s", rhs.unit);
		//qty = rhs.qty;
		//this->qtyNeed = rhs.qtyNeed;
		//price = rhs.price;
		//taxable = rhs.taxable;
		//if (!rhs.isClear())
		//{
		//	errmsg.message(rhs.errmsg.message());
		//}
		*this = rhs;
	}

	NonPerishable & NonPerishable::operator=(const NonPerishable& rhs)
	{
		if (&rhs == this) return *this;
		prod_type = rhs.prod_type;
		snprintf(sku, max_sku_length, "%s", rhs.sku);
		prod_name = nullptr;
		name(rhs.prod_name);
		snprintf(unit, max_unit_length, "%s", rhs.unit);
		qty = rhs.qty;
		this->qtyNeed = rhs.qtyNeed;
		price = rhs.price;
		taxable = rhs.taxable;
		if (!rhs.isClear())
		{
			errmsg.message(rhs.errmsg.message());
		}
		return *this;
	}


	NonPerishable::~NonPerishable()
	{
		delete[] prod_name;
		prod_name = nullptr;
		errmsg.ErrorMessage::clear();
	}

	std::fstream & NonPerishable::store(std::fstream & file, bool newLine) const
	{
		if (file.is_open())
		file << prod_type << ',' << sku << ',' << prod_name << ',' << unit << ',' << qty << "," << qtyNeed << "," << price << "," << taxable;
		if (newLine) file << endl;
		return file;
	}

	std::fstream & NonPerishable::load(std::fstream & file)	//not sure
	{
		NonPerishable temp;
		temp.prod_name = new char[max_name_length + 1];
		if (file.is_open())
		{
			file >> temp.prod_type >> temp.sku >> temp.prod_name >> temp.unit >> temp.qty >> temp.qtyNeed >> temp.price >> temp.taxable;
			*this = temp;
		}
		delete[] temp.prod_name;
		return file;
	}

	std::ostream & NonPerishable::write(std::ostream & os, bool linear) const	//not sure
	{
		if (linear)
		{
			os << "sku - " << setw(max_sku_length) << sku << '|'
				<< "name - " << setw(20) << prod_name << '|'
				<< "cost - " << setw(97) << price << '|'
				<< "quantity - " << setw(4) << qty << '|'
				<< "unit - " << setw(10) << unit << '|'
				<< "quantity needed - " << setw(4) << qtyNeed << '|';
		}
		else
		{
			os << "Sku: " << sku << "|" << endl
				<< "Name: " << prod_name << "|" << endl
				<< "Price: " << price << "|" << endl;
			if (taxable)
			{
				os << "Price after tax: " << price * (1 + tax_rate) << "|" << endl;
			}
			else os << "N/A" << "|" << endl;
			os << "Quantity On Hand: " << qty << "|" << endl
				<< "Quantity Needeed: " << qtyNeed << "|" << endl;
		}
		return os;
	}

	std::istream & NonPerishable::read(std::istream & is)  //not sure
	{
		char sku[max_sku_length + 1];
		char* prod_name;
		char unit[max_unit_length + 1];
		int qty;
		int qtyNeed;
		double price;
		char taxable[1];
		prod_name = new char[max_name_length + 1];
		cout << "Sku: ";
		is >> sku;
		cout << "Name: ";
		is >> prod_name;
		cout << "Unit: ";
		is >> unit;
		cout << "Taxed? (y/n): ";
		is >> taxable;
		if (taxable[0] != 'y' && taxable[0] != 'Y' && taxable[0] != 'n' && taxable[0] != 'N')
		{
			errmsg.message("Only(Y)es or (N)o are acceptable");
			is.setstate(std::ios::failbit);
		}
		cout << "Price: ";
		is >> price;
		if (is.fail())
		{
			errmsg.message("Invalid Price Entry");
			is.setstate(std::ios::failbit);
		}
		cout << "Quantity on hand: ";
		is >> qty;
		if (is.fail())
		{
			errmsg.message("Invalid Quantity Entry");
			is.setstate(std::ios::failbit);
		}
		cout << "Quantity Needed: ";
		is >> qtyNeed;
		if (is.fail())
		{
			errmsg.message("Invalid Quantity Needed Entry");
		}
		if (errmsg.isClear())
		{
			bool tax;
			if (taxable[0] == 'y' || taxable[0] == 'Y') 
				tax = true;
			else if (taxable[0] == 'n' || taxable[0] == 'N') 
				tax = false;
			snprintf(this->sku, max_sku_length, "%s", sku);
			name(prod_name);
			snprintf(this->unit, max_unit_length, "%s", unit);
			this->qty = qty;
			this->qtyNeed = qtyNeed;
			this->price = price;
			this->taxable = tax;
		}
		delete[] prod_name;
		return is;
	}

	bool NonPerishable::operator==(const char * sku) const
	{
		if (strcmp(this->sku, sku) != 0)
		{
			return false;
		}
		else 
		{
			return true;
		}
	}

	double NonPerishable::total_cost() const
	{
		if (taxable)
		{
			return static_cast<double>(qty) * price * (1 + tax_rate);
		}
		else return static_cast<double>(qty) * price;
	}

	void NonPerishable::quantity(int unit)
	{
		this->qty = unit;
	}

	bool NonPerishable::isEmpty() const
	{
		if (prod_name == nullptr)
			return true;
		else
			return false;
	}

	int NonPerishable::qtyNeeded() const
	{
		return qtyNeed;
	}

	int NonPerishable::quantity() const
	{
		return qty;
	}

	bool NonPerishable::operator>(const char * rhs) const
	{
		if (strcmp(rhs, sku) > 0)
		{
			return true;
		}
		else return false;
	}

	int NonPerishable::operator+=(int nUnit)
	{
		if (nUnit > 0)
		{
			qty += nUnit;
			return qty;
		}
		else return qty;
	}

	bool NonPerishable::operator>(const Product & rhs) const
	{
		if (strcmp(prod_name, rhs.name()) > 0)
		{
			return true;
		}
		else return false;
	}

	std::ostream & operator<<(std::ostream & os, const Product & prod)	//not sure
	{
		return prod.write(os, true);
	}

	std::istream & operator>>(std::istream & is, Product & prod)	//not sure
	{
		prod.read(is);
		return is;
	}

	double operator+=(double & value, const Product & prod)	//not sure
	{
		return value = value + prod.total_cost();
	}

	Product * CreateProduct()
	{
		Product *p = nullptr;
		p = new NonPerishable;
		return p;
	}

}