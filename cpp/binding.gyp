{
  "targets": [
    {
      "target_name": "tpx3data",
      "sources": [ "tpx3entrypoint.cpp", "entrypoint.cc", '<!@(ls -1 dataprocessing/*.cpp)' ],
      "libraries": ["/home/jiri/root_build/lib/*.so"],
      "include_dirs": ["/home/jiri/root_build/include/"],
      "cflags_cc!": [ "-fno-rtti", "-fno-exceptions" ],
      'cflags!': [ '-fno-exceptions' ]
    }
  ]
}
