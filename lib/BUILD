load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "input",
    srcs = ["input/input.c"],
    hdrs = ["input/input.h"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "command",
    srcs = ["command/command.c"],
    hdrs = ["command/command.h"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "exec",
    srcs = ["exec/exec.c"],
    hdrs = ["exec/exec.h"],
    visibility = ["//visibility:public"],
    deps = ["//lib:pipeline"],
)

cc_library(
    name = "pipeline",
    srcs = ["pipeline/pipeline.c"],
    hdrs = ["pipeline/pipeline.h"],
    visibility = ["//visibility:public"],
    deps = ["//lib:command"],
)

cc_library(
    name = "parser",
    srcs = ["parser/parser.c"],
    hdrs = ["parser/parser.h"],
    visibility = ["//visibility:public"],
    deps = ["//lib:pipeline"],
)
