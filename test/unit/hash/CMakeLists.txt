# MSVC C4310: (cstring_char_t)0xFF truncates when char is signed. The test
# stores that octet on purpose, including the signed-char case.
list(APPEND X_MSVC_CUSTOM_WARNINGS_TO_BE_SUPPRESSED
	4310
)

define_automated_test_program(test.unit.hash entry.c)
