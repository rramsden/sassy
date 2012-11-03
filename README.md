Sassy - Sass for Erlang
=======================

Simple Erlang NIF wrapper around [libsass](https://github.com/hcatlin/libsass)
enabling you to compile Sass scripts.

Usage
=====

    sassy:compile("$red = #test { color: red }").
    sassy:compile_file("./myfile.scss").
