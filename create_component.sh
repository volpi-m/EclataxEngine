#!bin/bash

display_help()
{
    echo "Wrong set of arguments, try with the following :"
    echo "bash create_components.sh nameOfTheComponent"
}

if [[ "$#" -ne 1 ]]
then
    display_help
    exit 84
fi

create_template()
{
    INPUT="template"

    touch src/engine/ecs/components/$1Component.hpp

    while IFS= read -r LINE
    do
	echo "${LINE//TEMPLATE/$1}" >> src/engine/ecs/components/$1Component.hpp
    done < "$INPUT"

    INPUT="template_test"
    
    touch tests/component/test_$1.cpp

    while IFS= read -r LINE
    do
	echo "${LINE//TEMPLATE/$1}" >> tests/component/test_$1.cpp
    done < "$INPUT"
}

create_template $1
