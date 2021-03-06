# Open Enclave Debugging

While you can use GDB to debug the host of the enclave app like any other normal process,
you won’t be able to debug into the enclave’s execution state or memory. To enable that,
you will need to launch the debugger with the **oe-gdb** plug-in.

Before you attempt to debug an enclave, you should ensure that:
- The enclave is built or signed to allow debugging as previously discussed.
- The host app creates the enclave at runtime with the `OE_ENCLAVE_FLAG_DEBUG`.
  For example, in the attestation/host/host.cpp:

```c
oe_result_t result = oe_create_enclave(
    enclavePath,
    OE_ENCLAVE_TYPE_SGX,
    OE_ENCLAVE_FLAG_DEBUG,
    NULL,
    0,
    &enclave);
```

**This flag effectively removes the enclave memory protection.**
It should only be set during development of the app and must be removed before
deployment into production.

You can use oe-gdb on the command line the same way you would use GDB, and is
added to `PATH` by sourcing the `openenclaverc` file in the installed Open Enclave SDK.

For example, to debug the helloworld sample from the sample build folder:

```bash
/opt/openenclave/bin/oe-gdb -arg ./host/helloworld_host ./enc/helloworld_enc.signed
```
Once GDB is started, you can use standard GDB commands to debug through the enclave,
include setting breakpoints, dumping memory addresses and back tracing the execution stack.

## Known issues:

- oe-gdb currently only supports debugging an enclave when the app is launched
  under the debugger. If the debugger is attached to an existing enclave host
  process, it will not be able to step into enclave code.
- The debugger will inevitably catch a SIGILL (Illegal instruction) signal during
  enclave initialization in the mbedtls_aesni_has_support method. This signal can
  be continued without issue as it is handled by Open Enclave as part of the CPUID
  emulation it provides to mbedtls.
- oe-gdb cannot be used to debug enclave code while running in simulation mode.
