load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "command",
    srcs = ["command/command.c"],
    hdrs = ["command/command.h"],
    visibility = ["//visibility:private"],
    deps = ["//lib:command"],
)

cc_library(
    name = "redirect",
    srcs = ["redirect/redirect.c"],
    hdrs = ["redirect/redirect.h"],
    visibility = ["//visibility:private"],
    deps = ["//lib:redirect"],
)

cc_library(
    name = "parser",
    srcs = ["parser.c"],
    hdrs = ["parser.h"],
    visibility = ["//visibility:public"],
    deps = [
        "command",
        "redirect",
        "//lib:pipeline",
    ],
)
