"""Decode HAnim's implicit depth-first parent stack without game assets."""

def parent_tags(table):
    result = {}
    stack = [None]
    parent = None
    for bone in table:
        if bone.id in result or bone.type & ~3:
            raise ValueError('Duplicate tag or invalid HAnim topology flags')
        result[bone.id] = parent
        if bone.type & 2:
            stack.append(parent)
        parent = bone.id
        if bone.type & 1:
            if not stack:
                raise ValueError('Unbalanced HAnim parent stack')
            parent = stack.pop()
    if stack:
        raise ValueError('Unbalanced HAnim parent stack')
    return result

def require_native_links(actual, donor):
    if len(actual) > 64:
        raise ValueError('Native skinned-clump limit is 64 joints')
    actual_parents = parent_tags(actual)
    for tag, parent in parent_tags(donor).items():
        if tag not in actual_parents or actual_parents[tag] != parent:
            raise ValueError('Native core parent links differ from the stock clip hierarchy')
    return actual_parents
