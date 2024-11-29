#!/usr/bin/python3
from bcc import BPF
from time import sleep
import ctypes as ct

program = r"""
BPF_HASH(counter_table);

int hello(struct bpf_raw_tracepoint_args *ctx) {
    u64 opcode = ctx->args[1];
    u64 counter = 0;
    u64 *p;
    
    p = counter_table.lookup(&opcode);
    if (p != 0) {
        counter = *p;
    }
    counter++; 
    counter_table.update(&opcode, &counter);  
    return 0;
}
"""

b = BPF(text=program)
b.attach_raw_tracepoint(tp="sys_enter", fn_name="hello")

# Print the syscall counts every 2 seconds
while True:
    sleep(2)
    s = ""
    for k,v in b["counter_table"].items():
        s += f"ID {k.value}: {v.value}\t"
    print(s)