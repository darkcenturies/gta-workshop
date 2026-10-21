# Investigative game film workflow

An investigative GTA film needs separate records for what was captured, what
the research establishes, and what was authored for the story. This method
comes from a GTA San Andreas MTA production using Blender 4.5.8, FFmpeg and
native game captures. It covers editing and evidence presentation rather than
distributing a capture adapter or game assets.

## Evidence and staging

Retain original source dates, image crops, file identities and analysis inputs.
A forum report is evidence that somebody reported an event; it is not proof of
the event. A manual acknowledgement, matching string or regional asset
difference cannot establish an encounter without further evidence. Label
authored reconstructions and keep promotional imagery outside evidence footage.

Use native actor controls and verify displacement through a complete take.
Playing a walking animation alone can leave a character walking in place.
Bone/ground diagnostics help explain a problem but do not establish visible
foot contact. Similarly, a camera above terrain can still lose its subject
behind a foreground ridge. Inspect actual movement, framing and occlusion.

For a partially concealed model, record a matching empty control. Collision
probes and placement coordinates guide setup; rendered comparison establishes
which pixels are visible. Magnify those pixels without synthesizing anatomical
detail. In a reconstruction, distinguish observed contours from hypotheses,
and an imported asset from an image-derived recovery.

## Research presentation

Use authentic source excerpts and images, introduced progressively. Sparse
handwriting can circle an observation or ask a question without turning the
page into a wall of explanation. Animate handwriting strokes with pressure,
pooling and paper-grain response; synchronize quiet friction to stroke/lift
intervals. Keep sources and comprehensive credits available outside the frame.

Use the game's actual map and verify world-to-image coordinates, axis direction
and bounds. Combine the reported areas and selected search route into one
briefing. Broad regional markers and measured camera positions are different
things. Repeated map or paper scenes can feel like padding even when their
labels change.

## Source identity and sound

Record each take's source identity, source in/out and destination interval.
Compare hashes as well as names, including backgrounds behind research cards.
Two differently named files may contain the same take. A still contact sheet
helps identify visual repetition, but complete motion review is still needed.
Cache signatures should include the complete edit record and treatment version.

Capture the game's own audio session and retain its clock observations. Client
frame ticks, host receipts and audio-start clocks need an explicit mapping;
file modification time alone is not synchronization. Preserve the difference
between recorded ambience, extracted game sounds and authored foley. Identify
music and source ranges, then measure loudness/true peak on the encoded result.
Filter execution success does not prove its requested target was reached.

Subtitles must follow the actual narration edit. If narration is split around
visuals, map each source interval to its own destination rather than applying
one global shift. Optional long-film subtitles and burned phone captions are
different delivery choices; avoid accidentally displaying both.

## Reusable graphics and delivery

Compare an extruded logo against its original colour artwork, including all
lettering. A close-looking mesh can lose the identity of the flat mark. For
smoke, distinguish a composited overlay, placed animated volume sequences and
a newly simulated interaction. Packed Blender images do not preserve external
VDB sequences; retain and validate those references separately.

Reframe every shot for vertical delivery and inspect the subject and captions
inside the phone interface. Keep the source intervals and crop coordinates.
Verify the export's duration, frame count, colour range, decoding and sound.
Report sampled image checks separately from complete playback review.

Maintain one explicit current-delivery record. If a locked destination forces
a new export filename, update all upload links to that actual file rather than
assuming the older unversioned master changed.

## Retention

Catalogue originals in place: final exports, editing footage, voice/audio,
scripts, editable scenes, fonts, textures, external volumes and provenance.
Delete generated frame sequences and segment renders only when the retained
inputs can reproduce them. Cache reuse code must tolerate a signature whose
corresponding rendered file was removed.

Deleting raw takes while retaining compressed editing copies is a quality
tradeoff. Obtain the owner's decision, compare counts and representative decoded
frames, and protect any unmatched final source. Preserve diagnostic images and
control takes. Use a reviewed explicit deletion list, reject path escapes and
reparse traversal, skip locked files, record actual reclaimed space and verify
protected hashes afterward. Large directories, installed games, repositories,
and private media collections are not automatically disposable.

## Evidence limits and references

The local exercise verified retained counterparts for every native source used
in the final edit, preserved editable scene dependencies and compared protected
asset hashes after cleanup. Those checks do not establish lossless equivalence
between raw and compressed footage, new cross-version runtime compatibility,
or complete human playback of a new edit. Capture implementation, project
assets, private paths and source media remain withheld; this is a reusable
method return. The published capture-tool route was consulted for scope, not
executed as proof of this private adapter's behavior.

- [Capture integrity tool route](VALKYRIE-DEVELOPMENT-TOOLS.md#valkyrie-capture)
- [Reference catalog](workshop/CATALOG.md#presentation)
- [MTA camera matrix](https://wiki.multitheftauto.com/wiki/SetCameraMatrix)
- [MTA native vision](https://wiki.multitheftauto.com/wiki/SetCameraGoggleEffect)
- [Blender 4.5 volumes](https://docs.blender.org/manual/en/4.5/modeling/volumes/index.html)
- [FFmpeg filters](https://ffmpeg.org/ffmpeg-filters.html)
