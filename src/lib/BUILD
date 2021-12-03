load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "TrojanMap",
    srcs = ["trojanmap.cc"],
    hdrs = ["trojanmap.h"],
    deps = ["@opencv//:opencv"],
    data = ["map.csv", 
    "input.jpg", 
    "output0.avi",
    "TSP_output_001.avi",
    "TSP_output_002.avi",
    "TSP_output_003.avi"],
    visibility = ["//visibility:public"],
)