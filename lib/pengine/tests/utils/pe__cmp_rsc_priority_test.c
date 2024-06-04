/*
 * Copyright 2022 the Pacemaker project contributors
 *
 * The version control history for this file may have further details.
 *
 * This source code is licensed under the GNU General Public License version 2
 * or later (GPLv2+) WITHOUT ANY WARRANTY.
 */

#include <crm_internal.h>

#include <crm/common/unittest_internal.h>
#include <crm/pengine/internal.h>

#include "pe_status_private.h"

static pcmk__resource_private_t rsc1_private = { pcmk__rsc_variant_primitive, };
static pcmk__resource_private_t rsc2_private = { pcmk__rsc_variant_primitive, };
static pcmk_resource_t rsc1 = { .private = &rsc1_private };
static pcmk_resource_t rsc2 = { .private = &rsc2_private };

static void
rscs_equal(void **state)
{
    rsc1.private->priority = 0;
    rsc2.private->priority = 0;
    assert_int_equal(pe__cmp_rsc_priority(NULL, NULL), 0);
    assert_int_equal(pe__cmp_rsc_priority(&rsc1, &rsc2), 0);
}

static void
rsc1_first(void **state)
{
    rsc1.private->priority = 1;
    rsc2.private->priority = 0;
    assert_int_equal(pe__cmp_rsc_priority(&rsc1, NULL), -1);
    assert_int_equal(pe__cmp_rsc_priority(&rsc1, &rsc2), -1);
}

static void
rsc2_first(void **state)
{
    rsc1.private->priority = 0;
    rsc2.private->priority = 1;
    assert_int_equal(pe__cmp_rsc_priority(NULL, &rsc2), 1);
    assert_int_equal(pe__cmp_rsc_priority(&rsc1, &rsc2), 1);
}

PCMK__UNIT_TEST(NULL, NULL,
                cmocka_unit_test(rscs_equal),
                cmocka_unit_test(rsc1_first),
                cmocka_unit_test(rsc2_first))
