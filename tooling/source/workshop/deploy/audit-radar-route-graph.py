"""Inspect connectivity for the failed long journey recorded in the radar log."""
import json
from pathlib import Path
import struct
import numpy as np
from scipy.sparse import csr_matrix
from scipy.sparse.csgraph import connected_components

data = Path('C:/Games/YourGame/Valkyrie-roadgraph.bin').read_bytes()
magic, version, count, links = struct.unpack_from('<4sIII', data)
dtype = np.dtype([('p','<f4',3),('start','<u4'),('count','<u2'),('flags','<u2'),
                  ('dir','<f4',2),('width','<f4'),('lanes','u1',4)])
n = np.frombuffer(data, dtype=dtype, count=count, offset=16)
targets = np.frombuffer(data, dtype='<u4', count=links, offset=16+36*count)
sources = np.repeat(np.arange(count), n['count'])
assert len(sources) == len(targets)
graph = csr_matrix((np.ones(links, dtype='u1'), (sources, targets)), shape=(count,count))
nw, weak = connected_components(graph, directed=True, connection='weak')
ns, strong = connected_components(graph, directed=True, connection='strong')
sizes = np.bincount(weak)
points = [(15500.7,-7903.5), (4958.7,-4669.5), (15013.2,-8555.1)]
out = []
for x,y in points:
    d = np.sum((n['p'][:,:2] - (x,y))**2, axis=1)
    d[(n['flags'] & 2) != 0] = np.inf
    i = int(np.argmin(d))
    out.append({'input':[x,y], 'node':i, 'position':n['p'][i].tolist(),
                'snap_distance':float(np.sqrt(d[i])), 'weak_component':int(weak[i]),
                'component_size':int(sizes[weak[i]]), 'strong_component':int(strong[i])})
print(json.dumps({'nodes':count,'links':links,'weak_components':nw,'strong_components':ns,
                  'largest_components':sorted(sizes.tolist(), reverse=True)[:8], 'endpoints':out}, indent=2))
