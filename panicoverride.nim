{.push stackTrace: off, profiler: off.}

proc rawoutput(msg: string) {.nimcall.} = discard

proc panic(s: string) =
  while true: discard

proc rawQuit(exitCode: int) =
  while true: discard

proc nimArgsPassed() = discard

{.pop.}
