#include "erl_nif.h"
#include <unistd.h>

// Prototypes
static ERL_NIF_TERM sassy_compile(ErlNifEnv* env, int argc,
                               const ERL_NIF_TERM argv[]);

static ErlNifFunc nif_funcs[] =
{
    {"compile", 0, sassy_compile}
};

static ERL_NIF_TERM sassy_compile(ErlNifEnv* env, int argc,
                                   const ERL_NIF_TERM argv[])
{
    return enif_make_atom(env, "true");
}


static int on_load(ErlNifEnv* env, void** priv_data, ERL_NIF_TERM load_info)
{
    return 0;
}

ERL_NIF_INIT(sassy, nif_funcs, &on_load, NULL, NULL, NULL);
