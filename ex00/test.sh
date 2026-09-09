#!/bin/sh

PROGRAM="./convert"

print_title()
{
    echo
    echo "============================================================"
    echo "$1"
    echo "============================================================"
}

run_test()
{
    echo
    echo "> $PROGRAM \"$1\""
    $PROGRAM "$1"
}

echo "Building..."
make re || exit 1


print_title "SUBJECT TESTS"

run_test "0"
run_test "nan"
run_test "42.0f"


print_title "CHAR TESTS"

run_test "a"
run_test "Z"
run_test "*"
run_test "+"
run_test "31"
run_test "32"
run_test "65"
run_test "126"
run_test "127"
run_test "128"
run_test "200"


print_title "INT BASIC TESTS"

run_test "0"
run_test "1"
run_test "-1"
run_test "42"
run_test "-42"


print_title "INT LIMIT TESTS"

run_test "2147483647"
run_test "-2147483648"

# INT_MAX + 1
run_test "2147483648"

# INT_MIN - 1
run_test "-2147483649"

# Extremely large integer
run_test "999999999999999999999999999999999"


print_title "FLOAT BASIC TESTS"

run_test "0.0f"
run_test "42.0f"
run_test "-42.0f"
run_test "42.5f"
run_test "-42.5f"
run_test "42.42f"


print_title "FLOAT -> INT TRUNCATION TESTS"

# Should truncate toward zero
run_test "42.9f"
run_test "42.1f"
run_test "-42.9f"
run_test "-42.1f"


print_title "DOUBLE BASIC TESTS"

run_test "0.0"
run_test "42.0"
run_test "-42.0"
run_test "42.5"
run_test "-42.5"
run_test "42.42"


print_title "DOUBLE -> INT TRUNCATION TESTS"

# Should truncate toward zero
run_test "42.9"
run_test "42.1"
run_test "-42.9"
run_test "-42.1"


print_title "DOUBLE VALUES OUTSIDE INT RANGE"

run_test "2147483648.0"
run_test "-2147483649.0"


print_title "DOUBLE -> FLOAT RANGE TESTS"

# Larger than the normal float range, but still representable by double
run_test "999999999999999999999999999999999999999.0"


print_title "FLOAT OVERFLOW TEST"

# Too large to be represented as a normal float
run_test "999999999999999999999999999999999999999.0f"


print_title "FLOAT PSEUDO-LITERALS"

run_test "nanf"
run_test "+inff"
run_test "-inff"


print_title "DOUBLE PSEUDO-LITERALS"

run_test "nan"
run_test "+inf"
run_test "-inf"


print_title "FLOAT PRECISION TESTS"

run_test "1.1f"
run_test "3.141592f"
run_test "123.456789f"


print_title "DOUBLE PRECISION TESTS"

run_test "1.1"
run_test "3.14159265358979"
run_test "123.456789012345"


print_title "INT -> FLOAT PRECISION TEST"

# float cannot exactly represent every integer at this size
run_test "16777216"
run_test "16777217"
run_test "16777218"


print_title "VALID DECIMAL FORM TESTS"

run_test ".5f"
run_test "42.f"
run_test ".5"
run_test "42."


print_title "INVALID INPUT TESTS"

run_test ""
run_test "abc"
run_test "42abc"
run_test "42.0ff"
run_test "42.0.0"
run_test "--42"
run_test "++42"
run_test "+-42"
run_test "-+42"
run_test "42 100"


print_title "SPECIAL SINGLE CHARACTER TESTS"

# These are valid chars, not invalid literals
run_test "+"
run_test "-"
run_test "."
run_test "f"

print_title "EXTRA TESTS"
run_test "16777217.1"
run_test "-16777217.1"

run_test "127.9"
run_test "128.0"
run_test "-128.0"
run_test "-129.0"

run_test "2147483647.9"
run_test "2147483648.1"
run_test "-2147483648.9"
run_test "-2147483649.1"


echo
echo "============================================================"
echo "ALL TESTS FINISHED"
echo "============================================================"