#include "button.h"

size_t get_bn_id(size_t j,size_t i)
{
	size_t temp = 1000;
	temp += j*100;
	temp += i;
	return temp;
}
button::button(size_t _j, size_t _i, field *_parent) :i(_i), j(_j) ,parent(_parent), is_pushed(false)
{
	BN_ID = get_bn_id(j,i);
	symbol = 2;
	InitWindow();
}

bool button::push(bool is_first)
{
	if (is_pushed) return false;
	if (is_first) {symbol = 1;paint_cross();}
	else			{symbol = 0;	paint_zero();}
	is_pushed = true;
	return true;
}
void field::push(size_t ID)
{
	size_t j, i;
	ID-= 1000;
	j = ID/100;
	i = ID%100;
	if (!arr[j][i].push(is_first)) return;
	if (ChekState(j, i)) Victory(is_first);
	is_first = !is_first;
}
field::field(size_t field_size) : _size(field_size)
{
	is_first = true;
	for (size_t  j = 0; j < _size; ++j)
	{
		std::vector<button> temp;
		for (size_t i = 0; i < _size; ++i)
			temp.push_back(button(j,i,this));
		arr.push_back(temp);
	}
}
/*
void check::set_default()
{
	i = _i;	j = _j;
}
bool check::operator ()(size_t _i, size_t _j)
{
	
	state = arr[j][i].get_symbol();
}
*/

bool Nord(size_t &i, size_t &j, size_t size)
{
	if (j > size -2) return false;
	++j;
	return true;
}

bool NordWest(size_t &i, size_t &j, size_t size )
{
	if (j > size -2 || i < 1) return false;
	++j;
	--i;
	return true;
}
bool NordEast(size_t &i, size_t &j, size_t size)
{
	if (j > size -2|| i> size-2) return false;
	++j;
	++i;
	return true;
}

bool South(size_t &i, size_t &j, size_t size)
{
	if (j < 1) return false;
	--j;
	return true;
}
bool SouthEast(size_t &i, size_t &j, size_t size)
{
	if (j <1 || i > size-2) return false;
	--j;
	++i;
	return true;
}
bool SouthWest(size_t &i, size_t &j, size_t size)
{
	if (j <1 || i < 1) return false;
	--j;
	--i;
	return true;
}
bool West(size_t &i, size_t &j, size_t size)
{
	if (i < 1) return false;
	--i;
	return true;
}
bool East(size_t &i, size_t &j, size_t size)
{
	if (i > size -2) return false;
	++i;
	return true;
}
bool (*go[4][2])(size_t &i, size_t &j, size_t size) = {Nord, South, NordWest, SouthEast, NordEast, SouthWest, East,  West};
bool field::Go(int chek_symbol, size_t i, size_t j, bool (**change_i_j)(size_t &i, size_t &j, size_t size) ) const
{
	size_t count = 0;
	for (int k = 0; k < 2; ++k)
	{
		size_t temp_i = i, temp_j = j;
		do
		{
			 ++count;
			if (!change_i_j[k](temp_i, temp_j, _size)) break;
		}while (arr[temp_j][temp_i].get_symbol() == chek_symbol);
	}
	if (count > 5) return true;
	return false;
}
bool field::ChekState(size_t j, size_t i) const
{
	int chek_symbol = arr[j][i].get_symbol();
	for(int sv = 0; sv < 4; ++sv)
	{
		if (Go(chek_symbol, i,j, go[sv])) {return true;}
	}
	return false;
}
