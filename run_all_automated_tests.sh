#! /bin/bash

ScriptPath=$0
Dir=$(cd "$(dirname "$ScriptPath")" && pwd)
Basename=$(basename "$ScriptPath")
CMakeDir=${SIS_CMAKE_BUILD_DIR:-$Dir/_build}
ProjectNameFile="$Dir/.sis/project_name.txt"
ProjectName=$(tr -d '[:space:]' < "$ProjectNameFile")


UnitOnly=0
ComponentOnly=0
ForwardedArgs=()


# ##########################################################
# command-line handling

while [[ $# -gt 0 ]]; do

  case $1 in
    --unit-only)

      UnitOnly=1
      ;;
    --component-only)

      ComponentOnly=1
      ;;
    --help)

      [ -f "$Dir/.sis/script_info_lines.txt" ] && cat "$Dir/.sis/script_info_lines.txt"
      cat << EOF
Runs all (matching) automated test programs (unit and component)

$ScriptPath [ ... flags/options ... ]

Flags/options:

    behaviour:

    --unit-only
        runs only unit-test programs

    --component-only
        runs only component-test programs

    (all other flags are forwarded to the category runner script)


    standard flags:

    --help
        displays this help and terminates

EOF

      exit 0
      ;;
    *)

      ForwardedArgs+=("$1")
      ;;
  esac

  shift
done

if [ $UnitOnly -ne 0 ] && [ $ComponentOnly -ne 0 ]; then

  >&2 echo "$ScriptPath: --unit-only and --component-only are mutually exclusive"

  exit 1
fi


# ##########################################################
# main()

status=0

if [ $UnitOnly -ne 0 ]; then

  "$Dir/run_all_unit_tests.sh" "${ForwardedArgs[@]}"
  exit $?
fi

if [ $ComponentOnly -ne 0 ]; then

  "$Dir/run_all_component_tests.sh" "${ForwardedArgs[@]}"
  exit $?
fi

echo "Running all ${ProjectName} automated test programs (unit and component)"

"$Dir/run_all_unit_tests.sh" "${ForwardedArgs[@]}"
status=$?

if [ $status -eq 0 ]; then

  "$Dir/run_all_component_tests.sh" "${ForwardedArgs[@]}"
  status=$?
fi

exit $status


# ############################## end of file ############################# #
