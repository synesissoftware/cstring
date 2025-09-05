@echo off

SETLOCAL

SET SCRIPT_DIRECTORY=%~dp0

FOR %%a IN (%*) DO (
	IF /I {--help}=={%%a} (
		ECHO ^
cstring is a small, standalone library, that provides extensible C-style string instances and extensible arrays of such ^

Copyright ^(c^) 2019-2025, Matthew Wilson and Synesis Information Systems ^

Copyright ^(c^) 2008-2019, Matthew Wilson and Synesis Software ^

Runs all ^(matching^) component-test and unit-test programs ^


^

%SCRIPT_DIRECTORY% [ ... flags/options ... ] ^

^

Flags/options: ^

    behaviour: ^

^

    standard flags: ^

^

        --help ^

            displays this help and terminates ^


		EXIT /B 0
	) ELSE (
		ECHO "%SCRIPT_DIRECTORY%: unrecognised argument '%%a'; use --help for usage" 1>&2

		EXIT /B 1
	)
)


FOR /F "usebackq" %%f IN (`DIR /A:-D /B /S %SCRIPT_DIRECTORY% ^| FINDSTR /I test.*unit.*\.exe$`) DO (
	ECHO .
	ECHO executing %%f
	%%f
)

ENDLOCAL

