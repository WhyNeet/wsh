load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_binary(
    name = "wsh",
    srcs = ["main.c"],
    deps = [
        "//lib:exec",
        "//lib:input",
        "//lib/parser:parser",
        "//lib:pipeline",
    ],
)
