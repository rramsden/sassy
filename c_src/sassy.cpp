#include "libsass/sass_interface.h"
#include "erl_nif.h"

static ERL_NIF_TERM sassy_compile(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]);

static ErlNifFunc nif_funcs[] =
{
    {"compile", 1, sassy_compile}
};

static inline ERL_NIF_TERM make_atom(ErlNifEnv* env, const char* name)
{
  ERL_NIF_TERM ret;
  if(enif_make_existing_atom(env, name, &ret, ERL_NIF_LATIN1)) {
    return ret;
  }
  return enif_make_atom(env, name);
}

static inline ERL_NIF_TERM make_ok(ErlNifEnv* env, const char* mesg)
{
      ERL_NIF_TERM ok = make_atom(env, "ok");
      ERL_NIF_TERM str = enif_make_string(env, mesg, ERL_NIF_LATIN1);
      return enif_make_tuple2(env, ok, str);
}


static inline ERL_NIF_TERM make_error(ErlNifEnv* env, const char* mesg)
{
      ERL_NIF_TERM error = make_atom(env, "error");
      ERL_NIF_TERM str = enif_make_string(env, mesg, ERL_NIF_LATIN1);
      return enif_make_tuple2(env, error, str);
}

static ERL_NIF_TERM sassy_compile(ErlNifEnv* env, int argc,
                                   const ERL_NIF_TERM argv[])
{
    ERL_NIF_TERM ret;
    int len;
    enif_get_list_length(env, argv[0], (unsigned int*)&len);
    char buffer[len];
    enif_get_string(env, argv[0], (char*)buffer, len + 1, ERL_NIF_LATIN1);

    struct sass_context* ctx = sass_new_context();
    ctx->options.include_paths = "";
    ctx->options.output_style = SASS_STYLE_NESTED;
    ctx->source_string = (char*)buffer;

    sass_compile(ctx);

    if (ctx->error_status) {
      if (ctx->error_message) {
        ret = make_error(env, ctx->error_message);
      } else {
        ret = make_error(env, "An error occured; no error message available.");
      }
    } else if (ctx->output_string) {
      ret = make_ok(env, ctx->output_string);
    } else {
      ret = make_error(env, "Unkown internal error.");
    }

    sass_free_context(ctx);

    return ret;
}

static int on_load(ErlNifEnv* env, void** priv_data, ERL_NIF_TERM load_info)
{
    return 0;
}

ERL_NIF_INIT(sassy, nif_funcs, &on_load, NULL, NULL, NULL);
