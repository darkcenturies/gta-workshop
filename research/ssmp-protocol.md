# S&SMP 1.3.1 Patch 1 interface findings

Source: the project's recorded interoperability analysis. Input ssmp.so SHA-256: `100d63366daef700caab4998dfb1dde48bb7c3a5136ac7bca8a912a6237517f3`.

| Interface | Recorded layout/behavior |
| --- | --- |
| RPC 25 ClientJoin | First 32 bits compared with 130002 (0x1FBD2) for S&SMP identification. |
| 0xE7 | 32-bit player ID; reference plugin dispatches OnPlayerConnect. Avoid duplicating a callback already dispatched by the host server. |
| 0xD8 | 16-bit player ID followed by 32-bit key mask. Track previous mask; bind the embedded ID to the actual network sender. |
| 0xE9 inbound | 16-bit vehicle ID followed by 224-byte CHandlingData record. |
| 0xE9 outbound | Same fields plus two zero padding bytes. |

If implementing handling setters before the baseline record arrives, queue operations per vehicle and replay in order. The archived adapter reported 17 handling setters, but this public repository does not include the private server adapter or claim complete client parity.

Unresolved validation: capture E7/D8/E9 with an unmodified matching client; exercise a handling setter and arithmetic update; verify reconnect cleanup and a non-S&SMP client; confirm no duplicate connect/key callbacks. Keep game/AMX calls on their owning thread.
