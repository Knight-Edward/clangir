// RUN: %clang_cc1 -triple x86_64-unknown-linux-gnu -std=c++20 -fclangir-enable -mconstructor-aliases -clangir-disable-emit-cxx-default -emit-cir %s -o %t.cir
// RUN: FileCheck --input-file=%t.cir %s

extern "C" int printf(char const*, ...);
struct C {
  C()  { printf("++A\n"); }
  ~C()  { printf("--A\n"); }
};
void dtor1() {
  {
    C c;
  }
  printf("Done\n");
}

// CHECK: cir.func @_Z5dtor1v()
// CHECK:   cir.scope {
// CHECK:     %4 = cir.alloca !ty_22C22, cir.ptr <!ty_22C22>, ["c", init] {alignment = 1 : i64}
// CHECK:     cir.call @_ZN1CC2Ev(%4) : (!cir.ptr<!ty_22C22>) -> ()
// CHECK:     cir.call @_ZN1CD2Ev(%4) : (!cir.ptr<!ty_22C22>) -> ()
// CHECK:   }