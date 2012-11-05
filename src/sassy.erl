%% @doc
%% @author Richard Ramsden <richard@rramsden.ca>
%% Sassy - Simple NIF wrapper around libsass
%% @end

-module(sassy).
-export([compile/1, compile_file/1]).
-on_load(init/0).
-define(nif_stub, nif_stub_error(?LINE)).

%% ============================================================
%% Public API
%% ============================================================

%% @doc
%% Compile a file given the pathname
%% @end
-spec compile_file(string()) -> {ok, string()} | {error, string()}.

compile_file(Path) ->
    case file:read_file(Path) of
        {ok, Bin} ->
            compile(binary_to_list(Bin));
        Err ->
            Err
    end.

%% @doc
%% Compile a string
%% @end
-spec compile(string()) -> {ok, string()} | {error, string()}.

compile(_Str) ->
    ?nif_stub.

%% ============================================================
%% NIF callbacks
%% ============================================================

nif_stub_error(Line) ->
    erlang:nif_error({nif_not_loaded,module,?MODULE,line,Line}).

init() ->
    PrivDir = case code:priv_dir(?MODULE) of
        {error, bad_name} ->
            EbinDir = filename:dirname(code:which(?MODULE)),
            AppPath = filename:dirname(EbinDir),
            filename:join(AppPath, "priv");
        Path ->
            Path
    end,
    erlang:load_nif(filename:join(PrivDir, ?MODULE), 0).






















