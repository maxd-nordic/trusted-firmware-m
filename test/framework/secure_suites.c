/*
 * Copyright (c) 2017-2019, Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "test_framework_integ_test.h"
#include "test_framework_integ_test_helper.h"
#include "test_framework.h"

/* Service specific includes */
#include "test/suites/sst/secure/sst_tests.h"
#include "test/suites/audit/secure/audit_s_tests.h"
#include "test/suites/attestation/secure/attestation_s_tests.h"
#include "test/suites/invert/secure/invert_s_tests.h"
#include "test/suites/crypto/secure/crypto_s_tests.h"

static struct test_suite_t test_suites[] = {
#if TFM_LVL == 3
#ifdef SERVICES_TEST_S
    /* List test cases which compliant with level 3 isolation */
    /* Secure initial attestation service test cases */
    {&register_testsuite_s_attestation_interface, 0, 0, 0},
#endif /* SERVICES_TEST_S */

#else /* TFM_LVL == 3 */

#ifdef SERVICES_TEST_S
    /* List test cases which compliant with level 1 isolation */

#ifdef PSA_PROTECTED_STORAGE
    {&register_testsuite_s_psa_ps_interface, 0, 0, 0},
#else /* PSA_PROTECTED_STORAGE */
    /* Secure SST test cases */
    {&register_testsuite_s_sst_sec_interface, 0, 0, 0},
    {&register_testsuite_s_sst_reliability, 0, 0, 0},

#if defined(SST_ROLLBACK_PROTECTION) && defined(SST_ENCRYPTION)
    {&register_testsuite_s_rollback_protection, 0, 0, 0},
#endif
#endif /* PSA_PROTECTED_STORAGE */

    /* Secure Audit Logging test cases */
    {&register_testsuite_s_audit_interface, 0, 0, 0},

    /* Crypto test cases */
    {&register_testsuite_s_crypto_interface, 0, 0, 0},

    /* Secure initial attestation service test cases */
    {&register_testsuite_s_attestation_interface, 0, 0, 0},

#ifdef TFM_PARTITION_TEST_CORE
    /* Secure invert test cases */
    /* Note: since this is sample code, only run if test services are enabled */
    {&register_testsuite_s_invert_interface, 0, 0, 0},
#endif /* TFM_PARTITION_TEST_CORE*/
#endif /* SERVICES_TEST_S */
#endif /* TFM_LVL == 3 */
};

static void setup_integ_test(void)
{
    /* Left empty intentionally, currently implemented
     * test suites require no setup
     */
}

static void tear_down_integ_test(void)
{
    /* Left empty intentionally, currently implemented
     * test suites require no tear down
     */
}

void start_integ_test(void)
{
    setup_integ_test();
    integ_test("Secure",
               test_suites,
               sizeof(test_suites)/sizeof(test_suites[0]));
    tear_down_integ_test();
}
