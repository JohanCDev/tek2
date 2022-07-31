#include "ikea.h"

#include <criterion/criterion.h>

Test(ikea, bed)
{
    cr_assert_str_eq(get_furniture("bed"), "BJÖRKSNÄS");
}

Test(ikea, chair)
{
    cr_assert_str_eq(get_furniture("chair"), "STIG");
}

Test(ikea, table)
{
    cr_assert_str_eq(get_furniture("table"), "LÄTT");
}