#include "../include/position.hpp"



Position_long::Position_long(double _close, double _tk, double _sl, double _size, __int64 _time):
    close(_close), tk(_tk), sl(_sl), size(_size), time(_time) {}

bool Position_long::update(double close)
{
    double evolution_pourcent = ((close - this->close) / this->close) * 100;

    if (evolution_pourcent >= this->tk)
	{
		std::cout << "TP" << std::endl;
        return true;
	}
	else if (evolution_pourcent <= -this->sl)
	{
		std::cout << "SL" << std::endl;
        return true;
	}
    return false;
}

INFO_POSITION Position_long::fermeture(double close, __int64 time)
{
    INFO_POSITION info_position;
    info_position.profit =  (close - this->close) * this->size;
    info_position.time = time - this->time;
    info_position.fees = 0; //! je ne sais pas definir les frais

    return info_position;
}

Position_short::Position_short(double _close, double _tk, double _sl, double _size, __int64 _time):
    close(_close), tk(_tk), sl(_sl), size(_size), time(_time) {}


bool Position_short::update(double close)
{
    double evolution = -(((close - this->close) / this->close) * 100); //! il y a un "-" !

    if (evolution >= this->tk)
	{
		std::cout << "TP" << std::endl;
        return true;
	}
	else if (evolution <= -this->sl)
	{
		std::cout << "SL" << std::endl;
        return true;
	}
    return false;
}

INFO_POSITION Position_short::fermeture(double close, __int64 time)
{
    INFO_POSITION info_position;
    info_position.profit =  (this->close - close) * this->size;
    info_position.time = time - this->time;
    info_position.fees = 0;
    return info_position;

}