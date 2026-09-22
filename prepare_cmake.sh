#! /bin/bash

Basename=$(basename "$0")
Dir=$(cd "$(dirname "$0")" && pwd)
CMakeDir=${SIS_CMAKE_BUILD_DIR:-$Dir/_build}
if [[ -n "$MSYSTEM" ]]; then

  DefaultMakeCmd=mingw32-make.exe
  MinGW=1
else

  DefaultMakeCmd=make
fi
MakeCmd=${SIS_CMAKE_MAKE_COMMAND:-${SIS_CMAKE_COMMAND:-$DefaultMakeCmd}}
ProjectNameFile="$Dir/.sis/project_name.txt"
ProjectName=$(tr -d '[:space:]' < "$ProjectNameFile")
ScriptPath=$0

AlwaysUseColours=${SIS_CMAKE_ALWAYS_USE_COLOURS:-${SIS_ALWAYS_USE_COLOURS:-0}}
BuildSharedLibs=0
Configuration=Release
ExamplesDisabled=0
MinGW="${MinGW:=0}"
MSVC_MT=0
NO_cxx=0
NO_shwild=0
RunMake=0
SisUseColours=0
STLSoftDirGiven=
TestingDisabled=0
VerboseMakefile=0


# ##########################################################
# colours
#
# Enable when tput is available and either:
#   - AlwaysUseColours is set (overrides NO_COLOR; may set TERM if
#     empty/dumb), or
#   - NO_COLOR is unset, stdout is a TTY, and TERM is not dumb (union of
#     collect-c's "TERM set + TTY" and cstring's "TTY" — empty TERM on a
#     TTY is OK).

SisClr_Blue=
SisClr_Bold=
SisClr_Green=
SisClr_None=
SisClr_Red=
SisClr_Yellow=

for arg in "$@"; do

  case $arg in
    --always-use-colors|--always-use-colours|-A)

      AlwaysUseColours=1
      ;;
  esac
done

if command -v tput >/dev/null 2>&1; then

  if [ $AlwaysUseColours -ne 0 ]; then

    if [ -z "${TERM:-}" ] || [ "$TERM" = "dumb" ]; then

      TERM=xterm-256color
    fi

    SisUseColours=1
  elif [ -z "${NO_COLOR:-}" ] && [ -t 1 ] && [ "${TERM:-}" != "dumb" ]; then

    SisUseColours=1
  fi
fi

if [ $SisUseColours -ne 0 ]; then

  SisClr_Blue=${FG_BLUE:-$(tput setaf 4)}
  SisClr_Bold=${FD_BOLD:-$(tput bold)}
  SisClr_Green=${FG_GREEN:-$(tput setaf 2)}
  SisClr_None=${FD_NONE:-$(tput sgr0)}
  SisClr_Red=${FG_RED:-$(tput setaf 1)}
  SisClr_Yellow=${FG_YELLOW:-$(tput setaf 3)}
fi

CMakeDirClr="${SisClr_Blue}${SisClr_Bold}${CMakeDir}${SisClr_None}"
MakeCmdClr="${SisClr_Blue}${SisClr_Bold}${MakeCmd}${SisClr_None}"
ProjectNameClr="${SisClr_Blue}${SisClr_Bold}${ProjectName}${SisClr_None}"
ScriptPathClr="${SisClr_Blue}${SisClr_Bold}${ScriptPath}${SisClr_None}"


# ##########################################################
# command-line handling

while [[ $# -gt 0 ]]; do

  case $1 in
    --always-use-colors|--always-use-colours|-A)

      # AlwaysUseColours=1 - this is handled by the for loop above
      ;;
    --build-shared-libs)

      BuildSharedLibs=1
      ;;
    --cmake-verbose-makefile|-v)

      VerboseMakefile=1
      ;;
    --debug-configuration|-d)

      Configuration=Debug
      ;;
    --disable-examples|-E)

      ExamplesDisabled=1
      ;;
    --disable-testing|-T)

      TestingDisabled=1
      ;;
    --mingw)

      MinGW=1
      ;;
    --msvc-mt)

      MSVC_MT=1
      ;;
    --no-cpp|--no-cxx|-C)

      NO_cxx=1
      ;;
    --no-shwild)

      NO_shwild=1
      ;;
    --run-make|-m)

      RunMake=1
      ;;
    --stlsoft-root-dir|-s)

      shift
      STLSoftDirGiven=$1
      ;;
    --help)

      [ -f "$Dir/.sis/script_info_lines.txt" ] && cat "$Dir/.sis/script_info_lines.txt"
      cat << EOF
Creates/reinitialises the CMake build script(s)

${ScriptPath} [ ... flags/options ... ]

Flags/options:

    behaviour:

    -A
    --always-use-colors
    --always-use-colours
        forces use of colours even when stdout is not a TTY

    --build-shared-libs
        builds ${ProjectName} as a shared library (BUILD_SHARED_LIBS=ON)

    -v
    --cmake-verbose-makefile
        configures CMake to run verbosely (CMAKE_VERBOSE_MAKEFILE=ON)

    -d
    --debug-configuration
        use Debug configuration (CMAKE_BUILD_TYPE=Debug). Default is Release

    -E
    --disable-examples
        disables building of examples (BUILD_EXAMPLES=OFF)

    -T
    --disable-testing
        disables building of tests (BUILD_TESTING=OFF). Unless testing is
        disabled the STLSoft and xTests libraries will be required to be
        available to CMake

    --mingw
        uses explicitly the "MinGW Makefiles" generator, and defaults the
        make-command to "mingw32-make.exe"

    --msvc-mt
        when using Visual C++ (MSVC), the static runtime library will be
        selected; the default is the dynamic runtime library

    -C
    --no-cpp
    --no-cxx
        omits the C++ API, C++ examples, and remaining C++ tests (CMake
        NO_CSTRING_CPP_API). C unit-tests still require STLSoft and xTests

    --no-shwild
        prevents recognising shwild library (NO_SHWILD=ON); xTests
        pattern-match assertions are then unavailable

    -m
    --run-make
        executes a build via ${MakeCmd} after a successful configure

    -s <dir>
    --stlsoft-root-dir <dir>
        specifies the STLSoft root-directory, which will be passed to CMake
        as the variable STLSOFT, and which will override the environment
        variable STLSOFT (if present)


    standard flags:

    --help
        displays this help and terminates

EOF

      exit 0
      ;;
    *)

      >&2 echo "${ScriptPathClr}: unrecognised argument '${SisClr_Red}${SisClr_Bold}$1${SisClr_None}'; use --help for usage"

      exit 1
      ;;
  esac

  shift
done


# ##########################################################
# main()

mkdir -p "$CMakeDir" || exit 1

cd "$CMakeDir"

echo
echo "Executing CMake for ${ProjectNameClr} (in ${CMakeDirClr})"

if [ $BuildSharedLibs -eq 0 ]; then CMakeBuildSharedLibsFlag="OFF" ; else CMakeBuildSharedLibsFlag="ON" ; fi
if [ $ExamplesDisabled -eq 0 ]; then CMakeBuildExamplesFlag="ON" ; else CMakeBuildExamplesFlag="OFF" ; fi
if [ $MSVC_MT -eq 0 ]; then CMakeMsvcMtFlag="OFF" ; else CMakeMsvcMtFlag="ON" ; fi
if [ $NO_cxx -eq 0 ]; then CMakeNoCppApiFlag="OFF" ; else CMakeNoCppApiFlag="ON" ; fi
if [ $NO_shwild -eq 0 ]; then CMakeNoShwild="OFF" ; else CMakeNoShwild="ON" ; fi
if [ -z $STLSoftDirGiven ]; then CMakeSTLSoftVariable="" ; else CMakeSTLSoftVariable="-DSTLSOFT=$STLSoftDirGiven/" ; fi
if [ $TestingDisabled -eq 0 ]; then CMakeBuildTestingFlag="ON" ; else CMakeBuildTestingFlag="OFF" ; fi
if [ $VerboseMakefile -eq 0 ]; then CMakeVerboseMakefileFlag="OFF" ; else CMakeVerboseMakefileFlag="ON" ; fi

# NOTE: the generator is the *only* thing that may differ between the MinGW
# and the default paths; every -D option is passed in both cases, so that no
# flag can be silently ignored according to the generator selected.

CMakeGeneratorArgs=()

if [ -n "${SIS_CMAKE_GENERATOR:-}" ] && [ $MinGW -eq 0 ]; then

  CMakeGeneratorArgs=(-G "$SIS_CMAKE_GENERATOR")
fi

if [ $MinGW -ne 0 ]; then

  CMakeGeneratorArgs=(-G "MinGW Makefiles")
fi

cmake \
  -DBUILD_EXAMPLES:BOOL=$CMakeBuildExamplesFlag \
  -DBUILD_SHARED_LIBS:BOOL=$CMakeBuildSharedLibsFlag \
  -DBUILD_TESTING:BOOL=$CMakeBuildTestingFlag \
  -DCMAKE_BUILD_TYPE=$Configuration \
  -DCMAKE_VERBOSE_MAKEFILE:BOOL=$CMakeVerboseMakefileFlag \
  -DMSVC_USE_MT:BOOL=$CMakeMsvcMtFlag \
  -DNO_CSTRING_CPP_API:BOOL=$CMakeNoCppApiFlag \
  -DNO_SHWILD:BOOL=$CMakeNoShwild \
  $CMakeSTLSoftVariable \
  "${CMakeGeneratorArgs[@]}" \
  -B "$CMakeDir" \
  -S "$Dir" \
  || (cd ->/dev/null ; exit 1)

status=0

if [ $RunMake -ne 0 ]; then

  echo
  echo "Executing build for ${ProjectNameClr} (via command \`${MakeCmdClr}\`)"

  $MakeCmd
  status=$?
fi

cd ->/dev/null

if [ $VerboseMakefile -ne 0 ]; then

  echo
  echo -e "contents of ${CMakeDirClr}:"
  ls -al "$CMakeDir"
fi

exit $status


# ############################## end of file ############################# #

