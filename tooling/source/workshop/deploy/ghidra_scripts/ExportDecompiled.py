# Headless Ghidra post-script used by deploy/decompile-ssmp-pe.ps1.
# @author SP-RP
# @category SP-RP

import json
import os

from ghidra.app.decompiler import DecompInterface
from ghidra.program.util import DefinedStringIterator


DECOMPILE_TIMEOUT_SECONDS = 120


def text(value):
    if value is None:
        return u""
    return str(value)


def csv(value):
    value = text(value).replace(u'"', u'""').replace(u'\r', u'\\r').replace(u'\n', u'\\n')
    return u'"' + value + u'"'


def line(stream, value=u""):
    stream.write(text(value))
    stream.write(u"\n")


def clean_block(stream, value):
    # Ghidra pads some declarations and blank lines with spaces. Keep the
    # reconstructed text stable and friendly to Git's whitespace checks.
    for row in text(value).splitlines():
        line(stream, row.rstrip())


def instruction_bytes(instruction):
    try:
        return u"".join(u"%02x" % (value & 0xff) for value in instruction.getBytes())
    except Exception:
        return u"<unreadable>"


args = getScriptArgs()
if len(args) != 1:
    raise ValueError("usage: ExportDecompiled.py <output-directory>")

output = os.path.abspath(args[0])
if not os.path.isdir(output):
    os.makedirs(output)

functions = list(currentProgram.getFunctionManager().getFunctions(True))
functions.sort(key=lambda function: text(function.getEntryPoint()))

internal_functions = 0
decompiled_functions = 0
failed_functions = 0

decompiler = DecompInterface()
decompiler.toggleCCode(True)
decompiler.toggleSyntaxTree(True)
decompiler.setSimplificationStyle("decompile")
if not decompiler.openProgram(currentProgram):
    raise RuntimeError("Ghidra decompiler could not open the imported program")

code = open(os.path.join(output, "decompiled.c"), "w", encoding="utf-8", newline="\n")
disassembly = open(os.path.join(output, "disassembly.txt"), "w", encoding="utf-8", newline="\n")
function_csv = open(os.path.join(output, "functions.csv"), "w", encoding="utf-8", newline="\n")
call_csv = open(os.path.join(output, "calls.csv"), "w", encoding="utf-8", newline="\n")

try:
    line(code, u"/*")
    line(code, u" * Complete best-effort Ghidra decompiler export.")
    line(code, u" * Binary SHA-256: " + text(currentProgram.getExecutableSHA256()))
    line(code, u" * This is reconstructed pseudocode, not original vendor source.")
    line(code, u" */")
    line(code)
    line(function_csv, u"entry,name,namespace,size,external,thunk,decompile_status")
    line(call_csv, u"caller_entry,caller_name,callee_entry,callee_name")

    for function in functions:
        monitor.checkCancelled()
        status = u"external"
        decompiled = None

        if not function.isExternal():
            internal_functions += 1
            result = decompiler.decompileFunction(function, DECOMPILE_TIMEOUT_SECONDS, monitor)
            if result.decompileCompleted() and result.getDecompiledFunction() is not None:
                decompiled = text(result.getDecompiledFunction().getC())
                status = u"ok"
                decompiled_functions += 1
            else:
                status = u"failed: " + text(result.getErrorMessage())
                failed_functions += 1

        line(function_csv, u",".join([
            csv(function.getEntryPoint()),
            csv(function.getName()),
            csv(function.getParentNamespace().getName(True)),
            text(function.getBody().getNumAddresses()),
            text(function.isExternal()).lower(),
            text(function.isThunk()).lower(),
            csv(status),
        ]))

        line(code, u"/* ================================================================")
        line(code, u" * %s  %s" % (function.getEntryPoint(), function.getName(True)))
        line(code, u" * bytes: %s  status: %s" % (function.getBody().getNumAddresses(), status))
        line(code, u" * ================================================================ */")
        if decompiled is not None:
            clean_block(code, decompiled)
        elif not function.isExternal():
            line(code, u"/* Decompiler failed; see disassembly.txt for the complete body. */")
        line(code)

        line(disassembly, u"FUNCTION %s %s" % (function.getEntryPoint(), function.getName(True)))
        instructions = currentProgram.getListing().getInstructions(function.getBody(), True)
        while instructions.hasNext():
            instruction = instructions.next()
            line(disassembly, u"%s\t%s\t%s" % (
                instruction.getAddress(), instruction_bytes(instruction), instruction))
        line(disassembly, u"END FUNCTION")
        line(disassembly)

        callees = list(function.getCalledFunctions(monitor))
        callees.sort(key=lambda callee: text(callee.getEntryPoint()))
        for callee in callees:
            line(call_csv, u",".join([
                csv(function.getEntryPoint()), csv(function.getName()),
                csv(callee.getEntryPoint()), csv(callee.getName()),
            ]))
finally:
    code.close()
    disassembly.close()
    function_csv.close()
    call_csv.close()
    decompiler.dispose()

string_count = 0
strings = open(os.path.join(output, "strings.csv"), "w", encoding="utf-8", newline="\n")
try:
    line(strings, u"address,length,value")
    iterator = DefinedStringIterator.forProgram(currentProgram)
    while iterator.hasNext():
        monitor.checkCancelled()
        data = iterator.next()
        line(strings, u",".join([
            csv(data.getAddress()), text(data.getLength()), csv(data.getDefaultValueRepresentation())
        ]))
        string_count += 1
finally:
    strings.close()

symbols = list(currentProgram.getSymbolTable().getAllSymbols(True))
symbols.sort(key=lambda symbol: (text(symbol.getAddress()), text(symbol.getName())))
symbol_count = 0
symbol_csv = open(os.path.join(output, "symbols.csv"), "w", encoding="utf-8", newline="\n")
try:
    line(symbol_csv, u"address,name,namespace,type,source,external,primary")
    for symbol in symbols:
        monitor.checkCancelled()
        line(symbol_csv, u",".join([
            csv(symbol.getAddress()), csv(symbol.getName()),
            csv(symbol.getParentNamespace().getName(True)), csv(symbol.getSymbolType()),
            csv(symbol.getSource()), text(symbol.isExternal()).lower(),
            text(symbol.isPrimary()).lower(),
        ]))
        symbol_count += 1
finally:
    symbol_csv.close()

metadata = {
    "program": text(currentProgram.getName()),
    "format": text(currentProgram.getExecutableFormat()),
    "language": text(currentProgram.getLanguageID()),
    "compiler": text(currentProgram.getCompilerSpec().getCompilerSpecID()),
    "image_base": text(currentProgram.getImageBase()),
    "md5": text(currentProgram.getExecutableMD5()),
    "sha256": text(currentProgram.getExecutableSHA256()),
    "functions_total": len(functions),
    "functions_internal": internal_functions,
    "functions_decompiled": decompiled_functions,
    "functions_failed": failed_functions,
    "strings": string_count,
    "symbols": symbol_count,
}
metadata_stream = open(os.path.join(output, "metadata.json"), "w", encoding="utf-8", newline="\n")
try:
    json.dump(metadata, metadata_stream, indent=2, sort_keys=True)
    metadata_stream.write(u"\n")
finally:
    metadata_stream.close()

print("EXPORT_COMPLETE output=%s functions=%d internal=%d decompiled=%d failed=%d strings=%d symbols=%d" % (
    output, len(functions), internal_functions, decompiled_functions,
    failed_functions, string_count, symbol_count))
