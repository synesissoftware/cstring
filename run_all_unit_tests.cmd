@echo off

SETLOCAL

SET SCRIPT_DIRECTORY=%~dp0
SET SCRIPT_PATH_DOC=%~n0[%~x0]

FOR %%a IN (%*) DO (
	IF /I {--help}=={%%a} (
		IF EXIST "%SCRIPT_DIRECTORY%.sis\script_info_lines.txt" (

					type "%SCRIPT_DIRECTORY%.sis\script_info_lines.txt"
		)
		ECHO ^
Runs all ^(matching^) component-test and unit-test programs ^

^

%SCRIPT_PATH_DOC% [ ... flags/options ... ] ^

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

