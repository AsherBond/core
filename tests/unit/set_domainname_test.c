#include <test.h>

#include <cf3.defs.h>
#include <sysinfo_priv.h>
#include <eval_context.h>
#include <item_lib.h>
#include <rlist.h>
#include <enterprise_extension.h>


static struct hostent h = {
    .h_name = "laptop.intra.cfengine.com"
};

#ifdef SOLARIS
int gethostname(char *name, ARG_UNUSED int len)
#else
int gethostname(char *name, ARG_UNUSED size_t len)
#endif
{
    strcpy(name, "laptop.intra");
    return 0;
}

struct hostent *gethostbyname(const char *name)
{
    assert_string_equal(name, "laptop.intra");
    return &h;
}

typedef struct
{
    const char *name;
    const char *value;
    bool found;
} ExpectedVars;

ExpectedVars expected_vars[] =
{
    {"host", "laptop.intra"},
    {"fqhost", "laptop.intra.cfengine.com"},
    {"uqhost", "laptop.intra"},
    {"domain", "cfengine.com"},
};

static void TestSysVar(EvalContext *ctx, const char *lval, const char *expected)
{
    VarRef *ref = VarRefParseFromScope(lval, "sys");
    assert_string_equal(expected, EvalContextVariableGet(ctx, ref, NULL));
    VarRefDestroy(ref);

    assert_string_equal(expected, EvalContextVariableGetSpecial(ctx, SPECIAL_SCOPE_SYS, lval, NULL));
    assert_string_equal(expected, EvalContextVariableGetSpecialString(ctx, SPECIAL_SCOPE_SYS, lval));
}

static void test_set_names(void)
{
    EvalContext *ctx = EvalContextNew();
    DetectDomainName(ctx, "laptop.intra");

    assert_true(!EvalContextClassGet(ctx, NULL, "laptop_intra_cfengine_com")->is_soft);
    assert_true(!EvalContextClassGet(ctx, NULL, "intra_cfengine_com")->is_soft);
    assert_true(!EvalContextClassGet(ctx, NULL, "cfengine_com")->is_soft);
    assert_true(!EvalContextClassGet(ctx, NULL, "com")->is_soft);
    assert_true(!EvalContextClassGet(ctx, NULL, "laptop_intra")->is_soft);

    TestSysVar(ctx, "host", "laptop.intra");
    TestSysVar(ctx, "fqhost", "laptop.intra.cfengine.com");
    TestSysVar(ctx, "uqhost", "laptop.intra");
    TestSysVar(ctx, "domain", "cfengine.com");

    EvalContextDestroy(ctx);
}

int main()
{
    PRINT_TEST_BANNER();
    const UnitTest tests[] =
    {
        unit_test(test_set_names),
    };

    return run_tests(tests);
}
