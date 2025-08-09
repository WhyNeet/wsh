load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "command",
    srcs = ["command/command.c"],
    hdrs = ["command/command.h"],
    deps = ["//lib:command"],
    visibility = ["//visibility:private"],
)

cc_library(
    name = "redirect",
    srcs = ["redirect/redirect.c"],
    hdrs = ["redirect/redirect.h"],
    deps = ["//lib:redirect"],
    visibility = ["//visibility:private"],
)

cc_library(
    name = "parser",
    srcs = ["parser.c"],
    hdrs = ["parser.h"],
    visibility = ["//visibility:public"],
    deps = ["//lib:pipeline", "command", "redirect"],
)
