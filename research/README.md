# Research index

This collection records interoperability work and the evidence needed to reproduce it on separately obtained inputs.

- [S&SMP protocol findings](ssmp-protocol.md)
- [Binary identities](targets.json)
- [Ped population findings](../docs/reverse-engineering/PECORE-PED-POPULATION.md)
- [GTA San Andreas PS2: what version 2.01 removed from version 1.00](gta-sa-ps2-1.00-vs-2.01.md)
- [Pinned upstream reference catalog](upstreams.md)
- [Dryxio references and Valkyrie workflow opportunities](dryxio-workflow.md) — dated source review, pinned revisions and proposed evaluations
- [Practical research-to-improvement workflow](../docs/RESEARCH_WORKFLOW.md)

The archive contains conflicting historical coverage claims: an older README said PECore was not completely decompiled, while the later population note records 7,617 recovered functions. Treat the dated target-specific record as the observation, not proof that every function was understood. GTA coverage was recorded as 20,820 of 20,823 functions, with 4,735 names mapped. The full output is now included in [the public archive](../docs/reverse-engineering/README.md). Coverage describes function recovery, not complete semantic understanding or a successful rebuild of the original product.

For new findings use [the finding template](finding-template.md). Record version/hash, method, observed behavior, inference, reproduction and limitations. Never infer compatibility from an address alone.

## Local reproduction

The focused tools accept your own copies of ssmp.so and samp03svr:

```sh
python -m pip install capstone
python deploy/ssmp-rpc-map.py /path/to/ssmp.so
python deploy/ssmp-hookmap.py /path/to/ssmp.so /path/to/samp03svr
```

The hook mapper also invokes GNU objdump. Run it in a compatible environment. Check hashes against targets.json before comparing results. Use work/ for temporary inputs and Ghidra projects; reviewed generated output belongs in docs/reverse-engineering/generated/ with metadata and updated checksums.
