#ifndef SICT_NONPERISHABLE_H
#define SICT_NONPERISHABLE_H
#include <iostream>
#include "ErrorMessage.h"
#include "Product.h"
namespace sict
{
	const int max_sku_length = 7;
	const int max_unit_length = 10;
	const int max_name_length = 75;
	const double tax_rate = 0.13;

	class NonPerishable : public Product
	{
		char prod_type;
		char sku[max_sku_length + 1];
		char* prod_name;
		char unit[max_unit_length + 1];
		int qty;
		int qtyNeed;
		double price;
		bool taxable;
		ErrorMessage errmsg;

	protected:
		void name(const char*);
		const char* name() const;
		double cost() const;
		void message(const char*);
		bool isClear() const;

	public:
		NonPerishable(char type = 'a');
		NonPerishable(const char* nSku, const char* nName, const char* nUnit, const int nQty = 0, const bool nTaxable = true, const double nPrice = 0, const int nQtyNeeded = 0);
		NonPerishable(const NonPerishable &);
		NonPerishable& operator=(const NonPerishable&);
		~NonPerishable();
		std::fstream& store(std::fstream& file, bool newLine = true) const;	//not sure
		std::fstream& load(std::fstream& file);	//not sure
		std::ostream& write(std::ostream& os, bool linear) const;	//not sure
		std::istream& read(std::istream& is);	//not sure
		bool operator==(const char*) const;
		double total_cost() const;
		void quantity(int);
		bool isEmpty() const;
		int qtyNeeded() const;
		int quantity() const;
		bool operator>(const char*) const;
		int operator+=(int);
		bool operator>(const Product&) const;
	};
	std::ostream& operator<<(std::ostream&, const Product&);	//not sure
	std::istream& operator>>(std::istream&, Product&);	//not sure
	double operator+=(double&, const Product&);	//not sure
	Product* CreateProduct();
}
#endif