// Copyright (c) 2013, the Dart project authors.  Please see the AUTHORS file
// for details. All rights reserved. Use of this source code is governed by a
// BSD-style license that can be found in the LICENSE file.

import "dart:io";

import "package:expect/expect.dart";
import "package:async_helper/async_helper.dart";

void testSignals(int usr1Expect,
                 int usr2Expect,
                 [int usr1Send,
                  int usr2Send,
                  bool shouldFail = false]) {
  if (usr1Send == null) usr1Send = usr1Expect;
  if (usr2Send == null) usr2Send = usr2Expect;
  asyncStart();
  Process.start(Platform.executable,
      [Platform.script.resolve('signals_test_script.dart').toFilePath(),
       usr1Expect.toString(),
       usr2Expect.toString()])
    .then((process) {
      process.stdin.close();
      process.stderr.drain();
      int v = 0;
      process.stdout.listen((out) {
        // Send as many signals as 'ready\n' received on stdout
        int count = out.where((c) => c == '\n'.codeUnitAt(0)).length;
        for (int i = 0; i < count; i++) {
          if (v < usr1Send) {
            process.kill(ProcessSignal.SIGUSR1);
          } else if (v < usr1Send + usr2Send) {
            process.kill(ProcessSignal.SIGUSR2);
          }
          v++;
        }
      });
      process.exitCode.then((exitCode) {
        Expect.equals(shouldFail, exitCode != 0);
        asyncEnd();
      });
    });
}


void testListenCancel() {
  for (int i = 0; i < 10; i++) {
    ProcessSignal.SIGINT.watch().listen(null).cancel();
  }
}

void main() {
  testListenCancel();
  if (Platform.isWindows) return;
  testSignals(0, 0);
  testSignals(1, 0);
  testSignals(0, 1);
  testSignals(1, 1);
  testSignals(10, 10);
  testSignals(10, 1);
  testSignals(1, 10);
  testSignals(1, 0, 0, 1, true);
  testSignals(0, 1, 1, 0, true);
}
