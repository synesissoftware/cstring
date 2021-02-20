
#include <cstring/cstring.h>

/*#include <stlsoft/stlsoft.h>*/
#ifndef STLSOFT_NUM_ELEMENTS
# define STLSOFT_NUM_ELEMENTS(ar)   (sizeof(ar) / sizeof(ar[0]))
#endif /*!STLSOFT_NUM_ELEMENTS*/

#include <string.h>

int main()
{
	static char const* strings[] =
	{
		"abc"
	,	"defghijklmno"
	,	"pqrstuvwxyz"
	};

	size_t	cchTotal = 0;

	{ for(size_t i = 0; i != STLSOFT_NUM_ELEMENTS(strings); ++i)
	{
		cchTotal += ::strlen(strings[i]);
	}}

	cstring_t	payload = cstring_t_DEFAULT;

	CSTRING_RC		rc;
	cstring_flags_t flags = CSTRING_F_USE_WIN32_GLOBAL_MEMORY;

	rc = ::cstring_createLenFn(&payload, NULL, 0, flags, NULL, cchTotal, NULL, NULL);
	rc = ::cstring_createLenEx(&payload, NULL, 0, flags, NULL, cchTotal);
	rc = ::cstring_createEx(&payload, NULL, flags, NULL, cchTotal);

	{ for(size_t i = 0; i != STLSOFT_NUM_ELEMENTS(strings); ++i)
	{
		cstring_append(&payload, strings[i]);
	}}

    cstring_destroy(&payload);

	return 0;
}
