import sys,unittest
from pathlib import Path
from types import SimpleNamespace
sys.path.insert(0,str(Path(__file__).resolve().parents[1]))
from sa_hanim_topology import parent_tags,require_native_links

def table(*pairs):
    return [SimpleNamespace(id=tag,type=flags) for tag,flags in pairs]

class TopologyTests(unittest.TestCase):
    def test_source_branch_preserves_stock_core(self):
        donor=table((0,0),(1,0),(2,0),(3,0),(5,1))
        expanded=table((0,0),(1,0),(2,0),(3,2),(5,1),(311,0),(312,1))
        parents=require_native_links(expanded,donor)
        self.assertEqual(parents[5],3)
        self.assertEqual(parents[311],2)

    def test_inserted_spine_joint_rejects_stock_local_rotations(self):
        donor=table((0,0),(1,0),(2,0),(3,0),(5,1))
        # Isolated full-world source pose baking can hide this incompatibility.
        broken=table((0,0),(1,0),(2,0),(311,0),(312,0),(3,0),(5,1))
        with self.assertRaisesRegex(ValueError,'Native core parent'):
            require_native_links(broken,donor)

    def test_missing_native_tag_is_rejected(self):
        with self.assertRaises(ValueError):
            require_native_links(table((0,0),(310,1)),table((0,0),(1,1)))

    def test_native_stack_capacity_is_enforced(self):
        for count in (64,65):
            chain=table(*[(i,1 if i==count-1 else 0) for i in range(count)])
            if count==64:self.assertEqual(len(require_native_links(chain,chain)),64)
            else:
                with self.assertRaisesRegex(ValueError,'64 joints'):require_native_links(chain,chain)

    def test_invalid_stack_and_flags_are_rejected(self):
        for malformed in (table((0,0)),table((0,1),(1,1)),table((0,0),(0,1)),table((0,4))):
            with self.assertRaises(ValueError):parent_tags(malformed)

if __name__=='__main__':unittest.main()
