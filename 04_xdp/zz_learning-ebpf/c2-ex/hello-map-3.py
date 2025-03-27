#!/usr/bin/python3  
from bcc import BPF
from time import sleep
import ctypes as ct


program = r"""
BPF_PROG_ARRAY(syscall, 300);
BPF_HASH(counter_table);

int hello(void *ctx) {
   u64 uid;
   u64 counter = 0;
   u64 *p;

   uid = bpf_get_current_uid_gid() & 0xFFFFFFFF;
   p = counter_table.lookup(&uid);
   if (p != 0) {
      counter = *p;
   }
   counter++;
   counter_table.update(&uid, &counter);
   return 0;
}

int ignore_opcode(void *ctx) {
    return 0;
}
"""

b = BPF(text=program)
b.attach_raw_tracepoint(tp="sys_enter", fn_name="hello")
ignore_fn = b.load_func("ignore_opcode", BPF.RAW_TRACEPOINT)

#syscall = b.get_syscall_fnname("execve")
#b.attach_kprobe(event=syscall, fn_name="hello")
# Attach to a tracepoint that gets hit for all syscalls 

while True:
    sleep(2)
    s = ""
    for k,v in b["counter_table"].items():
        s += f"ID {k.value}: {v.value}\t"
    print(s)
