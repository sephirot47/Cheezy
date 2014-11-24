#include "Printable.h"

//==== Printable ================================================
string operator&(const Printable &p1, const Printable &p2)
{
	return p1.ToString() + " " + p2.ToString();
}

//==== string ===================================================
string operator&(const string &str1, const string &str2)
{
	return str1 + " " + str2;
}

string operator&(const string &str, const Printable &p)
{
	return str + " " + p.ToString();
}

string operator&(const Printable &p, const string &str)
{
	return p.ToString() + " " + str;
}

//==== float ====================================================
string operator&(const float &f, const Printable &p)
{
	char buf[32];
	sprintf(buf, "%f ", f);
	return buf + p.ToString();
}

string operator&(const Printable &p, const float &f)
{
	char buf[32];
	sprintf(buf, " %f", f);
	return p.ToString() + buf;
}

string operator&(const float &f, const string &str)
{
	char buf[32];
	sprintf(buf, "%f ", f);
	return buf + str;
}

string operator&(const string &str, const float &f)
{
	char buf[32];
	sprintf(buf, " %f", f);
	return str + buf;
}

//==== int ======================================================
string operator&(const int &a, const Printable &p)
{
	char buf[32];
	sprintf(buf, "%i ", a);
	return buf + p.ToString();
}

string operator&(const Printable &p, const int &a)
{
	char buf[32];
	sprintf(buf, " %i", a);
	return p.ToString() + buf;
}

string operator&(const int &a, const string &str)
{
	char buf[32];
	sprintf(buf, " %i", a);
	return buf + str;
}

string operator&(const string &str, const int &a)
{
	char buf[32];
	sprintf(buf, "%i ", a);
	return str + buf;
}

//==== bool =====================================================
string operator&(const bool &a, const Printable &p)
{
	char buf[16];
	sprintf(buf, "%s ", a ? "true" : "false");
	return buf + p.ToString();
}

string operator&(const Printable &p, const bool &a)
{
	char buf[16];
	sprintf(buf, " %s", a ? "true" : "false");
	return p.ToString() + buf;
}

string operator&(const bool &a, const string &str)
{
	char buf[16];
	sprintf(buf, " %s", a ? "true" : "false");
	return buf + str;
}

string operator&(const string &str, const bool &a)
{
	char buf[16];
	sprintf(buf, "%s ", a ? "true" : "false");
	return str + buf;
}
