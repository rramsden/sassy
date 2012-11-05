% @doc
% Some simple tests to assert that the NIF is working correctly
% @end

-module(sassy_test).
-include_lib("eunit/include/eunit.hrl").

outputs_error_message_test() ->
    {error, Msg} = sassy:compile("broken"),
    ?assert(is_list(Msg)).

outputs_compiled_sass_test() ->
    {ok, Compiled} = sassy:compile("$color: red; #test{ color: $color; }"),
    ?assertEqual(Compiled, "#test {\n  color: red; }\n" ).

compiles_from_file_test() ->
    Path = code:priv_dir(sassy),
    Ex1 = Path ++ "/test/example.scss",
    ?assertMatch({ok, _}, sassy:compile_file(Ex1)),

    Ex2 = Path ++ "/test/example.sass",
    ?assertMatch({ok, _}, sassy:compile_file(Ex2)).
